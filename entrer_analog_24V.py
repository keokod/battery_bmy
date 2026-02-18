from machine import ADC
import time

# GP28 correspond à ADC2
adc = ADC(28)

while True:
    valeur = adc.read_u16()   # Lecture sur 16 bits (0 à 65535)
    #tension = valeur * 3.3 / 65535  # Conversion en volts 
    print("Valeur brute:", valeur)
    #print("Tension: {:.2f} V".format(tension))
    print("------------------------")
    
    time.sleep(0.5)

#poteniometre régler à 90khoms en entrer en série avec 12Khom qui va à la masse
#4.2V => 10000
#12.6 =>27000
#22V =>46000
#25.2=> 50000
