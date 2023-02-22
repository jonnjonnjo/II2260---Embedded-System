/*
  Color memory game for ESP32
    Made by Fawwaz Abrial Saffa

  Referenced: https://wokwi.com/projects/328451800839488084
*/ 

#include "pitches.h"

// Color order of index: RED, YELLOW, GREEN, BLUE
#define NUM_OF_COLORS 4

// set pin numbers
#define BUZZER_PIN 14
const int ledPins[] = {18, 19, 25, 26};
const int buttonPins[] = {4, 5, 34, 35};

// game variables + constants
#define MAX_GAME_LENGTH 30
const int gameTones[] = { NOTE_G3, NOTE_C4, NOTE_E4, NOTE_G5};
int gameSequence[MAX_GAME_LENGTH] = {0};
int gameIndex = 0;

void setup() {
  Serial.begin(115200);  
  // Set GPIO Pin for input and output
  for (int i=0; i<NUM_OF_COLORS; i++) {
    pinMode(buttonPins[i], INPUT);
    pinMode(ledPins[i], OUTPUT);
  }
  pinMode(BUZZER_PIN, INPUT);
}

int readButtons() {
  while (true) {
    for (int i=0; i<NUM_OF_COLORS; i++) {
      if (digitalRead(buttonPins[i]) == HIGH) return i;
    }
    delay(1);
  }
}

void lightLEDAndPlayTone(int ledIndex) {
  digitalWrite(ledPins[ledIndex], HIGH);
  tone(BUZZER_PIN, gameTones[ledIndex]);

  delay(300);
  digitalWrite(ledPins[ledIndex], LOW);
  noTone(BUZZER_PIN);
}

bool checkUserSequence() {
  for (int i=0; i<gameIndex; i++) {
    int expectedButton = gameSequence[i];
    int actualButton = readButtons();
    lightLEDAndPlayTone(actualButton);
    if (expectedButton != actualButton) return false;
  }
  return true;
}

void gameOver() {
  gameIndex = 0;
  delay(200);

  // Play a Wah-Wah-Wah-Wah sound
  tone(BUZZER_PIN, NOTE_DS5);
  delay(300);
  tone(BUZZER_PIN, NOTE_D5);
  delay(300);
  tone(BUZZER_PIN, NOTE_CS5);
  delay(300);
  for (byte i = 0; i < 10; i++) {
    for (int pitch = -10; pitch <= 10; pitch++) {
      tone(BUZZER_PIN, NOTE_C5 + pitch);
      delay(5);
    }
  }
  noTone(BUZZER_PIN);
}

void playLevelUpSound() {
  tone(BUZZER_PIN, NOTE_E4);
  delay(150);
  tone(BUZZER_PIN, NOTE_G4);
  delay(150);
  tone(BUZZER_PIN, NOTE_E5);
  delay(150);
  tone(BUZZER_PIN, NOTE_C5);
  delay(150);
  tone(BUZZER_PIN, NOTE_D5);
  delay(150);
  tone(BUZZER_PIN, NOTE_G5);
  delay(150);
  noTone(BUZZER_PIN);
}

void playSequence() {
  for (int i=0; i<gameIndex; i++) {
    lightLEDAndPlayTone(gameSequence[i]);
    delay(50);
  }
}

void loop() {
  Serial.println("\nSkor: " + gameIndex);
  gameSequence[gameIndex++] = random(0, 4);
  playSequence();
  if (!checkUserSequence() gameOver();
  delay(300);
  if (gameIndex > 0) {
    playLevelUpSound();
    delay(300);
  }
}