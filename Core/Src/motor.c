#include "motor.h"
#include "motor_param.h"
#include "config.h"
#include "print.h"

static int motor_initialized = 0;

void motor_init(MotorStatePublic_t *motor) {
    if (motor_initialized) return;

    // Si la autodetección está deshabilitada, usar los parámetros de motor_param.c
    if (motorParams.disable_auto_detect) {
        motor->pole_pairs = motorParams.pole_pairs;
        motor->bemf_constant = motorParams.bemf_constant;
        motor->phase_resistance = motorParams.phase_resistance;
        motor->phase_inductance = motorParams.phase_inductance;
        motor->flux_linkage = motorParams.flux_linkage;
    } else {
        // Aquí iría la autodetección (desactivada)
        motor->pole_pairs = POLE_PAIRS;
        motor->bemf_constant = BEMF_CONSTANT;
        motor->phase_resistance = 0.110f;
        motor->phase_inductance = 0.00015f;
        motor->flux_linkage = 0.024f;
    }

    motor->speed = 0;
    motor->i_q_setpoint_target = 0;
    motor->brake_active = false;
    motor->mode = 1; // modo normal
    motor->speed_limit = SPEEDLIMIT_NORMAL;
    motor->phase_current_limit = PH_CURRENT_MAX_NORMAL;
    motor->field_weakening_current_max = FIELD_WEAKNING_CURRENT_MAX;
    motor->battery_voltage_min = BATTERYVOLTAGE_MIN;

    motor_initialized = 1;
    printf_("Motor inicializado con %d pole pairs y autodetección %s\n",
            motor->pole_pairs,
            motorParams.disable_auto_detect ? "desactivada" : "activada");
}

void motor_disable_pwm(void) {
    // Apagar todas las salidas del inversor
    // Aquí deshabilitarías los MOSFETs o PWM (depende del hardware)
}

void motor_slow_loop(MotorStatePublic_t *motor) {
    // Lógica de control del motor, se ejecuta cada 10ms

    // Verificar límite de velocidad
    if (motor->speed > motor->speed_limit * 1000) { // convertir km/h a escala interna
        motor->i_q_setpoint_target = 0;
    }

    // Actualizar la corriente de fase según el modo
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
    }

    // TODO: implementar control FOC real
}

void motor_auto_detect(MotorStatePublic_t *motor) {
    // Esta función está intencionalmente desactivada
    // Siempre usamos los parámetros fijos de motorParams
}
