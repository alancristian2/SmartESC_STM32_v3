#include "motor_param.h"

// Tabla estados Hall (igual que en hall_sensor.c)
const uint8_t hall_table[8] = {
    0,  // 000 - inválido
    5,  // 001
    3,  // 010
    6,  // 011
    1,  // 100
    4,  // 101
    2,  // 110
    0   // 111 - inválido
};

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
