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
    void getBodyCoord();

    // attributes
    BOOLEAN _tracked;
    std::tuple<unsigned int, unsigned int> _coords;

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
};
