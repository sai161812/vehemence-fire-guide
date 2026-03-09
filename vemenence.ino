#include <Wire.h>
#include <Adafruit_MLX90614.h>

#define SDA_PIN 21
#define SCL_PIN 22

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

int trigPin = 5;
int echoPin = 18;

int rfPin = 27;
int ledPin = 2;

float tempThreshold = 70.0;   // danger heat
int distanceThreshold = 50;   // obstacle distance

long getDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;

  return distance;
}

void setup() {

  Serial.begin(115200);

  Wire.begin(SDA_PIN, SCL_PIN);
  mlx.begin();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(rfPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.println("System Started");
}

void loop() {

  float temperature = mlx.readObjectTempC();
  long distance = getDistance();
  int rfSignal = digitalRead(rfPin);

  Serial.println("-------------");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  Serial.print("RF Signal: ");
  Serial.println(rfSignal);

  bool safe = false;

  if (temperature < tempThreshold &&
      distance > distanceThreshold &&
      rfSignal == HIGH) {

    safe = true;
  }

  if (safe) {
    digitalWrite(ledPin, HIGH);
    Serial.println("SAFE DIRECTION");
  }
  else {
    digitalWrite(ledPin, LOW);
    Serial.println("UNSAFE");
  }

  delay(1000);
}