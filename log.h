#ifndef LOG_H
#define LOG_H

static int log_descriptor = -1;

void setup_log(int descriptor);
void err(int e);
void err_info(int e, char *msg);
void info(char *msg);

#endif