#include <iostream>
#include <stdio.h>
#include "Display.h"
#include "Kinector.h"

int main(int argc, char* argv[]) {
    Kinector K;

    while (TRUE) {
        if (K.isTracked()) {
            _skeleton tempSkeleton = K.getData();
            std::cout << "Tracking:";
            std::cout << tempSkeleton._head.X;
            std::cout << "\r";
        }
    }


    /*
    
    Display display;
    display.runDisplay();

    */

    return 0;
}