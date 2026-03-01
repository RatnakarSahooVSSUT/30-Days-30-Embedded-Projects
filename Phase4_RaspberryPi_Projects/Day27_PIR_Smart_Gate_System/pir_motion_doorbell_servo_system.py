import RPi.GPIO as GPIO
import time
from board import SCL, SDA
import busio
from PIL import Image, ImageDraw
import adafruit_ssd1306

PIR = 17
BUTTON = 23
LED = 24
BUZZER = 25
SERVO = 18

GPIO.setmode(GPIO.BCM)
GPIO.setup(PIR, GPIO.IN)
GPIO.setup(BUTTON, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(LED, GPIO.OUT)
GPIO.setup(BUZZER, GPIO.OUT)
GPIO.setup(SERVO, GPIO.OUT)

GPIO.output(BUZZER, GPIO.HIGH) 
GPIO.output(LED, GPIO.LOW)


pwm = GPIO.PWM(SERVO, 50)
pwm.start(0)

i2c = busio.I2C(SCL, SDA)
display = adafruit_ssd1306.SSD1306_I2C(128, 64, i2c)

width = display.width
height = display.height
image = Image.new("1", (width, height))
draw = ImageDraw.Draw(image)

def show(text):
    draw.rectangle((0, 0, width, height), outline=0, fill=0)
    draw.text((10, 25), text, fill=255)
    display.image(image)
    display.show()

def doorbell():
    for _ in range(3):
        GPIO.output(BUZZER, GPIO.LOW)
        time.sleep(0.2)
        GPIO.output(BUZZER, GPIO.HIGH)
        time.sleep(0.2)

def open_gate():
    pwm.ChangeDutyCycle(7) 
    time.sleep(5)
    pwm.ChangeDutyCycle(2) 
    time.sleep(1)
    pwm.ChangeDutyCycle(0)

try:
    show("System Ready")
    time.sleep(2)

    while True:
        if GPIO.input(PIR):
            show("Motion Detected!")
            GPIO.output(LED, GPIO.HIGH)
            doorbell()

            while GPIO.input(BUTTON):
                time.sleep(0.1)

            show("Gate Open")
            open_gate()

            GPIO.output(LED, GPIO.LOW)
            show("Gate Closed")
            time.sleep(2)
            show("System Ready")