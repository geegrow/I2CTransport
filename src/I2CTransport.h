#ifndef GEEGROW_I2C_TRANSPORT_H
#define GEEGROW_I2C_TRANSPORT_H

#include <Arduino.h>
#include <Wire.h>
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
        static uint8_t writeBits(
            uint8_t deviceAddress,
            uint8_t registerAddress,
            uint8_t byte,
            bool preventFreezing = false
        );
        static uint8_t writeByte(
            uint8_t deviceAddress,
            uint8_t registerAddress,
            uint8_t data,
            bool preventFreezing = false
        );
        static uint8_t writeBytes(
            uint8_t deviceAddress,
            uint8_t registerAddress,
            uint8_t length,
            const uint8_t * dataArray,
            bool preventFreezing = false
        );
        static uint8_t writeBytes(
            uint8_t deviceAddress,
            uint8_t length,
            const uint8_t * dataArray,
            bool preventFreezing = false
        );
        static uint8_t readByte(
            uint8_t deviceAddress,
            uint8_t registerAddress
        );
        static uint8_t readBytes(
            uint8_t deviceAddress,
            uint8_t registerAddress,
            uint8_t length,
            uint8_t *dest
        );

    private:
        I2CTransport() {};
        ~I2CTransport() {};
        I2CTransport(const I2CTransport&);
        I2CTransport& operator=(I2CTransport&);


        I2C *I2C_Client;
        TwoWire *TwoWire_Client;
};

#endif // GEEGROW_I2C_TRANSPORT_H
