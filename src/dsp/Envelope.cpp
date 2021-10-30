#include "Envelope.h"

#include <math.h>

void Envelope::Segment::calculateGradient() {
    gradient = (endValue - startValue) / length;
}

void Envelope::init(float sampleRate, int segmentCount, float length, bool repeat) {
    this->sampleRate = sampleRate;
    this->sampleRateRecip = 1/sampleRate;
    this->segmentCount = segmentCount;
    this->length = length;
    this->repeat = repeat;
    this->increment = 1.0f/sampleRate;
    position = 0;
    segmentIndex = 0;
    stopped = !repeat;

    // start with evenly distributed points
    float segmentLength = length / float(segmentCount);
    for(int i = 0; i < segmentCount; i++) {
        segments[i] = Segment(segmentLength * float(i), 0, 0);
    }
}

void Envelope::trigger() {
    stopped = false;
    position = 0;
    segmentIndex = 0;
}

float Envelope::process() {
    Segment& currentSegment = segments[segmentIndex];

    float value;
    if(isinf(currentSegment.getGradient())) {
        value = currentSegment.getEndValue();
    } else {
        value = currentSegment.getStartValue() + position * currentSegment.getGradient();
    }

    if(!stopped) {
        incrementPosition();
    }

    return value;
}

void Envelope::incrementPosition() {
    Segment& currentSegment = segments[segmentIndex];
    position += increment;

    if(position > currentSegment.getLength()) {
        segmentIndex++;
        position -= currentSegment.getLength();
    }
    if(segmentIndex >= segmentCount) {
        if(repeat) {
            position -= totalLength;
            segmentIndex = getSegmentForPosition(position);
        } else {
            stopped = true;
            segmentIndex = 0;
            position = 0;
        }
    }
}

void Envelope::setSegmentEndValue(int index, float endValue) {
    segments[index].setEndValue(endValue);
    if(index < segmentCount-1) {
        segments[index+1].setStartValue(endValue);
    }
}

void Envelope::setSegmentLength(int index, float length) {
    segments[index].setLength(length);
    for(int i = 0; i < segmentCount; i++) {
        totalLength += segments[i].getLength();
    }
}

int Envelope::getSegmentForPosition(float position) {
    float runningLength = 0;
    for(int i = 0; i < segmentCount; i++) {
        runningLength += segments[i].getLength();
        if(position < runningLength) {
            return i;
        }
    }
    return 0;
}

void Envelope::setFrequency(float frequency) {
    increment = frequency * sampleRateRecip;
}