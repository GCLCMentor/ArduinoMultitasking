// Pines
const int LED_1_PIN = 9;
const int LED_2_PIN = 10;
const int LED_3_PIN = 11;
const int LED_4_PIN = 12;
const int POTENTIOMETER_PIN = A0;
const int BUTTON_PIN = 5;

// Tiempos
unsigned long previousTimeLed1 = 0;
const unsigned long timeIntervalLed1 = 1000;
int ledState1 = LOW;

unsigned long previousTimeSerialPrint = 0;
const unsigned long timeIntervalSerialPrint = 2000;

void setup() {
  Serial.begin(9600);

  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(LED_3_PIN, OUTPUT);
  pinMode(LED_4_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  unsigned long currentTime = millis();

  // LED 1 parpadea
  if (currentTime - previousTimeLed1 > timeIntervalLed1) {
    previousTimeLed1 = currentTime;
    ledState1 = !ledState1;
    digitalWrite(LED_1_PIN, ledState1);
  }

  // Brillo LED 2 con entrada por Serial
  if (Serial.available()) {
    int userInput = Serial.parseInt();
    if (userInput >= 0 && userInput < 256) {
      analogWrite(LED_2_PIN, userInput);
    }
  }

  // LED 3 responde al botón
  digitalWrite(LED_3_PIN, digitalRead(BUTTON_PIN));

  // LED 4 según potenciómetro
  int potValue = analogRead(POTENTIOMETER_PIN);
  digitalWrite(LED_4_PIN, potValue > 512);

  // Imprime el valor del potenciómetro
  if (currentTime - previousTimeSerialPrint > timeIntervalSerialPrint) {
    previousTimeSerialPrint = currentTime;
    Serial.print("Value : ");
    Serial.println(potValue);
  }
}
