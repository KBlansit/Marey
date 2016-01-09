#include <iostream>
#include <stdio.h>
#include "Display.h"
#include "Kinector.h"

int main(int argc, char* argv[]) {
    Kinector K;

    while (TRUE) {
        K.updateKinect();
        if (K.isTracked()) {
            _skeleton tempSkeleton = K.getData();
            std::cout << "tracking...";
            std::cout << "\r";
        }
    }


    
    /*
    Display display;
    display.runDisplay();
    */


    return 0;
}