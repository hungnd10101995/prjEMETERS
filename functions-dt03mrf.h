#ifndef FUNCTIONS_DT03MRF_H
#define FUNCTIONS_DT03MRF_H
/*===========================================================================*/
#define REDUCTION_VERSION_SUPPORT
/*===========================================================================*/
#define U_I_MEASURE_SUPPORT
/*===========================================================================*/
#define UINT64_SUPPORT
#define USE_WATCHDOG //watchdog noi cua MCU
#define MCU_WATCHDOG_SUPPORT
#define POWERDOWN_DETECT_SUPPORT
#define BUTTON_SUPPORT

//hungnd 13/01/2021 them neutral doc cac thong so neutral
#define NEUTRAL_ENEGRY_SUPPORT
#define TOTAL_ACTIVE_NEUTRAL_ENERGY_SUPPORT
#define TOTAL_REACTIVE_NEUTRAL_ENERGY_SUPPORT

#if (defined(_DT03MRF_PCB_PIC_AS8_S_V20_) \
    || defined(_DT03MRF_PCB_PIC_AS8_S_V12_) \
    || defined(_DT03MRF_PCB_PIC_AS8_S_V22_))
#define ADNOMAL_LED_SUPPORT
#endif

//#define OBIS_SUPPORT //dung cho giao thuc IEC moi cua EVN
/*===========================================================================*/
/* RTC */
#define RTC_SUPPORT
#define PCF2129_SUPPORT 
#ifndef PCF2129_SUPPORT
#define RTCC_SUPPORT
#endif
//can chinh RTC
//#define RTC_CORRECTION
/*===========================================================================*/
//test PCB PIC+ADE 
/* DISPLAY */
#define DISPLAY_SUPPORT
#define DISPLAY_METERID_SUPPORT //hien thi ID dau chuong trinh
#define DISPLAY_NEW_ITEMS
#define DISPLAY_USE_ARRAY_CONFIG
#define ULTILITY_DISPLAY_SUPPORT
#define LCD_BACKLIT_SUPPORT
#define DISPLAY_3_DECIMAL_KW //hien thi don vi KW va 3 so thap phan cho cong suat
#define DISPLAY_ERROR_REGISTERS_SUPPORT //hien thi Err khi bi loi thanh ghi
//////////////////////////////////////////////
//Tm thoi bo cac chuc nang nay do thieu code//
//////////////////////////////////////////////
//#define UPDATE_VALUE_LCD //Update thong so online - Upadte sau moi 0.5s // vuonglq 26/1/2019
//#define DISPLAY_PRIVATE_PRI_SEC_TRANSFORMER_SUPPORT //Hien thi pri&second TU/TI // vuonglq 26/1/2019
//#define DISPLAY_DATE_INSTALL_BATT_SUPPORT ////Hien thi ngay gio lap PIN // vuonglq 26/1/2019
//#define DISPLAY_DATE_TIME_MAX_DEMAND_SUPPORT
//////////////////////////////////////////////

#ifndef _LCD_1602_
#define DISPLAY_OBIS_CODE_SUPPORT
#endif

//#define DISPLAY_BILLING_DATA_SUPPORT //chuyen thanh DISPLAY_BILLING_SUPPORT
//#define DISPLAY_ERRORCODE_SUPPORT
//#define DISPLAY_PHASE_ICON //ki hieu A, B, C va SUM
//#define BLINKING_ALERT_SUPPORT //nhap nhay cac ki hieu canh bao

#if defined(_LCD_M0754v2_PCF8545_) || defined(_LCD_M0754v3_PCF8545_)
#define PCF8545_DISPLAY_SUPPORT
#endif

/*===========================================================================*/
/* TRANSFORMERS */
#define TRANSFORMER_SUPPORT
#ifndef TRANSFORMER_SUPPORT
#define TU_ratio                1
#define TI_ratio                1 
#define transformer_ratio       1
#define TU_primary              1
#define TU_secondary            1
#define TI_primary              1
#define TI_secondary            1
#endif

/*===========================================================================*/
//hard configure
//#define HARD_CONFIGURE
/*===========================================================================*/


/*===========================================================================*/
//test PCB PIC+ADE  
/* MULTI-TARIFF  */
#define TARIFF_SUPPORT
#define DEFERRED_TARIFF_SUPPORT
//#define SEASON_TARIFF_SUPPORT
//hcm #define TARIFF_CHECK_SWT_SUPPORT
#define MAX_DEMAND_SUPPORT
//#define MAX_DEMAND_REDUCE_SUPPORT
//#define MAX_DEMAND_PERIOD //cho phep cau hinh period cua maxdemand
//#define MAX_DEMAND_TOTAL_SUPPORT
//#define SEASON_TARIFF_SUPPORT
 
//#define NEW_TARIFF_SUPPORT 
#define OLD_TARIFF_SUPPORT  

//Jumper can chinh HCM
//#define PROGRAM_ENERGY_NO_CHECK_JUMP_SUPPORT

/*===========================================================================*/
//test PCB PIC+ADE 
/* EVENTS */
#define EVENT_OBIS_QD103_SUPPORT
#define EVENT_SUPPORT
#define EVENT_CONFIG_SUPPORT
#define RF_READ_EVENT //hungnd 03/02/2021 obis RF cu
#define CHECK_BATTERY_RTC_SUPPORT
#define CHECK_BATTERY_SUPPORT //pin du phong
#define MAGNETIC_DETECT_SUPPORT
//#define UNBALANCE_PHASE_AVERAGE_SUPPORT
//#define UNBALANCE_VOLTAGE_AVERAGE_SUPPORT
#define UNBALANCE_VOLTAGE_PHASE_EVENT_SUPPORT
#define ACB_DETECT_SUPPORT
#define WARNING_SUPPORT //gui canh bao kem theo khi doc du lieu

#if ( defined(_DT03MRF_PCB_PIC_AS8_S_V10_) \
        || defined(_DT03MRF_PCB_PIC_AS8_S_V12_) \
        || defined(_DT03MRF_PCB_PIC_AS8_S_V20_) \
        || defined(_DT03MRF_PCB_PIC_AS8_S_V22_) )
    #define COVER_DETECT_SUPPORT //PCB DT03M-RF PIC+ADE
    #define TERMINAL_DETECT_SUPPORT //PCB DT03M-RF PIC+ADE
#endif

#if ( defined(_DT03MRF_PCB_PIC_AS8_S_V20_) \
        || defined(_DT03MRF_PCB_PIC_AS8_S_V22_) )
    #define WINDOW_DETECT_SUPPORT //PCB DT03M-RF PIC+ADE
#endif

/*===========================================================================*/
//#define ALERT_SUPPORT
/* chuc nang cua HCM
#define ALERT_SUPPORT
#ifdef DT03M_5_10A
    #define ALERT_MODEM_SUPPORT
#endif
*/
//------------------- Defination ERROR CODE -------------------
#define ACB_ERROR                                   1
#define PHASE_REVERSED_ERROR                        2
#define EEPROM_ERROR                                3

#define METER_MAGNETIC_DETECT   BIT0//canh bao tu truong
#define METER_LOWBAT_DETECT     BIT1//canh bao pin yeu
#define METER_REVERSE_POWER     BIT2//canh bao nguoc dong
#define METER_REVERSE_ACB       BIT3// canh bao nguoc thu pha
#define METER_NO_VOLTAGE_PHASE  BIT4// canh bao mat ap 1 pha bat ky
#define METER_OVER_CURRENT      BIT5// canh bao qua dong
#define METER_LOW_VOLTAGE       BIT6// canh bao ap thap
#define METER_OVER_VOLTAGE      BIT7// canh bao ap cao
#define METER_UNBALANCE_PHASE   BIT8// BIT8 mat can bang dong pha 
#define METER_UNBALANCE_VOLT    BIT9// mat can bang ap pha - dung cho 3pha
#define METER_EEPROM_ERROR      BIT_10 //canh bao loi eeprom 
#define METER_COVER_DETECT      BIT_11// canh bao mo nap cong to
#define METER_UNLOCK            BIT_12// canh bao mo khoa can chinh
#define METER_TERMINAL_DETECT   BIT_13 // canh bao mo nap che dau day
#define METER_LOWBAT_RTC_DETECT BIT_14 // canh bao pin rtc sap het
#define METER_WINDOW_DETECT     BIT_15 //canh bao mo nap truoc
/*===========================================================================*/
//test PCB PIC+ADE 
/* LOAD-PROFILE */ 
#define LOAD_PROFILE_SUPPORT
//#define LOAD_PROFILE_LOG_SUPPORT
#define LOAD_PROFILE_EEPROM_SUPPORT
#define LOAD_PROFILE_OBIS_QD103_2018_SUPPORT
//#define TEST_ERROR_LOADPROFILE 
/*===========================================================================*/
//test PCB PIC+ADE 
/* BILLING */
#define BILLING_SUPPORT 
#define DISPLAY_BILLING_SUPPORT
#define RF_READ_BILLING
#define BILLING_OBIS_QD103_2018_SUPPORT
//#define BILLING_PERIOD_SUPPORT
//#define BILLING_DAY
//#define BILLING_DAY_MAX_DEMAND_SUPPORT 

/*===========================================================================*/
//test PCB PIC+ADE  
/* COMMUNICATIONS  */
#if defined(_DT03MRF_PCB_PIC_AS8_S_V20_)
//    #define COMMUNICATION_RFSLOT_SUPPORT
//    #define COMMUNICATION_GSMSLOT_SUPPORT
//    #define COMMUNICATION_PC_SUPPORT
//    #define COMMUNICATION_OPTICAL_SUPPORT
#endif
#if defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
    #define COMMUNICATION_OPTICAL_SUPPORT
    #define COMMUNICATION_RFSLOT_SUPPORT
    #define COMMUNICATION_GSMSLOT_SUPPORT
    //#define COMMUNICATION_PC_SUPPORT
#endif

#define INSTANTANEOUS_SUPPORT //dung de doc thong so van hanh trong communication.c //namhv 03/01/2019
#ifdef __MSP430__
#define DLT645_SUPPORT //can chinh TI
#define CALIBRATION_SUPPORT
#define UART_PORT_0_SUPPORT                                 1
#define UART0_BAUD_RATE                                     300
#define UART_PORT_1_SUPPORT                                 1
#define UART1_BAUD_RATE                                     9600
#endif

#define COMM_PROCESS_OBIS_CMD_SUPPORT //cau truc moi, cmd obis
//#define COMM_PROCESS_EMEC_CMD_SUPPORT //cau truc moi
#define COMM_PROCESS_DTP_CMD_SUPPORT //theo cau truc dtp cu (dang san xuat) //namhv 03/01/2019

#define COMM_SLAVE_SUPPORT


#if defined(_DT03MRF_PCB_PIC_AS8_S_V20_)
    #define RS422_RS485_CONTROL_SUPPORT
    #define RS422_RS485_POWER_SUPPORT
#elif defined(_DT03MRF_PCB_PIC_AS8_S_V22_)
    //#define RS422_RS485_CONTROL_SUPPORT
    //#define RS422_RS485_POWER_SUPPORT
#else
#endif


/*===========================================================================*/
/* RF */
//#if defined(_DT03MRF_PCB_PIC_AS8_S_V10_) || defined(_DT03MRF_PCB_PIC_AS8_S_V12_) 
//    || defined(_DT03MRF_PCB_TI_S4_S_V272_) || defined(_DT03MRF_PCB_TI_S4_S_V273_)
/* RF */
#define RF_SUPPORT_PROTOCOL_EVN103      // quanhdt 01/11/2020 Ho tro giao thuc theo EVn QD103 => Tam de ben funtion

#define RF_SUPPORT
#define RFMESH_SUPPORT
#ifdef RFMESH_SUPPORT
//hcm #define RFMESH_BROADCAST
//#define RFMESH_AUTO_ROUTE
//#define RFMESH_AUTO_ROUTE2DCU
//#define RFMESH_DISPLAY_STATUS
//#define RFMESH_GET_TIMESLOT_RSSI
//#define RFMESH_AUTO_RESTART
//#define RFMESH_SPLIT_PATH 
//hcm #define RFMESH_LATCH_RSSI_DCU
#endif


#define RF_READ_SINGLE_PARAM
#define RF_READ_MULTI_PARAM
//#define RF_CONFIG_TARIFF
//hcm #define RF_CONFIG_SUPPORT
//#define RF_CONFIG_EVENT
//#define RF_CONFIG_DISPLAY
#define HHU_PROTOCOL_SUPPORT

#define SI4464_EMEC_CONFIG
//#define SI4464_PSMART_CONFIG
//#define RFPA_SUPPORT
#define DT01PRF_PROTOCOL ////FW V2.51 lam trung gian de doc cong to cmd PA

#define RF_ENCRYPT_AES_128_SUPPORT
#ifdef DT01PRF_PROTOCOL
//#define _GELEX_SUPPORT
//#define _STAR_SUPPORT
#ifdef _STAR_SUPPORT
#define _STAR_FORWARD_SUPPORT
#endif
#endif
//#define CC1101_408MHZ
#define METERPC_EMEC 
//#endif

/*===========================================================================*/
/* WAKE ON RADIO - WOR */
//#define WOR_SUPPORT  //disable WOR
#define WOR_TO_SLEEP    345600 //2 ngay 600//5ph
#define WOR_MONITOR_TIMEOUT 120

/*===========================================================================*/
//#define METERPC_EMEC
/*===========================================================================*/
//test PCB PIC+ADE 
/* IEC62056-21  */
#define IEC62056_21_SUPPORT
#define AES_128_SUPPORT 
#define ENCRYPT_PASSWORD_AES128_SUPPORT
//#define ENCRYPT_PASSWORD_ELSTER_SUPPORT
//#define CONFIG_UART_SUPPORT

//#define IEC62056_21_EVN_SUPPORT
#define IEC62056_21_EMEC_SUPPORT
#define IEC62056_21_EMEC_FULL_CMD
//#define USING_OLD_PROTOCOL_FOR_ENERGY_REGS //4 so thap phan
#define IEC62056_21_EMEC_READ_DC_METER // vuonglq 16/09/2019 dung de giao tiep voi cong to DC
#define UART_CONFIG_7_EVEN_1 //test QD103 Vuonglq 29012021
#ifdef COMMUNICATION_PC_SUPPORT
     #define UART_PC_BAUDRATE_300 //test QD103 Vuonglq 29012021
#endif
#ifdef COMMUNICATION_RFSLOT_SUPPORT
     #define UART_RFSLOT_BAUDRATE_300 //test QD103 Vuonglq 29012021
#endif
#ifdef COMMUNICATION_GSMSLOT_SUPPORT
    #define UART_GSMSLOT_BAUDRATE_300 //test QD103 Vuonglq 29012021
#endif
#ifdef IEC62056_21_EVN_SUPPORT
#define UART_CONFIG_7_EVEN_1
//#define UART_PC_BAUDRATE_300
#endif

#define IEC62056_WRITE_SUPPORT

#define IEC62056_CHANGE_CONFIG_SUPPORT
#define INSTANTANEOUS_SUPPORT
#define REACTIVE_POWER_OBIS_SUPPORT
#define REACTIVE_POWER_BY_QUADRATURE_OBIS_SUPPORT
#define APPARENT_POWER_OBIS_SUPPORT
#define REACTIVE_POWER_OBIS_SUPPORT
#define APPARENT_POWER_OBIS_SUPPORT
#define REACTIVE_POWER_BY_QUADRATURE_OBIS_SUPPORT
#define BILLING_OBIS_SUPPORT
#define ENERGY_OBIS_SUPPORT
/*===========================================================================*/

/* DTP PROTOCOL  */
#define DTP_SUPPORT
//#define DTP_PC_COMMUNICATION
//#define DTP_OPTICAL_COMMUNICATION
//#define DTP_RFSLOT_COMMUNICATION
//#define DTP_GSMSLOT_COMMUNICATION
//#define IEC62056_21_EMBEDDED_DLT645_SUPPORT //het tai nguyen MCU, tam thoi bo


/*===========================================================================*/
/* EEPROMS */
#define EEPROM_SUPPORT
#define EEPROM_25AA1024
#define LUU_XOAY_VONG_THANH_GHI_SUPPORT 
#define BACKUP_BELONG_WITH_TIME_SUPPORT 
//#define BACKUP_BELONG_WITH_ENERGY
#define EEPROM_1_SUPPORT
#define EEPROM_2_SUPPORT

//#define FLASH_SUPPORT
//#define SST25VF016B_SUPPORT //dung cho log bieu do phu tai
//#define FLASH_1_SUPPORT
//#define FLASH_2_SUPPORT

// 2020-05-04 namhv
#if ( defined(_DT03MRF_PCB_PIC_AS8_S_V10_) \
        || defined(_DT03MRF_PCB_PIC_AS8_S_V12_) \
        || defined(_DT03MRF_PCB_PIC_AS8_S_V20_) \
        || defined(_DT03MRF_PCB_PIC_AS8_S_V22_) )
#define FLASH_SUPPORT
#define SST25VF016B_SUPPORT //dung cho log bieu do phu tai
#define FLASH_1_SUPPORT
#if ( defined(_DT03MRF_PCB_PIC_AS8_S_V20_) \
        || defined(_DT03MRF_PCB_PIC_AS8_S_V22_) )
#define FLASH_2_SUPPORT
#endif
#endif
/*===========================================================================*/
/* REGISTERS */ 
#define REGISTER_64BIT_SUPPORT
#define CUSTOMER_DEFINED_REGS_SUPPORT //vuonglq off de test chuong trinh doc cong to dc
#ifdef REGISTER_64BIT_SUPPORT
#define KWH_WRAP                    999999999999999999 //so tran 99.999.999.999.999,9999
#define LENGTH_REGS                 8 //bytes
#define EEPROM_RATE_LENGTH          11 //1 thanh ghi rate (9 byte value(co CRC) + 2 byte source(co CRC))
#define EEPROM_START_SOURCE_RATE    9 //vi tri luu source cua bieu gia
#if defined(DT03M_1_12A)
#define RESOLUTION                  1000000//mWh do phan giai thanh ghi
//#define RESOLUTION_TO_dWh           100 //dua xuong duoi
#else
#define RESOLUTION                  10000 //kiem tra lai cho cong to 1(1.2)A; 
#endif

//#define REGION_BACKUP_MAX           10
/* #if defined(DT03M_5_10A) || defined(DT03M_1_12A)
#define THRESHOLD_KWH_BACKUP        5000//2500//250000 //0.25kWh cho cong to DT03M05
#define REGION_BACKUP_MAX           8
#elif defined(DT03M_10_100A)
#define THRESHOLD_KWH_BACKUP        120000//12kwh cho DT03M10 //kiem tra khai bao bien apparentTemp (uint16 or uint32)
#define REGION_BACKUP_MAX           8
#endif */

#else /* REGISTER_32BIT */
#define KWH_WRAP                    99999999 //so tran
#define LENGTH_REGS                 4 //bytes
#define EEPROM_RATE_LENGTH          7 //1 thanh ghi rate (5 byte value(co CRC) + 2 byte source(co CRC))
#define EEPROM_START_SOURCE_RATE    5 //vi tri luu source cua bieu gia
//do phan giai
#ifdef DT03M_1_12A
#define RESOLUTION                  20 // 2 chi so thap phan
#else
#define RESOLUTION                  100
#endif
#define REGION_BACKUP_MAX           6
#define READ_PULSE_COUNT_SUPPORT
#endif

/*===========================================================================*/
/* MEASUREMENTS */
#define MEASURES_QUADRATURE_REACTIVE_POWER_SUPPORT
#define NEUTRAL_MONITOR_SUPPORT
#define VRMS_SUPPORT
#define IRMS_SUPPORT
#define TOTAL_ACTIVE_ENERGY_SUPPORT
#define REACTIVE_POWER_SUPPORT
#define REACTIVE_POWER_BY_QUADRATURE_SUPPORT
#define TOTAL_REACTIVE_ENERGY_SUPPORT
#define APPARENT_POWER_SUPPORT
#define TOTAL_APPARENT_ENERGY_SUPPORT
#define POWER_FACTOR_SUPPORT
#define PHASE_REVERSED_DETECTION_SUPPORT
#define INSTANTANEOUS_MEASURE_SUPPORT //define cai nay de doc thong so van hanh
//#define PHASE_REVERSED_IS_TAMPERING // remove 20120726
#define MAINS_FREQUENCY_SUPPORT
#define MAINS_NOMINAL_FREQUENCY                         50
#define MAINS_NOMINAL_VOLTAGE                           230

#define TEMPERATURE_SUPPORT //thaodtn: lay he so nhiet do lam sai so hien thi cho P
/*! This switch select the use of current dependant phase correction, to allow
    the use of non-linear CTs. */
#define PHASE_CORRECTION_SUPPORT

//#undef PER_PHASE_ACTIVE_ENERGY_SUPPORT 
/*! This switch selects support for measuring the active energy consumption on a phase
by phase basis. This is only significant for poly-phase meters. */
//#define INHIBIT_NEGATIVE_PHASE_POWER_ACCUMULATION
/*! This switch inhibits the accumulation of per phase negative power */
//#define INHIBIT_NEGATIVE_TOTAL_POWER_ACCUMULATION
/*! This switch inhibits the accumulation of total negative power */

/*! The duration of the LED on time for an energy pulse. This is measured in
    ADC samples . The maximum allowed is 255, giving a
    pulse of about 78ms. 163 gives a 50ms pulse. */
#define ENERGY_PULSE_DURATION                       130 // -> 30 msec 163  //255 //
//#define ENERGY_PULSE_DURATION                       80

/*! Tiny power levels should not record at all, as they may just be rounding errors,
    noise, or the consumption of the meter itself. This value is the cutoff level,
    in 0.01W increments. */
#define RESIDUAL_POWER_CUTOFF                       50//250

/*! This is a shift value for comparing currents or powers when looking for
    imbalance between live and neutral. 3 give 12.5%. 4 give 6.25%. These are the
    two commonest values to use. The relaxed version is used at low power levels,
    where the values are less accurate, and a tight imbalance check might give false
    results. */
#define PERMITTED_IMBALANCE_FRACTION                4

/*! This is a relaxed version of the permitted imbalance fraction, for use at low
    powers/currents, where the power (and hence imbalance) measurement may be less
    precise. The tighter imbalance measurement may give false results under high
    EMI conditions. */
#define RELAXED_IMBALANCE_FRACTION                  2

/*! This is the number of successive measurement blocks which must agree the
    unbalanced status has changed before we accept it. */
#define PHASE_UNBALANCED_PERSISTENCE_CHECK          5

/*! This enables monitoring of the balance between the current in the live and neutral
    leads, for tamper detection. */
#define POWER_BALANCE_DETECTION_SUPPORT

/*! This is the minimum current level (limp mode) and minimum power level (normal
    mode) at which we will make checks for the earthed condition. Very small
    readings lack the accuracy and resolution needed to make meaningfulF comparisons
    between live and neutral. */
#define PHASE_UNBALANCED_THRESHOLD_CURRENT          500
#define PHASE_UNBALANCED_THRESHOLD_POWER            2000

/*! This selects the operation from current only, when only one lead is
    functioning, and the meter is powered by a parasitic CT supply attached to
    the leads. This is for anti-fraud purposes. Energy is accumulated at the
    highest possible rate, assuming unity power factor, and the nominal voltage */
#undef LIMP_MODE_SUPPORT
/*! If limp mode is supported, these set the voltage thresholds for switching
    bewteen normal mode and limp mode. */
//#define LIMP_MODE_VOLTAGE_THRESHOLD                 50
//#define NORMAL_MODE_VOLTAGE_THRESHOLD               80
/*! If limp mode is supported, this sets the threshold current, in mA, below which we
    no not operate. */
//#define LIMP_MODE_MINIMUM_CURRENT                   800

/*! Normally the meter software only calculates the properly scaled values
    for voltage, current, etc. as these values are needed. This define
    enables additional global parameters, which are regularly updated with
    all the metrics gathered by the meter. This is generally less efficient,
    as it means calculating things more often than necessary. However, some
    may find this easier to use, so it is offered as a choice for the meter
    designer. */
#define PRECALCULATED_PARAMETER_SUPPORT

/*! This switch select the use of current dependant phase correction, to allow
    the use of non-linear CTs. */
#define DYNAMIC_FIR_SUPPORT

/*! This is the number of successive measurement blocks which must agree the
    reversed current status has changed before we accept it. */
#define PHASE_REVERSED_PERSISTENCE_CHECK            1//5

/*! This is the minimum power level at which we will make checks for the reverse
    condition. Very small readings are not a reliable indicator, due to noise. */
#define PHASE_REVERSED_THRESHOLD_POWER              2000//1000 //2000

#define GAIN_STAGES                                 1
#define NEUTRAL_GAIN_STAGES                         1
#define I_HISTORY_STEPS                             2
/*===========================================================================*/
/* MORE OPTIONS */

/*===========================================================================*/
/* DEBUG */ //DUNG DE TEST CHUONG TRINH
#undef TEST
#undef TEST_LOAD_PROFILE //luu value = hour * 60 + minute
//#define DISABLE_SD16 //disable ngat do dem
//#define DEBUG_DTP
//#define DEBUG_LCD
//#define DEBUG_EEPROM_WRITE_TIMES //so lan luu toi da cua EEPROM
//#define DEBUG_IEC62056
//#define DEBUG_OPTICAL
//#define CLKOUT_1HZ_PCF2129_SUPPORT
//#define OFFSET_PCF2129_SUPPORT
        
  #if defined(RF_SUPPORT) || defined(_RF_SLOT_)
////////////////////////////////////////////////////////////////////////////
/*   defined RF MODULE     */
//#define CC1101_MODULE_SUPPORT
#define SI4464_MODULE_SUPPORT
#define SI4463_C2A // Vudh Define de chon SI4463-C2A // quanhdt 20/10/2019 chua co thong tin SI4464

////////////////////////////////////////////////////////////////////////////
/*   define RF protocol    */
#define RF_CPCIT
/*   define RF frequency    */
//#define  FREQ_424MHz
#define  FREQ_408MHz 
//#define  RF_409_125MHZ /// mo ca 2 define FREQ_408MHz+RF_409_125MHZ
//#define RF_409_325MHZ //Vuonglq - thu nghiem 409.125Mhz
//#define FREQ_433MHz
//#define FREQ_421MHz
//#ifdef FREQ_408MHz
//#define CC1101_408MHZ
//#endif
///////////////////////////////////////////////////////////////
#endif // RF_SUPPORT
////////////////////////////////////////////////////////////////////////////
/*   define measurement method    */
        
//#define _ADE7953_
//#define _ADE7758_
//#define _ADE7858_
#if defined(_DT01P_RF_) || defined(_DT01M_RF_)
#define _TI_MEASURE_1P_
#elif (defined(_DT03P_RF_) || defined(_DT03M_RF_)) && defined(__MSP430__)
#define _TI_MEASURE_3P_
#elif (defined(_DT03P_RF_) || defined(_DT03M_RF_)) && defined(__PIC24FJxxxGA410__)



#define ENERGY_MEASUREMENT_SUPPORT
#define _ADE78xx_
//#define ADE7858_SUPPORT

#ifndef ADE7858_SUPPORT
#define ADE7880_SUPPORT
#endif
#define ADE7858_POWER_CONTROL_SUPPORT

//#define CUSTOMER_DEFINED_REGS_SUPPORT    //da dinh nghia trong function-dt03mrf - vuonglq 19-6-2019
#define SAVE_DATA_THRESHOLD                 5000 // 0.5kWh luu 1 lan 5000
#endif

#endif 