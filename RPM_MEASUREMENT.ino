const int irSensorPin = 2;  // IR sensor connected to digital pin 2
volatile unsigned long prevTime = 0;
volatile unsigned long timeDiff = 0;
volatile float rpm = 0.0;

void detectWave() {
    unsigned long currentTime = micros();  // Get current time in microseconds
    timeDiff = currentTime - prevTime;     // Calculate time difference
    prevTime = currentTime;                // Update previous time
    
    if (timeDiff > 0) {
        rpm = (60.0 * 1000000.0) / timeDiff;  // Convert time difference to RPM
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(irSensorPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(irSensorPin), detectWave, FALLING); // Trigger on falling edge
}

void loop() {
    if (timeDiff > 0) {  // Check if a valid measurement is available
        Serial.print("Time difference: ");
        Serial.print(timeDiff);
        Serial.println(" microseconds");
        Serial.print("RPM: ");
        Serial.println(rpm);
        timeDiff = 0;  // Reset to avoid duplicate prints
    }
}
