#include "inc/oled/ssd1306.h"
#include "hardware/adc.h"
#include "common.h"

#define I2C_PORT i2c1
#define PINO_SCL 14
#define PINO_SDA 15

#define JOYSTICK_Y 0
#define JOYSTICK_BUTTON 22

void init_menu();
void load_menu(LOGIC_GATE *gate);
void get_selection(LOGIC_GATE *gate);
void draw_menu();

void init_menu()
{
    i2c_init(I2C_PORT, 400 * 1000); // I2C Inicialização. Usando 400Khz.
    gpio_set_function(PINO_SCL, GPIO_FUNC_I2C);
    gpio_set_function(PINO_SDA, GPIO_FUNC_I2C);
    gpio_pull_up(PINO_SCL);
    gpio_pull_up(PINO_SDA);
    ssd1306_init();

    // inicindo adc
    adc_init();
    adc_gpio_init(26);
    adc_gpio_init(27);
}

void load_menu(LOGIC_GATE *gate, uint8_t *buffer){
    static LOGIC_GATE last_gate = -1;

    draw_menu(buffer,0);

}


void draw_menu(uint8_t buffer, LOGIC_GATE selection){
    display_clear(buffer);

    char nomes[7][5] = {"AND", "OR", "NOT","NAND","NOR","XOR","XNOR"};

    // desenhando alternativas
    for (int i = 0; i < 7; i++)
    {
        char text[40] = "";
        sprintf(text, "%d. %s", i,nomes[i]);
        ssd1306_draw_string(buffer, 8, 16 * (1 + i) + 4, text);
    }

    // desenhando seletor
    draw_retangulo(buffer, 0, 16 * selection - 2, ssd1306_width - 1, 16 * selection + 8 + 4);

    display_draw(buffer);

}