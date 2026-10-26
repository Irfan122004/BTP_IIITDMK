#define steppin 3
#define dirpin 5
const int sensor = 2;

// Desired RPM
const int desiredRPM = 20;
float rollerRadius = 0.04;
float x = 0; // temporary variable
int stepsperrevolution = 1600;

// PI Controller constants
float Kp = 3.3;   // Proportional gain
float Ki = 0.1;   // Integral gain

// Variables for PI controller
float errorSum = 0;
unsigned long lastUpdateTime = 0;

// RPM calculation
volatile unsigned long prevTime = 0;
volatile unsigned long timeDiff = 0;
volatile bool rpmUpdated = false;
unsigned int rpm = 1;  // Start with 1 to avoid zero delay

// Sensor interrupt to measure RPM
void detectWave() {
  unsigned long currentTime = micros();
  timeDiff = currentTime - prevTime;
  prevTime = currentTime;
  int temp = 0;
  if (timeDiff > 100000) { // Filter very fast false triggers
    rpm = (60.0 * 1000000.0) / timeDiff;
    rpmUpdated = true;
    temp = rpm;
  }
  if (rpm > 1.5*desiredRPM) rpm = desiredRPM;
}

void setup() {
  Serial.begin(115200);
  pinMode(sensor, INPUT);
  pinMode(steppin, OUTPUT);
  pinMode(dirpin, OUTPUT);
  digitalWrite(dirpin, LOW);  // Set motor direction

  attachInterrupt(digitalPinToInterrupt(sensor), detectWave, FALLING);
}

void loop() {
  int delayTime = delayCalculator(rpm, stepsperrevolution);

  if (rpmUpdated) {
    unsigned long currentMillis = millis();
    float actual_beltSpeed = 2 * 3.14 * rollerRadius * rpm;
    float required_belt_speed = 2 * 3.14 * rollerRadius * desiredRPM;

    Serial.print(currentMillis); Serial.print(",");
    Serial.print(rpm); Serial.print(",");
    Serial.print(desiredRPM); Serial.print(",");
    Serial.print(actual_beltSpeed); Serial.print(",");
    Serial.println(required_belt_speed);

    rpmUpdated = false;
  }

  // Generate step signal
  digitalWrite(steppin, HIGH);
  delayMicroseconds(delayTime / 2);
  digitalWrite(steppin, LOW);
  delayMicroseconds(delayTime / 2);
}

//delay calculator
int delayCalculator(float currentRPM, int stepsPerRevolution) {
  if (currentRPM == 0) currentRPM = 1;

  float error = desiredRPM - currentRPM;

  float proportionalTerm = Kp * error;

  // backward euler method 1 / (1 - z^(-1))
// adding the previous error to the presnet error for integration part
  errorSum = x + error;
  x = error;
  float integralTerm = Ki * errorSum;

  float controlOutput = proportionalTerm + integralTerm;

  float desiredFrequency = desiredRPM * stepsPerRevolution / 60.0;
  float adjustedFrequency = desiredFrequency + controlOutput;

  // avoiding invalid condition
  if (adjustedFrequency <= 0) adjustedFrequency = 0.1;

  int adjustedTimePeriod = 1000000 / adjustedFrequency;

  // restricting the delay time to 37000 microseconds (1 RPM)
  //if (adjustedTimePeriod > 37000) adjustedTimePeriod = 37000;
  if (adjustedTimePeriod > 500000) adjustedTimePeriod = 500000;

  return adjustedTimePeriod;
}
