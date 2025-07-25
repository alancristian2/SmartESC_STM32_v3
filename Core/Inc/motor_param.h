#ifndef MOTOR_PARAM_H
#define MOTOR_PARAM_H

#include "config.h"

typedef struct {
    int pole_pairs;
    float bemf_constant;
    int max_speed_rpm;

    // Configuración autodetección: 1 = desactivar, 0 = activar
    int disable_auto_detect;

    // Configuración sensores Hall
    int hall_offset_1;
    int hall_offset_2;
    int hall_invert_c;

    // Corrientes máximas (mA)
    int phase_current_max_eco;
    int phase_current_max_normal;
    int phase_current_max_sport;
    int regen_max_current;
    int field_weakening_current_max;

    // Parámetros eléctricos
    float phase_resistance;
    float phase_inductance;
    float flux_linkage;
} MotorParams_t;

// Variable global con parámetros de motor
extern MotorParams_t motorParams;

// Si usas tabla Hall, declara aquí (sino elimina)
extern const uint8_t hall_table[8];

// Función para cargar parámetros por defecto
void motor_load_default_params(void);

#endif
