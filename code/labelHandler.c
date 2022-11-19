#include "labelHandler.h"
#include <string.h>
#include <stdio.h>

void InsertLabel(LabelTable *table, Label* label){
    int size = table->size;
    if (size != 20){
        table->table[size] = *label;
        table->size++;
    }
}
int findLabel(char* line, LabelTable* table){
    int length = strlen(line);
    for (int i = 0; i < table->size; i+= 1){
        printf("Search %sn", line);
        printf("  Name: %s\n", table->table[i].name);
        if (strncmp(line, table->table[i].name, length - 1) == 0){
            return i;
        }
    }
    return -1;
}
