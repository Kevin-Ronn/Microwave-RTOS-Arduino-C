# Microwave_Arduino-C

Av: Kevin Rönn


Tasks:

Heater Task:
Controls the power levels (800W or 400W).
Activates or deactivates heating based on the cooking program.
Sends messages: "Heater started" or "Heater stopped".

Lamp Task:
Turns the lamp on when the microwave is running or the door is open.
Sends messages: "Light on" and "Light off".

Motor Task:
Rotates the plate at 30 degrees per second.
Provides additional rotations for specific angles (90°, 360°, etc.).
Sends messages like "Motor round 30 degrees".

Door Task:
Monitors the door sensor (0 = open, 1 = closed).
Sends messages: "Door open" and "Door closed".
Ensures the microwave doesn’t run if the door is open.

Controller Task:
Supervises the overall program flow. (defrosting meat, defrosting vegetables, general heating).
Coordinates heater power, lamp, and motor activity.


Tasks:

Door Task: Continuously monitors the door state using a digital input (pin 2).

Lamp Task: Toggles the lamp based on the heater state and door status.

Heater Task: Controls the heater power and provides status messages.

Motor Task: Simulates plate rotation with messages every second.
Controller Task: Manages pre-programmed setups.

setups:

Defrosting Meat: Runs the heater at 800W for 5 minutes.

Defrosting Vegetables: Runs the heater at 400W for 1 minute.

General Heating: Runs the heater at 800W for 30 seconds.








