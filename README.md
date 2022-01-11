# Project_02
Systems final project 

IDEAS:
 
 Keyboard that multiple users can play
  - Sockets to have multiple clients play music together
  - Files to store and play back recordings
  - ALSA C library to play and record music
  - TinySoundFont for synth instruments
  - NCurses for interactive terminal
  - Maybe include operations window with options like mute and chat
  - Maybe use SoX cmd tool (or libsox) to play audio
    - Unsure if this would work but fork off process to play a note via play cmd tool for infinite time, then if the key is unpressed send a signal to the process to stop 
