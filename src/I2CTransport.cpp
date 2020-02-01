#include "I2CTransport.h"

// How to call: I2CTransport::setClient(new I2C());
void I2CTransport::setClient(I2C *client) {
    me().I2C_Client = client;
}

// How to call: I2CTransport::setClient(&Wire);
void I2CTransport::setClient(TwoWire *client) {
    me().TwoWire_Client = client;
}

void I2CTransport::begin() {
    if (me().I2C_Client) {
        me().I2C_Client->begin();
    } else {
        me().TwoWire_Client->begin();
    }
}

void I2CTransport::setClock(uint32_t frequency) {
    if (me().I2C_Client) {
        me().I2C_Client->setClock(frequency);
    } else {
        me().TwoWire_Client->setClock(frequency);
    }
}

uint8_t I2CTransport::writeBits(
    uint8_t deviceAddress,
    uint8_t registerAddress,
    uint8_t byte,
    bool preventFreezing
) {
    uint8_t data = readByte(deviceAddress, registerAddress);
    data |= byte;
    return writeByte(deviceAddress, registerAddress, data, preventFreezing);
}

/**
 * Send single byte to deviceAddress.registerAddress using I2C
 *
 * @param deviceAddress - I2C address of target device
 * @param registerAddress - register address
 * @param data - transmitted data (1 byte)
 * @return result of transmittion:
 * 	0 - success
 * 	1 - data too long to fit in transmit buffer
 * 	2 - received NACK on transmit of address
 * 	3 - received NACK on transmit of data
 * 	4 - other error
 */
uint8_t I2CTransport::writeByte(
    uint8_t deviceAddress,
    uint8_t registerAddress,
    uint8_t data,
    bool preventFreezing
) {
    if (me().I2C_Client) {
        me().I2C_Client->connect(deviceAddress, I2C_WRITE, preventFreezing);
        me().I2C_Client->send(registerAddress, preventFreezing);
        me().I2C_Client->send(data, preventFreezing);
        me().I2C_Client->stop(preventFreezing);

        // @TODO: fix it. I2C_Client must return real result code
        // «0» – success, «1» – data too long fo buffer, «2» – getting NACK-message while address sending,
        // «3» – getting NACK-message while data sending, «4» – other error.
        return 0;
    } else {
        // Initialize the Tx buffer
        me().TwoWire_Client->beginTransmission(deviceAddress);
        // Put slave register address in Tx buffer
        me().TwoWire_Client->write(registerAddress);
        // Put data in Tx buffer
        me().TwoWire_Client->write(data);
        // Send the Tx buffer
        return me().TwoWire_Client->endTransmission();
    }
}

/**
 * Send package of bytes to deviceAddress.registerAddress using I2C
 *
 * @param deviceAddress - I2C address of target device
 * @param registerAddress - register address
 * @param length - number of data bytes
 * @param dataArray - pointer to array of data to be sent
 * @return result of transmittion:
 * 	0 - success
 * 	1 - data too long to fit in transmit buffer
 * 	2 - received NACK on transmit of address
 * 	3 - received NACK on transmit of data
 * 	4 - other error
 */
uint8_t I2CTransport::writeBytes(
    uint8_t deviceAddress,
    uint8_t registerAddress,
    uint8_t length,
    const uint8_t * dataArray,
    bool preventFreezing
) {
    if (me().I2C_Client) {
        me().I2C_Client->connect(deviceAddress, I2C_WRITE, preventFreezing);

        me().I2C_Client->send(registerAddress, preventFreezing);

        for (uint8_t i = 0; i < length; i++) {
            me().I2C_Client->send(dataArray[i], preventFreezing);
        }

        me().I2C_Client->stop(preventFreezing);

        // @TODO: fix it. I2C_Client must return real result code
        // «0» – success, «1» – data too long fo buffer, «2» – getting NACK-message while address sending,
        // «3» – getting NACK-message while data sending, «4» – other error.
        return 0;
    } else {
        // Initialize the Tx buffer
        me().TwoWire_Client->beginTransmission(deviceAddress);

        // Put slave register address in Tx buffer
        me().TwoWire_Client->write(registerAddress);

        me().TwoWire_Client->write(dataArray, length);

        // Send the Tx buffer
        return me().TwoWire_Client->endTransmission();
    }
}

/**
 * Send package of bytes to deviceAddress using I2C
 *
 * @param deviceAddress - I2C address of target device
 * @param length - number of data bytes
 * @param dataArray - pointer to array of data to be sent
 * @return result of transmittion:
 * 	0 - success
 * 	1 - data too long to fit in transmit buffer
 * 	2 - received NACK on transmit of address
 * 	3 - received NACK on transmit of data
 * 	4 - other error
 */
uint8_t I2CTransport::writeBytes(
    uint8_t deviceAddress,
    uint8_t length,
    const uint8_t * dataArray,
    bool preventFreezing
) {
    if (me().I2C_Client) {
        me().I2C_Client->connect(deviceAddress, I2C_WRITE, preventFreezing);

        for (uint8_t i = 0; i < length; i++) {
            me().I2C_Client->send(dataArray[i], preventFreezing);
        }

        me().I2C_Client->stop(preventFreezing);

        // @TODO: fix it. I2C_Client must return real result code
        // «0» – success, «1» – data too long fo buffer, «2» – getting NACK-message while address sending,
        // «3» – getting NACK-message while data sending, «4» – other error.
        return 0;
    } else {
        // Initialize the Tx buffer
        me().TwoWire_Client->beginTransmission(deviceAddress);

        me().TwoWire_Client->write(dataArray, length);

        // Send the Tx buffer
        return me().TwoWire_Client->endTransmission();
    }
}

/**
 * Read single byte from deviceAddress.registerAddress using I2C
 *
 * @param deviceAddress - I2C address of target device
 * @param registerAddress - register address
 * @param data - transmitted data (1 byte)
 * @return data - received data (1 byte)
 */
uint8_t I2CTransport::readByte(
    uint8_t deviceAddress,
    uint8_t registerAddress
) {
    // Contained for register data storing
    uint8_t data;

    if (me().I2C_Client) {
        me().I2C_Client->connect(deviceAddress, I2C_WRITE);
        me().I2C_Client->send(registerAddress);
        me().I2C_Client->stop();
        me().I2C_Client->connect(deviceAddress, I2C_READ);
        data = me().I2C_Client->read();
        me().I2C_Client->stop();
    } else {
        // Initialize the Tx buffer
        me().TwoWire_Client->beginTransmission(deviceAddress);
        // Put slave register address in Tx buffer
        me().TwoWire_Client->write(registerAddress);
        // Send the Tx buffer, but send a restart to keep connection alive
        me().TwoWire_Client->endTransmission(false);
        // Read one byte from slave register address
        me().TwoWire_Client->requestFrom(deviceAddress, (uint8_t) 1);
        // Fill Rx buffer with result
        data = me().TwoWire_Client->read();
    }

    // Return data read from slave register
    return data;
}

/**
 * Read 1 or more bytes from deviceAddress.registerAddress using I2C
 *
 * @param deviceAddress - I2C address of target device
 * @param registerAddress - register address
 * @param length - number of bytes for reading
 * @param *dest - container pointer
 * @return number of really received bytes
 */
uint8_t I2CTransport::readBytes(
    uint8_t deviceAddress,
    uint8_t registerAddress,
    uint8_t length,
    uint8_t *dest
) {

    if (me().I2C_Client) {
        uint8_t i = 0;
        me().I2C_Client->connect(deviceAddress, I2C_WRITE);
        me().I2C_Client->send(registerAddress);
        me().I2C_Client->stop();
        me().I2C_Client->connect(deviceAddress, I2C_READ);
        for (i; i < length - 1; i++) {
            dest[i] = me().I2C_Client->readAck();
        }
        dest[i] = me().I2C_Client->read();
        me().I2C_Client->stop();
        return i;
    } else {
        // Initialize the Tx buffer
        me().TwoWire_Client->beginTransmission(deviceAddress);
        // Put slave register address in Tx buffer
        me().TwoWire_Client->write(registerAddress);
        // Send the Tx buffer, but send a restart to keep connection alive
        me().TwoWire_Client->endTransmission(false);

        uint8_t i = 0;
        // Read bytes from slave register address
        me().TwoWire_Client->requestFrom(deviceAddress, length);

        while (me().TwoWire_Client->available()) {
            // Put read results in the Rx buffer
            dest[i++] = me().TwoWire_Client->read();
        }

        return i;
    }
}
