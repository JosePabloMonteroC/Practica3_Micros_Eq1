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

DigitalIn BtnUD(PTB8); // Boton Up/Down
DigitalIn BtnA(PTB9);  // Boton aumentar velocidad
DigitalIn BtnB(PTB10); // Boton reducir velocidad

void imprimir(int i, int j, int frecuencia);
void UP(int i, int j, int frecuencia);

int main() {
  long int frecuencia =1000000; // 1 segundo = 1000000, MAXIMO = 300000, MINIMO 2000000
  int UD,A,B;

  while(1){
    

    BtnUD.mode(PullUp);
    BtnA.mode(PullUp);
    BtnB.mode(PullUp);

    UD = BtnUD;
    A = BtnA;
    B = BtnB;

    for(int i = 0; i <= 16; i++)
    {
        
        imprimir(0, i, frecuencia);
        for(int j = 0; j <= 16; j++)
        {
            if(A == 1 && frecuencia >= 300000 && frecuencia <= 2000000)frecuencia += 300000;
            else if(A == 0)frecuencia = frecuencia;
            if(B == 1 && frecuencia >= 300000 && frecuencia <= 2000000)frecuencia -= 300000;
            else if(B == 0)frecuencia = frecuencia;
            imprimir(1, j, frecuencia);
        }
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
