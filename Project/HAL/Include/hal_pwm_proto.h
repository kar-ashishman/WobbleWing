#ifndef __HAL_PWM_PROTO_H__
#define __HAL_PWM_PROTO_H__

    #include <stdint.h>

    void pwm_init(void);
    void pwm_set_duty_cycle(uint8_t duty_cycle);
    void pwm_set_frequency(uint32_t frequency);

#endif // __HAL_PWM_PROTO_H__