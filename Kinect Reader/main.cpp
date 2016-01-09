#include <iostream>
#include <stdio.h>
#include "Display.h"
#include "Kinector.h"

using namespace std;

int main(int argc, char* argv[]) {
    Kinector K;

    while (TRUE) {
        K.updateKinect();
        if (K.isTracked()) {

            _skeleton tempSkeleton = K.getData();

            cout << "x: ";
            cout << tempSkeleton._head.X;
            cout << "  ";
            cout << "y: ";
            cout << tempSkeleton._head.Y;
            cout << "\r";
        }
    }
    
    /*
    Display display;
    display.runDisplay();
    */


    return 0;
}