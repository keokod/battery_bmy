from machine import Pin, Timer
from machine import ADC
import time

led = Pin(2, Pin.OUT)
tim = Timer()
def tick(timer):
    global led
    led.toggle()
    

temp_sensor = ADC(0)

while True:
    adc_voltage = temp_sensor.read_u16() * 3.3 / 65535
    print(temp_sensor.read_u16())
    #cpu_temp = 27 - (adc_voltage - 0.706)/0.001721 # Formula given in RP2040 Datasheet
    #print(cpu_temp)
    time.sleep_ms(1000)

tim.init(freq=10000, mode=Timer.PERIODIC, callback=tick)

/*
0.6V => 25° => 11800
0.61V => 26° => 12000
0.64V => 28° => 13000
0.67V => 29° => 11800

0.72V => 30° => 14000
0.78V => mon coude => 16000

0.80V => 33° => 15000

0.9V => 36° => 17000

1V => 40° => 21000
1.1V => 45° => 21000
1.3V => 50° => 21000
*/
