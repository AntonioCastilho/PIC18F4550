
# <h1 align="center"> NTC Thermistor and PIC18F4550

## This program uses an NTC thermistor to obtain the temperature.

It is for automotive application in liquid environment, normally for engine cooling system control.
The Beta Formula was used to calculate the temperature, from a known temperature measurement and its resistance, corrected with the Beta coefficient.
There is a little explanation in the program description.

Thanks to Iguaçu Componentes Eletrônicos (www.iguacu.com.br), for the information about the characteristics of the NTC thermistor.


 This is a demo project about the NTC thermistor. I used a sensor that is commonly used in automotive engine cooling systems to report its temperature.
To acquire the signal I mounted a small voltage divider with a resistor of 10k in series with NTC, and applied 5V to then read the result in the analog channel AN0 of the ADC module of the PIC18F4550.
With this value read, the temperature value can be obtained by applying the Beta Formula.

![Setup NTC Thermistor](https://github.com/AntonioCastilho/PIC18F4550/blob/ECTsensor.X/Thermistor_PIC.jpg?raw=true)
