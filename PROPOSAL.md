# Project_02
Systems final project 
Ayan Chowdhury, Wilde Chu
Pd 4

A real-time keyboard jam session for multiple users

Description:
A user will connect to the server and be presented with a piano drawn in the terminal. Keys on the keyboard will be mapped to piano keys, and pressing a note will play the note for all users connected. There will be an options menu with mute, record, and disconnect buttons.

Technical Design:
There will be a main server that all clients connect to with TCP sockets. The server will need allocation of memory, usage of pipes and sockets. The server will keep accepting incomming connections. Another process within that server will deal with all the clients and the logic. We'll create a struct to send data from client to server. SoX cmd tool will be used along with exec and forking to play notes. Signals will be used to deal with stopping notes. NCurses will be used to deal with keyboard capture and the interface.

Divying work:
 - Ayan will focus on dealing with server
 - Wilde will focus on dealing with the interface/input with NCurses
 - Both will try to work on dealing with audio tools

Timeline:
 - Basic funcitonality for server connection in the first day
 - Playing and stopping notes (functions independent of user input) should be completed within the first few days
 - Specific server functionality such as sending the notes to all clients should be finished in the next day
 - Use NCurses to handle keyboard input by the end of the first week (At this point we should have a server where users can play music together, but with no interface)
 - Generate a basic interface for our program
 - Further steps (in order of priority)
   - Mute feature
   - Recording and playing back music
   - User files for customization of key's and interface
   - Introduce a chat feature on the side of our interface
   - Making our interface nicer
