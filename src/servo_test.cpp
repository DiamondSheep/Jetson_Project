#include "servo_driver.hpp"
#include <time.h>

int main (){
    servo_driver servo(1);
    servo.angle(0, 45);
    sleep(1);
    servo.angle(0, 135);
    sleep(1);
    servo.angle(1, 20);
    return 0;
}
