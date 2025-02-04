from datetime import datetime
from time import time, sleep
import pyrebase
import os.path
import serial
print(serial.__file__),

config = {  # firebase authentification
    "apiKey": "AIzaSyDEfkwr7Zl5WucXFluMxB8VIlngUnp7aDM",
    "authDomain": "smv-daq.firebaseapp.com",
    "databaseURL": "https://smv-daq.firebaseio.com",
    "projectId": "smv-daq",
    "storageBucket": "bucket.appspot.com"
}

firebase = pyrebase.initialize_app(config)

db = firebase.database()

# declare the dictionary to store all input data
inputs_dict = {
    'Cur': -1,
    'Vlt': -1,
    'Thr': -1,
    'Pwr': -1,
    'Spd': -1,
    'Lng': -1,
    'Lat': -1,
    'Alt': -1,
    'Tem': -1,
    'GyX': -1,
    'GyY': -1,
    'GyZ': -1,
    'AcX': -1,
    'AcY': -1,
    'AcZ': -1,
    'MaX': -1,
    'MaY': -1,
    'MaZ': -1,
    'Pit': -1,
    'Rol': -1,
    'Hea': -1,
    'Rpm': -1,
}

Trial_Number = input("Enter Trial Number \n")

# Reads in black box data to certain location
# sets file location for where the text files will be read from
save_path = 'C:\\Users\\jsand\\OneDrive\\Documents\\SMV\\DAQ\\Trials'
trialName = "Trial " + Trial_Number
fileName = trialName + ".txt"
completeName = os.path.join(save_path, fileName)

# Printing inputs to Black Box
text = open(completeName, 'r')

for position, line in enumerate(text):

    data = line.split(";")  # splits each data point into a list
    numValues = len(data) - 1  # expected number of data inputs
    timeName = data[numValues][: -1]
    print(data)

    for i in range(0, numValues, 2):
        # Since we have delimeter for both string and data, data[i] will represent the prefix and data[i+1] will be the associated data
        # e.x) Lat;314;Alt;516;Pwr;678...
        # may fail on first run, simply re-run
        inputs_dict[data[i]] = float(data[i + 1])

    # push collected data to database
    db.child(trialName).child(timeName).update({
        "gps":
        {"latitude": inputs_dict['Lat'],
         "longitude": inputs_dict['Lng']},
        "joulemeter":
        {"current": inputs_dict['Cur'],
         "power": inputs_dict['Pwr'],
         "voltage": inputs_dict['Vlt']},
        "gyroscope":
        {"GyX": inputs_dict['GyX'],
         "GyY": inputs_dict['GyY'],
         "GyZ": inputs_dict['GyZ'],
         "heading": inputs_dict['Hea'],
         "pitch": inputs_dict['Pit'],
         "roll": inputs_dict['Rol']},
        "environment":
        {"altitude": inputs_dict['Alt'],
         "temperature": inputs_dict['Tem']},
        "hall-effect":
        {"rpm": inputs_dict['Rpm'],
         "throttle": inputs_dict['Thr'],
         "speed": inputs_dict['Spd']},
        "accelerometer":
        {"acceleration x": inputs_dict['AcX'],
         "acceleration y": inputs_dict['AcY'],
         "acceleration z": inputs_dict['AcZ']},
        "magnetometer":
        {"MagX": inputs_dict['MaX'],
         "MagY": inputs_dict['MaY'],
         "MagZ": inputs_dict['MaZ']},
    })

    # Updates trial information only after successful push
    db.update(
        {"Latest Trial": trialName,
         "Latest Time": data[22],
         "Running": "True"})
