const int button = D1;
const int buzzer = D6;
const int redLed = D2;
const int greenLed = D3;
const int blueLed = D4;
const int yellowLed = D5;

const double octave[7] = {523.250, 587.330, 659.250, 698.460, 783.990, 880.000, 987.770};
const double sharpOctave[5] = {554.370, 622.250, 739.990, 830.610, 932.330};
const int happyBirthdayNotes[25] = {1, 1, 2, 1, 4, 9,
                                    1, 1, 2, 1, 5, 4,
                                    1, 1, 1, 6, 4, 9, 2,
                                    0, 0, 6, 4, 5, 4
                                   };
int noteIndex;
int startMusic;
int times;

void ICACHE_RAM_ATTR buttonPressed();

void setup() {
  // put your setup code here, to run once:

  pinMode(buzzer, OUTPUT);

  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);

  pinMode(button, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(button), buttonPressed, FALLING);

  startMusic = 0;
}

void turnLedsOff()
{
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);
    digitalWrite(blueLed, LOW);
    digitalWrite(yellowLed, LOW);
}
void ICACHE_RAM_ATTR buttonPressed()
{
  if (startMusic) {
    startMusic = 0;
    noTone(buzzer);
    turnLedsOff();
  } else {
    startMusic = 1;
    times = 3;
    noteIndex = 0;
  }
  delay(100);
}


void loop() {
  // put your main code here, to run repeatedly:

  if (startMusic) {
    if (happyBirthdayNotes[noteIndex] > 6) {
      tone(buzzer, sharpOctave[happyBirthdayNotes[noteIndex] - 7]);
    } else {
      tone(buzzer, octave[happyBirthdayNotes[noteIndex]]);
    }
    if (random(2)) {
      digitalWrite(redLed, HIGH);
    } else {
      digitalWrite(redLed, LOW);
    }
    if (random(2)) {
      digitalWrite(greenLed, HIGH);
    } else {
      digitalWrite(greenLed, LOW);
    }
    if (random(2)) {
      digitalWrite(blueLed, HIGH);
    } else {
      digitalWrite(blueLed, LOW);
    }
    if (random(2)) {
      digitalWrite(yellowLed, HIGH);
    } else {
      digitalWrite(yellowLed, LOW);
    }
    delay(400);
    noteIndex = noteIndex + 1;
    if (noteIndex == 25) {
      times--;
      noteIndex = 0;
      if (times == 0) {
        turnLedsOff();
        noTone(buzzer);
        startMusic = 0;
      }
    }
  }

}
