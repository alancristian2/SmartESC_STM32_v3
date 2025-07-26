#include "hall_eeprom.h"

extern MotorParams_t motorParams;  // Declaración externa

// Guarda los ángulos Hall y la configuración en EEPROM
void hall_save_to_eeprom(void) {
    EE_WriteVariable(EEPROM_POS_HALL_ORDER, motorParams.hall_order);
    EE_WriteVariable(EEPROM_POS_HALL_45, (int16_t)(motorParams.Hall_45 >> 16));
    EE_WriteVariable(EEPROM_POS_HALL_51, (int16_t)(motorParams.Hall_51 >> 16));
    EE_WriteVariable(EEPROM_POS_HALL_13, (int16_t)(motorParams.Hall_13 >> 16));
    EE_WriteVariable(EEPROM_POS_HALL_32, (int16_t)(motorParams.Hall_32 >> 16));
    EE_WriteVariable(EEPROM_POS_HALL_26, (int16_t)(motorParams.Hall_26 >> 16));
    EE_WriteVariable(EEPROM_POS_HALL_64, (int16_t)(motorParams.Hall_64 >> 16));
    EE_WriteVariable(EEPROM_POS_KV, motorParams.hall_invert_c ? 1 : 0);
}

// Carga los ángulos Hall y configuración desde EEPROM
void hall_load_from_eeprom(void) {
    int16_t value;

    EE_ReadVariable(EEPROM_POS_HALL_ORDER, &value);
    motorParams.hall_order = value;

    EE_ReadVariable(EEPROM_POS_HALL_45, &value);
    motorParams.Hall_45 = ((q31_t)value) << 16;

    EE_ReadVariable(EEPROM_POS_HALL_51, &value);
    motorParams.Hall_51 = ((q31_t)value) << 16;

    EE_ReadVariable(EEPROM_POS_HALL_13, &value);
    motorParams.Hall_13 = ((q31_t)value) << 16;

    EE_ReadVariable(EEPROM_POS_HALL_32, &value);
    motorParams.Hall_32 = ((q31_t)value) << 16;

    EE_ReadVariable(EEPROM_POS_HALL_26, &value);
    motorParams.Hall_26 = ((q31_t)value) << 16;

    EE_ReadVariable(EEPROM_POS_HALL_64, &value);
    motorParams.Hall_64 = ((q31_t)value) << 16;

    EE_ReadVariable(EEPROM_POS_KV, &value);
    motorParams.hall_invert_c = (value == 1);
}
