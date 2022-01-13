#ifndef MESSAGE_H
#define MESSAGE_H

#define PLAY_NOTE_MSG 'p'
#define STOP_NOTE_MSG 's'
#define CLOSE_CONNECTION_MSG 'q'

typedef struct message
{
    char type;
    union data
    {
        note_message note_data;
        close_message close_data;
        stop_message stop_data;
    } data;
} message;

typedef struct note_message
{
    char[10] instrument;
    char[3] note;
    char[100] note_id;
} note_message;

typdef struct close_message
{
    int id;
} close_message;

typdef struct stop_message
{
    char[100] note_id;
} close_message;

#endif
