#include "hall_sensor.h"
#include "motor_param.h"
#include "stm32f1xx_hal.h"

// Tabla estados para sensores Hall
const uint8_t hall_table[8] = {
    0,  // 000 - inválido
    5,  // 001
    3,  // 010
    6,  // 011
    1,  // 100
    4,  // 101
    2,  // 110
    0   // 111 - inválido
};

static inline uint8_t read_hall_pin(GPIO_TypeDef *port, uint16_t pin) {
    return (HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_SET) ? 1 : 0;
}

void hall_sensor_init(void) {
    // Asumiendo que los pines ya están configurados como inputs con pullup o similar en GPIO_Init()
    // Si quieres, aquí podrías configurar pines GPIO para entrada digital
}

uint8_t hall_read_raw(void) {
    uint8_t hallA = read_hall_pin(HALL_SENSOR_A_GPIO_Port, HALL_SENSOR_A_Pin);
    uint8_t hallB = read_hall_pin(HALL_SENSOR_B_GPIO_Port, HALL_SENSOR_B_Pin);
    uint8_t hallC = read_hall_pin(HALL_SENSOR_C_GPIO_Port, HALL_SENSOR_C_Pin);

    return (hallC << 2) | (hallB << 1) | hallA;
}

int hall_get_position(void) {
    uint8_t raw = hall_read_raw();

    if (raw > 7) return -1;

    uint8_t pos = hall_table[raw];
    if (pos == 0) {
        return -1; // Estado inválido
    }

    // Cada estado corresponde a 60° eléctricos (6 estados para 360°)
    int electrical_angle = pos * 60;

    // Aplicar offset 1 y 2
    electrical_angle += motorParams.hall_offset_1; // Ejemplo de offset principal
    electrical_angle %= 360;

    // Invertir sensor central si está configurado
    if (motorParams.hall_invert_c) {
        electrical_angle = 360 - electrical_angle;
    }

    return electrical_angle;
}
