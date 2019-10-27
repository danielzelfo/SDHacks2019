from flask import Flask, jsonify, request, redirect, render_template
import json
import os

app = Flask(__name__)


my_dir = os.path.dirname(__file__)

with open(os.path.join(my_dir, '/home/danielzelfo/mysite/data.json'), 'r') as json_file:
	data = json.load(json_file)

@app.route('/')
def homePage():
    ip_address = request.environ['REMOTE_ADDR']
    if ip_address in data["names"]:
        deviceName = data["devices"][ip_address]
        userName = data["names"][ip_address]
        brightness = data["sensors"][deviceName]["light"]
        return render_template("live.html", user=userName, device=deviceName, br=brightness);
    return render_template("index.html");


@app.route('/live')
def livePage():
    global userName, deviceName
    ip_address = request.environ['REMOTE_ADDR']
    if not ip_address in data["names"]:
        return render_template("index.html");

    userName = data["names"][ip_address]
    deviceName = data["devices"][ip_address]
    brightness = data["sensors"][deviceName]["light"]
    return render_template("live.html", user=userName, device=deviceName, br=brightness);

@app.route('/live', methods=['POST'])
def signUp():
    global userName, deviceName
    ip_address = request.environ['REMOTE_ADDR']
    userName = request.form["name"]
    deviceName = request.form["device"]
    brightness = data["sensors"][deviceName]["light"]

    data["names"][ip_address] = userName
    data["devices"][ip_address] = deviceName

    with open('/home/danielzelfo/mysite/data.json', 'w') as outfile:
        json.dump(data, outfile)

    return render_template("live.html", user=userName, device=deviceName, br=brightness);

@app.route('/sensor/info')
def sensorInfo():
	global db
	return jsonify(db)

@app.route('/sensor', methods=['POST'])
def create_task():
    global db
    db = request.json

    sensor = request.json["sensor"]
    value = request.json["value"]
    device = request.json["device"]


    data["sensors"] = {}
    data["sensors"][device] = {}
    data["sensors"][device][sensor] = value

    with open('/home/danielzelfo/mysite/data.json', 'w') as outfile:
        json.dump(data, outfile)

    return jsonify(request.json), 201

