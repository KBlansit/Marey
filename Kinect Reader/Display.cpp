#include <string>
#include <iostream>
#include <chrono>
#include "Display.h"

using namespace std;
using namespace std::chrono;
typedef steady_clock Clock;

// unparameterized constructor
Display::Display() {
}

// desctuctor
Display::~Display() {

}

// public methods

void Display::setBody(_skeleton body) {

}

// run method
void Display::runDisplay() {
    initSystem();
    displayLoop();
}

// private methods

// initializer private method
int Display::initSystem() {
    //TODO: add proper error checking

    _x = INIT_X;
    _y = INIT_Y;
    _w = INIT_W;
    _h = INIT_H;

    _currState = DisplayState::RUNNING;

    // initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    // create renderer
    _window = SDL_CreateWindow (
        "Display",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        _scnWidth,
        _scnHeight,
        SDL_WINDOW_OPENGL);
    if (_window == nullptr)
        return 1;

    // create renderer
    _rndr = SDL_CreateRenderer (
        _window,
        -1,
        SDL_RENDERER_ACCELERATED);
    if (_rndr == nullptr)
        return 2;

    // create texture
    _txtr = SDL_CreateTexture(
        _rndr,
        SDL_PIXELFORMAT_ABGR8888,
        SDL_TEXTUREACCESS_STREAMING,
        _scnWidth,
        _scnHeight);
    if (_txtr == nullptr)
        return 3;
    
    // set background colour and set renderer
    SDL_SetRenderDrawColor(_rndr, 50, 100, 255, 0);
    SDL_RenderClear(_rndr);

    SDL_SetRenderDrawColor(_rndr, 0, 100, 0, 0);
    _r.x = _x;
    _r.y = _y;
    _r.w= _w;
    _r.h = _h;

    SDL_RenderFillRect(_rndr, &_r);

    // return 
    SDL_RenderPresent(_rndr);

    return 0;
}
void Display::displayLoop() {
    while (_currState != DisplayState::OFF) {        
        processInput();

        // set square
        _r.x = _x;
        _r.y = _y;

        // reset background colour and set renderer
        SDL_SetRenderDrawColor(_rndr, 0, 0, 0, 0);
        SDL_RenderClear(_rndr);

        // draw square
        SDL_SetRenderDrawColor(_rndr, 0, 100, 0, 0);
        SDL_RenderFillRect(_rndr, &_r);
        SDL_RenderPresent(_rndr);

        SDL_RenderDrawLine(_rndr, INIT_X, INIT_Y, _x, _y);
        SDL_RenderPresent(_rndr);

        cout << "x: " << _x;
        cout << "  ";
        cout << "y: " << _y;
        cout << "\r";

    }
}

void Display::processInput() {
    SDL_Event evnt;

    while (SDL_PollEvent(&evnt)) {
        // keeps running until quit
        switch (evnt.type) {
        case SDL_QUIT:
            _currState = DisplayState::OFF;
            break;
        case SDL_MOUSEMOTION:
            _x = evnt.motion.x;
            _y = evnt.motion.y;
            validMove();
        }
    }
}

void Display::drawDisplay() {

}

void Display::validMove() {
    if (_x >= _scnWidth || _x <= 0)
        _x = INIT_X;
    if (_y >= _scnHeight || _y <= 0)
        _y = INIT_Y;
}