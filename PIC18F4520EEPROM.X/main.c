/*
 * File:   main.c
 * Author: 
 *
 * Created on July 3, 2018, 4:21 PM
 */

// PIC18F4520 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = INTIO67    // Oscillator Selection bits (Internal oscillator block, port function on RA6 and RA7)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = ON         // Watchdog Timer Enable bit (WDT enabled)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#define _XTAL_FREQ 8000000

void main(void) {
    
    //Set output pins for LEDs
    TRISD=0x00;
    
    LATD=0x00;
    
    //load up a buffer with data
    char buffer[16]={0x00};
    
    char i=0;
    
    for(i=0;i<16;i++){
        
        buffer[i]=i;
        
    }
    
    //WRITE EEPROM DATA
   
    //Point to data memory
    EECON1bits.EEPGD=0;
    
    //Access EEPROM
    EECON1bits.CFGS=0;
    
    //Enable writes
    EECON1bits.WREN=1;
    
    //Disable interrupts
    INTCONbits.GIE=0;
    
    //Write to eeprom location
    for(i=0;i<16;i++){
        
        //EEPROM ADDRESS
        EEADR=i;
    
        //EEPROM data to write
        EEDATA=buffer[i];
        
        //Required Sequence
        EECON2=0x55;
        EECON2=0xAA;
    
        //Set WR bit to begin write for each byte
        EECON1bits.WR=1;
        
        //A delay is required
        __delay_ms(5);
    } 
    
    
    //Enable Interrupts
    INTCONbits.GIE=1;
    
    //Disable writes
    EECON1bits.WREN=0;
    
 
    //READ EEPROM DATA
    
    //Point to Data memory
    EECON1bits.EEPGD=0;
    
    //Access EEPROM
    EECON1bits.CFGS=0;
    
   
    //Read the data stored in EEPROM
    for(i=0;i<16;i++){
        
        //Point to EEPROM address to read
        EEADR=i;
        
        //Read data and display the value on PORT D (LEDs)
        PORTD=EEDATA;
        
        //Enable EEPROM Read
        EECON1bits.RD=1;
        
        //Add a delay
        __delay_ms(100);
    }
    
    while(1);
    
}
