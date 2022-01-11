# Project_02
Systems final project 
Ayan Chowdhury, Wilde Chu
Pd 4

A real-time keyboard jam session for multiple users

Description:
A user will connect to the server and be presented with a piano drawn in the terminal. Keys on the keyboard will be mapped to piano keys, and pressing a note will play the note for all users connected. There will be an options menu with mute, record, and disconnect buttons.

Technical Design:
There will be a main server that all clients connect to with UDP sockets. When a client connects, the server will fork a subserver to handle client interactions. When a client sends a note, the server will send that note to all connected clients. We'll use linked lists to store the list of clients, and we'll create a struct to send note data from client to server.


 Keyboard that multiple users can play
  - Sockets to have multiple clients play music together
  - Files to store and play back recordings
  - ALSA C library to play and record music
  - TinySoundFont for synth instruments
  - NCurses for interactive terminal
  - Maybe include operations window with options like mute and chat
  - Maybe use SoX cmd tool (or libsox) to play audio
    - Unsure if this would work but fork off process to play a note via play cmd tool for infinite time, then if the key is unpressed send a signal to the process to stop 


TODO: talk about signals, dividing work
