#ifndef SETTINGS_H
#define SETTINGS_H

#define NOTES 13

// this name is beautiful appreciate it pls
typedef struct key
{
    char button;
    // C#4 null
    char note[4];
} key;

key *setup_notes(char *file);
void alter_settings(char *settings, char *instrument, key **keys);
void change_keys(key *keys);
void get_saved_notes(key **keys);
void change_settings_key(char *settings);
void change_instrument(char *instrument);
void save_notes(key *keys);

#endif
