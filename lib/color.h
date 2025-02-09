/**
 * @brief Tipo de dado para agrupar valor RGB
 * @param r Valor referente a cor vermelha
 * @param g Valor referente a cor verde
 * @param b Valor referente a cor azul
 */
typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGBColor;

// cores primárias no padrão RGB
RGBColor color[15] = {
    {255, 0, 0}, {255, 255, 255}, {0, 255, 0}, {0, 0, 255}, {255, 255, 0}, {0, 255, 255}, {255, 0, 255}, {192, 192, 192}, {128, 128, 128}, {128, 0, 0}, {128, 128, 0}, {0, 128, 0}, {128, 0, 128}, {0, 128, 128}, {0, 0, 128}};
