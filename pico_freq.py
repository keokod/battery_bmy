from machine import Pin, Timer

led = Pin(2, Pin.OUT)
tim = Timer()
def tick(timer):
    global led
    led.toggle()

tim.init(freq=10000, mode=Timer.PERIODIC, callback=tick)