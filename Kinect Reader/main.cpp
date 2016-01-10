#include <iostream>
#include <stdio.h>
#include "Display.h"
#include "Kinector.h"

using namespace std;

int main(int argc, char* argv[]) {
    Kinector K;
    _skeleton* tempSkeleton = nullptr;
    tempSkeleton = new _skeleton;
    K.startTimer();

    while (TRUE) {
        K.updateKinect();
        if (K.isTracked()) {

            tempSkeleton = &K.getData();
            long timeDiff = K.getTimeDiff();

            cout << "x: ";
            cout << tempSkeleton->_head.X;
            cout << "  ";
            cout << "y: ";
            cout << tempSkeleton->_head.Y;
            cout << "  ";
            cout << "time : ";
            cout << timeDiff;
            cout << "\r";
        }
    }
    
    /*
    Display display;
    display.runDisplay();
    */
}