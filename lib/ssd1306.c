#include "ssd1306.h"
#include "font.h"
#include <stdio.h>

void ssd1306_init(ssd1306_t *ssd, uint8_t width, uint8_t height, bool external_vcc, uint8_t address, i2c_inst_t *i2c)
{
  ssd->width = width;
  ssd->height = height;
  ssd->pages = height / 8U;
  ssd->address = address;
  ssd->i2c_port = i2c;
  ssd->bufsize = ssd->pages * ssd->width + 1;
  ssd->ram_buffer = calloc(ssd->bufsize, sizeof(uint8_t));
  ssd->ram_buffer[0] = 0x40;
  ssd->port_buffer[0] = 0x80;
}

void ssd1306_config(ssd1306_t *ssd)
{
  ssd1306_command(ssd, SET_DISP | 0x00);
  ssd1306_command(ssd, SET_MEM_ADDR);
  ssd1306_command(ssd, 0x01);
  ssd1306_command(ssd, SET_DISP_START_LINE | 0x00);
  ssd1306_command(ssd, SET_SEG_REMAP | 0x01);
  ssd1306_command(ssd, SET_MUX_RATIO);
  ssd1306_command(ssd, HEIGHT - 1);
  ssd1306_command(ssd, SET_COM_OUT_DIR | 0x08);
  ssd1306_command(ssd, SET_DISP_OFFSET);
  ssd1306_command(ssd, 0x00);
  ssd1306_command(ssd, SET_COM_PIN_CFG);
  ssd1306_command(ssd, 0x12);
  ssd1306_command(ssd, SET_DISP_CLK_DIV);
  ssd1306_command(ssd, 0x80);
  ssd1306_command(ssd, SET_PRECHARGE);
  ssd1306_command(ssd, 0xF1);
  ssd1306_command(ssd, SET_VCOM_DESEL);
  ssd1306_command(ssd, 0x30);
  ssd1306_command(ssd, SET_CONTRAST);
  ssd1306_command(ssd, 0xFF);
  ssd1306_command(ssd, SET_ENTIRE_ON);
  ssd1306_command(ssd, SET_NORM_INV);
  ssd1306_command(ssd, SET_CHARGE_PUMP);
  ssd1306_command(ssd, 0x14);
  ssd1306_command(ssd, SET_DISP | 0x01);
}

void ssd1306_command(ssd1306_t *ssd, uint8_t command)
{
  ssd->port_buffer[1] = command;
  i2c_write_blocking(
      ssd->i2c_port,
      ssd->address,
      ssd->port_buffer,
      2,
      false);
}

void ssd1306_send_data(ssd1306_t *ssd)
{
  ssd1306_command(ssd, SET_COL_ADDR);
  ssd1306_command(ssd, 0);
  ssd1306_command(ssd, ssd->width - 1);
  ssd1306_command(ssd, SET_PAGE_ADDR);
  ssd1306_command(ssd, 0);
  ssd1306_command(ssd, ssd->pages - 1);
  i2c_write_blocking(
      ssd->i2c_port,
      ssd->address,
      ssd->ram_buffer,
      ssd->bufsize,
      false);
}

void ssd1306_pixel(ssd1306_t *ssd, uint8_t x, uint8_t y, bool value)
{
  uint16_t index = (y >> 3) + (x << 3) + 1;
  uint8_t pixel = (y & 0x07);
  if (value)
  {
    ssd->ram_buffer[index] |= (1 << pixel);
  }
  else
  {
    ssd->ram_buffer[index] &= ~(1 << pixel);
  }
}

void ssd1306_fill(ssd1306_t *ssd, bool value)
{
  for (uint8_t y = 0; y < ssd->height; ++y)
  {
    for (uint8_t x = 0; x < ssd->width; ++x)
    {
      ssd1306_pixel(ssd, x, y, value);
    }
  }
}

void ssd1306_draw_char(ssd1306_t *ssd, char c, uint8_t x, uint8_t y)
{
  uint16_t index = 0;
  char ver = c;

  if (c >= 'A' && c <= 'Z')
  {
    index = (c - 'A' + 11) * 8; // delimita as letras maiúsculas
  }
  else if (c >= 'a' && c <= 'z')
  {
    index = (c - 'a' + 37) * 8; // delimita letras maiúsculas
  }
  else if (c >= '0' && c <= '9')
  {
    index = (c - '0' + 1) * 8; // adiciona o deslocamento necessário
  }

  for (uint8_t i = 8; i > 0; --i) // reposicionamento dos bits
  {
    for (uint8_t j = 0; j < 8; ++j)
    {
      // printf("%08b", ((font[index + j]) >> (7 - i))  & 0x01); //DEBUGGING: Antes de verificar a impressão comente a mensagem inicial da função main
      ssd1306_pixel(ssd, x + i, y + j, ((font[index + j]) >> (7 - i)) & 0x01);
    }
    // printf("\n"); //DEBUGGING: Antes de verificar a impressão comente a mensagem inicial da função main
  }
}

void ssd1306_draw_string(ssd1306_t *ssd, const char *str, uint8_t x, uint8_t y)
{
  while (*str)
  {
    ssd1306_draw_char(ssd, *str++, x, y);
    x += 8;
    if (x + 8 >= ssd->width)
    {
      x = 0;
      y += 8;
    }
    if (y + 8 >= ssd->height)
    {
      break;
    }
  }
}