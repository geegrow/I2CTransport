#ifndef GEEGROW_I2C_CLIENT_H_
#define GEEGROW_I2C_CLIENT_H_

#include <Arduino.h>
#include <util/twi.h>

//Define CPU Clock 16MHz
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

//Define TWI frequency 10kHz by default
#ifndef TWI_FREQ
#define TWI_FREQ 100000L
#endif

#define I2C_READ 1
#define I2C_WRITE 0

class I2C {
	public:
		I2C();
		void begin();
		void setClock(uint32_t frequency);
		size_t send(uint8_t, bool preventFreezing = false);
		int8_t read();
		int8_t readAck();
		void sendAddress(uint8_t address, uint8_t w, bool preventFreezing = false);
		void start(bool preventFreezing = false);
		void connect(uint8_t,uint8_t, bool preventFreezing = false);
		void stop(bool preventFreezing = false);

	private:
		uint8_t safeCounter  = 0;
};

#endif /* GEEGROW_I2C_CLIENT_H_ */
