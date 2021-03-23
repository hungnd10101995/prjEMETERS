/*===========================================================================*/
/*
SOURCE_FILE:		emeter-hardware.c
APPLICATION:		DT03M-RF
MODULE:				DT03M-RF
ORIGINAL AUTHOR:	thaodtn
VERSION:			2.0
DATE:				24/10/2016
*/
#ifndef _HARDWARE_H_
#define _HARDWARE_H_
/*===========================================================================*/
/* I N C L U D E S                                                           */
/*===========================================================================*/
#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "si4464.h"
#include "../prjEMETERS/devices.h"
#include "../prjEMETERS/devices.h"
#include "../prjLIB/prjCONVERT/macro.h"

#define PRIORITY_INT_LEVEL_UART     1

#define PC_COMMUNICATION
#define PC_DESIRED_BAUDRATE         9600
#define OPTICAL_COMMUNICATION
#define OPTICAL_DESIRED_BAUDRATE    300
#define RFSLOT_DESIRED_BAUDRATE     9600
#define GSMSLOT_DESIRED_BAUDRATE    9600

/*===========================================================================*/
/*  D I G I T A L   I / O    D E F I N A T I O N S                           */
/*===========================================================================*/
//#define ei()        INTCON2bits.GIE = 1
//#define di()        INTCON2bits.GIE = 0
//on change interrupt
#define on_change_interrupt_active()        PADCONbits.IOCON = 1
#define on_change_interrupt_deactive()      PADCONbits.IOCON = 0
#define on_change_interrupt_enable()        IEC1bits.CNIE = 1    
#define on_change_interrupt_disable()       IEC1bits.CNIE = 0
#define on_change_interrupt_flag_clear()    IFS1bits.CNIF = 0
#define on_change_interrupt_flag_status()   (IFS1bits.CNIF)
#define on_change_interrupt_priority()      IPC4bits.CNIP = 3//4
//watchdog
#define restart_watchdog()  ClrWdt()
#define watchdog_enable()   (_SWDTEN = 1)
#define watchdog_disable()  (_SWDTEN = 0)

//timer
//#define timer1_interrupt_status()               (IEC0bits.T1IE)
#define timer16ms_interrupt_enable_status()        (IEC0bits.T1IE) //timer1_interrupt_enable_status
#define timer16ms_interrupt_flag_clear()           IFS0bits.T1IF = 0 //timer1_interrupt_flag_clear
#define timer16ms_interrupt_flag_status()          (IFS0bits.T1IF) //timer1_interrupt_flag_status

//#define timer2_interrupt_status()               (IEC0bits.T2IE)
#define timer2_interrupt_enable_status()        (IEC0bits.T2IE)
#define timer2_interrupt_flag_clear()           IFS0bits.T2IF = 0
#define timer2_interrupt_flag_status()          (IFS0bits.T2IF)


#ifdef COMMUNICATION_OPTICAL_SUPPORT
#define UART_OPTICAL_BAUDRATE_REG                            U1BRG
#define uart_optical_level_interrupt(level)                 _U1RXIP = level; //6;
#if defined(_DT03MRF_PCB_PIC_AS8_S_V10_) || defined(_DT03MRF_PCB_PIC_AMS_S_V10_) || defined(_DT03MRF_PCB_PIC_AS8_S_V12_)
#define uart_optical_rx_dir_input()                         TRISCbits.TRISC1 = 1; // RX pin must be digital input
#define uart_optical_rx_select_pin()                        _U1RXR = 38;     
#define uart_optical_tx_dir_output()                        TRISGbits.TRISG8 = 0; //TX pin must be digital output
#define uart_optical_tx_select_pin()                        _RP19R = 3; //_U1TXR = 19; 
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V20_) || defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
#define uart_optical_rx_dir_input()                         TRISDbits.TRISD11 = 1; 
#define uart_optical_rx_select_pin()                        _U1RXR = 12; 
#define uart_optical_tx_dir_output()                        TRISDbits.TRISD0 = 0;
#define uart_optical_tx_select_pin()                        _RP11R = 3; // UART1 transmit
#endif

#define uart_optical_enable()                               U1MODEbits.UARTEN = 1; // Enable UART module 
#define uart_optical_disable()                              U1MODEbits.UARTEN = 0; // Enable UART module 
#define uart_optical_transmit_enable()                      U1STAbits.UTXEN = 1; // Enable UART transmit

#define uart_optical_rx_interrupt_flag_status()             _U1RXIF
#define uart_optical_tx_interrupt_flag_status()             _U1TXIF
#define uart_optical_rx_interrupt_status()                  _U1RXIE
#define uart_optical_tx_interrupt_status()                  _U1TXIE
#define uart_optical_rx_interrupt_flag_clear()              _U1RXIF = 0;
#define uart_optical_tx_interrupt_flag_clear()              _U1TXIF = 0;
#define uart_optical_rx_interupt_enable()                   _U1RXIE = 1;
#define uart_optical_rx_interupt_disable()                  _U1RXIE = 0;
#define uart_optical_rx_data_register()                     ((volatile unsigned char)U1RXREG)
#define uart_optical_get_error()                            (U1STA & (_U1STA_OERR_MASK | _U1STA_FERR_MASK | _U1STA_PERR_MASK))
#define uart_optical_clear_all_error()                      (U1STA &= 0xFFF0)//(U1STA = (_U1STA_OERR_MASK | _U1STA_FERR_MASK | _U1STA_PERR_MASK))
#define uart_optical_error_interrupt_flag_status()          _U1ERIF
#define uart_optical_error_interrupt_flag_clear()           _U1ERIF = 0;
#endif         

#ifdef COMMUNICATION_PC_SUPPORT
#define UART_PC_BAUDRATE_REG                           U2BRG
#define UART_PC_MODE_REG                               U2MODE
#define uart_pc_level_interrupt(level)                 IPC7bits.U2RXIP = level; //6;
#if defined(_DT03MRF_PCB_PIC_AS8_S_V10_) || defined(_DT03MRF_PCB_PIC_AMS_S_V10_) || defined(_DT03MRF_PCB_PIC_AS8_S_V12_)
#define uart_pc_rx_dir_input()                         TRISCbits.TRISC2 = 1; // RX pin must be digital input
#define uart_pc_rx_select_pin()                        _U2RXR = 39;     
#define uart_pc_tx_dir_output()                        TRISGbits.TRISG7 = 0; //TX pin must be digital output
#define uart_pc_tx_select_pin()                        _RP26R = 5; //_U1TXR = 26;
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V20_)
#define uart_pc_rx_dir_input()                         TRISDbits.TRISD2 = 1; 
#define uart_pc_rx_select_pin()                        _U2RXR = 23; 
#define uart_pc_tx_dir_output()                        TRISDbits.TRISD3 = 0;
#define uart_pc_tx_select_pin()                        _RP22R = 5; // UART2 transmit;
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
#define uart_pc_rx_dir_input()                          nop();//TRISGbits.TRISG7 = 1; 
#define uart_pc_rx_select_pin()                         nop();// _U2RXR = 26; 
#define uart_pc_tx_dir_output()                         nop();// TRISGbits.TRISG8 = 0;
#define uart_pc_tx_select_pin()                         nop();//_RP22R = 5; // UART2 transmit;
#endif

#define uart_pc_enable()                               U2MODEbits.UARTEN = 1; // Enable UART module 
#define uart_pc_disable()                              U2MODEbits.UARTEN = 0; // Enable UART module 
#define uart_pc_transmit_enable()                      U2STAbits.UTXEN = 1; // Enable UART transmit

#define uart_pc_rx_interrupt_flag_status()             _U2RXIF
#define uart_pc_tx_interrupt_flag_status()             _U2TXIF
#define uart_pc_rx_interrupt_status()                  _U2RXIE
#define uart_pc_tx_interrupt_status()                  _U2TXIE
#define uart_pc_rx_interrupt_flag_clear()              _U2RXIF = 0;
#define uart_pc_tx_interrupt_flag_clear()              _U2TXIF = 0;
#define uart_pc_rx_interupt_enable()                   _U2RXIE = 1;
#define uart_pc_rx_interupt_disable()                  _U2RXIE = 0;
#define uart_pc_rx_data_register()                     ((volatile unsigned char)U2RXREG)
#define uart_pc_get_error()                            (U2STA & (_U2STA_OERR_MASK | _U2STA_FERR_MASK | _U2STA_PERR_MASK))
#define uart_pc_clear_all_error()                      (U2STA &= 0xFFF0)//(U1STA = (_U1STA_OERR_MASK | _U1STA_FERR_MASK | _U1STA_PERR_MASK))
#define uart_pc_error_interrupt_flag_status()          _U2ERIF
#define uart_pc_error_interrupt_flag_clear()           _U2ERIF = 0;
#endif       

#ifdef COMMUNICATION_GSMSLOT_SUPPORT
#define UART_GSMSLOT_BAUDRATE_REG                           U3BRG
#define uart_gsmslot_level_interrupt(level)                 IPC20bits.U3RXIP = level; //6;
#if defined(_DT03MRF_PCB_PIC_AS8_S_V10_) || defined(_DT03MRF_PCB_PIC_AMS_S_V10_)
//ko co
//#elif defined(_DT03MRF_PCB_PIC_AS8_S_V20_)
//#define uart_gsmslot_rx_dir_input()                         TRISBbits.TRISB0 = 1; 
//#define uart_gsmslot_rx_select_pin()                        _U3RXR = 0; 
//#define uart_gsmslot_tx_dir_output()                        TRISBbits.TRISB1 = 0;
//#define uart_gsmslot_tx_select_pin()                        _RP1R = 19; //UART3 transmit
//#endif
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V20_) || defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
#define uart_gsmslot_rx_dir_input()                         TRISGbits.TRISG7 = 1; 
#define uart_gsmslot_rx_select_pin()                        _U4RXR = 26; 
#define uart_gsmslot_tx_dir_output()                        TRISGbits.TRISG8 = 0;
#define uart_gsmslot_tx_select_pin()                        _RP19R = 21; //UART4 transmit
#endif
#define uart_gsmslot_enable()                               U3MODEbits.UARTEN = 1; // Enable UART module 
#define uart_gsmslot_disable()                              U3MODEbits.UARTEN = 0; // Enable UART module 
#define uart_gsmslot_transmit_enable()                      U3STAbits.UTXEN = 1; // Enable UART transmit

#define uart_gsmslot_rx_interrupt_flag_status()             _U3RXIF
#define uart_gsmslot_tx_interrupt_flag_status()             _U3TXIF
#define uart_gsmslot_rx_interrupt_status()                  _U3RXIE
#define uart_gsmslot_tx_interrupt_status()                  _U3TXIE
#define uart_gsmslot_rx_interrupt_flag_clear()              _U3RXIF = 0;
#define uart_gsmslot_tx_interrupt_flag_clear()              _U3TXIF = 0;
#define uart_gsmslot_rx_interupt_enable()                   _U3RXIE = 1;
#define uart_gsmslot_rx_interupt_disable()                  _U3RXIE = 0;
#define uart_gsmslot_rx_data_register()                     ((unsigned char)U3RXREG)
#define uart_gsmslot_get_error()                            (U3STA & (_U3STA_OERR_MASK | _U3STA_FERR_MASK | _U3STA_PERR_MASK))
#define uart_gsmslot_clear_all_error()                      (U3STA &= 0xFFF0)//(U1STA = (_U1STA_OERR_MASK | _U1STA_FERR_MASK | _U1STA_PERR_MASK))
#define uart_gsmslot_error_interrupt_flag_status()          _U3ERIF
#define uart_gsmslot_error_interrupt_flag_clear()           _U3ERIF = 0;
#endif   

#ifdef COMMUNICATION_RFSLOT_SUPPORT
#define UART_RFSLOT_BAUDRATE_REG                           U4BRG
#define uart_rfslot_level_interrupt(level)                 _U4RXIP = level; //6;
#if defined(_DT03MRF_PCB_PIC_AS8_S_V10_) || defined(_DT03MRF_PCB_PIC_AMS_S_V10_)
//ko co
//#elif defined(_DT03MRF_PCB_PIC_AS8_S_V20_)
//#define uart_rfslot_rx_dir_input()                         TRISGbits.TRISG7 = 1; 
//#define uart_rfslot_rx_select_pin()                        _U4RXR = 26; 
//#define uart_rfslot_tx_dir_output()                        TRISGbits.TRISG8 = 0;
//#define uart_rfslot_tx_select_pin()                        _RP19R = 21; //UART4 transmit
//#endif
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V20_)
#define uart_rfslot_rx_dir_input()                         TRISBbits.TRISB0 = 1; 
#define uart_rfslot_rx_select_pin()                        _U3RXR = 0; 
#define uart_rfslot_tx_dir_output()                        TRISBbits.TRISB1 = 0;
#define uart_rfslot_tx_select_pin()                        _RP1R = 19; //UART3 transmit
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
#define uart_rfslot_rx_dir_input()                         TRISDbits.TRISD8 = 1; 
#define uart_rfslot_rx_select_pin()                        _U3RXR = 2; 
#define uart_rfslot_tx_dir_output()                        TRISDbits.TRISD9 = 0;
#define uart_rfslot_tx_select_pin()                        _RP4R = 19; //UART3 transmit
#endif

#define uart_rfslot_enable()                               U4MODEbits.UARTEN = 1; // Enable UART module 
#define uart_rfslot_disable()                              U4MODEbits.UARTEN = 0; // Enable UART module 
#define uart_rfslot_transmit_enable()                      U4STAbits.UTXEN = 1; // Enable UART transmit

#define uart_rfslot_rx_interrupt_flag_status()             _U4RXIF
#define uart_rfslot_tx_interrupt_flag_status()             _U4TXIF
#define uart_rfslot_rx_interrupt_status()                  _U4RXIE
#define uart_rfslot_tx_interrupt_status()                  _U4TXIE
#define uart_rfslot_rx_interrupt_flag_clear()              _U4RXIF = 0;
#define uart_rfslot_tx_interrupt_flag_clear()              _U4TXIF = 0;
#define uart_rfslot_rx_interupt_enable()                   _U4RXIE = 1;
#define uart_rfslot_rx_interupt_disable()                  _U4RXIE = 0;
#define uart_rfslot_rx_data_register()                     ((unsigned char)U4RXREG)
#define uart_rfslot_get_error()                            (U4STA & (_U4STA_OERR_MASK | _U4STA_FERR_MASK | _U4STA_PERR_MASK))
#define uart_rfslot_clear_all_error()                      (U4STA &= 0xFFF0)//(U1STA = (_U1STA_OERR_MASK | _U1STA_FERR_MASK | _U1STA_PERR_MASK))
#define uart_rfslot_error_interrupt_flag_status()          _U4ERIF
#define uart_rfslot_error_interrupt_flag_clear()           _U4ERIF = 0;

#endif  
////////////////////////////////////////////////////////////////////////////////
/*   for measurement    */
////////////////////////////////////////////////////////////////////////////////
#if defined(ADE7858_SUPPORT) || defined(ADE7880_SUPPORT)
#if defined(_DT03MRF_PCB_PIC_AS8_S_V10_) || defined(_DT03MRF_PCB_PIC_AMS_S_V10_) || defined(_DT03MRF_PCB_PIC_AS8_S_V12_)
#define ADE7858_CS_DIR                      TRISG
#define ADE7858_CS_OUT                      LATG
#define ADE7858_CS_BIT                      BIT9

#define ADE7858_SDI_DIR                     TRISA
#define ADE7858_SDI_OUT                     LATA
#define ADE7858_SDI_BIT                     BIT0

#define ADE7858_SCLK_DIR                    TRISE
#define ADE7858_SCLK_OUT                    LATE
#define ADE7858_SCLK_BIT                    BIT9

#define ADE7858_SDO_DIR                     TRISE
#define ADE7858_SDO_OUT                     LATE
#define ADE7858_SDO_IN                      PORTE
#define ADE7858_SDO_BIT                     BIT8

#define ADE7858_RESET_DIR                   TRISC
#define ADE7858_RESET_OUT                   LATC
#define ADE7858_RESET_BIT                   BIT3

#elif defined(_DT03MRF_PCB_PIC_AS8_S_V20_) || defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
#define ADE7858_CS_DIR                      TRISB
#define ADE7858_CS_OUT                      LATB
#define ADE7858_CS_BIT                      BIT14

#define ADE7858_SDI_DIR                     TRISB
#define ADE7858_SDI_OUT                     LATB
#define ADE7858_SDI_BIT                     BIT15

#define ADE7858_SCLK_DIR                    TRISD
#define ADE7858_SCLK_OUT                    LATD
#define ADE7858_SCLK_BIT                    BIT15

#define ADE7858_SDO_DIR                     TRISD
#define ADE7858_SDO_OUT                     LATD
#define ADE7858_SDO_IN                      PORTD
#define ADE7858_SDO_BIT                     BIT14

#define ADE7858_RESET_DIR                   TRISF
#define ADE7858_RESET_OUT                   LATF
#define ADE7858_RESET_BIT                   BIT12
#endif

//cs
#define _ade7858_cs_dir_output()			(ADE7858_CS_DIR clr ADE7858_CS_BIT)//TRISGbits.TRISG9 = 0
#define _ade7858_cs_low()					(ADE7858_CS_OUT clr ADE7858_CS_BIT)//LATGbits.LATG9 = 0
#define _ade7858_cs_high()                  (ADE7858_CS_OUT set ADE7858_CS_BIT)//LATGbits.LATG9 = 1
#define _ade7858_cs_tgl()                   (ADE7858_CS_OUT tgl ADE7858_CS_BIT)////LATGbits.LATG9 =!(LATGbits.LATG9)
//sdi
#define _ade7858_sdi_dir_output()           (ADE7858_SDI_DIR clr ADE7858_SDI_BIT)//TRISAbits.TRISA0 = 0
#define _ade7858_sdi_output_high()          (ADE7858_SDI_OUT set ADE7858_SDI_BIT)//LATAbits.LATA0 = 1
#define _ade7858_sdi_output_low()           (ADE7858_SDI_OUT clr ADE7858_SDI_BIT)//LATAbits.LATA0 = 0
//clk
#define _ade7858_sclk_dir_output()          (ADE7858_SCLK_DIR clr ADE7858_SCLK_BIT)//TRISEbits.TRISE9 = 0
#define _ade7858_sclk_output_high()         (ADE7858_SCLK_OUT set ADE7858_SCLK_BIT)//LATEbits.LATE9 = 1
#define _ade7858_sclk_output_low()          (ADE7858_SCLK_OUT clr ADE7858_SCLK_BIT)//LATEbits.LATE9 = 0
//sdo
#define _ade7858_sdo_dir_input()            (ADE7858_SDO_DIR set ADE7858_SDO_BIT)//TRISEbits.TRISE8 = 1
#define _ade7858_sdo_input()                (ADE7858_SDO_IN & ADE7858_SDO_BIT)//PORTEbits.RE8

//reset
#define _ade_reset_dir_output()              (ADE7858_RESET_DIR clr ADE7858_RESET_BIT)//TRISCbits.TRISC3 = 0
#define _ade_reset_output_low()              (ADE7858_RESET_OUT clr ADE7858_RESET_BIT)//LATCbits.LATC3 = 0
#define _ade_reset_output_high()             (ADE7858_RESET_OUT set ADE7858_RESET_BIT)//LATCbits.LATC3 = 1

////CF1 - active => PCB bi? ng???c
//#define _ade_active_pulse_dir_input()               TRISBbits.TRISB2 = 1
//#define _ade_active_pulse_input()                   PORTBbits.RB2
//#define _ade_active_pulse_interrupt_enable()        IEC1bits.INT1IE = 1
//#define _ade_active_pulse_interrupt_disable()       IEC1bits.INT1IE = 0
//#define _ade_active_pulse_interrupt_flag_status()   (IFS1bits.INT1IF)
//#define _ade_active_pulse_interrupt_flag_clear()    (IFS1bits.INT1IF = 0)
//#define _ade_active_pulse_interrupt_status()        (IEC1bits.INT1IE)
//#define _ade_active_pulse_interrupt_high_to_low()   INTCON2bits.INT1EP = 1
//#define _ade_active_pulse_interrupt_select()        RPINR0bits.INT1R = 13
////CF2 - reactive
//#define _ade_reactive_pulse_dir_input()                 TRISBbits.TRISB4 = 1
//#define _ade_reactive_pulse_input()                     PORTBbits.RB4
//#define _ade_reactive_pulse_interrupt_enable()          IEC1bits.INT2IE = 1
//#define _ade_reactive_pulse_interrupt_disable()         IEC1bits.INT2IE = 0
//#define _ade_reactive_pulse_interrupt_flag_status()     (IFS1bits.INT2IF)
//#define _ade_reactive_pulse_interrupt_flag_clear()      (IFS1bits.INT2IF = 0)
//#define _ade_reactive_pulse_interrupt_status()          (IEC1bits.INT2IE)
//#define _ade_reactive_pulse_interrupt_high_to_low()     INTCON2bits.INT2EP = 1
//#define _ade_reactive_pulse_interrupt_select()          RPINR1bits.INT2R = 28

#if defined(_DT03MRF_PCB_PIC_AS8_S_V10_) || defined(_DT03MRF_PCB_PIC_AMS_S_V10_)
#define ADE_ACTIVE_PULSE_DIR                            TRISB
#define ADE_ACTIVE_PULSE_OUT                            LATB
#define ADE_ACTIVE_PULSE_IN                             PORTB
#define ADE_ACTIVE_PULSE_BIT                            BIT4
#define ADE_ACTIVE_PULSE_RPI_PIN                        28

#define ADE_REACTIVE_PULSE_DIR                          TRISB
#define ADE_REACTIVE_PULSE_OUT                          LATB
#define ADE_REACTIVE_PULSE_IN                           PORTB
#define ADE_REACTIVE_PULSE_BIT                          BIT2
#define ADE_REACTIVE_PULSE_RPI_PIN                      13

#define ADE_APPARENT_PULSE_DIR                          TRISB
#define ADE_APPARENT_PULSE_OUT                          LATB
#define ADE_APPARENT_PULSE_IN                           PORTB
#define ADE_APPARENT_PULSE_BIT                          BIT5
#define ADE_APPARENT_PULSE_RPI_PIN                      18
//CF1 - reactive
//#define _ade_reactive_pulse_dir_input()               TRISBbits.TRISB2 = 1
//#define _ade_reactive_pulse_input()                   PORTBbits.RB2
//#define _ade_reactive_pulse_interrupt_enable()        IEC1bits.INT1IE = 1
//#define _ade_reactive_pulse_interrupt_disable()       IEC1bits.INT1IE = 0
//#define _ade_reactive_pulse_interrupt_flag_status()   (IFS1bits.INT1IF)
//#define _ade_reactive_pulse_interrupt_flag_clear()    (IFS1bits.INT1IF = 0)
//#define _ade_reactive_pulse_interrupt_status()        (IEC1bits.INT1IE)
//#define _ade_reactive_pulse_interrupt_high_to_low()   INTCON2bits.INT1EP = 1
//#define _ade_reactive_pulse_interrupt_select()        RPINR0bits.INT1R = 13
////CF2 - active
//#define _ade_active_pulse_dir_input()                 TRISBbits.TRISB4 = 1
//#define _ade_active_pulse_input()                     PORTBbits.RB4
//#define _ade_active_pulse_interrupt_enable()          IEC1bits.INT2IE = 1
//#define _ade_active_pulse_interrupt_disable()         IEC1bits.INT2IE = 0
//#define _ade_active_pulse_interrupt_flag_status()     (IFS1bits.INT2IF)
//#define _ade_active_pulse_interrupt_flag_clear()      (IFS1bits.INT2IF = 0)
//#define _ade_active_pulse_interrupt_status()          (IEC1bits.INT2IE)
//#define _ade_active_pulse_interrupt_high_to_low()     INTCON2bits.INT2EP = 1
//#define _ade_active_pulse_interrupt_select()          RPINR1bits.INT2R = 28
////CF3 - apparent
//#define _ade_apparent_pulse_dir_input()                 TRISBbits.TRISB5 = 1
//#define _ade_apparent_pulse_input()                     PORTBbits.RB5
//#define _ade_apparent_pulse_interrupt_enable()          IEC3bits.INT3IE = 1
//#define _ade_apparent_pulse_interrupt_disable()         IEC3bits.INT3IE = 0
//#define _ade_apparent_pulse_interrupt_flag_status()     (IFS3bits.INT3IF)
//#define _ade_apparent_pulse_interrupt_flag_clear()      (IFS3bits.INT3IF = 0)
//#define _ade_apparent_pulse_interrupt_status()          (IEC3bits.INT3IE)
//#define _ade_apparent_pulse_interrupt_high_to_low()     INTCON2bits.INT3EP = 1
//#define _ade_apparent_pulse_interrupt_select()          RPINR1bits.INT3R = 18

#elif defined(_DT03MRF_PCB_PIC_AS8_S_V20_) || defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
#define ADE_ACTIVE_PULSE_DIR                            TRISF
#define ADE_ACTIVE_PULSE_OUT                            LATF
#define ADE_ACTIVE_PULSE_IN                             PORTF
#define ADE_ACTIVE_PULSE_BIT                            BIT3
#define ADE_ACTIVE_PULSE_RPI_PIN                        16

#define ADE_REACTIVE_PULSE_DIR                          TRISF
#define ADE_REACTIVE_PULSE_OUT                          LATF
#define ADE_REACTIVE_PULSE_IN                           PORTF
#define ADE_REACTIVE_PULSE_BIT                          BIT5
#define ADE_REACTIVE_PULSE_RPI_PIN                      17

#define ADE_APPARENT_PULSE_DIR                          TRISF
#define ADE_APPARENT_PULSE_OUT                          LATF
#define ADE_APPARENT_PULSE_IN                           PORTF
#define ADE_APPARENT_PULSE_BIT                          BIT4
#define ADE_APPARENT_PULSE_RPI_PIN                      10

#elif defined(_DT03MRF_PCB_PIC_AS8_S_V12_)
#define ADE_ACTIVE_PULSE_DIR                            TRISB
#define ADE_ACTIVE_PULSE_OUT                            LATB
#define ADE_ACTIVE_PULSE_IN                             PORTB
#define ADE_ACTIVE_PULSE_BIT                            BIT2
#define ADE_ACTIVE_PULSE_RPI_PIN                        13

#define ADE_REACTIVE_PULSE_DIR                          TRISB
#define ADE_REACTIVE_PULSE_OUT                          LATB
#define ADE_REACTIVE_PULSE_IN                           PORTB
#define ADE_REACTIVE_PULSE_BIT                          BIT4
#define ADE_REACTIVE_PULSE_RPI_PIN                      28

#define ADE_APPARENT_PULSE_DIR                          TRISB
#define ADE_APPARENT_PULSE_OUT                          LATB
#define ADE_APPARENT_PULSE_IN                           PORTB
#define ADE_APPARENT_PULSE_BIT                          BIT5
#define ADE_APPARENT_PULSE_RPI_PIN                      18
#endif

//CF1 - active
#define _ade_active_pulse_dir_input()                 (ADE_ACTIVE_PULSE_DIR set ADE_ACTIVE_PULSE_BIT)//TRISBbits.TRISB4 = 1
#define _ade_active_pulse_input()                     (ADE_ACTIVE_PULSE_IN & ADE_ACTIVE_PULSE_BIT)//PORTBbits.RB4
#define _ade_active_pulse_interrupt_enable()          IEC1bits.INT2IE = 1
#define _ade_active_pulse_interrupt_disable()         IEC1bits.INT2IE = 0
#define _ade_active_pulse_interrupt_flag_status()     (IFS1bits.INT2IF)
#define _ade_active_pulse_interrupt_flag_clear()      (IFS1bits.INT2IF = 0)
#define _ade_active_pulse_interrupt_status()          (IEC1bits.INT2IE)
#define _ade_active_pulse_interrupt_high_to_low()     INTCON2bits.INT2EP = 1
#define _ade_active_pulse_interrupt_select()          (RPINR1bits.INT2R = ADE_ACTIVE_PULSE_RPI_PIN)//28

//CF2 - reactive
#define _ade_reactive_pulse_dir_input()               (ADE_REACTIVE_PULSE_DIR set ADE_REACTIVE_PULSE_BIT)//TRISFbits.TRISF5 = 1
#define _ade_reactive_pulse_input()                   (ADE_REACTIVE_PULSE_IN & ADE_REACTIVE_PULSE_BIT)//PORTBbits.RB2
#define _ade_reactive_pulse_interrupt_enable()        IEC1bits.INT1IE = 1
#define _ade_reactive_pulse_interrupt_disable()       IEC1bits.INT1IE = 0
#define _ade_reactive_pulse_interrupt_flag_status()   (IFS1bits.INT1IF)
#define _ade_reactive_pulse_interrupt_flag_clear()    (IFS1bits.INT1IF = 0)
#define _ade_reactive_pulse_interrupt_status()        (IEC1bits.INT1IE)
#define _ade_reactive_pulse_interrupt_high_to_low()   INTCON2bits.INT1EP = 1
#define _ade_reactive_pulse_interrupt_select()        (RPINR0bits.INT1R = ADE_REACTIVE_PULSE_RPI_PIN)//13

//CF3 - apparent
#define _ade_apparent_pulse_dir_input()                 (ADE_APPARENT_PULSE_DIR set ADE_APPARENT_PULSE_BIT)//TRISBbits.TRISB5 = 1
#define _ade_apparent_pulse_input()                     (ADE_APPARENT_PULSE_IN & ADE_APPARENT_PULSE_BIT)//PORTBbits.RB5
#define _ade_apparent_pulse_interrupt_enable()          IEC3bits.INT3IE = 1
#define _ade_apparent_pulse_interrupt_disable()         IEC3bits.INT3IE = 0
#define _ade_apparent_pulse_interrupt_flag_status()     (IFS3bits.INT3IF)
#define _ade_apparent_pulse_interrupt_flag_clear()      (IFS3bits.INT3IF = 0)
#define _ade_apparent_pulse_interrupt_status()          (IEC3bits.INT3IE)
#define _ade_apparent_pulse_interrupt_high_to_low()     INTCON2bits.INT3EP = 1
#define _ade_apparent_pulse_interrupt_select()          (RPINR1bits.INT3R = ADE_APPARENT_PULSE_RPI_PIN)//18


#ifdef ADE7858_POWER_CONTROL_SUPPORT
#if defined(_DT03MRF_PCB_PIC_AS8_S_V10_) || defined(_DT03MRF_PCB_PIC_AMS_S_V10_) || defined(_DT03MRF_PCB_PIC_AS8_S_V12_)
#define ADE7858_PM0_DIR                     TRISG
#define ADE7858_PM0_OUT                     LATG
#define ADE7858_PM0_BIT                     BIT6

#define ADE7858_PM1_DIR                     TRISC
#define ADE7858_PM1_OUT                     LATC
#define ADE7858_PM1_BIT                     BIT4
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V20_) || defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
#define ADE7858_PM0_DIR                     TRISB
#define ADE7858_PM0_OUT                     LATB
#define ADE7858_PM0_BIT                     BIT13

#define ADE7858_PM1_DIR                     TRISB
#define ADE7858_PM1_OUT                     LATB
#define ADE7858_PM1_BIT                     BIT12
#endif

//pm0
#define _ade7858_pm0_dir_output()           (ADE7858_PM0_DIR clr ADE7858_PM0_BIT)//TRISGbits.TRISG6 = 0
#define _ade7858_pm0_output_high()          (ADE7858_PM0_OUT set ADE7858_PM0_BIT)//LATGbits.LATG6 = 1
#define _ade7858_pm0_output_low()           (ADE7858_PM0_OUT clr ADE7858_PM0_BIT)//LATGbits.LATG6 = 0
//pm1
#define _ade7858_pm1_dir_output()           (ADE7858_PM1_DIR clr ADE7858_PM1_BIT)//TRISCbits.TRISC4 = 0
#define _ade7858_pm1_output_high()          (ADE7858_PM1_OUT set ADE7858_PM1_BIT)//LATCbits.LATC4 = 1
#define _ade7858_pm1_output_low()           (ADE7858_PM1_OUT clr ADE7858_PM1_BIT)//LATCbits.LATC4 = 0
#endif
#endif
////////////////////////////////////////////////////////////////////////////////
/*   for devices    */
////////////////////////////////////////////////////////////////////////////////
//khong dung
#define ACTIVE_PULSE_DIR                    TRISB
#define ACTIVE_PULSE_OUT                    LATB
#define ACTIVE_PULSE_BIT                    BIT2

#define REACTIVE_PULSE_DIR                  TRISB
#define REACTIVE_PULSE_OUT                  LATB
#define REACTIVE_PULSE_BIT                  BIT4

#ifdef ADNOMAL_LED_SUPPORT //defined(_DT03MRF_PCB_PIC_AS8_S_V10_) || defined(_DT03MRF_PCB_PIC_AMS_S_V10_)
//ko co
#if defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
    #define ADNORMAL_LED_DIR                    TRISB
    #define ADNORMAL_LED_OUT                    LATB
    #define ADNORMAL_LED_BIT                    BIT0
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V20_)
    #define ADNORMAL_LED_DIR                    TRISG
    #define ADNORMAL_LED_OUT                    LATG
    #define ADNORMAL_LED_BIT                    BIT3
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V12_)
    #define ADNORMAL_LED_DIR                    TRISA
    #define ADNORMAL_LED_OUT                    LATA
    #define ADNORMAL_LED_BIT                    BIT4
#endif
#endif

#if defined(_DT03MRF_PCB_PIC_AS8_S_V10_)
#define CALIB_ENABLE_DIR                    TRISB
#define CALIB_ENABLE_IN                     PORTB
#define CALIB_ENABLE_OUT                    LATB
#define CALIB_ENABLE_BIT                    BIT7
#elif defined(_DT03MRF_PCB_PIC_AMS_S_V10_)
#define CALIB_ENABLE_DIR                    TRISA
#define CALIB_ENABLE_IN                     PORTA
#define CALIB_ENABLE_OUT                    LATA
#define CALIB_ENABLE_BIT                    BIT3
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V20_)
#define CALIB_ENABLE_DIR                    TRISG
#define CALIB_ENABLE_IN                     PORTG
#define CALIB_ENABLE_OUT                    LATG
#define CALIB_ENABLE_BIT                    BIT2
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
#define CALIB_ENABLE_DIR                    TRISG
#define CALIB_ENABLE_IN                     PORTG
#define CALIB_ENABLE_OUT                    LATG
#define CALIB_ENABLE_BIT                    BIT3
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V12_)
#define CALIB_ENABLE_DIR                    TRISB
#define CALIB_ENABLE_IN                     PORTB
#define CALIB_ENABLE_OUT                    LATB
#define CALIB_ENABLE_BIT                    BIT7
#endif

#if defined(_DT03MRF_PCB_PIC_AS8_S_V10_) || defined(_DT03MRF_PCB_PIC_AMS_S_V10_) || defined(_DT03MRF_PCB_PIC_AS8_S_V12_)
#define BUTTON_UP_DIR                       TRISE
#define BUTTON_UP_IN                        PORTE
#define BUTTON_UP_OUT                       LATE
#define BUTTON_UP_IOCN                      IOCNE
#define BUTTON_UP_IOCP                      IOCPE
#define BUTTON_UP_IOCF                      IOCFE
#define BUTTON_UP_BIT                       BIT5

#define BUTTON_DOWN_DIR                     TRISE
#define BUTTON_DOWN_IN                      PORTE
#define BUTTON_DOWN_OUT                     LATE
#define BUTTON_DOWN_IOCN                    IOCNE
#define BUTTON_DOWN_IOCP                    IOCPE
#define BUTTON_DOWN_IOCF                    IOCFE
#define BUTTON_DOWN_BIT                     BIT6

#define BATT_MONITOR_DIR                    TRISE
#define BATT_MONITOR_IN                     PORTE
#define BATT_MONITOR_OUT                    LATE
#define BATT_MONITOR_BIT                    BIT4

#define MAGNETIC_DETECT_DIR                 TRISG
#define MAGNETIC_DETECT_IN                  PORTG
#define MAGNETIC_DETECT_OUT                 LATG
#define MAGNETIC_DETECT_BIT                 BIT15

#if defined(_DT03MRF_PCB_PIC_AS8_S_V10_) || defined(_DT03MRF_PCB_PIC_AMS_S_V10_)
#define WATCHDOG_PULSE_DIR                  TRISF
#define WATCHDOG_PULSE_OUT                  LATF
#define WATCHDOG_PULSE_BIT                  BIT2
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V12_)
#define WATCHDOG_PULSE_DIR                  TRISF
#define WATCHDOG_PULSE_OUT                  LATF
#define WATCHDOG_PULSE_BIT                  BIT8
#endif

#elif defined(_DT03MRF_PCB_PIC_AS8_S_V20_)
//E7 -> C1
#define BUTTON_UP_DIR                       TRISC
#define BUTTON_UP_IN                        PORTC
#define BUTTON_UP_OUT                       LATC
#define BUTTON_UP_IOCN                      IOCNC
#define BUTTON_UP_IOCP                      IOCPC
#define BUTTON_UP_IOCF                      IOCFC
#define BUTTON_UP_BIT                       BIT1
//C1 -> E7
#define BUTTON_DOWN_DIR                     TRISE
#define BUTTON_DOWN_IN                      PORTE
#define BUTTON_DOWN_OUT                     LATE
#define BUTTON_DOWN_IOCN                    IOCNE
#define BUTTON_DOWN_IOCP                    IOCPE
#define BUTTON_DOWN_IOCF                    IOCFE
#define BUTTON_DOWN_BIT                     BIT7

#define BATT_MONITOR_DIR                    TRISA
#define BATT_MONITOR_IN                     PORTA
#define BATT_MONITOR_OUT                    LATA
#define BATT_MONITOR_BIT                    BIT14

#define MAGNETIC_DETECT_DIR                 TRISD
#define MAGNETIC_DETECT_IN                  PORTD
#define MAGNETIC_DETECT_OUT                 LATD
#define MAGNETIC_DETECT_BIT                 BIT9

#define WATCHDOG_PULSE_DIR                  TRISB
#define WATCHDOG_PULSE_OUT                  LATB
#define WATCHDOG_PULSE_BIT                  BIT6

#elif defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
//E7 -> C1
#define BUTTON_UP_DIR                       TRISC
#define BUTTON_UP_IN                        PORTC
#define BUTTON_UP_OUT                       LATC
#define BUTTON_UP_IOCN                      IOCNC
#define BUTTON_UP_IOCP                      IOCPC
#define BUTTON_UP_IOCF                      IOCFC
#define BUTTON_UP_BIT                       BIT1
//C1 -> E7
#define BUTTON_DOWN_DIR                     TRISE
#define BUTTON_DOWN_IN                      PORTE
#define BUTTON_DOWN_OUT                     LATE
#define BUTTON_DOWN_IOCN                    IOCNE
#define BUTTON_DOWN_IOCP                    IOCPE
#define BUTTON_DOWN_IOCF                    IOCFE
#define BUTTON_DOWN_BIT                     BIT7

#define BATT_MONITOR_DIR                    TRISB
#define BATT_MONITOR_IN                     PORTB
#define BATT_MONITOR_OUT                    LATB
#define BATT_MONITOR_BIT                    BIT6

#define MAGNETIC_DETECT_DIR                 TRISA
#define MAGNETIC_DETECT_IN                  PORTA
#define MAGNETIC_DETECT_OUT                 LATA
#define MAGNETIC_DETECT_BIT                 BIT14

#define WATCHDOG_PULSE_DIR                  TRISB
#define WATCHDOG_PULSE_OUT                  LATB
#define WATCHDOG_PULSE_BIT                  BIT1
#endif

#define total_active_energy_pulse_dir_output()      (ACTIVE_PULSE_DIR clr ACTIVE_PULSE_BIT)
#define total_active_energy_pulse_start()           (ACTIVE_PULSE_OUT clr ACTIVE_PULSE_BIT)
#define total_active_energy_pulse_end()             (ACTIVE_PULSE_OUT set ACTIVE_PULSE_BIT)
#define total_active_energy_pulse_toggle()          (ACTIVE_PULSE_OUT tgl ACTIVE_PULSE_BIT)

#define total_reactive_energy_pulse_dir_output()    (REACTIVE_PULSE_DIR clr REACTIVE_PULSE_BIT)
#define total_reactive_energy_pulse_start()         (REACTIVE_PULSE_OUT clr REACTIVE_PULSE_BIT)
#define total_reactive_energy_pulse_end()           (REACTIVE_PULSE_OUT set REACTIVE_PULSE_BIT)
#define total_reactive_energy_pulse_toggle()        (REACTIVE_PULSE_OUT tgl REACTIVE_PULSE_BIT)

#ifdef ADNOMAL_LED_SUPPORT
    #define adnormal_led_dir_output()                   (ADNORMAL_LED_DIR clr ADNORMAL_LED_BIT)
    #if defined(_DT03MRF_PCB_PIC_AS8_S_V12_)
    #define adnormal_led_start()                        (ADNORMAL_LED_OUT clr ADNORMAL_LED_BIT)
    #define adnormal_led_end()                          (ADNORMAL_LED_OUT set ADNORMAL_LED_BIT)
    #else
    #define adnormal_led_start()                        (ADNORMAL_LED_OUT set ADNORMAL_LED_BIT)
    #define adnormal_led_end()                          (ADNORMAL_LED_OUT clr ADNORMAL_LED_BIT)
    #endif
    #define adnormal_led_toggle()                       (ADNORMAL_LED_OUT tgl ADNORMAL_LED_BIT)
#else
    #define adnormal_led_dir_output()                   nop() // quanhdt 20/10/2019 (1)
    #define adnormal_led_start()                        nop() // quanhdt 20/10/2019 (1)
    #define adnormal_led_end()                          nop() // quanhdt 20/10/2019 (1)
    #define adnormal_led_toggle()                       nop() // quanhdt 20/10/2019 (1)
#endif

//jump can chinh
#define calib_enable_dir_input()          (CALIB_ENABLE_DIR set CALIB_ENABLE_BIT)
#define calib_enable_dir_output()         (CALIB_ENABLE_DIR clr CALIB_ENABLE_BIT)
#define calib_enable_pullup_enable()      nop() // quanhdt 20/10/2019 (1)//(CALIB_ENABLE_REN |= CALIB_ENABLE_BIT)
#define calib_enable_pullup_disable()     nop() // quanhdt 20/10/2019 (1)//(CALIB_ENABLE_REN clr CALIB_ENABLE_BIT)
#define calib_enable_pullup()             nop() // quanhdt 20/10/2019(1)//(CALIB_ENABLE_OUT |= CALIB_ENABLE_BIT)
#define calib_enable_input()              (CALIB_ENABLE_IN & CALIB_ENABLE_BIT)
#define calib_enable_output_low()         (CALIB_ENABLE_OUT clr CALIB_ENABLE_BIT)
#define calib_enable_output_high()        (CALIB_ENABLE_OUT set CALIB_ENABLE_BIT)

//button up
#define button_up_dir_input()                 (BUTTON_UP_DIR set BUTTON_UP_BIT)
#define button_up_pullup_enable()             nop() // quanhdt 20/10/2019 (1)//(BUTTON_UP_REN set BUTTON_UP_BIT)
#define button_up_pullup_disable()            nop() // quanhdt 20/10/2019 (1)//(BUTTON_UP_REN clr BUTTON_UP_BIT)
#define button_up_pullup()                    nop() // quanhdt 20/10/2019 (1)//(BUTTON_UP_OUT set BUTTON_UP_BIT)
#define button_up_interrupt_enable()          (BUTTON_UP_IOCN set BUTTON_UP_BIT)//(IOCNEbits.IOCNE5 = 1)//{IOCNEbits.IOCNE5 = 1;IOCPEbits.IOCPE5 = 1;} //(BUTTON_UP_INTR_REG set BUTTON_UP_BIT)
#define button_up_interrupt_disable()         {BUTTON_UP_IOCN clr BUTTON_UP_BIT;BUTTON_UP_IOCP clr BUTTON_UP_BIT;}//{IOCNEbits.IOCNE5 = 0;IOCPEbits.IOCPE5 = 0;}//(BUTTON_UP_INTR_REG clr BUTTON_UP_BIT)
#define button_up_interrupt_low_to_high()     {BUTTON_UP_IOCN clr BUTTON_UP_BIT;BUTTON_UP_IOCP set BUTTON_UP_BIT;}//{IOCPEbits.IOCPE5 = 1;IOCNEbits.IOCNE5 = 0;}//(BUTTON_UP_INTR_REG_EDGE clr BUTTON_UP_BIT)
#define button_up_interrupt_high_to_low()     {BUTTON_UP_IOCN set BUTTON_UP_BIT;BUTTON_UP_IOCP clr BUTTON_UP_BIT;}//{IOCNEbits.IOCNE5 = 1;IOCPEbits.IOCPE5 = 0;}//(BUTTON_UP_INTR_REG_EDGE set BUTTON_UP_BIT)
#define button_up_interrupt_flag_check()      (BUTTON_UP_IOCF & BUTTON_UP_BIT)//(IOCFEbits.IOCFE5)//(BUTTON_UP_INTR_REG_FLAG & BUTTON_UP_BIT)
#define button_up_interrupt_flag_clear()      (BUTTON_UP_IOCF clr BUTTON_UP_BIT)//(IOCFEbits.IOCFE5 = 0)//(BUTTON_UP_INTR_REG_FLAG clr BUTTON_UP_BIT)
#define button_up_input()                     (BUTTON_UP_IN & BUTTON_UP_BIT)

//button down
#define button_down_dir_input()                 (BUTTON_DOWN_DIR set BUTTON_DOWN_BIT)
#define button_down_pullup_enable()             nop() // quanhdt 20/10/2019 (1)//(BUTTON_DOWN_REN set BUTTON_DOWN_BIT)
#define button_down_pullup_disable()            nop() // quanhdt 20/10/2019 (1)//(BUTTON_DOWN_REN clr BUTTON_DOWN_BIT)
#define button_down_pullup()                    nop() // quanhdt 20/10/2019 (1)//(BUTTON_DOWN_OUT set BUTTON_DOWN_BIT)
#define button_down_interrupt_enable()          (BUTTON_DOWN_IOCN set BUTTON_DOWN_BIT)//(IOCNEbits.IOCNE6 = 1)//{IOCNEbits.IOCNE6 = 1;IOCPEbits.IOCPE6 = 1;}//(BUTTON_DOWN_INTR_REG set BUTTON_DOWN_BIT)
#define button_down_interrupt_disable()         {BUTTON_DOWN_IOCN clr BUTTON_DOWN_BIT;BUTTON_DOWN_IOCP clr BUTTON_DOWN_BIT;}//{IOCNEbits.IOCNE6 = 0;IOCPEbits.IOCPE6 = 0;}//(BUTTON_DOWN_INTR_REG clr BUTTON_DOWN_BIT)
#define button_down_interrupt_low_to_high()     {BUTTON_DOWN_IOCN clr BUTTON_DOWN_BIT;BUTTON_DOWN_IOCP set BUTTON_DOWN_BIT;}//{IOCPEbits.IOCPE6 = 1;IOCNEbits.IOCNE6 = 0;}//(BUTTON_DOWN_INTR_REG_EDGE clr BUTTON_DOWN_BIT)
#define button_down_interrupt_high_to_low()     {BUTTON_DOWN_IOCN set BUTTON_DOWN_BIT;BUTTON_DOWN_IOCP clr BUTTON_DOWN_BIT;}//{IOCNEbits.IOCNE6 = 1;IOCPEbits.IOCPE6 = 0;}//(BUTTON_DOWN_INTR_REG_EDGE set BUTTON_DOWN_BIT)
#define button_down_interrupt_flag_check()      (BUTTON_DOWN_IOCF & BUTTON_DOWN_BIT)//(IOCFEbits.IOCFE6)//(BUTTON_DOWN_INTR_REG_FLAG & BUTTON_DOWN_BIT)
#define button_down_interrupt_flag_clear()      (BUTTON_DOWN_IOCF clr BUTTON_DOWN_BIT)//(IOCFEbits.IOCFE6 = 0)//(BUTTON_DOWN_INTR_REG_FLAG clr BUTTON_DOWN_BIT)
#define button_down_input()                     (BUTTON_DOWN_IN & BUTTON_DOWN_BIT)

//giam sat pin
#define batt_monitor_dir_input()                (BATT_MONITOR_DIR set BATT_MONITOR_BIT)
#define batt_monitor_pullup_enable()            nop() // quanhdt 20/10/2019 (1)//(BATT_MONITOR_REN set BATT_MONITOR_BIT)
#define batt_monitor_pullup_disable()           nop() // quanhdt 20/10/2019 (1)// (BATT_MONITOR_REN clr BATT_MONITOR_BIT)
#define batt_monitor_pullup()                   nop() // quanhdt 20/10/2019 (1)//(BATT_MONITOR_OUT set BATT_MONITOR_BIT)
#define batt_monitor_pulldown()                 nop() // quanhdt 20/10/2019 (1)//(BATT_MONITOR_OUT clr BATT_MONITOR_BIT)
#define batt_monitor_input()                    (BATT_MONITOR_IN & BATT_MONITOR_BIT)

//canh bao tu truong
#define magnetic_detect_dir_input()          (MAGNETIC_DETECT_DIR set MAGNETIC_DETECT_BIT)
#define magnetic_detect_dir_output()         (MAGNETIC_DETECT_DIR clr MAGNETIC_DETECT_BIT)
#define magnetic_detect_pullup_enable()      nop() // quanhdt 20/10/2019 (1)//(MAGNETIC_DETECT_REN set MAGNETIC_DETECT_BIT)
#define magnetic_detect_pullup_disable()     nop() // quanhdt 20/10/2019(1)//(MAGNETIC_DETECT_REN clr MAGNETIC_DETECT_BIT)
#define magnetic_detect_pullup()             nop() // quanhdt 20/10/2019(1)//(MAGNETIC_DETECT_OUT set MAGNETIC_DETECT_BIT)
#define magnetic_detect_input()              (MAGNETIC_DETECT_IN & MAGNETIC_DETECT_BIT)
#define magnetic_detect_output_low()         (MAGNETIC_DETECT_OUT clr MAGNETIC_DETECT_BIT)
#define magnetic_detect_output_high()        (MAGNETIC_DETECT_OUT set MAGNETIC_DETECT_BIT)

#define mcu_watchdog_dir_output()            (WATCHDOG_PULSE_DIR clr WATCHDOG_PULSE_BIT)
#define mcu_watchdog_pullup_enable()         nop() // quanhdt 20/10/2019(1)//(WATCHDOG_PULSE_REN set WATCHDOG_PULSE_BIT)
#define mcu_watchdog_start()                 (WATCHDOG_PULSE_OUT clr WATCHDOG_PULSE_BIT)
#define mcu_watchdog_end()                   (WATCHDOG_PULSE_OUT set WATCHDOG_PULSE_BIT)
#define mcu_watchdog_toggle()                (WATCHDOG_PULSE_OUT tgl WATCHDOG_PULSE_BIT)

////////////////////////////////////////////////////////////////////////////////
/*   for low voltage detect    */
////////////////////////////////////////////////////////////////////////////////
//phat hien mat dien
#if defined(_DT03MRF_PCB_PIC_AS8_S_V10_) || defined(_DT03MRF_PCB_PIC_AMS_S_V10_) || defined(_DT03MRF_PCB_PIC_AS8_S_V12_)
#define POWER_FAIL_DETECT_DIR               TRISE
#define POWER_FAIL_DETECT_IN                PORTE
#define POWER_FAIL_DETECT_OUT               LATE
#define POWER_FAIL_DETECT_IOCN              IOCNE
#define POWER_FAIL_DETECT_IOCP              IOCPE
#define POWER_FAIL_DETECT_IOCF              IOCFE
#define POWER_FAIL_DETECT_BIT               BIT7

#define power_fail_detect_dir_input()               (POWER_FAIL_DETECT_DIR set POWER_FAIL_DETECT_BIT)
#define power_fail_detect_pullup_enable()           nop()//(POWER_FAIL_DETECT_REN set POWER_FAIL_DETECT_BIT)
#define power_fail_detect_pullup_disable()          nop()// (POWER_FAIL_DETECT_REN clr POWER_FAIL_DETECT_BIT)
#define power_fail_detect_pullup()                  nop()//(POWER_FAIL_DETECT_OUT set POWER_FAIL_DETECT_BIT)
#define power_fail_detect_input()                   (POWER_FAIL_DETECT_IN & POWER_FAIL_DETECT_BIT)
#define power_fail_detect_interrupt_enable()        (POWER_FAIL_DETECT_IOCN set POWER_FAIL_DETECT_BIT)//(IOCNEbits.IOCNE7 = 1) //{IOCNEbits.IOCNE7 = 1;IOCPEbits.IOCPE7 = 1;}//(POWER_FAIL_DETECT_INTR_REG set POWER_FAIL_DETECT_BIT)
#define power_fail_detect_interrupt_disable()       {POWER_FAIL_DETECT_IOCN clr POWER_FAIL_DETECT_BIT;POWER_FAIL_DETECT_IOCP clr POWER_FAIL_DETECT_BIT;}////{IOCNEbits.IOCNE7 = 0;IOCPEbits.IOCPE7 = 0;}//(POWER_FAIL_DETECT_INTR_REG clr POWER_FAIL_DETECT_BIT)
#define power_fail_detect_interrupt_low_to_high()   {POWER_FAIL_DETECT_IOCN clr POWER_FAIL_DETECT_BIT;POWER_FAIL_DETECT_IOCP set POWER_FAIL_DETECT_BIT;}//{IOCPEbits.IOCPE7 = 1;IOCNEbits.IOCNE7 = 0;}//(POWER_FAIL_DETECT_INTR_REG_EDGE clr POWER_FAIL_DETECT_BIT)
#define power_fail_detect_interrupt_high_to_low()   {POWER_FAIL_DETECT_IOCN set POWER_FAIL_DETECT_BIT;POWER_FAIL_DETECT_IOCP clr POWER_FAIL_DETECT_BIT;}//{IOCNEbits.IOCNE7 = 1;IOCPEbits.IOCPE7 = 0;}//(POWER_FAIL_DETECT_INTR_REG_EDGE set POWER_FAIL_DETECT_BIT)
#define power_fail_detect_interrupt_flag_check()    (POWER_FAIL_DETECT_IOCF & POWER_FAIL_DETECT_BIT)//(IOCFEbits.IOCFE7)//(POWER_FAIL_DETECT_INTR_REG_FLAG & POWER_FAIL_DETECT_BIT)
#define power_fail_detect_interrupt_flag_clear()    (POWER_FAIL_DETECT_IOCF clr POWER_FAIL_DETECT_BIT)//(IOCFEbits.IOCFE7 = 0)//(POWER_FAIL_DETECT_INTR_REG_FLAG clr POWER_FAIL_DETECT_BIT)

#elif defined(_DT03MRF_PCB_PIC_AS8_S_V20_) || defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
#define POWER_FAIL_DETECT_DIR               TRISC
#define POWER_FAIL_DETECT_IN                PORTC
#define POWER_FAIL_DETECT_OUT               LATC
#define POWER_FAIL_DETECT_IOCN              IOCNC
#define POWER_FAIL_DETECT_IOCP              IOCPC
#define POWER_FAIL_DETECT_IOCF              IOCFC
#define POWER_FAIL_DETECT_BIT               BIT2
#define POWER_FAIL_DETECT_RPI_PIN           39

#define power_fail_detect_dir_input()               (POWER_FAIL_DETECT_DIR set POWER_FAIL_DETECT_BIT)
#define power_fail_detect_pullup_enable()           nop() // quanhdt 20/10/2019 (1)//(POWER_FAIL_DETECT_REN set POWER_FAIL_DETECT_BIT)
#define power_fail_detect_pullup_disable()          nop() // quanhdt 20/10/2019 (1)// (POWER_FAIL_DETECT_REN clr POWER_FAIL_DETECT_BIT)
#define power_fail_detect_pullup()                  nop() // quanhdt 20/10/2019 (1)//(POWER_FAIL_DETECT_OUT set POWER_FAIL_DETECT_BIT)
#define power_fail_detect_input()                   (POWER_FAIL_DETECT_IN & POWER_FAIL_DETECT_BIT)
#define power_fail_detect_interrupt_enable()        (IEC3bits.INT4IE = 1)
#define power_fail_detect_interrupt_disable()       (IEC3bits.INT4IE = 0)
#define power_fail_detect_interrupt_low_to_high()   (INTCON2bits.INT4EP = 0)
#define power_fail_detect_interrupt_high_to_low()   (INTCON2bits.INT4EP = 1)
#define power_fail_detect_interrupt_flag_check()    (IEC3bits.INT4IE)
#define power_fail_detect_interrupt_flag_clear()    (IFS3bits.INT4IF = 0)
#define power_fail_detect_interrupt_select()        (RPINR2bits.INT4R = POWER_FAIL_DETECT_RPI_PIN)

#endif
////////////////////////////////////////////////////////////////////////////////
/*   for SPI    */
////////////////////////////////////////////////////////////////////////////////
#if defined(_DT03MRF_PCB_PIC_AS8_S_V10_) || defined(_DT03MRF_PCB_PIC_AS8_S_V12_)
#define EEPROM_WR_EN_DIR                    TRISD
#define EEPROM_WR_EN_OUT                    LATD
#define EEPROM_WR_EN_BIT                    BIT4

#define EEPROM_CS1_DIR                      TRISD
#define EEPROM_CS1_OUT                      LATD
#define EEPROM_CS1_BIT                      BIT6

#define EEPROM_CS2_DIR                      TRISD
#define EEPROM_CS2_OUT                      LATD
#define EEPROM_CS2_BIT                      BIT5

#define FLASH_CS1_DIR                       TRISD
#define FLASH_CS1_OUT                       LATD
#define FLASH_CS1_BIT                       BIT7

//#define FLASH_CS3_DIR                       TRISD
//#define FLASH_CS3_OUT                       LATD
//#define FLASH_CS3_BIT                       BIT7

#define EEPROM_HOLD_DIR                     TRISF
#define EEPROM_HOLD_OUT                     LATF
#define EEPROM_HOLD_BIT                     BIT0

#elif defined(_DT03MRF_PCB_PIC_AMS_S_V10_)
#define EEPROM_WR_EN_DIR                    TRISG
#define EEPROM_WR_EN_OUT                    LATG
#define EEPROM_WR_EN_BIT                    BIT14

#define EEPROM_CS1_DIR                      TRISG
#define EEPROM_CS1_OUT                      LATG
#define EEPROM_CS1_BIT                      BIT13

#define EEPROM_CS2_DIR                      TRISG
#define EEPROM_CS2_OUT                      LATG
#define EEPROM_CS2_BIT                      BIT12

#define FLASH_CS3_DIR                       TRISE
#define FLASH_CS3_OUT                       LATE
#define FLASH_CS3_BIT                       BIT2

#define EEPROM_HOLD_DIR                     TRISE
#define EEPROM_HOLD_OUT                     LATE
#define EEPROM_HOLD_BIT                     BIT3

#elif defined(_DT03MRF_PCB_PIC_AS8_S_V20_) || defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
#define EEPROM_WR_EN_DIR                    TRISA
#define EEPROM_WR_EN_OUT                    LATA
#define EEPROM_WR_EN_BIT                    BIT7

#define EEPROM_HOLD_DIR                     TRISG
#define EEPROM_HOLD_OUT                     LATG
#define EEPROM_HOLD_BIT                     BIT1

#define EEPROM_CS1_DIR                      TRISG
#define EEPROM_CS1_OUT                      LATG
#define EEPROM_CS1_BIT                      BIT12

#define EEPROM_CS2_DIR                      TRISG
#define EEPROM_CS2_OUT                      LATG
#define EEPROM_CS2_BIT                      BIT13

#define FLASH_CS1_DIR                       TRISE
#define FLASH_CS1_OUT                       LATE
#define FLASH_CS1_BIT                       BIT4

#define FLASH_CS2_DIR                       TRISG
#define FLASH_CS2_OUT                       LATG
#define FLASH_CS2_BIT                       BIT15
#endif

#define eeprom_wr_en_dir_output()           (EEPROM_WR_EN_DIR clr EEPROM_WR_EN_BIT)
#define eeprom_wr_en_pullup_enable()        (1)//(EEPROM_WR_EN_REN set EEPROM_WR_EN_BIT)
#define eeprom_wr_en_low()                  (EEPROM_WR_EN_OUT clr EEPROM_WR_EN_BIT)
#define eeprom_wr_en_high()                 (EEPROM_WR_EN_OUT set EEPROM_WR_EN_BIT)

#define eeprom_hold_dir_output()            (EEPROM_HOLD_DIR clr EEPROM_HOLD_BIT)
#define eeprom_hold_high()                  (EEPROM_HOLD_OUT set EEPROM_HOLD_BIT)
#define eeprom_hold_low()                   (EEPROM_HOLD_OUT clr EEPROM_HOLD_BIT)

#define eeprom_cs1_dir_output()             (EEPROM_CS1_DIR clr EEPROM_CS1_BIT)
#define eeprom_cs1_pullup_enable()          (1)//(EEPROM_CS1_REN set EEPROM_CS1_BIT)
#define eeprom_cs1_low()                    (EEPROM_CS1_OUT clr EEPROM_CS1_BIT)
#define eeprom_cs1_high()                   (EEPROM_CS1_OUT set EEPROM_CS1_BIT)

#define eeprom_cs2_dir_output()             (EEPROM_CS2_DIR clr EEPROM_CS2_BIT)
#define eeprom_cs2_pullup_enable()          (1)//(EEPROM_CS2_REN set EEPROM_CS2_BIT)
#define eeprom_cs2_low()                    (EEPROM_CS2_OUT clr EEPROM_CS2_BIT)
#define eeprom_cs2_high()                   (EEPROM_CS2_OUT set EEPROM_CS2_BIT)

#define flash_cs1_dir_output()              (FLASH_CS1_DIR clr FLASH_CS1_BIT)
#define flash_cs1_output_high()             (FLASH_CS1_OUT set FLASH_CS1_BIT)
#define flash_cs1_output_low()              (FLASH_CS1_OUT clr FLASH_CS1_BIT)

//sua sau
#define flash_cs2_dir_output()              (FLASH_CS2_DIR clr FLASH_CS2_BIT)
#define flash_cs2_output_high()             (FLASH_CS2_OUT set FLASH_CS2_BIT)
#define flash_cs2_output_low()              (FLASH_CS2_OUT clr FLASH_CS2_BIT)

////chi co router 3 pha dung flash 2
//#define flash_cs2_dir_output()              (1)  
//#define flash_cs2_output_high()             (1) 
//#define flash_cs2_output_low()              (1)

////eeprom 3 la flash
//#define eeprom_cs3_dir_output()             flash_cs1_dir_output()
//#define eeprom_cs3_high()                   flash_cs1_output_high()
//#define eeprom_cs3_low()                    flash_cs1_output_low()

//eeprom 4 la flash
//sua sau
//#define eeprom_cs4_dir_output()             flash_cs1_dir_output()
//#define eeprom_cs4_high()                   flash_cs1_output_high()
//#define eeprom_cs4_low()                    flash_cs1_output_low()
////////////////////////////////////////////////////////////////////////////////
/*   for RTC    */
////////////////////////////////////////////////////////////////////////////////
#if defined(_DT03MRF_PCB_PIC_AS8_S_V10_) || defined(_DT03MRF_PCB_PIC_AMS_S_V10_) || defined(_DT03MRF_PCB_PIC_AS8_S_V12_)
#define RTC_CS_DIR                          TRISD
#define RTC_CS_OUT                          LATD
#define RTC_CS_BIT                          BIT8

#define RTC_INTR_DIR                        TRISD
#define RTC_INTR_IN                         PORTD
#define RTC_INTR_OUT                        LATD
#define RTC_INTR_BIT                        BIT9
#define RTC_INTR_RPI_PIN                    4

//intA
#define pcf2129_interrupt_select_pin()      RPINR2bits.INT4R = 4 //RP4
#define pcf2129_interrupt_dir_input()       (RTC_INTR_DIR set RTC_INTR_BIT)
#define pcf2129_interrupt_input()           (RTC_INTR_IN  & RTC_INTR_BIT)
#define pcf2129_interrupt_pullup_enable()   (1)//(RTC_INTR_REN set RTC_INTR_BIT)
#define pcf2129_interrupt_pullup_disable()  (1)//(RTC_INTR_REN clr RTC_INTR_BIT)
#define pcf2129_interrupt_pullup()          (1)//(RTC_INTR_OUT set RTC_INTR_BIT)
#define pcf2129_interrupt_enable()          IEC3bits.INT4IE = 1
#define pcf2129_interrupt_disable()         IEC3bits.INT4IE = 0
#define pcf2129_interrupt_low_to_high()     INTCON2bits.INT4EP = 0 // cu = 1?
#define pcf2129_interrupt_high_to_low()     INTCON2bits.INT4EP = 1 // cu = 0?
#define pcf2129_interrupt_flag_check()      (IFS3bits.INT4IF)
#define pcf2129_interrupt_flag_clear()      IFS3bits.INT4IF = 0//(RTC_INTR_REG_FLAG clr RTC_INTR_BIT)

#elif defined(_DT03MRF_PCB_PIC_AS8_S_V20_) || defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
#define RTC_CS_DIR                          TRISE
#define RTC_CS_OUT                          LATE
#define RTC_CS_BIT                          BIT5

#define RTC_INTR_DIR                        TRISE
#define RTC_INTR_IN                         PORTE
#define RTC_INTR_OUT                        LATE
#define RTC_INTR_BIT                        BIT6

#define RTC_INTR_IOCN                       IOCNE
#define RTC_INTR_IOCP                       IOCPE
#define RTC_INTR_IOCF                       IOCFE
#define RTC_INTR_BIT                        BIT6

#define pcf2129_interrupt_select_pin()      nop() // quanhdt 20/10/2019 (1) //ko có ng?t ngoài
#define pcf2129_interrupt_dir_input()       (RTC_INTR_DIR set RTC_INTR_BIT)
#define pcf2129_interrupt_input()           (RTC_INTR_IN  & RTC_INTR_BIT)
#define pcf2129_interrupt_pullup_enable()   nop() // quanhdt 20/10/2019 (1)//(RTC_INTR_REN set RTC_INTR_BIT)
#define pcf2129_interrupt_pullup_disable()  nop() // quanhdt 20/10/2019 (1)//(RTC_INTR_REN clr RTC_INTR_BIT)
#define pcf2129_interrupt_pullup()          nop() // quanhdt 20/10/2019 (1)//(RTC_INTR_OUT set RTC_INTR_BIT)
#define pcf2129_interrupt_disable()         {RTC_INTR_IOCN clr RTC_INTR_BIT;RTC_INTR_IOCP clr RTC_INTR_BIT;}
#define pcf2129_interrupt_low_to_high()     {RTC_INTR_IOCN clr RTC_INTR_BIT;RTC_INTR_IOCP set RTC_INTR_BIT;}
#define pcf2129_interrupt_high_to_low()     {RTC_INTR_IOCN set RTC_INTR_BIT;RTC_INTR_IOCP clr RTC_INTR_BIT;}
#define pcf2129_interrupt_enable()          pcf2129_interrupt_high_to_low()
#define pcf2129_interrupt_flag_check()      (RTC_INTR_IOCF & RTC_INTR_BIT)
#define pcf2129_interrupt_flag_clear()      (RTC_INTR_IOCF clr RTC_INTR_BIT)
#endif

#define pcf2129_cs_dir_output()             (RTC_CS_DIR clr RTC_CS_BIT)
#define pcf2129_cs_low()                    (RTC_CS_OUT clr RTC_CS_BIT)
#define pcf2129_cs_high()                   (RTC_CS_OUT set RTC_CS_BIT)

////////////////////////////////////////////////////////////////////////////////
/*   for SPI    */
////////////////////////////////////////////////////////////////////////////////
#if defined(_DT03MRF_PCB_PIC_AS8_S_V10_) || defined(_DT03MRF_PCB_PIC_AMS_S_V10_) || defined(_DT03MRF_PCB_PIC_AS8_S_V12_)
#define SPI_SCLK_DIR                        TRISD
#define SPI_SCLK_OUT                        LATD
#define SPI_SCLK_BIT                        BIT0

#define SPI_SDI_DIR                         TRISD
#define SPI_SDI_OUT                         LATD
#define SPI_SDI_BIT                         BIT11

#define SPI_SDO_DIR                         TRISD
#define SPI_SDO_IN                          PORTD
#define SPI_SDO_OUT                         LATD
#define SPI_SDO_BIT                         BIT10
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V20_) || defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
#define SPI_SCLK_DIR                        TRISG
#define SPI_SCLK_OUT                        LATG
#define SPI_SCLK_BIT                        BIT0

#define SPI_SDI_DIR                         TRISA
#define SPI_SDI_OUT                         LATA
#define SPI_SDI_BIT                         BIT6

#define SPI_SDO_DIR                         TRISG
#define SPI_SDO_IN                          PORTG
#define SPI_SDO_OUT                         LATG
#define SPI_SDO_BIT                         BIT14
#endif

//#define _spi_sdi_dir_output()        (SPI_SDI_DIR clr SPI_SDI_BIT)
//#define _spi_sdi_pullup_enable()     nop() // quanhdt 20/10/2019 ((1) //(SPI_SDI_REN set SPI_SDI_BIT)
//#define _spi_sdi_pullup()            nop() // quanhdt 20/10/2019 ((1)//(SPI_SDI_OUT set SPI_SDI_BIT)
//#define _spi_sdi_low()               (SPI_SDI_OUT clr SPI_SDI_BIT)
//#define _spi_sdi_high()              (SPI_SDI_OUT set SPI_SDI_BIT)
//
//#define _spi_sdo_dir_input()         (SPI_SDO_DIR set SPI_SDO_BIT) 
//#define _spi_sdo_pullup_enable()     nop() // quanhdt 20/10/2019 (1) //(SPI_SDO_REN set SPI_SDO_BIT)
//#define _spi_sdo_pullup_disable()    nop() // quanhdt 20/10/2019 ((1) //(SPI_SDO_REN clr SPI_SDO_BIT)
//#define _spi_sdo_pullup()            nop() // quanhdt 20/10/2019 ((1)//(SPI_SDO_OUT set SPI_SDO_BIT)
//#define _spi_sdo_pulldown()          nop() // quanhdt 20/10/2019 ((1)//(SPI_SDO_OUT clr SPI_SDO_BIT)
//#define _spi_sdo_input()             (SPI_SDO_IN & SPI_SDO_BIT)
//
//#define _spi_sclk_dir_output()       (SPI_SCLK_DIR clr SPI_SCLK_BIT)
//#define _spi_sclk_pullup_enable()    nop() // quanhdt 20/10/2019 ((1) //(SPI_SCLK_REN set SPI_SCLK_BIT)
//#define _spi_sclk_pullup_disable()   nop() // quanhdt 20/10/2019 ((1) //(SPI_SCLK_REN clr SPI_SCLK_BIT)
//#define _spi_sclk_pullup()           nop() // quanhdt 20/10/2019 ((1)//(SPI_SCLK_OUT set SPI_SCLK_BIT)
//#define _spi_sclk_low()              (SPI_SCLK_OUT clr SPI_SCLK_BIT)
//#define _spi_sclk_high()             (SPI_SCLK_OUT set SPI_SCLK_BIT)
//#define _spi_sclk_toggle()           (SPI_SCLK_OUT tgl SPI_SCLK_BIT)

////////////////////////////////////////////////////////////////////////////////
/*   other functions    */
////////////////////////////////////////////////////////////////////////////////
#ifdef RF_SUPPORT
#ifdef CC1101_MODULE_SUPPORT
#if defined(_DT03MRF_PCB_PIC_AS8_S_V20_)
#define RF_CS_DIR                               TRISA
#define RF_CS_OUT                               LATA
#define RF_CS_BIT                               BIT5

#define RF_GDO2_DIR                             TRISA
#define RF_GDO2_IN                              PORTA
#define RF_GDO2_BIT                             BIT4

#define RF_GDO0_DIR                             TRISA
#define RF_GDO0_IN                              PORTA
#define RF_GDO0_BIT                             BIT3

#define cc1101_gdo2_interrupt_disable()         {IOCNAbits.IOCNA4 = 0;IOCPAbits.IOCPA4 = 0;}
#define cc1101_gdo2_interrupt_low_to_high()     {IOCPAbits.IOCPA4 = 1;IOCNAbits.IOCNA4 = 0;}
#define cc1101_gdo2_interrupt_high_to_low()     {IOCPAbits.IOCPA4 = 0;IOCNAbits.IOCNA4 = 1;}
#define cc1101_gdo2_interrupt_flag_check()      (IOCFAbits.IOCFA4)
#define cc1101_gdo2_interrupt_flag_clear()      (IOCFAbits.IOCFA4 = 0)
#define cc1101_gdo2_pullup_enable()             (IOCPUAbits.IOCPA4 = 1)
#define cc1101_gdo2_pullup_disable()            (IOCPUAbits.IOCPA4 = 0)
#define cc1101_gdo2_pullup()                    (IOCPUAbits.IOCPA4 = 1)
#define cc1101_gdo2_pulldown()                  (IOCPDAbits.IOCPDA4 = 1)
#define cc1101_gdo2_interrupt_status_check()    (IOCPAbits.IOCPA4)// | IOCNDbits.IOCND12) //low to high

#define cc1101_gdo0_interrupt_enable()          (IOCNAbits.IOCNA3 = 1)
#define cc1101_gdo0_interrupt_disable()         (IOCNAbits.IOCNA3 = 0)
#else
#define RF_CS_DIR                               TRISD
#define RF_CS_OUT                               LATD
#define RF_CS_BIT                               BIT13

#define RF_GDO2_DIR                             TRISD
#define RF_GDO2_IN                              PORTD
#define RF_GDO2_BIT                             BIT12

#define RF_GDO0_DIR                             TRISD
#define RF_GDO0_IN                              PORTD
#define RF_GDO0_BIT                             BIT3

#define cc1101_gdo2_interrupt_disable()         {IOCNDbits.IOCND12 = 0;IOCPDbits.IOCPD12 = 0;}
#define cc1101_gdo2_interrupt_low_to_high()     {IOCPDbits.IOCPD12 = 1;IOCNDbits.IOCND12 = 0;}
#define cc1101_gdo2_interrupt_high_to_low()     {IOCPDbits.IOCPD12 = 0;IOCNDbits.IOCND12 = 1;}
#define cc1101_gdo2_interrupt_flag_check()      (IOCFDbits.IOCFD12)
#define cc1101_gdo2_interrupt_flag_clear()      (IOCFDbits.IOCFD12 = 0)
#define cc1101_gdo2_pullup_enable()             (IOCPUDbits.IOCPD12 = 1)
#define cc1101_gdo2_pullup_disable()            (IOCPUDbits.IOCPD12 = 0)
#define cc1101_gdo2_pullup()                    (IOCPUDbits.IOCPD12 = 1)
#define cc1101_gdo2_pulldown()                  (IOCPDDbits.IOCPDD12 = 1)
#define cc1101_gdo2_interrupt_status_check()    (IOCPDbits.IOCPD12)// | IOCNDbits.IOCND12) //low to high

#define cc1101_gdo0_interrupt_enable()          (IOCNDbits.IOCND3 = 1)
#define cc1101_gdo0_interrupt_disable()         (IOCNDbits.IOCND3 = 0)
#endif
#define cc1101_cs_dir_output()        (RF_CS_DIR clr RF_CS_BIT)
#define cc1101_cs_output_low()        (RF_CS_OUT clr RF_CS_BIT)
#define cc1101_cs_output_high()       (RF_CS_OUT set RF_CS_BIT)


#define cc1101_gdo2_dir_input()                 (RF_GDO2_DIR set RF_GDO2_BIT)
#define cc1101_gdo2_input()                     (RF_GDO2_IN & RF_GDO2_BIT)
#define cc1101_gdo2_interrupt_enable()          nop(); // quanhdt 20/10/2019  (1);//{IOCNDbits.IOCND12 = 1;IOCPDbits.IOCPD12 = 1;}


#define cc1101_gdo0_dir_input()                 (RF_GDO2_DIR set RF_GDO2_BIT)
#define cc1101_gdo0_input()                     (RF_GDO2_IN & RF_GDO2_BIT)

#define cc1101_gdo0_interrupt_low_to_high()     nop()
#define cc1101_gdo0_interrupt_high_to_low()     nop()
#define cc1101_gdo0_interrupt_flag_check()      nop()
#define cc1101_gdo0_interrupt_flag_clear()      nop()
#define cc1101_gdo0_pullup_enable()             nop()
#define cc1101_gdo0_pullup_disable()            nop()
#define cc1101_gdo0_pullup()                    nop()
#define cc1101_gdo0_pulldown()                  nop()

#ifdef RFPA_SUPPORT
#define RF_TXAMP_EN_DIR                     TRISD
#define RF_TXAMP_EN_OUT                     LATD
#define RF_TXAMP_EN_BIT                     BIT2
#define cc1101_tx_pa_dir_output()        (RF_TXAMP_EN_DIR clr RF_TXAMP_EN_BIT)
#define cc1101_tx_pa_enable()            (RF_TXAMP_EN_OUT set RF_TXAMP_EN_BIT)
#define cc1101_tx_pa_disable()           (RF_TXAMP_EN_OUT clr RF_TXAMP_EN_BIT)

#define RF_RXAMP_EN_DIR                     TRISD
#define RF_RXAMP_EN_OUT                     LATD
#define RF_RXAMP_EN_BIT                     BIT1
#define cc1101_rx_pa_dir_output()        (RF_RXAMP_EN_DIR clr RF_RXAMP_EN_BIT)
#define cc1101_rx_pa_enable()            (RF_RXAMP_EN_OUT clr RF_RXAMP_EN_BIT)
#define cc1101_rx_pa_disable()           (RF_RXAMP_EN_OUT set RF_RXAMP_EN_BIT)
#endif
#endif

#ifdef SI4464_MODULE_SUPPORT
#if defined(_DT03MRF_PCB_PIC_AS8_S_V20_)
#ifdef COMUNICATION_RF_PRIVATE_SPI //hungnd 21/01/2021 chinh sua spi rieng cho rf
    //hungnd 19/01/2021 doi lai SPi dung rieng (PCB DT03MRF_PCB_PIC_AS8_S_V21-namhv)
    #define RF_SPI_SCLK_DIR                     TRISA
    #define RF_SPI_SCLK_OUT                     LATA
    #define RF_SPI_SCLK_BIT                     BIT3

    #define RF_SPI_SDI_DIR                      TRISA
    #define RF_SPI_SDI_OUT                      LATA
    #define RF_SPI_SDI_BIT                      BIT15

    #define RF_SPI_SDO_DIR                      TRISA
    #define RF_SPI_SDO_IN                       PORTA
    #define RF_SPI_SDO_OUT                      LATA
    #define RF_SPI_SDO_BIT                      BIT4

    #define _rf_spi_sdi_dir_output()        (RF_SPI_SDI_DIR clr RF_SPI_SDI_BIT)
    #define _rf_spi_sdi_pullup_enable()      nop() // quanhdt 20/10/2019 ((1) //(SPI_SDI_REN set SPI_SDI_BIT)
    #define _rf_spi_sdi_pullup()             nop() // quanhdt 20/10/2019 ((1)//(SPI_SDI_OUT set SPI_SDI_BIT)
    #define _rf_spi_sdi_low()               (RF_SPI_SDI_OUT clr RF_SPI_SDI_BIT)
    #define _rf_spi_sdi_high()              (RF_SPI_SDI_OUT set RF_SPI_SDI_BIT)

    #define _rf_spi_sdo_dir_input()         (RF_SPI_SDO_DIR set RF_SPI_SDO_BIT) 
    #define _rf_spi_sdo_pullup_enable()      nop() // quanhdt 20/10/2019 (1) //(SPI_SDO_REN set SPI_SDO_BIT)
    #define _rf_spi_sdo_pullup_disable()     nop() // quanhdt 20/10/2019 ((1) //(SPI_SDO_REN clr SPI_SDO_BIT)
    #define _rf_spi_sdo_pullup()             nop() // quanhdt 20/10/2019 ((1)//(SPI_SDO_OUT set SPI_SDO_BIT)
    #define _rf_spi_sdo_pulldown()           nop() // quanhdt 20/10/2019 ((1)//(SPI_SDO_OUT clr SPI_SDO_BIT)
    #define _rf_spi_sdo_input()             (RF_SPI_SDO_IN & RF_SPI_SDO_BIT)

    #define _rf_spi_sclk_dir_output()       (RF_SPI_SCLK_DIR clr RF_SPI_SCLK_BIT)
    #define _rf_spi_sclk_pullup_enable()     nop() // quanhdt 20/10/2019 ((1) //(SPI_SCLK_REN set SPI_SCLK_BIT)
    #define _rf_spi_sclk_pullup_disable()    nop() // quanhdt 20/10/2019 ((1) //(SPI_SCLK_REN clr SPI_SCLK_BIT)
    #define _rf_spi_sclk_pullup()            nop() // quanhdt 20/10/2019 ((1)//(SPI_SCLK_OUT set SPI_SCLK_BIT)
    #define _rf_spi_sclk_low()              (RF_SPI_SCLK_OUT clr RF_SPI_SCLK_BIT)
    #define _rf_spi_sclk_high()             (RF_SPI_SCLK_OUT set RF_SPI_SCLK_BIT)
    #define _rf_spi_sclk_toggle()           (RF_SPI_SCLK_OUT tgl RF_SPI_SCLK_BIT)


    #define RF_CS_DIR                               TRISA
    #define RF_CS_OUT                               LATA
    #define RF_CS_BIT                               BIT5

    #define RF_GDO2_DIR                             TRISB
    #define RF_GDO2_IN                              PORTB
    #define RF_GDO2_BIT                             BIT0

    #define RF_GDO0_DIR                             TRISB
    #define RF_GDO0_IN                              PORTB
    #define RF_GDO0_OUT                             LATB
    #define RF_GDO0_BIT                             BIT1

    #define si4464_gdo2_interrupt_enable()           IOCNBbits.IOCNB0 = 1//nop(); // quanhdt 20/10/2019  (1);//
    #define si4464_gdo2_interrupt_disable()         {IOCNBbits.IOCNB0 = 0;IOCPBbits.IOCPB0 = 0;}
    #define si4464_gdo2_interrupt_low_to_high()     {IOCPBbits.IOCPB0 = 1;IOCNBbits.IOCNB0 = 0;}
    #define si4464_gdo2_interrupt_high_to_low()     {IOCPBbits.IOCPB0 = 0;IOCNBbits.IOCNB0 = 1;}
    #define si4464_gdo2_interrupt_flag_check()      (IOCFBbits.IOCFB0)
    #define si4464_gdo2_interrupt_flag_clear()      (IOCFBbits.IOCFB0 = 0)
    #define si4464_gdo2_pullup_enable()             (IOCPUBbits.IOCPB0 = 1)
    #define si4464_gdo2_pullup_disable()            (IOCPUBbits.IOCPB0 = 0)
    #define si4464_gdo2_pullup()                    (IOCPUBbits.IOCPB0 = 1)
    #define si4464_gdo2_pulldown()                  (IOCPDBbits.IOCPDB0 = 1)
    #define si4464_gdo2_interrupt_status_check()    (IOCNBbits.IOCNB0)// | IOCNDbits.IOCND12) //low to high

    #define si4464_gdo0_interrupt_enable()          (IOCNBbits.IOCNB0 = 1)
    #define si4464_gdo0_interrupt_disable()         (IOCNBbits.IOCNB0 = 0)
#else // not COMUNICATION_RF_PRIVATE_SPI
    //hungnd 19/01/2021 Doi lai SPI dung rieng ( khai bai cu dang dung chung SPI)
    #define RF_CS_DIR                               TRISA
    #define RF_CS_OUT                               LATA
    #define RF_CS_BIT                               BIT5

    #define RF_GDO2_DIR                             TRISA
    #define RF_GDO2_IN                              PORTA
    #define RF_GDO2_BIT                             BIT4

    #define RF_GDO0_DIR                             TRISA
    #define RF_GDO0_IN                              PORTA
    #define RF_GDO0_OUT                             LATA
    #define RF_GDO0_BIT                             BIT3

    #define si4464_gdo2_interrupt_enable()          IOCNAbits.IOCNA4 = 1//nop(); // quanhdt 20/10/2019  (1);//
    #define si4464_gdo2_interrupt_disable()         {IOCNAbits.IOCNA4 = 0;IOCPAbits.IOCPA4 = 0;}
    #define si4464_gdo2_interrupt_low_to_high()     {IOCPAbits.IOCPA4 = 1;IOCNAbits.IOCNA4 = 0;}
    #define si4464_gdo2_interrupt_high_to_low()     {IOCPAbits.IOCPA4 = 0;IOCNAbits.IOCNA4 = 1;}
    #define si4464_gdo2_interrupt_flag_check()      (IOCFAbits.IOCFA4)
    #define si4464_gdo2_interrupt_flag_clear()      (IOCFAbits.IOCFA4 = 0)
    #define si4464_gdo2_pullup_enable()             (IOCPUAbits.IOCPA4 = 1)
    #define si4464_gdo2_pullup_disable()            (IOCPUAbits.IOCPA4 = 0)
    #define si4464_gdo2_pullup()                    (IOCPUAbits.IOCPA4 = 1)
    #define si4464_gdo2_pulldown()                  (IOCPDAbits.IOCPDA4 = 1)
    #define si4464_gdo2_interrupt_status_check()    (IOCNAbits.IOCNA4)// | IOCNDbits.IOCND12) //low to high

    #define si4464_gdo0_interrupt_enable()          (IOCNAbits.IOCNA3 = 1)
    #define si4464_gdo0_interrupt_disable()         (IOCNAbits.IOCNA3 = 0)
#endif //spi dunng chung or rieng vs eefrom
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
    #define RF_CS_DIR                               TRISD
    #define RF_CS_OUT                               LATD
    #define RF_CS_BIT                               BIT3

    #define RF_GDO2_DIR                             TRISD
    #define RF_GDO2_IN                              PORTD
    #define RF_GDO2_BIT                             BIT1

    #define RF_GDO0_DIR                             TRISD
    #define RF_GDO0_IN                              PORTD
    #define RF_GDO0_OUT                             LATD
    #define RF_GDO0_BIT                             BIT2

    #define si4464_gdo2_interrupt_enable()          IOCNDbits.IOCND1 = 1//nop(); // quanhdt 20/10/2019  (1);//
    #define si4464_gdo2_interrupt_disable()         {IOCNDbits.IOCND1 = 0;IOCPDbits.IOCPD1 = 0;}
    #define si4464_gdo2_interrupt_low_to_high()     {IOCPDbits.IOCPD1 = 1;IOCNDbits.IOCND1 = 0;}
    #define si4464_gdo2_interrupt_high_to_low()     {IOCPDbits.IOCPD1 = 0;IOCNDbits.IOCND1 = 1;}
    #define si4464_gdo2_interrupt_flag_check()      (IOCFDbits.IOCFD1)
    #define si4464_gdo2_interrupt_flag_clear()      (IOCFDbits.IOCFD1 = 0)
    #define si4464_gdo2_pullup_enable()             (IOCPUDbits.IOCPD1 = 1)
    #define si4464_gdo2_pullup_disable()            (IOCPUDbits.IOCPD1 = 0)
    #define si4464_gdo2_pullup()                    (IOCPUDbits.IOCPD1 = 1)
    #define si4464_gdo2_pulldown()                  (IOCPDDbits.IOCPDD1 = 1)
    #define si4464_gdo2_interrupt_status_check()    (IOCNDbits.IOCND1)

    #define si4464_gdo0_interrupt_enable()          (IOCNDbits.IOCND2 = 1)
    #define si4464_gdo0_interrupt_disable()         (IOCNDbits.IOCND2 = 0)

#else
#endif //ENDIF PCB

#define si4464_cs_dir_output()                  (RF_CS_DIR clr RF_CS_BIT)
#define si4464_cs_output_low()                  (RF_CS_OUT clr RF_CS_BIT)
#define si4464_cs_output_high()                 (RF_CS_OUT set RF_CS_BIT)

#define si4464_gdo2_dir_input()                 (RF_GDO2_DIR set RF_GDO2_BIT)
#define si4464_gdo2_input()                     (RF_GDO2_IN & RF_GDO2_BIT)

#define si4464_sdn_dir_input()                 (RF_GDO0_DIR set RF_GDO0_BIT)
#define si4464_sdn_dir_output()                (RF_GDO0_DIR clr RF_GDO0_BIT)
#define si4464_sdn_input()                     (RF_GDO0_IN & RF_GDO0_BIT)
#define si4464_sdn_output_high()               (RF_GDO0_OUT set RF_GDO0_BIT)
#define si4464_sdn_output_low()                (RF_GDO0_OUT clr RF_GDO0_BIT)

#ifdef RFPA_SUPPORT
    #define RF_TXAMP_EN_DIR                     TRISD
    #define RF_TXAMP_EN_OUT                     LATD
    #define RF_TXAMP_EN_BIT                     BIT2
    #define si4464_tx_pa_dir_output()        (RF_TXAMP_EN_DIR clr RF_TXAMP_EN_BIT)
    #define si4464_tx_pa_enable()            (RF_TXAMP_EN_OUT set RF_TXAMP_EN_BIT)
    #define si4464_tx_pa_disable()           (RF_TXAMP_EN_OUT clr RF_TXAMP_EN_BIT)

    #define RF_RXAMP_EN_DIR                     TRISD
    #define RF_RXAMP_EN_OUT                     LATD
    #define RF_RXAMP_EN_BIT                     BIT1
    #define si4464_rx_pa_dir_output()        (RF_RXAMP_EN_DIR clr RF_RXAMP_EN_BIT)
    #define si4464_rx_pa_enable()            (RF_RXAMP_EN_OUT clr RF_RXAMP_EN_BIT)
    #define si4464_rx_pa_disable()           (RF_RXAMP_EN_OUT set RF_RXAMP_EN_BIT)
#endif // RFPA_SUPPORT
#endif //SI4464_MODULE_SUPPORT
#endif
													
					
								 
								 
								 
								
																						
																					   
																					  

								 
								 
								 
								
																					   
																					 
																					 

									   
									   
									   
																										   
														 
	  
////////////////////////////////////////////////////////////////////////////////
/*   other functions    */
////////////////////////////////////////////////////////////////////////////////
#if defined(_DT03MRF_PCB_PIC_AS8_S_V10_) || defined(_DT03MRF_PCB_PIC_AS8_S_V12_)
#define LCD_BACKLIT_DIR                     TRISB
#define LCD_BACKLIT_OUT                     LATB
#define LCD_BACKLIT_BIT                     BIT6
#elif defined(_DT03MRF_PCB_PIC_AMS_S_V10_)
#define LCD_BACKLIT_DIR                     TRISA
#define LCD_BACKLIT_OUT                     LATA
#define LCD_BACKLIT_BIT                     BIT2
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V20_) || defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
#define LCD_BACKLIT_DIR                     TRISD
#define LCD_BACKLIT_OUT                     LATD
#define LCD_BACKLIT_BIT                     BIT10
#endif

//LCD back light
#ifdef LCD_BACKLIT_SUPPORT
#define lcd_backlit_dir_output()            (LCD_BACKLIT_DIR clr LCD_BACKLIT_BIT)
#define lcd_backlit_pullup_enable()         nop() //(LCD_BACKLIT_REN set LCD_BACKLIT_BIT)
#define lcd_backlit_start()                 (LCD_BACKLIT_OUT clr LCD_BACKLIT_BIT)
#define lcd_backlit_end()                   (LCD_BACKLIT_OUT set LCD_BACKLIT_BIT)
#define lcd_backlit_toggle()                (LCD_BACKLIT_OUT tgl LCD_BACKLIT_BIT)
#endif

#ifdef RS422_RS485_CONTROL_SUPPORT
//high: RS422, RS485
//low: RS232
#if defined(_DT03MRF_PCB_PIC_AS8_S_V20_)
    #define RS422_CONTROL_DIR                   TRISD
    #define RS422_CONTROL_OUT                   LATD
    #define RS422_CONTROL_BIT                   BIT1
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
    #define RS422_CONTROL_DIR                   nop();
    #define RS422_CONTROL_OUT                   nop();
    #define RS422_CONTROL_BIT                   nop();
#endif
    #define rs422_control_dir_output()          (RS422_CONTROL_DIR clr RS422_CONTROL_BIT)
    #define rs422_control_enable()              (RS422_CONTROL_OUT set RS422_CONTROL_BIT)
    #define rs422_control_disable()             (RS422_CONTROL_OUT clr RS422_CONTROL_BIT)
#endif

#ifdef RS422_RS485_POWER_SUPPORT
#define RS422_POWER_DIR                     TRISA
#define RS422_POWER_OUT                     LATA
#define RS422_POWER_BIT                     BIT3

#define rs422_power_dir_output()            (RS422_POWER_DIR clr RS422_POWER_BIT)
#define rs422_power_enable()                (RS422_POWER_OUT set RS422_POWER_BIT)
#define rs422_power_disable()               (RS422_POWER_OUT clr RS422_POWER_BIT)
#endif

#ifdef COVER_DETECT_SUPPORT
#if defined(_DT03MRF_PCB_PIC_AS8_S_V20_) //kiem tra lai
#define COVER_DETECT_DIR                    TRISD
#define COVER_DETECT_OUT                    LATD
#define COVER_DETECT_IN                     PORTD
#define COVER_DETECT_BIT                    BIT8
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
#define COVER_DETECT_DIR                    TRISA
#define COVER_DETECT_OUT                    LATA
#define COVER_DETECT_IN                     PORTA
#define COVER_DETECT_BIT                    BIT2
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V10_) || defined(_DT03MRF_PCB_PIC_AS8_S_V12_)
#define COVER_DETECT_DIR                    TRISA
#define COVER_DETECT_OUT                    LATA
#define COVER_DETECT_IN                     PORTA
#define COVER_DETECT_BIT                    BIT14
#endif

#define cover_detect_dir_input()            (COVER_DETECT_DIR set COVER_DETECT_BIT)
#define cover_detect_input()                (COVER_DETECT_IN & COVER_DETECT_BIT)
#define cover_detect_pullup_disable()       nop() // quanhdt 20/10/2019 (1)
#endif

#ifdef TERMINAL_DETECT_SUPPORT
#if defined(_DT03MRF_PCB_PIC_AS8_S_V20_) || defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
#define TERMINAL_DETECT_DIR                 TRISF
#define TERMINAL_DETECT_OUT                 LATF
#define TERMINAL_DETECT_IN                  PORTF
#define TERMINAL_DETECT_BIT                 BIT6
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V10_) || defined(_DT03MRF_PCB_PIC_AS8_S_V12_)
#define TERMINAL_DETECT_DIR                 TRISF
#define TERMINAL_DETECT_OUT                 LATF
#define TERMINAL_DETECT_IN                  PORTF
#define TERMINAL_DETECT_BIT                 BIT2
#endif

#define terminal_detect_dir_input()         (TERMINAL_DETECT_DIR set TERMINAL_DETECT_BIT)
#define terminal_detect_input()             (TERMINAL_DETECT_IN & TERMINAL_DETECT_BIT)
#endif

#ifdef WINDOW_DETECT_SUPPORT
#if defined(_DT03MRF_PCB_PIC_AS8_S_V20_) || defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
#define WINDOW_DETECT_DIR                   TRISF
#define WINDOW_DETECT_OUT                   LATF
#define WINDOW_DETECT_IN                    PORTF
#define WINDOW_DETECT_BIT                   BIT7
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V12_)
#define WINDOW_DETECT_DIR                   TRISF
#define WINDOW_DETECT_OUT                   LATF
#define WINDOW_DETECT_IN                    PORTF
#define WINDOW_DETECT_BIT                   BIT7
#endif

#define window_detect_dir_input()           (WINDOW_DETECT_DIR set WINDOW_DETECT_BIT)
#define window_detect_input()               (WINDOW_DETECT_IN & WINDOW_DETECT_BIT)
#endif

////////////////////////////////////////////////////////////////////////////////
/*   for LCD   S E G M E N T S                                                */
////////////////////////////////////////////////////////////////////////////////
#if defined(_LCD_M0754_)
#if defined(_DT03MRF_PCB_PIC_AS8_S_V10_) || defined(_DT03MRF_PCB_PIC_AS8_S_V12_)
#define LCD_ANTEN_MEM                       LCDDATA31
#define LCD_ANTEN_BIT                       BIT5

#define LCD_BATT_MEM                        LCDDATA30
#define LCD_BATT_BIT                        BIT5

//test LCD 2 chan nap chuong trinh
//#define LCD_BATT_MEM                        LCDDATA28//LCDDATA30
//#define LCD_BATT_BIT                        BIT6//BIT5

#define LCD_REVERSE_MEM                     LCDDATA24
#define LCD_REVERSE_BIT                     BIT10

#define LCD_ER_MEM                          LCDDATA31
#define LCD_ER_BIT                          BIT12

#define LCD_ACB_MEM                         LCDDATA28
#define LCD_ACB_BIT                         BIT10

#define LCD_MD_MEM                          LCDDATA31
#define LCD_MD_BIT                          BIT13

#define LCD_COL2_MEM                        LCDDATA28
#define LCD_COL2_BIT                        BIT8

#define LCD_L1_MEM                          LCDDATA16
#define LCD_L1_BIT                          BIT10

#define LCD_L2_MEM                          LCDDATA12
#define LCD_L2_BIT                          BIT10

#define LCD_L3_MEM                          LCDDATA8
#define LCD_L3_BIT                          BIT10

#define LCD_GND_MEM                         LCDDATA4
#define LCD_GND_BIT                         BIT10

#define LCD_MAGNETIC_MEM                    LCDDATA0
#define LCD_MAGNETIC_BIT                    BIT10

#define LCD_UNLOCK_MEM                      LCDDATA29
#define LCD_UNLOCK_BIT                      BIT3

#define LCD_POWERFAIL_MEM                   LCDDATA20
#define LCD_POWERFAIL_BIT                   BIT10

#define LCD_TARIFF_MEM                      LCDDATA31
#define LCD_TARIFF_BIT                      BIT8

#define LCD_Q_REVERSE_MEM                   LCDDATA20
#define LCD_Q_REVERSE_BIT                   BIT12

#define LCD_P_REVERSE_MEM                   LCDDATA24
#define LCD_P_REVERSE_BIT                   BIT12

#define LCD_P_ACTIVE_MEM                    LCDDATA28
#define LCD_P_ACTIVE_BIT                    BIT12

#define LCD_Q_ACTIVE_MEM                    LCDDATA31
#define LCD_Q_ACTIVE_BIT                    BIT7

#define LCD_POINT0_MEM                      LCDDATA30
#define LCD_POINT0_BIT                      BIT14

#define LCD_POINT1_MEM                      LCDDATA30
#define LCD_POINT1_BIT                      BIT7

#define LCD_POINT2_MEM                      LCDDATA30
#define LCD_POINT2_BIT                      BIT6

#define LCD_POINT3_MEM                      LCDDATA28
#define LCD_POINT3_BIT                      BIT9

#define LCD_POINT6_MEM                      LCDDATA31
#define LCD_POINT6_BIT                      BIT11

#define LCD_POINT7_MEM                      LCDDATA31
#define LCD_POINT7_BIT                      BIT10

#define LCD_POINT8_MEM                      LCDDATA31
#define LCD_POINT8_BIT                      BIT9

#define LCD_POINT9_MEM                      LCDDATA31
#define LCD_POINT9_BIT                      BIT1

#define LCD_Z_MEM                           LCDDATA28
#define LCD_Z_BIT                           BIT11

#define LCD_P5_MEM                          LCDDATA24
#define LCD_P5_BIT                          BIT11

#define LCD_S9_MEM                          LCDDATA16
#define LCD_S9_BIT                          BIT12

#define LCD_S10_MEM                         LCDDATA12
#define LCD_S10_BIT                         BIT12

#define LCD_S11_MEM                         LCDDATA8
#define LCD_S11_BIT                         BIT12

#define LCD_V_MEM                           LCDDATA4
#define LCD_V_BIT                           BIT12

#define LCD_S13_MEM                         LCDDATA0
#define LCD_S13_BIT                         BIT12

#define LCD_S14_MEM                         LCDDATA0
#define LCD_S14_BIT                         BIT11

#define LCD_S5_MEM                          LCDDATA4
#define LCD_S5_BIT                          BIT11

#define LCD_R_MEM                           LCDDATA8
#define LCD_R_BIT                           BIT11

#define LCD_S17_MEM                         LCDDATA12
#define LCD_S17_BIT                         BIT11

#define LCD_S16_MEM                         LCDDATA16
#define LCD_S16_BIT                         BIT11

#define LCD_H_MEM                           LCDDATA20
#define LCD_H_BIT                           BIT11

//test LCD 2 chan nap chuong trinh
//#define LCD_V_HIGH_MEM                      LCDDATA28//LCDDATA30
//#define LCD_V_HIGH_BIT                      BIT7//BIT4

#define LCD_V_HIGH_MEM                      LCDDATA30
#define LCD_V_HIGH_BIT                      BIT4

#define LCD_V_LOW_MEM                       LCDDATA31
#define LCD_V_LOW_BIT                       BIT6

#define LCD_A_HIGH_MEM                      LCDDATA29
#define LCD_A_HIGH_BIT                      BIT2

#define LCD_DIGIT1_SEGA_MEM                 LCDDATA2
#define LCD_DIGIT1_SEGB_MEM                 LCDDATA6
#define LCD_DIGIT1_SEGF_MEM                 LCDDATA10
#define LCD_DIGIT1_SEGG_MEM                 LCDDATA14
#define LCD_DIGIT1_SEGE_MEM                 LCDDATA18
#define LCD_DIGIT1_SEGC_MEM                 LCDDATA22
#define LCD_DIGIT1_SEGD_MEM                 LCDDATA26
#define LCD_DIGIT1_BIT                      BIT7                 

#define LCD_DIGIT2_SEGA_MEM                 LCDDATA2
#define LCD_DIGIT2_SEGB_MEM                 LCDDATA6
#define LCD_DIGIT2_SEGF_MEM                 LCDDATA10
#define LCD_DIGIT2_SEGG_MEM                 LCDDATA14
#define LCD_DIGIT2_SEGE_MEM                 LCDDATA18
#define LCD_DIGIT2_SEGC_MEM                 LCDDATA22
#define LCD_DIGIT2_SEGD_MEM                 LCDDATA26
#define LCD_DIGIT2_BIT                      BIT6

#define LCD_DIGIT3_SEGA_MEM                 LCDDATA0
#define LCD_DIGIT3_SEGB_MEM                 LCDDATA4
#define LCD_DIGIT3_SEGF_MEM                 LCDDATA8
#define LCD_DIGIT3_SEGG_MEM                 LCDDATA12
#define LCD_DIGIT3_SEGE_MEM                 LCDDATA16
#define LCD_DIGIT3_SEGC_MEM                 LCDDATA20
#define LCD_DIGIT3_SEGD_MEM                 LCDDATA24
#define LCD_DIGIT3_BIT                      BIT9

#define LCD_DIGIT4_SEGA_MEM                 LCDDATA0
#define LCD_DIGIT4_SEGB_MEM                 LCDDATA4
#define LCD_DIGIT4_SEGF_MEM                 LCDDATA8
#define LCD_DIGIT4_SEGG_MEM                 LCDDATA12
#define LCD_DIGIT4_SEGE_MEM                 LCDDATA16
#define LCD_DIGIT4_SEGC_MEM                 LCDDATA20
#define LCD_DIGIT4_SEGD_MEM                 LCDDATA24
#define LCD_DIGIT4_BIT                      BIT8

#define LCD_DIGIT5_SEGA_MEM                 LCDDATA1
#define LCD_DIGIT5_SEGB_MEM                 LCDDATA5
#define LCD_DIGIT5_SEGF_MEM                 LCDDATA9
#define LCD_DIGIT5_SEGG_MEM                 LCDDATA13
#define LCD_DIGIT5_SEGE_MEM                 LCDDATA17
#define LCD_DIGIT5_SEGC_MEM                 LCDDATA21
#define LCD_DIGIT5_SEGD_MEM                 LCDDATA25
#define LCD_DIGIT5_BIT                      BIT3

#define LCD_DIGIT6_SEGA_MEM                 LCDDATA1
#define LCD_DIGIT6_SEGB_MEM                 LCDDATA5
#define LCD_DIGIT6_SEGF_MEM                 LCDDATA9
#define LCD_DIGIT6_SEGG_MEM                 LCDDATA13
#define LCD_DIGIT6_SEGE_MEM                 LCDDATA17
#define LCD_DIGIT6_SEGC_MEM                 LCDDATA21
#define LCD_DIGIT6_SEGD_MEM                 LCDDATA25
#define LCD_DIGIT6_BIT                      BIT2

#define LCD_DIGIT7_SEGA_MEM                 LCDDATA3
#define LCD_DIGIT7_SEGB_MEM                 LCDDATA7
#define LCD_DIGIT7_SEGF_MEM                 LCDDATA11
#define LCD_DIGIT7_SEGG_MEM                 LCDDATA15
#define LCD_DIGIT7_SEGE_MEM                 LCDDATA19
#define LCD_DIGIT7_SEGC_MEM                 LCDDATA23
#define LCD_DIGIT7_SEGD_MEM                 LCDDATA27
#define LCD_DIGIT7_BIT                      BIT6

#define LCD_DIGIT8_SEGA_MEM                 LCDDATA2
#define LCD_DIGIT8_SEGB_MEM                 LCDDATA6
#define LCD_DIGIT8_SEGF_MEM                 LCDDATA10
#define LCD_DIGIT8_SEGG_MEM                 LCDDATA14
#define LCD_DIGIT8_SEGE_MEM                 LCDDATA18
#define LCD_DIGIT8_SEGC_MEM                 LCDDATA22
#define LCD_DIGIT8_SEGD_MEM                 LCDDATA26
#define LCD_DIGIT8_BIT                      BIT4

#define LCD_DIGIT9_SEGA_MEM                 LCDDATA3
#define LCD_DIGIT9_SEGB_MEM                 LCDDATA7
#define LCD_DIGIT9_SEGF_MEM                 LCDDATA11
#define LCD_DIGIT9_SEGG_MEM                 LCDDATA15
#define LCD_DIGIT9_SEGE_MEM                 LCDDATA19
#define LCD_DIGIT9_SEGC_MEM                 LCDDATA23
#define LCD_DIGIT9_SEGD_MEM                 LCDDATA27
#define LCD_DIGIT9_BIT                      BIT8

#define LCD_DIGIT10_SEGA_MEM                 LCDDATA3
#define LCD_DIGIT10_SEGB_MEM                 LCDDATA7
#define LCD_DIGIT10_SEGF_MEM                 LCDDATA11
#define LCD_DIGIT10_SEGG_MEM                 LCDDATA15
#define LCD_DIGIT10_SEGE_MEM                 LCDDATA19
#define LCD_DIGIT10_SEGC_MEM                 LCDDATA23
#define LCD_DIGIT10_SEGD_MEM                 LCDDATA27
#define LCD_DIGIT10_BIT                      BIT13

#define LCD_DIGIT11_SEGA_MEM                 LCDDATA3
#define LCD_DIGIT11_SEGB_MEM                 LCDDATA7
#define LCD_DIGIT11_SEGF_MEM                 LCDDATA11
#define LCD_DIGIT11_SEGG_MEM                 LCDDATA15
#define LCD_DIGIT11_SEGE_MEM                 LCDDATA19
#define LCD_DIGIT11_SEGC_MEM                 LCDDATA23
#define LCD_DIGIT11_SEGD_MEM                 LCDDATA27
#define LCD_DIGIT11_BIT                      BIT12

#define LCD_DIGIT12_SEGA_MEM                 LCDDATA3
#define LCD_DIGIT12_SEGB_MEM                 LCDDATA7
#define LCD_DIGIT12_SEGF_MEM                 LCDDATA11
#define LCD_DIGIT12_SEGG_MEM                 LCDDATA15
#define LCD_DIGIT12_SEGE_MEM                 LCDDATA19
#define LCD_DIGIT12_SEGC_MEM                 LCDDATA23
#define LCD_DIGIT12_SEGD_MEM                 LCDDATA27
#define LCD_DIGIT12_BIT                      BIT11

#define LCD_DIGIT13_SEGA_MEM                 LCDDATA3
#define LCD_DIGIT13_SEGB_MEM                 LCDDATA7
#define LCD_DIGIT13_SEGF_MEM                 LCDDATA11
#define LCD_DIGIT13_SEGG_MEM                 LCDDATA15
#define LCD_DIGIT13_SEGE_MEM                 LCDDATA19
#define LCD_DIGIT13_SEGC_MEM                 LCDDATA23
#define LCD_DIGIT13_SEGD_MEM                 LCDDATA27
#define LCD_DIGIT13_BIT                      BIT10

#define LCD_DIGIT14_SEGA_MEM                 LCDDATA3
#define LCD_DIGIT14_SEGB_MEM                 LCDDATA7
#define LCD_DIGIT14_SEGF_MEM                 LCDDATA11
#define LCD_DIGIT14_SEGG_MEM                 LCDDATA15
#define LCD_DIGIT14_SEGE_MEM                 LCDDATA19
#define LCD_DIGIT14_SEGC_MEM                 LCDDATA23
#define LCD_DIGIT14_SEGD_MEM                 LCDDATA27
#define LCD_DIGIT14_BIT                      BIT9

#define LCD_DIGIT15_SEGA_MEM                 LCDDATA3
#define LCD_DIGIT15_SEGB_MEM                 LCDDATA7
#define LCD_DIGIT15_SEGF_MEM                 LCDDATA11
#define LCD_DIGIT15_SEGG_MEM                 LCDDATA15
#define LCD_DIGIT15_SEGE_MEM                 LCDDATA19
#define LCD_DIGIT15_SEGC_MEM                 LCDDATA23
#define LCD_DIGIT15_SEGD_MEM                 LCDDATA27
#define LCD_DIGIT15_BIT                      BIT1

#define LCD_DIGIT16_SEGA_MEM                 LCDDATA3
#define LCD_DIGIT16_SEGB_MEM                 LCDDATA7
#define LCD_DIGIT16_SEGF_MEM                 LCDDATA11
#define LCD_DIGIT16_SEGG_MEM                 LCDDATA15
#define LCD_DIGIT16_SEGE_MEM                 LCDDATA19
#define LCD_DIGIT16_SEGC_MEM                 LCDDATA23
#define LCD_DIGIT16_SEGD_MEM                 LCDDATA27
#define LCD_DIGIT16_BIT                      BIT7

#define LCD_DIGIT17_SEGA_MEM                 LCDDATA2
#define LCD_DIGIT17_SEGB_MEM                 LCDDATA6
#define LCD_DIGIT17_SEGF_MEM                 LCDDATA10
#define LCD_DIGIT17_SEGG_MEM                 LCDDATA14
#define LCD_DIGIT17_SEGE_MEM                 LCDDATA18
#define LCD_DIGIT17_SEGC_MEM                 LCDDATA22
#define LCD_DIGIT17_SEGD_MEM                 LCDDATA26
#define LCD_DIGIT17_BIT                      BIT5

#define LCD_DIGIT18_SEGA_MEM                 LCDDATA3
#define LCD_DIGIT18_SEGB_MEM                 LCDDATA7
#define LCD_DIGIT18_SEGF_MEM                 LCDDATA11
#define LCD_DIGIT18_SEGG_MEM                 LCDDATA15
#define LCD_DIGIT18_SEGE_MEM                 LCDDATA19
#define LCD_DIGIT18_SEGC_MEM                 LCDDATA23
#define LCD_DIGIT18_SEGD_MEM                 LCDDATA27
#define LCD_DIGIT18_BIT                      BIT5

#define LCD_DIGIT19_SEGA_MEM                 LCDDATA2
#define LCD_DIGIT19_SEGB_MEM                 LCDDATA6
#define LCD_DIGIT19_SEGF_MEM                 LCDDATA10
#define LCD_DIGIT19_SEGG_MEM                 LCDDATA14
#define LCD_DIGIT19_SEGE_MEM                 LCDDATA18
#define LCD_DIGIT19_SEGC_MEM                 LCDDATA22
#define LCD_DIGIT19_SEGD_MEM                 LCDDATA26
#define LCD_DIGIT19_BIT                      BIT14

#elif defined(_DT03MRF_PCB_PIC_AS8_S_V20_) || defined(_DT03MRF_PCB_PIC_AS8_S_V22_)

#define LCD_ANTEN_MEM                       LCDDATA31
#define LCD_ANTEN_BIT                       BIT5

#define LCD_BATT_MEM                        LCDDATA30
#define LCD_BATT_BIT                        BIT5

//test LCD 2 chan nap chuong trinh
//#define LCD_BATT_MEM                        LCDDATA28//LCDDATA30
//#define LCD_BATT_BIT                        BIT6//BIT5

#define LCD_REVERSE_MEM                     LCDDATA27
#define LCD_REVERSE_BIT                     BIT0

#define LCD_ER_MEM                          LCDDATA30
#define LCD_ER_BIT                          BIT13

#define LCD_ACB_MEM                         LCDDATA31
#define LCD_ACB_BIT                         BIT0

#define LCD_MD_MEM                          LCDDATA30
#define LCD_MD_BIT                          BIT12

#define LCD_COL2_MEM                        LCDDATA28
#define LCD_COL2_BIT                        BIT3

#define LCD_L1_MEM                          LCDDATA19
#define LCD_L1_BIT                          BIT0

#define LCD_L2_MEM                          LCDDATA15
#define LCD_L2_BIT                          BIT0

#define LCD_L3_MEM                          LCDDATA11
#define LCD_L3_BIT                          BIT0

#define LCD_GND_MEM                         LCDDATA7
#define LCD_GND_BIT                         BIT0

#define LCD_MAGNETIC_MEM                    LCDDATA3
#define LCD_MAGNETIC_BIT                    BIT0

#define LCD_UNLOCK_MEM                      LCDDATA28
#define LCD_UNLOCK_BIT                      BIT4

#define LCD_POWERFAIL_MEM                   LCDDATA23
#define LCD_POWERFAIL_BIT                   BIT0

#define LCD_TARIFF_MEM                      LCDDATA30
#define LCD_TARIFF_BIT                      BIT1

#define LCD_Q_REVERSE_MEM                   LCDDATA20
#define LCD_Q_REVERSE_BIT                   BIT0

#define LCD_P_REVERSE_MEM                   LCDDATA24
#define LCD_P_REVERSE_BIT                   BIT0

#define LCD_P_ACTIVE_MEM                    LCDDATA28
#define LCD_P_ACTIVE_BIT                    BIT0

#define LCD_Q_ACTIVE_MEM                    LCDDATA31
#define LCD_Q_ACTIVE_BIT                    BIT4

#define LCD_POINT0_MEM                      LCDDATA29
#define LCD_POINT0_BIT                      BIT11

#define LCD_POINT1_MEM                      LCDDATA30
#define LCD_POINT1_BIT                      BIT2

#define LCD_POINT2_MEM                      LCDDATA30
#define LCD_POINT2_BIT                      BIT3

#define LCD_POINT3_MEM                      LCDDATA28
#define LCD_POINT3_BIT                      BIT2

#define LCD_POINT6_MEM                      LCDDATA29
#define LCD_POINT6_BIT                      BIT7

#define LCD_POINT7_MEM                      LCDDATA29
#define LCD_POINT7_BIT                      BIT8

#define LCD_POINT8_MEM                      LCDDATA29
#define LCD_POINT8_BIT                      BIT9

#define LCD_POINT9_MEM                      LCDDATA29
#define LCD_POINT9_BIT                      BIT10

#define LCD_Z_MEM                           LCDDATA28
#define LCD_Z_BIT                           BIT1

#define LCD_P5_MEM                          LCDDATA24
#define LCD_P5_BIT                          BIT1

#define LCD_S9_MEM                          LCDDATA16
#define LCD_S9_BIT                          BIT0

#define LCD_S10_MEM                         LCDDATA12
#define LCD_S10_BIT                         BIT0

#define LCD_S11_MEM                         LCDDATA8
#define LCD_S11_BIT                         BIT0

#define LCD_V_MEM                           LCDDATA4
#define LCD_V_BIT                           BIT0

#define LCD_S13_MEM                         LCDDATA0
#define LCD_S13_BIT                         BIT0

#define LCD_S14_MEM                         LCDDATA0
#define LCD_S14_BIT                         BIT1

#define LCD_S5_MEM                          LCDDATA4
#define LCD_S5_BIT                          BIT1

#define LCD_R_MEM                           LCDDATA8
#define LCD_R_BIT                           BIT1

#define LCD_S17_MEM                         LCDDATA12
#define LCD_S17_BIT                         BIT1

#define LCD_S16_MEM                         LCDDATA16
#define LCD_S16_BIT                         BIT1

#define LCD_H_MEM                           LCDDATA20
#define LCD_H_BIT                           BIT1

//test LCD 2 chan nap chuong trinh
//#define LCD_V_HIGH_MEM                      LCDDATA28//LCDDATA30
//#define LCD_V_HIGH_BIT                      BIT7//BIT4

#define LCD_V_HIGH_MEM                      LCDDATA30
#define LCD_V_HIGH_BIT                      BIT4

#define LCD_V_LOW_MEM                       LCDDATA31
#define LCD_V_LOW_BIT                       BIT15

#define LCD_A_HIGH_MEM                      LCDDATA28
#define LCD_A_HIGH_BIT                      BIT5

#define LCD_DIGIT1_SEGA_MEM                 LCDDATA2
#define LCD_DIGIT1_SEGB_MEM                 LCDDATA6
#define LCD_DIGIT1_SEGF_MEM                 LCDDATA10
#define LCD_DIGIT1_SEGG_MEM                 LCDDATA14
#define LCD_DIGIT1_SEGE_MEM                 LCDDATA18
#define LCD_DIGIT1_SEGC_MEM                 LCDDATA22
#define LCD_DIGIT1_SEGD_MEM                 LCDDATA26
#define LCD_DIGIT1_BIT                      BIT2                 

#define LCD_DIGIT2_SEGA_MEM                 LCDDATA2
#define LCD_DIGIT2_SEGB_MEM                 LCDDATA6
#define LCD_DIGIT2_SEGF_MEM                 LCDDATA10
#define LCD_DIGIT2_SEGG_MEM                 LCDDATA14
#define LCD_DIGIT2_SEGE_MEM                 LCDDATA18
#define LCD_DIGIT2_SEGC_MEM                 LCDDATA22
#define LCD_DIGIT2_SEGD_MEM                 LCDDATA26
#define LCD_DIGIT2_BIT                      BIT3

#define LCD_DIGIT3_SEGA_MEM                 LCDDATA0
#define LCD_DIGIT3_SEGB_MEM                 LCDDATA4
#define LCD_DIGIT3_SEGF_MEM                 LCDDATA8
#define LCD_DIGIT3_SEGG_MEM                 LCDDATA12
#define LCD_DIGIT3_SEGE_MEM                 LCDDATA16
#define LCD_DIGIT3_SEGC_MEM                 LCDDATA20
#define LCD_DIGIT3_SEGD_MEM                 LCDDATA24
#define LCD_DIGIT3_BIT                      BIT2

#define LCD_DIGIT4_SEGA_MEM                 LCDDATA0
#define LCD_DIGIT4_SEGB_MEM                 LCDDATA4
#define LCD_DIGIT4_SEGF_MEM                 LCDDATA8
#define LCD_DIGIT4_SEGG_MEM                 LCDDATA12
#define LCD_DIGIT4_SEGE_MEM                 LCDDATA16
#define LCD_DIGIT4_SEGC_MEM                 LCDDATA20
#define LCD_DIGIT4_SEGD_MEM                 LCDDATA24
#define LCD_DIGIT4_BIT                      BIT3

#define LCD_DIGIT5_SEGA_MEM                 LCDDATA0
#define LCD_DIGIT5_SEGB_MEM                 LCDDATA4
#define LCD_DIGIT5_SEGF_MEM                 LCDDATA8
#define LCD_DIGIT5_SEGG_MEM                 LCDDATA12
#define LCD_DIGIT5_SEGE_MEM                 LCDDATA16
#define LCD_DIGIT5_SEGC_MEM                 LCDDATA20
#define LCD_DIGIT5_SEGD_MEM                 LCDDATA24
#define LCD_DIGIT5_BIT                      BIT4

#define LCD_DIGIT6_SEGA_MEM                 LCDDATA0
#define LCD_DIGIT6_SEGB_MEM                 LCDDATA4
#define LCD_DIGIT6_SEGF_MEM                 LCDDATA8
#define LCD_DIGIT6_SEGG_MEM                 LCDDATA12
#define LCD_DIGIT6_SEGE_MEM                 LCDDATA16
#define LCD_DIGIT6_SEGC_MEM                 LCDDATA20
#define LCD_DIGIT6_SEGD_MEM                 LCDDATA24
#define LCD_DIGIT6_BIT                      BIT5

#define LCD_DIGIT7_SEGA_MEM                 LCDDATA3
#define LCD_DIGIT7_SEGB_MEM                 LCDDATA7
#define LCD_DIGIT7_SEGF_MEM                 LCDDATA11
#define LCD_DIGIT7_SEGG_MEM                 LCDDATA15
#define LCD_DIGIT7_SEGE_MEM                 LCDDATA19
#define LCD_DIGIT7_SEGC_MEM                 LCDDATA23
#define LCD_DIGIT7_SEGD_MEM                 LCDDATA27
#define LCD_DIGIT7_BIT                      BIT15

#define LCD_DIGIT8_SEGA_MEM                 LCDDATA2
#define LCD_DIGIT8_SEGB_MEM                 LCDDATA6
#define LCD_DIGIT8_SEGF_MEM                 LCDDATA10
#define LCD_DIGIT8_SEGG_MEM                 LCDDATA14
#define LCD_DIGIT8_SEGE_MEM                 LCDDATA18
#define LCD_DIGIT8_SEGC_MEM                 LCDDATA22
#define LCD_DIGIT8_SEGD_MEM                 LCDDATA26
#define LCD_DIGIT8_BIT                      BIT4

#define LCD_DIGIT9_SEGA_MEM                 LCDDATA2
#define LCD_DIGIT9_SEGB_MEM                 LCDDATA6
#define LCD_DIGIT9_SEGF_MEM                 LCDDATA10
#define LCD_DIGIT9_SEGG_MEM                 LCDDATA14
#define LCD_DIGIT9_SEGE_MEM                 LCDDATA18
#define LCD_DIGIT9_SEGC_MEM                 LCDDATA22
#define LCD_DIGIT9_SEGD_MEM                 LCDDATA26
#define LCD_DIGIT9_BIT                      BIT1

#define LCD_DIGIT10_SEGA_MEM                 LCDDATA2
#define LCD_DIGIT10_SEGB_MEM                 LCDDATA6
#define LCD_DIGIT10_SEGF_MEM                 LCDDATA10
#define LCD_DIGIT10_SEGG_MEM                 LCDDATA14
#define LCD_DIGIT10_SEGE_MEM                 LCDDATA18
#define LCD_DIGIT10_SEGC_MEM                 LCDDATA22
#define LCD_DIGIT10_SEGD_MEM                 LCDDATA26
#define LCD_DIGIT10_BIT                      BIT12

#define LCD_DIGIT11_SEGA_MEM                 LCDDATA2
#define LCD_DIGIT11_SEGB_MEM                 LCDDATA6
#define LCD_DIGIT11_SEGF_MEM                 LCDDATA10
#define LCD_DIGIT11_SEGG_MEM                 LCDDATA14
#define LCD_DIGIT11_SEGE_MEM                 LCDDATA18
#define LCD_DIGIT11_SEGC_MEM                 LCDDATA22
#define LCD_DIGIT11_SEGD_MEM                 LCDDATA26
#define LCD_DIGIT11_BIT                      BIT13

#define LCD_DIGIT12_SEGA_MEM                 LCDDATA1
#define LCD_DIGIT12_SEGB_MEM                 LCDDATA5
#define LCD_DIGIT12_SEGF_MEM                 LCDDATA9
#define LCD_DIGIT12_SEGG_MEM                 LCDDATA13
#define LCD_DIGIT12_SEGE_MEM                 LCDDATA17
#define LCD_DIGIT12_SEGC_MEM                 LCDDATA21
#define LCD_DIGIT12_SEGD_MEM                 LCDDATA25
#define LCD_DIGIT12_BIT                      BIT7

#define LCD_DIGIT13_SEGA_MEM                 LCDDATA1
#define LCD_DIGIT13_SEGB_MEM                 LCDDATA5
#define LCD_DIGIT13_SEGF_MEM                 LCDDATA9
#define LCD_DIGIT13_SEGG_MEM                 LCDDATA13
#define LCD_DIGIT13_SEGE_MEM                 LCDDATA17
#define LCD_DIGIT13_SEGC_MEM                 LCDDATA21
#define LCD_DIGIT13_SEGD_MEM                 LCDDATA25
#define LCD_DIGIT13_BIT                      BIT8

#define LCD_DIGIT14_SEGA_MEM                 LCDDATA1
#define LCD_DIGIT14_SEGB_MEM                 LCDDATA5
#define LCD_DIGIT14_SEGF_MEM                 LCDDATA9
#define LCD_DIGIT14_SEGG_MEM                 LCDDATA13
#define LCD_DIGIT14_SEGE_MEM                 LCDDATA17
#define LCD_DIGIT14_SEGC_MEM                 LCDDATA21
#define LCD_DIGIT14_SEGD_MEM                 LCDDATA25
#define LCD_DIGIT14_BIT                      BIT9

#define LCD_DIGIT15_SEGA_MEM                 LCDDATA1
#define LCD_DIGIT15_SEGB_MEM                 LCDDATA5
#define LCD_DIGIT15_SEGF_MEM                 LCDDATA9
#define LCD_DIGIT15_SEGG_MEM                 LCDDATA13
#define LCD_DIGIT15_SEGE_MEM                 LCDDATA17
#define LCD_DIGIT15_SEGC_MEM                 LCDDATA21
#define LCD_DIGIT15_SEGD_MEM                 LCDDATA25
#define LCD_DIGIT15_BIT                      BIT10

#define LCD_DIGIT16_SEGA_MEM                 LCDDATA3
#define LCD_DIGIT16_SEGB_MEM                 LCDDATA7
#define LCD_DIGIT16_SEGF_MEM                 LCDDATA11
#define LCD_DIGIT16_SEGG_MEM                 LCDDATA15
#define LCD_DIGIT16_SEGE_MEM                 LCDDATA19
#define LCD_DIGIT16_SEGC_MEM                 LCDDATA23
#define LCD_DIGIT16_SEGD_MEM                 LCDDATA27
#define LCD_DIGIT16_BIT                      BIT4

#define LCD_DIGIT17_SEGA_MEM                 LCDDATA2
#define LCD_DIGIT17_SEGB_MEM                 LCDDATA6
#define LCD_DIGIT17_SEGF_MEM                 LCDDATA10
#define LCD_DIGIT17_SEGG_MEM                 LCDDATA14
#define LCD_DIGIT17_SEGE_MEM                 LCDDATA18
#define LCD_DIGIT17_SEGC_MEM                 LCDDATA22
#define LCD_DIGIT17_SEGD_MEM                 LCDDATA26
#define LCD_DIGIT17_BIT                      BIT5

#define LCD_DIGIT18_SEGA_MEM                 LCDDATA3
#define LCD_DIGIT18_SEGB_MEM                 LCDDATA7
#define LCD_DIGIT18_SEGF_MEM                 LCDDATA11
#define LCD_DIGIT18_SEGG_MEM                 LCDDATA15
#define LCD_DIGIT18_SEGE_MEM                 LCDDATA19
#define LCD_DIGIT18_SEGC_MEM                 LCDDATA23
#define LCD_DIGIT18_SEGD_MEM                 LCDDATA27
#define LCD_DIGIT18_BIT                      BIT5

#define LCD_DIGIT19_SEGA_MEM                 LCDDATA1
#define LCD_DIGIT19_SEGB_MEM                 LCDDATA5
#define LCD_DIGIT19_SEGF_MEM                 LCDDATA9
#define LCD_DIGIT19_SEGG_MEM                 LCDDATA13
#define LCD_DIGIT19_SEGE_MEM                 LCDDATA17
#define LCD_DIGIT19_SEGC_MEM                 LCDDATA21
#define LCD_DIGIT19_SEGD_MEM                 LCDDATA25
#define LCD_DIGIT19_BIT                      BIT11
#endif

#endif //_LCD_M0754_

////////////////////////////////////////////////////////////////////////////////
/*   for LCD   M A T R I X                                                    */
////////////////////////////////////////////////////////////////////////////////
#if defined(_LCD_1602_)
#define LCD_PINS_CTRL_DIR                   TRISD
#define LCD_PINS_CTRL_OUT                   LATD

#define LCD_PINS_DATA_DIR                   TRISA //dinh nghia lai
#define LCD_PINS_DATA_OUT                   LATA
#define LCD_PINS_DATA_IN                    PORTA

#define LCD_RS_PIN                          BIT4
#define LCD_RW_PIN                          BIT5
#define LCD_ENABLE_PIN                      BIT6
#define LCD_PINS_CTRL                       (0x70)//RD4 -> RD6//(0xE0) //P3.5 -> P3.7
//#define LCD_PINS_DATA                       (0xF0) //P4.4 -> P4.7

//LCD back light
#define lcd_controls_dir_output()           (LCD_PINS_CTRL_DIR clr LCD_PINS_CTRL)
#define lcd_controls_output_high()          (LCD_PINS_CTRL_OUT set LCD_PINS_CTRL)
#define lcd_controls_output_low()           (LCD_PINS_CTRL_OUT clr LCD_PINS_CTRL)

#define lcd_rs_output_high()                (LCD_PINS_CTRL_OUT set LCD_RS_PIN)
#define lcd_rs_output_low()                 (LCD_PINS_CTRL_OUT clr LCD_RS_PIN)
#define lcd_wr_output_high()                (LCD_PINS_CTRL_OUT set LCD_RW_PIN)
#define lcd_wr_output_low()                 (LCD_PINS_CTRL_OUT clr LCD_RW_PIN)
#define lcd_enable_output_high()            (LCD_PINS_CTRL_OUT set LCD_ENABLE_PIN)
#define lcd_enable_output_low()             (LCD_PINS_CTRL_OUT clr LCD_ENABLE_PIN)

//#define lcd_datas_dir_output()              (LCD_PINS_DATA_DIR clr 0xFF)
//#define lcd_datas_dir_input()               (LCD_PINS_DATA_DIR clr 0xFF)
//
//#define lcd_datas_output(x)                 (LCD_PINS_DATA_OUT = x)
//#define lcd_datas_input()                   (LCD_PINS_DATA_IN)

#define LCD16x2_D0_DIR                      TRISD
#define LCD16x2_D0_OUT                      LATD
#define LCD16x2_D0_BIT                      BIT7
#define lcd16x2_d0_output()                 LATDbits.LATD7
#define lcd16x2_d0_input()                  PORTDbits.RD7
#define lcd16x2_d0_dir_output()             (LCD16x2_D0_DIR clr LCD16x2_D0_BIT)
#define lcd16x2_d0_dir_input()              (LCD16x2_D0_DIR set LCD16x2_D0_BIT)
#define lcd16x2_d0_output_high()            (LCD16x2_D0_OUT set LCD16x2_D0_BIT)
#define lcd16x2_d0_output_low()             (LCD16x2_D0_OUT clr LCD16x2_D0_BIT)

#define LCD16x2_D1_DIR                      TRISF
#define LCD16x2_D1_OUT                      LATF
#define LCD16x2_D1_BIT                      BIT0
#define lcd16x2_d1_output()                 LATFbits.LATF0
#define lcd16x2_d1_input()                  PORTFbits.RF0
#define lcd16x2_d1_dir_output()             (LCD16x2_D1_DIR clr LCD16x2_D1_BIT)
#define lcd16x2_d1_dir_input()              (LCD16x2_D1_DIR set LCD16x2_D1_BIT)
#define lcd16x2_d1_output_high()            (LCD16x2_D1_OUT set LCD16x2_D1_BIT)
#define lcd16x2_d1_output_low()             (LCD16x2_D1_OUT clr LCD16x2_D1_BIT)

#define LCD16x2_D2_DIR                      TRISF
#define LCD16x2_D2_OUT                      LATF
#define LCD16x2_D2_BIT                      BIT1
#define lcd16x2_d2_output()                 LATFbits.LATF1
#define lcd16x2_d2_input()                  PORTFbits.RF1
#define lcd16x2_d2_dir_output()             (LCD16x2_D2_DIR clr LCD16x2_D2_BIT)
#define lcd16x2_d2_dir_input()              (LCD16x2_D2_DIR set LCD16x2_D2_BIT)
#define lcd16x2_d2_output_high()            (LCD16x2_D2_OUT set LCD16x2_D2_BIT)
#define lcd16x2_d2_output_low()             (LCD16x2_D2_OUT clr LCD16x2_D2_BIT)

#define LCD16x2_D3_DIR                      TRISG
#define LCD16x2_D3_OUT                      LATG
#define LCD16x2_D3_BIT                      BIT1
#define lcd16x2_d3_output()                 LATGbits.LATG1
#define lcd16x2_d3_input()                  PORTGbits.RG1
#define lcd16x2_d3_dir_output()             (LCD16x2_D3_DIR clr LCD16x2_D3_BIT)
#define lcd16x2_d3_dir_input()              (LCD16x2_D3_DIR set LCD16x2_D3_BIT)
#define lcd16x2_d3_output_high()            (LCD16x2_D3_OUT set LCD16x2_D3_BIT)
#define lcd16x2_d3_output_low()             (LCD16x2_D3_OUT clr LCD16x2_D3_BIT)

#define LCD16x2_D4_DIR                      TRISG
#define LCD16x2_D4_OUT                      LATG
#define LCD16x2_D4_BIT                      BIT0
#define lcd16x2_d4_output()                 LATGbits.LATG0
#define lcd16x2_d4_input()                  PORTGbits.RG0
#define lcd16x2_d4_dir_output()             (LCD16x2_D4_DIR clr LCD16x2_D4_BIT)
#define lcd16x2_d4_dir_input()              (LCD16x2_D4_DIR set LCD16x2_D4_BIT)
#define lcd16x2_d4_output_high()            (LCD16x2_D4_OUT set LCD16x2_D4_BIT)
#define lcd16x2_d4_output_low()             (LCD16x2_D4_OUT clr LCD16x2_D4_BIT)

#define LCD16x2_D5_DIR                      TRISA
#define LCD16x2_D5_OUT                      LATA
#define LCD16x2_D5_BIT                      BIT6
#define lcd16x2_d5_output()                 LATAbits.LATA6
#define lcd16x2_d5_input()                  PORTAbits.RA6
#define lcd16x2_d5_dir_output()             (LCD16x2_D5_DIR clr LCD16x2_D5_BIT)
#define lcd16x2_d5_dir_input()              (LCD16x2_D5_DIR set LCD16x2_D5_BIT)
#define lcd16x2_d5_output_high()            (LCD16x2_D5_OUT set LCD16x2_D5_BIT)
#define lcd16x2_d5_output_low()             (LCD16x2_D5_OUT clr LCD16x2_D5_BIT)

#define LCD16x2_D6_DIR                      TRISA
#define LCD16x2_D6_OUT                      LATA
#define LCD16x2_D6_BIT                      BIT7
#define lcd16x2_d6_output()                 LATAbits.LATA7
#define lcd16x2_d6_input()                  PORTAbits.RA7
#define lcd16x2_d6_dir_output()             (LCD16x2_D6_DIR clr LCD16x2_D6_BIT)
#define lcd16x2_d6_dir_input()              (LCD16x2_D6_DIR set LCD16x2_D6_BIT)
#define lcd16x2_d6_output_high()            (LCD16x2_D6_OUT set LCD16x2_D6_BIT)
#define lcd16x2_d6_output_low()             (LCD16x2_D6_OUT clr LCD16x2_D6_BIT)

#define LCD16x2_D7_DIR                      TRISE
#define LCD16x2_D7_OUT                      LATE
#define LCD16x2_D7_BIT                      BIT0
#define lcd16x2_d7_output()                 LATEbits.LATE0
#define lcd16x2_d7_input()                  PORTEbits.RE0
#define lcd16x2_d7_dir_output()             (LCD16x2_D7_DIR clr LCD16x2_D7_BIT)
#define lcd16x2_d7_dir_input()              (LCD16x2_D7_DIR set LCD16x2_D7_BIT)
#define lcd16x2_d7_output_high()            (LCD16x2_D7_OUT set LCD16x2_D7_BIT)
#define lcd16x2_d7_output_low()             (LCD16x2_D7_OUT clr LCD16x2_D7_BIT)

extern void lcd_datas_dir_output();
extern void lcd_datas_dir_input();
extern void lcd_datas_output(uint8_t data);
extern uint8_t lcd_datas_input();
#endif


void eeprom_init(void);

extern void hardware_init(void);
extern void interrupt_enable(void);
extern void interrupt_disable(void);
extern void test_hardware(void);
extern void on_change_interrupt_init(void);
extern void test_eeprom(void);
extern void test_rtc(void);

#if defined(_LCD_M0754_)
extern void lcd_init(void);
#endif

//just for test
//extern void lcd_L1(char status);
//extern void lcd_L2(char status);
//extern void lcd_L3(char status);
//extern void display_calib_mode(char status);
//extern void display_item_reverse(char status);
//extern void display_item_phase(int ph, char status);
////extern void lcd_ACB(char status);
//extern void display_item_V_high(char status);
//extern void display_item_V_low(char status);
//extern void display_item_A_high(char status);
//extern void display_item_powerfail(char status);
//extern void display_item(int item);
//extern void display_item_battery(char status);



extern void system_setup(void);
//extern uint8_t config_baudrate(int uart, int value);
extern void uart_pc_send_byte(uint8_t data);
extern void uart_optical_send_byte(uint8_t data);
#ifdef COMMUNICATION_RFSLOT_SUPPORT
extern void uart_rfslot_send_byte(uint8_t data);
#endif
#ifdef COMMUNICATION_GSMSLOT_SUPPORT
extern void uart_gsmslot_send_byte(uint8_t data);
#endif
extern void meterpc_read_timer();
extern void rtc_timer();
extern void system_refresh_timer();
extern void led_status_timer_task();
extern void uart_wakeup_timer_task();


#endif