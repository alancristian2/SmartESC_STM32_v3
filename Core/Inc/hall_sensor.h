#ifndef HALL_SENSOR_H
#define HALL_SENSOR_H

#include <stdint.h>

// Pines y puertos sensores Hall (Xiaomi Pro 2 - STM32F103CBT6)
#define HALL_SENSOR_A_Pin GPIO_PIN_4
#define HALL_SENSOR_A_GPIO_Port GPIOA

#define HALL_SENSOR_B_Pin GPIO_PIN_5
#define HALL_SENSOR_B_GPIO_Port GPIOA

#define HALL_SENSOR_C_Pin GPIO_PIN_6
#define HALL_SENSOR_C_GPIO_Port GPIOA

// Tabla estados Hall (configuración estándar para 3 sensores)
extern const uint8_t hall_table[8];

// Inicializa sensores Hall (si necesitas configurar GPIO, etc)
void hall_sensor_init(void);

// Lee el estado raw combinado de sensores Hall (0-7)
uint8_t hall_read_raw(void);

// Devuelve posición eléctrica en grados ajustada con offsets e inversión
// Retorna -1 si lectura inválida
int hall_get_position(void);

#endif // HALL_SENSOR_H
