#include <stdio.h>
#include <unistd.h>     // for exec() functions
#include <errno.h>      // for errno variable
#include <string.h>     // displays errors with strerror()

int main() {
    if (execl("/sbin/ifconfig", "/sbin/ifconfig", NULL) == -1) {
        if (execlp("ipconfig", "ipconfig", NULL) == -1) {
            fprintf(stderr, "Cannot run ipconfig: %s", strerror(errno));
        }
        return 1;
    }

    return 0;
}
