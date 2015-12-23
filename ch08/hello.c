#include <stdio.h>
#include <glib.h>

int main(int argc, char** argv) {
    GList* list = NULL;
    list = g_list_append(list, "Hello world!");
    int i;
    for (i = 0; i < 5; i++) {
        list = g_list_append(list, "new item");
    }
    printf("The first item is '%s'\n", g_list_first(list)->data);
    i = 0;
    GList* l;
    for (l = list; l != NULL; l = l->next) {
        printf("item #%d: '%s'\n", i, l->data);
        i++;
    }
    return 0;
}
