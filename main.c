/* 
 * File:   main.c
 * Author: takumi
 *
 * Created on 2016/12/28, 7:09
 */

#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 32000000
#include <math.h>
#include "skI2Cslave.h"

// PIC16F1939 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable (PWRT enabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable (All VCAP pin functionality is disabled)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>


void clear();
void setup();
void show(short, short);
void tmadd(char);

int i = 46, j = 46;

char num[11] = {0x11, 0xDB, 0x45, 0x49, 0x8B, 0x29, 0x21, 0x1B, 0x01, 0x09, 0xFF};

void interrupt timer() {
    if (T0IF == 1) {
        T0IF = 0;
        show(i, j);
    }
    char x;

    if (SSPIF == 1) { // 
        if (SSPSTATbits.R_nW == 0) {
            if (SSPSTATbits.D_nA == 0) {
                Rdtp = (char *) rcv_data;
                x = SSPBUF;
                rcv_flg = 0;
            } else {
                *Rdtp = SSPBUF;
                Rdtp++;
                rcv_flg++;
            }
            SSPIF = 0;
            SSPCON1bits.CKP = 1;
        } else {
            if (SSPSTATbits.BF == 1) {
                Sdtp = (char *) snd_data;
                x = SSPBUF;
                while ((SSPCON1bits.CKP) | (SSPSTATbits.BF));
                SSPBUF = *Sdtp;
                Sdtp++;
                SSPIF = 0;
                SSPCON1bits.CKP = 1;
            } else {
                if (SSPCON2bits.ACKSTAT == 0) {
                    while ((SSPCON1bits.CKP) | (SSPSTATbits.BF));
                    SSPBUF = *Sdtp;
                    Sdtp++;
                    SSPIF = 0;
                    SSPCON1bits.CKP = 1;
                } else {
                    SSPIF = 0;
                }
            }
        }
    }

    if (BCLIF == 1) {
        BCLIF = 0;
    }
}

int main() {
    setup();
    int ans;
    InitI2C_Slave(46);
    while (1) {
        ans = I2C_ReceiveCheck();
        if (ans != 0) {
            j = rcv_data[0] * 256 + rcv_data[1];
            i = rcv_data[2] * 256 + rcv_data[3];
            if(rcv_data[4]==1)tmadd(1);
            else if(rcv_data[4]==46)clear();
            //else tmadd(0);
        } else {
        }
    }


    return 0;
}

void tmadd(char data) {
    LATB2 = data;
    LATB3 = 1;
    LATB3 = 0;

    return;
}

void setup() {
    OSCCON = 0b01110000;
    ANSELA = 0x00;
    ANSELB = 0x00;
    TRISA = 0x00;
    TRISB = 0x00;
    TRISC = 0b00011000;

    OPTION_REG = 0b00000111;
    TMR0 = 0;
    T0IF = 0;
    T0IE = 1;
    GIE = 1;

    for (int i = 0; i < 10; i++) {
        LATB3 = 1;
        LATB3 = 0;
    }

    return;
}

void show(short data, short data2) {
    LATB4 = 0;
    LATB5 = 1;
    LATB4 = 1;
    LATB4 = 0;
    LATB5 = 0;

    if (data >= 100)LATA = num[data / 100];
    else LATA = num[10];
    __delay_us(500);
    LATA = num[10];
    LATB4 = 1;
    LATB4 = 0;

    if (data >= 10)LATA = num[(data / 10) % 10];
    else LATA = num[10];
    __delay_us(500);
    LATA = num[10];
    LATB4 = 1;
    LATB4 = 0;

    LATA = num[data % 10];
    __delay_us(500);
    LATA = num[10];
    LATB4 = 1;
    LATB4 = 0;

    LATB4 = 1;
    LATB4 = 0;


    LATA = num[data2 % 10];
    __delay_us(500);
    LATA = num[10];
    LATB4 = 1;
    LATB4 = 0;

    if (data2 >= 10)LATA = num[(data2 / 10) % 10];
    __delay_us(500);
    LATA = num[10];
    LATB4 = 1;
    LATB4 = 0;

    LATB4 = 1;
    LATB4 = 0;

    if (data2 >= 100)LATA = num[data2 / 100];
    __delay_us(500);
    LATA = num[10];
    LATB4 = 1;
    LATB4 = 0;


    return;
}

void clear(){
    for(int i=0; i<10; i++)tmadd(0);
    j=0;
    
    return;
}