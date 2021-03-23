#ifndef LIBRARY_H
#define LIBRARY_H
/*===========================================================================*/
/* INCLUDES                                                                */
/*===========================================================================*/
#include <stdint.h>
/*===========================================================================*/
/* 1. METER TYPE                                                                */
/*===========================================================================*/
// #define _DT01P40_RF_				
//#define _DT01M_RF_
//#define _DT01P_RF_
//#define _DT01PP_RF_
//#define _DT_EXT_RF_
//#define _DT03P_RF_
#define _DT03M_RF_
//#define _ROUTER1P_
//#define _ROUTER3P_
//#define _DCU_
//#define _IHD_
//#define _HU_
//#define _RF_SLOT_
//>>define here!<<//

//-----------------------------------//
/*===========================================================================*/
/* 2. DEFINE MCU                                                               */
/*===========================================================================*/
#ifdef _DT01M_RF_
	#define __MSP430__
#endif
#ifdef _DT01P_RF_
    //#define __MSP430__ //TI
    #ifndef __MSP430__
        //Luu Y: Khi define nhu sau khong dong thoi mo 2 project su dung XC8 va XC16!!!
    #warning "Just OPEN project using XC8!!!"
        #if defined(_16LF1947)|| defined(_16F1947)//|| defined(_16F1946)
            #define _PIC16XX194Y_
        #elif defined(_16F19197)||defined(_16LF19197)
            #define _PIC16XX1919Y_
        #endif
    #endif
#endif
#ifdef _DT01PP_RF_
	#define __MSP430__
#endif
#ifdef _DT_EXT_RF_
	#define __MSP430__
#endif
#ifdef _DT01PP_RF_
	#define __MSP430__
#endif
#ifdef _DT03P_RF_
	#define __MSP430__
#endif
#ifdef _DT03M_RF_
	//#define __MSP430__
	#if defined(__PIC24FJ256GA410__)
	#define __PIC24FJxxxGA410__
	#endif
    
#endif
#ifdef _ROUTER1P_
//>>define here!<<//
#endif
#ifdef _ROUTER3P_
//>>define here!<<//
#endif
#ifdef _DCU_
//>>define here!<<//
#endif
#ifdef _IHD_
//>>define here!<<//
#endif
#ifdef _HU_
//>>define here!<<//
#endif
#ifdef _RF_SLOT_
//>>define here!<<//
#endif
/*===========================================================================*/
/* 3. DEFINE CONG TO, CAP DONG VA HANG SO XUNG                              */
/*===========================================================================*/
#ifdef _DT01M_RF_
	//#define DT01M_5_10A
	#define DT01M_5_80A // vinh test

	#ifdef DT01M_5_10A
		#define PHASE_ENERGY_PULSES_PER_KW_HOUR             1000
		#define TOTAL_ENERGY_PULSES_PER_KW_HOUR             5000//>>insert here!<<//
		#define ENERGY_PER_PULSE                            2//>>insert here!<<//
		#define dW_HOUR_PER_PULSE                           ENERGY_PER_PULSE
		//#define mWh_PER_PULSE                               ENERGY_PER_PULSE
		#define THRESHOLD_KWH_BACKUP        				5000//>>insert here!<<//
		#define REGION_BACKUP_MAX           				8//>>insert here!<<//
	#elif defined(DT01M_5_80A)
		#define PHASE_ENERGY_PULSES_PER_KW_HOUR             1000
		#define TOTAL_ENERGY_PULSES_PER_KW_HOUR             1000//>>insert here!<<//
		#define ENERGY_PER_PULSE                            10//>>insert here!<<//
		#define dW_HOUR_PER_PULSE                           ENERGY_PER_PULSE
		//#define mWh_PER_PULSE                               ENERGY_PER_PULSE
		#define THRESHOLD_KWH_BACKUP        				35000//>>insert here!<<//
		#define REGION_BACKUP_MAX           				8//>>insert here!<<//	
	#else
			#error "Dinh nghia loai cong to!"
	#endif 
#endif //_DT01M_RF_

#ifdef _DT01P_RF_
	//#define DT01P_5_60A
	//#define DT01P_5_80A
	//#define DT01P_10_40A
	#define DT01P_20_80A

	#if defined(DT01P_5_80A) || defined(DT01P_20_80A)
		#define TOTAL_ENERGY_PULSES_PER_KW_HOUR             1000 //1600
		#define dW_HOUR_PER_PULSE                           10
	//    #define mWh_PER_PULSE                               (1000/RESOLUTION_TRANSFORMER)
        #define REGION_BACKUP_MAX                           6
    #ifdef __PICC__
        #define IMPULSE_CONST   10
    #endif
	#elif defined(DT01P_5_10A)
		#define TOTAL_ENERGY_PULSES_PER_KW_HOUR             5000
		//#define dW_HOUR_PER_PULSE                         2
		#define mWh_PER_PULSE                               (200/RESOLUTION_TRANSFORMER)
        #define REGION_BACKUP_MAX                           6
	#endif

	#if defined(mWh_PER_PULSE)
	#define RESOLUTION_ENERGY_UNIT               1000000   // 6 chu so thap phan khi doi tu mWh ra kWh
	#define MAX_DECIMAL_ENERGY                   6   
	#elif defined(dW_HOUR_PER_PULSE)
	#define RESOLUTION_ENERGY_UNIT               100   // 4 chu so thap phan khi doi tu dWh ra kWh
	#define MAX_DECIMAL_ENERGY                   2   
	#endif						

#endif //_DT01P_RF_

#ifdef _DT01PP_RF_
	//#define DT01P_5_60A
	//#define DT01P_5_80A
	//#define DT01P_10_40A
	#define DT01P_20_80A

	#if defined(DT01P_5_80A) || defined(DT01P_20_80A)
		#define TOTAL_ENERGY_PULSES_PER_KW_HOUR             1000 //1600
		#define dW_HOUR_PER_PULSE                           10
	//    #define mWh_PER_PULSE                               (1000/RESOLUTION_TRANSFORMER)
        #define REGION_BACKUP_MAX                           6
	#elif defined(DT01P_5_10A)
		#define TOTAL_ENERGY_PULSES_PER_KW_HOUR             5000
		//#define dW_HOUR_PER_PULSE                           2
		#define mWh_PER_PULSE                               (200/RESOLUTION_TRANSFORMER)
        #define REGION_BACKUP_MAX                           6
	#endif

	#if defined(mWh_PER_PULSE)
	#define RESOLUTION_ENERGY_UNIT               1000000   // 6 chu so thap phan khi doi tu mWh ra kWh
	#define MAX_DECIMAL_ENERGY                   6   
	#elif defined(dW_HOUR_PER_PULSE)
	#define RESOLUTION_ENERGY_UNIT               100   // 4 chu so thap phan khi doi tu dWh ra kWh
	#define MAX_DECIMAL_ENERGY                   2   
	#endif		
#endif //_DT01PP_RF_

#ifdef _DT_EXT_RF_
//>>code here!<<//
#endif //_DT_EXT_RF_

#ifdef _DT03P_RF_
    #define DT03P_10_100A
    //#define DT03P_5_10A
    //===================================//
	#ifdef DT03P_5_10A
		#define PHASE_ENERGY_PULSES_PER_KW_HOUR             5000
		#define TOTAL_ENERGY_PULSES_PER_KW_HOUR             5000
		#define ENERGY_PER_PULSE                            2 //200 //thaodtn: tam thoi
		#define dW_HOUR_PER_PULSE                           ENERGY_PER_PULSE
		//#define mWh_PER_PULSE                               ENERGY_PER_PULSE
		#define THRESHOLD_KWH_BACKUP        				5000
		#define REGION_BACKUP_MAX           				8
	#elif defined (DT03P_10_100A)
		#define PHASE_ENERGY_PULSES_PER_KW_HOUR             1000
		#define TOTAL_ENERGY_PULSES_PER_KW_HOUR             1000
		#define ENERGY_PER_PULSE                            10 //200 //thaodtn: tam thoi
		#define dW_HOUR_PER_PULSE                           ENERGY_PER_PULSE
		//#define mWh_PER_PULSE                               ENERGY_PER_PULSE
		#define THRESHOLD_KWH_BACKUP        				120000
		#define REGION_BACKUP_MAX           				8
	#else
			#error "Dinh nghia loai cong to!"
	#endif
    //====================================================//
    #if defined(mWh_PER_PULSE)
    #define RESOLUTION_ENERGY_UNIT               1000000   // 6 chu so thap phan khi doi tu mWh ra kWh
    #define MAX_DECIMAL_ENERGY                   6   
    #elif defined(dW_HOUR_PER_PULSE)
    #define RESOLUTION_ENERGY_UNIT               10000   // 4 chu so thap phan khi doi tu dWh ra kWh
    #define MAX_DECIMAL_ENERGY                   4   
    #endif

#endif //_DT03P_RF_

#ifdef _DT03M_RF_
	//#define DT03M_1_12A //
	//#define DT03M_5_10A    
	#define DT03M_10_100A 
	//===================================//
	#ifdef DT03M_1_12A
		#define PHASE_ENERGY_PULSES_PER_KW_HOUR             5000
		#define TOTAL_ENERGY_PULSES_PER_KW_HOUR             5000
		#define ENERGY_PER_PULSE                            40 //200 //thaodtn: tam thoi
	#ifdef __PIC24FJxxxGA410__ //namhv: ADE su dung mWh_PER_PULSE
        #define mWh_PER_PULSE                               40
    #else
		#define dW_HOUR_PER_PULSE                           ENERGY_PER_PULSE
        //#define mWh_PER_PULSE                               ENERGY_PER_PULSE
    #endif
		#define THRESHOLD_KWH_BACKUP        				5000//2500//250000 //0.25kWh cho cong to DT03M05
		#define REGION_BACKUP_MAX           				8
	#elif defined (DT03M_5_10A)
		#define PHASE_ENERGY_PULSES_PER_KW_HOUR             5000
		#define TOTAL_ENERGY_PULSES_PER_KW_HOUR             5000
		#define ENERGY_PER_PULSE                            2 //200 //thaodtn: tam thoi
	#ifdef __PIC24FJxxxGA410__ //namhv: ADE su dung mWh_PER_PULSE
        #define mWh_PER_PULSE                               (ENERGY_PER_PULSE*100)
    #else
		#define dW_HOUR_PER_PULSE                           ENERGY_PER_PULSE
        //#define mWh_PER_PULSE                               ENERGY_PER_PULSE
    #endif 
		#define THRESHOLD_KWH_BACKUP        				5000//2500//250000 //0.25kWh cho cong to DT03M05
		#define REGION_BACKUP_MAX           				8
	#elif defined (DT03M_10_100A)
		#define PHASE_ENERGY_PULSES_PER_KW_HOUR             1000
		#define TOTAL_ENERGY_PULSES_PER_KW_HOUR             1000 //1600
		#define ENERGY_PER_PULSE                            10 //1000 //thaodtn: tam thoi
    #ifdef __PIC24FJxxxGA410__ //namhv: ADE su dung mWh_PER_PULSE
        //#define mWh_PER_PULSE                               (ENERGY_PER_PULSE*100) //CHUYEN SANG 4 SO THAP PHAN
        //#define dW_HOUR_PER_PULSE                           ENERGY_PER_PULSE
    #else
		//#define dW_HOUR_PER_PULSE                           ENERGY_PER_PULSE
        //#define mWh_PER_PULSE                               ENERGY_PER_PULSE
    #endif
		
		#define THRESHOLD_KWH_BACKUP        				120000//2500//250000 //0.25kWh cho cong to DT03M05
		#define REGION_BACKUP_MAX           				8
	#else
			#error "Dinh nghia loai cong to!"
	#endif
    //====================================================//
    #if defined(mWh_PER_PULSE)
        #define RESOLUTION_ENERGY_UNIT               1000000   // 6 chu so thap phan khi doi tu mWh ra kWh
        #define MAX_DECIMAL_ENERGY                   6   
        #define RESOLUTION_TO_dWh                    1
    #elif defined(dW_HOUR_PER_PULSE)
        #define RESOLUTION_ENERGY_UNIT               10000   // 4 chu so thap phan khi doi tu dWh ra kWh
        #define MAX_DECIMAL_ENERGY                   4 
        #define RESOLUTION_TO_dWh                    100
    #else 
        #define RESOLUTION_ENERGY_UNIT               10000   // 4 chu so thap phan khi doi tu dWh ra kWh
        #define MAX_DECIMAL_ENERGY                   4 
        #define RESOLUTION_TO_dWh                    100
    #endif
#endif //_DT03M_RF_
/*===========================================================================*/
/* 4. DEFINE THIET BI TRUYEN THONG                                          */
/*===========================================================================*/
#ifdef _ROUTER1P_ 
//>>define PCB here!<<//
#endif //_ROUTER1P_

#ifdef _ROUTER3P_
//>>define PCB here!<<//
#endif //_ROUTER3P_

#ifdef _DCU_
//>>define PCB here!<<//
#endif //_DCU_

#ifdef _IHD_
//>>define PCB here!<<//
#endif //_IHD_

#ifdef _HU_
//>>define PCB here!<<//
#endif //_HU_

#ifdef _RF_SLOT_
	///#define PCB_HURFHANDHELD_V211_PIC18
	//#define PCB_MULTIMETER_RF
	//#define PCB_ELSETR_RF
#define _EMEC_RF_SLOT_M00_V101
	//#define _EMEC_RF_SLOT_M00_V201 
	//#define _EMEC_RF_SLOT_M00_V401
	
#endif //_RF_SLOT_

/*===========================================================================*/
/* 5. DEFINE PCB VA LCD                                                 	 */
/*===========================================================================*/
#ifdef _DT01M_RF_
	//#define _DT01M_PCB_V3_0_  //ten version pcb cu  
	//#define _DT01MRF_PCB_TI_V12_
	#define _DT01MRF_PCB_TI_S8M_T_V13_//TI, Segment 8COM, Transformers // ten pcb moi

	#define _LCD_M0754_ //Blaze 3 pha COM8 (ko dung PCF)
	#ifdef _LCD_M0754_
		//#define _LCD_M0754_V20_	
		#define _LCD_M0754_V30_
	#endif
	//#define _LCD_L0712_  //Blaze 4COM
	//#define _LCD_OST11295_  //3 pha OSWEL 4COM

	//#define _LCD_M0753_PCF8545_ // 4 COM co PCF8545
	//#define _LCD_M0754v2_PCF8545_ // 8 COM v2 co PCF8545
	//#define _LCD_M0754v3_PCF8545_ // 8 COM v3 co PCF8545
	//
	//#define _LCD_MATRIX_16x02_4BIT_ //cu LCD_MATRIX_SUPPORT  //LCD1602
	//#define _LCD_MATRIX_16x02_8BIT_ //cu LCD_MATRIX_SUPPORT  //LCD1602
	//#define _LCD_MATRIX_128x64_ //cu LCD_MATRIX_SUPPORT  //LCD1602
//===============================================//
    #if defined(DT01M_5_80A)
        #define PCB_VERSION         014 //dt01m-rf chua dung bien nay ==> dang dung bien pcb_version
        #define FW_VERSION          246 //khi thay doi version thi phai thay doi them mang COMMUNICATION_FIRMWARE
        #define FW_VERSION_TEST     01 //ban chinh thuc = 0, cac ban thu nghiem # 0
        #ifdef IEC62056_21_EVN_SUPPORT
            //const char DEVICE_VERSION[] = {"DT01M80.ver246"}; //chieu dai co dinh la 14
            #define COMMUNICATION_FIRMWARE  "DT01M10.ver246"
        #else
            //const char DEVICE_VERSION[] = {"01mvers246"};
            #define COMMUNICATION_FIRMWARE  "01mvers246"
        #endif
    #elif defined(DT01M_5_10A)
        #define PCB_VERSION         014 //dt01m-rf chua dung bien nay ==> dang dung bien pcb_version        
        #define FW_VERSION          246 // khi thay doi version thi phai thay doi them mang COMMUNICATION_FIRMWARE
        #define FW_VERSION_TEST     01 //ban chinh thuc = 0, cac ban thu nghiem # 0
        #ifdef IEC62056_21_EVN_SUPPORT
            //const char DEVICE_VERSION[] = {"DT01M10.ver246"}; //chieu dai version co dinh la 14 ki tu ,dung cho giao tiep
            #define COMMUNICATION_FIRMWARE  "DT01M10.ver246" //chieu dai version co dinh la 14 ki tu ,dung cho giao tiep
        #else
            //const char DEVICE_VERSION[] = {"01mvers246"};
            #define COMMUNICATION_FIRMWARE  "01mvers246" //chieu dai version co dinh la 10 ki tu ,dung cho giao tiep
        #endif
    #endif

    #define DAY_PCB         20 // ngay 10
    #define MONTH_PCB       06 // thang 10
    #define YEAR_PCB        17 // nam 2016

    #include "functions-dt01mrf.h"
#endif //_DT01M_RF_

#ifdef _DT01P_RF_
#ifdef __MSP430__
	//#define _DT01PRF_PCB_TI_2014_ //dd-mm-yy
	//#define _DT01PRF_PCB_TI_2015_ //dd-mm-yy
	//#define _DT01PRF_PCB_TI_2016_ //dd-mm-yy // PCB_DT01P80_2016//
        //#define PCB_EXT_V2
	//#define _DT01P80_EXP_PCB_TI_S8_T_V21_
	//#define _DT01P80_EXP_PCB_PIC_S4_T_V10_
	//#define _DT01P80_PCB_TI_S8_T_V23_
	#define _DT01P80_PCB_TI_S4_T_V24_ //PCB cho FW v604 ban giao xdt
#else
	//#define _DT01PRF_PCB_PIC_V10_ //de danh cho Khue
	//#define EMEC_PIC1947_20180106 // cap nhat lai PCB PICADE
    //#define _DT01PRF_M_S4_T_V72_ //PDM pic16F19197_test
    #define _DT01PRF_M_S4_T_V80_ //PDM pic16F19197
#endif

    //===============================================//
	#if defined(_DT01P80_PCB_TI_S8_T_V23_)
        #define _LCD_M0752_ //Blaze 1 pha 8COM (ko dung PCF)    
#elif defined(_DT01PRF_M_S4_T_V72_) || defined(_DT01PRF_M_S4_T_V80_)
        #define _LCD_OST11088S05_ //DT01P xanh (DT01P40_RF)
    #else	
        #define _LCD_OST11248_  //1 pha OSWEL LCD4COM
    #endif
    //===============================================//
#ifdef __MSP430__
    #define FW_VERSION     604 //khi thay doi version thi phai thay doi them mang COMMUNICATION_FIRMWARE 
    #define FW_VERSION_TEST 0 //ban chinh thuc = 0, cac ban thu nghiem # 0
#elif defined(_PIC16XX1919Y_)
    #define FW_VERSION     407 //khi thay doi version thi phai thay doi them mang COMMUNICATION_FIRMWARE 
    #define FW_VERSION_TEST 1 //ban chinh thuc = 0, cac ban thu nghiem # 0
#endif
  //===============================================//
    #ifdef IEC62056_21_EVN_SUPPORT //Theo VERSION FIRMWARE!!!
        #ifdef __MSP430__
        //const char DEVICE_VERSION[] = {"DT01PRF.ver604"}; //chieu dai co dinh la 14
        #define COMMUNICATION_FIRMWARE  "DT01PRF.ver604"
        #else
        #define COMMUNICATION_FIRMWARE  "DT01PRF.ver407"
        #endif
	#else
        #ifdef __MSP430__
        //const char DEVICE_VERSION[] = {"01pvers604"};
        #define COMMUNICATION_FIRMWARE  "01pvers604"
        #else
        //const char DEVICE_VERSION[] = {"01pvers407"};
        #define COMMUNICATION_FIRMWARE  "01pvers407"
        #endif
    #endif
  //===============================================//  
    #if defined(_DT01PRF_PCB_TI_2016_)
        #define DAY_PCB        12 // ngay 12
        #define MONTH_PCB      11 // thang 11
        #define YEAR_PCB       15 // nam 2015
    #elif defined(PCB_EXT_V2)
        #define DAY_PCB        26 // ngay 12
        #define MONTH_PCB      9 // thang 11
        #define YEAR_PCB       15 // nam 2015
    #elif defined(_DT01P80_EXP_PCB_TI_S8_T_V21_)
        #define DAY_PCB        28 // ngay 12
        #define MONTH_PCB      12 // thang 11
        #define YEAR_PCB       16 // nam 2015
    #elif defined(_DT01P80_PCB_TI_S8_T_V23_)
        #define DAY_PCB        15 // ngay 15
        #define MONTH_PCB      10 // thang 10
        #define YEAR_PCB       18 // nam 2018 
    #elif defined(_DT01P80_PCB_TI_S4_T_V24_)
        #define DAY_PCB        24 // ngay 15
        #define MONTH_PCB      10 // thang 10
        #define YEAR_PCB       18 // nam 2018
    #elif defined(_DT01PRF_M_S4_T_V72_)
        #define DAY_PCB        22 // ngay 22
        #define MONTH_PCB      07 // thang 07
        #define YEAR_PCB       19 // nam 2019
    #elif defined(_DT01PRF_M_S4_T_V80_)
        #define DAY_PCB        19 // ngay 19
        #define MONTH_PCB      11 // thang 11
        #define YEAR_PCB       19 // nam 2019
    #else
        // neu PCB loai 2014 thi 25/02/2014
        #define DAY_PCB        9 // ngay 09
        #define MONTH_PCB      6 // thang 06
        #define YEAR_PCB       15 // nam 2015
    #endif
    //===============================================//
    #if (MONTH_PCB > 9) 
    #define PCB_VERSION ((1 << 15) +  (DAY_PCB*1000) + ((MONTH_PCB%10)*100) + YEAR_PCB)
    #else 
    #define PCB_VERSION ((DAY_PCB*1000) + ((MONTH_PCB%10)*100) + YEAR_PCB)
    #endif
  //===============================================//
    #include "functions-dt01prf.h"
  //===============================================//
#endif //_DT01P_RF_

#ifdef _DT01PP_RF_
	#define _DT01PPRF_PCB_TI_V10_
#endif //_DT01PP_RF_

#ifdef _DT_EXT_RF_
#define _DTEXTRF_PCB_PIC_V10_
#endif //_DT_EXT_RF_

#ifdef _DT03P_RF_
//===========================DEFINE PCB DT03P-RF ===============================
//#define _DT03PRF_PCB_TI_2014_
//#define _DT03PRF_PCB_TI_2015_ //20-11-2015, thay cho _PCB_FOR_LCD_OST11295_ cu
//#define _DT03PRF_PCB_TI_S4B_T_V10_ //_PCB_FOR_LCD_BLAZE_V1_
//#define _DT03PRF_PCB_TI_S8PCF_T_V10_ //_PCB_DT03P_TE3023_ //24/04/2016
//#define _DT03PRF_PCB_ICDREC_S8PCF_T_V10_
#define _DT03PRF_PCB_TI_S4_T_V271_ //02/11/2016 EMEC DT03P-RF T.S4.T V2.7.1
//===========================DEFINE PCB DT03P05 ================================
//#define _DT03PRF_PCB_TI_2012_ //"CPC IT V01 2012" cong to vo xanh
//#define _DT03PRF_PCB_TI_2014_ //"IT DT03M 2013.03" cong to vo xanh
//#define _DT03P05_PCB_TI_2014_
//#define _DT03P05_PCB_TI_2015_
//#define _PCB_3P05_2015_
//#define _DT03P05_PCB_TI_S4_T_V272_ //01/01/2017 EMEC DT03M-RF T.S4.S V2.72
//=============================================================================//
//============= DEFINE LCD =============//
#define _LCD_OST11295_  //3 pha OSWEL 4COM
//======================================//
    #if defined (DT03P_10_100A)
        #define FW_VERSION              319 //khi thay doi version thi phai thay doi them mang COMMUNICATION_FIRMWARE
        #define PCB_VERSION             272 
        #define FW_VERSION_TEST         01   //ban chinh thuc = 0, cac ban thu nghiem # 0
        #define DAY_PCB                 12
        #define MONTH_PCB               10
        #define YEAR_PCB                18
    #elif defined (DT03P_5_10A)
        #define FW_VERSION              319 //khi thay doi version thi phai thay doi them mang COMMUNICATION_FIRMWARE
        #define PCB_VERSION             273
        #define FW_VERSION_TEST         0   //ban chinh thuc = 0, cac ban thu nghiem # 0
        #define DAY_PCB                 6
        #define MONTH_PCB               8
        #define YEAR_PCB                15 
    #endif
//======================================//
    #ifdef IEC62056_21_EVN_SUPPORT
        #define COMMUNICATION_FIRMWARE  "DT03P10.ver330" //chieu dai version co dinh la 14 ki tu ,dung cho giao tiep
    #else
        #define COMMUNICATION_FIRMWARE  "version411" //chieu dai version co dinh la 14 ki tu ,dung cho giao tiep
    #endif

    #include "functions-dt03prf.h"
#endif //_DT03P_RF_

#ifdef _DT03M_RF_
//============= DEFINE PCB =============//
	//#define _DT03MRF_PCB_TI_2014_		    //PCB DANH CHO V2.6 cpc TRO XUONG
	//#define _DT03MRF_PCB_TI_2016_
	//#define _DT03MRF_PCB_TI_S8_S_V271_    //dung PCF cho LCD 8COM (HCM)
	//#define _DT03MRF_PCB_TI_S4_S_V272_ 	//PCB san xuat 2017
	//#define _DT03MRF_PCB_PIC_AS8_S_V10_   //PCB PIC ADE LCD 8COM v1.0
	//#define _DT03MRF_PCB_PIC_AMS_S_V10_
	//#define _DT03MRF_PCB_PIC_AS8_S_V12_
	//#define _DT03MRF_PCB_TI_S4_S_V273_  //PCB DANH CHO V2.7 cpc TRO LEN
	//#define _DT03MRF_PCB_PIC_AS8_S_V20_
    #define _DT03MRF_PCB_PIC_AS8_S_V22_     // quanhdt : 05/02/2021
//============= DEFINE LCD =============//
	#if defined(__PIC24FJxxxGA410__)
		//#define _LCD_OST11295_  //3 pha OSWEL 4COM	
		#define _LCD_M0754_ //Blaze 3 pha COM8 (ko dung PCF)
		#if defined (_LCD_M0754_) //LCD DUNG CHO PIC
			//#define _LCD_M0754_V20_
			#define _LCD_M0754_V30_
		#endif
	#elif defined (__MSP430__)
		#define _LCD_OST11295_  //3 pha OSWEL 4COM dung CPC	
		//#define _LCD_M0753_
		//#define _LCD_M0753_V1_ 
		//#define _LCD_M0753_V2_ //Su dung de san xuat HCM
	#else
		#error "Dinh nghia loai MCU cho cong to"
	#endif
    //==========DEFINE VERSION DT03M-RF=========//
    #if defined(_DT03MRF_PCB_TI_2014_)
        #define PCB_VERSION                260
        #define FW_VERSION                 253 //khi thay doi version thi phai thay doi them mang COMMUNICATION_FIRMWARE
        #define FW_VERSION_TEST            01   //ban chinh thuc = 0, cac ban thu nghiem # 0
    #endif
    #if defined(_DT03MRF_PCB_TI_S4_S_V272_)
        #define PCB_VERSION                272
        #define FW_VERSION                 400 //khi thay doi version thi phai thay doi them mang COMMUNICATION_FIRMWARE
        #define FW_VERSION_TEST            0   //ban chinh thuc = 0, cac ban thu nghiem # 0
    #endif
    #if defined(_DT03MRF_PCB_TI_S4_S_V273_)
        #define PCB_VERSION                273
        #define FW_VERSION                 254 //khi thay doi version thi phai thay doi them mang COMMUNICATION_FIRMWARE
        #define FW_VERSION_TEST            01   //ban chinh thuc = 0, cac ban thu nghiem # 0
    #endif
    #if defined(_DT03MRF_PCB_PIC_AS8_S_V20_)
        #define PCB_VERSION                200
        #define FW_VERSION                 300 //khi thay doi version thi phai thay doi them mang COMMUNICATION_FIRMWARE
        #define FW_VERSION_TEST            12   //ban chinh thuc = 0, cac ban thu nghiem # 0
    #endif
    #if defined(_DT03MRF_PCB_PIC_AS8_S_V22_)  // quanhdt 11/03/2021
        #define PCB_VERSION                220
        #define FW_VERSION                 300 //khi thay doi version thi phai thay doi them mang COMMUNICATION_FIRMWARE
        #define FW_VERSION_TEST            12   //ban chinh thuc = 0, cac ban thu nghiem # 0
    #endif
    //=================================================================//
    #define DAY_PCB                     26
    #define MONTH_PCB                   9
    #define YEAR_PCB                    16 // nam 2016
    //=================================================================//
    #ifdef IEC62056_21_EVN_SUPPORT
        #if defined(DT03M_5_10A)
            //const char DEVICE_VERSION[] = {"DT03M05.ver400"}; //chieu dai version co dinh la 10 ki tu ,dung cho giao tiep
            #define COMMUNICATION_FIRMWARE  "DT03M05.ver400" //chieu dai version co dinh la 14 ki tu ,dung cho giao tiep
        #elif defined(DT03M_10_100A)
            //const char DEVICE_VERSION[] = {"DT03M10.ver400"};
            #define COMMUNICATION_FIRMWARE  "DT03M10.ver400" //chieu dai version co dinh la 14 ki tu ,dung cho giao tiep
        #elif defined(DT03M_1_12A)
            //const char DEVICE_VERSION[] = {"DT03M01.ver400"};
            #define COMMUNICATION_FIRMWARE  "DT03M01.ver400" //chieu dai version co dinh la 14 ki tu ,dung cho giao tiep
        #endif
    #else
        //const char DEVICE_VERSION[] = {"version254"}; //chieu dai version co dinh la 10 ki tu ,dung cho giao tiep
        //#define COMMUNICATION_FIRMWARE  "version253" //chieu dai version co dinh la 14 ki tu ,dung cho giao tiep
        #define COMMUNICATION_FIRMWARE  "version300" //chieu dai version co dinh la 14 ki tu ,dung cho giao tiep
    #endif
    #include "functions-dt03mrf.h"
#endif //_DT03M_RF_
///////////////////////////////////////////////////////////////
/*Chon chung loai cong to*/
#if defined (_DT03M_RF_)
    #ifdef DT03M_5_10A    
        #define METER_TYPE      305 //DT03M05
    #elif defined DT03M_10_100A 
        #define METER_TYPE      310 //DT03M10
    #elif defined DT03M_1_12A    
        #define METER_TYPE      301 //DT03M01
    #else
        Chon dung chung loai cong to loai cong to - vuonglq- 20200627
    #endif
#elif defined (_DT01M_RF_)
    #ifdef DT01M_5_10A    
        #define METER_TYPE      110 //DT01M10
    #elif defined DT01M_5_80A 
        #define METER_TYPE      180 //DT01M80
    #else
        Chon dung chung loai cong to loai cong to - vuonglq- 20200627
    #endif
#else
    Chon dung chung loai cong to loai cong to - vuonglq- 20200627
#endif
#endif //LIBRARY_H


