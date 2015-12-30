#include <iostream>
#include "Display.h"
#include "Kinector.h"

int main(int argc, char* argv[]) {
    Kinector K;
    while (TRUE) {
        K.updateCoords();
    }

    // Display display;
    // display.runDisplay();

    return 0;
}