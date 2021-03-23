/*===========================================================================*/
/*
SOURCE_FILE:		hardware.c                                  
APPLICATION:		ROUTER 
MODULE:				FW
ORIGINAL AUTHOR:	thaodtn 
VERSION:			1.0     
DATE:				6/5/2016 
*/
/*===========================================================================*/
/* I N C L U D E S                                                           */
/*===========================================================================*/
#include <xc.h>
#include <stdio.h>
#include <string.h>
#include "devices.h"
#include "hardware.h"

#include "spi.h"
#include "aa1024.h"
#include "sst25vf016.h"
#include "ade7858.h"
#include "rtc.h"
#include "pcf2129.h"
#include "timers.h"
#include "spi.h"
#include "uart.h"
#include "delay.h"

#ifdef RF_SUPPORT
#include "rf.h"
#endif

#ifdef DISPLAY_SUPPORT
#if defined(_LCD_OST11295_) || defined(_LCD_L0712_)
#include "lcd-segment-ost11295.h"
#elif defined(_LCD_OST11248_)
#include "lcd-segment-ost11248.h"
#elif defined(_LCD_M0754v2_PCF8545_)
#include "lcd-segment-pcf8545-m0754v2.h"
#elif defined(_LCD_M0754v3_PCF8545_)
#include "lcd-segment-pcf8545-m0754v3.h"
#elif defined(_LCD_1602_)
#include "lcd16x2.h"
#elif defined(_LCD_M0754_)
#include "lcd-segment-m0754.h"
#elif defined(_LCD_OST11088S05_)
#include "lcd_segment-OST11088S05.h"
#endif

#include "emeter-display.h"
#endif

void hardware_init(void)
{
#if defined(_DT03MRF_PCB_PIC_AS8_S_V20_)
    //cau hinh cac IO ko su dung
    ANSA = 0;
    ANSB = 0;
    ANSC = 0;
    ANSD = 0;
    ANSE = 0;
    ANSF = 0;
    ANSG = 0;  
    
    TRISA = 0xFFFF;
    TRISB = 0xFFFF;
    TRISC = 0xFFFF;
    TRISD = 0xFFFF;
    TRISE = 0xFFFF;
    TRISF = 0xFFFF;
    TRISG = 0xFFFF; 
    
    LATA = 0xFFFF;
    LATB = 0xFFFF;
    LATC = 0xFFFF;
    LATD = 0xFFFF;
    LATE = 0xFFFF;
    LATF = 0xFFFF;
    LATG = 0xFFFF;
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
    //cau hinh cac IO ko su dung
    ANSA = 0; ANSB = 0; ANSC = 0; ANSD = 0;
    ANSE = 0; ANSF = 0; ANSG = 0;  
    ///////////////////////////////////////
//    TRISA = 0b0111111100000111;//0b0111100100000110;
//    TRISB = 0b0000111111111100;//0b0000100001000000;
//    TRISC = 0b1111111111111111;//0b1111111111100111;
//    TRISD = 0b0111100111110110;//0b0100100100000110;
//    TRISE = 0b1111111111001111;//0b1111110011000000;
//    TRISF = 0b1111111111111111;//0b1100111111111100;
//    TRISG = 0b0100110011111100;//0b0100110010111100;
    TRISA = 0xFFFF;
    TRISB = 0xFFFF;
    TRISC = 0xFFFF;
    TRISD = 0xFFFF;
    TRISE = 0xFFFF;
    TRISF = 0xFFFF;
    TRISG = 0xFFFF; 
    ///////////////////////////////////////
    LATA = 0x0000;//0xFFFF;
    LATB = 0x0000;//0xFFFF;
    LATC = 0x0000;//0xFFFF;
    LATD = 0x0000;//0xFFFF;
    LATE = 0x0000;//0xFFFF;
    LATF = 0x0000;//0xFFFF;
    LATG = 0x0000;//0xFFFF;
#endif
  
#ifdef LCD_BACKLIT_SUPPORT
    lcd_backlit_end();
    lcd_backlit_dir_output();
#endif
    
#ifdef ADNOMAL_LED_SUPPORT
    adnormal_led_dir_output();
    adnormal_led_end();
#endif
    
    power_fail_detect_dir_input();
    power_fail_detect_interrupt_flag_clear();
    power_fail_detect_interrupt_enable();
    power_fail_detect_interrupt_high_to_low();
#if defined(_DT03MRF_PCB_PIC_AS8_S_V20_) || defined(_DT03MRF_PCB_PIC_AS8_S_V22_) //INT4
    power_fail_detect_interrupt_select();
#endif
    
    calib_enable_dir_input();
    batt_monitor_dir_input();
    
    button_up_dir_input();
    button_up_interrupt_high_to_low();
    button_up_interrupt_enable();
    
    button_down_dir_input();
    //button_down_interrupt_high_to_low();
    button_down_interrupt_enable();
    
    magnetic_detect_dir_input();
    
    mcu_watchdog_dir_output();
    mcu_watchdog_end();
    
    eeprom_init();
    
#ifdef RS422_RS485_CONTROL_SUPPORT
    rs422_control_dir_output();
    rs422_control_enable();
#endif
    
#ifdef RS422_RS485_POWER_SUPPORT
    rs422_power_dir_output();
    rs422_power_enable();
#endif
    
#ifdef COVER_DETECT_SUPPORT
    cover_detect_dir_input();
#endif
    
#ifdef TERMINAL_DETECT_SUPPORT
    terminal_detect_dir_input();
#endif
    
#ifdef WINDOW_DETECT_SUPPORT
    window_detect_dir_input();
#endif
}

void system_setup(void)
{
    hardware_init();     
    spi_init();
    uart_init();
    timer_init(); 
#ifdef RF_SUPPORT
    rf_init();
#endif    
#ifdef DISPLAY_SUPPORT
#if defined(_LCD_M0754_)
    lcd_init();
#elif defined(_LCD_1602_)
    LCD_init();
    delay_ms(10);
    LCD_init();
#endif    
#endif
}

void on_change_interrupt_init(void)
{
    on_change_interrupt_active();
    on_change_interrupt_enable();
    on_change_interrupt_flag_clear();
    on_change_interrupt_priority();
}

void interrupt_enable(void)
{
    ei();
}

void interrupt_disable(void)
{
    di();
}


//==============================================================================
// UART FUNCTIONS
//==============================================================================

void uart_optical_send_byte(uint8_t data)
{
    while (U1STAbits.UTXBF == 1);
    while (U1STAbits.TRMT == 0);
    U1TXREG = data;
    while (U1STAbits.UTXBF == 1);
    while (U1STAbits.TRMT == 0);
}

void uart_pc_send_byte(uint8_t data)
{
    while (U2STAbits.UTXBF == 1);
    while (U2STAbits.TRMT == 0);
    U2TXREG = data;
    while (U2STAbits.UTXBF == 1);
    while (U2STAbits.TRMT == 0);
}
#ifdef COMMUNICATION_GSMSLOT_SUPPORT
void uart_gsmslot_send_byte(uint8_t data)
{
    while (U3STAbits.UTXBF == 1);
    while (U3STAbits.TRMT == 0);
    U3TXREG = data; 
    while (U3STAbits.UTXBF == 1);
    while (U3STAbits.TRMT == 0);
}
#endif
#ifdef COMMUNICATION_RFSLOT_SUPPORT
void uart_rfslot_send_byte(uint8_t data)
{
    while (U4STAbits.UTXBF == 1);
    while (U4STAbits.TRMT == 0);
    U4TXREG = data; 
    while (U4STAbits.UTXBF == 1);
    while (U4STAbits.TRMT == 0);
}
#endif
void hardware_uart_transmit_byte(uint8_t data, uint8_t module)
{
    switch (module) 
    {
        case 1:
            uart_pc_send_byte(data);      
            break;
        case 2:
            uart_optical_send_byte(data);           
            break;        
        default:
            break;
    }   
}

//uint8_t config_baudrate(int uart, int value)
//{
//    //uart = 0: optical; uart = 1: pc
//    switch (value)
//    {
//        case BAUD_300: 
//            if (uart == UART_PC) U1BRG = 1535;
//            if (uart == UART_OPTICAL) U2BRG = 1535;             
//            break;
//        case BAUD_600:            
//            if (uart == UART_PC) U1BRG = 767;
//            if (uart == UART_OPTICAL) U2BRG = 767;   
//            break;
//        case BAUD_1200:
//            if (uart == UART_PC) U1BRG = 383;
//            if (uart == UART_OPTICAL) U2BRG = 383;
//            break;
//        case BAUD_2400:
//            if (uart == UART_PC) U1BRG = 191;
//            if (uart == UART_OPTICAL) U2BRG = 191;
//            break;
//        case BAUD_4800:
//            if (uart == UART_PC) U1BRG = 95;
//            if (uart == UART_OPTICAL) U2BRG = 95;
//            break;
//        case BAUD_9600:
//            if (uart == UART_PC) U1BRG = 47;
//            if (uart == UART_OPTICAL) U2BRG = 47;
//            break;
//        case BAUD_19200:
//            if (uart == UART_PC) U1BRG = 23;
//            if (uart == UART_OPTICAL) U2BRG = 23;
//            break;
//        default:
//            return FALSE;
//    }
//    return TRUE;
//}

#if defined(_LCD_M0754_)
void lcd_init(void)
{
#if defined(_DT03MRF_PCB_PIC_AS8_S_V10_) || defined(_DT03MRF_PCB_PIC_AS8_S_V12_)
    LCDSE0 = BIT8 + BIT9 + BIT10 + BIT11 + BIT12;//0b0000000100111110;
    LCDSE1 = BIT2 + BIT3;//0b0000011111001100;
    LCDSE2 = BIT4 + BIT5 + BIT6 + BIT7 + BIT14;//0b0011000000111100;
    LCDSE3 = BIT1 + BIT5 + BIT6 + BIT7 + BIT8 + BIT9 + BIT10 + BIT11 + BIT12 + BIT13;//0b0000000001100001;
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V20_)
    LCDSE0 = BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5;
    LCDSE1 = BIT7 + BIT8 + BIT9 + BIT10 + BIT11;
    LCDSE2 = BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT12 + BIT13;
    LCDSE3 = BIT0 + BIT4 + BIT5 + BIT15;
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
//      
    // LCD00 : LCDSE3:SEG53:BIT5
    // LCD01 : LCDSE2:SEG37:BIT5 
    // LCD02 : LCDSE2:SEG36:BIT4
    // LCD03 : LCDSE3:SEG63:BIT15
    // LCD04 : LCDSE0:SEG5:BIT5
    // LCD05 : LCDSE0:SEG4:BIT4 
    // LCD06 : LCDSE0:SEG3:BIT3
    // LCD07 : LCDSE0:SEG2:BIT2 
    // LCD08 : LCDSE2:SEG35:BIT3
    // LCD09 : LCDSE2:SEG34:BIT2
    // LCD10 : LCDSE3:SEG48:BIT0
    // LCD11 : LCDSE0:SEG1:BIT1
    // LCD12 : LCDSE0:SEG0:BIT0  
    // LCD13 : LCDSE3:SEG52:BIT4
    // LCD14 : LCDSE2:SEG33:BIT1
    // LCD15 : LCDSE2:SEG44:BIT12
    // LCD16 : LCDSE2:SEG45:BIT13
    // LCD17 : LCDSE1:SEG23:BIT7
    // LCD18 : LCDSE1:SEG24:BIT8
    // LCD19 : LCDSE1:SEG25:BIT9
    // LCD20 : LCDSE1:SEG26:BIT10
    // LCD21 : LCDSE1:SEG27:BIT11      
    LCDSE0 = BIT0 + BIT1 + BIT2 + BIT3 + BIT4 + BIT5; 
    LCDSE1 = BIT7 + BIT8 + BIT9 + BIT10 + BIT11; 
    LCDSE2 = BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT12 + BIT13;
    LCDSE3 = BIT0 + BIT4 + BIT5 + BIT15; 
#endif
    LCDCONbits.LCDEN = 1; // enable LCD
    LCDCONbits.LCDSIDL = 0; //LCD driver continues to operate in CPU Idle mode
    //LCDCONbits.SLPEN = 1; // LCD driver is disable in sleep mode
    LCDCONbits.SLPEN = 0; // LCD driver is enable in sleep mode
    LCDCONbits.CS = 0; //FRC
//    LCDCONbits.CS = 0b01; // select LPRC
    LCDCONbits.LMUX = 0b111; // mode 8 com
    LCDREGbits.CPEN = 0;//1; //charge bump disable
    //LCDREGbits.CLKSEL = 0b10;
    LCDPSbits.LCDA = 1; // LCD driver module is active
    //LCDPSbits.WA = 1;
    LCDPSbits.LP = 0b0001;  // LCD Prescaler Select bits : 1/2
    LCDREFbits.LCDIRE = 1;  //  LCD Internal Reference Enable bit
    LCDREFbits.LRLAP = 0b11;
    LCDREFbits.LRLBP = 0b11;  
}

void lcd_disable(void)
{
    LCDSE0 = 0;
    LCDSE1 = 0;
    LCDSE2 = 0;
    LCDSE3 = 0;
    LCDCONbits.LCDEN = 0; // enable LCD    
}
#endif

void lcd_set_mode(char mode)
{
    switch (mode)
    {
        case 0:
            break;
        case 1:
            break;
    }
}

void test_hardware(void)
{
    if (calib_enable_input() != 0)
        lcd_backlit_toggle();
    if (magnetic_detect_input() == 0)
        total_active_energy_pulse_start();
    //total_active_energy_pulse_toggle();
    //total_reactive_energy_pulse_toggle();
}

//void eeprom_init(void)
//{
//#if defined(_DT03M_RF_) || defined(_DT01M_RF_) || defined(_PREPAID_METER_) || defined(_ROUTER_)
//    eeprom_wr_en_high();    
//    eeprom_wr_en_dir_output();
//    eeprom_cs1_high();
//    eeprom_cs2_high();
//    eeprom_cs3_high();
//    eeprom_cs1_dir_output();
//    eeprom_cs2_dir_output();
//    eeprom_cs3_dir_output();
//    eeprom_hold_high();    
//    eeprom_hold_dir_output();
//#elif defined(_DT03P_RF_)
//    //cap nguon cho eeprom
//    eeprom_power_dir_output();
//    eeprom_power_high();
//    eeprom_wr_en_dir_output();
//    eeprom_wr_en_high();
//    eeprom_cs1_dir_output();
//    eeprom_cs2_dir_output();
//    #ifdef POWER_EEPROM_SUPPORT
//    eeprom_power_dir_output();
//    eeprom_power_high();
//    #endif
//#else
//#warning "check meter type in eeprom.c"
//#endif
//#ifdef FLASH_SUPPORT
//    sst25_init();
//#endif
//}

void test_eeprom(void)
{
    int i = 0;
    int data = 0;
    #if defined(SST25VF016B_SUPPORT)
    sst25_unblock_write_protection(FLASH_1);
    sst25_unblock_write_protection(FLASH_2);
    #endif
    for (i = 1; i < 100; i++)
    {
        aa1024_write_byte(0, i, EEPROM_1);
        data = aa1024_read_byte(0, EEPROM_1);
        aa1024_write_2byte(100, i + 0xFF00, EEPROM_2);
        data = aa1024_read_2byte(100, EEPROM_2);
        #if defined(SST25VF016B_SUPPORT)
        sst25_sector_erase(0, FLASH_1);
        sst25_write_byte(0, i + 1, FLASH_1);
        data = sst25_read_byte(0, FLASH_1);
        
        sst25_sector_erase(0, FLASH_2);
        sst25_write_byte(0, i + 2, FLASH_2);
        data = sst25_read_byte(0, FLASH_2);
        #endif
    }
    #if defined(SST25VF016B_SUPPORT)
    sst25_block_write_protection(FLASH_1);
    sst25_block_write_protection(FLASH_2);
    #endif
}

void test_rtc(void)
{
// quanhdt 20/10/2019    unsigned char second, minute, hour, day, weekday, month, year;
    rtc_set_time(18, 30, 0);
    rtc_set_date(1, 7, 3, 16);
    rtc_read_time();  
    rtc_read_time();
}

#if defined(_LCD_1602_)
void lcd_datas_dir_output()
{
    lcd16x2_d0_dir_output();
    lcd16x2_d1_dir_output();
    lcd16x2_d2_dir_output();
    lcd16x2_d3_dir_output();
    lcd16x2_d4_dir_output();
    lcd16x2_d5_dir_output();
    lcd16x2_d6_dir_output();
    lcd16x2_d7_dir_output();
}

void lcd_datas_dir_input()
{
    lcd16x2_d0_dir_input();
    lcd16x2_d1_dir_input();
    lcd16x2_d2_dir_input();
    lcd16x2_d3_dir_input();
    lcd16x2_d4_dir_input();
    lcd16x2_d5_dir_input();
    lcd16x2_d5_dir_input();
    lcd16x2_d7_dir_input();
}

void lcd_datas_output(uint8_t data)
{
    lcd16x2_d0_output() = (data & 0x01);
    lcd16x2_d1_output() = ((data >> 1) & 0x01);
    lcd16x2_d2_output() = ((data >> 2) & 0x01);
    lcd16x2_d3_output() = ((data >> 3) & 0x01);
    lcd16x2_d4_output() = ((data >> 4) & 0x01);
    lcd16x2_d5_output() = ((data >> 5) & 0x01);
    lcd16x2_d6_output() = ((data >> 6) & 0x01);
    lcd16x2_d7_output() = ((data >> 7) & 0x01);
}

uint8_t lcd_datas_input()
{
    uint8_t value = 0;
    if (lcd16x2_d0_input()) value |= BIT0;
    if (lcd16x2_d1_input()) value |= BIT1;
    if (lcd16x2_d2_input()) value |= BIT2;
    if (lcd16x2_d3_input()) value |= BIT3;
    if (lcd16x2_d4_input()) value |= BIT4;
    if (lcd16x2_d5_input()) value |= BIT5;
    if (lcd16x2_d6_input()) value |= BIT6;
    if (lcd16x2_d7_input()) value |= BIT7;
    return value;
}
#endif
//hoi Khue
void meterpc_read_timer() {}
void rtc_timer() {}
void system_refresh_timer() {}
void led_status_timer_task() {}
void uart_wakeup_timer_task() {}