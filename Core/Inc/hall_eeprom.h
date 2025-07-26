#ifndef HALL_EEPROM_H
#define HALL_EEPROM_H

#include "stm32f1xx_hal.h"
#include "motor_param.h"
#include "eeprom.h"

// Prototipos
void hall_save_to_eeprom(void);
void hall_load_from_eeprom(void);

#endif // HALL_EEPROM_H
