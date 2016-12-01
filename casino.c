#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "aes.h"

int main(int argc, char *argv[]) {
    const char *flag = getenv("CRYPTO_FLAG");
    const char *key = getenv("CRYPTO_KEY");

    char input_string[256];
    scanf("%255[^\n]s", input_string);

    char padding[17];
    memset(padding, 'Y', sizeof(padding));
    padding[16 - ( strlen(input_string) % 16 )] = '\0';

    char input_buffer[256];
    int len = snprintf(input_buffer, 256, "%s%s%s", input_string, flag, padding);
    if(len > 255) {
        printf("Please use a smaller input.\n");
        exit(0);
    }
    printf("%d\n", len);

    char output_buffer[256];
    int i;
    for(i = 0; i < len; i += 16) {
        AES128_ECB_encrypt(input_buffer + i, key, output_buffer + i);
    }
    write(STDOUT_FILENO, output_buffer, i);
    return 0;
}
