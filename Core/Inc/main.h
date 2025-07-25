#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include "main.h"
#include "motor.h"

#ifdef __cplusplus
extern "C" {
#endif

// parámetros para cálculo de velocidad
// #define WHEEL_CIRCUMFERENCE 822 // mm para rueda de 10,3 pulgadas
// #define GEAR_RATIO 15 // 15 para motor original M365

// Canales ADC para medir corrientes
#define ADC_CHANA 3
#define ADC_CHANB 4
#define ADC_CHANC 5

// Canal ADC para medir tensión de batería
#define ADC_VOLTAGE 0

// factores de calibración para tensión y corriente
#define CAL_BAT_V 13 	// ADC counts * CAL_BAT_V = tensión batería en mV

// límites de tensión de batería en mV
#define BATTERYVOLTAGE_MIN 33000
#define BATTERYVOLTAGE_MAX 42000

#define CAL_I 38 // ADC counts * CAL_I = corriente en mA

// corrientes máximas en mA
#define BATTERYCURRENT_MAX 10000 // 10A, 36V batería, 350W límite
#define REGEN_CURRENT_MAX 6000

#define P_FACTOR_I_Q 100
#define I_FACTOR_I_Q 2
#define P_FACTOR_I_D 100
#define I_FACTOR_I_D 10
#define MAX_D_FACTOR 1

#define SPEEDFILTER 3
#define SPEC_ANGLE -167026406L
#define REVERSE 1 // 1 para motor original M365

// Parámetros PLL motor
#define P_FACTOR_PLL 8
#define I_FACTOR_PLL 8
#define SIXSTEPTHRESHOLD 9000

// Pines de corriente de fase
#define Phase_Current_1_Pin GPIO_PIN_3
#define Phase_Current_1_GPIO_Port GPIOA
#define Phase_Current_2_Pin GPIO_PIN_4
#define Phase_Current_2_GPIO_Port GPIOA
#define Phase_Current_3_Pin GPIO_PIN_5
#define Phase_Current_3_GPIO_Port GPIOA

#define Batt_Voltage_Pin GPIO_PIN_2
#define Batt_Voltage_GPIO_Port GPIOA

// Pines sensores Hall
#define HALL_1_Pin GPIO_PIN_4
#define HALL_1_GPIO_Port GPIOB
#define HALL_2_Pin GPIO_PIN_5
#define HALL_2_GPIO_Port GPIOB
#define HALL_3_Pin GPIO_PIN_0
#define HALL_3_GPIO_Port GPIOB

};

// void motor_init(MotorStatePublic_t* p_MotorStatePublic);
// void motor_autodetect();
// void motor_slow_loop(MotorStatePublic_t* p_MotorStatePublic);
// void motor_disable_pwm();

#ifdef __cplusplus
}
#endif
