#!/bin/bash

# Get current directory
current_dir=$(pwd)

# Check if current dir is the project directory
if [[ "$current_dir" != "/home/pi/RPi5-pcb" ]]; then
    cd RPi5-pcb || {
        echo "Directory 'RPi5-pcb' not found." >&2
        exit 1
    }
    echo "Changed directory to RPi5-pcb"
else
    echo "RPi5-pcb is the current directory"
fi

# Start camera stream
nohup rpicam-vid --width 640 --height 640 --framerate 25 --codec mjpeg -t 0 --inline --listen -o tcp://0.0.0.0:8080 &

# Run defect detection
python main.py --model=./models/best.onnx &