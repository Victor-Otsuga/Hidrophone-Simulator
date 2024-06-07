# Hidrophone Simulator
>Status: Finished✅


<img src="https://github.com/Victor-Otsuga/Hidrophone-Simulator/assets/105857027/ea073684-a14d-4cf3-aff1-1131f4783f40">


### The wires represents:
+ 🔴 the passage of 5V power.
+ 🟢 the direct power flow from the sensor.
+ ⚫ the passage of energy to ground.

### How does it work
The esp connects to wifi and waits for a trigger to make a MQTT post passing thru a Node-RED flow and then posting on the project's API indicating the location, its function is to report movement and based on this information the project's backend in python generates a map of reports, when the project is running a sound sensor (Hydrophone) will be attached instead of a motion sensor and a GPS to inform the location in real time

### Node-RED flow
<img src="https://github.com/Victor-Otsuga/Hidrophone-Simulator/assets/105857027/5187cd04-0c85-4f44-abb6-238167c7be98">


### Reports Map
<img src="https://github.com/Victor-Otsuga/Hidrophone-Simulator/assets/105857027/0084c17a-c2d9-406d-8b25-bfddb392996a">


### How to run the application:
1) Click: https://www.tinkercad.com/things/fMj0DPhAl9r
2) Click on "Start Simulation"
3) Wait until ESP32 connect to internet
4) Click on pir-motion-sensor to ping a trigger
5) Done the MQTT post has been done
