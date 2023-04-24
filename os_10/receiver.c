#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int received_number = 0;
int received_bits = 0;

void receive_bit(int signal) {
  int bit = (signal == SIGUSR1) ? 1 : 0;
  received_number |= (bit << received_bits);
  received_bits++;
}

void sigusr1_handler(int signal) {
  receive_bit(signal);
}

void sigusr2_handler(int signal) {
  receive_bit(signal);
}

void setup_signal_handlers() {
  struct sigaction sa1, sa2;
  sa1.sa_handler = sigusr1_handler;
  sa2.sa_handler = sigusr2_handler;

  sigemptyset(&sa1.sa_mask);
  sigemptyset(&sa2.sa_mask);

  sa1.sa_flags = 0;
  sa2.sa_flags = 0;

  sigaction(SIGUSR1, &sa1, NULL);
  sigaction(SIGUSR2, &sa2, NULL);
}

int main() {
  pid_t receiver_pid = getpid();

  printf("Receiver PID: %d\n", receiver_pid);
  printf("Waiting for the integer...\n");

  setup_signal_handlers();

  while (received_bits < 32) {
    pause();
  }

  printf("Received integer: %d\n", received_number);

  return 0;
}
