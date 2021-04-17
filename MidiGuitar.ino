/* These two lines allow for altering variables within the Arduino's default code
 Later in the program these functions will be used to change the rate at which the 
 Arduino can read analog pin values.
 */
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))



void setup()
{

  /*
   The following 3 lines set the Analog to Digital Converter prescale clock to 16
   This should allow for analog read rates at ~77 Khz. 
   */
  sbi(ADCSRA,ADPS2) ;
  cbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;

  // initializes the serial communication, 31250 is the MIDI spec baud rate
  Serial.begin(31250);
}
void loop()
{


}


void fretChecker()
{

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
