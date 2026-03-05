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

#define BOARD_NAME DSF722BT
#define MANUFACTURER_ID DSRC

#define USE_ACC
#define USE_ACC_SPI_ICM42688P
#define USE_GYRO
#define USE_GYRO_SPI_ICM42688P
#define USE_ACCGYRO_IIM42652
#define USE_ACC_SPI_LSM6DSV16X
#define USE_GYRO_SPI_LSM6DSV16X
#define USE_ACCGYRO_LSM6DSV16X
#define USE_FLASH
#define USE_FLASH_PY25Q128HA
#define USE_BARO
#define USE_BARO_BMP280
#define USE_BARO_DPS310
#define USE_MAG
#define USE_MAG_HMC5883
#define USE_GPS

#define USE_LED_STRIP

#define BEEPER_PIN PB2
#define MOTOR1_PIN PA10
#define MOTOR2_PIN PA9
#define MOTOR3_PIN PC9
#define MOTOR4_PIN PC8
#define SERVO1_PIN PA6
#define SERVO2_PIN PA7 

#define RX_PPM_PIN PA3

#define LED_STRIP_PIN PB1
#define UART1_TX_PIN PB6
#define UART2_TX_PIN PA2
#define UART3_TX_PIN PC10
#define UART4_TX_PIN PA0
#define UART5_TX_PIN PC12
#define UART6_TX_PIN PC6

#define UART1_RX_PIN PB7
#define UART2_RX_PIN PA3
#define UART3_RX_PIN PC11
#define UART4_RX_PIN PA1
#define UART5_RX_PIN PD2
#define UART6_RX_PIN PC7

#define I2C1_SCL_PIN PB8
#define I2C1_SDA_PIN PB9

#define LED0_PIN PB0

//#define SPI1_SCK_PIN PA5
#define SPI2_SCK_PIN PB13
#define SPI3_SCK_PIN PB3
//#define SPI1_SDI_PIN PA6
#define SPI2_SDI_PIN PB14
#define SPI3_SDI_PIN PB4
//#define SPI1_SDO_PIN PA7
#define SPI2_SDO_PIN PB15
#define SPI3_SDO_PIN PB5
#define ESCSERIAL_PIN PC7

#define ADC_VBAT_PIN PC1
#define ADC_CURR_PIN PC2

#define FLASH_CS_PIN PA15

#define USE_GYRO_CLKIN
#define GYRO_1_EXTI_PIN PB12
#define GYRO_1_CS_PIN PA8
#define GYRO_1_CLKIN_PIN PB11

#define PINIO1_PIN PC4 //BT
#define PINIO1_BOX 40

#define PINIO2_PIN PC13 //CAM Switch
#define PINIO2_BOX 41


#define TIMER_PIN_MAPPING \
    TIMER_PIN_MAP( 0, PA3, 2, 0) \
    TIMER_PIN_MAP( 1, PC9, 2, 0) \
    TIMER_PIN_MAP( 2, PC8, 2, 1) \
    TIMER_PIN_MAP( 3, PA9, 1, 1) \
    TIMER_PIN_MAP( 4, PA10, 1, 1) \
    TIMER_PIN_MAP( 5, PB1, 2, 0) \
    TIMER_PIN_MAP( 6, PB11, 1, -1) \
    TIMER_PIN_MAP( 7, PA6, 2, 0) \
    TIMER_PIN_MAP( 8, PA7, 4, 0) \

#define ADC1_DMA_OPT 0

#define DEFAULT_BLACKBOX_DEVICE     BLACKBOX_DEVICE_FLASH
#define DEFAULT_DSHOT_BURST DSHOT_DMAR_ON
#define DEFAULT_CURRENT_METER_SOURCE CURRENT_METER_ADC
#define DEFAULT_VOLTAGE_METER_SOURCE VOLTAGE_METER_ADC
#define DEFAULT_CURRENT_METER_SCALE 250
#define BEEPER_INVERTED
#define SYSTEM_HSE_MHZ 8
#define OSD_CANVAS_SIZE_DEBUG

#define MAG_I2C_INSTANCE (I2CDEV_1)
#define BARO_I2C_INSTANCE (I2CDEV_1)
#define GYRO_1_SPI_INSTANCE SPI2
#define FLASH_SPI_INSTANCE SPI3
#define GYRO_1_ALIGN CW0_DEG

#define MSP_DISPLAYPORT_UART    SERIAL_PORT_UART4

#define SERIALRX_UART SERIAL_PORT_USART2
#define SERIALRX_PROVIDER SERIALRX_CRSF

#define MSP_UART SERIAL_PORT_USART1
