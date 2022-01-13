#ifndef MESSAGE_H
#define MESSAGE_H

#define PLAY_NOTE_MSG 'p'
#define CLOSE_CONNECTION_MSG 'q'

typedef struct message
{
    char type;
    union data 
    {
        note_message note_data;
        close_message close_data;
    } data;
} message;

typedef struct note_message
{
    char[10] instrument;
    char[3] note;
} note_message;

typdef struct close_message
{
    int id;
} close_message;

#endif
