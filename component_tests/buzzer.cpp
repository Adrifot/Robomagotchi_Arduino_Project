#include <Arduino.h>
#define BUZZ_PIN 6

int noteFrequencies[] = {262, 294, 330, 349, 392, 440, 494}; 
int noteDurations[] = {1500, 1500, 500, 500, 1500, 100, 500}; // 500 ms for each note
int currentNoteIndex = 0; // Track the current note being played
unsigned long buzzStartTime = 0, buzzDuration = 0;
bool buzzActive = false;
void loop() {
  // If no note is playing, start the next note in the sequence
  if (!buzzActive && currentNoteIndex < 7) {
    startBuzzer(noteFrequencies[currentNoteIndex], noteDurations[currentNoteIndex]);
    currentNoteIndex++; // Move to the next note
  }

  // Check if the buzzer duration has expired
  updateBuzzer();

  // Reset the sequence when all notes are played
  if (currentNoteIndex >= 7 && !buzzActive) {
    currentNoteIndex = 0; // Restart the sequence
  }
}

void startBuzzer(int frequency, unsigned long duration) {
    tone(BUZZ_PIN, frequency);
    buzzStartTime = millis();
    buzzDuration = duration;
    buzzActive = true;
    delay(1);
}

void updateBuzzer() {
    if(buzzActive && (millis() - buzzStartTime >= buzzDuration)) {
        noTone(BUZZ_PIN);
        buzzActive = false;
        delay(1);
    }
}