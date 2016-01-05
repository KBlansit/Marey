#pragma once
#include <SDL\SDL.h>
#include "Skeleton.h"

enum class DisplayState { RUNNING, OFF };

class Display {
public:
    // constructors
    Display();

    // destructor
    ~Display();

    // methods
    void setBody(_skeleton body);
    void runDisplay();

private:
    // methods
    int initSystem();
    void displayLoop();
    void processInput();
    void drawDisplay();

    void validMove();

    // attributes
    SDL_Window* _window = nullptr;
    SDL_Renderer* _rndr = nullptr;
    SDL_Texture* _txtr = nullptr;

    SDL_Rect _r;

    unsigned int _x;
    unsigned int _y;
    unsigned int _h;
    unsigned int _w;

    DisplayState _currState;
        
    // const attributes
    const unsigned int _scnWidth = 1024;
    const unsigned int _scnHeight = 768;

    const unsigned int INIT_X = 50;
    const unsigned int INIT_Y = 50;
    const unsigned int INIT_H = 50;
    const unsigned int INIT_W = 50;

    // structre of body coords for plotting
    // _body => _bodyPart => XYZ
    // three member structure of X Y Z coordinates for kinect joints
    _skeleton* _bodyCoords = nullptr;
};
