#ifndef Envelope_h
#define Envelope_h


class Point {
    public:
        Point() { x=0; y=0; }
        Point(float x, float y) { this->x = x; this->y = y; }
        float x;
        float y;
};

class Envelope
{
    public:
        static const int MAX_POINTS = 6;
        Envelope() {}
        void init(float sampleRate, int pointCount = 3, float length = 1, bool repeat = false);
        void trigger();
        float process();

        void setPoint(int index, Point point);
        void setSegmentLength(int index, float segmentLength);
        void setFrequency(float frequency);
        
    private:
        Point points[MAX_POINTS];
        int pointCount;
        int sustainPoint;
        bool repeat;
 
        float sampleRate;
        float sampleRateRecip;
        float increment;
        float position;
        bool stopped;

        int segment;
        float length;

        int getSegmentForPosition(float position);
        void incrementPosition();
};

#endif