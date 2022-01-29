#ifndef BaseOscillator_h
#define BaseOscillator_h

class BaseOscillator
{
  public:
        virtual void setFrequency(const float f) = 0;
        virtual float process() = 0;
};

#endif