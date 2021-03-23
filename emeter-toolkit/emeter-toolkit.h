
//  $Id: emeter-toolkit.h,v 1.14 2007/08/07 05:53:42 a0754793 Exp $
//
//--------------------------------------------------------------------------

/*! \file */
#if !defined(_EMETER_TOOLKIT_H_)
#define _EMETER_TOOLKIT_H_

#include <isr_compat.h>

#define __inline__ inline
#define __uninitialized__ /**/


#if defined(__MSP430_HAS_LCD4__)  ||  defined(__MSP430_HAS_LCD_A__)
#define SUPPORT_INTERNAL_LCD    1
#define SUPPORT_LCD_MODULE      0
#else
#define SUPPORT_INTERNAL_LCD    0
#define SUPPORT_LCD_MODULE      1
#endif


#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE (!FALSE)
#endif

#define BUTTON_PERSISTENCE_CHECK    60

#define DEBOUNCE_JUST_RELEASED      0
#define DEBOUNCE_JUST_HIT           1
#define DEBOUNCE_RELEASED           2
#define DEBOUNCE_HIT                3

typedef struct rtc_s
{
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t sumcheck;
} rtc_t;


typedef uint8_t lcd_cell_t;

/* lcd_cells is the number of character positions in the main body of the LCD display */
//extern const int lcd_cells;
/* lcd_pos_base is the position of the first character on the display in the LCD memory */
//extern const int lcd_pos_base;
/* lcd_pos_step is 1 if increasing LCD memory locations move to the right on the display.
   It is -1 if they move to the left. */
//extern const int lcd_pos_step;

/* Two patterns for LCDs are widely useful, and do not depend on the way segments are
   allocated. Define them here. */
#if !defined(CHAR_SPACE)
#define CHAR_SPACE  0x00
#endif
#if !defined(CHAR_ALL)
#define CHAR_ALL    0xFF
#endif

extern int16_t Q1_15_mul(int16_t operand1, int16_t operand2);
extern int16_t Q1_15_mulr(int16_t operand1, int16_t operand2);
extern int16_t Q1_15_mulq(int16_t operand1, int16_t operand2);
extern void tpd_gen(void);
extern int32_t imul16(int16_t operand1, int16_t operand2);

/*! \brief Find the square root of a 32 bit integer. The result is a 16.16 bit fractional integer.
    \param x The value for which the square root is required.
    \return The square root in the form 16 integer bits : 16 fractional bit.
*/
extern int32_t isqrt32(int32_t x);


/*! \brief Find the square root of a 32 bit integer. The result is a 16 bit integer.
    \param x The value for which the square root is required.
    \return The square root, as a 16 bit integer.
*/
extern int16_t isqrt32i(int32_t x);

/*! \brief Remove the DC content from a signal.
    \param p A pointer to a running DC estimation. This should be zeroed before the first call to dc_filter.
    \param x A signal sample to be filtered.
*/

extern int16_t dc_filter(int32_t *p, int16_t x);

/*! \brief Convert a 16 bit unsigned integer to nibble packed BCD.
    \param bcd The buffer which will contain the BCD result.
    \param bin The integer value to be converted.
*/

extern void bin2bcd16(uint8_t bcd[3], uint16_t bin);
/*! \brief Convert a 32 bit unsigned integer to nibble packed BCD.
    \param bcd The buffer which will contain the BCD result.
    \param bin The integer value to be converted.
*/
extern void bin2bcd32(uint8_t bcd[5], uint32_t bin);

extern const lcd_cell_t lcd_digit_table[16];
extern const lcd_cell_t char_minus;

extern void LCDinit(void);
/*
extern void LCDsleep(void);
extern void LCDawaken(void);
extern void LCDchars(const uint8_t *s, int pos, int len);
extern void LCDchar(uint16_t ch, int pos);
extern void LCDmodify_char(uint16_t ch, int pos, int on);

extern void LCDdec16(int16_t value, int pos, int digits, int after);
extern void LCDdec32(int32_t value, int pos, int digits, int after);
extern void LCDdecu16(uint16_t value, int pos, int digits, int after);
extern void LCDdecu32(uint32_t value, int pos, int digits, int after);
*/
extern int debounce(uint8_t *deb, uint8_t state);

extern int16_t rand16(void);

extern int16_t dds(int *phase_acc, int phase_rate);
extern int16_t dds_offset(int phase_acc, int phase_offset);

extern const int cos_table[];

extern int bump_rtc(void);
extern void set_rtc_sumcheck(void);
extern int check_rtc_sumcheck(void);
extern int weekday(void);

extern rtc_t rtc;
extern int32_t time_to_next_hop;

extern void flash_write_int8(int8_t *ptr, int8_t value);
extern void flash_write_int16( int16_t *ptr, int16_t value);
extern void flash_write_int32( int32_t *ptr, int32_t value);
extern void flash_memcpy( char *ptr, char *from, int len);
extern void flash_clr( int *ptr);
extern void flash_secure(void);
extern void flash_replace16(int16_t *ptr, int16_t word);
extern void flash_replace32(int32_t *ptr, int32_t word);

extern void host_hex16(uint16_t value);
extern void host_hex32(uint32_t value);
extern void host_dec16(int16_t value);
extern void host_dec32(int32_t value);
extern void host_decu16(uint16_t value);
extern void host_decu32(uint32_t value);
extern int hex2ASCII(int hex);
extern void host_char(char ch);
extern void host_str(const char *s);

//extern int iicEEPROM_read(uint16_t addr, void *dat, int len);
//extern int iicEEPROM_write(uint16_t addr, void *dat, int len);
//extern int iicEEPROM_init(void);

#if defined(BCSCTL1_)  &&  defined(TACCR0_)
extern void set_dco(int freq);
#endif

/* AQ430 and IAR cannot handle int64_t data type. GNU can, but it
   wastes some memory when we are accumulating things only a little
   longer than 32 bits. Use some simple functions to achieve some
   basic handling of a 48 bit int data type. This is stored as a
   3 element int16_t array. */

/* If an accumulated value in one of our 48 bit ints is composed of
   many 32 bit values, then dividing by the number of values returns
   us to a 32 bit value. 48/16 => 32 division is, therefore, ideal for
   scalar dot product handling. */
int32_t div48(register int16_t x[3], register int16_t y);

/* A 16 bit into 48 bit divide, with upwards preshifting of the 48 bit
   number. */
int32_t div_sh48(register int16_t x[3], int sh, register int16_t y);

/* Multiply an int32_t by an int16_t, and return the top 32 bits of the
   48 bit result. */
int32_t mul48(int32_t x, int16_t y);

void shift48(register int16_t x[3], register int how_far);

static __inline__ void transfer48(register int16_t y[3], register int16_t x[3])
{
    y[2] = x[2];
    y[1] = x[1];
    y[0] = x[0];
    x[0] =
    x[1] =
    x[2] = 0;
}

static __inline__ void assign48(register int16_t y[3], register int16_t x[3])
{
    y[2] = x[2];
    y[1] = x[1];
    y[0] = x[0];
}

void accum48(register int16_t x[3], register int32_t y);


static void __inline__ brief_pause(register unsigned int n)
{
    while (n > 0)
    {
        n--;
        _NOP();
    }

}

static void __inline__ restart_watchdog(void)
{
    WDTCTL = (WDTCTL & 0xFF) | WDTPW | WDTCNTCL;
}

#endif
