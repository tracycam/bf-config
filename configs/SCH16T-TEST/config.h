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

#define FC_TARGET_MCU        STM32H743

#define BOARD_NAME           SCH16T_TEST
#define MANUFACTURER_ID      ARBT

#define USE_ACC
#define USE_GYRO
#define USE_ACCGYRO_SCH16T
#define USE_BARO
#define USE_BARO_LPS22H
#define USE_FLASH
#define USE_FLASH_W25N01G
#define USE_FLASH_W25Q128FV
#define USE_MAX7456

// Beeper - PE3 [pin 2]
#define BEEPER_PIN           PE3
#define BEEPER_INVERTED

// Motors - TIM5(PA0-PA3) + TIM3(PB0-PB1) + TIM8(PC8-PC9)
#define MOTOR1_PIN           PA0
#define MOTOR2_PIN           PA1
#define MOTOR3_PIN           PA2
#define MOTOR4_PIN           PA3
#define MOTOR5_PIN           PB0
#define MOTOR6_PIN           PB1
#define MOTOR7_PIN           PC8
#define MOTOR8_PIN           PC9

// Servos - TIM4(PD12-PD15) [pins 59-62]
#define SERVO1_PIN           PD12
#define SERVO2_PIN           PD13
#define SERVO3_PIN           PD14
#define SERVO4_PIN           PD15

// LED strip - PA8 [pin 67], TIM1_CH1
#define LED_STRIP_PIN        PA8

// UART - 8 channels
#define UART1_TX_PIN         PA9
#define UART1_RX_PIN         PA10
#define UART2_TX_PIN         PD5
#define UART2_RX_PIN         PD6
#define UART3_TX_PIN         PD8
#define UART3_RX_PIN         PD9
#define UART4_TX_PIN         PD1
#define UART4_RX_PIN         PD0
#define UART5_TX_PIN         PC12
#define UART5_RX_PIN         PD2
#define UART6_TX_PIN         PC6
#define UART6_RX_PIN         PC7
#define UART7_TX_PIN         PE8
#define UART7_RX_PIN         PE7
#define UART8_TX_PIN         PE1
#define UART8_RX_PIN         PE0

// I2C
#define I2C1_SCL_PIN         PB8
#define I2C1_SDA_PIN         PB9
#define I2C2_SCL_PIN         PB10
#define I2C2_SDA_PIN         PB11

// Status LED
#define LED0_PIN             PE4

// SPI1 - Gyro 1 [pins 28-31 area]
#define SPI1_SCK_PIN         PA5
#define SPI1_SDI_PIN         PA6
#define SPI1_SDO_PIN         PA7

// SPI2 - OSD [pins 51-54 area]
#define SPI2_SCK_PIN         PB13
#define SPI2_SDI_PIN         PB14
#define SPI2_SDO_PIN         PB15

// SPI3 - Flash [pins 77-79 area]
#define SPI3_SCK_PIN         PC10
#define SPI3_SDI_PIN         PC11
#define SPI3_SDO_PIN         PB2

// SPI4 - Gyro 2 [pins 42-44 area]
#define SPI4_SCK_PIN         PE12
#define SPI4_SDI_PIN         PE13
#define SPI4_SDO_PIN         PE14

// ADC - 4 firmware channels (hardware supports 6, PC2_C/PC3_C reserved for AUX)
#define ADC_VBAT_PIN         PC0
#define ADC_CURR_PIN         PC1
#define ADC_RSSI_PIN         PC4
#define ADC_EXTERNAL1_PIN    PC5

// PINIO
#define PINIO1_PIN           PD10
#define PINIO2_PIN           PD11

// Gyro 1 - SPI1, CS/EXTI/RST for SCH16T-K10
#define GYRO_1_CS_PIN        PA4
#define GYRO_1_EXTI_PIN      PE5
#define GYRO_1_RST_PIN       PE9

// OSD - SPI2, CS adjacent [pin 51]
#define MAX7456_SPI_CS_PIN   PB12
#define MAX7456_SPI_INSTANCE SPI2

// Flash - SPI3, CS adjacent [pin 77]
#define FLASH_CS_PIN         PA15
#define FLASH_SPI_INSTANCE   SPI3

// CAN - FDCAN2, PB5/PB6 [pins 91-92]
#define FDCAN2_TX            PB6
#define FDCAN2_RX            PB5

// USB detect
#define USB_DETECT_PIN       PE6

// Timer pin mapping
//  0-7: motors (DSHOT)
//  8-11: servos (TIM4, standard PWM)
//  12: LED strip
#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, PA0,  2,  0) \
    TIMER_PIN_MAP( 1, PA1,  2,  1) \
    TIMER_PIN_MAP( 2, PA2,  2,  2) \
    TIMER_PIN_MAP( 3, PA3,  2,  3) \
    TIMER_PIN_MAP( 4, PB0,  2,  4) \
    TIMER_PIN_MAP( 5, PB1,  2,  5) \
    TIMER_PIN_MAP( 6, PC8,  2,  6) \
    TIMER_PIN_MAP( 7, PC9,  2,  7) \
    TIMER_PIN_MAP( 8, PD12, 1, -1) \
    TIMER_PIN_MAP( 9, PD13, 1, -1) \
    TIMER_PIN_MAP(10, PD14, 1, -1) \
    TIMER_PIN_MAP(11, PD15, 1, -1) \
    TIMER_PIN_MAP(12, PA8,  1,  8)

// DMA options
#define ADC1_DMA_OPT         9
#define ADC3_DMA_OPT         10
#define TIMUP5_DMA_OPT       11
#define TIMUP3_DMA_OPT       12
#define TIMUP8_DMA_OPT       0

// Sensor I2C instances
#define BARO_I2C_INSTANCE    I2CDEV_1
#define MAG_I2C_INSTANCE     I2CDEV_2

// Defaults
#define DEFAULT_BLACKBOX_DEVICE        BLACKBOX_DEVICE_FLASH
#define DEFAULT_GYRO_TO_USE            GYRO_CONFIG_USE_GYRO_1
#define DEFAULT_CURRENT_METER_SOURCE   CURRENT_METER_ADC
#define DEFAULT_VOLTAGE_METER_SOURCE   VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SCALE    250
#define DEFAULT_VOLTAGE_METER_SCALE    110

#define GYRO_1_SPI_INSTANCE  SPI1
#define GYRO_1_ALIGN         CW0_DEG

#define PINIO1_BOX           40
#define PINIO2_BOX           41
#define PINIO1_CONFIG        129
#define PINIO2_CONFIG        129
