#include <hal.h>

void rtc_init(void) {
    // Initialize the RTC hardware
    // This is a placeholder implementation and should be replaced with actual RTC initialization code

    // Clock configuration for RTC - LSE 32.768 kHz
    RCC->BDCR |= RCC_BDCR_LSEON;         // Enable LSE
    //while(!(RCC->BDCR & RCC_BDCR_LSERDY)); // Wait until ready
    RCC->BDCR |= RCC_BDCR_RTCSEL_0;      // Select LSE as RTC clock
    RCC->BDCR |= RCC_BDCR_RTCEN;         // Enable RTC

    // Disable write protection for RTC registers
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    // Configure RTC prescaler for 1 Hz output
    RTC->PRER = (127 << 16) | 255;

    // Set time and date
    RTC->TR = (0x12 << 16) | (0x34 << 8) | 0x56; // 12:34:56
    RTC->DR = (0x24 << 16) | (0x04 << 8) | 0x04; // 2024-Apr-06

    // Enable write protection for RTC registers
    RTC->WPR = 0xFF;
}


void rtc_get_time(uint8_t *hours, uint8_t *minutes, uint8_t *seconds) {
    // Read the current time from the RTC hardware
    // This is a placeholder implementation and should be replaced with actual RTC reading code

    // Disable write protection for RTC registers
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    uint32_t tr = RTC->TR; // Read time register

    // Extract hours, minutes, and seconds
    *hours = (tr >> 16) & 0xFF;
    *minutes = (tr >> 8) & 0xFF;
    *seconds = tr & 0xFF;

    // Enable write protection for RTC registers
    RTC->WPR = 0xFF;
}