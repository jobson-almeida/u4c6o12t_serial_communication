## Funcionalidades do Projeto

1. Modificação da Biblioteca font.h
- [x] Adicionar caracteres minúsculos à biblioteca font.h. Use sua criatividade para criar os novos caracteres.

2. Entrada de caracteres via PC
- [] Utilize o Serial Monitor do VS Code para digitar os caracteres.
- [] Cada caractere digitado no Serial Monitor deve ser exibido no display SSD1306.
Observação: Apenas um caractere será enviado de cada vez, não é necessário suportar o envio de strings completas.
- [] Quando um número entre 0 e 9 for digitado, um símbolo correspondente ao número deve ser exibido, também, na matriz 5x5 WS2812.

3. Interação com o Botão A
- [] Pressionar o botão A deve alternar o estado do LED RGB Verde (ligado/desligado).
    - [] Uma mensagem informativa sobre o estado do LED deve ser exibida no display SSD1306
    - [] Um texto descritivo sobre a operação deve ser enviado ao Serial Monitor.

4. Interação com o Botão B
- [] Pressionar o botão A deve alternar o estado do LED RGB Azul (ligado/desligado).
    - [] Uma mensagem informativa sobre o estado do LED deve ser exibida no display SSD1306
    - [] Um texto descritivo sobre a operação deve ser enviado ao Serial Monitor.
 
5. Extra
- [] Modularizar os setups
    - [x] I2C
    - [] UART
    - [x] Botões
    - [] LEDs
    - [] Matriz RGB
 
## Requisitos do Projeto

Para o desenvolvimento, devem ser seguidos os seguintes requisitos:<br>
- [] Uso de interrupções.<br>
- [] Debouncing.<br>
- [] Controle de LEDs comuns e LEDs WS2812.<br>
- [] Utilização do Display 128 x 64.<br>
- [] Envio de informação pela UART.<br>
- [] Organização do código.<br>