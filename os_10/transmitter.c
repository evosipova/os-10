#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void send_bit(int bit, pid_t receiver_pid) {
  int signal = (bit == 1) ? SIGUSR1 : SIGUSR2;
  kill(receiver_pid, signal);
  usleep(1000);
}

void send_integer(int num, pid_t receiver_pid) {
  for (int i = 0; i < 32; ++i) {
    send_bit((num >> i) & 1, receiver_pid);
  }
}

int main() {
  pid_t transmitter_pid = getpid();
  pid_t receiver_pid;
  int number;

  printf("Transmitter PID: %d\n", transmitter_pid);
  printf("Enter the receiver's PID: ");
  scanf("%d", &receiver_pid);

  printf("Enter an integer to send: ");
  scanf("%d", &number);

  send_integer(number, receiver_pid);

  return 0;
}
