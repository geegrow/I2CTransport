# I2CTransport

Often there is a problem with using of I2C in timer interrupts. The standard
TwoWire library cannot do it at all. This library solves the problem and allows
you to choose what you want: TwoWire or hardware I2C library which is able to
work in interrupts.
Moreover, it allows you to get access to I2C from anywhere of your code, like
you do with standard Arduino Wire library.

We also add "preventFreezing" parameter to every "send" function, because some
of peripheral devices can freeze your system from time to time.

For more information you can visit https://github.com/geegrow/I2CTransport

--------------------------------------------------------------------

"___________________________________" <--   This is a place for very motivating
                                            and enthusiastic slogan!

Please visit our store https://geegrow.ru and check out for some cool stuff!



<!-- START COMPATIBILITY TABLE -->

## Compatibility

MCU                | Tested Works | Doesn't Work | Not Tested  | Notes
------------------ | :----------: | :----------: | :---------: | -----
Atmega328 @ 16MHz  |              |              |     X       |
Atmega328 @ 12MHz  |              |              |     X       |
Atmega32u4 @ 16MHz |      X       |              |             |  
ESP8266            |              |              |     X       |
Atmega2560 @ 16MHz |              |              |     X       |
ATSAM3X8E          |              |              |     X       |
ATSAM21D           |              |              |     X       |
Intel Curie @ 32MHz|              |              |     X       |
STM32F2            |              |              |     X       |

  * ATmega328 @ 16MHz : Arduino UNO
  * ATmega328 @ 12MHz : Adafruit Pro Trinket 3V
  * ATmega32u4 @ 16MHz : Arduino Leonardo, Arduino Micro, Arduino Yun, Geegrow DaVinci
  * ESP8266 :
  * ATmega2560 @ 16MHz : Arduino Mega
  * ATSAM3X8E : Arduino Due
  * ATSAM21D : Arduino Zero, M0 Pro

<!-- END COMPATIBILITY TABLE -->
