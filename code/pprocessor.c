#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pprocessor.h"

void pProcess(char* line, char* loc, FILE* output){
    loc[0] = 0;
    int ind = 0;
    char* comm = strchr(line, '#');
    if (comm != NULL){
        int num = (int)(comm - line);
        strncat(loc, line, num);
        ind = 1;
    }
    else {
        strcpy(loc, line);
    }
    if (loc[0] != '\n'){
        char* p = strtok(loc, "\t");
        while (p != NULL){
            fprintf(output. "%s", p);
            p = strtok(NULL, "\t");
        }
        if (ind == 1){
            fprintf(output, "\n");
        }
    }
}
Label* detectLabel(char* line, int num){
    if (strrchr(line, ':') != NULL){
        Label *n = malloc(sizeof(Label));
        printf("Hex Address: %p ", num * 4);
        int address = (num * 4);
        n->lineNumber = num;
        printf("Address: ");
        for (int i = 16; i >= 0; i-= 1){
            int temp = address >> i;
            n->address[i] = (temp) & 1;
            printf("%d", n->address[i]);
        }
        printf("   ");
        char* c = strchr(line, ":");
        int pos = c - line;
        strncpy(n->name, line, pos);
        printf("%s\n", n->name);
        return n;
    }
    return NULL;
}
