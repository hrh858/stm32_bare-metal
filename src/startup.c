#include <stdint.h>

// region Create the vector table
//  For the STM32F411RE we have 82 IRQs, 16 system exceptions and MSP.
//  Then he total memory consumed by the VT is 82+16 words so 98*4=392 bytes.
#define SRAM_START 0x20000000U
#define SRAM_SIZE (128 * 1024) // 128KB
#define SRAM_END ((SRAM_START) + (SRAM_SIZE))

#define STACK_START SRAM_END

void Reset_Handler(void);
// `weak` so the programer can implement the function and overwrite this if
// necessary. `alias` so this fallsback to the `Default_Handler` if the programmer
// does not implement the function.
void NMI_Hanlder(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Hanlder(void) __attribute__((weak, alias("Default_Handler")));
// Do this for all of the interrupts that the microcrontroller expects...
void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVCall_Hanlder(void) __attribute__((weak, alias("Default_Handler")));
void DebugMonitor_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void Systick_Hanlder(void) __attribute__((weak, alias("Default_Handler")));
void WWDG_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI16_PVD_Hanlder(void) __attribute__((weak, alias("Default_Handler")));
void EXTI21_TAMP_STAMP_Hanlder(void) __attribute__((weak, alias("Default_Handler")));
void EXTI22_RTC_WKUP_Hanlder(void) __attribute__((weak, alias("Default_Handler")));
void FLASH_Handler(void) __attribute__((weak, alias("Default_Handler")));
void RCC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream5_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream6_Handler(void) __attribute__((weak, alias("Default_Handler")));
void ADC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI9_5_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_TIM9_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_UP_TIM10_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM11_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM1_CC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C1_EV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C1_ER_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C2_EV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C2_ER_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SPI1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SPI2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void USART1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void USART2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI15_10_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI17_RTC_Alarm_Handler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI18_OTG_FS_WKUP_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Stream7_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SDIO_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIM5_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SPI3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void OTG_FS_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream5_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream6_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2_Stream7_Handler(void) __attribute__((weak, alias("Default_Handler")));
void USART6_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C3_EV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C3_ER_Handler(void) __attribute__((weak, alias("Default_Handler")));
void FPU_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SPI4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SPI5_Handler(void) __attribute__((weak, alias("Default_Handler")));

void Default_Handler(void) {
  while(1);
}

// By default the compiler will put the contents of the `vectors` variable
// in the .data section but we don't want that since we want to put the
// vector table in the correct position in FLASH.
// That's why we need to tell the compiler to put it in a different section.
uint32_t vectors[98] __attribute__((section(".isr_vector"))) = {
    STACK_START,
    (uint32_t)&Reset_Handler,
    (uint32_t)&NMI_Hanlder,
    (uint32_t)&HardFault_Hanlder,
    (uint32_t)&MemManage_Handler,
    (uint32_t)&BusFault_Handler,
    (uint32_t)&UsageFault_Handler,
    0,
    0,
    0,
    0,
    (uint32_t)&SVCall_Hanlder,
    (uint32_t)&DebugMonitor_Handler,
    0,
    (uint32_t)&PendSV_Handler,
    (uint32_t)&Systick_Hanlder,
    (uint32_t)&WWDG_Handler,
    (uint32_t)&EXTI16_PVD_Hanlder,
    (uint32_t)&EXTI21_TAMP_STAMP_Hanlder,
    (uint32_t)&EXTI22_RTC_WKUP_Hanlder,
    (uint32_t)&FLASH_Handler,
    (uint32_t)&RCC_Handler,
    (uint32_t)&EXTI0_Handler,
    (uint32_t)&EXTI1_Handler,
    (uint32_t)&EXTI2_Handler,
    (uint32_t)&EXTI3_Handler,
    (uint32_t)&EXTI4_Handler,
    (uint32_t)&DMA1_Stream0_Handler,
    (uint32_t)&DMA1_Stream1_Handler,
    (uint32_t)&DMA1_Stream2_Handler,
    (uint32_t)&DMA1_Stream3_Handler,
    (uint32_t)&DMA1_Stream4_Handler,
    (uint32_t)&DMA1_Stream5_Handler,
    (uint32_t)&DMA1_Stream6_Handler,
    (uint32_t)&ADC_Handler,
    (uint32_t)&EXTI9_5_Handler,
    (uint32_t)&TIM1_BRK_TIM9_Handler,
    (uint32_t)&TIM1_UP_TIM10_Handler,
    (uint32_t)&TIM1_TRG_COM_TIM11_Handler,
    (uint32_t)&TIM1_CC_Handler,
    (uint32_t)&TIM2_Handler,
    (uint32_t)&TIM3_Handler,
    (uint32_t)&TIM4_Handler,
    (uint32_t)&I2C1_EV_Handler,
    (uint32_t)&I2C1_ER_Handler,
    (uint32_t)&I2C2_EV_Handler,
    (uint32_t)&I2C2_ER_Handler,
    (uint32_t)&SPI1_Handler,
    (uint32_t)&SPI2_Handler,
    (uint32_t)&USART1_Handler,
    (uint32_t)&USART2_Handler,
    (uint32_t)&EXTI15_10_Handler,
    (uint32_t)&EXTI17_RTC_Alarm_Handler,
    (uint32_t)&EXTI18_OTG_FS_WKUP_Handler,
    (uint32_t)&DMA1_Stream7_Handler,
    (uint32_t)&SDIO_Handler,
    (uint32_t)&TIM5_Handler,
    (uint32_t)&SPI3_Handler,
    (uint32_t)&DMA2_Stream0_Handler,
    (uint32_t)&DMA2_Stream1_Handler,
    (uint32_t)&DMA2_Stream2_Handler,
    (uint32_t)&DMA2_Stream3_Handler,
    (uint32_t)&DMA2_Stream4_Handler,
    (uint32_t)&OTG_FS_Handler,
    (uint32_t)&DMA2_Stream5_Handler,
    (uint32_t)&DMA2_Stream6_Handler,
    (uint32_t)&DMA2_Stream7_Handler,
    (uint32_t)&USART6_Handler,
    (uint32_t)&I2C3_EV_Handler,
    (uint32_t)&I2C3_ER_Handler,
    (uint32_t)&FPU_Handler,
    (uint32_t)&SPI4_Handler,
    (uint32_t)&SPI5_Handler,
};
//_Handler endregion_Handler

void Reset_Handler(void) {}
void NMI_Handler_Handler(void) {}
