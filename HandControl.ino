#include <Servo.h>

Servo ThumbRot, ThumbContract, Index, Mid, PinkyRing, UDwrist, LRwrist;
const int Midpot = A0;
const int ThumbButton = 6;

int pos, Mpot, angleMid, buttonState;
int MidExtd, MidCont;

void setup() {
  Serial.begin(9600);

  Index.attach(7);
  ThumbContract.attach(8);
  Mid.attach(9);
  ThumbRot.attach(10);
  UDwrist.attach(11);
  LRwrist.attach(12);
  PinkyRing.attach(6);

  delay(2000);
  MidExtd = analogRead(Midpot);
  delay(2000);
  MidCont = analogRead(Midpot);
}

void loop() {
  wave();
  delay(10000);
  relax();
  keygrab();
  delay(10000);
  relax();
  fist();
  delay(10000);
  relax();
}

void wave() {
  for (pos = 70; pos <= 110; pos += 1) {
    moveLRwrist(pos);
    delay(15);
  }
  for (pos = 110; pos >= 70; pos -= 1) {
    moveLRwrist(pos);
    delay(15);
  }
}

void keygrab() {
  moveIndex(180);
  delay(1000);
  moveThumb(130, -1);
}

void fist() {
  moveIndex(180);
  moveMiddle(180);
  movePinkyRing(180);
  moveThumb(130, -1);
}

void relax() {
  moveIndex(90);
  moveMiddle(90);
  movePinkyRing(90);
  moveThumb(130, 1);
  moveLRwrist(90);
  moveUDwrist(90);
}

void moveThumb(int rotAngle, int contract) {
  if (rotAngle >= 60 && rotAngle <= 140 && contract >= -1 && contract <= 1) {
    ThumbRot.write(pos);
    delay(25);
    if (contract == -1) {
      buttonState = digitalRead(ThumbButton);
      while (buttonState == LOW) {
        ThumbContract.write(0);
        buttonState = digitalRead(ThumbButton);
        delay(25);
      }
    } else if (contract == 1) {
      buttonState = digitalRead(ThumbButton);
      while (buttonState == LOW) {
        ThumbContract.write(0);
        buttonState = digitalRead(ThumbButton);
        delay(25);
      }
    }
  } else {
    Serial.println("Error, thumb rotation or contraction out of range");
  }
}

void moveMiddle(int angle) {
  if (angle >= 90 && angle <= 180) {
    Mpot = analogRead(Midpot);
    angleMid = map(Mpot, MidExtd, MidCont, 90, 180);
    if (angleMid < angle) {
      while (angleMid < angle) {
        Mid.write(180);
        Mpot = analogRead(Midpot);
        angleMid = map(Mpot, MidExtd, MidCont, 90, 180);
        delay(25);
      }
    } else if (angleMid > angle) {
      while (angleMid > angle) {
        Mid.write(0);
        Mpot = analogRead(Midpot);
        angleMid = map(Mpot, MidExtd, MidCont, 90, 180);
        delay(25);
      }
    }
  } else {
    Serial.println("Error, middle finger angle out of range");
  }
}

void moveIndex(int angle) {
  if (angle >= 90 && angle <= 180) {
    Index.write(angle);
    delay(25);
  } else {
    Serial.println("Error, index finger angle out of range");
  }
}

void movePinkyRing(int angle) {
  if (angle >= 90 && angle <= 180) {
    PinkyRing.write(angle);
    delay(25);
  } else {
    Serial.println("Error, pinky/ring finger angle out of range");
  }
}

void moveUDwrist(int angle) {
  if (angle >= 70 && angle <= 110) {
    UDwrist.write(angle);
    delay(25);
  } else {
    Serial.println("Error, angle out of range for wrist motion");
  }
}

void moveLRwrist(int angle) {
  if (angle >= 70 && angle <= 110) {
    LRwrist.write(angle);
    delay(25);
  } else {
    Serial.println("Error, angle out of range for wrist motion");
  }
}