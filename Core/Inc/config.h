#ifndef CONFIG_H
#define CONFIG_H

// ***** CONTROL DE ACELERADOR Y FRENO (valores ADC) *****
#define THROTTLEOFFSET 45
#define THROTTLEMAX 175
#define BRAKEOFFSET 50
#define BRAKEMAX 100

// ***** LÍMITES DE VELOCIDAD PARA MODOS (km/h) *****
#define SPEEDLIMIT_ECO 6
#define SPEEDLIMIT_NORMAL 20
#define SPEEDLIMIT_SPORT 55

// ***** LÍMITES DE CORRIENTE DEL MOTOR (mA) *****
#define PH_CURRENT_MAX_ECO 10000
#define PH_CURRENT_MAX_NORMAL 15000
#define PH_CURRENT_MAX_SPORT 25000

// ***** FRENADO REGENERATIVO *****
#define REGEN_MAX_CURRENT 10000  // Corriente máxima de regeneración (mA)

// ***** FIELD WEAKENING *****
#define FIELD_WEAKNING_CURRENT_MAX 0 // 0 = deshabilitado

// ***** CANALES ADC *****
#define ADC_VOLTAGE 0
#define ADC_THROTTLE 1
#define ADC_TEMP 2

// ***** PINES GPIO *****
#define LED_Pin GPIO_PIN_1
#define LED_GPIO_Port GPIOD

#define UART1_Tx_Pin GPIO_PIN_6
#define UART1_Tx_GPIO_Port GPIOB
#define UART1_Rx_Pin GPIO_PIN_7
#define UART1_Rx_GPIO_Port GPIOB

#define BrakeLight_Pin GPIO_PIN_15
#define BrakeLight_GPIO_Port GPIOA

#define Temp_Pin GPIO_PIN_0
#define Temp_GPIO_Port GPIOA

#define Throttle_Pin GPIO_PIN_1
#define Throttle_GPIO_Port GPIOA

#define Batt_Voltage_Pin GPIO_PIN_2
#define Batt_Voltage_GPIO_Port GPIOA

#define PWR_BTN_Pin GPIO_PIN_14
#define PWR_BTN_GPIO_Port GPIOC

#define TPS_ENA_Pin GPIO_PIN_15
#define TPS_ENA_GPIO_Port GPIOC

// ***** PARÁMETROS MOTOR PRO 4 *****
#define POLE_PAIRS 20            // 40 imanes = 20 pares de polos

// Configuración de sensores Hall
#define HALL_SENSOR_OFFSET_1 60  // Primer hall a 60°
#define HALL_SENSOR_OFFSET_2 150 // Segundo hall a 150° (60 + 90)
#define HALL_SENSOR_INVERT_C 1   // Hall central invertido (C)

// Velocidad nominal y BEMF
#define MAX_RATED_SPEED 3000     // RPM máximas nominales
#define BEMF_CONSTANT 42.0       // V/krpm para motor Pro 4

// ***** AUTODETECCIÓN *****
#define DISABLE_AUTO_DETECT 1    // 1 = desactivar autodetección

#endif // CONFIG_H
