#pragma once
#include <Windows.h>
#include <Kinect.h>

class Kinector {
public:
    // constructor
    Kinector();

    // destructor
    ~Kinector();

    int getCoordsX();
    int getCoordsY();

private:
    // methods
    HRESULT initKinect();

    // attributes
    IKinectSensor* _sensor;

    unsigned int _x;
    unsigned int _y;
};
