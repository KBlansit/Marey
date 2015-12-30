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

    if (_multiSource) {
        _multiSource->Release();
        cout << "released frameSource\n";
    }
}