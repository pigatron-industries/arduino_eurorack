#ifdef TEST_COMPILE
    #include "eurorack.h"
    #include "eurorack_dsp.h"
    #include "eurorack_max11300.h"
    #include "eurorack_mcp23s17.h"
    #include "eurorack_hc595.h"
    #include "eurorack_is32fl3738.h"
    #include "eurorack_dac8164.h"

    void setup() {}
    void loop() {}

    //Native

    class Hardware {
        public:
            static Hardware hw;
            AnalogInput(A0)
            AnalogInput(test1, A0)
            AnalogOutput(A1)
            AnalogOutput(test2, A1)
            DigitalInput(10)
            DigitalInput(test3, 10)
            DigitalOutput(11)
            DigitalOutput(test4, 11)

            AnalogInputSumPin<> sum = AnalogInputSumPin<>(Hardware::hw.A0, Hardware::hw.test1);
    };

    Hardware Hardware::hw;

    void testNativePins() {
        Hardware::hw.A0.analogRead();
        Hardware::hw.A1.analogWrite(5);
        Hardware::hw.D10.digitalRead();
        Hardware::hw.D11.digitalWrite(true);

        Hardware::hw.test1.analogRead();
        Hardware::hw.test2.analogWrite(5);
        Hardware::hw.test3.digitalRead();
        Hardware::hw.test4.digitalWrite(true);
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
    LinearInput<AnalogInputPin<MAX11300Device>> max11300Input = LinearInput<AnalogInputPin<MAX11300Device>>(max11300.pins[0], -5.0, 5.0, 0.0, 1.0);

    void testMAX11300Pins() {
        max11300.pins[0].setPinType(ANALOG_OUTPUT);
        max11300.pins[0].digitalWrite(true);
        max11300.pins[0].analogWrite(5);
        max11300.pins[0].digitalRead();
        max11300.pins[0].analogRead();
    }

    // IS32FL3738

    IS32FL3738Device is32fl3738 = IS32FL3738Device(Wire, IS32_ADDRESS_A);

    void testIS32FL3738Pins() {
        is32fl3738.pins[0].analogWrite(1);
    }

    // DAC8164

    DAC8164Device dac8164 = DAC8164Device();

    void testDAC8164Pins() {
        dac8164.pins[0].analogWrite(1);
    }

    // Analog Inputs

    LinearInput<> linearInput = LinearInput<>(Hardware::hw.A0, -5.0, 5.0, 0.0, 5.0);
    LinearInput<> linearSumInput = LinearInput<>(Hardware::hw.sum, -5.0, 5.0, 0.0, 5.0);
    AnalogGateInput<> analogGateInput = AnalogGateInput<>(Hardware::hw.A0, 3.0);
    CrossfadeInput<> crossfadeInput = CrossfadeInput<>(Hardware::hw.A0, -5.0, 5.0);
    ExpInput<> expInput = ExpInput<>(Hardware::hw.A0);
    PowInput<> powInput = PowInput<>(Hardware::hw.A0, 2, -5.0, 5.0);

    void testAnalogInputs() {
        linearInput.update();
        linearInput.getValue();
        analogGateInput.update();
        analogGateInput.isTriggeredOn();
        analogGateInput.isGateOn();
    }

    // Digital inputs

    GateInput<> gateInput = GateInput<>(Hardware::hw.D10);
    PushButton<> pushButton = PushButton<>(Hardware::hw.D10);
    eurorack::TriggerInput<> triggerInput = eurorack::TriggerInput<>(Hardware::hw.D10, true, 10);

    void testDigitalInputs() {
        gateInput.update();
        pushButton.update();
    }

    // Digital Outputs

    TriggerOutput<> triggerOutput = TriggerOutput<>(Hardware::hw.D11);

    void testDigitalOutputs() {
        triggerOutput.trigger();
    }

    // Analog Outputs

    AnalogTriggerOutput<> analogTriggerOutput = AnalogTriggerOutput<>(Hardware::hw.A1);

    void testAnalogOutputs() {
        analogTriggerOutput.trigger();
    }

#endif
