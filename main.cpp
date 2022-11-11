#include "mbed.h"



struct segments{
    DigitalOut a01;
    DigitalOut b01;
    DigitalOut c01;
    DigitalOut d01;
    DigitalOut e01;
    DigitalOut f01;
    DigitalOut g01;

    DigitalOut a10;
    DigitalOut b10;
    DigitalOut c10;
    DigitalOut d10;
    DigitalOut e10;
    DigitalOut f10;
    DigitalOut g10;

    //Constructor
    segments(PinName pin1, PinName pin2, PinName pin3, PinName pin4, PinName pin5, PinName pin6, PinName pin7, PinName pin8, PinName pin9, PinName pin10, PinName pin11, PinName pin12, PinName pin13, PinName pin14) : a01(pin1), b01(pin2), c01(pin3), d01(pin4), e01(pin5), f01(pin6), g01(pin7), a10(pin8), b10(pin9), c10(pin10), d10(pin11), e10(pin12), f10(pin13), g10(pin14){};
    void encender(int a1, int b1, int c1, int d1, int e1, int f1, int g1, int a2, int b2, int c2, int d2, int e2, int f2, int g2){

        a01 = a1;   //SEGMENTO 01
        b01 = b1;
        c01 = c1;
        d01 = d1;
        e01 = e1;
        f01 = f1;
        g01 = g1;

        a10 = a2;   //SEGMENTO 10
        b10 = b2;
        c10 = c2;
        d10 = d2;
        e10 = e2;
        f10 = f2;
        g10 = g2;
        
    }
};

DigitalIn BtnUD(PTB0);   //Boton Up/Down
DigitalIn BtnA(PTB1);    //Boton aumentar velocidad
DigitalIn BtnB(PTB2);    //Boton reducir velocidad

/**Prototipos de Funcion*/
void UP(segments segmentos, int freq);


int main()
{
    segments segmentos(PTC9, PTC8, PTA5, PTA4, PTA12, PTD4, PTA2, PTC11, PTC10, PTC6, PTC5, PTC4, PTC3, PTC0);
    float frecuencia = 1000000;  //1 segundo = 1000000, MAXIMO = 300000, MINIMO 2000000
    int btn;

    while(true){

        if(BtnUD == 0)btn = 0;         //Sube
        else if(BtnUD == 1)btn = 1;    //Baja

        // if(BtnA && frecuencia >= 300000 && frecuencia <= 2000000)frecuencia += 300000;
        // else if(BtnB && frecuencia >= 300000 && frecuencia <= 2000000)frecuencia -= 300000;

        UP(segmentos, frecuencia);
       
        
        
    }
}

void UP(segments segmentos, int freq){

    segmentos.encender(0,0,0,0,0,0,1,0,0,0,0,0,0,1);
    wait_us(freq);
    segmentos.encender(1,0,0,1,1,1,1,0,0,0,0,0,0,1);
    wait_us(freq);
    segmentos.encender(0,0,1,0,0,1,0,0,0,0,0,0,0,1);
    wait_us(freq);
    segmentos.encender(0,0,0,0,1,1,0,0,0,0,0,0,0,1);
    wait_us(freq);
    segmentos.encender(1,0,0,1,1,0,0,0,0,0,0,0,0,1);
    wait_us(freq);
    segmentos.encender(0,1,0,0,1,0,0,0,0,0,0,0,0,1);
    wait_us(freq);
}
