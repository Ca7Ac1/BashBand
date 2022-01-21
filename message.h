#ifndef MESSAGE_H
#define MESSAGE_H

#define PLAY_NOTE_MSG 'p'
#define STOP_NOTE_MSG 's'
#define OPEN_CONNECTION_MSG 'j'
#define CLOSE_CONNECTION_MSG 'q'
#define KICK_CONNECTION_MSG 'k'

typedef struct note_message
{
    char instrument[10];
    char note[3];
    char note_id[25];
} note_message;

typedef struct stop_message
{
    char note_id[25];
} stop_message;

typedef struct open_message
{
    int id; 
    char name[100];
} open_message;

typedef struct close_message
{
    int id;
} close_message;

typedef struct message
{
    char type;
    union data
    {
        note_message note_data;
        close_message close_data;
        open_message open_data;
        stop_message stop_data;
    } data;
} message;

#endif
