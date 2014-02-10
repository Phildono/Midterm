/*
William Kasurak
2456259


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
//setting the initial spot in the key entry to be at 0 so that the passcode is imputed in order
int position = 0;

//keymap
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


//estalish some pins
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
  
  //start the function for setting recognizing 
  int bd;
  
  //reads keypad as input for the passcode
  char key = keypad.getKey();
  
  //if any key is pressed this starts the next segment of code that checks to see if the entry is correct or incorrect
  //using if statements to push the user to the next number in the passcode if a number is entered correctly and 
  //restarts the sequence if it is not functioning properly
  if (int(key) != 0) {
    
    
    for(bd=0; bd<=position; ++bd)
    {
      digitalWrite(greenPin,HIGH);
      delay(500);
      digitalWrite(greenPin,LOW);
    }
    
    //this sets up the condition required to make the lock open which is that all 8 numbers are entered in the right order
    if (key == bDay[position])
      {
        ++position;
        if (position == 8)
        {
          playSong();
          position = 0;
        }
    //this portion of code calls the function that freezes the  arduino when passcode entry is incorect
    //and resets the user's postition in the password back to the start of it so that they can not figure out the lock by
    //process of elimination
    } else {
        invalidCode();
        position = 0;
      }
    
    
  }


}

//execute the playback of the song notes
void song(){
  //tone function this isnt working properly although I formated it the way the reference said to? I can't figure out how to debug this
  //becuase I am unfamiliar with the tone function its syntax as well as how it's library works
   tone(speakPin,melody,noteDurations);
}

//establishes an if statement that freezes the arduino with a 5 sec delay as a lockout feature to prevent reentry of password for the 5 second delay
void invalidCode()
{
  digitalWrite(redPin, HIGH);
  
  //delays for 5 seconds to keep led on before turning freezing the arduino for 5 seconds to keep the open state on
  delay(5000);
  digitalWrite(redPin, LOW);
  
}


}

//function that functions as the unlock state of the lock and calls the song to be played
void playSong()
{
 song();
 
  digitalWrite(greenPin, HIGH);

  
  delay(5000);
  digitalWrite(greenPin, LOW);

}
}

