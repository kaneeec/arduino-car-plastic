#include <Arduino.h>
#include "libraries/BTController/BTController.h"
#include "libraries/DCMotor/DCMotor.h"

DCMotor engine(2, 3);
DCMotor steering(4, 5);
BTController bt(10, 11);

void readBtController();

void setup() {
    Serial.begin(9600);
}

void loop() {
    readBtController();
    engine.run();
    steering.run();
}

void readBtController() {
    if (bt.read()) {
        String value = bt.getValue();

        if (value.indexOf('1') >= 0) {
            engine.setDirection(FORWARDS);
            engine.start();
        } else if (value.indexOf('2') >= 0) {
            engine.setDirection(BACKWARDS);
            engine.start();
        } else {
            engine.stop();
        }

        if (value.indexOf('3') >= 0) {
            steering.setDirection(FORWARDS);
            steering.start();
        } else if (value.indexOf('4') >= 0) {
            steering.setDirection(BACKWARDS);
            steering.start();
        } else {
            steering.stop();
        }
    }
}
