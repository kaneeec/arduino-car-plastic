#include <Arduino.h>
#include "libraries/DCMotor/DCMotor.h"
//#include "libraries/IRemote/IrRemote.h"
//#include "libraries/IRemote/IrRemoteInt.h"
#include "libraries/BTController/BTController.h"

//const long IR_OK = 16712445;
//const long IR_LEFT = 16720605;
//const long IR_RIGHT = 16761405;
//const long IR_UP = 16736925;
//const long IR_DOWN = 16754775;
//const long IR_STAR = 16728765;
//const long IR_HASH = 16732845;

DCMotor engine(2, 3);
DCMotor steering(4, 5);

//IrReceiver irReceiver(6);
//IrReading irReading;

BTController bt(10, 11);

//void readIr();
void readBtController();

void setup() {
    Serial.begin(9600);
//    irReceiver.enableIRIn();
}

void loop() {
//    readIr();
    readBtController();
    engine.run();
    steering.run();
}

//void readIr() {
//    if (irReceiver.decode(&irReading)) {
//        if (irReading.value == IR_STAR) {
//            if (engine.isRunning()) {
//                engine.stop();
//            } else {
//                engine.start();
//            }
//            if (steering.isRunning()) {
//                steering.stop();
//            }
//        } else if (irReading.value == IR_LEFT) {
//            steering.start();
//            steering.setDirection(FORWARDS);
//        } else if (irReading.value == IR_RIGHT) {
//            steering.start();
//            steering.setDirection(BACKWARDS);
//        } else if (irReading.value == IR_OK) {
//            steering.stop();
//        } else if (irReading.value == IR_UP) {
//            engine.setDirection(FORWARDS);
//        } else if (irReading.value == IR_DOWN) {
//            engine.setDirection(BACKWARDS);
//        }
//        irReceiver.resume(); // Receive the next value
//    }
//}

void readBtController() {
    if (bt.parseValues()) {
        BTControllerAngles& angles = bt.getAngles();
        if (angles.turn < -10) {
            steering.setDirection(FORWARDS);
            steering.start();
        } else if (angles.turn > 10) {
            steering.setDirection(BACKWARDS);
            steering.start();
        } else {
            steering.stop();
        }

        if (angles.forward < 20) {
            engine.setDirection(FORWARDS);
            engine.start();
        } else if (angles.forward > 40) {
            engine.setDirection(BACKWARDS);
            engine.start();
        } else {
            engine.stop();
        }
    }
}
