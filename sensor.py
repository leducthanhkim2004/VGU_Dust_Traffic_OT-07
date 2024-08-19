import serial
import csv
import datetime
import time
import os
import sys
import glob
import oss2
from dotenv import load_dotenv
import RPi.GPIO as GPIO
from cloudsdk import upload_bucket


# Parameters
node_name = "default-node"  # Default node name if needed
data_buffer_time = 86400  # 24 hours in seconds

def delete_file(filepath):
    os.remove(filepath)
    print('Deleted', filepath)


# Delete old data file
# Initialize GPIO and serial port detection

# Setup serial port
ser = serial.Serial(
    port='/dev/ttyACM0',\
    baudrate=9600,\
    parity=serial.PARITY_NONE,\
    stopbits=serial.STOPBITS_ONE,\
    bytesize=serial.EIGHTBITS,\
    timeout=0\
)

print("connected to: " + ser.portstr)

# Setup data logging
epoch_time = int(round(time.time())) + 25200
folder_name = '/home/leducthanhkim/Raw_data'
data_filename = f'{folder_name}/data_{datetime.datetime.now().strftime("%Y-%m-%d")}.csv'

# Create the raw data folder if it doesn't exist
try:
    os.mkdir(folder_name)
    print("successful")
except OSError as error:
    print(error)

struct = ["Timestamp", "Temperature", "Humidity", "Pressure", "PM1.0", "PM2.5", "PM10"]

# Main data logging loop

while True:
    epoch_time = int(round(time.time())) + 25200  # offset for GMT+7
    # Read data from serial
    line = ser.readline()
    # Create new data file if file does not exist
    try:
        with open(data_filename, 'r', newline=''):
            pass
    except FileNotFoundError:
        with open(data_filename, 'w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(struct)

    # Read serial data and save to log file
    if len(line) > 0:
        print("line:",line)
        data = line.decode('UTF-8').rstrip().split(',')
        print("data:", data)
        with open(data_filename, 'a', newline='') as file:
             writer = csv.writer(file)
             writer.writerow(data)
       

    # Upload data file and delete old data file at the end of a day
    if (epoch_time) % 86400 == 0:
        upload_bucket('node-' + node_name, data_filename)
        # Delete old data file
        delete_file(data_filename)

