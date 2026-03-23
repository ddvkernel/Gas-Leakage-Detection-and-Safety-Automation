#include <SoftwareSerial.h>

// Pin connections
int mqSensor = A0;        // MQ-2 sensor connected to A0
int motorRelay = 6;       // Relay to control motor
int solenoidRelay = 7;    // Relay to control solenoid valve
int ledPin = 8;           // LED for status indication

// GSM module pins
int gsmRx = 10;           // Arduino RX (connected to GSM TX)
int gsmTx = 11;           // Arduino TX (connected to GSM RX)

SoftwareSerial gsm(gsmRx, gsmTx);  // RX, TX

// Variables
int gasValue = 0;              // Stores gas sensor value
int threshold = 350;           // Set limit after testing
unsigned long lastSmsTime = 0;
unsigned long smsDelay = 120000; // 2 minutes gap between messages

// Change to your mobile number
char phoneNumber[] = "+91XXXXXXXXXX";

void setup() {
  Serial.begin(115200);
  gsm.begin(9600);

  pinMode(mqSensor, INPUT);
  pinMode(motorRelay, OUTPUT);
  pinMode(solenoidRelay, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // Default safe state
  digitalWrite(motorRelay, HIGH);      // Motor OFF (Relay normally closed)
  digitalWrite(solenoidRelay, HIGH);   // Solenoid Open
  digitalWrite(ledPin, HIGH);          // LED ON (System normal)

  Serial.println("Gas Leakage Detection System Starting...");
  delay(2000);

  // GSM initialization
  sendAT("AT");
  delay(500);
  sendAT("AT+CMGF=1"); // Set to text mode
  delay(500);
}

void loop() {
  gasValue = analogRead(mqSensor); // Read gas sensor

  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  if (gasValue > threshold) {
    gasDetected();   // Run alarm functions
  } else {
    systemNormal();  // Stay normal
  }

  delay(1000); // Check every second
}

void gasDetected() {
  Serial.println("ALERT! Gas Leak Detected!");

  // Turn ON safety devices
  digitalWrite(motorRelay, LOW);       // Motor ON
  digitalWrite(solenoidRelay, LOW);    // Solenoid Closed
  digitalWrite(ledPin, LOW);           // LED OFF

  // Send SMS alert (only once every few minutes)
  if (millis() - lastSmsTime > smsDelay) {
    sendSMS(phoneNumber, "ALERT: Gas Leak Detected! Please Check Immediately!");
    lastSmsTime = millis();
  }
}

void systemNormal() {
  Serial.println("System Normal - No Gas Detected.");

  // Keep devices OFF / Open
  digitalWrite(motorRelay, HIGH);     // Motor OFF
  digitalWrite(solenoidRelay, HIGH);  // Solenoid Open
  digitalWrite(ledPin, HIGH);         // LED ON
}

void sendAT(const char *cmd) {
  gsm.println(cmd);
  delay(500);

  while (gsm.available()) {
    Serial.write(gsm.read());
  }
}

void sendSMS(const char *number, const char *msg) {
  Serial.println("Sending SMS...");

  gsm.println("AT+CMGF=1"); // Text mode
  delay(300);

  gsm.print("AT+CMGS=\"");
  gsm.print(number);
  gsm.println("\"");
  delay(300);

  gsm.print(msg);
  delay(300);

  gsm.write(26); // CTRL+Z to send SMS
  delay(3000);

  Serial.println("SMS Sent Successfully!");
}
