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
_skeleton Kinector::getData() {
    updateFrame();
    updateBody();
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

    if (_multiSource)
        _multiSource->Release();
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
        _body->_head = joints[JointType_Head].Position;
        _body->_cervicalSpine = joints[JointType_Neck].Position;
        _body->_sacrumSpine = joints[JointType_SpineBase].Position;

        // update right limbs
        _body->_handRight = joints[JointType_HandRight].Position;
        _body->_elbowRight = joints[JointType_ElbowRight].Position;
        _body->_shoulderRight = joints[JointType_ShoulderRight].Position;
        _body->_hipRight = joints[JointType_HipRight].Position;
        _body->_kneeRight = joints[JointType_KneeRight].Position;
        _body->_footRight = joints[JointType_FootRight].Position;

        // update left limbs
        _body->_handLeft = joints[JointType_HandLeft].Position;
        _body->_elbowLeft = joints[JointType_ElbowLeft].Position;
        _body->_shoulderLeft = joints[JointType_ShoulderLeft].Position;
        _body->_hipLeft = joints[JointType_HipLeft].Position;
        _body->_kneeLeft = joints[JointType_KneeLeft].Position;
        _body->_footLeft = joints[JointType_FootLeft].Position;
    }

    if (_bodyFrame)
        _bodyFrame->Release();

    if (_bodyRef)
        _bodyRef->Release();
}
