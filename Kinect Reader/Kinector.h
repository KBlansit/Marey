#pragma once
#include <Windows.h>
#include <Kinect.h>
#include <chrono>

#include "Skeleton.h"

typedef std::chrono::high_resolution_clock Clock;

class Kinector {
public:
    // constructor
    Kinector();

    // destructor
    ~Kinector();

    // methods
    void updateKinect();
    void startTimer();
    bool isTracked();
    _skeleton getData();

private:
    // methods
    HRESULT initKinect();
    void updateFrame();
    void updateBody();

    // attributes
    BOOLEAN _tracked;

    // kinect specific attributes
    // sensor and mapper
    IKinectSensor* _sensor = nullptr;
    ICoordinateMapper* _mapper = nullptr;

    // frame readers
    IMultiSourceFrameReader* _multiReader = nullptr;

    // frames source
    IMultiSourceFrame* _multiSource = nullptr;

    // frames
    IBodyFrame* _bodyFrame = nullptr;

    // kinect references
    IBodyFrameReference* _bodyRef = nullptr;

    // joints
    Joint joints[JointType_Count];

    // body data
    _skeleton* _body = nullptr;

    // timer
    Clock::time_point* _initTime = nullptr;
};
