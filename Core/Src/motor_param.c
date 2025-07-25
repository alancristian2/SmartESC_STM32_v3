#include "motor.h"
#include "config.h"

// Parámetros característicos del motor Pro 4
// Valores aproximados, ajustables en calibración

// Resistencia de fase (Ohm)
#define PHASE_RESISTANCE 0.135f

// Inductancia de fase (Henrios)
#define PHASE_INDUCTANCE 0.00018f

// Enlace de flujo (Weber)
#define FLUX_LINKAGE 0.023f

void motor_load_default_params(MotorStatePublic_t *motor) {
    motor->pole_pairs = POLE_PAIRS;          // definido en config.h (20)
    motor->bemf_constant = BEMF_CONSTANT;    // definido en config.h (42 V/krpm)
    motor->phase_resistance = PHASE_RESISTANCE;
    motor->phase_inductance = PHASE_INDUCTANCE;
    motor->flux_linkage = FLUX_LINKAGE;
}
