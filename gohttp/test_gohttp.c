#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libgohttp.h"

int main(int argc, char** argv) {
    char* url = argc > 1 ? argv[1] : (char*)"https://httpbin.org/get";
    int timeoutMs = 5000;

    char* resp = GoHttpGet(url, timeoutMs);
    if (!resp) {
        fprintf(stderr, "GoHttpGet returned NULL\n");
        return 1;
    }

    if (strncmp(resp, "ERROR:", 6) == 0) {
        fprintf(stderr, "%s\n", resp);
        GoFree(resp);
        return 2;
    }

    printf("Response:\n%.*s\n", 1000, resp); // show up to 1000 chars
    GoFree(resp);
    return 0;
}
