#ifndef ControllerList_h
#define ControllerList_h

#include "Controller.h"

template<class T, int SIZE>
class ControllerList {

    public:

        void addController(Controller& controller) {
            controllers[controllerSize] = &controller;
            controllerSize++;
        }

        T* setActiveController(int controllerIndex) {
            activeControllerIndex = controllerIndex;
            activeController = controllers[activeControllerIndex];
            return activeController;
        }

        T* incrementController() {
            activeControllerIndex = ((activeControllerIndex + 1) % (controllerSize));
            activeController = controllers[activeControllerIndex];
            return activeController;
        }

        T* decrementController() {
            activeControllerIndex = activeControllerIndex > 0 ? activeControllerIndex - 1 : controllerSize - 1;
            activeController = controllers[activeControllerIndex];
            return activeController;
        }

        T* getActiveController() {
            return activeController;
        }

    private:

        int controllerSize = 0;
        T* controllers[SIZE];
        int activeControllerIndex = 0;
        T* activeController = 0;

};

#endif