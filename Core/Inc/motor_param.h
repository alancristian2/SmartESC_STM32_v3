#ifndef MOTOR_PARAM_H
#define MOTOR_PARAM_H

#include "config.h"

typedef struct {
    int pole_pairs;
    float bemf_constant;
    int max_speed_rpm;
    int disable_auto_detect;

    int hall_offset_1;
    int hall_offset_2;
    int hall_invert_c;

    int phase_current_max_eco;
    int phase_current_max_normal;
    int phase_current_max_sport;
    int regen_max_current;
    int field_weakening_current_max;

    float phase_resistance;
    float phase_inductance;
    float flux_linkage;
} MotorParams_t;

extern MotorParams_t motorParams;

#endif
