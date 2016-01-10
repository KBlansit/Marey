#include "Display.h"

#include <string>
#include <iostream>
#include <chrono>

using namespace std;

// unparameterized constructor
Display::Display() {
    _bodyCoords = new _skeleton;

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
}

// desctuctor
Display::~Display() {
    SDL_GL_DeleteContext(_window);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

// public methods

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
        case SDL_KEYDOWN:
            if (SDLK_RETURN) {
                cout << "return";
                cout << "\r";
            }
        }
    }
}

// return body data to display
void Display::setBody() {
    _bodyCoords = &_k.getData();
}

void Display::drawBody() {

}

// draw display
void Display::drawDisplay() {
    while (_currState != DisplayState::OFF) {        
        setBody();

        glClearColor(0.0f, 0.15f, 0.3f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        if (_k.isTracked()) {
            // head to cervical spine line
            glBegin(GL_LINES);
            glVertex2f(_bodyCoords->_head.X, _bodyCoords->_head.Y);
            glVertex2f(_bodyCoords->_cervicalSpine.X, _bodyCoords->_cervicalSpine.Y);
            glEnd();

            // cervical spine to sacrum spine
            glBegin(GL_LINES);
            glVertex2f(_bodyCoords->_cervicalSpine.X, _bodyCoords->_cervicalSpine.Y);
            glVertex2f(_bodyCoords->_sacrumSpine.X, _bodyCoords->_sacrumSpine.Y);
            glEnd();

            // right
            // neck to shoulder
            glBegin(GL_LINES);
            glVertex2f(_bodyCoords->_cervicalSpine.X, _bodyCoords->_cervicalSpine.Y);
            glVertex2f(_bodyCoords->_shoulderRight.X, _bodyCoords->_shoulderRight.Y);
            glEnd();

            // shoulder to elbow
            glBegin(GL_LINES);
            glVertex2f(_bodyCoords->_shoulderRight.X, _bodyCoords->_shoulderRight.Y);
            glVertex2f(_bodyCoords->_elbowRight.X, _bodyCoords->_elbowRight.Y);
            glEnd();

            // shoulder to elbow
            glBegin(GL_LINES);
            glVertex2f(_bodyCoords->_elbowRight.X, _bodyCoords->_elbowRight.Y);
            glVertex2f(_bodyCoords->_handRight.X, _bodyCoords->_handRight.Y);
            glEnd();

            // spine to hip
            glBegin(GL_LINES);
            glVertex2f(_bodyCoords->_sacrumSpine.X, _bodyCoords->_sacrumSpine.Y);
            glVertex2f(_bodyCoords->_hipRight.X, _bodyCoords->_hipRight.Y);
            glEnd();

            // hip to knee
            glBegin(GL_LINES);
            glVertex2f(_bodyCoords->_hipRight.X, _bodyCoords->_hipRight.Y);
            glVertex2f(_bodyCoords->_kneeRight.X, _bodyCoords->_kneeRight.Y);
            glEnd();

            // knee to foot
            glBegin(GL_LINES);
            glVertex2f(_bodyCoords->_kneeRight.X, _bodyCoords->_kneeRight.Y);
            glVertex2f(_bodyCoords->_footRight.X, _bodyCoords->_footRight.Y);
            glEnd();

            // left
            // neck to shoulder
            glBegin(GL_LINES);
            glVertex2f(_bodyCoords->_cervicalSpine.X, _bodyCoords->_cervicalSpine.Y);
            glVertex2f(_bodyCoords->_shoulderLeft.X, _bodyCoords->_shoulderLeft.Y);
            glEnd();

            // shoulder to elbow
            glBegin(GL_LINES);
            glVertex2f(_bodyCoords->_shoulderLeft.X, _bodyCoords->_shoulderLeft.Y);
            glVertex2f(_bodyCoords->_elbowLeft.X, _bodyCoords->_elbowLeft.Y);
            glEnd();

            // shoulder to elbow
            glBegin(GL_LINES);
            glVertex2f(_bodyCoords->_elbowLeft.X, _bodyCoords->_elbowLeft.Y);
            glVertex2f(_bodyCoords->_handLeft.X, _bodyCoords->_handLeft.Y);
            glEnd();

            // spine to hip
            glBegin(GL_LINES);
            glVertex2f(_bodyCoords->_sacrumSpine.X, _bodyCoords->_sacrumSpine.Y);
            glVertex2f(_bodyCoords->_hipLeft.X, _bodyCoords->_hipLeft.Y);
            glEnd();

            // hip to knee
            glBegin(GL_LINES);
            glVertex2f(_bodyCoords->_hipLeft.X, _bodyCoords->_hipLeft.Y);
            glVertex2f(_bodyCoords->_kneeLeft.X, _bodyCoords->_kneeLeft.Y);
            glEnd();

            // knee to foot
            glBegin(GL_LINES);
            glVertex2f(_bodyCoords->_kneeLeft.X, _bodyCoords->_kneeLeft.Y);
            glVertex2f(_bodyCoords->_footLeft.X, _bodyCoords->_footLeft.Y);
            glEnd();
        }

        // swap window
        SDL_GL_SwapWindow(_window);

        processInput();
    }
}
