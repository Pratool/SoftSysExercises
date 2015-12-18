#include <stdio.h>

typedef struct island {
    const char *name;
    const char *opens;
    const char *closes;
    struct island *next;
} island;

void display(island *start) {
    island *i = start;
    for (; i != NULL; i = i->next) {
        printf("Name: %s\topen: %s-%s\n", i->name, i->opens, i->closes);
    }
}

int main() {
    island amity = {"Amity", "09:00", "17:00", NULL};
    island craggy = {"Craggy", "09:00", "17:00", NULL};
    island isla_nebular = {"Isla Nebular", "09:00", "17:00", NULL};
    island shutter = {"Shutter", "09:00", "17:00", NULL};
    amity.next = &craggy;
    craggy.next = &isla_nebular;
    isla_nebular.next = &shutter;

    printf("%s\t%s\t%s\n", amity.name, amity.opens, amity.closes);

    display(&amity);

    return 0;
}
