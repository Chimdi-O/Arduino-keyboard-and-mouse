import serial.tools.list_ports
import time
from pynput.keyboard import Key, Controller
from pynput.keyboard import Controller as keyboardController
import regex
from pynput.mouse import Button
from pynput.mouse import Controller as mouseController
keyboard = keyboardController()
mouse = mouseController()

ports = serial.tools.list_ports.comports()
serialInst = serial.Serial()

portsList = []

key_mapping = {
    'w': 'w',  
    'a': 'a',  
    's': 's',  
    'd': 'd',  
    ' ': 'space', 
}

for onePort in ports:
    portsList.append(str(onePort))git
    print(str(onePort))

val = 7

portVar = None

for x in range(0, len(portsList)):
    if portsList[x].startswith("COM" + str(val)):
        portVar = "COM" + str(val)
        print(portVar)

if portVar is None:
    print("Selected port is not available.")
    exit()

try:
    serialInst.baudrate = 2400
    serialInst.port = portVar
    serialInst.open()
except Exception as e:
    print(f"Error opening serial port: {e}")
    exit()


prev_key = None
time.sleep(1)
while True:
    if serialInst.in_waiting:
        packet = serialInst.readline()
        hardwareState = str(packet.decode('utf').strip())
       
       

        print(hardwareState)
        splitHardwareState = hardwareState.split("|")
        
        keyState , mouseVal = splitHardwareState[0].split("/")[:-1], splitHardwareState[1].split("/")
        keys = ['w','a','s','d']
      
        for i in range(len(keyState)): 
      
            if keyState[i] == '1' : 
                keyboard.press(keys[i])
            else: 
                keyboard.release(keys[i])

        mouse.move(float(mouseVal[0])*-50,float(mouseVal[1])*50)
        time.sleep(0.05)