# Midi_Guitar

This project is my attempt to create a MIDI controller in the form factor of a guitar

To achieve this I plan to build a miniature style guitar with only 7 frets. These frets will approximate the scale length between frets 7-14 on a real guitar. This is my favorite and most confortable playing position. The device will allow transposing frets to allow playing in different positions. 

Needs:
6 strings
7 fret sensors
7? led fret markers
6 Analog bend sensors --- not sure if this will work, more below
6 analog pluck sensors --- similar to the "knock sensor" sample arduino project
5? transpose switches
1 single/multichannel switch --- multichannel output will treat each string as its own midi channel. This will allow each string to have its own pitchwheel setting, and synths that accept multiple channel input will produce polyphonic audio
Single channel input will reduce all of the data to a single midi channel. This would probably have to disable the bend sensors, or perhaps use a seperate pot as a whammy sensor.

The hardware aspect of this project is more involved, schematics and drawings will be provided.

The code logic should be as follows:

Strings object
base note - EADGBe, each fret will add a semitone.
fretted value - which fret on the device is fretted?

Each loop one string will be pulled up to a HIGH voltage state. The fret sensors will be read in descending order to see if one of them is in contact with the string. If a fret reads "high" it breaks the loop and sets the strings fret value to the sensors number + transpose value.

After determining the fret values we read the analog pluck sensors. 
if a value above a threshold is read the string will be flagged as plucked.
When a string is plucked it will begin populating an array of readings, the number is TBD
Once the array is full the highest value will be used to assign velocity --- or maybe calculate somehow?
Once the velocity is determined a MIDI note on will be sent. The string will be flagged as "ON"

If a string is "ON" we will check the bend sensors for their values
Need to decide how often we update the bend/send MIDI CC values. This could be a bottleneck

Need to determine how NOTE OFF is found. 




