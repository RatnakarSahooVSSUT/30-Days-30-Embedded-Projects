from machine import Pin, I2C, PWM
import dht
import ssd1306
import time


dht_sensor = dht.DHT22(Pin(15))

led = Pin(14, Pin.OUT)
buzzer = PWM(Pin(13))
buzzer.duty_u16(0)

i2c = I2C(0, scl=Pin(5), sda=Pin(4))
oled = ssd1306.SSD1306_I2C(128, 64, i2c)

def beep():
    buzzer.freq(1500)
    buzzer.duty_u16(30000)
    time.sleep(0.2)
    buzzer.duty_u16(0)
    time.sleep(0.2)

while True:

    # Read sensor
    dht_sensor.measure()
    temp = dht_sensor.temperature()
    hum = dht_sensor.humidity()

    # Clear OLED
    oled.fill(0)

    # Display Title
    oled.text("Env Monitor", 10, 0)

    # Display Values
    oled.text("Temp: {} C".format(temp), 0, 20)
    oled.text("Hum : {} %".format(hum), 0, 35)

    if temp > 35:
        status = "HOT ALERT"
        led.on()

        beep()

    elif temp > 30:
        status = "WARM"
        led.off()
        buzzer.duty_u16(0)

    else:
        status = "NORMAL"
        led.off()
        buzzer.duty_u16(0)

    # Show status
    oled.text(status, 0, 50)

    # Update OLED
    oled.show()

    time.sleep(2)