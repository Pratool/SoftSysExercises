#include <stdio.h>

typedef union {
    int Integer;
    float Float;
} number;

typedef struct {
    number price;
    const char *name;
} menu_item;

int main() {
    menu_item item0 = { {.Float=13.70}, "Hand-Tossed Burger"};
    menu_item item1 = { {.Float=1.79}, "Medium Soda"};
    menu_item receipt[] = {item0, item1};

    printf("%s\t\t%f\n", receipt[0].name, receipt[0].price.Float);
    printf("%s\t\t%f\n", receipt[1].name, receipt[1].price.Float);

    return 0;
}
