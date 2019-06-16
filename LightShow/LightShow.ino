#include <NewPing.h>

#define PLACEHOLDER1 2
#define PLACEHOLDER2 3

NewPing sonar(PLACEHOLDER1, PLACEHOLDER2, 200);

int purple[] = {255, 0, 255};
float beat = 60000 / 160;
int x = 0;
int y = 0;
int z = 0;

void setup() {
  // notes - song starts 8 seconds in and there are chorus from beats 72 to 132
  Serial.begin(9600);
  UltraSonicActivation();
  RGBCount(beat);
}

int RGBOn(int t) {
  analogWrite(9, random(0, 255));
  analogWrite(10, random(0, 255));
  analogWrite(11, random(0, 255));
  delay(t);
  analogWrite(9, 0);
  analogWrite(10, 0);
  analogWrite(11, 0);
  delay(t);
}

int ColorOn(int col[], int t) {
  analogWrite(9, col[0]);
  analogWrite(10, col[1]);
  analogWrite(11, col[2]);
  delay(t);
}

int ColorFlash(int col[], int t) {
  analogWrite(9, col[0]);
  analogWrite(10, col[1]);
  analogWrite(11, col[2]);
  delay(t);
  analogWrite(9, 0);
  analogWrite(10, 0);
  analogWrite(11, 0);
  delay(t);
}

int RGBCount(int t) {
  Serial.println("IT WORKS");
  while (x < 34 ) {
    analogWrite(9, random(0, 255));
    analogWrite(10, random(0, 255));
    delay(t);
    analogWrite(11, random(0, 255));
    analogWrite(9, 0);
    analogWrite(10, 0);
    analogWrite(11, 0);
    delay(t);
    x++;
    z++;
    Serial.println(z);
  }
  while (y < 32) {
    analogWrite(9, 255);
    analogWrite(10, 255);
    analogWrite(11, 0);
    delay(t / 2);
    analogWrite(9, 0);
    analogWrite(10, 0);
    analogWrite(11, 0);
    delay(t / 2);
    analogWrite(9, 0);
    analogWrite(10, 0);
    analogWrite(11, 255);
    delay(t / 2);
    analogWrite(9, 0);
    analogWrite(10, 0);
    analogWrite(11, 0);
    delay(t / 2);
    y++;
    z++;
    Serial.println(z);
  }
  while (z < 96) {
    analogWrite(9, random(0, 255));
    analogWrite(10, random(0, 255));
    analogWrite(11, random(0, 255));
    delay(t);
    analogWrite(9, 0);
    analogWrite(10, 0);
    analogWrite(11, 0);
    delay(t);
    z++;
    Serial.println(z);
  }
}

void UltraSonicActivation() {
   int uS = sonar.ping_cm();
   delay(50);
   while ((uS == 0) || (uS < 30)) {
      uS = sonar.ping_cm();
      Serial.print("Activation: ");
      Serial.print(uS);
      Serial.println("cm");
      delay(50);
   }
   Serial.println("Start dancing");
}



void loop() {
  // put your main code here, to run repeatedly:
  delay(100000);
}
