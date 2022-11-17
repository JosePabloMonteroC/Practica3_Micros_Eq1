#include "mbed.h"

/**Arreglo bidimensional codificado con las salidas de cada segmento*/
int salidas[16][7] = {{0, 0, 0, 0, 0, 0, 1},    // 0
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
                      {1, 1, 0, 0, 0, 0, 0},   // 11 (B)
                      {0, 1, 1, 0, 0, 0, 1},   // 12 (C)
                      {1, 0, 0, 0, 0, 1, 0},   // 13 (D)
                      {0, 1, 1, 0, 0, 0, 0},   // 14 (E)
                      {0, 1, 1, 1, 0, 0, 0}};   // 15 (F)
                      //{0, 0, 0, 0, 0, 0, 1}};  // 0

DigitalOut ledRojo(LED1);
DigitalOut ledVerde(LED2);
DigitalOut ledAzul(LED3);


/**Arreglo bidimensional de puertos para los segmentos*/
DigitalOut segm01[2][7] = {{PTC11, PTC10, PTC6, PTC5, PTC4, PTC3, PTC0},    //Segmento 10
                            {PTC9, PTC8, PTA5, PTA4, PTA12, PTD4, PTA2}};   //Segmento 01

DigitalIn BtnUD(PTB8); // Boton Up/Down
DigitalIn BtnA(PTB9);  // Boton aumentar velocidad
DigitalIn BtnB(PTB10); // Boton reducir velocidad

/**Variables globales*/
long int vel =1000000;                   //vel inicial 1s, minimo 0.3s, máximo 2s
int indicador = 0;                      //Variable que definirá si la cuenta es ascendente o descendente.
int ultimo10 = 0;                       //Variable que almacenará el último número en el que se quedó el segmento más significativo.
int ultimo01 = 0;                       //Variable que almacenará el último número en el que se quedó el segmento menos significativo.

/**Prototipos de funcion*/
void imprimir(int i, int j, int vel);
void up(void);
void down(void);

/**Función principal*/
int main() {
  
  ledRojo = 1;
  ledVerde = 1;
  ledAzul = 1;

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

  return 0;
}


/**
@fn imprimir
@details Funcion que manda un 0 o un 1 a las salidas del segmento correspondiente para encender el número.
@param variable i para definir cual de los 2 segmentos encender, variable j para indicar que numero encender, vel para controlar la velocidad de espera.
@return
*/
void imprimir(int i, int j, int vel) {
  for (int k = 0; k <= 6; k++) 
  {
    segm01[i][k] = salidas[j][k];
  }
  wait_us(vel);
}

/**
@fn up
@details Funcion que cuenta de manera ascendente
@return
*/
void up(){

    for(int i = ultimo10; i <= 15; i++)
    {
        
        imprimir(0, i, vel);

        for(int j = ultimo01; j <= 15; j++)
        {
            imprimir(1, j, vel);
            if(BtnUD == 1)
            {
                ultimo10 = i;
                ultimo01 = j;
                indicador = 1;
                ledAzul= 0;
                wait_us(100000);
                ledAzul = 1;
                return;
            }
            if(BtnA == 1 && vel >= 400000)
            {
                ledVerde = 0;
                wait_us(100000);
                ledVerde = 1;
                vel -= 200000;
            }
            else if(BtnB == 1 && vel <= 2000000)
            {
                ledRojo = 0;
                wait_us(200000);
                ledRojo = 1;
                vel += 200000;
            }
            
        }
        ultimo01 = 0;
    }
    ultimo10 = 0;
    indicador = 0;
    return;
}

/**
@fn down
@details Funcion que cuenta de manera descendiente
@return
*/
void down(){
    for(int i = ultimo10; i >= 0; i--)
    {
        imprimir(0, i, vel);
        for(int j = ultimo01; j >= 0; j--)
        {
            
            imprimir(1, j, vel);
            if(BtnUD == 1)
            {
                ultimo10 = i;
                ultimo01 = j;
                indicador = 0;
                ledAzul = 0;
                wait_us(100000);
                ledAzul = 1;
                return;
            }
            if(BtnA == 1 && vel >= 400000)
            {
                ledVerde = 0;
                wait_us(200000);
                ledVerde = 1;
                vel -= 200000;
            }
            else if(BtnB == 1 && vel <= 2000000)
            {
                ledRojo = 0;
                wait_us(200000);
                ledRojo = 1;
                vel += 200000;
            }
            
        }
        ultimo01 = 15;
    }
    ultimo10 = 15;
    indicador = 1;
    return;
}