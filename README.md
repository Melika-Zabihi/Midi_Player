# Midi_Player
This repository contains a Midi Player application. The application uses the libsoundio library for audio input and output, and a custom library named *beep* for generating certain frequencies to play notes.
* **Phase 1: Note Playback:** In the first phase, we utilize the beep.h library to play the notes listed in the NOTES.txt file.
* **Phase 2: Getting MIDI Header Chunk:** In the second phase, we focus on printing the header chunk of a given MIDI file.
* **Phase 3: Note and Event Extraction:** In the third phase, we extract and print the notes and events from a given MIDI file.
<br>

## Building the Project
**Step 1:**
* Create a directory for storing your libraries.
* Change your directory to the directory you just made.
* Type the following command in your terminal:
```
 git clone https://github.com/andrewrk/libsoundio.git
```
* Change your directory tolibsoundio folder.
* Create a folder for building the source code.
* Change your directory to the directory you just made.
* Make your *make* file (cmake)
* Make created files (make)
* Run this command:
```
sudo make install
```
Some of the object files may fail to be copied to /lib or /usr/lib during the install process so you will need to copy them using terminal, you can use following commands: (run them in build dir)
```
sudo cp ./libsoundio.so.2 /usr/lib/
sudo cp ./libsoundio.so.2 /lib/
```
**Step 2:**
* Include “beep.h” in your source code. (You should copy “beep.h” in your project directory.)
* Copy libsoundio.so.2 in your project directory
```
cp libsoundio.so.2 where_ever_your_project_main.c_located
```
* Copy “beep.o” in your project directory .
* Use the following command to compile and run your project:
```
gcc name_of_your_file.c beep.o libsoundio.so.2 -lm
```
