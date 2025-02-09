#ifndef MATRIX
#define MATRIX

#include "hardware/pio.h"

/**
 * @brief Função que permite configurar a intensidade dos leds de um frame
 * @param frame Item da animação que se deseja aplicar a intensidade
 * @param intensity Valor atribuido a intensidade de brilho do LED de 0.0 à 1.0
 */
double *apply_intensity_frame(uint32_t frame, double intensity);

/**
 * @brief Função que permite a conversão da cor, no format RGB, em um valor binário
 * @param r Valor referente a cor vermelha
 * @param g Valor referente a cor verde
 * @param b Valor referente a cor azul
 */
uint32_t rgb(uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Função que permite aplicar uma determinada cor, no padrão RGB, ao led
 * @note O efeito luminoso produzido pela cor será influencido pela intensidade definida nos framee
 * @param frame Valor referente ao número que se deseja aplicar a cor
 * @param pio Valor referente a interface PIO
 * @param sm Valor referente a máquina de estados
 * @param r Valor referente a cor vermelha
 * @param g Valor referente a cor verde
 * @param b Valor referente a cor azul
 */
void apply_color_frame(double *frame, PIO pio, uint sm, uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Função responsável por exibir um determinado número na matriz de LEDs
 * @note O efeito produzido pela cor será influencido pela intensidade predefinida no frame
 * @param pio Valor referente a interface PIO
 * @param sm Valor referente a máquina de estados
 * @param r Valor referente a cor vermelha
 * @param g Valor referente a cor verde
 * @param b Valor referente a cor azul
 * @param frame Valor referente ao número (0-9) que se deseja visualizar na matriz
 */
void show_number(PIO pio, uint sm, uint8_t r, uint8_t g, uint8_t b, double intensity, size_t frame);

#endif