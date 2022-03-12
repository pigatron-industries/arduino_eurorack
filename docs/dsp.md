---
order: 5
---

# DSP

## Oscillators

Oscillators can be combined with different WaveShapes to produces repeating wave forms. 

All oscillators have a process method wich must be called at the specified sample rate in order to give the next sample.

### WaveOscillator

Basic oscillator which uses any WaveShape to produce a repeating wave form. There are 2 basic ways of defining it.

The first way is to let the oscillator instantiate it's own WaveShape object, you just need to tell it the type of the WaveShape you want e.g. to create a basic Sine wave oscillator:

``` cpp
WaveOscillator<Sine> oscillator;
```

The second way is to instantiate the WaveShape yourself, outside of the oscillator, and give the oscillator a reference to it:

```
Sine sine;
WaveOscillator<Sine&> oscillator = WaveOscillator(sine);
```

The oscialltor must be initialised with the sample rate before it can be used:

``` cpp
oscillator.init(sampleRate);
```

Other parameters that can be set are:

``` cpp
oscillator.setFrequency(frequency);
oscillator.setAmplitude(amplitude);
oscillator.setPeriod(period);
oscillator.setPhase(phase);
```

``` cpp
oscillator.setPolyblep(true);
```

Polyblep can be enabled but only has an effect if the WaveShape supports it.


## WaveShapes


