/*
 * File:   RTOS_ADC_PWM_1.c
 * Author: Jorge estrella
 *
 * Created on 7 de julio de 2021, 13:24
 */
#include <xc.h>
#include <pic12f675.h>


#define _XTAL_FREQ 4000000
#define Lectura_ADC GPIObits.GP0
#define PWM GPIObits.GP1

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on GP4/OSC2/CLKOUT pin, I/O function on GP5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-Up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // GP3/MCLR pin function select (GP3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = OFF       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)



uint16_t tick = 0;
unsigned int conversion;
unsigned int lectura;
unsigned int medicion;
int PWM1DC;
uint8_t TMR1_C;
short PWM1Cont;
int valor_PWM1;

//Declaracion de funciones utilizadas
void TMR0_Init(void);
void ADC_Init(void);
unsigned int task1(void);
unsigned int task2(void);
void TMR1_Init(void);

void main(void) {
    VRCON=0x00;    //Disable voltage reference 
    CMCON=0b00000111;   //Disable comparator 
    TRISIO = 0b000001;
    GPIO=0b000000;     //Clear GPIO
    TMR0_Init();
    ADC_Init();
    TMR1_Init();
    while(1)
    {
        if(tick%30 == 0)
        {
            valor_PWM1 = task1()*50/1023;
            
        }            
        if(tick%50 == 0)
        {
         task2();
        }
             
    }
    return;
}

void TMR0_Init(void)
{
    TMR0 = 252;
    GIE = 1;
    PEIE = 1;
    T0IE = 1;
    T0IF = 0;
    T0CS = 0;
    T0SE = 1;
    PSA = 0;
    PS0 = 1;
    PS1 = 1;
    PS2 = 1;
}
void ADC_Init(void){
    //Configuracion del ADC
    ADCON0bits.ADFM = 1;
    ADCON0bits.VCFG = 0;//Voltage Reference VDD
    ADCON0bits.CHS  = 0b00; //Select chanel AN0
    ANSELbits.ADCS  = 0b100;
    ANSELbits.ANS   = 0b0001;
    ADCON0bits.ADON = 1;//Turn ADC on
}

    unsigned int task1(void){
    unsigned int RESULT_ADC = 0;
    ADCON0bits.GO = 1;//Start ADC
    while(ADCON0bits.GO);
        RESULT_ADC = ADRESH << 8;
        RESULT_ADC = RESULT_ADC + ADRESL;
    return (RESULT_ADC);//Return ADC value
}
    
    
    void TMR1_Init(void)
{
    TMR1 = 65335;
    TMR1CS = 0;
    T1CKPS0 = 0;
    T1CKPS1 = 0;
    TMR1ON = 1;
    TMR1IE = 1;
    TMR1IF = 0;
    PEIE = 1;
    GIE = 1;
}
    
void __interrupt() ISR()
{
    if(T0IF)
    {
        tick++;
        TMR0 = 252;
        T0IF = 0;
    }
    if(TMR1IF)
    {
        TMR1_C++;
       if(TMR1_C >= valor_PWM1)
     {
        PWM = 0;
     }
     if(TMR1_C == 50)
     {
         PWM = 1;
         TMR1_C = 0;
     }
        
        TMR1IF = 0;
     //TMR1 = 65515;
        TMR1 = 65335;
     }
        
    }
unsigned int task2 (void)
{
    int comparador = (valor_PWM1*50/1023);
    if((PWM1DC <= comparador) && PWM1DC >= 0)
    {
        PWM1DC++;
        __delay_ms(10);
        return(PWM1DC);
     }else if((PWM1DC >= comparador) && PWM1DC <= 50)
      {      
        PWM1DC--;
        __delay_ms(10);
        return(PWM1DC);
        }
     else{
         ;
     }
    }
