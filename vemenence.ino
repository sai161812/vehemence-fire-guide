#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

#define SDA_PIN 21
#define SCL_PIN 22

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

int trigPin = 5;
int echoPin = 19;
int ledPin = 2;

const char* beaconSSID = "EXIT_BEACON";

float tempThreshold = 70.0;
int distanceThreshold = 50;
int rssiThreshold = -60;

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

int getBeaconRSSI() {

  int networks = WiFi.scanNetworks();

  for(int i = 0; i < networks; i++) {

    if(WiFi.SSID(i) == beaconSSID) {
      return WiFi.RSSI(i);
    }

  }

  return -100;
}

void setup() {

  Serial.begin(115200);

  Wire.begin(SDA_PIN, SCL_PIN);
  mlx.begin();

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(ledPin, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  Serial.println("Firefighter Escape System Started");
}

void loop() {

  float temperature = mlx.readObjectTempC();
  long distance = getDistance();
  int rssi = getBeaconRSSI();

  Serial.println("------");

  Serial.print("Temperature: ");
  Serial.println(temperature);

  Serial.print("Distance: ");
  Serial.println(distance);

  Serial.print("WiFi RSSI: ");
  Serial.println(rssi);

  bool safe = false;

  if(temperature < tempThreshold &&
     distance > distanceThreshold &&
     rssi > rssiThreshold) {

      safe = true;
  }

  if(safe) {

    digitalWrite(ledPin, HIGH);
    Serial.println("SAFE DIRECTION");

  } 
  else {

    digitalWrite(ledPin, LOW);
    Serial.println("UNSAFE");

  }

  delay(2000);
}
