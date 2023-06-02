#ifndef GPIO_H
#define GPIO_h

#define F_CPU 16000000UL

#define FREQ_PIN PC0    //пин изменения частоты (пин A0)
#define DUTY_PIN PC1    //пин изменения скважности (пин A1)
#define SWITCH_PIN PD6  //пин изменения скважности (пин D6)

void GPIO_init(void);

#endif