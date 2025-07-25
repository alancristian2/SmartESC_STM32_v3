#include "motor_param.h"

MotorParams_t motorParams = {
    .pole_pairs = POLE_PAIRS,
    .bemf_constant = BEMF_CONSTANT,
    .max_speed_rpm = MAX_RATED_SPEED,
    .disable_auto_detect = DISABLE_AUTO_DETECT,

    .hall_offset_1 = HALL_SENSOR_OFFSET_1,
    .hall_offset_2 = HALL_SENSOR_OFFSET_2,
    .hall_invert_c = HALL_SENSOR_INVERT_C,

    .phase_current_max_eco = PH_CURRENT_MAX_ECO,
    .phase_current_max_normal = PH_CURRENT_MAX_NORMAL,
    .phase_current_max_sport = PH_CURRENT_MAX_SPORT,
    .regen_max_current = REGEN_MAX_CURRENT,
    .field_weakening_current_max = FIELD_WEAKNING_CURRENT_MAX,

    .phase_resistance = 0.110f,
    .phase_inductance = 0.00015f,
    .flux_linkage = 0.024f
};

const uint8_t hall_table[8] = {
    0, 1, 3, 2, 5, 6, 4, 0
};
