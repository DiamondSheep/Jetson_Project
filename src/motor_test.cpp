#include <iostream>
#include "motor_test.hpp"

int epoll_fun(int gpio, int edge_set){
    if (_epoll_fd_thread == 0){
        _epoll_fd_thread = epoll_create(4);
        if (_epoll_fd_thread == -1)
            return 2;
    }
    try{
        // obtain the file discription for target gpio
        char path[128];
        sprintf(path, "%s/gpio%d/value", _SYSFS_ROOT, gpio);
        int value_fd = open(path, O_WRONLY);
        cout << "gpio " << gpio << " fd: " << value_fd << endl;

        //initialization for epoll_event
        struct epoll_event ev;
        ev.data.fd = value_fd;
        ev.events = EPOLLET; 
        cout << "epoll ctl: " << epoll_ctl(_epoll_fd_thread, EPOLL_CTL_ADD, value_fd, &ev) << endl;
        // timeout argument specifies the number of milliseconds
        int maxevents = 40;
        cout << "epoll wait: " << epoll_wait(_epoll_fd_thread, &ev, maxevents, 10) << endl;
        cout << endl;
    }
    catch(exception &e){
        cerr << "[Exception] " << e.what() << " (catched from: epoll_fun())" << endl;
        terminate();
    }

}

int main (){
    cout << "Motor testing " << endl;
    // initial the pins
    GPIO::setmode(GPIO::BOARD);
    GPIO::setup(21, GPIO::IN);
    GPIO::setup(22, GPIO::IN);
    GPIO::setup(23, GPIO::IN);
    GPIO::setup(24, GPIO::IN);


    epoll_fun(17, 1);
    epoll_fun(13, 1);
    epoll_fun(18, 1);
    epoll_fun(19, 1);
    
    // clean up the pins
    GPIO::cleanup(21);
    GPIO::cleanup(22);
    GPIO::cleanup(23);
    GPIO::cleanup(24);
    return 0;
}

