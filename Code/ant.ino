#include <ESP32Servo.h>

#define NUM_SERVOS 18

Servo servo[NUM_SERVOS];

int pins[NUM_SERVOS] = {
  2, 4, 5,
  12, 13, 14,
  15, 16, 17,
  18, 19, 21,
  22, 23, 25,
  26, 27, 32
};

int neutral[NUM_SERVOS] = {
  90, 90, 90,
  90, 90, 90,
  90, 90, 90,
  90, 90, 90,
  90, 90, 90,
  90, 90, 90
};

int lift = 30;
int swing = 25;

void setup() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    servo[i].setPeriodHertz(50);
    servo[i].attach(pins[i], 500, 2500);
    servo[i].write(neutral[i]);
  }
  delay(2000);
}

void moveLeg(int leg, int coxa, int femur, int tibia) {
  int i = leg * 3;
  servo[i].write(neutral[i] + coxa);
  servo[i + 1].write(neutral[i + 1] + femur);
  servo[i + 2].write(neutral[i + 2] + tibia);
}

int tripodA[3] = {0, 3, 4};
int tripodB[3] = {1, 2, 5};

void loop() {

  for (int i = 0; i < 3; i++) moveLeg(tripodA[i], 0, -lift, lift);
  delay(200);

  for (int i = 0; i < 3; i++) moveLeg(tripodA[i], swing, -lift, lift);
  delay(200);

  for (int i = 0; i < 3; i++) moveLeg(tripodA[i], swing, 0, 0);
  delay(200);

  for (int i = 0; i < 3; i++) moveLeg(tripodB[i], -swing, 0, 0);
  delay(200);

  for (int i = 0; i < 3; i++) moveLeg(tripodB[i], -swing, -lift, lift);
  delay(200);

  for (int i = 0; i < 3; i++) moveLeg(tripodB[i], swing, -lift, lift);
  delay(200);

  for (int i = 0; i < 3; i++) moveLeg(tripodB[i], swing, 0, 0);
  delay(200);

  for (int i = 0; i < 3; i++) moveLeg(tripodA[i], -swing, 0, 0);
  delay(200);
}