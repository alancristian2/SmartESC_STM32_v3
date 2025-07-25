#include "motor.h"
#include "motor_param.h"
#include "hall_sensor.h"
#include "config.h"
#include "print.h"

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
        // Si habilitas autodetect, implementa aquí (ahora deshabilitado)
    }

    motor->speed = 0;
    motor->i_q_setpoint_target = 0;
    motor->brake_active = false;
    motor->mode = 1; // modo normal
    motor->speed_limit = SPEEDLIMIT_NORMAL;
    motor->phase_current_limit = PH_CURRENT_MAX_NORMAL;
    motor->field_weakening_current_max = FIELD_WEAKNING_CURRENT_MAX;
    motor->battery_voltage_min = BATTERYVOLTAGE_MIN;

    hall_sensor_init(); // Inicializa sensores Hall

    motor_initialized = 1;
    printf_("Motor inicializado con %d pares de polos y autodetección %s\n",
            motor->pole_pairs,
            motorParams.disable_auto_detect ? "desactivada" : "activada");
}

void motor_disable_pwm(void) {
    // Apaga salidas PWM/MOSFET (según hardware)
}

void motor_slow_loop(MotorStatePublic_t *motor) {
    // Cada 10ms - actualizar control básico

    // Leer posición motor por sensores Hall
    int hall_pos = hall_get_position();
    if (hall_pos < 0) {
        // Estado inválido - frenar o mantener
        motor->i_q_setpoint_target = 0;
    } else {
        // Aquí podrías usar hall_pos para control vectorial (FOC)
        // Por ahora solo simulamos actualización velocidad
        motor->speed = (motor->speed + 1) % (motorParams.max_speed_rpm * 10);
    }

    // Límite de velocidad
    if (motor->speed > motor->speed_limit * 1000) { // convertir km/h escala interna
        motor->i_q_setpoint_target = 0;
    }

    // Ajustar corriente según modo
    switch (motor->mode) {
        case 0:
            motor->phase_current_limit = motorParams.phase_current_max_eco;
            break;
        case 1:
            motor->phase_current_limit = motorParams.phase_current_max_normal;
            break;
        case 2:
            motor->phase_current_limit = motorParams.phase_current_max_sport;
            break;
        default:
            motor->phase_current_limit = motorParams.phase_current_max_normal;
    }

    // TODO: implementar control real FOC usando hall_pos y i_q_setpoint_target
}

void motor_auto_detect(MotorStatePublic_t *motor) {
    // Función deshabilitada (usamos parámetros fijos)
}
