#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>

#define CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789~!@#$%^&*()"

void print_usage(char *program_name);
char *generate_password(int length, char *device);
void check_password_strength(char *password);

int main(int argc, char *argv[]) {
    int random = 0;
    int check = 0;
    int checkp = 0;
    char *password_to_check = NULL;
    int length = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "--random") == 0) {
            random = 1;
        } else if (strcmp(argv[i], "--check") == 0) {
            check = 1;
        } else if (strcmp(argv[i], "--checkp") == 0) {
            checkp = 1;
            i++;
            if (i < argc) {
                password_to_check = argv[i];
            } else {
                fprintf(stderr, "Error: --checkp requires a password argument\n");
                return 1;
            }
        } else if (argv[i][0] == '-' && argv[i][1] == '-') {
            fprintf(stderr, "Error: Non-existent argument found: %s\n", argv[i]);
            return 1;
        } else {
            length = atoi(argv[i]);
        }
    }

    if (checkp) {
        check_password_strength(password_to_check);
    } else {
        char *password = (random) ? generate_password(length, "/dev/urandom") : generate_password(length, "/dev/urandom");
        if (password) {
            printf("Generated password: %s\n", password);
            if (check) {
                check_password_strength(password);
            }
            free(password);
        } else {
            fprintf(stderr, "Error generating password\n");
        }
    }

    return 0;
}

char *generate_password(int length, char *device) {
    int fd = open(device, O_RDONLY);
    if (fd == -1) {
        return NULL;
    }

    char *buffer = malloc(length + 1);
    if (read(fd, buffer, length) != length) {
        free(buffer);
        close(fd);
        return NULL;
    }

    close(fd);

    for (int i = 0; i < length; i++) {
        buffer[i] = CHARS[buffer[i] % strlen(CHARS)];
    }
    buffer[length] = '\0';

    return buffer;
}

void check_password_strength(char *password) {
    int length_score = strlen(password);
    int digit_score = 0;
    int upper_score = 0;
    int lower_score = 0;
    int special_score = 0;

    for (int i = 0; password[i]; i++) {
        if (isdigit(password[i])) {
            digit_score = 1;
        } else if (isupper(password[i])) {
            upper_score = 1;
        } else if (islower(password[i])) {
            lower_score = 1;
        } else if (ispunct(password[i])) {
            special_score = 1;
        }
    }

    int score = length_score + 5 * (digit_score + upper_score + lower_score + special_score);
    const char *strength, *color;
    if (score < 15) {
        strength = "weak";
        color = "\x1b[31m"; // red
    } else if (score < 25) {
        strength = "medium";
        color = "\x1b[33m"; // yellow
    } else {
        strength = "strong";
        color = "\x1b[32m"; // green
    }

    printf("Password strength: %s%s (score: %d)\x1b[0m\n", color, strength, score);
}

void print_usage(char *program_name) {
    printf("Usage: %s [--help] [--random] [--check] [--checkp <password>] <length>\n", program_name);
}
