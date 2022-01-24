
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <ctype.h>
#include <signal.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "settings.h"
#include "input.h"

key *setup_notes(char *file)
{
    key *keys = malloc(sizeof(key) * NOTES);

    if (file != NULL)
    {
        struct stat st;
        stat(file, &st);

        if (st.st_size == sizeof(key) * NOTES)
        {
            int fd = open(file, O_RDONLY, 0644);

            read(fd, keys, sizeof(key) * NOTES);
        }
        else
        {
            file = NULL;
        }
    }

    if (file == NULL)
    {
        // 0: C, 1: C#, 2: D, 3: D#, 4: E, 5: F, 6: F#, 7: G, 8: G#, 9: A, 10: A#, 11: B
        keys[0] = (key){.button = 'Z', .note = "C4"};
        keys[1] = (key){.button = 'S', .note = "C#4"};
        keys[2] = (key){.button = 'X', .note = "D4"};
        keys[3] = (key){.button = 'D', .note = "D#4"};
        keys[4] = (key){.button = 'C', .note = "E4"};
        keys[5] = (key){.button = 'V', .note = "F4"};
        keys[6] = (key){.button = 'G', .note = "F#4"};
        keys[7] = (key){.button = 'B', .note = "G4"};
        keys[8] = (key){.button = 'H', .note = "G#4"};
        keys[9] = (key){.button = 'N', .note = "A4"};
        keys[10] = (key){.button = 'J', .note = "A#4"};
        keys[11] = (key){.button = 'M', .note = "B4"};
        keys[12] = (key){.button = ',', .note = "C5"};
    }

    return keys;
}

void alter_settings(char *settings, char *instrument, key **keys)
{
    char altering = 1;

    while (altering)
    {
        char input[100];

        printf("\n\n\nWhat would you like to do\n");
        printf("1: Quit\n2: Return to playing\n3. Change instrument\n4. Alter keys manually\n5. Alter keys from saved data\n6. Save key data\n");
        fgets(input, sizeof(input), stdin);

        switch (input[0])
        {
        case '1':
            SDL_Quit();
            kill(-1 * getpid(), SIGKILL);
            break;

        case '2':
            altering = 0;
            break;

        case '3':
            change_instrument(instrument);
            break;

        case '4':
            change_keys(*keys);
            change_settings_key(settings);
            break;

        case '5':
            get_saved_notes(keys);
            change_settings_key(settings);

            break;

        case '6':
            save_notes(*keys);
            break;

        default:
            printf("Invalid input, please try again\n\n\n");
            break;
        }
    }
}

void change_instrument(char *instrument)
{
    printf("Choose an instrument\n");
    printf("1: Piano\n2: Guitar");
}

void change_settings_key(char *settings)
{
    char input[100];

    while (1)
    {
        printf("What would you like your settings key to be: ");
        fgets(input, sizeof(input), stdin);

        if (isalnum(input[0]) && (input[1] == '\n' || input[1] == '\0'))
        {
            settings[0] = toupper(input[0]);
            break;
        }
        else
        {
            printf("Please enter a valid key\n");
        }
    }
}


void change_keys(key *keys)
{
    char input[100];

    for (int i = 0; i < NOTES; i++)
    {
        while (1)
        {
            printf("What would you like your %s key to be: ", keys[i].note);
            fgets(input, sizeof(input), stdin);

            if (isalnum(input[0]) && (input[1] == '\n' || input[1] == '\0'))
            {
                keys[i].button = toupper(input[0]);
                break;
            }
            else
            {
                printf("Please enter a valid key\n");
            }
        }
    }
}

void get_saved_notes(key **keys)
{
    char file[100];
    printf("Enter the name of the file you wish to get your keys from (blank for default): ");
    fgets(file, sizeof(file), stdin);

    free(*keys);

    if (file[0] == '\0' || file[0] == '\n')
    {
        *keys = setup_notes(NULL);
    }
    else
    {
        *keys = setup_notes(file);
    }
}

void save_notes(key *keys)
{
    char file[100];

    while (1)
    {
        printf("Enter the name of the file you wish to save your keys to: ");
        fgets(file, sizeof(file), stdin);

        if (strlen(file) < 3)
        {
            printf("File name must be more than 2 characters long, please try again\n");
        }
        else
        {
            break;
        }
    }

    int fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);

    write(fd, keys, sizeof(key) * NOTES);
}

