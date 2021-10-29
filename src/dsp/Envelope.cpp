#include "Envelope.h"

#include <Arduino.h>

void Envelope::init(float sampleRate, int pointCount, float length, bool repeat) {
    this->sampleRate = sampleRate;
    this->sampleRateRecip = 1/sampleRate;
    this->pointCount = pointCount;
    this->length = length;
    this->repeat = repeat;
    this->increment = 1.0f/sampleRate;
    position = 0;
    segment = 0;
    stopped = !repeat;

    // start with evenly distributed points
    float segmentLength = length / float(pointCount);
    for(int i = 0; i < pointCount; i++) {
        points[i] = Point(segmentLength * float(i), 0);
    }
}

void Envelope::trigger() {
    stopped = false;
    position = 0;
    segment = 0;
}

float Envelope::process() {
    Point point1 = points[segment];
    Point point2 = points[segment+1];
    float gradient = (point2.y-point1.y) / (point2.x-point1.x); //TODO precalculate gradients
    float value;
    if(isinf(gradient)) {
        value = point2.y;
    } else {
        float segmentX = position - point1.x;
        float segmentY = segmentX * gradient;
        value = point1.y + segmentY;
    }

    if(!stopped) {
        incrementPosition();
    }

    return value;
}

void Envelope::incrementPosition() {
    position += increment;

    if(position > points[segment+1].x) {
        segment++;
    }
    if(position > length) {
        if(repeat) {
            position -= length;
            segment = getSegmentForPosition(position);
        } else {
            stopped = true;
            segment = 0;
            position = 0;
        }
    }
}

void Envelope::setPoint(int index, Point point) {
    if(index > 0 && point.x < points[index-1].x) {
        point.x = points[index-1].x;
    } else if(index < pointCount-1 && point.x > points[index+1].x) {
        point.x = points[index+1].x;
    }
    points[index] = point;

    if(index == pointCount-1) {
        length = point.x;
    }

    //TODO recalculate gradient for segment before and after point
}

void Envelope::setSegmentLength(int index, float segmentLength) {
    float diff = (points[index].x + segmentLength) - points[index+1].x;
    for(int i = index+1; i < pointCount; i++) {
        points[i].x += diff;
    }
    length = points[pointCount-1].x;
}

int Envelope::getSegmentForPosition(float position) {
    for(int i = 0; i < pointCount; i++) {
        if(points[i].x > position) {
            return i-1;
        }
    }
    return pointCount-1;
}

void Envelope::setFrequency(float frequency) {
    increment = frequency * sampleRateRecip;
}