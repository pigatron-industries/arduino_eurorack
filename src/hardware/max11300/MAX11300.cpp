
#include "MAX11300.h"

// default values
#define DEFAULT_THRESHOLD	0x03ff
#define TEMP_LSB			(0.125/16)

MAX11300::MAX11300(SPIClass *spi, uint8_t convertPin, uint8_t selectPin) {
		_convertPin = convertPin;
		_spi = spi;
		_select = selectPin;
		_interrupt = 255;
		_analogStatus = 0;
		pinMode(_convertPin, OUTPUT);
		pinMode(_select, OUTPUT);
		digitalWrite(_convertPin, HIGH);
		digitalWrite(_select, HIGH);
		_spiMode = new SPISettings(20000000L, MSBFIRST, SPI_MODE0);
		_spi->begin();
		setDefaults();
}

MAX11300::MAX11300(SPIClass *spi, uint8_t convertPin, uint8_t selectPin, uint8_t interruptNumber) {
		_convertPin = convertPin;
		_spi = spi;
		_select = selectPin;
		_interrupt = interruptNumber;
		_analogStatus = 0;
		pinMode(_convertPin, OUTPUT);
		pinMode(_select, OUTPUT);
		digitalWrite(_convertPin, HIGH);
		digitalWrite(_select, HIGH);
		_spiMode = new SPISettings(20000000L, MSBFIRST, SPI_MODE0);
		_spi->begin();
		_spi->usingInterrupt(_interrupt);
		setDefaults();
}

void MAX11300::setDefaults() {
	setDACref(DACInternal);
    setDACmode(SequentialUpdate);
    setADCmode(ContinuousSweep);
}

bool MAX11300::begin() {
		//if (_interrupt < 255) {attachInterrupt(_interrupt, MAX11300::serviceInterrupt, FALLING);}
		return true;
}

bool MAX11300::end() {
		if (_interrupt < 255) detachInterrupt(_interrupt);
		return true;
}

bool MAX11300::setPinMode(uint8_t pin, pinMode_t mode) {
		return this->setPinMode(pin, mode, 255);
}

bool MAX11300::setPinMode(uint8_t pin, pinMode_t mode, uint8_t differentialPin) {
		uint16_t configuration;
		uint16_t negConf;
		if ((mode == analogDifferential) && (differentialPin > 19)) return false;	// if we don't have a valid additional pin, bail
		if (differentialPin == pin) return false;									// this configuration is invalid, so bail
		configuration = readRegister(MAX_FUNC_BASE + pin);							// read in the existing configuration so we don't stomp it
		switch (mode) {
				case digitalIn:
						if (getPinThreshold(pin) == 0) {
								setPinThreshold(pin, DEFAULT_THRESHOLD);
								delay(1);
						}
						configuration = MAX_FUNCID_GPI;
						break;
				case digitalOut:
						if (getPinThreshold(pin) == 0) {
								setPinThreshold(pin, DEFAULT_THRESHOLD);
								delay(1);
						}
						configuration = MAX_FUNCID_GPO;
						break;
				case analogIn:
						configuration = (configuration & ~(MAX_FUNCID_MASK)) | MAX_FUNCID_ADC;
						break;
				case analogOut:
						configuration = (configuration & ~(MAX_FUNCID_MASK)) | MAX_FUNCID_DAC;
						break;
				case analogDifferential:
						configuration = (configuration & ~(MAX_FUNCID_MASK)) | MAX_FUNCID_ADC_DIFF_POS;
						negConf = readRegister(MAX_FUNC_BASE + differentialPin);
						negConf = (negConf & ~(MAX_FUNCID_MASK)) | MAX_FUNCID_ADC_DIFF_NEG;
						if (!writeRegister((MAX_FUNC_BASE + differentialPin), negConf)) return false;
						break;
				case highImpedance:
						configuration = MAX_FUNCID_HI_Z;
						break;
				default:
						return false;
		}
		if (writeRegister((MAX_FUNC_BASE + pin), configuration)) return true;
		return false;
}

bool MAX11300::setPinModeAnalogOut(uint8_t pin, DACRange_t range) {
		uint16_t configuration = MAX_FUNCID_DAC | range;
		if (writeRegister((MAX_FUNC_BASE + pin), configuration)) return true;
		return false;
}

bool MAX11300::setPinModeAnalogIn(uint8_t pin, ADCRange_t range) {
		uint16_t configuration = MAX_FUNCID_ADC | range;
		if (writeRegister((MAX_FUNC_BASE + pin), configuration)) return true;
		return false;
}

pinMode_t MAX11300::getPinMode(uint8_t pin) {
		uint16_t conf = readRegister(MAX_FUNC_BASE + pin);
		conf &= MAX_FUNCID_MASK;
		if (conf == MAX_FUNCID_HI_Z) return highImpedance;
		if (conf == MAX_FUNCID_GPI) return digitalIn;
		if (conf == MAX_FUNCID_GPO) return digitalOut;
		if (conf == MAX_FUNCID_ADC) return analogIn;
		if (conf == MAX_FUNCID_DAC) return analogOut;
		if (conf == MAX_FUNCID_ADC_DIFF_POS) return analogDifferential;
		if (conf == MAX_FUNCID_ADC_DIFF_NEG) return differentialNegative;
		return pinModeNONE;
}

int8_t MAX11300::getDifferentialPin(uint8_t pin) {
		uint16_t conf = readRegister(MAX_FUNC_BASE + pin);
		return (conf & MAX_FUNCPRM_ASSOC_MASK);
}

bool MAX11300::setPinThreshold(uint8_t pin, uint16_t voltage) {
		return writeAnalogPin(pin, voltage);
}

uint16_t MAX11300::getPinThreshold(uint8_t pin) {
		return readRegister(MAX_DACDAT_BASE + pin);
}

bool MAX11300::setDigitalInputMode(uint8_t pin, GPImode_t mode) {
		uint8_t gpiAddress, gpiOffset;
		if (pin > 15) {
				gpiAddress = MAX_GPIMD_16_19;
				gpiOffset = 2*(pin - 16);
		} else if (pin > 7) {
				gpiAddress = MAX_GPIMD_8_15;
				gpiOffset = 2*(pin - 8);
		} else {
				gpiAddress = MAX_GPIMD_0_7;
				gpiOffset = 2*pin;
		}
		return readModifyWriteRegister(gpiAddress, (0x03 << gpiOffset), ((uint16_t)(mode) << gpiOffset));
}

GPImode_t MAX11300::getDigitalInputMode(uint8_t pin) {
		uint8_t gpiAddress, gpiOffset;
		uint16_t gpimdRegister;
		if (pin > 15) {
				gpiAddress = MAX_GPIMD_16_19;
				gpiOffset = 2*(pin - 16);
		} else if (pin > 7) {
				gpiAddress = MAX_GPIMD_8_15;
				gpiOffset = 2*(pin - 8);
		} else {
				gpiAddress = MAX_GPIMD_0_7;
				gpiOffset = 2*pin;
		}
		gpimdRegister = ((readRegister(gpiAddress) >> gpiOffset) && 0x03);
		if (gpimdRegister == 0x0) return GPIneither;
		if (gpimdRegister == 0x1) return GPIpositive;
		if (gpimdRegister == 0x2) return GPInegative;
		if (gpimdRegister == 0x3) return GPIboth;
		return GPINONE;
}

uint16_t MAX11300::readAnalogPin (uint8_t pin) {
		switch(getADCmode()) {
				case Idle:
						return 0;
						break;
				case SingleSweep:
				case SingleSample:
						while (!(isAnalogDataReady(pin))) {
								startConversion();
								while (!(isAnalogConversionComplete()));
						}
						break;
				case ContinuousSweep:
						break;
				default:
						return 0;
		}
		_analogStatus &= ~(1 << pin);					// show that we've read the data from that pin
		return readRegister(MAX_ADCDAT_BASE + pin);
}

bool MAX11300::readDigitalPin (uint8_t pin) {
		uint8_t address, offset;
		uint16_t reg;
		if (pin > 15) {
				address = MAX_GPIDAT_H;
				offset = pin - 15;
		} else {
				address = MAX_GPIDAT_L;
				offset = pin;
		}
		reg = readRegister(address);
		return (bool)((reg >> offset) & 1);
}

bool MAX11300::writeAnalogPin (uint8_t pin, uint16_t value) {
	return writeRegister((MAX_DACDAT_BASE + pin), value);
}

bool MAX11300::writeDigitalPin (uint8_t pin, bool value) {
		uint8_t address, offset;
		uint16_t reg;
		if (pin > 15) {
				address = MAX_GPODAT_H;
				offset = pin - 15;
		} else {
				address = MAX_GPODAT_L;
				offset = pin;
		}
		reg = readRegister(address);
		if (value) {
				reg |= 1 << offset;
		} else {
				reg &= ~(1 << offset);
		}
		return writeRegister(address, reg);
}

bool MAX11300::setPinAveraging (uint8_t pin, uint8_t samples) {
		uint16_t val = 0;
		switch (samples) {
				case 1:
						val = 0x0;
						break;
				case 2:
						val = (0x1 << MAX_FUNCPRM_AVG);
						break;
				case 4:
						val = (0x2 << MAX_FUNCPRM_AVG);
						break;
				case 8:
						val = (0x3 << MAX_FUNCPRM_AVG);
						break;
				case 16:
						val = (0x4 << MAX_FUNCPRM_AVG);
						break;
				case 32:
						val = (0x5 << MAX_FUNCPRM_AVG);
						break;
				case 64:
						val = (0x6 << MAX_FUNCPRM_AVG);
						break;
				case 128:
						val = (0x7 << MAX_FUNCPRM_AVG);
						break;
				default:
						return false;
		}
		return readModifyWriteRegister((MAX_FUNC_BASE + pin), MAX_FUNCPRM_AVG_MASK, val);
}

uint8_t MAX11300::getPinAveraging (uint8_t pin) {
		uint16_t reg = readRegister(MAX_FUNC_BASE + pin);
		reg = (reg & MAX_FUNCPRM_AVG_MASK) >> MAX_FUNCPRM_AVG;
		return (pow(2,reg));
}

bool MAX11300::setPinADCref (uint8_t pin, ADCref_t reference) {
		return readModifyWriteRegister((MAX_FUNC_BASE + pin), MAX_FUNCPRM_AVR_MASK, (uint16_t)(reference));
}

ADCref_t MAX11300::getPinADCref (uint8_t pin) {
		uint16_t reg = readRegister(MAX_FUNC_BASE + pin);
		if (reg & MAX_FUNCPRM_AVR_MASK) return ADCExternal;
		return ADCInternal;
}

bool MAX11300::setDACref (DACref_t reference) {
		return readModifyWriteRegister(MAX_DEVCTL, (1 << MAX_DACREF), (uint16_t)(reference));
}

DACref_t MAX11300::getDACref (void) {
		uint16_t reg = readRegister(MAX_DEVCTL);
		if (reg & (1 << MAX_DACREF)) return DACExternal;
		return DACInternal;
}

bool MAX11300::setConversionRate(conversionRate_t rate) {
		return readModifyWriteRegister(MAX_DEVCTL, MAX_ADCCONV_MASK, (uint16_t)(rate));
}

conversionRate_t MAX11300::getConversionRate(void) {
		uint16_t reg = readRegister(MAX_DEVCTL);
		reg &= MAX_ADCCONV_MASK;
		if (reg == MAX_RATE_200) return rate200ksps;
		if (reg == MAX_RATE_250) return rate250ksps;
		if (reg == MAX_RATE_333) return rate333ksps;
		if (reg == MAX_RATE_400) return rate400ksps;
		return rateNONE;
}

double MAX11300::readInternalTemp (void) {
		return convertTemp(readRegister(MAX_TMPINTDAT));
}

double MAX11300::readExternalTemp1 (void) {
		return convertTemp(readRegister(MAX_TMPEXT1DAT));
}

double MAX11300::readExternalTemp2 (void) {
		return convertTemp(readRegister(MAX_TMPEXT2DAT));
}

bool MAX11300::setDACmode (DACmode_t mode) {
		return readModifyWriteRegister(MAX_DEVCTL, MAX_DACCTL_MASK, (uint16_t)(mode));
}

bool MAX11300::setADCmode (ADCmode_t mode) {
		return readModifyWriteRegister(MAX_DEVCTL, MAX_ADCCTL_MASK, (uint16_t)(mode));
}

ADCmode_t MAX11300::getADCmode (void) {
		uint16_t reg = readRegister(MAX_DEVCTL);
		reg &= MAX_ADCCTL_MASK;
		if (reg == MAX_ADC_IDLE) return Idle;
		if (reg == MAX_ADC_SINGLE_SWEEP) return SingleSweep;
		if (reg == MAX_ADC_SINGLE_CONVERSION) return SingleSample;
		if (reg == MAX_ADC_CONTINUOUS) return ContinuousSweep;
		return ADCmodeNONE;
}

bool MAX11300::burstAnalogRead (uint16_t* samples, uint8_t size) {
		return burstAnalogRead(0, samples, size);
}

bool MAX11300::burstAnalogWrite (uint16_t* samples, uint8_t size) {
		return burstAnalogWrite(0, samples, size);
}

bool MAX11300::burstAnalogRead (uint8_t startPin, uint16_t* samples, uint8_t size) {
		if (size > 20) size = 20;
		return readRegister((MAX_ADCDAT_BASE + startPin), samples, size);
}

bool MAX11300::burstAnalogWrite (uint8_t startPin, uint16_t* samples, uint8_t size) {
		if (size > 20) size = 20;
		return writeRegister((MAX_DACDAT_BASE + startPin), samples, size);
}

bool MAX11300::isAnalogDataReady (uint8_t pin) {
		if (readRegister(MAX_INT) & MAX_ADCDR_MASK) {
				// read in the analog status registers from the chip and update the internal tracking
				_analogStatus |= (((uint32_t)(readRegister(MAX_ADCST_H))) << 16) |
									(readRegister(MAX_ADCST_L));
		}
		if (_analogStatus & (1 << pin)) return true;
		return false;
}

bool MAX11300::isAnalogConversionComplete (void) {
		if (_analogFlag) {
				_analogFlag = false;
				return true;
		} else if (readRegister(MAX_INT) & MAX_ADCFLAG_MASK) return true;
		return false;
}

void MAX11300::serviceInterrupt(void) {
		lastEvent.time = micros();							// set the time as soon as possible
		uint16_t lastIntVector = lastEvent.lastIntVector;	// copy the last interrupt vector over for comparison
		lastEvent.clearEvent();								// clears everything except the time
		lastEvent.lastIntVector = readRegister(MAX_INT);	// load the latest interrupt vector
		uint16_t delta = ((lastEvent.lastIntVector ^ lastIntVector) & lastEvent.lastIntVector);
		if (delta & MAX_VMON_MASK) {
				lastEvent.event = VoltageMonitor;
		} else if (delta & MAX_TMPINT_MASK) {
				if (delta & (1 << MAX_TMPINT_AVAIL)) lastEvent.event = InternalTempAvailable;
				if (delta & (1 << MAX_TMPINT_HI)) lastEvent.event = InternalTempMonitorHigh;
				if (delta & (1 << MAX_TMPINT_LO)) lastEvent.event = InternalTempMonitorLow;
		} else if (delta & MAX_TMPEXT1_MASK) {
				if (delta & (1 << MAX_TMPEXT1_AVAIL)) lastEvent.event = ExternalTemp1Available;
				if (delta & (1 << MAX_TMPEXT1_HI)) lastEvent.event = ExternalTemp1MonitorHigh;
				if (delta & (1 << MAX_TMPEXT1_LO)) lastEvent.event = ExternalTemp1MonitorLow;
		} else if (delta & MAX_TMPEXT2_MASK) {
				if (delta & (1 << MAX_TMPEXT2_AVAIL)) lastEvent.event = ExternalTemp2Available;
				if (delta & (1 << MAX_TMPEXT2_HI)) lastEvent.event = ExternalTemp2MonitorHigh;
				if (delta & (1 << MAX_TMPEXT2_LO)) lastEvent.event = ExternalTemp2MonitorLow;
		} else if (delta & MAX_DACOI_MASK) {
				lastEvent.event = DACovercurrent;
				lastEvent.status = (((uint32_t)(readRegister(MAX_DACOI_H))) << 16) | (readRegister(MAX_DACOI_L));
		} else if (delta & MAX_GPIDM_MASK) {
				lastEvent.event = DigitalDataMissed;
				lastEvent.status = (((uint32_t)(readRegister(MAX_GPIST_H))) << 16) | (readRegister(MAX_GPIST_L));
		} else if (delta & MAX_GPIDR_MASK) {
				lastEvent.event = DigitalDataReady;
				lastEvent.status = (((uint32_t)(readRegister(MAX_GPIST_H))) << 16) | (readRegister(MAX_GPIST_L));
		} else if (delta & MAX_ADCDM_MASK) {
				lastEvent.event = AnalogDataMissed;
		} else if (delta & MAX_ADCDR_MASK) {
				lastEvent.event = AnalogDataReady;
				isAnalogDataReady(0);
				lastEvent.status = _analogStatus;
		} else if (delta & MAX_ADCFLAG_MASK) {
				lastEvent.event = AnalogConversionComplete;
				_analogFlag = true;
		} else {
				lastEvent.event = eventNONE;
		}
}

MAX11300Event MAX11300::getLastEvent (void) {
		return lastEvent;
}

bool MAX11300::writeRegister (uint8_t address, uint16_t value) {
		return writeRegister(address, &value, 1);
}

bool MAX11300::writeRegister (uint8_t address, uint16_t * values, uint8_t size) {
		_spi->beginTransaction(*_spiMode);
		digitalWrite(_select, LOW);
		_spi->transfer((address << 1)); //stick a 0 on lsb to signify write mode
		for (uint8_t i = 0; i < size; i++) {
				_spi->transfer((uint8_t)((values[i] >> 8) & 0xff));
				_spi->transfer((uint8_t)(values[i] & 0xff));
		}
		digitalWrite(_select, HIGH);
		_spi->endTransaction();
		return true;
}

uint16_t MAX11300::readRegister (uint8_t address) {
		uint16_t val = 0;
		readRegister(address, &val, 1);
		return val;
}

uint16_t MAX11300::readRegister (uint8_t address, uint16_t * values, uint8_t size) {
		_spi->beginTransaction(*_spiMode);
		digitalWrite(_select, LOW);
		_spi->transfer((address << 1) | 1); //stick a 1 on lsb to signify read mode
		for (uint8_t i = 0; i < size; i++) {
				values[i] = ((uint16_t)(_spi->transfer(0)) << 8) + _spi->transfer(0);
		}
		digitalWrite(_select, HIGH);
		_spi->endTransaction();
		return size;
}

void MAX11300::startConversion(void) {
		digitalWrite(_convertPin, LOW);
		delayMicroseconds(1);
		digitalWrite(_convertPin, HIGH);
}

bool MAX11300::readModifyWriteRegister(uint8_t address, uint16_t mask, uint16_t value) {
		uint16_t reg = readRegister(address);
		reg = (reg & ~mask) | (uint16_t)(value);
		return writeRegister(address, reg);
}

double MAX11300::convertTemp (uint16_t temp) {
		return ((int16_t)(temp << 4) * TEMP_LSB);
}

uint16_t MAX11300::convertTemp (double temp) {
		return (uint16_t)(((int16_t)(temp/TEMP_LSB)) >> 4);
}

MAX11300Event::MAX11300Event(void) {
		this->clearEvent();
}

void MAX11300Event::clearEvent(void) {
		lastIntVector = 0;
		event = eventNONE;
		status = 0;
}
