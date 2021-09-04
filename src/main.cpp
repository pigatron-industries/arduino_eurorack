#include "eurorack.h"

#ifdef TEST_COMPILE
    #include "eurorack_dsp.h"
    #include "eurorack_max11300.h"
    #include "eurorack_mcp23s17.h"
    #include "eurorack_hc595.h"

    //Native

    NativeDevice native = NativeDevice();
    AnalogInputPin<NativeDevice> nativeAnalogInputPin = AnalogInputPin<NativeDevice>(native, 10);
    AnalogOutputPin<NativeDevice> nativeAnalogOutputPin = AnalogOutputPin<NativeDevice>(native, 10);
    DigitalInputPin<NativeDevice> nativeDigitalInputPin = DigitalInputPin<NativeDevice>(native, 10);
    DigitalOutputPin<NativeDevice> nativeDigitalOutputPin = DigitalOutputPin<NativeDevice>(native, 10);

    void testNativePins() {
        nativeAnalogInputPin.analogRead();
        nativeAnalogOutputPin.analogWrite(5);
        nativeDigitalInputPin.digitalRead();
        nativeDigitalOutputPin.digitalWrite(true);
    }

    // HC595

    HC595Device hc595 = HC595Device(10, 11, 12);

    void testHC595Pins() {
        hc595.setDeferredOutput(false);
        hc595.pins[0].digitalWrite(true);
    }

    // MCP23S17

    MCP23S17Device mcp23s17 = MCP23S17Device(10, 0x20);

    void testMCP23S17Pins() {
        mcp23s17.pins[0].setPinType(DIGITAL_OUTPUT);
        mcp23s17.pins[0].digitalWrite(true);
        mcp23s17.pins[0].digitalRead();
    }

    // MAX11300

    MAX11300Device max11300 = MAX11300Device(&SPI, 10, 11);

    void testMAX11300Pins() {
        max11300.pins[0].setPinType(ANALOG_OUTPUT);
        max11300.pins[0].digitalWrite(true);
        max11300.pins[0].analogWrite(5);
        max11300.pins[0].digitalRead();
        max11300.pins[0].analogRead();
    }

    // Analog Inputs

    LinearInput<> linearInput = LinearInput<>(nativeAnalogInputPin, -5.0, 5.0, 0.0, 5.0);
    AnalogGateInput<> analogGateInput = AnalogGateInput<>(nativeAnalogInputPin, 3.0);
    CrossfadeInput<> crossfadeInput = CrossfadeInput<>(nativeAnalogInputPin, -5.0, 5.0);
    ExpInput<> expInput = ExpInput<>(nativeAnalogInputPin);
    PowInput<> powInput = PowInput<>(nativeAnalogInputPin, 2, -5.0, 5.0);

    void testAnalogInputs() {
        linearInput.update();
        linearInput.getValue();
        analogGateInput.update();
        analogGateInput.getValue();
    }

    // Digital inputs

    GateInput<> gateInput = GateInput<>(nativeDigitalInputPin);
    PushButton<> pushButton = PushButton<>(nativeDigitalInputPin);

    void testDigitalInputs() {
        gateInput.update();
        pushButton.update();
    }

    // Digital Outputs

    TriggerOutput<> triggerOutput = TriggerOutput<>(nativeDigitalOutputPin);

    void testDigitalOutputs() {
        triggerOutput.trigger();
    }

    // Analog Outputs

    AnalogTriggerOutput<> analogTriggerOutput = AnalogTriggerOutput<>(nativeAnalogOutputPin);

    void testAnalogOutputs() {
        analogTriggerOutput.trigger();
    }

#endif
