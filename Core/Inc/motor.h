#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>
#include <stdbool.h>
#include "config.h"

// Estructura pública del estado del motor
typedef struct {
    int32_t speed;                    // velocidad en milésimas de km/h
    int32_t i_q_setpoint_target;      // corriente q objetivo (mA)
    bool brake_active;                // freno activado
    uint8_t mode;                     // 0 = ECO, 1 = Normal, 2 = Sport
    int32_t speed_limit;              // límite de velocidad (km/h)
    int32_t phase_current_limit;      // límite de corriente de fase (mA)
    int32_t field_weakening_current_max; // corriente máxima para field weakening
    int32_t battery_voltage_min;      // voltaje mínimo de batería (mV)

    int32_t adcData[3];               // datos ADC: voltaje, acelerador, temperatura
    int32_t debug[2];                 // variables de depuración

    // Parámetros fijos del motor
    uint8_t pole_pairs;               // pares de polos
    float bemf_constant;              // constante BEMF (V/krpm)
    float phase_resistance;           // resistencia de fase (Ohm)
    float phase_inductance;           // inductancia de fase (H)
    float flux_linkage;               // enlace de flujo (Wb)
} MotorStatePublic_t;

// Funciones del motor
void motor_init(MotorStatePublic_t *motor);
void motor_disable_pwm(void);
void motor_slow_loop(MotorStatePublic_t *motor);
void motor_auto_detect(MotorStatePublic_t *motor);

#endif // MOTOR_H
