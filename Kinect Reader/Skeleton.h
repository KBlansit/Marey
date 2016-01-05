#pragma once
#include <Kinect.h>

struct _skeleton {
    // spine
    CameraSpacePoint _head;
    CameraSpacePoint _cervicalSpine;
    CameraSpacePoint _sacrumSpine;

    // right limbs
    CameraSpacePoint _handRight;
    CameraSpacePoint _elbowRight;
    CameraSpacePoint _shoulderRight;
    CameraSpacePoint _hipRight;
    CameraSpacePoint _kneeRight;
    CameraSpacePoint _footRight;

    // left limbs
    CameraSpacePoint _handLeft;
    CameraSpacePoint _elbowLeft;
    CameraSpacePoint _shoulderLeft;
    CameraSpacePoint _hipLeft;
    CameraSpacePoint _kneeLeft;
    CameraSpacePoint _footLeft;
};

