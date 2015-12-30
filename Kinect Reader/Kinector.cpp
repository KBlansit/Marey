#include "Kinector.h"
#include <iostream>

using namespace std;

// public

// constructor
Kinector::Kinector() {
    HRESULT HR = initKinect();
}

// destructor
Kinector::~Kinector() {
}

// methods
std::tuple<unsigned int, unsigned int> Kinector::updateCoords() {
    this->updateFrame();

    return _coords;
}

// private

// methods
HRESULT Kinector::initKinect() {
    HRESULT hr;

    hr = GetDefaultKinectSensor(&_sensor);
    if (! SUCCEEDED(hr))
        return hr;

    hr = _sensor->Open();
    if (! SUCCEEDED(hr))
        return hr;

    hr = _sensor->get_CoordinateMapper(&_mapper);
    if (! SUCCEEDED(hr))
        return hr;

    hr = _sensor->OpenMultiSourceFrameReader(
          FrameSourceTypes::FrameSourceTypes_Body
        | FrameSourceTypes::FrameSourceTypes_Color
        | FrameSourceTypes::FrameSourceTypes_Depth,
        &_multiReader);
    if (! SUCCEEDED(hr))
        return hr;

    return hr;
}

void Kinector::updateFrame() {
    HRESULT hr;
    hr = _multiReader->AcquireLatestFrame(&_multiSource);

    // may be limited by frame rate on Kinect sensor, and will fall through
    if (!SUCCEEDED(hr))
        return;

    getBodyCoord();

    if (_multiSource)
        _multiSource->Release();
}

void Kinector::getBodyCoord() {
    _multiSource->get_BodyFrameReference(&_bodyRef);
    _bodyRef->AcquireFrame(&_bodyFrame);
    _tracked = FALSE;

    // BODT_COUNT == 6 as defiend within kinect framework
    IBody* body[BODY_COUNT] = { 0 };
    _bodyFrame->GetAndRefreshBodyData(BODY_COUNT, body);
    for (int i = 0; i < BODY_COUNT; i++) {
        // converts _tracked to TRUE when tracked
        body[i]->get_IsTracked(&_tracked);
        if (_tracked) {
            body[i]->GetJoints(JointType_Count, joints);
            break;
        }
    }
    if (_tracked) {
        cout << "x: " << joints[JointType_Head].Position.X;
        cout << "  ";
        cout << "y: " << joints[JointType_Head].Position.Y;
        cout << "\r";
    }

    if (_bodyFrame)
        _bodyFrame->Release();
    if (_bodyRef)
        _bodyRef->Release();
}