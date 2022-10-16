#include <BleMouse.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#define READPOINTER analogRead(35) > 2000 ? 1 : 0
#define READMIDDLE analogRead(14) > 2000 ? 1 : 0
#define READRING analogRead(33) > 2000 ? 1 : 0
#define READPINKIE analogRead(34) > 2000 ? 1 : 0

#define I2C_SDA 18
#define I2C_SCL 19

Adafruit_MPU6050 mpu;
BleMouse mouse("Power Glove", "FML Manufacturers", 100);
int X, Y;
int pos[2] {0, 0};
float X_off, Y_off, X_last, Y_last;
unsigned long connectedMillis = 0;  // delay actions until after connected for 10 seconds, because apple is dumb

void setup() {
  X = Y = X_off = Y_off = X_last = Y_last = 0;
  Serial.begin(115200);
  mouse.begin();
  Wire.setPins(I2C_SDA, I2C_SCL);
  Wire.setClock(400000);
  mpu.begin();
  delay(100);
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  X_off = a.acceleration.x;
  Y_off = a.acceleration.y;
}


void loop() {

  if (mouse.isConnected()) {
    if (connectedMillis == 0) {
      connectedMillis = millis();
    }
  }

  if (millis() < connectedMillis + (10 * 1000)) {
    return;
  }

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  float Xread = a.acceleration.x;
  float Yread = a.acceleration.y;
  if (Xread == X_last)
    X_off = Xread;
  if (Yread == Y_last)
    Y_off = Yread;
  X += (Xread - X_off);
  Y += (Yread - Y_off);
  X_last = Xread;
  Y_last = Yread;
  if (mouse.isConnected()) {
    if (READPOINTER) {
      mouse.click(MOUSE_LEFT);
      delay(100);
    }
    if (READMIDDLE) {
      mouse.click(MOUSE_RIGHT);
      delay(100);
    }
    if (READRING) {
      mouse.move(0, 0, 1);
      delay(20);
    }
    if (READPINKIE) {
      mouse.move(0, 0, -1);
      delay(20);
    }
    if (X < -5 || X > 5)
      X = 0;
    if (Y < -5 || Y > 5)
      Y = 0;
    if (X > 1) X = -10;
    else if (X < -1) X = 10;
    else X = 0;
    if (Y > 1) Y = 10;
    else if (Y < -1) Y = -10;
    else Y = 0;
    mouse.move(X, Y);
    X = 0;
    Y = 0;
  }
  delay(10);
}