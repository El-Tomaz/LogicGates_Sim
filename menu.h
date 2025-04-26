#include "inc/oled/ssd1306.h"
#include "hardware/adc.h"
#include "common.h"
#include "bitmaps.h"

#define I2C_PORT i2c1
#define PINO_SCL 14
#define PINO_SDA 15

#define JOYSTICK_Y 0
#define JOYSTICK_BUTTON 22

void init_menu();
void load_menu(LOGIC_GATE *gate, uint8_t *buffer);
void get_selection(LOGIC_GATE *gate);
void draw_gate(LOGIC_GATE gate, uint8_t *buffer);

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

    adc_select_input(0); //adc on y axix
}

int joystick_read(){
    const int upper_limit = 3000;
    const int lower_limit = 1000;

    if(adc_read() > upper_limit){ //when adc is high, direction is down
        return -1;
    }
    else if(adc_read() < lower_limit){ // when adc is low value, direction is up
        return 1;
    }

    return 0;

}

void load_menu(LOGIC_GATE *gate, uint8_t *buffer){
    static LOGIC_GATE last_gate = -1; //

    if(joystick_read() == 1){ // joystick is pointing down
        if(*gate < 6){
            *gate = *gate + 1; //go to next gate
        } else{
            *gate = 0; //use this to get "circular effect"
        }
    }
    else if(joystick_read() == -1){
        if(*gate > 0){
            *gate = *gate - 1; //go to past gate 
        }else{
           *gate = 6; // put this to put "circular effect"
        }
    }
    

    if (last_gate == *gate) return; // to not redraw if not needed
    draw_gate(*gate, buffer);


    last_gate = *gate;
}


void draw_gate(LOGIC_GATE gate, uint8_t *buffer ){
    clear_display(buffer);
    ssd1306_show(buffer);

    const unsigned char* bitmaps[] = {bitmap_and, bitmap_or, bitmap_not, bitmap_nand, bitmap_nor, bitmap_xor, bitmap_xnor}; 

    static ssd1306_t ssd_bm;
    ssd1306_init_bm(&ssd_bm, 128, 64, false, 0x3C, i2c1);
    ssd1306_config(&ssd_bm);

    ssd1306_draw_bitmap(&ssd_bm, bitmaps[gate]);
    sleep_ms(400);//delay to not change to fast

}