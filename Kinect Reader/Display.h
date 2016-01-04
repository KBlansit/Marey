#pragma once

#include <SDL\SDL.h>

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
    struct _bodyCoords{
        // along the spine
        struct _headCoords { unsigned int X; unsigned int Y; unsigned int Z; };
        struct _cervicalSpineCoords { unsigned int X; unsigned int Y; unsigned int Z; };
        struct _sacrumSpineCoords { unsigned int X; unsigned int Y; unsigned int Z; };

        // right limbs
        struct _handRightCoords { unsigned int X; unsigned int Y; unsigned int Z; };
        struct _elbowRightCoords { unsigned int X; unsigned int Y; unsigned int Z; };
        struct _shoulderRightCoords { unsigned int X; unsigned int Y; unsigned int Z; };
        struct _hipRightCoords { unsigned int X; unsigned int Y; unsigned int Z; };
        struct _kneeRightCoords { unsigned int X; unsigned int Y; unsigned int Z; };
        struct _footRightCoords { unsigned int X; unsigned int Y; unsigned int Z; };

        // left limbs
        struct _handLeftCoords { unsigned int X; unsigned int Y; unsigned int Z; };
        struct _elbowLeftCoords { unsigned int X; unsigned int Y; unsigned int Z; };
        struct _shoulderLeftCoords { unsigned int X; unsigned int Y; unsigned int Z; };
        struct _hipLeftCoords { unsigned int X; unsigned int Y; unsigned int Z; };
        struct _kneeLeftCoords { unsigned int X; unsigned int Y; unsigned int Z; };
        struct _footLeftCoords { unsigned int X; unsigned int Y; unsigned int Z; };
    };
};
