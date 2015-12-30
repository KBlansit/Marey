#include "Kinector.h"
#include <iostream>

using namespace std;

// public

// constructor
Kinector::Kinector() {
    HRESULT HR = initKinect();
    cout << "seems to be okay";
}

// destructor
Kinector::~Kinector() {
}

// methods
// int Kinector::getCoordsX() {
// }

// int Kinector::getCoordsY() {
// }

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

    hr = _sensor->OpenMultiSourceFrameReader(
          FrameSourceTypes::FrameSourceTypes_Body
        | FrameSourceTypes::FrameSourceTypes_Color
        | FrameSourceTypes:: FrameSourceTypes_Depth,
        &_reader);
    if (! SUCCEEDED(hr))
        return hr;

    hr = _sensor->get_CoordinateMapper(&_mapper);
    if (! SUCCEEDED(hr))
        return hr;

    return hr;
}