#pragma once
#include <SDL\SDL.h>
#include "GL\glew.h"
#include "Skeleton.h"
#include "Kinector.h"

enum class DisplayState { RUNNING, OFF };

class Display {
public:
    // constructors
    Display();

    // destructor
    ~Display();

    // methods
    void runDisplay();

private:
    // methods
    void setBody();
    void processInput();
    void drawDisplay();

    // attributes
    SDL_Window* _window = nullptr;
    SDL_Renderer* _rndr = nullptr;
    SDL_Texture* _txtr = nullptr;

    Kinector _k;

    DisplayState _currState;

    // const attributes
    const unsigned int _scnWidth = 1024;
    const unsigned int _scnHeight = 768;

    // structre of body coords for plotting
    // _body => _bodyPart => XYZ
    // three member structure of X Y Z coordinates for kinect joints
    _skeleton* _bodyCoords = nullptr;
};
