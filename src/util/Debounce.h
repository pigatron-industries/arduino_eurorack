#ifndef Debounce_h
#define Debounce_h

#include <inttypes.h>

#define BOUNCE_LOCK_OUT 1

class Debounce {

    public:
        Debounce();
        void setInterval(uint16_t intervalMillis);
        void begin(bool value);
        bool update(bool value);
        bool read() const;
        bool fell() const;
        bool rose() const;

        bool changed( ) const { return getStateFlag(CHANGED_STATE); }
        unsigned long duration() const;
        unsigned long previousDuration() const;

    private:
        static const uint8_t DEBOUNCED_STATE = 0b00000001;
        static const uint8_t UNSTABLE_STATE  = 0b00000010;
        static const uint8_t CHANGED_STATE   = 0b00000100;

        unsigned long previousMillis;
        uint16_t intervalMillis;
        uint8_t state;
        unsigned long stateChangeLastTime;
        unsigned long durationOfPreviousState;

        inline void changeState();
        inline void setStateFlag(const uint8_t flag)       {state |= flag;}
        inline void unsetStateFlag(const uint8_t flag)     {state &= ~flag;}
        inline void toggleStateFlag(const uint8_t flag)    {state ^= flag;}
        inline bool getStateFlag(const uint8_t flag) const {return((state & flag) != 0);}

};

#endif
