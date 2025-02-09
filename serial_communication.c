#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/clocks.h"
#include "lib/ssd1306.h"
#include "serial_communication.pio.h"
#include "lib/font.h"

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define IC2_ADDRESS 0x3C

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

ssd1306_t ssd; // variável da estrutura do display

void setup_i2c()
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

int main()
{

    // Limpa o display. O display inicia com todos os pixels apagados.
    // ssd1306_fill(&ssd, false);
    // ssd1306_send_data(&ssd);

    // bool cor = true;
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