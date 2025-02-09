## Comunicação Serial

Conforme o solicitado, esse estudo se propõe em demonstrar um pouco da experiência inicial com o comunicação serial **UART**, **I2C** e alguns dos periféficos presentes da **Raspeberry Pi Pico W** e sua plataforma base de desenvolvimento educacional **BitDogLab**. 

Para tal contou-se com o display **SSD1306**, contido na placa, e a manipulação da biblioteca **font.h**, cujo o conteúdo conta com as representações do alfabeto maiúsculo e minúsculo, além dos números inteiros de 0 a 9 - em seu formato visual original.

Na interação com o display destaca-se a conexão realizada por meio da conexão USB - microcontrolador -, a simulação com o **Wokwi** em ambiente de desenvolvimento, o protocolo de comunicação UART, para envio dos caracteres e o I2C, para comunicação direta com o SSD1306.

Por meio do serial monitor foi possível interagir com a **Matriz de LEDs RGB**, botões, e com o próprio display. No ambiente de simulação também foi possível demonstrar, por meio de interrupções, as trocas de caracteres no display, dos números na matriz e do envio de notificações decorrentes dos botões e LEDs.