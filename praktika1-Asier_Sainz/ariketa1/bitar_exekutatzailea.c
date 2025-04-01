#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Erabilera: %s <bitar_izena> <hex_payloada>\n", argv[0]);
        return 1;
    }

    char *file_to_execute = argv[1];
    char *hex_payload = argv[2];

    // Kate hexadezimala bytetara pasa
    int payload_len = strlen(hex_payload) / 4;
    char *payload = malloc(payload_len + 1);
    if (!payload) {
        perror("malloc failed");
        return 1;
    }

    char *p = payload;
    for (int i = 0; hex_payload[i] != '\0'; i += 4) {
        if (hex_payload[i] == '\\' && hex_payload[i + 1] == 'x') {
            int byte = 0;
            sscanf(&hex_payload[i + 2], "%2x", &byte);
            *p++ = (char)byte;
        } else {
            fprintf(stderr, "PAyload formatua ez da zuzena: %s\n", hex_payload);
            free(payload);
            return 1;
        }
    }
    *p = '\0';

    // PArametroen arraya osatu
    char *exec_args[] = {file_to_execute, payload, NULL};

    // Exekutatu bitarra
    execv(exec_args[0], exec_args);
    perror("execv failed");
    free(payload);
    return 1;
}

