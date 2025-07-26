#include "eeprom.h"

// Variables globales Hall definidas en tu código (externas)
extern q31_t Hall_45;
extern q31_t Hall_51;
extern q31_t Hall_13;
extern q31_t Hall_32;
extern q31_t Hall_26;
extern q31_t Hall_64;

// Guarda los valores Hall en EEPROM (solo parte alta 16 bits)
void save_hall_angles_to_eeprom(void) {
    EE_WriteVariable(EEPROM_POS_HALL_ORDER, 1); // marca que está definido manualmente

    EE_WriteVariable(EEPROM_POS_HALL_45,  (int16_t)(Hall_45 >> 16));
    EE_WriteVariable(EEPROM_POS_HALL_51,  (int16_t)(Hall_51 >> 16));
    EE_WriteVariable(EEPROM_POS_HALL_13,  (int16_t)(Hall_13 >> 16));
    EE_WriteVariable(EEPROM_POS_HALL_32,  (int16_t)(Hall_32 >> 16));
    EE_WriteVariable(EEPROM_POS_HALL_26,  (int16_t)(Hall_26 >> 16));
    EE_WriteVariable(EEPROM_POS_HALL_64,  (int16_t)(Hall_64 >> 16));
}

// Carga los valores Hall de EEPROM, si existen, o deja valores por defecto si no
void load_hall_angles_from_eeprom(void) {
    int16_t temp;
    int16_t hall_order;

    if (EE_ReadVariable(EEPROM_POS_HALL_ORDER, &hall_order) == 0 && hall_order == 1) {
        EE_ReadVariable(EEPROM_POS_HALL_45, &temp); Hall_45 = ((q31_t)temp) << 16;
        EE_ReadVariable(EEPROM_POS_HALL_51, &temp); Hall_51 = ((q31_t)temp) << 16;
        EE_ReadVariable(EEPROM_POS_HALL_13, &temp); Hall_13 = ((q31_t)temp) << 16;
        EE_ReadVariable(EEPROM_POS_HALL_32, &temp); Hall_32 = ((q31_t)temp) << 16;
        EE_ReadVariable(EEPROM_POS_HALL_26, &temp); Hall_26 = ((q31_t)temp) << 16;
        EE_ReadVariable(EEPROM_POS_HALL_64, &temp); Hall_64 = ((q31_t)temp) << 16;
    } else {
        // No está configurado en EEPROM: cargar valores por defecto (los que tengas en tu código)
        // O implementar autocalibración
    }
}
