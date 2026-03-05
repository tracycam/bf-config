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

#define FC_TARGET_MCU     STM32F7X2

#define BOARD_NAME        HXJL_F722_V5
#define MANUFACTURER_ID   HXJL

#define USE_ACC
#define USE_ACC_SPI_ICM42688P
#define USE_GYRO
#define USE_GYRO_SPI_ICM42688P
#define USE_FLASH
#define USE_FLASH_W25Q128FV
#define USE_BARO
//#define USE_BARO_BMP280
#define USE_BARO_DPS310
//#define USE_BARO_LPS22DF
#define USE_BARO_LPS22H
#define USE_MAG
#define USE_MAG_HMC5883
#define USE_MAG_QMC5883L
#define USE_MAG_IST8310

#define USE_GPS

// LED_STRIP disabled, PA15 used for SERVO1
//#define USE_LED_STRIP

#define BEEPER_PIN           PB0
#define BEEPER_PWM_HZ        4000

#define MOTOR1_PIN           PC8
#define MOTOR2_PIN           PB6
#define MOTOR3_PIN           PC9
#define MOTOR4_PIN           PB7

// PA15 changed from LED_STRIP to SERVO1
//#define LED_STRIP_PIN        PA15
#define SERVO1_PIN           PA15

#define UART1_TX_PIN         PA9
#define UART2_TX_PIN         PA2
#define UART3_TX_PIN         PC10
#define UART4_TX_PIN         PA0
#define UART5_TX_PIN         PC12
#define UART6_TX_PIN         PC6
#define UART1_RX_PIN         PA10
#define UART3_RX_PIN         PC11
#define UART4_RX_PIN         PA1
#define UART5_RX_PIN         PD2
#define UART6_RX_PIN         PC7

#define I2C1_SCL_PIN         PB8
#define I2C1_SDA_PIN         PB9

#define LED0_PIN             PB12
#define SPI1_SCK_PIN         PA5
//#define SPI2_SCK_PIN         PB13
#define SPI3_SCK_PIN         PB3
#define SPI1_SDI_PIN         PA6
//#define SPI2_SDI_PIN         PB14
#define SPI3_SDI_PIN         PB4
#define SPI1_SDO_PIN         PA7
//#define SPI2_SDO_PIN         PB15
#define SPI3_SDO_PIN         PB5

#define CAMERA_CONTROL_PIN   PA8

#define ADC_VBAT_PIN         PC0
//#define ADC_RSSI_PIN         PC2
#define ADC_CURR_PIN         PC1
#define PINIO1_PIN           PB13
#define PINIO2_PIN           PB11

#define FLASH_CS_PIN         PA3

#define GYRO_1_EXTI_PIN      PC3
#define GYRO_1_CS_PIN        PB10

#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, PA15, 1,  0) \
    TIMER_PIN_MAP( 1, PA8 , 1,  0) \
    TIMER_PIN_MAP( 2, PC8 , 2,  0) \
    TIMER_PIN_MAP( 3, PB6 , 1,  0) \
    TIMER_PIN_MAP( 4, PC9 , 2,  0) \
    TIMER_PIN_MAP( 5, PB7 , 1,  0) \
    TIMER_PIN_MAP( 6, PB0 , 2,  -1) \

#define ADC1_DMA_OPT        1

#define BARO_I2C_INSTANCE (I2CDEV_1)
#define DEFAULT_BLACKBOX_DEVICE     BLACKBOX_DEVICE_FLASH
#define DEFAULT_DSHOT_BURST DSHOT_DMAR_ON
#define DEFAULT_CURRENT_METER_SOURCE CURRENT_METER_ADC
#define DEFAULT_VOLTAGE_METER_SOURCE VOLTAGE_METER_ADC
#define BEEPER_INVERTED

#define PINIO1_CONFIG 129
#define PINIO2_CONFIG 129
#define PINIO1_BOX 40
#define PINIO2_BOX 41
#define FLASH_SPI_INSTANCE SPI3
#define GYRO_1_SPI_INSTANCE SPI1

#define MSP_DISPLAYPORT_UART    SERIAL_PORT_UART5
#define MSP_UART                SERIAL_PORT_USART6

// Gyro alignment changed from CW0_DEG_FLIP to CW180_DEG
#define GYRO_1_ALIGN CW180_DEG
