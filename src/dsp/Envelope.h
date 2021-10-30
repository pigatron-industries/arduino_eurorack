#ifndef Envelope_h
#define Envelope_h

class Envelope
{
    public:
        static const int MAX_SEGMENTS = 6;
        Envelope() {}
        void init(float sampleRate, int segmentCount = 2, float length = 1, bool repeat = false);
        void trigger();
        float process();

        void setSegmentEndValue(int index, float endValue);
        void setSegmentLength(int index, float length);
        void setFrequency(float frequency);
        
    private:

        class Segment {
            public:
                Segment() {}
                Segment(float length, float start, float end) { 
                    this->length = length; this->startValue = start; this->endValue = end;
                    calculateGradient();
                }
                float getLength() { return length; }
                float getStartValue() { return startValue; }
                float getEndValue() { return endValue; }
                float getGradient() { return gradient; }
                void setLength(float length) { this->length = length; calculateGradient(); }
                void setEndValue(float endValue) { this->endValue = endValue; calculateGradient(); }
                void setStartValue(float startValue) { this->startValue = startValue; calculateGradient(); }

            private:
                float length, startValue, endValue;
                float gradient;
                void calculateGradient();
        };

        Segment segments[MAX_SEGMENTS];
        int segmentCount;
        float totalLength;

        int sustainPoint;
        bool repeat;
 
        float sampleRate;
        float sampleRateRecip;
        float increment;
        
        bool stopped;
        float position;
        int segmentIndex;
        float length;

        int getSegmentForPosition(float position);
        void incrementPosition();
};

#endif