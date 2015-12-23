#include <stdio.h>
#include <glib.h>
#include <ctype.h>

void print_hash(gpointer key, gpointer value, gpointer outfile) {
    int val = (int) value;
    fprintf((FILE *)outfile, "%s,%d\n", (char*)key, val);
}

int main(int argc, char **argv) {
    FILE *text;
    FILE *out_data;
    if ( (text = fopen(argv[1], "r")) == NULL ) {
        printf("Error: unable to open file %s\n", argv[1]);
        return 1;
    }
    if ( (out_data = fopen(argv[2], "w")) == NULL) {
        printf("Error: unable to open file %s\n", argv[2]);
        return 1;
    }
    char bufc[80];
    unsigned int bufc_ind = 0;
    char val = getc(text);
    GHashTable *word_freq = g_hash_table_new(g_str_hash, g_str_equal);

    while ( (val = getc(text)) != EOF ) {
        val = tolower(val);
        if ( isspace(val) || ispunct(val) ) {
            bufc[bufc_ind] = '\0';
            if (g_hash_table_contains(word_freq, bufc)) {
                g_hash_table_insert(word_freq, g_strdup(bufc),
                        g_hash_table_lookup(word_freq, bufc)+1);
            } else {
                g_hash_table_insert(word_freq, g_strdup(bufc), (void *)1);
            }
            bufc_ind = 0;
        } else {
            bufc[bufc_ind++] = val;
        }
    }

    fprintf(out_data, "word,frequency\n");
    g_hash_table_foreach(word_freq, print_hash, out_data);
    return 0;
}
