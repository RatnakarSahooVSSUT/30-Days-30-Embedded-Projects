from flask import Flask, Response, render_template_string
from picamera2 import Picamera2
import cv2

app = Flask(__name__)

picam2 = Picamera2()
config = picam2.create_preview_configuration(
    main={"size": (320, 240)},
    controls={"FrameRate": 15.0}
)
picam2.configure(config)
picam2.start()

def generate_frames():
    while True:
        frame = picam2.capture_array()
        frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)

        ret, buffer = cv2.imencode('.jpg', frame)
        frame = buffer.tobytes()

        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

HTML_PAGE = """
<!DOCTYPE html>
<html>
<head>
    <title>Camera</title>
    <style>
        body {
            background-color: black;
            text-align: center;
        }
        img {
            width: 900px;
            border-radius: 10px;
        }
    </style>
</head>
<body>
    <h2 style="color:white;">Live Stream</h2>
    <img src="/video">
</body>
</html>
"""

@app.route('/')
def index():
    return render_template_string(HTML_PAGE)

@app.route('/video')
def video():
    return Response(generate_frames(),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000)