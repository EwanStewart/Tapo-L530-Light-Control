from PyP100 import PyL530
from flask import Flask
from flask import request

bulb1 = PyL530.L530("192.168.1.233", "x", "x")
bulb2 = PyL530.L530("192.168.1.200", "x", "x")
bulb3 = PyL530.L530("192.168.1.113", "x", "x")
bulb4 = PyL530.L530("192.168.1.72", "x", "x")

bulb1.handshake()
bulb1.login()

bulb2.handshake() 
bulb2.login() 

bulb3.handshake() 
bulb3.login() 

bulb4.handshake()
bulb4.login()

app = Flask(__name__)

@app.route("/on")
def on():
    bulb1.turnOn()
    bulb2.turnOn()
    bulb3.turnOn()
    bulb4.turnOn()
    return "Bulbs On"

@app.route("/off")
def off():
    bulb1.turnOff()
    bulb2.turnOff()
    bulb3.turnOff()
    bulb4.turnOff()
    return "Bulbs Off"

@app.route("/toggle")
def state():
    bulb1.toggleState()
    bulb2.toggleState()
    bulb3.toggleState()
    bulb4.toggleState()
    return "toggle"


@app.route('/set_colour', methods=['GET'])
def set_color():
    hue = int(request.args.get('hue'))
    s = int(request.args.get('saturation'))
    bulb1.setColor(hue, s)
    bulb2.setColor(hue, s)
    bulb3.setColor(hue, s)
    bulb4.setColor(hue, s)
    return "color"
