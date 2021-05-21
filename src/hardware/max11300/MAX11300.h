
#ifndef __MAX11300_H__
#define __MAX11300_H__

#include <Arduino.h>
#include <SPI.h>
#include "MAX11300registers.h"


enum pinMode_t {
	digitalIn = 			MAX_FUNCID_GPI,
	digitalOut = 			MAX_FUNCID_GPO,
	analogIn = 				MAX_FUNCID_ADC,
	analogOut = 			MAX_FUNCID_DAC,
	analogDifferential = 	MAX_FUNCID_ADC_DIFF_POS,
	differentialNegative = 	MAX_FUNCID_ADC_DIFF_NEG,
	highImpedance = 		MAX_FUNCID_HI_Z,
	pinModeNONE = 			0xffff
};

enum DACRange_t {
	DACZeroTo10 = 			MAX_DAC_RANGE_0_10,
	DACNegative5to5 = 		MAX_DAC_RANGE_5_5,
	DACNegative10to0 = 		MAX_DAC_RANGE_10_0,
	DACrangeNONE = 			0xffff
};

enum ADCRange_t {
	ADCZeroTo10 = 			MAX_ADC_RANGE_0_10,
	ADCNegative5to5 = 		MAX_ADC_RANGE_5_5,
	ADCNegative10to0 = 		MAX_ADC_RANGE_10_0,
	ADCZeroTo2_5 = 			MAX_ADC_RANGE_0_2_5,
	ADCrangeNONE = 			0xffff
};

enum ADCmode_t {
	Idle = 				MAX_ADC_IDLE,
	SingleSweep = 		MAX_ADC_SINGLE_SWEEP,
	SingleSample =		MAX_ADC_SINGLE_CONVERSION,
	ContinuousSweep	=	MAX_ADC_CONTINUOUS,
	ADCmodeNONE = 		0xffff
};

enum DACmode_t {
	SequentialUpdate = 		MAX_DAC_SEQUENTIAL,
	ImmediateUpdate  = 		MAX_DAC_IMMEDIATE,
	DACmodeNONE = 		0xffff
};

enum GPImode_t {
	GPIneither	= 		0x0,
	GPIpositive	= 		0x1,
	GPInegative	= 		0x2,
	GPIboth		= 		0x3,
	GPINONE		= 		0xff
};

enum conversionRate_t {
	rate200ksps	= 		MAX_RATE_200,
	rate250ksps = 		MAX_RATE_250,
	rate333ksps = 		MAX_RATE_333,
	rate400ksps = 		MAX_RATE_400,
	rateNONE = 			0xffff
};

enum ADCref_t {
	ADCInternal =	0x0000,
	ADCExternal = 	(1 << MAX_FUNCPRM_AVR),
	ADCrefNONE =	0xffff
};

enum DACref_t {
	DACExternal = 	0x0000,
	DACInternal = 	(1 << MAX_DACREF),
	DACrefNONE = 	0xffff
};

enum eventType_t {
	VoltageMonitor,
	InternalTempMonitorHigh,
	ExternalTemp1MonitorHigh,
	ExternalTemp2MonitorHigh,
	InternalTempMonitorLow,
	ExternalTemp1MonitorLow,
	ExternalTemp2MonitorLow,
	InternalTempAvailable,
	ExternalTemp1Available,
	ExternalTemp2Available,
	DACovercurrent,
	DigitalDataReady,
	DigitalDataMissed,
	AnalogDataReady,
	AnalogDataMissed,
	AnalogConversionComplete,
	eventNONE
};

class MAX11300Event {
	public:
		// Methods
		MAX11300Event(void);
		void clearEvent(void);

		// Members
		unsigned long 	time;			// the time in microseconds at which the last event occurred
		uint16_t 		lastIntVector;	// the interrupt vector the last time this was written
		eventType_t 	event;			// type of interrupt event
		uint32_t 		status;			// shows which pin(s) are responsible
	private:
};

class MAX11300 {

	public:

		// Methods
		/**
		 * Constructor
		 *
		 * @param spi - The SPI interface the MAX11300 is attached to.
		 * @param convertPin - The pin attached to the CNVT pin on the MAX11300
		 *
		 */
		MAX11300(SPIClass* spi, uint8_t convertPin, uint8_t selectPin);
		MAX11300(SPIClass* spi, uint8_t convertPin, uint8_t selectPin, uint8_t interruptNumber);

		void setDefaults();
		bool begin();
		bool end();

		/**
		 * Set the given pin to the given mode
		 *
		 * @param pin - The target MAX11300 pin
		 * @param mode - The mode of the target MAX11300 pin
		 * @param differentialPin - If the mode selected is analogDifferential, then add the second pin to use.
		 * @retval true - The pin mode setting succeeded
		 * @retval false - The pin mode setting failed, or no differential pin was given for analogDifferential
		 */
		bool setPinMode(uint8_t pin, pinMode_t mode);
		bool setPinMode(uint8_t pin, pinMode_t mode, uint8_t differentialPin);

		bool setPinModeAnalogOut(uint8_t pin, DACRange_t range);
		bool setPinModeAnalogIn(uint8_t pin, ADCRange_t range);

		/**
		 * Read the mode of the given pin
		 *
		 * @param pin - The pin to read from
		 */
		pinMode_t getPinMode(uint8_t pin);

		/**
		 * Read the differential partner of a given pin
		 *
		 * @param pin - The pin to read the differential partner of
		 * @retval The differential partner of pin, or -1 if the given pin is not in differential mode
		 */
		int8_t getDifferentialPin(uint8_t pin);

		/**
		 * Set the given pin's digital logic threshold or digital output voltage
		 *
		 * @param pin - The target MAX11300 pin
		 * @param voltage - The threshhold or output voltage
		 */
		bool setPinThreshold(uint8_t pin, uint16_t voltage);

		/**
		 * Get the given pin's digital logic threshold or digital output voltage
		 *
		 * @param pin - The target MAX11300 pin
		 * @retval false - The threshold or output value
		 */
		uint16_t getPinThreshold(uint8_t pin);
		bool setDigitalInputMode(uint8_t pin, GPImode_t mode);
		GPImode_t getDigitalInputMode(uint8_t pin);

		uint16_t readAnalogPin (uint8_t pin);
		bool readDigitalPin (uint8_t pin);
		bool writeAnalogPin (uint8_t pin, uint16_t value);
		bool writeDigitalPin (uint8_t pin, bool value);
		bool setPinAveraging (uint8_t pin, uint8_t samples);
		uint8_t getPinAveraging (uint8_t pin);
		bool setPinADCref (uint8_t pin, ADCref_t reference);
		ADCref_t getPinADCref (uint8_t pin);
		bool setDACref (DACref_t reference);
		DACref_t getDACref (void);
		bool setConversionRate(conversionRate_t rate);
		conversionRate_t getConversionRate(void);
		double readInternalTemp (void);
		double readExternalTemp1 (void);
		double readExternalTemp2 (void);

		/**
		 * Set the conversion mode of the ADC
		 *
		 * @param mode - The mode to use. It is STRONGLY suggested that you only use Continuous Sweep
		 *
		 */
		bool setADCmode (ADCmode_t mode);
		bool setDACmode (DACmode_t mode);
		ADCmode_t getADCmode (void);
		bool burstAnalogRead (uint16_t* samples, uint8_t size);
		bool burstAnalogWrite (uint16_t* samples, uint8_t size);
		bool burstAnalogRead (uint8_t startPin, uint16_t* samples, uint8_t size);
		bool burstAnalogWrite (uint8_t startPin, uint16_t* samples, uint8_t size);
		bool isAnalogDataReady (uint8_t pin);
		bool isAnalogConversionComplete (void);

		void serviceInterrupt(void);
		MAX11300Event getLastEvent (void);

		bool writeRegister (uint8_t address, uint16_t value);
		bool writeRegister (uint8_t address, uint16_t* values, uint8_t size);
		uint16_t readRegister (uint8_t address);
		uint16_t readRegister (uint8_t address, uint16_t* values, uint8_t size);

	private:

		// Methods
		bool readModifyWriteRegister (uint8_t address, uint16_t mask, uint16_t value);
		void startConversion(void);
		double convertTemp (uint16_t temp);
		uint16_t convertTemp (double temp);

		// Members
		SPIClass* 	_spi;
		SPISettings* _spiMode;
		uint8_t 	_convertPin;
		uint8_t 	_interrupt;
		uint8_t 	_select;
		uint32_t	_analogStatus;
		bool		_analogFlag;
		MAX11300Event lastEvent;

};


#endif
