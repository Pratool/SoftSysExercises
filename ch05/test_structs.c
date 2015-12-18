#include <stdio.h>

int main() {
    struct fish {
        const char *name;
        const char *species;
        int teeth;
        int age;
    };

    struct fish snappy = {"Snappy", "Piranha", 69, 4};

    printf("%s the %s is %d years old and has %d teeth.\n",
            snappy.name, snappy.species, snappy.age, snappy.teeth);

    return 0;
}
