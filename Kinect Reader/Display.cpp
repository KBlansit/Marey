#include <string>
#include <iostream>
#include <chrono>
#include "Display.h"

using namespace std;
using namespace std::chrono;
typedef steady_clock Clock;

// unparameterized constructor
Display::Display() {
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
    if (_window == nullptr) {
        cout << "Problem creating SDL window";
        return;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(_window);
    if (glContext == nullptr) {
        cout << "Problem creating GL context";
        return;
    }

    GLenum status = glewInit();
    if (status != GLEW_OK) {
        cout << "Problem initializing GLEW";
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // create renderer
    _rndr = SDL_CreateRenderer (
        _window,
        -1,
        SDL_RENDERER_ACCELERATED);
    if (_rndr == nullptr) {
        return;
    }

    if (_vboID == 0) {
        glGenBuffers(1, &_vboID);
    }
}

// desctuctor
Display::~Display() {
    SDL_GL_DeleteContext(_window);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

// public methods

void Display::setBody(_skeleton body) {
}

// run method
void Display::runDisplay() {
    drawDisplay();
}

// private methods

// process input
void Display::processInput() {
    SDL_Event evnt;

    while (SDL_PollEvent(&evnt)) {
        // keeps running until quit
        switch (evnt.type) {
        case SDL_QUIT:
            _currState = DisplayState::OFF;
            break;
        }
    }
}

// draw display
void Display::drawDisplay() {
    while (_currState != DisplayState::OFF) {        
        glClearColor(0.0f, 0.15f, 0.3f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBegin(GL_LINES);

        glVertex2f(0.0, 0.0);
        glVertex2f(0.1, 0.1);

        glEnd();

        // swap window
        SDL_GL_SwapWindow(_window);

        processInput();
    }
}
