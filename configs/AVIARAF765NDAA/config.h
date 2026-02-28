/*
 * This file is part of Betaflight.
 *
 * Betaflight is free software. You can redistribute this software
 * and/or modify this software under the terms of the GNU General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later
 * version.
 *
 * Betaflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define FC_TARGET_MCU     STM32F765

#define BOARD_NAME        AVIARAF765NDAA
#define MANUFACTURER_ID   LMNR

#define USE_ACC
#define USE_ACC_SPI_ICM42688P
#define USE_GYRO
#define USE_GYRO_SPI_ICM42688P
#define USE_BARO
#define USE_BARO_DPS310
#define USE_FLASH
#define USE_FLASH_W25Q128FV
#define USE_GYRO_CLKIN

#define BEEPER_PIN           PC8
#define BEEPER_INVERTED

// Motors - TIM5(PA0-PA3) + TIM1(PE9/PE11/PE13/PE14)
#define MOTOR1_PIN           PA0
#define MOTOR2_PIN           PA1
#define MOTOR3_PIN           PA2
#define MOTOR4_PIN           PA3
#define MOTOR5_PIN           PE9
#define MOTOR6_PIN           PE11
#define MOTOR7_PIN           PE13
#define MOTOR8_PIN           PE14

// Servos - TIM4(PD12-PD15)
#define SERVO1_PIN           PD12
#define SERVO2_PIN           PD13
#define SERVO3_PIN           PD14
#define SERVO4_PIN           PD15

#define LED_STRIP_PIN        PB5
#define CAMERA_CONTROL_PIN   PB9

// UART
#define UART1_TX_PIN         PA9
#define UART1_RX_PIN         PA10
#define UART2_TX_PIN         PD5
#define UART2_RX_PIN         PD6
#define UART3_TX_PIN         PD8
#define UART3_RX_PIN         PD9
#define UART4_TX_PIN         PC10
#define UART4_RX_PIN         PC11
#define UART5_TX_PIN         PB6
#define UART5_RX_PIN         PD2
#define UART6_TX_PIN         PC6
#define UART6_RX_PIN         PC7
#define UART7_TX_PIN         PE8
#define UART7_RX_PIN         PE7
#define UART8_TX_PIN         PE1
#define UART8_RX_PIN         PE0

// I2C3 - baro + mag
#define I2C3_SCL_PIN         PA8
#define I2C3_SDA_PIN         PC9

// Status LED
#define LED0_PIN             PE4

// SPI1 - Gyro
#define SPI1_SCK_PIN         PA5
#define SPI1_SDI_PIN         PA6
#define SPI1_SDO_PIN         PA7

// SPI2 - Flash
#define SPI2_SCK_PIN         PB13
#define SPI2_SDI_PIN         PB14
#define SPI2_SDO_PIN         PB15

// ADC
#define ADC_VBAT_PIN         PC3
#define ADC_RSSI_PIN         PC1
#define ADC_CURR_PIN         PC2
#define ADC_EXTERNAL1_PIN    PC0

// Flash - SPI2
#define FLASH_CS_PIN         PB12

// Gyro - SPI1
#define GYRO_1_CS_PIN        PA4
#define GYRO_1_EXTI_PIN      PE15
#define GYRO_1_CLKIN_PIN     PB10

// USB detect
#define USB_DETECT_PIN       PD7

// Timer pin mapping
//  0-3:  motors 1-4 (TIM5, DSHOT)
//  4-7:  motors 5-8 (TIM1, DSHOT)
//  8-11: servos (TIM4, standard PWM)
//  12:   LED strip (TIM3)
//  13:   GYRO_CLKIN (TIM2)
//  14:   camera control (TIM11)
#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, PA0,  2,  0) \
    TIMER_PIN_MAP( 1, PA1,  2,  0) \
    TIMER_PIN_MAP( 2, PA2,  2,  0) \
    TIMER_PIN_MAP( 3, PA3,  2,  0) \
    TIMER_PIN_MAP( 4, PE9,  1,  2) \
    TIMER_PIN_MAP( 5, PE11, 1,  1) \
    TIMER_PIN_MAP( 6, PE13, 1,  1) \
    TIMER_PIN_MAP( 7, PE14, 1,  0) \
    TIMER_PIN_MAP( 8, PD12, 1, -1) \
    TIMER_PIN_MAP( 9, PD13, 1, -1) \
    TIMER_PIN_MAP(10, PD14, 1, -1) \
    TIMER_PIN_MAP(11, PD15, 1, -1) \
    TIMER_PIN_MAP(12, PB5,  1,  0) \
    TIMER_PIN_MAP(13, PB10, 1, -1) \
    TIMER_PIN_MAP(14, PB9,  2, -1)

// DMA
#define ADC1_DMA_OPT         0

// Sensor I2C instances
#define BARO_I2C_INSTANCE    I2CDEV_3
#define MAG_I2C_INSTANCE     I2CDEV_3

// Defaults
#define DEFAULT_BLACKBOX_DEVICE      BLACKBOX_DEVICE_FLASH
#define DEFAULT_CURRENT_METER_SOURCE CURRENT_METER_ADC
#define DEFAULT_VOLTAGE_METER_SOURCE VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SCALE  179
#define DEFAULT_VOLTAGE_METER_SCALE  110
#define DEFAULT_DSHOT_BITBANG        DSHOT_BITBANG_AUTO

// SPI instances
#define FLASH_SPI_INSTANCE   SPI2
#define GYRO_1_SPI_INSTANCE  SPI1
#define GYRO_1_ALIGN         CW90_DEG_FLIP
