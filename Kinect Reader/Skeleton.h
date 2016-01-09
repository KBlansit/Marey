#pragma once
#include <Kinect.h>

// structre of body coords for plotting
// _body => _bodyPart => XYZ
// three member structure of X Y Z coordinates for kinect joints

// spine
struct head { float X; float Y; };
struct cervicalSpine{ float X; float Y; };
struct sacrumSpine { float X; float Y; };

// right limbs
struct handRight { float X; float Y; };
struct elbowRight { float X; float Y; };
struct shoulderRight { float X; float Y; };
struct hipRight { float X; float Y; };
struct kneeRight { float X; float Y; };
struct footRight { float X; float Y; };

// left limbs
struct handLeft { float X; float Y; };
struct elbowLeft { float X; float Y; };
struct shoulderLeft { float X; float Y; };
struct hipLeft { float X; float Y; };
struct kneeLeft { float X; float Y; };
struct footLeft { float X; float Y; };

struct _skeleton {
    // spine
    head _head;
    cervicalSpine _cervicalSpine;
    sacrumSpine _sacrumSpine;

    // right limbs
    handRight _handRight;
    elbowRight _elbowRight;
    shoulderRight _shoulderRight;
    hipRight _hipRight;
    kneeRight _kneeRight;
    footRight _footRight;
    
     // left limbs
    handLeft _handLeft;
    elbowLeft _elbowLeft;
    shoulderLeft _shoulderLeft;
    hipLeft _hipLeft;
    kneeLeft _kneeLeft;
    footLeft _footLeft;
};
