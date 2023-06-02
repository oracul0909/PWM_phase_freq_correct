#ifndef PWM_H
#define PWM_h

void PWM_init(void);
void PWM_set(uint16_t frequency, uint16_t duty_cycle);
void PWM_freq_switch(void);

#endif