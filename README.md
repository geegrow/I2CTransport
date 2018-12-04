# I2CTransport
Often there is a problem to use I2C in timer interrupts. The standart TwoWire library can't do this at all.
This library solves the problem and allows you to choose what you want: TwoWire or hardware I2C library, which 
is able to work in interrupts.
Moreover, it allows you to get access to I2C from anywhere of your code, like you do with standart arduino 
Wire library.

We also add "preventFreezing" parameter to every "send" functions, because some peripherial devices can 
freeze your system from time to time.  

--------------------------------------------------------------------
  
We like working for you, and create useful products and programs that save developers' time. 
We hope you will also support us. Please visit our store www.geegrow.ru ;-)
Thank you!
