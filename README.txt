Often there is the problem to use I2C in timer interrupts. The standart TwoWire library can't do this at all.
This library solves the problem and allows you to chouse what you want: TwoWire, or hardware I2C library which able to work in interrupts.
Moreover, it allows you to get access to I2C from anywhere of your code, like you do with standart arduino Wire library.

We also add "preventFreezing" paramter to evry "send" functions, because some peripherial devices can 
freeze your system from time to time.  

Please, for more information and recipes please visit github page https://github.com/geegrow/I2CTransport

--------------------------------------------------------------------
  
We like to work for you, and create useful products and programs that save developers time. 
We hope you will also support us. Please visit our store www.geegrow.ru ;-)
Thank you!