/* These two lines allow for altering variables within the Arduino's default code
  Later in the program these functions will be used to change the rate at which the
  Arduino can read analog pin values.
*/
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

struct GuitarString {
  int pin;
  int baseNote;
  bool fretted = false;
  int fret;
  bool plucked = false;
  int readings;
  bool noteOn = false;
  long timeOn;
  long duration;
};

const int numStrings = 6;
GuitarString guitString[numStrings];
const int numFrets = 7;
int fret[numFrets];

void setup()
{
  /*
    The following 3 lines set the Analog to Digital Converter prescale clock to 16
    This should allow for analog read rates at ~77 Khz.
  */
  sbi(ADCSRA, ADPS2) ;
  cbi(ADCSRA, ADPS1) ;
  cbi(ADCSRA, ADPS0) ;

  guitString[0].baseNote = 52; //e4
  guitString[1].baseNote = 47; //b3
  guitString[2].baseNote = 43; //g3
  guitString[3].baseNote = 38; //d3
  guitString[4].baseNote = 33; //a2
  guitString[5].baseNote = 28; //e2

  guitString[0].pin = 2;
  guitString[1].pin = 3;
  guitString[2].pin = 4;
  guitString[3].pin = 5;
  guitString[4].pin = 6;
  guitString[5].pin = 7;

  fret[0] = 8;
  fret[1] = 9;
  fret[2] = 10;
  fret[3] = 11;
  fret[4] = 12;
  fret[5] = 13;
  fret[6] = 14;

  // initializes the serial communication, 31250 is the MIDI spec baud rate
  Serial.begin(31250);
}
void loop()
{
  fretChecker();


}


void fretChecker()
{
  for (int i = 0; i < numStrings; i++)
  {
    digitalWrite(guitString[i].pin, HIGH);
    for (int j = numFrets - 1; j >= 0; j--)
    {
      //preset these to not fretted, if we are they will be fixed
      guitString[i].fretted = false;
      guitString[i].fret = 0;
      if (digitalRead(fret[j]) == HIGH)
      {
        guitString[i].fretted = true;
        guitString[i].fret = j + 1;
      }
    }
    // turn the string back to low so the next one can be done
    digitalWrite(guitString[i].pin, LOW);
  }

}

void midiPlay(int cmd, int note, int velocity)
{
  /*
  	midiPlay(0x99,pad[i].noteValue,vel); //hex 99 is note on, second nine is channel 10
  	midiPlay(0x99,pad[i].noteValue,0x00); // velocity of 0 indicates note off
  	also 0x8c where c is channel is valid note off. zero velocity might be easier however.

  	pitch bend is 0xEc byte 1 is bend LSB, byte 2 is MSB
  	each byte in this case is 7 bits. 127 max for each
  	for my purposes it might make sense to only read the MSB, or modulate it at least. will need to do some mathi

  	pitch bend 0 - 16383
  	b1 is msb
  	b2 is lsb
  	p = b1 << 7 + b2

  	midi note 60 is middle C
  */
  Serial.write(cmd);
  Serial.write(note);
  Serial.write(velocity);
}
