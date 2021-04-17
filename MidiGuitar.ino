/* These two lines allow for altering variables within the Arduino's default code
 Later in the program these functions will be used to change the rate at which the 
 Arduino can read analog pin values.
 */
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))



void setup()
{

  /*
  The following 3 lines of code are borrowed from microsmart.co.za/technical/2013/03/01/advanced-arduino-adc/
   They set the Analog to Digital Converter prescale clock to 16, meaning 16Mhz / prescale(16) = 1Mhz
   The adc requires 25 cycles to resolve a value so 1Mhz/25 = approx 40,000 samples per second
   */
  sbi(ADCSRA,ADPS2) ;
  cbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;

  // initializes the serial communication, 31250 is the MIDI spec baud rate
  Serial.begin(31250);

void loop() //like java's main, but more powerful, this body loops indefinitely
{


}


void fretChecker()
{

}

