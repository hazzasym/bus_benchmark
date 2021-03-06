#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <czmq.h>
#include <pthread.h>

int main(int argc, const char *argv[]) {

  zsock_t *sub = zsock_new_sub("tcp://122.155.0.233:9876", "T");
  assert(sub);
  printf("HVM current %d\n", zsock_rcvhwm(sub));
  zsock_set_rcvhwm(sub, 0);
  printf("HVM current %d\n", zsock_rcvhwm(sub));

  zsock_t *req = zsock_new_req("tcp://122.155.0.233:9877");
  assert(req);

  while (true) {
    char *str_recv = zstr_recv(sub);
    if (0 == strcmp("T-Hello", str_recv)) {
      zstr_free(&str_recv);
      zstr_send(req, "sub_ready");
      char *res = zstr_recv(req);
      if (0 == strcmp("OK", res)) {
        zstr_free(&res);
        break;
      }
    }
  }

  printf("%s\n", "Subscribe to channal success.");

  int ndata = 0;

  while (true) {
    char *sub_msg = zstr_recv(sub);
    printf("%s : %d\n", sub_msg, ndata);
    if (0 == strcmp("TEND", sub_msg)) {
      printf("%s %s\n", "received last message.", sub_msg);
      zstr_free(&sub_msg);
      break;
    }
    zstr_free(&sub_msg);
    ndata++;
  }
  printf("%s : %d\n", "Data received", ndata);

  zsock_destroy(&sub);
  zsock_destroy(&req);
  return (0);
}
