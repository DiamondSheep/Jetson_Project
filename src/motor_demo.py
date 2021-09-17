import RPi.GPIO as GPIO
import time

read_pin = [21, 22, 23, 24]

def blink(channel):
    print("read.")

def main():
    GPIO.setmode(GPIO.BOARD)
    for pin in read_pin:
        GPIO.setup(pin, GPIO.IN)

    GPIO.add_event_detect(pin[1], GPIO.FALLING, callback=blink, bouncetime=10)

    GPIO.cleanup()
    
if __name__ == "__main__":
    main()