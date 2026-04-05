#ifndef __HAL_RTC_PROTO_H__
#define __HAL_RTC_PROTO_H__

    #include <stdint.h>

    void rtc_init(void);
    void rtc_get_time(uint8_t *hours, uint8_t *minutes, uint8_t *seconds);

#endif // __HAL_RTC_PROTO_H__