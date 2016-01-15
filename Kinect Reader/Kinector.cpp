#include "Kinector.h"

#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// public

// constructor
Kinector::Kinector() {
    _body = new _skeleton;

    HRESULT HR = initKinect();
}

// destructor
Kinector::~Kinector() {
}

// methods
void Kinector::updateKinect() {
    updateFrame();
}

void Kinector::startTimer() {
    _initTime = new Clock::time_point;

    *_initTime = Clock::now();
}

bool Kinector::isTracked() {
    return _tracked;
}

_skeleton Kinector::getData() {
    updateFrame();

    return *_body;
}

long Kinector::getTimeDiff() {
    if (_initTime == nullptr || _currTime == nullptr) {
        return NULL;
    }

    milliseconds diffTime = duration_cast<milliseconds>(*_currTime - *_initTime);

    return diffTime.count();
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
    if (!SUCCEEDED(hr)) {
        return;
    }

    if (_initTime != nullptr) {
        if (_currTime == nullptr) {
            _currTime = new Clock::time_point;
        }
        *_currTime = Clock::now();
    }

    updateBody();

    if (_multiSource) {
        _multiSource->Release();
    }
}

void Kinector::updateBody() {
    _multiSource->get_BodyFrameReference(&_bodyRef);
    _bodyRef->AcquireFrame(&_bodyFrame);
    _tracked = FALSE;

    // BODT_COUNT == 6 as defiend within kinect framework
    IBody* ppBody[BODY_COUNT] = { 0 };
    _bodyFrame->GetAndRefreshBodyData(BODY_COUNT, ppBody);

    // find body within array of bodies
    for (int i = 0; i < BODY_COUNT; i++) {
        // converts _tracked to TRUE when tracked
        ppBody[i]->get_IsTracked(&_tracked);
        if (_tracked) {
            ppBody[i]->GetJoints(JointType_Count, joints);
            break;
        }
    }

    // if tracked, update _body
    if (_tracked) {
        // update spine
        _body->_head.X = joints[JointType_Head].Position.X;
        _body->_head.Y = joints[JointType_Head].Position.Y;

        _body->_cervicalSpine.X = joints[JointType_Neck].Position.X;
        _body->_cervicalSpine.Y = joints[JointType_Neck].Position.Y;

        _body->_sacrumSpine.X = joints[JointType_SpineBase].Position.X;
        _body->_sacrumSpine.Y = joints[JointType_SpineBase].Position.Y;

        // update right limb
        _body->_handRight.X = joints[JointType_HandRight].Position.X;
        _body->_handRight.Y = joints[JointType_HandRight].Position.Y;

        _body->_elbowRight.X = joints[JointType_ElbowRight].Position.X;
        _body->_elbowRight.Y = joints[JointType_ElbowRight].Position.Y;

        _body->_shoulderRight.X = joints[JointType_ShoulderRight].Position.X;
        _body->_shoulderRight.Y = joints[JointType_ShoulderRight].Position.Y;

        _body->_hipRight.X = joints[JointType_HipRight].Position.X;
        _body->_hipRight.Y = joints[JointType_HipRight].Position.Y;

        _body->_kneeRight.X = joints[JointType_KneeRight].Position.X;
        _body->_kneeRight.Y = joints[JointType_KneeRight].Position.Y;

        _body->_footRight.X = joints[JointType_FootRight].Position.X;
        _body->_footRight.Y = joints[JointType_FootRight].Position.Y;

        // update left limb
        _body->_handLeft.X = joints[JointType_HandLeft].Position.X;
        _body->_handLeft.Y = joints[JointType_HandLeft].Position.Y;

        _body->_elbowLeft.X = joints[JointType_ElbowLeft].Position.X;
        _body->_elbowLeft.Y = joints[JointType_ElbowLeft].Position.Y;

        _body->_shoulderLeft.X = joints[JointType_ShoulderLeft].Position.X;
        _body->_shoulderLeft.Y = joints[JointType_ShoulderLeft].Position.Y;

        _body->_hipLeft.X = joints[JointType_HipLeft].Position.X;
        _body->_hipLeft.Y = joints[JointType_HipLeft].Position.Y;

        _body->_kneeLeft.X = joints[JointType_KneeLeft].Position.X;
        _body->_kneeLeft.Y = joints[JointType_KneeLeft].Position.Y;

        _body->_footLeft.X = joints[JointType_FootLeft].Position.X;
        _body->_footLeft.Y = joints[JointType_FootLeft].Position.Y;
    }

    if (_bodyFrame) {
        _bodyFrame->Release();
    }

    if (_bodyRef) {
        _bodyRef->Release();
    }
}
