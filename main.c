#include <Arduino_FreeRTOS.h>
#include <semphr.h> 

// Global variables and states
bool doorClosed = true;
int heaterPower = 0;
bool lampOn = false;
int motorAngle = 0;

// Func prototypes
void taskDoor(void *pvParameters);
void taskLamp(void *pvParameters);
void taskHeater(void *pvParameters);
void taskMotor(void *pvParameters);
void taskController(void *pvParameters);

void setup() {
  Serial.begin(9600);

  // Create tasks
  xTaskCreate(taskDoor, "Door Task", 128, NULL, 2, NULL);
  xTaskCreate(taskLamp, "Lamp Task", 128, NULL, 2, NULL);
  xTaskCreate(taskHeater, "Heater Task", 128, NULL, 2, NULL);
  xTaskCreate(taskMotor, "Motor Task", 128, NULL, 2, NULL);
  xTaskCreate(taskController, "Controller Task", 128, NULL, 1, NULL);
}

void loop() {
  
}

//Monitors door status
void taskDoor(void *pvParameters) {
  for (;;) {
    // door sensor
    if (digitalRead(2) == HIGH) { // Simulate door closed
      if (!doorClosed) {
        doorClosed = true;
        Serial.println("Door closed");
      }
    } else { // door open
      if (doorClosed) {
        doorClosed = false;
        Serial.println("Door open");
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS); // Poll every 100ms
  }
}

// Controls the lamp
void taskLamp(void *pvParameters) {
  for (;;) {
    if (doorClosed && heaterPower > 0) {
      if (!lampOn) {
        lampOn = true;
        Serial.println("Light on");
      }
    } else if (!doorClosed || heaterPower == 0) {
      if (lampOn) {
        lampOn = false;
        Serial.println("Light off");
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS); // Poll every 100ms
  }
}

// Controls the heater power
void taskHeater(void *pvParameters) {
  for (;;) {
    if (heaterPower > 0) {
      Serial.println(heaterPower == 800 ? "Heater started at 800W" : "Heater started at 400W");
    } else {
      Serial.println("Heater stopped");
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Update every 1 second
  }
}

// Rotates the plate
void taskMotor(void *pvParameters) {
  for (;;) {
    if (heaterPower > 0) {
      motorAngle = (motorAngle + 30) % 360;
      Serial.print("Motor round ");
      Serial.print(motorAngle);
      Serial.println(" degrees");
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Rotate every second
  }
}

// Manages cooking programs
void taskController(void *pvParameters) {
  for (;;) {
    // Defrosting meat (5 minutes at 800W)
    heaterPower = 800;
    vTaskDelay(300000 / portTICK_PERIOD_MS); // Run for 5 minutes
    heaterPower = 0;

    vTaskDelay(2000 / portTICK_PERIOD_MS); // Wait before next program

    // Defrosting vegetables (1 minute at 400W)
    heaterPower = 400;
    vTaskDelay(60000 / portTICK_PERIOD_MS); // Run for 1 minute
    heaterPower = 0;

    vTaskDelay(2000 / portTICK_PERIOD_MS); // Wait 

    // General heating (30 seconds)
    heaterPower = 800;
    vTaskDelay(30000 / portTICK_PERIOD_MS); // Run for 30 seconds
    heaterPower = 0;

    vTaskDelay(5000 / portTICK_PERIOD_MS); // Wait before restarting loop
  }
}
