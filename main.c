/*===========================================================================*/
/* I N C L U D E S                                                           */
/*===========================================================================*/
#include <xc.h>
#include <stdio.h>
#include <string.h>

// Header prjEMETERS
#include "devices.h"
#include "quanhdt.h"
#include "main.h"
#include "hardware.h"

// Header prjLIB
#include "delay.h"
#include "ade-measure-foreground.h"
#include "eeprom.h"
#include "timers.h"
#include "process.h"
#include "communication.h"
#include "uart.h"
#include "spi.h"
#ifdef TARIFF_SUPPORT
#include "multi-tariff.h"
#endif
#ifdef EVENT_SUPPORT
#include "events.h"
#endif
#ifdef BILLING_SUPPORT
#include "billing.h"
#endif 
#ifdef BILLING_PERIOD_SUPPORT
#include "billing_period.h"
#endif
#ifdef LOAD_PROFILE_SUPPORT
#include "load-profile.h"
#endif
#ifdef DISPLAY_SUPPORT
#include "emeter-display.h"
#endif
#ifdef DTP_SUPPORT
#include "dtp.h"
#endif
#ifdef RF_SUPPORT
#include "rf.h"
#include "rfmesh.h"
#endif
#ifdef RTC_SUPPORT
#include "rtc.h"
#ifdef RTCC_SUPPORT
#include "rtcc.h"
#endif
#endif

// Header prjDRVIER
#include "ade7858.h"

/*===========================================================================*/
/*  G L O B A L   S Y M B O L   D E C L A R A T I O N S                      */
/*===========================================================================*/
// PIC24FJ128GA406 Configuration Bit Settings
// 'C' source line config statements
// FSEC
#pragma config BWRP = OFF               // Boot Segment Write Protect (Boot segment may be written)
#pragma config BSS = DISABLED            // Boot segment Protect (No Protection (other than BWRP))
#pragma config BSEN = OFF               // Boot Segment Control bit (No Boot Segment)
#pragma config GWRP = OFF               // General Segment Write Protect (Writes to program memory are allowed)
#pragma config GSS = DISABLED            // General Segment Code Protect (Code protection is disabled)
#pragma config CWRP = OFF               // Configuration Segment Program Write Protection bit (Configuration Segment may be written)
#pragma config CSS = DISABLED            // Configuration Segment Code Protection Level bits (No Protection (other than CWRP))
#pragma config AIVTDIS = DISABLE        // Alternate Interrupt Vector Table Disable bit (Disable AIVT)

// FBSLIM
#pragma config BSLIM = 0x1FFF           // Boot Segment Code Flash Page Address Limit bits (Boot Segment Flash page address limit)

// FSIGN

// FOSCSEL
#pragma config FNOSC = PRI          // Oscillator Select (Primary Oscillator with PLL module (XTPLL, HSPLL, ECPLL))
#pragma config PLLMODE = DISABLED       // Frequency Multiplier Select Bits (No PLL used; PLLEN bit is not available)
#pragma config IESO = ON                // Internal External Switchover (Start up device with FRC, then switch to user-selected oscillator source)

// FOSC
#pragma config POSCMOD = HS             // Primary Oscillator Select (External clock mode selected)
#pragma config OSCIOFCN = OFF           // OSCO Pin Configuration (OSCO/CLKO/RC15 functions as CLKO (FOSC/2))
#ifdef USE_LPRC
#pragma config SOSCSEL = OFF 
#else
#pragma config SOSCSEL = ON             // SOSC Power Selection Configuration bits (SOSC is used in crystal (SOSCI/SOSCO) mode)
#endif
#pragma config PLLSS = PLL_FRC//PLL_PRI          // PLL Secondary Selection Configuration bit (PLL is fed by the Primary oscillator)
#pragma config IOL1WAY = OFF             // IOLOCK One-Way Set Enable (Once set the IOLOCK bit cannot be cleared)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock switching and Fail-Safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPS = PS2048            // Watchdog Timer Postscaler (1:512)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config FWDTEN = ON              // Watchdog Timer Enable (Watchdog Timer is enabled)
#pragma config WINDIS = OFF             // Windowed Watchdog Timer Disable bit (Standard Watchdog Timer enabled (Windowed-mode is disabled))
#pragma config WDTWIN = PS25_0          // Watchdog Window Select bits (Watch Dog Timer Window Width is 25 percent)
#pragma config WDTCMX = WDTCLK          // WDT Clock Source Select bits (WDT clock source is determined by the WDTCLK Configuration bits)
#pragma config WDTCLK = LPRC            // WDT Clock Source Select bits (WDT uses LPRC)

// FPOR
#pragma config BOREN = ON               // Brown-out Reset Enable bits (Brown-out Reset Enable)
#pragma config LPCFG = OFF              // Low power regulator control (Disabled)

// FICD
#pragma config ICS = PGx1               // Emulator Pin Placement Select bits (Emulator functions are shared with PGEC1/PGED1)
#pragma config JTAGEN = OFF              // JTAG Port Enable (JTAG port is enabled)
#pragma config BTSWP = OFF              // BOOTSWP Instruction Enable bit (BOOTSWP instruction is disabled)

// FDS
#pragma config DSWDTPS = DSWDTPS1F      // Deep Sleep Watchdog Timer Postscale Select bits (1:68,719,476,736 (25.7 days))
#pragma config DSWDTOSC = LPRC          // DSWDT Reference Clock Select bit (DSWDT uses Low Power RC Oscillator (LPRC))
#pragma config DSBOREN = ON             // Deep Sleep Zero-Power BOR Enable bit (Deep Sleep BOR enabled in Deep Sleep)
#pragma config DSWDTEN = ON             // Deep Sleep Watchdog Timer Enable bit (DSWDT enabled)
//#pragma config DSSWEN = ON              //  (Deep Sleep enabled and controlled by the DSEN bit)

// FDEVOPT1
#pragma config ALTCMPI = DISABLE        // Alternate Comparator Input Enable bit (C1INC, C2INC, and C3INC are on their standard pin locations)
#pragma config TMPRPIN = OFF            // Tamper Pin Enable bit (TMPRN pin function is disabled)
#pragma config TMPRWIPE = OFF           // RAM Based Entryption Key Wipe Enable bit (Cryptographic Engine Key RAM is not erased onTMPR pin events)
#pragma config ALTVREF = ALTVREFDIS     // Alternate VREF location Enable (VREF is on a default pin (VREF+ on RA10 and VREF- on RA9))

/*===========================================================================*/
/*  G L O B A L   D A T A   D E F I N I T I O N S                            */
/*===========================================================================*/

/*===========================================================================*/
/* G L O B A L   F U N C T I O N S   P R O T O T Y P E S                     */
/*===========================================================================*/
//ngat on change
void __attribute__ ((interrupt,auto_psv)) _CNInterrupt(void)
{
    
    if(on_change_interrupt_flag_status())
    {        
        ////////////////////////////////////////////////////////////////////////////
        /*   ngat RTC    */
        ////////////////////////////////////////////////////////////////////////////
        #if defined(PCF2129_SUPPORT)
        if (pcf2129_interrupt_flag_check())
        {
            pcf2129_interrupt_flag_clear();
            if(pcf2129_interrupt_input() == 0)
            {
                emeter.flags.rtc_interrupt = TRUE;           
            }            
        } 
        #endif
        ////////////////////////////////////////////////////////////////////////////
        /*   ngat button DOWN    */
        ////////////////////////////////////////////////////////////////////////////
        if (button_down_interrupt_flag_check())
        {
            button_down_interrupt_flag_clear();
            //button_scan();
            if(button_down_input() == 0)
            {
                emeter.task.button_down = TRUE;        
    #ifdef MCU_WATCHDOG_SUPPORT
                mcu_watchdog_toggle();
    #endif
            }            
        }        
        ////////////////////////////////////////////////////////////////////////////
        /*   ngat button UP    */
        ////////////////////////////////////////////////////////////////////////////    
        if (button_up_interrupt_flag_check())
        {
            button_up_interrupt_flag_clear();
            //button_scan();
            if(button_up_input() == 0)
            {
                emeter.task.button_up = TRUE;
    #ifdef MCU_WATCHDOG_SUPPORT
                mcu_watchdog_toggle();
    #endif                
            }     
        }
        
#ifdef RF_SUPPORT
        rf_interrupts_process();      
#endif
    }
    on_change_interrupt_flag_clear();
}


//ngat xung do dem
//reactive
void __attribute__((interrupt, auto_psv)) _INT1Interrupt(void)
{
    if(_ade_reactive_pulse_interrupt_flag_status())
    {
        _ade_reactive_pulse_interrupt_flag_clear();
        emeter.flags.reactive_pulse = TRUE; // Code
    }
}
//active
void __attribute__((interrupt, auto_psv)) _INT2Interrupt(void)
{
    if(_ade_active_pulse_interrupt_flag_status())
    {
        _ade_active_pulse_interrupt_flag_clear();
        emeter.flags.active_pulse = TRUE; // Code
    }
}
//apparent
void __attribute__((interrupt, auto_psv)) _INT3Interrupt(void)
{
    if(_ade_apparent_pulse_interrupt_flag_status())
    {
        _ade_apparent_pulse_interrupt_flag_clear();
        emeter.flags.apparent_pulse = TRUE; // Code
    }
}


void __attribute__((interrupt, auto_psv)) _INT4Interrupt(void)
{
    //ngat RTC
#if defined(PCF2129_SUPPORT) && (defined(_DT03MRF_PCB_PIC_AS8_S_V10_) || defined(_DT03MRF_PCB_PIC_AMS_S_V10_) || defined(_DT03MRF_PCB_PIC_AS8_S_V12_))
    if(pcf2129_interrupt_flag_check())
    {
        pcf2129_interrupt_flag_clear();
        emeter.flags.rtc_interrupt = TRUE; // test
    }
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V20_) || defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
    //ngat low voltage detect
    if (power_fail_detect_interrupt_flag_check())
        {
            power_fail_detect_interrupt_flag_clear();
            if (power_fail_detect_input() == 0)
            {                
                unsigned char low_volt_detect_count = 0;
                unsigned char i = 0;
                //delay chong nhieu
                for (i = 0; i < 20; i++)
                {
                   if (power_fail_detect_input() == 0)
                   {
                       delay_us(5);
                       low_volt_detect_count++;
                   }
                }
                if (low_volt_detect_count >= 4)
                {
                    low_volt_detect_count = 0;
                    emeter.flags.low_voltage_detect = TRUE;
                    emeter.flags.power_down = TRUE;
                    //disable ngat uart
                    #if defined(ALERT_MODEM_SUPPORT)
                    disable_UART0();//UC0IE &= ~UCA0RXIE;
                    #else
                    uart_disable(); //thay cho disable_UART0 va disable_UART1
                    #endif
                    //disable timer
                    //thaodtn: sua sau TACCTL0 &= ~CCIE;        // TACCR0 interrupt disable
                    //thaodtn: sua sau TACTL =  MC_0 | TASSEL_2;// TASSEL_1 + MC_1;  // Stop timerA0
                    //xoa cac flag cua tien trinh khac
                    emeter.task.button_down = FALSE;
                    emeter.task.button_up = FALSE;
                    emeter.task.display_scroll = FALSE;
                    timers.refresh_system.action = FALSE;//emeter.task.refresh_system = FALSE;
                    timers.refresh_cc1101.action = FALSE;
                    emeter.flags.power_down = TRUE; //Meter_state = 0;
                    #ifdef RF_SUPPORT
                        rf.flags.transmitted = FALSE;//Flag_RF_transmit_OK = 0;
                        rf.flags.received = FALSE; //Flag_RF_receive_data = FALSE;
                    #endif

                    #ifdef IEC62056_21_SUPPORT
                        iec62056.flags.message = FALSE;
                        iec62056.flags.proccess = FALSE;
                        iec62056.Flag_xuli_UART1 = FALSE;
                    #endif
                    #ifdef OLD_TARIFF_SUPPORT
                        #ifdef DEFERRED_TARIFF_SUPPORT
                            tariff.deferred_tariff_flag = FALSE;
                        #endif
                        #ifdef SEASON_TARIFF_SUPPORT
                            tariff.season_tariff_config = FALSE;
                        #endif
                    #ifdef MAX_DEMAND_SUPPORT
                        tariff.max_demand.flag = FALSE;
                        tariff.max_demand.consumed_flag = FALSE;
                    #endif
                    #endif
                    #ifdef BILLING_SUPPORT
                        billing.flags.save_data = FALSE;
                    #endif
                    #ifdef LOAD_PROFILE_SUPPORT
                        load_profile.proccess = FALSE;
                    #endif
                    #ifdef EVENT_SUPPORT
                        events.task = FALSE;
                    #endif
                }
            }
        }
#endif
}


//ngat RTCC
#ifdef RTCC_SUPPORT
void __attribute__((interrupt, auto_psv)) _RTCCInterrupt(void)
{
    if (rtcc_interrupt_flag_check() == TRUE)
    {
        rtcc_interrupt_flag_clear();
        emeter.flags.rtc_interrupt = TRUE;
    }
}
#endif

//timer 500ms
void __attribute__((interrupt, auto_psv)) _T1Interrupt(void)
{
    timer16ms_interrupt_process();
}

//timer 500ms
void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) 
{
    if ((timer2_interrupt_flag_status()) && (timer2_interrupt_enable_status()))  //timer2_interrupt_status
    {        
        timer2_interrupt_flag_clear();
        //todo 500ms, phai do lai        
        count_0_5s++;
        count_watchdog++;
        timers.half_second.action = TRUE; //dung cho timer_task()
        ////////////////////////////////////////////////////////////////////////
        #ifdef MCU_WATCHDOG_SUPPORT
        //mcu_watchdog_toggle();
        //cho IC watchdog moi STWD100XY
        mcu_watchdog_start();
        delay_us(10);
        mcu_watchdog_end();
        #endif
#ifdef WOR_SUPPORT//WOR
        if (emeter.flags.power_down == TRUE) //if(Meter_state == POWER_FAILURE)
        {
            if(rf.flags.wor_mode == 1)
            {
                rf.count_wor++;
                if(rf.count_wor > 345600)//2 ngay //518400)  // 3 ngay thi tat wor, dua rf vao che do ngu
                {
                    cc1101_cmd_strobe(CC1101_SIDLE);
                    delay_ms(2);
                    cc1101_cmd_strobe(CC1101_SPWD);
                    rf.flags.wor_mode = 0;
                    rf.flags.wake_up = 0;
                    port2_interrupt_disable();
                    cc1101_cs_output_high();
                    #ifdef RTC_SUPPORT
                    pcf2129_cs_low();
                    #endif
                    eeprom_cs2_low();
                    eeprom_cs1_low();
                    spi_sdi_low();
                    spi_sclk_low();
                }
            }
        }
#endif
        ////////////////////////////////////////////////////////////////////////////
#ifdef RTC_SUPPORT
        if (count_0_5s % 2)
        {
            emeter.task.update_time = TRUE;//moi giay doc rtc 1 lan
        }
#endif
        ////////////////////////////////////////////////////////////////////////////
        if (++timers.auto_display.counter > timers.auto_display.timeout)//(count_0_5s == 10)
        {
            timers.auto_display.counter = 0;
            //timers.auto_display.action = TRUE;
            display.flags.scroll_auto = TRUE;
            //count_0_5s = 0;
            //LPM3_EXIT;
        }
        else if (power_fail_detect_input())
        {
    //#ifdef WOR_SUPPORT//WOR
            count_watchdog = 0;
            if (emeter.flags.power_down == TRUE) //if (Meter_state == POWER_FAILURE)
            {
                emeter.flags.power_down = FALSE; //Meter_state = 0;
                //LPM3_EXIT;
            }

    //#endif
            // thaodtn 24/11
            if (flag_display_TIME == 1)
            {
                emeter.task.update_time = 1;
            }

        ////////////////////////////////////////////////////////////////////////////
#ifdef RF_SUPPORT
//            if(rf.status == TX) //vinh
//            {
//                if(rf.flags.transmiting)
//                    rf.count_rf++;
//                else
//                {
//                    rf.count_rf_tx++;
//                    if(rf.count_rf_tx > 2)
//                        rf.flags.error_tx = 1; // sau 1s neu rf ko phat duoc tuc ko xay ra ngat chan GDO2 thi set flag error tx
//                }
//            }
#endif
        }
        else // mat dien
        {
            count_watchdog = 0;
            //canh bao het pin
            if (!batt_monitor_input())
            {
                emeter.flags.low_batt = TRUE;
            }
            else
            {
                emeter.flags.low_batt = FALSE;
            }

        //////////
#ifdef WOR_SUPPORT//WOR
            if(rf.flags.wake_up)
            {
                if(rf.flags.wor_mode)
                {
                    rf.count_rf++;
                    if(!rf.flags.transmiting)
                    {
                        if(rf.flags.received == 1)
                        {
                            if(rf.status == RX) rf_process_data_receive();
                        }
                        else if(rf.count_rf > 9)
                        {
                            if(rf.status == RX)
                            {
                                rf.count_rf = 0;
                                display_item_comm(HIDE);
    #ifdef WOR_SUPPORT
                                cc1101_enter_wor_mode();
    #endif
                                cc1101_gdo2_interrupt_enable();
                            }
                        }
                    }
                    else if((rf.count_rf>2)||(cc1101_gdo2_input() ==0))
                    {
                        rf.count_rf = 0;
                        display_item_comm(HIDE);
                        rf.flags.transmiting = 0;
                        #ifdef WOR_SUPPORT
                        cc1101_enter_wor_mode();
                        #endif
                        cc1101_gdo2_interrupt_enable();
                    }
                }
            }
#endif
        }
        //if (power_fail_detect_input()) warning_task();  //tranh t/h moi cap nguon da canh bao
        if(emeter.flags.low_voltage_detect == FALSE) emeter.flags.warning_task = TRUE;//warning_task();
        //display_quadrature(); da goi trong cac ham display_process_...
        /////// CODE CU
//        if(emeter.flags.low_voltage_detect == FALSE)
//        {
//#ifdef ADE78XX_ANGLE_SWITCH_MODE_SUPPORT
//            ade7858.flags.angle_UU_mode = !(ade7858.flags.angle_UU_mode);
//#endif       
//            
//        } 
//        else if(power_fail_detect_input()) //co dien lai
//        {
//            while(1);
//        }
    }    
}

void variable_init()
{
    active_reg 		= &emeter.active;
	reactive_reg 	= &emeter.reactive;
	apparent_reg 	= &emeter.apparent;
    emeter.flags.low_voltage_detect = FALSE;
    pcb_version = (DAY_PCB * 1000) + ((MONTH_PCB % 10)*100) + YEAR_PCB;
    if (MONTH_PCB > 9)
        pcb_version |= 0x8000;
}
/*===========================================================================*/
/* M A I N                                                                   */

/*===========================================================================*/
int main(void)
{
    di();    
    system_setup(); 
    variable_init();
    //hien thi LCD
    display_version();
    delay_ms(600);//600);  // Cho dien ap on dinh
    watchdog_enable();
    #if defined(RTC_SUPPORT)
    //VUONGLQ 17032021 fix loi tai thoi diem cau hinh thi xay ra ngat phut
    //Swap 2 lenh ben duoi
    rtc_interrupt_enable();
    rtc_init();
    #endif
    eeprom_load_parameters();
    
    //ade
    ade7858_load_calib_value();
    ade7858_init();
    on_change_interrupt_init();
    
    delay_ms(400);//600);  // Cho dien ap on dinh
    emeter_measurement_task();//tuantm doc 1 lan cho ade on dinh
    
    ////////////////////////////////////////////////////////////////////////////
    /*   khoi tao chuc nang    */
    ////////////////////////////////////////////////////////////////////////////
    /*   khoi tao chuc nang    */
    #ifdef RFMESH_SUPPORT //tuantm
    rfmesh_init();
    #endif
    //thaodtn delay_ms(600);
    timer_init();
    #ifdef DISPLAY_USE_ARRAY_CONFIG
    display_init();
    #else
    display_init(emeter.auto_list, emeter.manual_list, emeter.ultility_list, timers.auto_display.timeout);
    #endif
    //kiem tra pin
    //kiem tra het pin
#ifdef CHECK_BATTERY_SUPPORT
    if (!batt_monitor_input())
    {
        display_item_battery(SHOW);
        emeter.flags.low_batt = 1;
    }
    else
    {
      emeter.flags.low_batt = 0;
      display_item_battery(HIDE);
    }
#endif
	//kiem tra nguon cung cap
    /*
    if ((!power_fail_detect_input()) && (emeter.flags.low_batt == 0)) //ko co dien ap luoi nhung co dung pin
    {
        emeter.flags.low_voltage_detect = TRUE;
        flag_power_fail = 1;
    }
    else
    {
        flag_power_fail = 0;
    }
    */
    //kiem tra jump can chinh
	//kiem tra jump cho phep ghi va can chinh , neu dung pin ngay tu dau thi ko hien thi
    emeter.flags.calib_enable = 0;
    if ((calib_enable_input() == 0)&&(flag_power_fail == 0))
    {
        delay_ms(10);
        if ((calib_enable_input() == 0)&&(flag_power_fail == 0))
        {
             emeter.flags.calib_enable = 1;
             display_calib_mode(SHOW);
        }
    }
    if (calib_enable_input() == 0) emeter.flags.calib_enable = 1;
    ////////////////////////////////////////////////////////////////////////////
    // khoi tao bieu gia
#ifdef TARIFF_SUPPORT
    tariff_init();
#endif
    ////////////////////////////////////////////////////////////////////////////
    //khoi tao load profile
#ifdef LOAD_PROFILE_SUPPORT
    load_profile_init(&datetime);
    //load_profile.period = 300; // 5 phut
    //load_profile.config = 1;
    if ((load_profile.period != 0)&&(load_profile.config != 0))
    {
        load_profile.status = RESTART;
        load_profile.start_time = datetime.utc;
        load_profile_update_header(&datetime,datetime.utc);
    }
#endif
#if defined(TRANSFORMER_SUPPORT) && defined(LOAD_PROFILE_SUPPORT)
    if ((load_profile.period != 0)&&(load_profile.config != 0))
    {
        if (transformer.status_ratio != 0)
        {
            load_profile.status = CHANGE_TRANSFORMER_RATIO;
            load_profile.start_time = datetime.utc;
            load_profile_update_header(&datetime,datetime.utc);
            load_profile_proccess();
            restart_watchdog();
            load_profile.status = NEW_CONFIG;
            load_profile_update_header(&datetime,datetime.utc);
        }
    }
#endif
    ////////////////////////////////////////////////////////////////////////////
    //khoi tao max demand
#ifdef MAX_DEMAND_SUPPORT
    //max_demand.period = load_profile.period / 10; // giay <=> 1 phut (lay 10% cua chu ki tich phan)
    //tariff.max_demand.period = 60; doc tu eeprom, dua vao ham max_demand_init()
    max_demand_init();
#endif
    ////////////////////////////////////////////////////////////////////////////
    // khoi tao billing
#ifdef BILLING_SUPPORT
    billing_init(&datetime);
    billing_check(&datetime);
#endif
#ifdef BILLING_DAY_MAX_DEMAND_SUPPORT
    billing_max_demand_init();
#endif
    ////////////////////////////////////////////////////////////////////////////
    // giao tiep iec
#ifdef IEC62056_21_SUPPORT
    iec1107_reset();
#endif
#ifdef DTP_SUPPORT
    dtp_init();
#endif
    ////////////////////////////////////////////////////////////////////////////
    // events
#ifdef EVENT_SUPPORT
    events_init();
    //if (events.config == EVENT_POWER_DOWN)
    //    lcd_display_value(11111111);
    if (events.config & MASK_32BIT[EVENT_POWER_DOWN])
    {
        //luu thoi gian co dien, ket thuc su kien POWER DOWN
        events_save_stop_time(datetime.utc,EVENT_POWER_DOWN);
    }
#ifdef ALERT_SUPPORT
    #ifdef ALERT_MODEM_SUPPORT
    //send_alert_power_on_modem(UART_PC);
    //send_alert_power_on_off_modem(UART_PC, ON); //co dien, ket thuc su kien power down
    alert.event_off = MASK_32BIT[EVENT_POWER_DOWN];
    alert.utc_stop = datetime.utc;
    send_alert_dtp_message(UART_PC);
    #else
    //send_alert_power_on(UART_PC);
    send_alert_power_on(UART_RFSLOT);
    send_alert_power_on(UART_GSMSLOT);
    #endif
#endif
//    if (events.config & MASK_32BIT[EVENT_EEPROM_FLASH_ERROR])
//    {
//      if (events.index[EVENT_EEPROM_FLASH_ERROR].status == 1)
//        save_length_time_event(EVENT_EEPROM_FLASH_ERROR);
//    }
//    if (events.config & ((unsigned long)1<<EVENT_EEPROM_FLASH_ERROR))
//    {
//      if (events.index[EVENT_EEPROM_FLASH_ERROR].status == 1)
//        save_length_time_event(EVENT_EEPROM_FLASH_ERROR);
//    }

#endif
    ////////////////////////////////////////////////////////////////////////////
    //test
    //test_eeprom();
    //lcd_display_all();
//    while (1)
//    {
//        ClrWdt(); 
//        //test_rtc();
//        //test_eeprom();
//        delay_ms(500);
//        lcd_backlit_toggle();
//        total_active_energy_pulse_dir_output();  
//        total_reactive_energy_pulse_dir_output();
//        adnormal_led_dir_output();
//        total_active_energy_pulse_toggle();
//        total_reactive_energy_pulse_toggle();
//        adnormal_led_toggle();
//    }
    
    //rtc_set_time(13, 33, 0);
    //rtc_set_date(6, 9, 12, 17);
    
    
//    while (1)
//    {
//        ClrWdt();  
//        //test_hardware();
//        //lcd_backlit_start();
//        //adnormal_led_dir_output();
//        adnormal_led_start();
//        delay_ms(500);
//        uart_pc_send_byte('A');
//        uart_optical_send_byte('B');
//        //emeter_measurement_task();
//        //lcd_anten(SHOW);
//        //======================
//        //ClrWdt();  
//        //test_hardware();
//        //lcd_backlit_toggle();
//        //delay_ms(500);
//        //lcd_anten(HIDE);
//    }
    ////////////////////////////////////////////////////////////////////////////
	/*   xu ly chinh    */
	////////////////////////////////////////////////////////////////////////////    
    
    ei();  
 
    while (1)
    {        
        restart_watchdog();       
        //test rf hungnd 22/01/2021
        
        ////////////////////////////////////////////////////////////////////////////    
        if (ade7858.flags.register_error == 1)
            display_Gnd(SHOW);
        else
            display_Gnd(HIDE);  
                 
        //==================== Energy Measurement ==============================
		if (emeter.token != 0) { _DINT();  while(1); }
		emeter.token++; //1
        emeter_measurement_task();
         
        //===================== button =========================================
		if (emeter.token != 1) {_DINT(); while(1); }
		emeter.token++;  //2
        button_task();       
        //==================== hien thi ========================================
		if (emeter.token != 2) {_DINT(); while(1); }
		emeter.token++;//3
        display_task();

		//==================== PC communication ================================
		if (emeter.token != 3) {_DINT(); while(1); }
		emeter.token++;//4
        communication_task();
        
        //==================== RF communication ================================
		if (emeter.token != 4) { _DINT();  while(1); }
		emeter.token++; //5
#ifdef RF_SUPPORT
        rf_task();
        #ifdef RFMESH_SUPPORT
        rfmesh_task();
        #endif
#endif
        //========================= rtc ========================================
		if (emeter.token != 5) {_DINT(); while(1); }
		emeter.token++;//6
#ifdef RTC_SUPPORT
		rtc_task();
#endif
        
        //========================= multi tariff ===============================
		if (emeter.token != 6) {_DINT(); while(1); }
		emeter.token++;//7
#ifdef TARIFF_SUPPORT
		tariff_task();
#endif
       
        //========================= billing ====================================
		if (emeter.token != 7) {_DINT(); while(1); }
		emeter.token++;//8
#ifdef BILLING_SUPPORT
		billing_task();
#endif
#if defined(BILLING_PERIOD_SUPPORT)
        billing_period_task();
#endif
        
        //========================= events =====================================
		if (emeter.token != 8) {_DINT(); while(1); }
		emeter.token++;//9
#ifdef EVENT_SUPPORT
		events_task();
#endif
         
        //========================= load profile ===============================
		if (emeter.token != 9) {_DINT(); while(1); }
		emeter.token++;//10
#ifdef LOAD_PROFILE_SUPPORT
		load_profile_task();
#endif
        
		//====================  DATA SAVE  tang 1kWh thi luu 1 lan` ============
		if (emeter.token != 10) {_DINT(); while(1); }
		emeter.token++; //11
        save_data_task();
       
		//=========================  Power Fail   ==============================
		if (emeter.token != 11) {_DINT(); while(1); }
		emeter.token++;//12
        emeter_power_failure_task();
         
		//==================== reset system ====================================
		if (emeter.token != 12) {_DINT(); while(1); }
		emeter.token++;//13
		//if(count_watchdog >2) while(1);
      
		//====================refresh system ===================================
		if (emeter.token != 13) {_DINT(); while(1); }
		emeter.token++;//14
        refresh_system_task();

        //==================== warning task  ===================================
		if (emeter.token != 14) {_DINT(); while(1); }
		emeter.token++;//15
        event_monitor_task();//warning_task();   dua len timer 0.5s
        //==================== timer task   ====================================
        if (emeter.token != 15) {_DINT(); while(1); }
		emeter.token++;//16
        timer_task();

		emeter.token = 0;
    }    
    return 0;
    
}
