#include "FreeRTOS.h"
#include "task.h"
#include <stdint.h>


#include <hal_rtc_proto.h>

/* linker memory maps */
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;


#define RAM_START  0x20000000U
#define RAM_LENGTH 8192U
#define RAM_END    RAM_START + RAM_LENGTH
#define STACK      RAM_END - 4

#define SCB_AIRCR  (*((volatile uint32_t*)0xE000ED0C))
#define SCB_AIRCR_VECTKEY_Pos   16U
#define SCB_AIRCR_VECTKEY_Msk   (0xFFFFUL << SCB_AIRCR_VECTKEY_Pos)
#define SCB_AIRCR_PRIGROUP_Pos  8U
#define SCB_AIRCR_PRIGROUP_Msk  (7UL << SCB_AIRCR_PRIGROUP_Pos)
#define SCB_AIRCR_VECTKEY       (0x5FAUL << SCB_AIRCR_VECTKEY_Pos)

void SetPriorityGrouping(uint32_t prigroup) {
    uint32_t regValue = SCB_AIRCR;
    regValue &= ~(SCB_AIRCR_PRIGROUP_Msk | SCB_AIRCR_VECTKEY_Msk);
    regValue |= SCB_AIRCR_VECTKEY | (prigroup << SCB_AIRCR_PRIGROUP_Pos);
    SCB_AIRCR = regValue;
}


uint32_t SystemCoreClock = 72000000; // 72 MHz

//int main() {
//    while(1);
//};

void *memset(void *s, int c, int n) {
    unsigned char *p = s;
    while (n--) *p++ = (unsigned char)c;
    return s;
}

void vMyTaskFunction(void *pvParameters) {
    uint8_t hours, minutes, seconds;
    for(;;) {
        // Task code goes here
        rtc_get_time(&hours, &minutes, &seconds);
    }
}

void vMyTaskFunction2(void *pvParameters) {
    uint8_t hours, minutes, seconds;
    for(;;) {
        // Task code goes here
        rtc_get_time(&hours, &minutes, &seconds);
    }
}


int main(void) {
    // 1. Initialize hardware here
    // Initialize the RTC
    rtc_init();

    // Set NVIC priority grouping: 4 bits for preemption priority, 0 bits for subpriority (PRIGROUP = 0)
    SetPriorityGrouping(0);

    // Enable global interrupts
    //__asm volatile ("cpsie i");

    // 2. Create the task
    BaseType_t xReturned = xTaskCreate(
        vMyTaskFunction,    // Function name
        "ExampleTask",      // Debug name
        128,                // Stack size in words
        NULL,               // Task parameters
        1,                  // Priority
        NULL                // Task handle
    );

    xReturned = xTaskCreate(
        vMyTaskFunction2,    // Function name
        "ExampleTask",      // Debug name
        128,                // Stack size in words
        NULL,               // Task parameters
        1,                  // Priority
        NULL                // Task handle
    );

    if (xReturned == pdPASS) {
        // 3. Start the scheduler
        vTaskStartScheduler();
    }

    // Should never reach here
    for (;;);
}



/* ARM Cortex-M4 Vector Table Handlers */
int reset_hdlr() {

    uint32_t size, *dptr, *sptr;
    /* copy .data to SRAM */
    dptr = &_sdata;
    sptr = &_etext;
    size = &_edata - &_sdata;
    for(uint32_t i = 0; i < size; i++) {
        *dptr = *sptr;
        dptr++;
        sptr++;
    }

    /* Initialize bss with 0 */
    dptr = (uint32_t *)_sbss;
    size = &_ebss - &_sbss;
    for(uint32_t i = 0; i < size; i++) {
        *dptr = 0;
        dptr++;
    }


    main();
    while(1) {}
}

void nmi_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void hard_fault_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void mem_fault_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void bus_fault_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void usage_fault_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void SVC_Handler(void) __attribute__ ((weak, alias("default_handler")));
void debug_monitor_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void PendSV_Handler(void) __attribute__ ((weak, alias("default_handler")));
void SysTick_Handler(void) __attribute__ ((weak, alias("default_handler")));

/* External IRQ Handlers */
void wwdg_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void pvd_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void tamper_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void rtc_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void flash_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void rcc_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void exti0_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void exti1_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void exti2_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void exti3_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void exti4_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void dma1_ch1_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void dma1_ch2_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void dma1_ch3_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void dma1_ch4_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void dma1_ch5_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void dma1_ch6_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void dma1_ch7_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void adc1_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void exti9_5_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void tim1_brk_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void tim1_up_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void tim1_trg_com_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void tim1_cc_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void tim2_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void tim3_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void i2c1_ev_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void i2c1_er_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void spi1_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void usart1_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void exti15_10_hdlr(void) __attribute__ ((weak, alias("default_handler")));
void rtc_alarm_hdlr(void) __attribute__ ((weak, alias("default_handler")));

/* Default Handler */
void default_handler(void) {
    while(1);
}

/* ARM Cortex-M3 Vector Table (STM32F100 Discovery Board) */
volatile unsigned int __attribute__((section(".vector_table"))) vector_table [83] = {
    /* Cortex-M3 Exceptions (0-15) */
    [0] = STACK,                                    /* Stack pointer */
    [1] = (unsigned int)&reset_hdlr,               /* Reset handler */
    [2] = (unsigned int)&nmi_hdlr,                 /* NMI handler */
    [3] = (unsigned int)&hard_fault_hdlr,          /* Hard fault handler */
    [4] = (unsigned int)&mem_fault_hdlr,           /* Memory management fault */
    [5] = (unsigned int)&bus_fault_hdlr,           /* Bus fault */
    [6] = (unsigned int)&usage_fault_hdlr,         /* Usage fault */
    [7] = 0,                                        /* Reserved */
    [8] = 0,                                        /* Reserved */
    [9] = 0,                                        /* Reserved */
    [10] = 0,                                       /* Reserved */
    [11] = (unsigned int)&SVC_Handler,                /* SVCall */
    [12] = (unsigned int)&debug_monitor_hdlr,      /* Debug monitor */
    [13] = 0,                                       /* Reserved */
    [14] = (unsigned int)&PendSV_Handler,            /* PendSV */
    [15] = (unsigned int)&SysTick_Handler,           /* SysTick */

    /* STM32F100 External Interrupts (16-82) */
    [16] = (unsigned int)&wwdg_hdlr,               /* WWDG */
    [17] = (unsigned int)&pvd_hdlr,                /* PVD */
    [18] = (unsigned int)&tamper_hdlr,             /* Tamper */
    [19] = (unsigned int)&rtc_hdlr,                /* RTC */
    [20] = (unsigned int)&flash_hdlr,              /* Flash */
    [21] = (unsigned int)&rcc_hdlr,                /* RCC */
    [22] = (unsigned int)&exti0_hdlr,              /* EXTI0 */
    [23] = (unsigned int)&exti1_hdlr,              /* EXTI1 */
    [24] = (unsigned int)&exti2_hdlr,              /* EXTI2 */
    [25] = (unsigned int)&exti3_hdlr,              /* EXTI3 */
    [26] = (unsigned int)&exti4_hdlr,              /* EXTI4 */
    [27] = (unsigned int)&dma1_ch1_hdlr,           /* DMA1 Channel 1 */
    [28] = (unsigned int)&dma1_ch2_hdlr,           /* DMA1 Channel 2 */
    [29] = (unsigned int)&dma1_ch3_hdlr,           /* DMA1 Channel 3 */
    [30] = (unsigned int)&dma1_ch4_hdlr,           /* DMA1 Channel 4 */
    [31] = (unsigned int)&dma1_ch5_hdlr,           /* DMA1 Channel 5 */
    [32] = (unsigned int)&dma1_ch6_hdlr,           /* DMA1 Channel 6 */
    [33] = (unsigned int)&dma1_ch7_hdlr,           /* DMA1 Channel 7 */
    [34] = (unsigned int)&adc1_hdlr,               /* ADC1 */
    [35] = (unsigned int)&exti9_5_hdlr,            /* EXTI9_5 */
    [36] = (unsigned int)&tim1_brk_hdlr,           /* TIM1 Break */
    [37] = (unsigned int)&tim1_up_hdlr,            /* TIM1 Update */
    [38] = (unsigned int)&tim1_trg_com_hdlr,       /* TIM1 Trigger and Commutation */
    [39] = (unsigned int)&tim1_cc_hdlr,            /* TIM1 Capture Compare */
    [40] = (unsigned int)&tim2_hdlr,               /* TIM2 */
    [41] = (unsigned int)&tim3_hdlr,               /* TIM3 */
    [42] = (unsigned int)&i2c1_ev_hdlr,            /* I2C1 Event */
    [43] = (unsigned int)&i2c1_er_hdlr,            /* I2C1 Error */
    [44] = (unsigned int)&spi1_hdlr,               /* SPI1 */
    [45] = (unsigned int)&usart1_hdlr,             /* USART1 */
    [46] = (unsigned int)&exti15_10_hdlr,          /* EXTI15_10 */
    [47] = (unsigned int)&rtc_alarm_hdlr,          /* RTC Alarm */
};