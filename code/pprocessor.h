#include "labelHandler.h";
#ifndef PPROCESSOR_H
#define PPROCESSOR_H

void pProcess(char* line, char* loc, FILE* output);

Label* detectLabel(char* line, int num);
#endif
