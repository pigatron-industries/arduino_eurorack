#include "eurorack.h"

#ifdef TEST_COMPILE
    #include "eurorack_dsp.h"
    #include "eurorack_max11300.h"
    #include "eurorack_mcp23s17.h"
    #include "eurorack_hc595.h"

    NativeDevice native = NativeDevice();
    AnalogInputPin<NativeDevice> nativeAnalogInputPin = AnalogInputPin<NativeDevice>(native, 10);

    //devices
    HC595Device hc595 = HC595Device(10, 11, 12);
    MAX11300Device max11300 = MAX11300Device(&SPI, 10, 11);
    MCP23S17Device mcp23s17 = MCP23S17Device(10, 0x20);

    //IO
    LinearInput<> nativeInput = LinearInput<>(nativeAnalogInputPin, -5.0, 5.0, 0.0, 5.0);
    LinearInput<MAX11300Device> max11300Input = LinearInput<MAX11300Device>(max11300.pins[0], -5.0, 5.0, 0.0, 5.0);
    GateInput<MCP23S17Device> mcp23s17Input = GateInput<MCP23S17Device>(mcp23s17.pins[0]);

    void test() {
        nativeAnalogInputPin.analogRead();

        hc595.pins[0].digitalWrite(true);
        hc595.setDeferredOutput(false);

        max11300.pins[0].digitalWrite(true);
        max11300.pins[0].analogWrite(5);
        max11300.pins[0].digitalRead();
        max11300.pins[0].analogRead();

        mcp23s17.pins[0].digitalWrite(true);
        mcp23s17.pins[0].digitalRead();
    }

#endif
