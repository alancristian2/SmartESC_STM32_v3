#include "motor_param.h"

// Tabla de estados para sensores Hall (ejemplo típico 3 sensores)
// Puedes ajustar según la configuración de tus sensores
const uint8_t hall_table[8] = {
    0,  // 000 - no válido
    5,  // 001
    3,  // 010
    6,  // 011
    1,  // 100
    4,  // 101
    2,  // 110
    0   // 111 - no válido
};

// Variable global con parámetros inicializados para motor Pro 4
MotorParams_t motorParams = {
    .pole_pairs = 20,
    .bemf_constant = 42.0f,
    .max_speed_rpm = 3000,

    .disable_auto_detect = 1, // desactivada autodetección

    .hall_offset_1 = 60,
    .hall_offset_2 = 150,
    .hall_invert_c = 1,

    .phase_current_max_eco = 10000,
    .phase_current_max_normal = 15000,
    .phase_current_max_sport = 25000,
    .regen_max_current = 10000,
    .field_weakening_current_max = 0,

    .phase_resistance = 0.135f,
    .phase_inductance = 0.00018f,
    .flux_linkage = 0.023f
};

// Función para cargar parámetros por defecto en una estructura MotorStatePublic_t
// (puedes adaptar el tipo según tu motor.h)
void motor_load_default_params(MotorStatePublic_t *motor) {
    motor->pole_pairs = motorParams.pole_pairs;
    motor->bemf_constant = motorParams.bemf_constant;
    motor->speed = 0;
    motor->max_speed_rpm = motorParams.max_speed_rpm;
    motor->phase_resistance = motorParams.phase_resistance;
    motor->phase_inductance = motorParams.phase_inductance;
    motor->flux_linkage = motorParams.flux_linkage;
    
    motor->phase_current_limit = motorParams.phase_current_max_normal;
    motor->regen_max_current = motorParams.regen_max_current;
    motor->field_weakening_current_max = motorParams.field_weakening_current_max;

    // Otros parámetros que quieras copiar
}
