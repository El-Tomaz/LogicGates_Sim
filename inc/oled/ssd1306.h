#include <string.h>
#include "ssd1306_i2c.h"
extern void calculate_render_area_buffer_length(struct render_area *area);
extern void ssd1306_send_command(uint8_t cmd);
extern void ssd1306_send_command_list(uint8_t *ssd, int number);
extern void ssd1306_send_buffer(uint8_t ssd[], int buffer_length);
extern void ssd1306_init();
extern void ssd1306_scroll(bool set);
extern void render_on_display(uint8_t *ssd, struct render_area *area);
extern void ssd1306_set_pixel(uint8_t *ssd, int x, int y, bool set);
extern void ssd1306_draw_line(uint8_t *ssd, int x_0, int y_0, int x_1, int y_1, bool set);
extern void ssd1306_draw_char(uint8_t *ssd, int16_t x, int16_t y, uint8_t character);
extern void ssd1306_draw_string(uint8_t *ssd, int16_t x, int16_t y, char *string);
extern void ssd1306_command(ssd1306_t *ssd, uint8_t command);
extern void ssd1306_config(ssd1306_t *ssd);
extern void ssd1306_init_bm(ssd1306_t *ssd, uint8_t width, uint8_t height, bool external_vcc, uint8_t address, i2c_inst_t *i2c);
extern void ssd1306_send_data(ssd1306_t *ssd);
extern void ssd1306_draw_bitmap(ssd1306_t *ssd, const uint8_t *bitmap);

// Minhas funcoes vvvvv

void ssd1306_clear(uint8_t *buffer)
{
    memset(buffer, 0, ssd1306_buffer_length);
}


void ssd1306_show(uint8_t *buffer)
{
    // config display

    struct render_area frame_area = {
        start_column : 0,
        end_column : ssd1306_width - 1,
        start_page : 0,
        end_page : ssd1306_n_pages - 1
    };

    render_on_display(buffer, &frame_area);
}

void ssd1306_draw_empty_square(uint8_t *buffer, int x1, int y1, int x2, int y2)
{
    ssd1306_draw_line(buffer, x1, y1, x1, y2, 1);
    ssd1306_draw_line(buffer, x1, y1, x2, y1, 1);
    ssd1306_draw_line(buffer, x2, y1, x2, y2, 1);
    ssd1306_draw_line(buffer, x1, y2, x2, y2, 1);
}

uint8_t buffer_display[ssd1306_buffer_length];
struct render_area frame_area = {
    start_column : 0,
    end_column : ssd1306_width - 1,
    start_page : 0,
    end_page : ssd1306_n_pages - 1
};


// função escrita no display.
void print_texto(char *msg, uint pos_x, uint pos_y)
{
    ssd1306_draw_string(buffer_display, pos_x, pos_y, msg);
    render_on_display(buffer_display, &frame_area);
}

// o desenho do retangulo fará o papel de seletor
void print_retangulo(int x1, int y1, int x2, int y2)
{
    ssd1306_draw_empty_square(buffer_display, x1, y1, x2, y2);
    render_on_display(buffer_display, &frame_area);
}

void clear_display()
{
    memset(buffer_display, 0, ssd1306_buffer_length);
}
