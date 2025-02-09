#include "matrix.h"
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"

#define NUM_PIXELS 25 // quantidade de LEds da matriz

/*
 * frames/itens estão no formato hexadecimal, que representam cada um dos números de 0 a 9, uma representação específica da matriz 5x5 incluída na placa de desenvolvimento BitLogLab
 * O valor 0x1FCCF3F, por exemplo, se refere a 1111111001100111100111111 que corresponde a exibição do número '0' na matriz da placa educacional BitDogLab
 * O valor também é representado pela matriz:
 *  11111
 *  11001
 *  10011
 *  11001
 *  11111
 *
 *  Os valores dos frames se encontram na ordem de 0 à 9
 */
uint32_t numbers_frames[11] = {0x1FCCF3F, 0x03C0F03, 0x1FC7C7F, 0x1FC3F1F, 0x1BDFF03, 0x1F1FF1F, 0x1F1FF7F, 0x1FC0F03, 0x1FCFF3F, 0x1FCFF1F, 0x0000000};

double *apply_intensity_frame(uint32_t frame, double intensity)
{
    double *frames = (double *)calloc(1, sizeof(double));
    size_t index_number = 0;

    for (size_t j = 0; j < NUM_PIXELS; j++)
    {
        // APENAS PARA DEBUGGING
        // printf("%b\t & \t%025b\t", frame, 0x1 << (NUM_PIXELS - j) - 1);
        int binary = (int)frame & (0x1 << ((NUM_PIXELS - j) - 1));
        // APENAS PARA DEBUGGING
        // printf("= \t%025b\n", binary);

        if (binary > 0)
        {
            frames[index_number] = intensity;
        }
        else
        {
            frames[index_number] = 0.0;
        }
        // APENAS PARA DEBUGGING
        // printf("%025b\t %.1f\n", binary, frames[index_number]);
        index_number++;
    }
    free(frames);
    return frames;
}

uint32_t rgb(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 16) |
           ((uint32_t)(g) << 24) |
           (uint32_t)(b << 8);
}

void apply_color_frame(double *frame, PIO pio, uint sm, uint8_t r, uint8_t g, uint8_t b)
{
    for (size_t i = 0; i < NUM_PIXELS; ++i)
    {
        // APENAS PARA DEBUGGING
        // printf("%.1f\n", frame[(NUM_PIXELS-1) - i]);
        uint32_t color = rgb(frame[(NUM_PIXELS - 1) - i] * r, frame[(NUM_PIXELS - 1) - i] * g, frame[(NUM_PIXELS - 1) - i] * b);
        pio_sm_put_blocking(pio, sm, color);
    }
}

void show_number(PIO pio, uint sm, uint8_t r, uint8_t g, uint8_t b, double intensity, size_t frame)
{
    // APENAS PARA DEBUGGING
    // printf("%d %d %d %d %.1f %d\n", sm, r, g, b, intensity, frame);
    apply_color_frame(apply_intensity_frame(numbers_frames[frame], intensity), pio, sm, r, g, b);
}
