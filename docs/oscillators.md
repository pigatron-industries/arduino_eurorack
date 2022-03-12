---
order: 5
title: Oscillators
---

# Oscillators and WaveShapes

Oscillators can be combined with different WaveShapes to produce repeating wave forms. 

All oscillators have a process method wich must be called at the specified sample rate in order to give the next sample. It is up to your code to call this at the correct rate.

```cpp
float sample = oscillator.process();
```

## WaveOscillator

Basic oscillator which uses any WaveShape to produce a repeating wave form. 

### Instantiation

There are 2 basic ways of instantiating a WaveOscillator.

The first way is to let the oscillator instantiate it's own WaveShape object, you just need to tell it the type of the WaveShape you want e.g. to create a basic Sine wave oscillator:

``` cpp
WaveOscillator<Sine> oscillator;
```

The second way is to instantiate the WaveShape yourself, outside of the oscillator, and give the oscillator a reference to it:

```
Sine sine;
WaveOscillator<Sine&> oscillator = WaveOscillator(sine);
```

### Initialisation

The oscillator must be initialised with the sample rate before it can be used:

``` cpp
oscillator.init(sampleRate);
```

### Parameters

Other parameters that can be set are:

- **Frequency**

Set frequency in Hz.

``` cpp
oscillator.setFrequency(frequency);
```

- **Amplitude** 

Set amplitude, nomrmally between 0 and 1.

``` cpp
oscillator.setAmplitude(amplitude);
```

- **Period**

Does the same as setting the frequency but using the wave period in seconds instead.

``` cpp
oscillator.setPeriod(period);
```

- **Phase**

The phase is automatically incremented by the process function but can also be reset or set to any point manually. Phase should be between 0 and 1.

``` cpp
oscillator.setPhase(phase);
```

- **Polyblep**

Polyblep can be enabled but only has an effect if the WaveShape supports it.

``` cpp
oscillator.setPolyblep(true);
```

---

## WaveShapes

Shapes used by an oscillator. Some shapes support polyblep, which is a means of bandlimiting a waveshape so that aliasing artifacts are reduced when played at higher frequencies. Polyblep must be turned on at the oscillator level.


### Sine

A basic sine wave.

![Sine](images/waveshape_sine.drawio.png)

### Pulse

A pulse wave shape. Supports polyblep.

- **Width**

Set the width of the pulse from 0 (very short pulse), to 1 (long pulse)

```cpp
pulse.setWidth(pulseWidth);
```

![Pulse](images/waveshape_pulse.drawio.png)


### Triangle

A basic triangle wave. Supports polyblep.

![Triangle](images/waveshape_triangle.drawio.png)


### Saw

A basic saw wave. Supports polyblep.

![Saw](images/waveshape_saw.drawio.png)


### AsymmetricalTriangle

A triangle wave with the optional to move the point from sawtooth to ramp wave.

- **Peak Position**

Set the position of the peak from 0 to 1.

```cpp
triangle.setPeakPosition(peakPosition);
```

![Asymmetrical Triangle](images/waveshape_asymmetrical_triangle.drawio.png)

### Line

A Line is intended to be used as part of a longer WaveSequence although it could be used on it's own to create a ramp or saw like wave form

A line has the following parameters:

- **Start Value**: The amplitude at the start of the line.
- **End Value**: The amplitude of the end of the line.
- **Length**: The length of the line measured as a fraction of the total phase of the waveform.


### WaveSequence

Used to put together multiple other WaveShapes to create a longer WaveShape. Can also be use for envelopes. The WaveShape types must be specified as tempalte parameters. e.g A wave made from 3 lines:

``` cpp
WaveSequence<3, Line> lineShape;
```

The properties of each individual segment of the sequence can be changed, e.g. for a sequence made of lines:

```cpp
lineShape.segment(0).setStartValue(-0.8);
lineShape.segment(0).setEndValue(0.8);
lineShape.segment(0).setLength(0.2);
lineShape.segment(1).setStartValue(0.8);
lineShape.segment(1).setEndValue(0.8);
lineShape.segment(1).setLength(0.6);
lineShape.segment(2).setStartValue(0.8);
lineShape.segment(2).setEndValue(-0.8);
lineShape.segment(2).setLength(0.2);
```

If used with an oscillator, the total length of the sequence should add up to 1, otherwise the oscillator frequency calculations would play it back at the wrong frequency.

If the end position of a segment does not match the start position of the next segment then a jump will occur.


### WaveSelector

Allows a single WaveShape to be selected from a list at runtime. The WaveShapes to be selected from can be added as template parameters. Since the template names can get lengthy a typedef can be used:

```cpp
typedef WaveSelector<Sine, Triangle, Saw, Pulse> WaveSelectionT;
WaveSelectionT waveSelector;
WaveOscillator<WaveSelectionT&> oscillator = WaveOscillator<WaveSelectionT&>(waveSelector);
```

Then, at runtime, a selection can be made to change which wave the oscillator uses. The select function uses the index of the waveform in the list.

```cpp
waveSelector.select(2);
```


### WaveTable

TODO

### WaveInterpolator

TODO


