#ifndef MOTOR_H
#define MOTOR_H

#include <stdbool.h>

// Estructura para estado público del motor
typedef struct {
    int pole_pairs;
    float bemf_constant;
    int speed;                 // velocidad en escala interna (ejemplo)
    int max_speed_rpm;

    float phase_resistance;
    float phase_inductance;
    float flux_linkage;

    int phase_current_limit;
    int regen_max_current;
    int field_weakening_current_max;

    bool brake_active;
    int mode;
    int speed_limit;
    int i_q_setpoint_target;

    int battery_voltage_min;

    int adcData[3];            // indices ADC_VOLTAGE, ADC_THROTTLE, ADC_TEMP

    int battery_voltage;
    int temperature;

    int debug[2];
} MotorStatePublic_t;

void motor_init(MotorStatePublic_t *motor);
void motor_disable_pwm(void);
void motor_slow_loop(MotorStatePublic_t *motor);
void motor_auto_detect(MotorStatePublic_t *motor);

#endif
