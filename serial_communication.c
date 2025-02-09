#include <stdlib.h>
#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/i2c.h"
#include "hardware/clocks.h"
#include "lib/ssd1306.h"
#include "serial_communication.pio.h"
#include "lib/font.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define IC2_ADDRESS 0x3C

// definição das macros da UART - seleção da UART, GPIOs e baud rate
#define UART_ID uart0           // seleciona a UART0
#define BAUD_RATE 115200        // define a taxa de transmissão
#define UART_TX_PIN 0           // GPIO usada para TX
#define UART_RX_PIN 1           // GPIO usada para RX
#define DATA_BITS 8             // limite máximo de dados a serem transmitidos
#define STOP_BITS 1             // sinaliza o fim de um caractere transmitido e fornece um período de tempo para o receptor se preparar para o próximo caractere
#define PARITY UART_PARITY_NONE // método simples de detecção de erros durante a transmissão de dados

// definção das macros dos botões - GPIOs
#define BUTTON_A 5
#define BUTTON_B 6
#define BUTTON_C 22 //  botão de seleção do joystick, definido para alterar a cor dos LEDs da matriz

// definção das macros dos LEDs - GPIOs
#define LED_GREEN 11
#define LED_BLUE 12

// definção da macro da matriz de LEDS - GPIO
#define MATRIX_RGB 7

PIO pio;     // variável de entrada e saída programável
uint sm;     // variável relacionada a máquina de estados
uint offset; // variável que representa o offset da memória de instruções

volatile uint32_t last_time = 0; // variável auxiliar para deboucing

ssd1306_t ssd; // variável da estrutura do display


// interrupção da UART //////////////////////////////////////////////////////////
void uart_rx_interruption()
{
    //
}

// handler de interrupção dos botões /////////////////////////////////////////
void button_interruption_gpio_irq_handler(uint gpio, uint32_t events)
{
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    // verificar se passou tempo o bastante desde o último evento
    if (current_time - last_time > 250000) // 250 ms de debouncing
    {
        last_time = current_time; // atualiza o tempo do último evento
        char *notification;

        if (gpio_get(BUTTON_A) == 0)
        {
            // altera o estado do LED verde (ligado/desligado).
            gpio_put(LED_GREEN, !gpio_get(LED_GREEN));

            // notifica o status do LED verde
            notification = gpio_get(LED_GREEN) ? "LED VERDE ON" : "LED VERDE OFF";
            printf("botão c\n");
        }
        if (gpio_get(BUTTON_B) == 0)
        {
            // altera o estado do LED azul (ligado/desligado).
            gpio_put(LED_BLUE, !gpio_get(LED_BLUE));

            // notifica o status do LED azul
            notification = gpio_get(LED_BLUE) ? "LED BLUE ON" : "LED BLUE OFF";
        }
        if (gpio_get(BUTTON_C) == 0)
        {
            printf("botão sem uso\n");
        }
        printf("%s\n", notification);
    }
    gpio_acknowledge_irq(gpio, events); // limpa a interrupção
}

// setups ////////////////////////////////////////////////////////////////////////////
void uart_setup()
{
    // inicia a UART com uma taxa de transmissão básica.
    uart_init(UART_ID, 2400);

    // define os pinos TX e RX usando a função de seleção de GPIOs para UART
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART); // Configura o pino 0 para TX
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART); // Configura o pino 1 para RX

    // define a taxa de transmissão real selecionada, mais próxima da solicitada
    int __unused real_rate = uart_set_baudrate(UART_ID, BAUD_RATE);
    // printf("%d\n", real_rate);

    // desliga o controle de fluxo UART CTS/RTS
    uart_set_hw_flow(UART_ID, false, false);

    // define o formato dos dados
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

    // desliga FIFO's - first in, first out
    uart_set_fifo_enabled(UART_ID, false);

    // configura e habilita os manipuladores de interrupção
    irq_set_exclusive_handler(UART0_IRQ, uart_rx_interruption);
    irq_set_enabled(UART0_IRQ, true);

    // habilita o UART para enviar interrupções - somente RX
    uart_set_irq_enables(UART_ID, true, false);
}

void i2c_setup()
{
    // initializa a I2C usando 400Khz.
    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);                       // define o SDA utilizando a função de GPIO para I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);                       // define o SCL utilizando a função de GPIO para I2C
    gpio_pull_up(I2C_SDA);                                           // define o pull up da linha de dados
    gpio_pull_up(I2C_SCL);                                           // define o pull up na linha do clock
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, IC2_ADDRESS, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd);                                            // configura o display
    ssd1306_send_data(&ssd);                                         // envia os dados para o display
}

void button_setup()
{
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);

    gpio_init(BUTTON_C);
    gpio_set_dir(BUTTON_C, GPIO_IN);
    gpio_pull_up(BUTTON_C);
}

void led_setup()
{
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_put(LED_GREEN, false);

    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_put(LED_BLUE, false);
}

void matrix_setup()
{
    pio = pio0;
    offset = pio_add_program(pio, &serial_communication_program);
    sm = pio_claim_unused_sm(pio, true);
    serial_communication_program_init(pio, sm, offset, MATRIX_RGB);
}

///////////////////////////////////////////////////////////////////////

int main()
{

    // Limpa o display. O display inicia com todos os pixels apagados.
    // ssd1306_fill(&ssd, false);
    // ssd1306_send_data(&ssd);

    // bool cor = true;

    button_setup();

    // habilitar as interrupções para exibir os frames que representam os números de 0-9
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &button_interruption_gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &button_interruption_gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_C, GPIO_IRQ_EDGE_FALL, true, &button_interruption_gpio_irq_handler);

    while (true)
    {
        // cor = !cor;
        // Atualiza o conteúdo do display com animações
        // ssd1306_fill(&ssd, !cor);                           // Limpa o display
        // ssd1306_rect(&ssd, 3, 3, 122, 58, cor, !cor);       // Desenha um retângulo
        // ssd1306_draw_string(&ssd, "CEPEDI   TIC37", 8, 10); // Desenha uma string
        // ssd1306_draw_string(&ssd, "EMBARCATECH", 20, 30);   // Desenha uma string
        // ssd1306_draw_string(&ssd, "PROF WILTON", 15, 48);   // Desenha uma string
        // ssd1306_send_data(&ssd);                            // Atualiza o display

        sleep_ms(1000);
    }
}