#include "mbed.h"

int salidas[17][7] = {{0, 0, 0, 0, 0, 0, 1},    // 0
                      {1, 0, 0, 1, 1, 1, 1},   // 1
                      {0, 0, 1, 0, 0, 1, 0},   // 2
                      {0, 0, 0, 0, 1, 1, 0},   // 3
                      {1, 0, 0, 1, 1, 0, 0},   // 4
                      {0, 1, 0, 0, 1, 0, 0},   // 5
                      {0, 1, 0, 0, 0, 0, 0},   // 6
                      {0, 0, 0, 1, 1, 1, 1},   // 7
                      {0, 0, 0, 0, 0, 0, 0},   // 8
                      {0, 0, 0, 0, 1, 0, 0},   // 9
                      {0, 0, 0, 1, 0, 0, 0},   // 10(A)
                      {1, 1, 0, 0, 0, 0, 0},  // 11 (B)
                      {0, 1, 1, 0, 0, 0, 1},  // 12 (C)
                      {1, 0, 0, 0, 0, 1, 0},  // 13 (D)
                      {0, 1, 1, 0, 0, 0, 0},  // 14 (E)
                      {0, 1, 1, 1, 0, 0, 0},  // 15 (F)
                      {0, 0, 0, 0, 0, 0, 1}}; // 0

//  DigitalOut segm01[2][7] = {{PTC9, PTC8, PTA5, PTA4, PTA12, PTD4, PTA2},
//                             {PTC11, PTC10, PTC6, PTC5, PTC4, PTC3, PTC0}};

DigitalOut segm01[2][7] = {{PTC11, PTC10, PTC6, PTC5, PTC4, PTC3, PTC0},
                            {PTC9, PTC8, PTA5, PTA4, PTA12, PTD4, PTA2}};

DigitalOut myled(LED1);
long int frecuencia =1000000;
int indicador = 0, ultimo10 = 0, ultimo01 = 0;

DigitalIn BtnUD(PTB8); // Boton Up/Down
DigitalIn BtnA(PTB9);  // Boton aumentar velocidad
DigitalIn BtnB(PTB10); // Boton reducir velocidad

void imprimir(int i, int j, int frecuencia);
void up(void);
void down(void);

int main() {
  
  

  while(1){
    
    switch(indicador){
        case 0:
            up();

        break;

        case 1:
            down();
        break;
    }

    

  }
}

void imprimir(int i, int j, int frecuencia) {
  for (int k = 0; k <= 6; k++) 
  {
    segm01[i][k] = salidas[j][k];
  }
  wait_us(frecuencia);
}

void up(){

    for(int k = ultimo10; k <= 16; k++)
    {
        
        imprimir(0, k, frecuencia);

        for(int l = ultimo01; l <= 16; l++)
        {
            imprimir(1, l, frecuencia);
            if(BtnUD == 1)
            {
                ultimo10 = k;
                ultimo01 = l;
                indicador = 1;
                return;
            }
                 myled = 1;
            if(BtnA == 1 && frecuencia >= 300000)
            {
                myled = 0;
                wait_us(200000);
                frecuencia -= 300000;
            }
            else if(BtnB == 1 && frecuencia <= 2000000)
            {
                myled = 0;
                wait_us(200000);
                frecuencia += 300000;
            }
            
        }
    }
    ultimo10 = 0;
    ultimo01 = 0;
    indicador = 0;
    return;
}

void down(){
    for(int k = ultimo10; k >= 0; k--)
    {
        imprimir(0, k, frecuencia);
        for(int l = ultimo01; l >= 0; l--)
        {
            imprimir(1, l, frecuencia);
            if(BtnUD == 1)
            {
                
                ultimo10 = k;
                ultimo01 = l;
                indicador = 0;
                return;
            }
            myled = 1;
            if(BtnA == 1 && frecuencia >= 300000)
            {
                myled = 0;
                wait_us(200000);
                frecuencia -= 300000;
            }
            else if(BtnB == 1 && frecuencia <= 2000000)
            {
                myled = 0;
                wait_us(200000);
                frecuencia += 300000;
            }
            
        }
    }
    ultimo10 = 15;
    ultimo01 = 15;
    indicador = 1;
    return;

}