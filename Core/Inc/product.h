#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
#include <string.h>
#include <stdlib.h>
#include <arm_math.h>
#include <stdbool.h>
#include "utils.h"
#include "motor.h"

/* Exported functions --------------------------------------------------------*/
void Error_Handler(void);
extern void UserSysTickHandler(void);

/* Estado principal del patinete */
typedef struct {
  q31_t battery_voltage;        // Voltaje de batería
  int16_t phase_current_limit;  // Límite de corriente de fase
  int16_t regen_max_current;    // Corriente máxima de regeneración
  int8_t temperature;           // Temperatura del motor/controlador
  int8_t mode;                  // Modo actual (eco, normal, sport)
  bool light;                   // Luz activada
  bool beep;                    // Beep activado
  int32_t i_q_setpoint_target;  // Setpoint de corriente q
  uint32_t speed;               // Velocidad actual
  bool brake_active;            // Estado del freno
  uint32_t shutdown;            // Contador para apagado
  int8_t speed_limit;           // Límite de velocidad
  int8_t error_state;           // Estado de error
} M365State_t;

/* Enumeración de modos */
enum modes {
  eco = 2,
  normal = 0,
  sport = 4
};

/* Mapeo para compatibilidad con HAL */
#define Phase_Current_1_Pin   M1_CURR_AMPL_U_Pin
#define Phase_Current_2_Pin   M1_CURR_AMPL_V_Pin
#define Phase_Current_3_Pin   M1_CURR_AMPL_W_Pin

#define HALL_1_Pin            M1_HALL_H1_Pin
#define HALL_2_Pin            M1_HALL_H2_Pin
#define HALL_3_Pin            M1_HALL_H3_Pin

#ifdef __cplusplus
}
#endif
