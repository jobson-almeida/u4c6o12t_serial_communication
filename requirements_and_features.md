## Funcionalidades do Projeto

1. Modificação da Biblioteca font.h
- [x] Adicionar caracteres minúsculos à biblioteca font.h. Use sua criatividade para criar os novos caracteres.

2. Entrada de caracteres via PC
- [x] Utilize o Serial Monitor do VS Code para digitar os caracteres.
- [x] Cada caractere digitado no Serial Monitor deve ser exibido no display SSD1306.
Observação: Apenas um caractere será enviado de cada vez, não é necessário suportar o envio de strings completas.
- [x] Quando um número entre 0 e 9 for digitado, um símbolo correspondente ao número deve ser exibido, também, na matriz 5x5 WS2812.

3. Interação com o Botão A
- [x] Pressionar o botão A deve alternar o estado do LED RGB Verde (ligado/desligado).
    - [x] Uma mensagem informativa sobre o estado do LED deve ser exibida no display SSD1306
    - [x] Um texto descritivo sobre a operação deve ser enviado ao Serial Monitor.

4. Interação com o Botão B
- [x] Pressionar o botão A deve alternar o estado do LED RGB Azul (ligado/desligado).
    - [x] Uma mensagem informativa sobre o estado do LED deve ser exibida no display SSD1306
    - [x] Um texto descritivo sobre a operação deve ser enviado ao Serial Monitor.
 
5. Extra
- [x] Modularizar os setups
    - [x] I2C
    - [x] UART
    - [x] Botões
    - [x] LEDs
    - [x] Matriz RGB
    - [x] Interrupção UART
    - [x] Interrupção dos botões
    - [x] Arquivos de fontes - representação na posição original 
    - [x] Função de desenho do caracter, especificamente no reposicionamento dos bits para formação do caracter, conforme seu formato original 
 
## Requisitos do Projeto

Para o desenvolvimento, devem ser seguidos os seguintes requisitos:<br>
- [] Uso de interrupções.<br>
- [x] Debouncing.<br>
- [x] Controle de LEDs comuns.<br>
- [x] Controle de LEDs WS2812.<br>
- [x] Utilização do Display 128 x 64.<br>
- [x] Envio de informação pela UART.<br>
- [x] Organização do código.<br>