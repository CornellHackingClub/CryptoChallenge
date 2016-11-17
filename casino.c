#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "aes.h"

const char *flag = "CHC{WherePutDis}";
const char *key = "ThisIsNotTheFlag";

int main(int argc, char *argv[]) {
    char buf[128];
	if(argc < 2) {
		printf("Usage: %s <plaintext>\n", argv[0]);
		exit(1);
	}
    char padding[17];
    memset(padding, 'X', sizeof(padding));
    padding[16 - ( strlen(argv[1]) % 16 )] = '\0';

    int len = snprintf(buf, 128, "%s%s%s", argv[1], flag, padding);
    if(len > 127) {
        printf("Please use a smaller input.\n");
        exit(1);
    }

    char output[128];
    int i;
    for(i = 0; i < len; i += 16) {
        AES128_ECB_encrypt(buf + i, key, output + i);
    }
    write(STDOUT_FILENO, output, i);
    return 0;
}
