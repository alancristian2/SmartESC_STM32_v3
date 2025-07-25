#include "config.h"
#include "motor.h"
#include "motor_param.h"
#include "print.h"
#include <stdbool.h>

static int motor_initialized = 0;

void motor_init(MotorStatePublic_t *motor) {
    if (motor_initialized) return;

    if (motorParams.disable_auto_detect) {
        motor->pole_pairs = motorParams.pole_pairs;
        motor->bemf_constant = motorParams.bemf_constant;
        motor->phase_resistance = motorParams.phase_resistance;
        motor->phase_inductance = motorParams.phase_inductance;
        motor->flux_linkage = motorParams.flux_linkage;
    } else {
        motor->pole_pairs = POLE_PAIRS;
        motor->bemf_constant = BEMF_CONSTANT;
        motor->phase_resistance = 0.110f;
        motor->phase_inductance = 0.00015f;
        motor->flux_linkage = 0.024f;
    }

    motor->speed = 0;
    motor->i_q_setpoint_target = 0;
    motor->brake_active = false;
    motor->mode = 1;
    motor->speed_limit = SPEEDLIMIT_NORMAL;
    motor->phase_current_limit = PH_CURRENT_MAX_NORMAL;
    motor->field_weakening_current_max = FIELD_WEAKNING_CURRENT_MAX;
    motor->battery_voltage_min = BATTERYVOLTAGE_MIN;

    motor_initialized = 1;

    printf_("Motor inicializado con %d pares de polos y autodetección %s\n",
            motor->pole_pairs,
            motorParams.disable_auto_detect ? "desactivada" : "activada");
}

void motor_disable_pwm(void) {
    // TODO: implementar parada de PWM
}

void motor_slow_loop(MotorStatePublic_t *motor) {
    if (motor->speed > motor->speed_limit * 1000) {
        motor->i_q_setpoint_target = 0;
    }

    switch (motor->mode) {
        case 0:
            motor->phase_current_limit = PH_CURRENT_MAX_ECO;
            break;
        case 1:
            motor->phase_current_limit = PH_CURRENT_MAX_NORMAL;
            break;
        case 2:
            motor->phase_current_limit = PH_CURRENT_MAX_SPORT;
            break;
        default:
            motor->phase_current_limit = PH_CURRENT_MAX_NORMAL;
            break;
    }

    // Aquí va el control FOC real
}

void motor_auto_detect(MotorStatePublic_t *motor) {
    // Autodetección desactivada
}
