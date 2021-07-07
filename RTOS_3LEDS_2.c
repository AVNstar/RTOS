/*
 * File:   RTOS_3LEDS.c
 * Author: NOVA
 *
 * Created on 19 de junio de 2021, 22:09
 */

//para hacer este gestor de tareas rudimentario me guie del foro
//https://www.youtube.com/watch?v=79TZ08jM7Jc,
//trate de adaptaro para MPLAB XC8 solo con tres leds de salidas, la idea era hacer
//algo similar a algo como en este tutorial pero solo con 3 leds ya que tiene muchos
//menos recursos nuestro pic12F675 que el pic16F887.
//Lo lleve a la practica y es inestabe, estaria bueno que comencemos con esto
//porque creo que es algo mas sencillo y despues llevarlo a otros ejemplos
//o proyectos.
//En el ultimo ejemplo que este tutorial de los leds tiene url 
//https://www.youtube.com/watch?v=QpHS-9aH5LY
//la idea es hacer funcionar tres leds de manera "independiente" o cuasi paralelo
//a diferentes frecuencias cada uno.

// modificado por fede

cosas locas q romperian el codigo

#include <xc.h>
#include <stdint.h>
#include <htc.h>
#include <pic.h>
#include <pic12f675.h>



#define LED1 GPIO0
#define LED2 GPIO1
#define LED3 GPIO2

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = OFF       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

#define __XTAL_FREQ 4000000

uint16_t tick = 0;
void TMR0_Init(void);

void main(void) {
    VRCON=0x00;    //Disable voltage reference 
    CMCON=0b00000111;   //Disable comparator 
    ANSEL=0x00;    //A/D disabled        
    GPIO=0;     //Clear GPIO
    TRISIO = 0x00;
    TMR0_Init();
    while(1)
    {
        if(tick%50 == 0)
        {
            LED1 = ~LED1; //este es el primer task, podria ponerlo en una funcion pero como es cortito lo deje aqui
        }
        if(tick%70 == 0)
        {
            LED2 = ~LED2; //este es el segundo task
        }
        if(tick%220 == 0)
            LED3 = ~LED3; //este es el tercer task
    }
    return;
}

void __interrupt() ISR()
{
    if(T0IF)
    {
        tick++;
        TMR0 = 252;
        T0IF = 0;
    }
}

void TMR0_Init(void)
{
    TMR0 = 252;
    GIE = 1;
    PEIE = 1;
    T0IE = 1;
    T0IF = 0;
    //TMR0ON = 1;
    T0CS = 0;
    T0SE = 1;
    PSA = 0;
    PS0 = 1;
    PS1 = 1;
    PS2 = 1;
}
