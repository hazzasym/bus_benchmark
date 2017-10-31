#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <czmq.h>
#include <pthread.h>

#define MSG_MAX 1000000

int client = 0;

const char *data2k1 =
    "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"
    "Cf";

const char *data2k = "T-data";

void burst_message(zsock_t *sock) {
  sleep(5);
  int n_p;
  int64_t start = zclock_time();
  for (n_p = 0; n_p < MSG_MAX; n_p++) {
    zstr_sendf(sock, "%s : %d", data2k, n_p);
  }
  int elaps = (zclock_time() - start) / 1000;
  printf("%s : %d\n", "Time used", elaps);
  zstr_send(sock, "TEND");
}

void *publish(void *sock) {

  zsock_t *pub = (zsock_t *)sock;

  while (!client) {
    zstr_send(sock, "T-Hello");
    sleep(1);
  }
  printf("%s\n", "Client connected");
  burst_message(sock);
  return (NULL);
}

void *check_client(void *sock) {

  zsock_t *rep = (zsock_t *)sock;

  while (true) {
    char *str_recv = zstr_recv(sock);
    if (0 == strcmp(str_recv, "sub_ready")) {
      zstr_send(sock, "OK");
      zstr_free(&str_recv);
      client = 1;
      break;
    }
  }
  return (NULL);
}

int main(int argc, const char *argv[]) {

  zsock_t *pub = zsock_new_pub("tcp://127.0.0.1:9876");
  assert(pub);
  printf("HVM current %d\n", zsock_sndhwm(pub));
  zsock_set_sndhwm(pub, 0);
  printf("HVM current %d\n", zsock_sndhwm(pub));
  zsock_t *rep = zsock_new_rep("tcp://127.0.0.1:9877");
  assert(rep);

  pthread_t publish_t, client_t;
  pthread_create(&publish_t, NULL, publish, (void *)pub);
  pthread_create(&client_t, NULL, check_client, (void *)rep);

  pthread_join(publish_t, NULL);
  pthread_join(client_t, NULL);

  zsock_destroy(&pub);
  zsock_destroy(&rep);
  return (0);
}
