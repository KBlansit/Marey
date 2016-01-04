#pragma once
#include <tuple>
#include <Windows.h>
#include <Kinect.h>

class Kinector {
public:
    // constructor
    Kinector();

    // destructor
    ~Kinector();

    // methods
    std::tuple<unsigned int, unsigned int> updateCoords();

private:
    // methods
    HRESULT initKinect();
    void updateFrame();

    // attributes
    // sensor and mapper
    IKinectSensor* _sensor;
    ICoordinateMapper* _mapper;

    // frame readers
    IMultiSourceFrameReader* _multiReader;

    // frames source
    IMultiSourceFrame* _multiSource;


    std::tuple<unsigned int, unsigned int> _coords;
};
