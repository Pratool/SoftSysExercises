#include <stdio.h>

void skip(char *msg) {
    puts(msg+6);
}

int main() {
    char *msgO = "Don't call me";
    skip(msgO);

    return 0;
}
