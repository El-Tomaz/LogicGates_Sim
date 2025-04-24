#include <stdio.h>
#include "pico/stdlib.h"
#include "common.h"
#include "menu.h"

// Hardware Mapping
#define pBUTTON_A 5
#define pBUTTON_B 6

#define pLED_R 13
#define pLED_G 11
#define pLED_B 12

void hardware_setup();
void setLed(bool R, bool G, bool B);
bool readButton(uint gpio);

bool calculateLogicGate(LOGIC_GATE gate, bool A, bool B);

int main()
{
    stdio_init_all();

    hardware_setup();
    
    uint8_t buffer_display[ssd1306_buffer_length];
    init_menu();

    LOGIC_GATE gate = AND;
    while (true)
    {

        // reading buttons vvv
        bool A = readButton(pBUTTON_A);
        bool B = readButton(pBUTTON_B);

        bool S = calculateLogicGate(gate, A, B);
        
        if(S == true){
            setLed(0,1,0);
        }else{
            setLed(1,0,0);
        }

        // menu stuff

        load_menu(buffer_display,&gate);


    }
}

void hardware_setup()
{
    gpio_init(pBUTTON_A);
    gpio_init(pBUTTON_B);

    gpio_pull_up(pBUTTON_A);
    gpio_pull_up(pBUTTON_B);

    gpio_init(pLED_R);
    gpio_init(pLED_G);
    gpio_init(pLED_B);

    gpio_set_dir(pLED_R,GPIO_OUT);
    gpio_set_dir(pLED_G,GPIO_OUT);
    gpio_set_dir(pLED_B,GPIO_OUT);
}

void setLed(bool R, bool G, bool B){
    gpio_put(pLED_R,R);
    gpio_put(pLED_G,G);
    gpio_put(pLED_B,B);
}


bool readButton(uint gpio){
    return !gpio_get(gpio);
}

bool calculateLogicGate(LOGIC_GATE gate, bool A, bool B)
{
    switch (gate)
    {
    case AND:
        return A & B;
    
    case OR:
        return A | B;
    case NOT:
        return !A;
    case NAND:
        return !(A & B);
    case NOR:
        return !(A | B);
    case XOR:
        return ((!A&B) | (A&!B));
    case XNOR:
        return ((!A&!B) | (A&B));
    default:
        break;
    }
}

