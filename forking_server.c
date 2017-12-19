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
  while (1) {
  }
}

void process(char * s) {
}
