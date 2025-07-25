// Control de acelerador y freno (valores ADC)
#define THROTTLEOFFSET 45
#define THROTTLEMAX 175
#define BRAKEOFFSET 50
#define BRAKEMAX 100

// Límites de velocidad para modos (en km/h)
#define SPEEDLIMIT_ECO 6
#define SPEEDLIMIT_NORMAL 20
#define SPEEDLIMIT_SPORT 56

// Límites de corriente motor para modos (mA)
#define PH_CURRENT_MAX_ECO 10000
#define PH_CURRENT_MAX_NORMAL 15000
#define PH_CURRENT_MAX_SPORT 25000

// Corriente máxima de frenado regenerativo (mA)
#define REGEN_MAX_CURRENT 10000

// Corriente máxima para debilitar campo (field weakening) (mA)
#define FIELD_WEAKNING_CURRENT_MAX 0 // Deshabilitado

// Canales ADC usados
#define ADC_VOLTAGE 0
#define ADC_THROTTLE 1
#define ADC_TEMP 2

// Pines GPIO originales Xiaomi Pro 2
#define LED_Pin GPIO_PIN_1
#define LED_GPIO_Port GPIOD

#define UART1_Tx_Pin GPIO_PIN_6
#define UART1_Tx_GPIO_Port GPIOB

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

// Pines Hall sensores para Xiaomi Pro 2 (STM32F103CBT6)
#define HALL_PIN_A GPIO_PIN_4
#define HALL_PORT_A GPIOB

#define HALL_PIN_B GPIO_PIN_5
#define HALL_PORT_B GPIOB

#define HALL_PIN_C GPIO_PIN_0
#define HALL_PORT_C GPIOB

// Número de pares de polos para motor Pro 4 (40 imanes)
#define POLE_PAIRS 20

// Configuración sensores Hall (separados diente y medio, hall central invertido)
#define HALL_SENSOR_OFFSET_1 60      // Primer sensor hall a 60°
#define HALL_SENSOR_OFFSET_2 150     // Segundo sensor hall a 150° (60 + 90)
#define HALL_SENSOR_INVERT_C 1       // Invertir sensor hall central (C)

// Velocidad nominal máxima (RPM)
#define MAX_RATED_SPEED 3000

// Constante BEMF aproximada para motor Pro 4 (V/krpm)
#define BEMF_CONSTANT 42.0

// Desactivar autodetección parámetros motor (0 = activar, 1 = desactivar)
#define DISABLE_AUTO_DETECT 1

// config.h o en la parte superior de motor.c si no tienes config.h
#define BATTERYVOLTAGE_MIN 30000  // ejemplo: 30.0 V si usas milivoltios
