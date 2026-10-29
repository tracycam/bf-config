/*
 * This file is part of Betaflight.
 *
 * Betaflight is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * Betaflight is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details. You should have received a copy of the GNU General Public
 * License along with Betaflight. If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

/* RATE Racing FC v26.9: board netlist and MCU schematic, 2026-09-18. */
#define FC_TARGET_MCU           CH32H415
#define BOARD_NAME              RATE_H4_RACING
#define MANUFACTURER_ID         RATE
#define TARGET_BOARD_IDENTIFIER "R4RC"
#define USBD_PRODUCT_STRING     "RATE_H4_Racing"
#define SYSTEM_HSE_MHZ          25

#define USE_GYRO
#define USE_ACC
#define USE_GYRO_SPI_ICM42688P
#define USE_ACC_SPI_ICM42688P
#define GYRO_1_SPI_INSTANCE     SPI3
#define GYRO_1_CS_PIN           PF3
#define GYRO_1_EXTI_PIN         PA15
/* Mounting alignment must be checked against the board's forward direction. */

/* IMU CLKIN is wired to PC9. Use the internal clock until an independent
 * timer source can be assigned without sharing TIM8 with the motors. */
#define SPI3_SCK_PIN            PC10
#define SPI3_SDI_PIN            PC11
#define SPI3_SDO_PIN            PC12

#define USE_BARO
#define USE_BARO_DPS310
#define USE_BARO_BMP280
#define I2C2_SCL_PIN            PC0
#define I2C2_SDA_PIN            PC1
#define BARO_I2C_INSTANCE       I2CDEV_2
#define MAG_I2C_INSTANCE        I2CDEV_2

#define SPI2_SCK_PIN            PB13
#define SPI2_SDI_PIN            PB14
#define SPI2_SDO_PIN            PB15
#define SPI4_SCK_PIN            PE12
#define SPI4_SDI_PIN            PE13
#define SPI4_SDO_PIN            PE14
#define FLASH_CS_PIN            PB10
#define FLASH_SPI_INSTANCE      SPI4
#define USE_FLASH
#define USE_FLASH_M25P16

#define MOTOR1_PIN              PE3
#define MOTOR2_PIN              PE4
#define MOTOR3_PIN              PE5
#define MOTOR4_PIN              PE6
#define LED_STRIP_PIN           PB6
#define BEEPER_PIN              PB11
#define BEEPER_INVERTED
#define CAMERA_CONTROL_PIN      PA4

/* DMA2 channel 6 belongs to Theia OSD. Assign separate DMA1 channels to
 * motor outputs, ADC, and LED strip; all require board-level validation. */
#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP(0, PE3, 1, 0) \
    TIMER_PIN_MAP(1, PE4, 1, 1) \
    TIMER_PIN_MAP(2, PE5, 1, 2) \
    TIMER_PIN_MAP(3, PE6, 1, 3) \
    TIMER_PIN_MAP(4, PB6, 1, 5)

#define ADC_INSTANCE            ADC1
#define ADC_VBAT_PIN            PC3
#define ADC_CURR_PIN            PC2
#define ADC1_DMA_OPT            4
#define DEFAULT_VOLTAGE_METER_SOURCE VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SOURCE CURRENT_METER_ADC

#define UART1_TX_PIN            PA9
#define UART1_RX_PIN            PA10
#define UART2_TX_PIN            PA2
#define UART2_RX_PIN            PA3
#define UART3_TX_PIN            PA13
#define UART3_RX_PIN            PA14
#define UART4_TX_PIN            PC6
#define UART4_RX_PIN            PC7
#define UART5_TX_PIN            PE0
#define UART5_RX_PIN            PF5
#define UART6_TX_PIN            PA0
#define UART6_RX_PIN            PA1
#define UART7_RX_PIN            PB12
#define UART8_TX_PIN            PB4
#define UART8_RX_PIN            PB3

/* PC4 is the board LED, but it is owned by the paired OSD core. PA12 is
 * the camera switch and is also reserved for OSD; do not allocate either. */
