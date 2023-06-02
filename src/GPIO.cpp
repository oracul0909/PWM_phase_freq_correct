#include <Arduino.h>
#include "GPIO.h"



void GPIO_init()
{
    PORTC |= ((1<<FREQ_PIN)) | ((1<<DUTY_PIN));
    PORTD |= ((1<<SWITCH_PIN));
}
