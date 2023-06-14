// GARAGE SYSTEM : GASY
#ifndef GASY_INTERFACE_H
#define GASY_INTERFACE_H

#define TESY_MAX_TEMP_FAN_ON 35u
#define TESY_MAX_TEMP_FAN_OFF 30u
#define TESY_LIGHT_LEVEL_RANGE 15u

typedef struct TESY_CONFIG_t
{
    LDR_Config_t TE_LDR;
    LM_Config_t TE_LM;
    DCM_Config_t TE_DCMotor;
} TESY_CONFIG_t;

void ADC0CallBack(void);
void ADC7CallBack(void);

uint8 TESY_u8init(TESY_CONFIG_t *referance_TESY);
void TESY_voidMainSystem(uint8 *ref_u8INTFlag);

#endif
