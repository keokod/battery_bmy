from machine import Pin
import time
led = Pin(16, mode=Pin.OUT) # la broche numéro 21 est la gpio 16
while True:
 led.toggle()
 time.sleep(1)
 print("clign")
