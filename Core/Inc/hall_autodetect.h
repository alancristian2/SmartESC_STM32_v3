#include "hall_autodetect.h"
#include "hall_sensor.h"
#include "hall_eeprom.h"
#include "motor_param.h"
#include "print.h"

void hall_autodetect(MotorStatePublic_t *motor) {
    printf_("Iniciando autodetección de sensores Hall...\n");

    int32_t hall_angles[6];
    uint8_t hall_states[6] = {1, 2, 3, 4, 5, 6};

    for (int i = 0; i < 6; i++) {
        motor->i_q_setpoint_target = 200; // corriente mínima para mover motor
        HAL_Delay(300);
        hall_angles[i] = hall_get_position();
        printf_("Estado %d: ángulo detectado = %ld\n", hall_states[i], hall_angles[i]);
    }

    // Guardar en EEPROM
    hall_eeprom_write_angles(hall_angles);

    printf_("Autodetección completa. Valores guardados en EEPROM.\n");
}
