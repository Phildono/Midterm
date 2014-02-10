/*
William Kasurak

This is a change to the code

simplified and altered the code from the following sources  to create
the interactive birthday invite sketch
http://musicdiver.com/wordpress/2013/01/keypad-code-lock-with-arduino/

http://tech-zen.tv/episodes/shows/make-it-work/episodes/keypad-input-to-an-arduino-episode-11

http://www.arduino.cc/en/Tutorial/PlayMelody


http://arduino.cc/en/Reference/tone
*/

#include <Keypad.h>
#include "pitches.h"


//initiallizing the passcode (my birthday)
char* bDay ="03181993";
int position = 0;

const byte rows = 4;
const byte cols = 4;
char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

//put together and set up the basis of my keymap
byte rowPins[rows] = {4, 5, 6, 7};
byte colPins[cols] = {0, 1, 2, 3};
Keypad keypad = Keypad(makeKeymap(keys),rowPins, colPins, rows, cols);


//initiate the pins
int redPin = 8;
int greenPin = 9;
int speakPin = 11;

 //transcribong happy birthday to the arduino
int melody[] = {NOTE_G4, NOTE_G4,NOTE_G4, NOTE_A4, NOTE_G4,NOTE_C4, NOTE_B4};
int noteDurations[] = { 4, 8, 8, 4,4,4,4 };
  
void setup()
{

for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(8, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }

 
 //set up led and speaker as output
  pinMode(speakPin,  OUTPUT);
  pinMode(redPin,    OUTPUT);
  pinMode(greenPin,  OUTPUT);
  digitalWrite(redPin,  LOW);
  digitalWrite(greenPin,LOW);
  Serial.begin(9600);
  
}

 void loop()
{
  int bd;
  
  char key = keypad.getKey();
  
  if (int(key) != 0) {
    
    
    for(bd=0; bd<=position; ++bd)
    {

    }
    
    if (key == bDay[position])
      {
        ++position;
        if (position == 8)
        {
          playSong();
          position = 0;
        }
      } else {
        invalidCode();
        position = 0;
      }
    
    
  }


}

void song(){
  
   tone(speakPin,melody,noteDurations);
}
void invalidCode()
{
  digitalWrite(redPin, HIGH);
  
  
  delay(5000);
  digitalWrite(redPin, LOW);
  
}

void playSong()
{
 song();
 
  digitalWrite(greenPin, HIGH);

  
  delay(5000);
  digitalWrite(greenPin, LOW);

}
}

