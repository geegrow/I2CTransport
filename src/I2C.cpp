/*
 * Title: A I2C library using the hardware TWI interface of a Atmega32u4
 * Created: 03.11.2014 13:20:06
 * Author: Benjamin Frank
 */ 
#include <util/twi.h>
#include "I2C.h"

I2C::I2C() {
	/* do nothing */
}

//#define DEBUG_I2C
//#define DEBUG_I2C_FREEZING
//#define DEBUG_I2C_ERRORS

/*
 * Initialization of the I2C bus
 */
void I2C::begin() {
	PORTD &= ~(1 << 0); //Port D0 SCL
	PORTD &= ~(1 << 1); //Port D1 SDA
	setClock(TWI_FREQ); //TWBR = ((( F_CPU / TWI_FREQ ) - 16) / 2); 
	TWSR = 0; 
	TWCR = ( 1 << TWEN ); // enable the i2c bus f
}

void I2C::setClock(uint32_t frequency) {
	TWBR = ((F_CPU / frequency) - 16) / 2;
}

/*
 * Sends the start condition
 * adr: address of the hardware
 * w: read or write flag
 */
void I2C::connect(uint8_t adr, uint8_t w, bool preventFreezing) {
	#ifdef DEBUG_I2C
		Serial.print("I2C::connect, preventFreezing=");
		Serial.println(preventFreezing ? "yes" : "no");
	#endif

	start(preventFreezing);
	sendAddress(adr, w, preventFreezing);
}

/*
 * Sends the start condition
 */
void I2C::start(bool preventFreezing) {
	#ifdef DEBUG_I2C
		Serial.print("I2C::start, preventFreezing=");
		Serial.println(preventFreezing ? "yes" : "no");
	#endif

	uint8_t twstatus;
	// send START condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	
	// wait until transmission completed
	if (preventFreezing == true) {
		this->safeCounter = 0;

		// @TODO Throw some error code in case if I2C transmission is critical for user
		while (!(TWCR & (1<<TWINT)) && this->safeCounter < 255) {
			#ifdef DEBUG_I2C_FREEZING
				Serial.print("*");
			#endif

			this->safeCounter++;
		}
	} else {
		while (!(TWCR & (1<<TWINT)));
	}
	
	twstatus = TW_STATUS & 0xF8;

	if ((twstatus != TW_START) && (twstatus != TW_REP_START)){
		#ifdef DEBUG_I2C_ERRORS
			Serial.print("\n   |Error: Start -> [");
		    Serial.print(TWSR & 0xF8, HEX);
		    Serial.println("]");
		#endif
	}
}

/*
 * 
 * address: address of the hardware
 * w: read or write flag
 */
void I2C::sendAddress(uint8_t address, uint8_t w, bool preventFreezing) {
	#ifdef DEBUG_I2C
		Serial.print("I2C::sendAddress, preventFreezing=");
		Serial.println(preventFreezing ? "yes" : "no");
	#endif

	uint8_t   twstatus;
	TWDR = (address<<1) | w ;
	TWCR = (1 << TWINT) | (1<<TWEN);
	
	if (preventFreezing == true) {
		this->safeCounter = 0;

		// @TODO Throw some error code in case if I2C transmission is critical for user
		while (!(TWCR & (1 << TWINT)) && this->safeCounter < 255) {
			#ifdef DEBUG_I2C_FREEZING
				Serial.print("*");
			#endif

			this->safeCounter++;
		}
	} else {
		while (!(TWCR & (1 << TWINT)));
	}
	
	twstatus = TW_STATUS & 0xF8;
	
	if ( (twstatus != TW_MT_SLA_ACK) && (twstatus != TW_MR_SLA_ACK) ) {
		#ifdef DEBUG_I2C_ERRORS
			Serial.print("\n   |Error: ADRESS -> [");
		    Serial.print(TWSR & 0xF8, HEX);
		    Serial.println("]");
		#endif
	}
}

/*
 * sends the stop condition
 */
void I2C::stop(bool preventFreezing) {
	#ifdef DEBUG_I2C
		Serial.print("I2C::stop, preventFreezing=");
		Serial.println(preventFreezing ? "yes" : "no");
	#endif

	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
//	while(TWCR & (1 << TWSTO)) {
//		Serial.println('$');
//	};
	if (preventFreezing == true) {
		#ifdef DEBUG_I2C_FREEZING
			Serial.print("*");
		#endif

		this->safeCounter = 0;
		// @TODO Throw some error code in case if I2C transmission is critical for user
		while ((TWCR & (1 << TWSTO)) && this->safeCounter < 255) {
			this->safeCounter++;
		}
	} else {
		while (TWCR & (1 << TWSTO));
	}
}

/*
 * sends one byte to the I2C hardware
 * data: byte to send
 */
size_t I2C::send(uint8_t data, bool preventFreezing) {
	#ifdef DEBUG_I2C
		Serial.print("I2C::send, preventFreezing=");
		Serial.println(preventFreezing ? "yes" : "no");
	#endif

	uint8_t   twstatus;
	// send data to the previously addressed device
	TWDR = data;
	TWCR = (1 << TWINT) | (1<<TWEN);
	
	// wait until transmission completed
	if (preventFreezing == true) {
		#ifdef DEBUG_I2C_FREEZING
			Serial.print("*");
		#endif

		this->safeCounter = 0;

		// @TODO Throw some error code in case if I2C transmission is critical for user
		while (!(TWCR & (1 << TWINT)) && this->safeCounter < 255) {
			this->safeCounter++;
		}
	} else {
		while (!(TWCR & (1 << TWINT)));
	}

	twstatus = TW_STATUS & 0xF8;

	if( twstatus != TW_MT_DATA_ACK){
		#ifdef DEBUG_I2C_ERRORS
			Serial.print("\n   |Error: Data -> [");
		    Serial.print(TWSR & 0xF8, HEX);
		    Serial.println("]");
		#endif

		return 0;
	} else {
		return 1;
	}
}

/*
 * receive one byte of the I2C hardware, followed by a stop condition
 */
int8_t I2C::read() {
	TWCR = (1 << TWINT) | (1 << TWEN);
	while(!(TWCR & (1 << TWINT)));
	return TWDR;
}

/*
 * receive one byte of the I2C hardware, request more data from hardware
 */
int8_t I2C::readAck() {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1<<TWEA);
	while(!(TWCR & (1 << TWINT)));
	return TWDR;
}
