#include "pipe_networking.h"
#include <signal.h>

void process(char *s);
void subserver(int from_client);

static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove("luigi");
    exit(0);
  }
}

int main() {
  signal(SIGINT, sighandler);
  
  while (1) {
    int from_client = server_setup();
    if (fork() == 0) {
      subserver(from_client);
    }
  }
}

void subserver(int from_client) {
  int to_client = server_connect(from_client);

  char buffer[256];
  while (1) {
    read(from_client, buffer, sizeof(buffer));
    process(buffer);
    write(to_client, buffer, sizeof(buffer));
  }
}

char rot13(char c) {
  if (('A' <= c && c <= 'M') || ('a' <= c && c <= 'n')) {
    return c + 13;
  }
  if (('N' <= c && c <= 'Z') || ('n' <= c && c <= 'z')) {
    return c - 13;
  }

  return c;
}

void process(char * s) {
  while (*s != '\0') {
    *s = rot13(*s);
    s++;
  }
}
