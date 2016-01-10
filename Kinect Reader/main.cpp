#include <iostream>
#include <stdio.h>
#include "Display.h"
#include "Kinector.h"

using namespace std;

// for test coding only
#include <chrono>
#include <thread>

int main(int argc, char* argv[]) {
    /*
    Kinector K;
    _skeleton* tempSkeleton = nullptr;
    tempSkeleton = new _skeleton;

    while (TRUE) {
        K.updateKinect();
        if (K.isTracked()) {

            tempSkeleton = &K.getData();

            cout << "x: ";
            cout << tempSkeleton->_head.X;
            cout << "  ";
            cout << "y: ";
            cout << tempSkeleton->_head.Y;
            cout << "\r";
        }
    }
    
    Display display;
    display.runDisplay();
    */
    typedef std::chrono::high_resolution_clock Clock;
    Clock::time_point* _initTime = nullptr;
    _initTime = new Clock::time_point;
    *_initTime = Clock::now();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    auto nowTime = Clock::now();

    auto diffTime = std::chrono::duration_cast<std::chrono::milliseconds>(nowTime - *_initTime);
    std::cout << diffTime.count();

    return 0;
}