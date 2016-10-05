#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <czmq.h>
#include <pthread.h>

int main(int argc, const char* argv[])
{

	zsock_t *sub = zsock_new_sub("tcp://127.0.0.1:9876", "T");

	assert(sub);
	zsock_t *req = zsock_new_req("tcp://127.0.0.1:9877");
	assert(req);

	while (true) {
		char* str_recv = zstr_recv(sub);
		if (0 == strcmp("T-Hello", str_recv)) {
			zstr_free(&str_recv);
			zstr_send(req, "sub_ready");
			char* res = zstr_recv(req);
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
		printf("%s %d\n", "data numbers", ndata);
		if (0 == strcmp("Last message!", sub_msg)) {
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
