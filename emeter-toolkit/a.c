
&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
/*! This union overlays a segment of the info, ensuring correct
   alignment. */
struct info_mem_s
{
    union
    {
        struct nv_parms_s s;
        int8_t x[128];
    } seg_a;
};

************************************************************************
/* The main per-phase non-volatile parameter structure */
__infomem__ const struct info_mem_s nv_parms =
{
    {
    {
        0xFFFF,
        {
            {
                {
                    {DEFAULT_I_RMS_SCALE_FACTOR_A},
                    0,
#if GAIN_STAGES == 1
                    DEFAULT_P_SCALE_FACTOR_A_LOW,
#else
                    {DEFAULT_P_SCALE_FACTOR_A_LOW, DEFAULT_P_SCALE_FACTOR_A_HIGH},
#endif
                    DEFAULT_I_DC_ESTIMATE << 16,
    #if GAIN_STAGES == 1
                    DEFAULT_BASE_PHASE_A_CORRECTION_LOW,
    #else
                    {DEFAULT_BASE_PHASE_A_CORRECTION_LOW, DEFAULT_BASE_PHASE_A_CORRECTION_HIGH},
    #endif
                },

                DEFAULT_V_RMS_SCALE_FACTOR_A,
                DEFAULT_V_DC_ESTIMATE << 16,

            },
#if !defined(SINGLE_PHASE)
            {
                {

                    {DEFAULT_I_RMS_SCALE_FACTOR_B},
                    0,
    #if GAIN_STAGES == 1
                    DEFAULT_P_SCALE_FACTOR_B_LOW,
    #else
                    {DEFAULT_P_SCALE_FACTOR_B_LOW, DEFAULT_P_SCALE_FACTOR_B_HIGH},
    #endif
                    DEFAULT_I_DC_ESTIMATE << 16,

        #if GAIN_STAGES == 1
                    DEFAULT_BASE_PHASE_B_CORRECTION_LOW,
        #else
                    {DEFAULT_BASE_PHASE_B_CORRECTION_LOW, DEFAULT_BASE_PHASE_B_CORRECTION_HIGH},
        #endif
                },
                DEFAULT_V_RMS_SCALE_FACTOR_B,
                DEFAULT_V_DC_ESTIMATE << 16,
            },
            {
                {
                    {DEFAULT_I_RMS_SCALE_FACTOR_C},
                    0,
    #if GAIN_STAGES == 1
                    DEFAULT_P_SCALE_FACTOR_C_LOW,
    #else
                    {DEFAULT_P_SCALE_FACTOR_C_LOW, DEFAULT_P_SCALE_FACTOR_C_HIGH},
    #endif
                    DEFAULT_I_DC_ESTIMATE << 16,
        #if GAIN_STAGES == 1
                    DEFAULT_BASE_PHASE_C_CORRECTION_LOW,
        #else
                    {DEFAULT_BASE_PHASE_C_CORRECTION_LOW, DEFAULT_BASE_PHASE_C_CORRECTION_HIGH},
        #endif
                },
                DEFAULT_V_RMS_SCALE_FACTOR_C,
                DEFAULT_V_DC_ESTIMATE << 16,
            }
        },
#endif
#if defined(NEUTRAL_MONITOR_SUPPORT)
        {
            DEFAULT_I_RMS_SCALE_FACTOR_NEUTRAL,
            0,
            DEFAULT_P_SCALE_FACTOR_NEUTRAL,
            DEFAULT_I_DC_ESTIMATE << 16,
            DEFAULT_NEUTRAL_BASE_PHASE_CORRECTION,
        },
#endif
#if defined(TEMPERATURE_SUPPORT)
        25,
        DEFAULT_TEMPERATURE_OFFSET,
        DEFAULT_TEMPERATURE_SCALING,
#endif

        {
            0,
            0,
            0,
            0,
            0,
            0
        },
        0,
        "",
        "",
        ""
    }
    }
};




~~~~~~~~~~~~~~~~~~~~~~~~~

struct phase_nv_parms_s
{
    /*! \brief The non-volatile information (e.g. calibration parameters) for a current channel. */
    struct current_sensor_nv_parms_s current;
    /*! \brief The calibration scaling factor for the measured RMS voltage. */
    int16_t V_rms_scale_factor;
    dc_estimate_t initial_v_dc_estimate;
};



@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
/*! This structure is an image of the non-volatile calibration parameters
    stored in the info memory. */
struct nv_parms_s
{

    /*! \brief The non-volatile per channel information (e.g. calibration parameters). */
    struct phase_nv_parms_s chan[NUM_PHASES];

#if defined(NEUTRAL_MONITOR_SUPPORT)
    /*! \brief The non-volatile neutral lead information (e.g. calibration parameters). */
    struct current_sensor_nv_parms_s neutral;
#endif
#if defined(TEMPERATURE_SUPPORT)
    /*! \brief The room temperature at the time of calibration, in degrees Celcius */
    uint16_t temperature_at_calibration;
    /*! \brief The DC offset of readings from the temperature sensor, relative to zero Celcius. */
    uint16_t temperature_offset;
    /*! \brief The scaling factor between readings from the temperature sensor, and degrees Celcius. */
    uint16_t temperature_scaling;
#endif

    /*! \brief A snapshot of the meter's RTC, taken at calibration time. If the calibration process
               has correctly set the RTC, this should be a record of when the meter was calibrated. */
    rtc_t rtc_at_calibration;
    /*! \brief Pad to word alignment */
    uint8_t xxx;
    /* Keep these administrative strings an even number of bytes each */
    /*! \brief The serial number of the meter */
    uint8_t serial_number[16 + 2];
    /*! \brief The property number of the meter (see IEC1107). */
    uint8_t property_number[16 + 2];
    /*! \brief The factory number of the meter (see IEC1107). */
    uint8_t factory_number[10 + 2];
};


************************************
/*! This structure holds all the working data for one phase. */
struct phase_parms_s
{

    struct phase_readings_s readings;
    struct phase_metrology_s metrology;
    
#if defined(PER_PHASE_ACTIVE_ENERGY_SUPPORT)
    int32_t active_power_counter;
    int32_t active_energy_counter;
    uint32_t consumed_active_energy;
#endif
#if defined(PER_PHASE_ACTIVE_ENERGY_SUPPORT)
    int32_t reactive_power_counter;
#endif

#if defined(PER_PHASE_ACTIVE_ENERGY_SUPPORT)
    /*! \brief This times the duration of an energy pulse */
    uint8_t active_energy_pulse_remaining_time;
#endif
#if defined(PER_PHASE_REACTIVE_ENERGY_SUPPORT)
    /*! \brief This times the duration of an energy pulse */
    uint8_t reactive_energy_pulse_remaining_time;
#endif
    /*! \brief Status bits */
    uint16_t /*volatile*/ status;
};
struct phase_parms_s chan[NUM_PHASES];

&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
/*! This structure contains the non-volatile parameters associated with a
    single current sensor (e.g a shunt resistor or a current transformer). */
struct current_sensor_nv_parms_s
{
    /*! The scaling factor between the raw RMS current value, and milliamps, when in   normal operation. */
    int16_t I_rms_scale_factor[GAIN_STAGES];
    /*! An offset to remove an approximation of the front end noise from the measured RMS  current. */
    int32_t ac_offset;
    /*! The scaling factor between the raw active power value, and 0.1W increments, when in       normal operation. */
    int16_t P_scale_factor[];
    /*! An initial value for the DC estimate, to ensure rapid settling after reset. */
    dc_estimate_t initial_dc_estimate;

    int16_t phase_correction[GAIN_STAGES];

};

**************************************
struct phase_readings_s
{
    /*! \brief The active power, in steps of 0.01W */
    power_t active_power;
    #if defined(REACTIVE_POWER_SUPPORT)
    /*! \brief The reactive power, in steps of 0.01W */
    power_t reactive_power;
    #endif
    #if defined(APPARENT_POWER_SUPPORT)
    /*! \brief The apparent power, in steps of 0.01W */
    power_t apparent_power;
    #endif
    #if defined(VRMS_SUPPORT)
    /*! \brief The RMS voltage, in 10mV steps */
    rms_voltage_t V_rms;
    #endif
    #if defined(IRMS_SUPPORT)
    /*! \brief The RMS current, in 1mA steps */
    rms_current_t I_rms;
    #endif
    #if defined(MAINS_FREQUENCY_SUPPORT)
    /*! \brief The mains frequency, in steps of 1/100Hz */
    frequency_t frequency;
    #endif
    #if defined(POWER_FACTOR_SUPPORT)
    /*! \brief The power factor, in steps of 0.001 */
    int16_t power_factor;
    #endif
};



  i = phase_nv->V_rms_scale_factor;
