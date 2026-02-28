# STM32H743VIT6 Betaflight Dual-Gyro Pinout Design

> **MCU**: STM32H743VIT6 (LQFP100)
> **Core**: Arm Cortex-M7 @ 480MHz
> **Flash**: 2MB | **RAM**: 1MB
> **Config**: AIRBOTSTDH743

---

## 1. LQFP100 封装限制

LQFP100 封装下以下端口 **不可用或受限**：

| 端口 | 状态 |
|------|------|
| PF0 - PF15 | 全部缺失 |
| PG0 - PG15 | 全部缺失 |
| PH2 - PH15 | 仅 PH0/PH1 可用（HSE 晶振） |
| PI0 - PI15 | 全部缺失 |
| PJ / PK | 全部缺失 |
| PC2, PC3 | 封装提供 PC2_C/PC3_C（模拟专用引脚），仅限模拟输入，可用作 ADC |

可用 GPIO 端口：PA0-PA15、PB0-PB15、PC0-PC1/PC4-PC13、PD0-PD15、PE0-PE15

---

## 2. 系统保留引脚

| 引脚 | Pin# | 功能 | 备注 |
|------|:----:|------|------|
| PA13 | 72 | SWDIO | SWD 调试接口 |
| PA14 | 76 | SWCLK | SWD 调试接口 |
| PA11 | 70 | USB_DM | OTG_FS, AF10 |
| PA12 | 71 | USB_DP | OTG_FS, AF10 |
| PH0 | 12 | HSE_IN | 高速外部晶振输入 |
| PH1 | 13 | HSE_OUT | 高速外部晶振输出 |

---

## 3. 双陀螺仪 SPI 总线

### 设计原则

**物理邻近性优化**：每个陀螺仪的 CS、EXTI 引脚尽量与其 SPI 总线引脚在 LQFP100 封装上物理相邻，缩短 PCB 走线，降低 EMI。

### Gyro 1 — SPI1（左下角，Pin 28-31 区域）

| 信号 | 引脚 | Pin# | AF | 说明 |
|------|:----:|:----:|:--:|------|
| SCK | PA5 | 29 | AF5 | SPI1_SCK |
| MISO | PA6 | 30 | AF5 | SPI1_SDI |
| MOSI | PA7 | 31 | AF5 | SPI1_SDO |
| CS | PA4 | 28 | GPIO | **邻接** SPI 总线（Pin 28 紧邻 Pin 29） |
| EXTI | PE9 | 39 | GPIO | 同侧芯片（底部边），8 pin 距离 |

### Gyro 2 — SPI4（底部，Pin 42-44 区域）

| 信号 | 引脚 | Pin# | AF | 说明 |
|------|:----:|:----:|:--:|------|
| SCK | PE12 | 42 | AF5 | SPI4_SCK |
| MISO | PE13 | 43 | AF5 | SPI4_SDI |
| MOSI | PE14 | 44 | AF5 | SPI4_SDO |
| CS | PE11 | 41 | GPIO | **邻接** SPI 总线（Pin 41 紧邻 Pin 42） |
| EXTI | PE15 | 45 | GPIO | **邻接** SPI 总线（Pin 45 紧邻 Pin 44） |

### IMUCLK — 共享外部时钟（TIM15）

> Betaflight 固件限制：`pwmGyroClk` 为全局唯一 PWM 输出，两个陀螺仪 **必须共享同一 CLKIN 引脚**。
> 第二个陀螺仪初始化时检查 `pwmGyroClk.io == io`，不同引脚会导致 CLKIN 初始化失败。
>
> PE5[4] 使用 TIM15_CH1 产生 32kHz 外部参考时钟，PCB 上从 PE5 拉两条走线分别至两个陀螺仪的 CLKIN 输入。
> 32kHz 低频信号对走线长度不敏感，跨芯片边走线无信号完整性问题。

| 信号 | 引脚 | Pin# | Timer | AF | 说明 |
|------|:----:|:----:|:-----:|:--:|------|
| GYRO_CLKIN (shared) | PE5 | 4 | TIM15_CH1 | AF4 | PCB 分两路至 Gyro1/Gyro2 |

---

## 4. OSD — SPI2（右侧底部，Pin 51-54 区域）

| 信号 | 引脚 | Pin# | AF | 说明 |
|------|:----:|:----:|:--:|------|
| SCK | PB13 | 52 | AF5 | SPI2_SCK |
| MISO | PB14 | 53 | AF5 | SPI2_SDI |
| MOSI | PB15 | 54 | AF5 | SPI2_SDO |
| CS | PB12 | 51 | GPIO | **邻接** SPI 总线（Pin 51 紧邻 Pin 52） |

> 典型芯片：MAX7456

---

## 5. Flash 黑匣子 — SPI3（顶部右段，Pin 77-79 + Pin 36）

| 信号 | 引脚 | Pin# | AF | 说明 |
|------|:----:|:----:|:--:|------|
| SCK | PC10 | 78 | AF6 | SPI3_SCK |
| MISO | PC11 | 79 | AF6 | SPI3_SDI |
| MOSI | PB2 | 36 | AF7 | SPI3_SDO，需跨芯片走线 |
| CS | PA15 | 77 | GPIO | **邻接** SCK/MISO（Pin 77 紧邻 Pin 78） |

> **⚠ JTAG 释放**：PA15 复位后为 JTDI，固件启动时 **必须** 关闭 JTAG 复用（仅保留 SWD），
> 否则 Flash CS 无法正常工作。此为"没做就直接不工作"的硬性前提条件。
> 典型芯片：W25N01G / W25Q128FV

---

## 6. DSHOT 电机输出（8 通道）

> 分布在 TIM5 + TIM3 + TIM8 三个独立 Timer 上。

| 通道 | 引脚 | Pin# | Timer 通道 | AF | 说明 |
|:----:|:----:|:----:|:----------:|:--:|------|
| M1 | PA0 | 22 | TIM5_CH1 | AF2 | |
| M2 | PA1 | 23 | TIM5_CH2 | AF2 | |
| M3 | PA2 | 24 | TIM5_CH3 | AF2 | |
| M4 | PA3 | 25 | TIM5_CH4 | AF2 | |
| M5 | PB0 | 34 | TIM3_CH3 | AF2 | |
| M6 | PB1 | 35 | TIM3_CH4 | AF2 | |
| M7 | PC8 | 65 | TIM8_CH3 | AF3 | |
| M8 | PC9 | 66 | TIM8_CH4 | AF3 | |

### 设计说明

原设计使用 TIM1(PE9/PE11/PE13/PE14) + TIM8 驱动电机，但 PE11-PE14 现已分配给 SPI4（Gyro 2），
因此电机输出改用 TIM5 + TIM3 + TIM8 方案。Betaflight 完全支持在通用定时器上运行 DSHOT。

---

## 7. 舵机输出（4 通道）

> 使用 TIM4 的 4 个通道，标准 PWM 输出（50-333Hz）。
> PD12-PD15 位于芯片顶部边（Pin 59-62），物理相邻。

| 通道 | 引脚 | Pin# | Timer 通道 | AF |
|:----:|:----:|:----:|:----------:|:--:|
| S1 | PD12 | 59 | TIM4_CH1 | AF2 |
| S2 | PD13 | 60 | TIM4_CH2 | AF2 |
| S3 | PD14 | 61 | TIM4_CH3 | AF2 |
| S4 | PD15 | 62 | TIM4_CH4 | AF2 |

---

## 8. LED 灯带（1 通道）

| 引脚 | Pin# | Timer 通道 | AF |
|:----:|:----:|:----------:|:--:|
| PA8 | 67 | TIM1_CH1 | AF1 |

---

## 9. UART 串口（8 通道）

| 序号 | 外设 | TX 引脚 | TX Pin# | RX 引脚 | RX Pin# | AF | DFU 风险 |
|:----:|:----:|:-------:|:-------:|:-------:|:-------:|:--:|:--------:|
| 1 | USART1 | PA9 | 68 | PA10 | 69 | AF7 | **HIGH** |
| 2 | USART2 | PD5 | 86 | PD6 | 87 | AF7 | 安全 |
| 3 | USART3 | PD8 | 55 | PD9 | 56 | AF7 | 安全 |
| 4 | UART4 | PD1 | 82 | PD0 | 81 | AF8 | 安全 |
| 5 | UART5 | PC12 | 80 | PD2 | 83 | AF8 | 安全 |
| 6 | USART6 | PC6 | 63 | PC7 | 64 | AF7 | 安全 |
| 7 | UART7 | PE8 | 38 | PE7 | 37 | AF7 | 安全 |
| 8 | UART8 | PE1 | 98 | PE0 | 97 | AF8 | 安全 |

### 变更说明

- UART4 改用 PD1/PD0（AF8），原 PA0/PA1 释放给电机
- PD0/PD1 原为 FDCAN1，已被 UART4 占用
- CAN 使用 FDCAN2（PB5/PB6, AF9），无需牺牲 UART4

---

## 10. I2C 总线（2 路）

| I2C | SCL | SCL Pin# | SDA | SDA Pin# | AF | 用途 |
|:---:|:---:|:--------:|:---:|:--------:|:--:|------|
| I2C1 | PB8 | 95 | PB9 | 96 | AF4 | 气压计 (LPS22H)、磁力计 |
| I2C2 | PB10 | 46 | PB11 | 47 | AF4 | 外部磁力计 / 扩展 |

---

## 11. ADC 模拟输入（6 通道硬件 / 4 通道固件）

| 用途 | 引脚 | Pin# | ADC 通道 | 固件支持 | 说明 |
|------|:----:|:----:|:--------:|:--------:|------|
| VBAT 电压检测 | PC0 | 15 | ADC123_INP10 | ADC_VBAT_PIN | 经分压电阻接入 |
| 电流传感器 | PC1 | 16 | ADC123_INP11 | ADC_CURR_PIN | 电流计模拟输出 |
| RSSI 模拟输入 | PC4 | 32 | ADC12_INP4 | ADC_RSSI_PIN | 接收机 RSSI |
| AIRSPEED 空速 | PC5 | 33 | ADC12_INP8 | ADC_EXTERNAL1_PIN | 空速传感器模拟输出 |
| AUX1 备用 | PC2_C | 17 | ADC3_INP0 | *硬件预留* | 需通过内部模拟开关，固件暂不支持 |
| AUX2 备用 | PC3_C | 18 | ADC3_INP1 | *硬件预留* | 需通过内部模拟开关，固件暂不支持 |

> **注**：当前 Betaflight 固件支持 4 个外部 ADC 通道（VBAT、CURRENT、RSSI、EXTERNAL1）。
> AUX1/AUX2 已在 PCB 上引出焊盘，固件扩展后即可启用。
> PC2_C/PC3_C 属于 LQFP100 的模拟专用引脚，工作在模拟模式时无需额外 AF 配置。

---

## 12. DFU Bootloader 劫持分析

### STM32H74x Bootloader 激活的 UART 引脚

| Bootloader 接口 | TX 引脚 | RX 引脚 | 本设计中该引脚用途 | 劫持风险 |
|:---------------:|:-------:|:-------:|:-----------------:|:--------:|
| USART1 主 | PA9 | PA10 | **USART1 (串口1)** | **HIGH** |
| USART1 备 | PB14 | PB15 | SPI2 MISO/MOSI | LOW — SPI 从设备高阻 |
| USART2 | PA2 | PA3 | DSHOT M3/M4 | LOW — ESC 不发 UART 帧 |
| USART3 | PB10 | PB11 | I2C2 SCL/SDA | NONE — I2C 空闲高电平 |

### 风险缓解

1. 避免将持续输出数据的设备（GPS、遥测）接到 UART1
2. UART1 推荐接需主动请求才发送的设备（ESC Telemetry）
3. 硬件设计中 BOOT0 引脚（Pin 94）应下拉

---

## 13. Timer 资源总览

| Timer | 类型 | 分配用途 | 使用通道 | 冲突 |
|:-----:|:----:|:--------:|:--------:|:----:|
| TIM1 | Advanced 16-bit | LED Strip | CH1 (PA8) | 无 |
| TIM3 | General 16-bit | DSHOT M5-M6 | CH3, CH4 | 无 |
| TIM4 | General 16-bit | Servo S1-S4 | CH1-CH4 (PD12-PD15) | 无 |
| TIM5 | General 32-bit | DSHOT M1-M4 | CH1-CH4 | 无 |
| TIM8 | Advanced 16-bit | DSHOT M7-M8 | CH3, CH4 | 无 |
| TIM15 | Advanced 16-bit | IMUCLK | CH1 (PE5) | 无 |
| TIM2 | General 32-bit | *未分配* | — | 备用 |
| TIM12-14,16-17 | GP / LP | *未分配* | — | 备用 |

> 6 个已分配 Timer 完全独立，无时基冲突。
> TIM2 保留供 Softserial 或其他扩展使用。

---

## 14. 其他 GPIO 分配

| 引脚 | Pin# | 功能 | 说明 |
|:----:|:----:|------|------|
| PE3 | 2 | 蜂鸣器 | GPIO，反相驱动 |
| PE4 | 3 | 状态 LED | GPIO |
| PE6 | 5 | USB 检测 | GPIO 输入 |
| PD10 | 57 | PINIO1 | 可编程 IO（VTX 电源控制等） |
| PD11 | 58 | PINIO2 | 可编程 IO（摄像头切换等） |

---

## 15. 冲突检查清单

| 检查项 | 状态 | 说明 |
|--------|:----:|------|
| 引脚唯一性 | OK | 每个引脚仅分配一个功能 |
| Timer 独立性 | OK | TIM1/TIM3/TIM4/TIM5/TIM8/TIM15 六个 Timer 互不共享 |
| DSHOT Timer 兼容 | OK | 全部 8 路 DSHOT 在 TIM5/TIM3/TIM8 上 |
| Servo Timer 独立 | OK | TIM4 专用于 4 路舵机，不与 DSHOT 共享 |
| IMUCLK 独立 Timer | OK | TIM15 专用于 32kHz 时钟生成，不与 DSHOT/Servo 共享 |
| IMUCLK 共享引脚 | OK | 双陀螺仪共用 PE5，符合固件 pwmGyroClk 全局单 PWM 限制 |
| LED 独立 Timer | OK | TIM1 不与 DSHOT、Servo 或 IMUCLK 共享 |
| SPI 4 路可用 | OK | SPI1(Gyro1)/SPI2(OSD)/SPI3(Flash)/SPI4(Gyro2) 无冲突 |
| Gyro CS/EXTI 邻近 | OK | CS 引脚均紧邻对应 SPI 总线，EXTI 在同侧 |
| UART 引脚无冲突 | OK | 8 路 UART 均使用独立引脚对 |
| UART DFU 劫持 | WARN | 仅 USART1 (PA9/PA10) 存在风险 |
| ADC 模拟模式 | OK | 6 路 ADC 均为模拟输入，不占 AF |
| I2C 引脚无冲突 | OK | I2C1(PB8/PB9)、I2C2(PB10/PB11) 专用 |
| USB 保留 | OK | PA11/PA12 保留给 OTG_FS |
| SWD 保留 | OK | PA13/PA14 保留给调试接口 |
| **JTAG 释放** | **必须** | **PA15 用作 Flash CS，固件必须关闭 JTAG（仅保留 SWD），否则 Flash 不工作** |

---

## 16. 剩余空闲 GPIO

```
PB: PB3(89), PB4(90), PB7(93)
PC: PC13(7)
PD: PD3(84), PD4(85), PD7(88)
PE: PE2(1), PE10(40)
```

> 共 8 个空闲 GPIO 可用于：
> - LPUART1 (PB7=RX, AF8 + 其他空闲 TX) 作为额外串口
> - 额外按键、LED 指示灯
> - Softserial

---

## 17. 引脚总图

> 引脚编号严格依据 DS12110 Rev 7 — Figure 5（LQFP100 Top View）。

```
                         STM32H743VIT6 (LQFP100)
                                Top View

                      pin 76 ←─────────────→ pin 100
                      ┌─────────────────────────────┐
            PE2  [ 1] │                             │ [100] VDD
   BEEP  →  PE3  [ 2] │                             │ [ 99] VSS
   LED0  →  PE4  [ 3] │                             │ [ 98] PE1   ← U8TX
  CLKIN  →  PE5  [ 4] │                             │ [ 97] PE0   ← U8RX
   USBD  →  PE6  [ 5] │                             │ [ 96] PB9   ← I2C1D
            VBAT [ 6] │                             │ [ 95] PB8   ← I2C1C
            PC13 [ 7] │                             │ [ 94] BOOT0
   LSE   →  PC14 [ 8] │                             │ [ 93] PB7
   LSE   →  PC15 [ 9] │                             │ [ 92] PB6   ← CANTX
            VSS  [10] │                             │ [ 91] PB5   ← CANRX
            VDD  [11] │                             │ [ 90] PB4
   HSE   →  PH0  [12] │                             │ [ 89] PB3
   HSE   →  PH1  [13] │                             │ [ 88] PD7
            NRST [14] │                             │ [ 87] PD6   ← U2RX
   VBAT  →  PC0  [15] │                             │ [ 86] PD5   ← U2TX
   CURR  →  PC1  [16] │                             │ [ 85] PD4
   AUX1  →  PC2C [17] │                             │ [ 84] PD3
   AUX2  →  PC3C [18] │                             │ [ 83] PD2   ← U5RX
            VSSA [19] │                             │ [ 82] PD1   ← U4TX
           VREF+ [20] │                             │ [ 81] PD0   ← U4RX
            VDDA [21] │                             │ [ 80] PC12  ← U5TX
   M1    →  PA0  [22] │                             │ [ 79] PC11  ← SPI3I
   M2    →  PA1  [23] │                             │ [ 78] PC10  ← SPI3K
   M3    →  PA2  [24] │                             │ [ 77] PA15  ← FLCS ⚠JTAG
   M4    →  PA3  [25] │                             │ [ 76] PA14  ← SWCLK
            VSS  [26] │                             │ [ 75] VDD
            VDD  [27] │                             │ [ 74] VSS
   G1CS  →  PA4  [28] │                             │ [ 73] VCAP
  SPI1K  →  PA5  [29] │                             │ [ 72] PA13  ← SWDIO
  SPI1I  →  PA6  [30] │                             │ [ 71] PA12  ← USB_DP
  SPI1O  →  PA7  [31] │                             │ [ 70] PA11  ← USB_DM
   RSSI  →  PC4  [32] │                             │ [ 69] PA10  ← U1RX ⚠DFU
   EXT1  →  PC5  [33] │                             │ [ 68] PA9   ← U1TX ⚠DFU
   M5    →  PB0  [34] │                             │ [ 67] PA8   ← LED
   M6    →  PB1  [35] │                             │ [ 66] PC9   ← M8
  SPI3O  →  PB2  [36] │                             │ [ 65] PC8   ← M7
   U7RX  →  PE7  [37] │                             │ [ 64] PC7   ← U6RX
   U7TX  →  PE8  [38] │                             │ [ 63] PC6   ← U6TX
  G1EXT  →  PE9  [39] │                             │ [ 62] PD15  ← SRV4
            PE10 [40] │                             │ [ 61] PD14  ← SRV3
   G2CS  →  PE11 [41] │                             │ [ 60] PD13  ← SRV2
  SPI4K  →  PE12 [42] │                             │ [ 59] PD12  ← SRV1
  SPI4I  →  PE13 [43] │                             │ [ 58] PD11  ← PINIO2
  SPI4O  →  PE14 [44] │                             │ [ 57] PD10  ← PINIO1
  G2EXT  →  PE15 [45] │                             │ [ 56] PD9   ← U3RX
  I2C2C  →  PB10 [46] │                             │ [ 55] PD8   ← U3TX
  I2C2D  →  PB11 [47] │                             │ [ 54] PB15  ← SPI2O
            VCAP [48] │                             │ [ 53] PB14  ← SPI2I
            VSS  [49] │                             │ [ 52] PB13  ← SPI2K
            VDD  [50] │                             │ [ 51] PB12  ← OSDCS
                      └─────────────────────────────┘
```

---

## 18. 完整引脚分配速查表

| 引脚 | Pin# | 功能 | AF / 模式 | 所属外设 |
|:----:|:----:|------|:---------:|:--------:|
| PA0 | 22 | TIM5_CH1 (M1) | AF2 | DSHOT |
| PA1 | 23 | TIM5_CH2 (M2) | AF2 | DSHOT |
| PA2 | 24 | TIM5_CH3 (M3) | AF2 | DSHOT |
| PA3 | 25 | TIM5_CH4 (M4) | AF2 | DSHOT |
| PA4 | 28 | GYRO_1_CS | GPIO Output | SPI1 |
| PA5 | 29 | SPI1_SCK | AF5 | SPI1 |
| PA6 | 30 | SPI1_SDI | AF5 | SPI1 |
| PA7 | 31 | SPI1_SDO | AF5 | SPI1 |
| PA8 | 67 | TIM1_CH1 (LED) | AF1 | LED Strip |
| PA9 | 68 | USART1_TX | AF7 | USART1 |
| PA10 | 69 | USART1_RX | AF7 | USART1 |
| PA11 | 70 | USB_DM | AF10 | USB |
| PA12 | 71 | USB_DP | AF10 | USB |
| PA13 | 72 | SWDIO | AF0 | SWD |
| PA14 | 76 | SWCLK | AF0 | SWD |
| PA15 | 77 | FLASH_CS | GPIO Output | SPI3 ⚠需关闭 JTAG |
| PB0 | 34 | TIM3_CH3 (M5) | AF2 | DSHOT |
| PB1 | 35 | TIM3_CH4 (M6) | AF2 | DSHOT |
| PB2 | 36 | SPI3_SDO | AF7 | SPI3 |
| PB5 | 91 | FDCAN2_RX | AF9 | CAN |
| PB6 | 92 | FDCAN2_TX | AF9 | CAN |
| PB8 | 95 | I2C1_SCL | AF4 | I2C1 |
| PB9 | 96 | I2C1_SDA | AF4 | I2C1 |
| PB10 | 46 | I2C2_SCL | AF4 | I2C2 |
| PB11 | 47 | I2C2_SDA | AF4 | I2C2 |
| PB12 | 51 | MAX7456_CS | GPIO Output | SPI2 |
| PB13 | 52 | SPI2_SCK | AF5 | SPI2 |
| PB14 | 53 | SPI2_SDI | AF5 | SPI2 |
| PB15 | 54 | SPI2_SDO | AF5 | SPI2 |
| PC0 | 15 | ADC_VBAT | Analog | ADC |
| PC1 | 16 | ADC_CURR | Analog | ADC |
| PC2_C | 17 | ADC_AUX1 | Analog | ADC (预留) |
| PC3_C | 18 | ADC_AUX2 | Analog | ADC (预留) |
| PC4 | 32 | ADC_RSSI | Analog | ADC |
| PC5 | 33 | ADC_AIRSPEED | Analog | ADC |
| PC6 | 63 | USART6_TX | AF7 | USART6 |
| PC7 | 64 | USART6_RX | AF7 | USART6 |
| PC8 | 65 | TIM8_CH3 (M7) | AF3 | DSHOT |
| PC9 | 66 | TIM8_CH4 (M8) | AF3 | DSHOT |
| PC10 | 78 | SPI3_SCK | AF6 | SPI3 |
| PC11 | 79 | SPI3_SDI | AF6 | SPI3 |
| PC12 | 80 | UART5_TX | AF8 | UART5 |
| PD0 | 81 | UART4_RX | AF8 | UART4 |
| PD1 | 82 | UART4_TX | AF8 | UART4 |
| PD2 | 83 | UART5_RX | AF8 | UART5 |
| PD5 | 86 | USART2_TX | AF7 | USART2 |
| PD6 | 87 | USART2_RX | AF7 | USART2 |
| PD8 | 55 | USART3_TX | AF7 | USART3 |
| PD9 | 56 | USART3_RX | AF7 | USART3 |
| PD10 | 57 | PINIO1 | GPIO Output | PINIO |
| PD11 | 58 | PINIO2 | GPIO Output | PINIO |
| PD12 | 59 | TIM4_CH1 (SERVO1) | AF2 | Servo |
| PD13 | 60 | TIM4_CH2 (SERVO2) | AF2 | Servo |
| PD14 | 61 | TIM4_CH3 (SERVO3) | AF2 | Servo |
| PD15 | 62 | TIM4_CH4 (SERVO4) | AF2 | Servo |
| PE0 | 97 | UART8_RX | AF8 | UART8 |
| PE1 | 98 | UART8_TX | AF8 | UART8 |
| PE3 | 2 | 蜂鸣器 | GPIO Output | Beeper |
| PE4 | 3 | 状态 LED | GPIO Output | LED |
| PE5 | 4 | TIM15_CH1 (CLKIN) | AF4 | IMUCLK (共享) |
| PE6 | 5 | USB 检测 | GPIO Input | USB |
| PE7 | 37 | UART7_RX | AF7 | UART7 |
| PE8 | 38 | UART7_TX | AF7 | UART7 |
| PE9 | 39 | GYRO_1_EXTI | GPIO Input | EXTI |
| PE11 | 41 | GYRO_2_CS | GPIO Output | SPI4 |
| PE12 | 42 | SPI4_SCK | AF5 | SPI4 |
| PE13 | 43 | SPI4_SDI | AF5 | SPI4 |
| PE14 | 44 | SPI4_SDO | AF5 | SPI4 |
| PE15 | 45 | GYRO_2_EXTI | GPIO Input | EXTI |
| PH0 | 12 | HSE_IN | — | 晶振 |
| PH1 | 13 | HSE_OUT | — | 晶振 |

---

## 19. SPI 总线外设邻近性总结

| SPI | 用途 | 数据引脚 (Pin#) | CS (Pin#) | EXTI (Pin#) | 邻近评价 |
|:---:|------|:---------------:|:---------:|:-----------:|:--------:|
| SPI1 | Gyro 1 | PA5-PA7 (29-31) | PA4 (28) | PE9 (39) | CS 紧邻，EXTI 同侧 |
| SPI2 | OSD | PB13-PB15 (52-54) | PB12 (51) | — | CS 紧邻 |
| SPI3 | Flash | PC10-PC11 (78-79) | PA15 (77) | — | CS 紧邻，MOSI 需走线 |
| SPI4 | Gyro 2 | PE12-PE14 (42-44) | PE11 (41) | PE15 (45) | CS+EXTI 均紧邻 |

---

*Rev 4 — 修正全部 Pin# 标注（依据 DS12110 Rev 7 Figure 5 逐 pin 核对），修正引脚总图，强化 JTAG 释放条件提示。*
*基于 DS12110 Rev 7 (STM32H743 Datasheet) 及 AN2606 Bootloader 引脚参考交叉核对。*
