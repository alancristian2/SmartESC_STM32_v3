// main.c

#include "main.h"
#include "config.h"
#include "print.h"
#include "motor.h"
#include "motor_param.h"
#include "button_processing.h"
#include "M365_Dashboard.h"

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;

DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart3_tx;
DMA_HandleTypeDef hdma_usart3_rx;

M365State_t M365State;
MotorStatePublic_t MSPublic;

volatile uint32_t systick_cnt = 0;

// every 1ms
void UserSysTickHandler(void) {
    static uint32_t c;
    systick_cnt++;
    c++;
    // every 10ms
    if ((c % 10) == 0) {
        motor_slow_loop(&MSPublic);
    }
}

static void DMA_Init(void) {
    __HAL_RCC_DMA1_CLK_ENABLE();

    HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);

    HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);

    HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 3, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
}

void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_PeriphCLKInitTypeDef PeriphClkInit;

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = 16;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }

    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
        Error_Handler();
    }

    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
    HAL_NVIC_SetPriority(SysTick_IRQn, 2, 0);
}

static void USART1_UART_Init(void) {
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart1) != HAL_OK) {
        Error_Handler();
    }
}

static void USART3_UART_Init(void) {
    huart3.Instance = USART3;
    huart3.Init.BaudRate = 115200;
    huart3.Init.WordLength = UART_WORDLENGTH_8B;
    huart3.Init.StopBits = UART_STOPBITS_1;
    huart3.Init.Parity = UART_PARITY_NONE;
    huart3.Init.Mode = UART_MODE_TX_RX;
    huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart3.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart3) != HAL_OK) {
        Error_Handler();
    }
}

static void GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    GPIO_InitStruct.Pin = PWR_BTN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PWR_BTN_GPIO_Port, &GPIO_InitStruct);

    HAL_GPIO_WritePin(TPS_ENA_GPIO_Port, TPS_ENA_Pin, GPIO_PIN_SET);
    GPIO_InitStruct.Pin = TPS_ENA_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(TPS_ENA_GPIO_Port, &GPIO_InitStruct);

    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin = LED_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    HAL_GPIO_WritePin(BrakeLight_GPIO_Port, BrakeLight_Pin, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin = BrakeLight_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(BrakeLight_GPIO_Port, &GPIO_InitStruct);
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle) {}
void HAL_UART_ErrorCallback(UART_HandleTypeDef *UartHandle) {}

void Error_Handler(void) {
    __disable_irq();
    while (1) {
        motor_disable_pwm();
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) {}
#endif

int main(void) {
    HAL_Init();
    SystemClock_Config();
    GPIO_Init();
    DMA_Init();
    USART1_UART_Init();
    USART3_UART_Init();

    motor_load_default_params(&MSPublic);
    motor_init(&MSPublic);

    M365State.phase_current_limit = motorParams.phase_current_max_normal;
    M365State.speed_limit = SPEEDLIMIT_NORMAL;
    M365State.regen_max_current = motorParams.regen_max_current;

    M365Dashboard_init(huart1);
    PWR_init();

    static uint32_t systick_cnt_old = 0;
    static uint8_t debug_cnt = 0;
    static q31_t q31_batt_voltage_acc = 0;
    static q31_t q31_current_acc = 0;

    while (1) {
        M365State.speed = MSPublic.speed;
        search_DashboardMessage(&M365State, huart1);

        MSPublic.phase_current_limit = M365State.phase_current_limit;
        MSPublic.i_q_setpoint_target = M365State.i_q_setpoint_target;
        MSPublic.brake_active = M365State.brake_active;

        if ((systick_cnt_old != systick_cnt) && (systick_cnt % 20) == 0) {
            systick_cnt_old = systick_cnt;
            checkButton(&M365State);

            MSPublic.mode = M365State.mode;
            MSPublic.speed_limit = M365State.speed_limit;

            q31_batt_voltage_acc -= (q31_batt_voltage_acc >> 7);
            q31_batt_voltage_acc += MSPublic.adcData[ADC_VOLTAGE];
            float battery_voltage = (q31_batt_voltage_acc >> 7) * CAL_BAT_V;
            MSPublic.battery_voltage = M365State.battery_voltage = battery_voltage;

            q31_current_acc -= (q31_current_acc >> 7);
            q31_current_acc += MSPublic.adcData[ADC_CURRENT];
            float current_amps = (q31_current_acc >> 7) * CAL_I;

            if (M365State.shutdown)
                M365State.shutdown++;

            M365State.temperature = (MSPublic.adcData[ADC_TEMP] * 41) >> 8;

            if (++debug_cnt > 13) {
                debug_cnt = 0;
                printf_("%d, %.2f\n", MSPublic.debug[0], current_amps);
            }
        }
    }
}
