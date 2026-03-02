from flask import Flask, Response, render_template_string
from picamera2 import Picamera2
import cv2
import RPi.GPIO as GPIO
import time
from datetime import datetime
import os
import threading
import smtplib
from email.message import EmailMessage

app = Flask(__name__)

SENDER_EMAIL = "@gmail.com"
APP_PASSWORD = ""
RECEIVER_EMAIL = "@gmail.com"


GPIO.setwarnings(False)
SENSOR_PIN = 17
GPIO.setmode(GPIO.BCM)
GPIO.setup(SENSOR_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)

picam2 = Picamera2()
config = picam2.create_video_configuration(
    main={"size": (640, 480)},
    controls={"FrameRate": 30}
)
picam2.configure(config)
picam2.start()

stable_detected = False
detection_start = None
snapshot_taken = False

if not os.path.exists("snapshots"):
    os.makedirs("snapshots")

def send_email_alert(image_path):
    try:
        msg = EmailMessage()
        msg["Subject"] = "?? Security Alert - Object Detected"
        msg["From"] = SENDER_EMAIL
        msg["To"] = RECEIVER_EMAIL
        msg.set_content("An object was detected by your IR Security System.")

        with open(image_path, "rb") as f:
            img_data = f.read()
            msg.add_attachment(img_data,
                               maintype="image",
                               subtype="jpeg",
                               filename=os.path.basename(image_path))

        with smtplib.SMTP_SSL("smtp.gmail.com", 465) as smtp:
            smtp.login(SENDER_EMAIL, APP_PASSWORD)
            smtp.send_message(msg)

        print("Email Alert Sent!")

    except Exception as e:
        print("Email Failed:", e)

def monitor_ir():
    global stable_detected, detection_start, snapshot_taken

    while True:
        sensor_state = GPIO.input(SENSOR_PIN)

        if sensor_state == 0:
            if detection_start is None:
                detection_start = time.time()

            elif (time.time() - detection_start >= 2):
                stable_detected = True

                if not snapshot_taken:
                    frame = picam2.capture_array()
                    frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)

                    filename = "snapshots/" + datetime.now().strftime("%Y%m%d_%H%M%S") + ".jpg"
                    cv2.imwrite(filename, frame)

                    print("Snapshot Saved:", filename)

                    
                    threading.Thread(
                        target=send_email_alert,
                        args=(filename,),
                        daemon=True
                    ).start()

                    snapshot_taken = True

        else:
            detection_start = None
            stable_detected = False
            snapshot_taken = False

        time.sleep(0.05)

threading.Thread(target=monitor_ir, daemon=True).start()


def generate_frames():
    while True:
        frame = picam2.capture_array()
        frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)

        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        cv2.putText(frame, timestamp, (10, 460),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    0.6, (255, 255, 255), 2)

        if stable_detected:
            text = "OBJECT DETECTED"
            color = (0, 0, 255)
        else:
            text = "NO OBJECT"
            color = (0, 255, 0)

        cv2.putText(frame, text, (20, 40),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    1, color, 2)

        ret, buffer = cv2.imencode('.jpg', frame)
        frame = buffer.tobytes()

        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

@app.route('/')
def index():
    return render_template_string("""
        <html>
        <head>
            <title>Smart Security System</title>
        </head>
        <body style="text-align:center;">
            <h2>IR Triggered Snapshot + Email Alert</h2>
            <img src="/video_feed" width="640">
        </body>
        </html>
    """)

@app.route('/video_feed')
def video_feed():
    return Response(generate_frames(),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, threaded=True)