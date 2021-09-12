#ifndef ControllerList_h
#define ControllerList_h

template<class T, int SIZE>
class ControllerList {

    public:

        int getSize() { return controllerSize; }

        void addController(T& controller) {
            controllers[controllerSize] = &controller;
            controllerSize++;
            if(activeController == nullptr) {
                activeController = &controller;
            }
        }

        T* setActiveController(int controllerIndex) {
            if(controllerIndex >= controllerSize) {
                return activeController;
            }
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

        T* cycle(int amount) {
            if(amount > 0) {
                return incrementController();
            } else if(amount < 0) {
                return decrementController();
            }
            return getActiveController();
        }

        T* getActiveController() {
            return activeController;
        }

        int getActiveControllerIndex() {
            return activeControllerIndex;
        }

    private:

        int controllerSize = 0;
        T* controllers[SIZE];
        int activeControllerIndex = 0;
        T* activeController = nullptr;

};

#endif