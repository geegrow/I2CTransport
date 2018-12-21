#ifndef GEEGROW_I2C_TRANSPORT_H
#define GEEGROW_I2C_TRANSPORT_H

#include <Arduino.h>
#include "Wire.h"
#include "I2C.h"

class I2CTransport {

	public:
		static I2CTransport& me() {
			static I2CTransport  instance;
			return instance;
		}
	    // Public method declarations

	    static void setClient(I2C*);
	    static void setClient(TwoWire*);

		static void begin();
		static void setClock(uint32_t frequency);
		static uint8_t writeBits(uint8_t, uint8_t, uint8_t, bool preventFreezing = false);
		static uint8_t writeByte(uint8_t, uint8_t, uint8_t, bool preventFreezing = false);
		static uint8_t writeBytes(uint8_t, uint8_t, uint8_t, const uint8_t *, bool preventFreezing = false);
		static uint8_t readByte(uint8_t, uint8_t);
		static uint8_t readBytes(uint8_t, uint8_t, uint8_t, uint8_t *);

	private:
		I2CTransport() {};
		~I2CTransport() {};
		I2CTransport(const I2CTransport&);
		I2CTransport& operator=(I2CTransport&);


		I2C *I2C_Client;
		TwoWire *TwoWire_Client;
};

#endif // GEEGROW_I2C_TRANSPORT_H
