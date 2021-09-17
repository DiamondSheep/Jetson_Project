#ifndef _MOTOR_TEST_H
#define _MOTOR_TEST_H

#include "definitions.h"
#include "driver.hpp"

#include <time.h>
#include <unistd.h>
#include <fstream>
#include <string>

#include <sys/epoll.h> // for edge-triggered (ET) and level-triggered (LT) 
#include <JetsonGPIO.h>

using namespace std;

char _SYSFS_ROOT[32] = "/sys/class/gpio";
int _epoll_fd_thread = 0;


#endif