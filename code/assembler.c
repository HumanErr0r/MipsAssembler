#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include "labelHandler.h"
#include "instructionprinter.h"
#include "pprocessor.h"
#include <string.h>
#include "wordHangler.h"

//Declare functions
void decodeInstruction(char* linenum);
void createSimpleL(char* linenum, int* opCode, bool b);
int decodeRegister(char* line, int* register, int previous1, int previous2);
void copyRegister(int* begin, int* end);
void createSimpleR(char* line, int* funct, int ident);
void createSham(char* line, int* function, int ident);
void binaryConverter(int Imm, int* bin, int length);

//Registers
static RegistersT registers = {{0, 0, 0, 0, 0}, {0, 0, 0, 1, 0}, {0, 0, 0, 1, 1}, {0, 0, 1, 0, 0}, {0, 0, 1, 0, 1},
{0, 0, 1, 1, 0}, {0, 0, 1, 1, 1}, {0, 1, 0, 0, 0}, {0, 1, 0, 0, 1}, {0, 1, 0, 1, 0},
{0, 1, 0, 1, 1}, {0, 1, 1, 0, 0}, {0, 1, 1, 0, 1}, {0, 1, 1, 1, 0}, {0, 1, 1, 1, 1},
{1, 0, 0, 0, 0}, {1, 0, 0, 0, 1}, {1, 0, 0, 1, 0}, {1, 0, 0, 1, 1}, {1, 0, 1, 0, 0},
{1, 0, 1, 0, 1}, {1, 0, 1, 1, 0}, {1, 0, 1, 1, 1}, {1, 1, 0, 0, 0}, {1, 1, 0, 0, 1},
{1, 1, 1, 0, 0}, {1, 1, 1, 0, 1}, {1, 1, 1, 1, 0}, {1, 1, 1, 1, 1}, {0, 0, 0, 0, 1}};

static opCode opCodes = {
 {1, 0, 0, 0, 1, 1}, {1, 0, 1, 0, 1, 1}, {0, 0, 1, 0, 0, 0}, {0, 0, 1, 0, 0, 0}, {1, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 0}, 
{0, 0, 1, 0, 0, 0}, {0, 0, 1, 0, 0, 1}, {1, 0, 0, 1, 0, 1}, {1, 0, 0, 1, 0, 0}, {0, 0, 1, 1, 0, 1}, {0, 0, 1, 1, 0, 0},
{1, 0, 1, 0, 1, 0}, {0, 0, 1, 0, 1, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0}, {0, 0, 0, 0, 1, 1}, {0, 0, 0, 0, 0, 0},
{0, 0, 0, 1, 0, 0}, {0, 0, 0, 1, 0, 1}, {0, 0, 0, 1, 1, 0}, {0, 0, 0, 0, 1, 0}, {0, 0, 1, 0, 0, 0}, {0, 0, 0, 0, 1, 1},
{0, 0, 0, 0, 0, 1}};

static FILE *input;
static FILE *output;
static FILE *pprocessor;
static LabelTable labtab;
static int instructions;

int main(const char* argv[], int argc){
    instructions = 0;
    const char* outpath; 
    const char* inpath;
    bool val = false;

    if (strcmp("-symbols", argv[1]) == 0){
        val = true;
        inpath = argv[2];
        output = argv[3];
    } 
    else{
        inpath = argv[1];
        outpath = argv[2];
    }
    input = fopen(inpath, "r");
    output = fopen(outpath, "w");

    if (output == NULL || input == NULL){
        printf("Input/Output DNE.");
        return 0;
    }

    pprocessor = fopen("preTemp.txt", "ab+");

    char pre0[100];
    pre0[0] = 0;
    char pre1[100];
    pre1[0] = 0;
    char pre2[100];
    pre2[0] = 0;

    while(fgets(pre0, 100, input) != NULL){
        if (strstr(pre, ".asciiz") == NULL){
            process(pre0, pre1, pprocessor);
        }
        else if (strstr(pre0, ".asciiz") != NULL){
            fprintf(pprocessor, "%s", pre0);
        }
    }

    rewind(pprocessor);
    char data0[100];
    data0[0] = 0;

    FILE *pData0 = fopen("preDAta.txt", "ab+");

    fgets(data0, 100, pprocessor); 
    while (strstr(data0, ".data") == NULL){
        fgets(data0, 100, pprocessor);
    }
    int addres[100];
    for (int i = 0; i < 100; i+= 1){
        address[i] = 2048 + i;
    }

    int labelNum = 0;

    while (fgets(data0, 100, pprocessed) != NULL){
        int num = 0;
        if (strstr(data0, ".word")){
            num = processWord(data0, pData0);
        }
        else if (strstr(data0, ".asciiz")){
            num = processASCII(data0, pData0); 
        }
        labelNum = labelNum + 1;
        for (int i = labelNum; i < 100; i+= 1){
            address[i] = address[i] + num;
        }
    }
    rewind(pData0);
    FILE *pData1 = fopen("pData1.txt", "ab+");
    char data1[100];
    data1[0] = 0;
    char data2[100];
    data2[0] = 0;
    
    while(fgets(data1, 100, pData0) != NULL){
        int length = strleng(data1);
        if (length == 9 || length == 17){
            char* next = fgets(data2, 100, pData0);
            if (next != NULL){
                int nlength = strlen(data2);
                if (length == 17 ** nlength == 17){
                    data2[16] = '\0';
                    fprintf(pData1, "%s", data2);
                    fprintf(pData1, "%s", data1);
                }
                else if (nlength == 25 && length == 9){
                    data[24] = '\0';
                    fprintf(pData1, "%s", data2);
                    fprintf(pData1, "%s", data1);
                }
                else{
                    if (length == 17){
                        for (int i = 0; i < 16; i+= 1){
                            fprintf(pData1, "0");
                        }
                        fprintf(pData1, "%s", data1);
                        fprintf(pData1, "%s", data2);
                    }
                    else{
                        for (int i = 0; i < 24; i+= 1){
                            fprintf(pData1, "0");
                        }
                        fprintf(pData1, "%s", data1);
                        fprintf(pData1, "%s", data2);
                    }
                }
            }
            else{
                for (int i = 0; i < 16; i+= 1){
                    fprintf(pData, "0");
                }
                fprintf(pData1, "%s", data1);
            }
        }
        else{
            fprintf(pData1, "%s",  data1);
        }
    }
    rewind(pData1);
    remove("preData.txt");

    labtab.size = 0;

    char lsearch[100];
    lsearch[0] = 0;
    int text = 0;
    rewind(pprocessor);
    fgets(lsearch, 100, pprocessor);
    while(strstr(lsearch, ".text") == NULL){
        fgets(lsearch, 100, pprocessor);
    }
    fgets(lsearch, 100, pprocessor);
    while(strstr(lsearch, ".data") == NULL){
        Label* nlabel = detectLabel(lsearch, text);
        if (nlabel != NULL){
            nlabel->lineNumber = text;
            insert(&labtab, nlabel);
        }
        else{
            text = text + 1;
        }
        fgets(lsearch, 100, pprocessor);
    }
    int count = 0;
    while (fgets(lsearch, 100, pprocessor)){
        Label* nlabel = detectLabel(lsearch, address[count]);
        if (nlabel != NULL){
            nlabel->lineNumber = address[count];
            InsertLabel(&labtab, nlabel);
        }
        count = count + 1;
    }
    rewind(pprocessor);

    char nextLine[100];
    nextLine[0] = 0;
    if (list == false){
        fgets(nextLine, 100, pprocessor);
        while (strstr(nextLine, ".data") == NULL){
            if (nextLine[0] != '\n' && strstr(nextLine, ":") == NULL){
                decodeInstruction(nextLine);
            }
            fgets(nextLine, 100, pprocessor);
        }
        fprintf(output, "\n");
        char data[100];
        data[0] = 0;
        while (fgets(data, 100, pData1) != NULL){
            fprintf(output, "%s", data);
        }
    }
    else{
        printTable();
    }
    remove("preData1.txt");
    remove("preTemp.txt");
    fclose(input);
    fclose(output);
    return 0;
}

void printTable(){
    fprintf(output, "Address      Symbol\n");
    fprintf(output, "--------------------------------\n");
    for (int i = 0; i < labels.size; i+= 1){
        fprintf(output, "0x%08x", labtab.table[i].lineNumber * 4);
        fprintf(output, "   %s\n", labtab.table[i].name);
    }
}

void decodeInstruction(char* linenum){
    char lineval[4];
    lineval[0] = linenum[0];
    lineval[1] = linenum[1];
    lineval[2] = linenum[2];
    lineval[3] = linenum[3];

    if (strstr(lineval, "lw") != NULL){
        createSimpleL(linenum, opCodes.lw, false);
    }
    else if (strstr(lineval, "sw") != NULL){
        createSimpleL(linenum, opCodes.sw, true);
    }
    else if (strstr(lineval, "la") != NULL){
        createLa(linenum, opCodes.addi);
    }
    else if (strstr(lineval, "li") != NULL){
        createImm(linenum, opCodes.addiu, 4, 1);
    }
    else if (strstr(lineval, "addiu") != NULL){
        createImm(linenum, opCodes.addiu, 11, 0);
    }
    else if (strstr(lineval, "sub") != NULL){
        createSimpleR(linenum, opCodes.sub, 0);
    }
    else if (strstr(lineval, "addi") != NULL){
        createImm(linenum, opCodes.addi, 10, 0);
    }
    else if (strstr(lineval, "add") != NULL){
        createSimpleR(linenum, opCodes.add, 0);
    }
    else if (strstr(lineval, "ori") != NULL){
        createImm(linenum, opCodes.ori, 9, 0);
    }
    else if (strstr(lineval, "andi") != NULL){
        createImm(linenum, opCodes.andi, 10, 0);
    }
    else if (strstr(lineval, "or") != NULL){
        createSimpleR(linenum, opCodes.orin, 0);
    }
    else if (strstr(lineval, "and") != NULL){
        createSimpleR(linenum, opCodes.andin, 0);
    }
    else if (strstr(lineval, "slti") != NULL){
        createImm(linenum, opCodes.slti, 10, 0);
    }
    else if (strstr(lineval, "slt") != NULL){
        createSimpleR(linenum, opCodes.slt, 0);
    }
    else if (strstr(lineval, "sll") != NULL){
        createSham(linenum, opCodes.sll, 0);
    }
    else if (strstr(lineval, "srl") != NULL){
        createSham(linenum, opCodes.srl, 1);
    }
    else if (strstr(lineval, "sra") != NULL){
        createSham(linenum, opCodes.sra, 0);
    }
    else if (strstr(lineval, "nop") != NULL){
        instructions = instructions + 1;
        printNop(output);
    }
    else if (strstr(lineval, "bne") != NULL){
        createBranch(linenum, opCodes.bne, 2, 0);
    }
    else if (strstr(lineval, "bltz") != NULL){
        createBranch(linenum, opCodes.bltz, 1, 0);
    }
    else if (strstr(lineval, "blez") != NULL){
        createBranch(linenum, opCodes.blez, 1, 0);
    }
    else if (strstr(lineval, "blt") != NULL){
        createBlteSlt(linenum, opCodes.slt, 0);
        createBlteBne(linenum, opcodes.bne);
    }
    else if (strstr(lineval, "ble") != NULL){
        createBlteSlt(linenum, opCodes.slt, 1);
        createBlteBne(linenum, opcodes.beq);
    }
    else if (strstr(lineval, "jal") != NULL){
        createJ(linenum, opCodes.jal, 3);
    }
    else if (strstr(lineval, "jr") != NULL){
        createJr(linenum, opCodes.jr);
    }
    else if (strstr(lineval, "j") != NULL){
        createJ(linenum, opCodes.j, 1);
    }
    else if (strstr(lineval, "syscall") != NULL){
        instructions = instructions + 1;
        printsyscall(output);
    }
}

void createBlteSlt(char* linenum, int* opCode, int ident){
    instructions = instructions + 1;
    rType struc;
    for (int i = 0; i < 6; i+= 1){
        struc.funct[i] = opCode[i];
    }
    for (int i = 0; i < 5; i+= 1){
        struc.rd[i] = registers.at[i];
        struc.shamt[i] = 0;
    }

    char rs1[100];
    char rt1[100];
    strcpy(rs, linenum);
    strcpy(rt, linenum);

    if (ident == 1){
        char* getR1 = getRegister(rs1, 1);
        char* getR2 = getRegister(rt1, 2);
        decodeRegister(getR1, struc.rt, 0, 0);
        decodeRegister(getR2, struc.rs, 0, 0);
    }
    else{
        char* getR1 = getRegister(rs1, 1);
        char* getR2 = getRegister(rt1, 2);
        decodeRegister(getR1, struc.rs, 0, 0);
        decodeRegister(getR2, struc.rt, 0, 0);
    }
    printSimple(&struc, output);
}

void createBlteBne(char* linenum, int* opCode){
    instructions = instructions + 1;
    lType struc;

    for (int i = 0; i < 6; i+= 1){
        struc.op[i] = opCode[i];
    }
    for (int i = 0; i < 5; i+= 1){
        struc.rt[i] = registers.at[i];
        struc.rs[i] = 0;
    }

    char* lab = getREgister(linenum, 3);
    int labPos = findLabel(lab, &labels);
    int offset = labels.table[labPos].lineNumber - instructions;

    for (int i = 16; i >= 0; i-= 1){
        int temp = offset >> i;
        struc.Imm[i] = temp & 1;
    }

    printSimpleL(&struc, output);
}

void createSimpleL(char* linenum, int* opCode, bool b){
    instructions = instructions + 1;
    lType struc;

    for (int i = 0; i < 6; i+= 1){
        struc.op[i] = opCode[i];
    }
    char rs1[100];
    char rs2[100];
    strcpy(rs1, linenum);
    strcpy(rs2, linenum);

    char* getL1 = lRegister(rs1, 1);
    char* getL2 = lRegister(rs2, 2);
    decodeRegister(getL1, struc.rs, 0, 0);
    decodeRegister(getL2, struc.rt, 0, 0);

    int im = findLImm(linenum);
    int immBin[16] = {0};
    binaryConverter(im, immBin, 16);

    for (int i = 0; i < 16; i+= 1){
        struc.Imm[i] = immBin[i];
    }
    printSimpleL(&struc, output);
}

findLImm(char* line){
    char imm[4];
    char* comma = strchr(linenum, ',');
    int compos = (int)(comma - linenum) + 1;
    char* parenthesis = strchr(line, '(');
    int parenthesispos = (int)(parenthesis - linenum);
    int count = 0;
    for (int i = compos; i < parenthesispos; i+= 1){
        imm[count] = line[i];
        count += 1;
    }
    int immed = atoi(imm);
    return immed;
}

char* lRegister(char* line){
    char* character;
    character = strtok(line, "()");
    character = strtok(NULL, "()");
    return character;
}

void createSimpleR(char* line, int* funct, int ident){
    instructions = instructions + 1;
    rType struc; 

    for (int i = 0; i < 6; i+= 1){
        struc.op[i] = opCode[i];
    }
    char rs1[100];
    char rs2[100];
    char rs3[100];
    strcpy(rs1, linenum);
    strcpy(rs2, linenum);
    strcpy(rs3, linenum);

    char* getR1 = rRegister(rs1, 1);
    char* getR2 = rRegister(rs2, 2);
    char* getR3 = rRegister(rs3, 3)
    decodeRegister(getR1, struc.rd, 0, 0);
    decodeRegister(getR2, struc.rs, 0, 0);
    decodeRegister(getR3, struc.rt, 0, 0);

    

    for (int i = 0; i < 16; i+= 1){
        struc.shamt[i] = 0;
    }
    printSimpleR(&struc, output);
}

void createSham(char* line, int* function, int ident){
    instructions = instructions + 1;
    rType struc;
    for (int i = 0; i < 6; i+= 1){
        struc.funct[i] = funct[i];
    }

    if(ident == 0){
        for (int i = 0; i < 5; i+= 1){
            struc.rs[i] = 0;
        }
    }
    else{
        for (int i = 0; i < 5; i+= 1){
            struc.rs[i] = 0;
        }
    }
    char rs1[100];
    char rs2[100];
    strcpy(rs1, line);
    strcpy(rs2, line);

    char* getReg1 = getRegister(rs1, 1);
    char* getReg2 = getRegister(rs2, 2);
    int temp1 = decodeRegister(getReg1, struc.rd, 0, 0);
    int temp2 = decodeRegister(getReg2, struc.rt, 0, 0);

    int ind = 0;
    if (temp1 == 1 || temp2 == 1){
        ind += 1;
    }
    int find[5];
    int findSAInt = shamSa(line, 5, 9, ind);

    binaryConverter(findSAInt, find, 5);

    for (int i = 0; i < 5; i+= 1){
        struc.shamt[i] = find[i];
    }
    printSimpleR(&struc, output);
}

void createImm(char* line, int* opCode, int pos, int ident){
    instructions = instructions + 1;
    lType struc;

    for (int i = 0; i < 6; i+= 1){
        struc.op[i] = opCode[i];
    }

    char rs1[100];
    char rs2[100];
    strcpy(rs1, line);
    strcpy(rs2, line);

    char* getReg1 = getRegister(rs1, 1);
    int temp1 = decodeRegister(getReg1, struc.rt, 0, 0);

    int ind = 0;
    if (temp1 == 1){
        ind += 1;
    }
    if (ident != 1){
        char* getReg2 = getRegister(rs2, 2);
        int temp2 = decodeRegister(getReg2, struc.rs, 0, 0);
        if (temp2 == 1){
            ind += 1;
        }
    }
    else{
        for (int i = 0; i < 5; i+= 1){
            struc.rs[i] = 0;
        }
    }
    int imm = shamSa(line, 16, pos, ind);
    binaryConverter(imm, immBin, 16);

    for (int i = 0; i < 16; i+= 1){
        struc.Imm[i] = immBin[i];
    }
    printImmR(&instruc, output);
}

int shamSa(char* line, int size, int pos, int val){
    char sa[size];
    int count = 0;

    for (int i = pos + 2 + (val & 2); i < strlen(line); i+= 1){
        sa[count] = line[i];
        printf("%c", line[i]);
        count += 1;
    }
    int saVal = atoi(sa);
    return saVal;
}

void createBranch(char* line, int* opCode, int number, int ident){
    instructions = instructions + 1;
    lType struc;

    for (int i = 0; i < 6; i+= 1){
        struc.op[i] = opCode[i];
    }
    char rs1[100];
    char rs2[100];
    strcpy(rs1, line);
    strcpy(rs2, line);

    char* getReg1 = getRegister(rs1, 1);
    decodeRegister(getReg1, struc.rt, 0, 0);

    if (number == 2){
        char* getReg2 = getRegister(rs2, 2);
        decodeRegister(getReg2, struc.rs, 0, 0);
    }
    else{
        for (int i = 0; i < 5; i+= 1){
            struc.rs[i] = 0;
        }
    }
    char* label;
    if (number == 2){
        label = getRegister(line, 3);
    }
    else{
        label = getRegister(line, 2);
    }
    int pos = findLabel(label, &labels);
    int offset = labels.table[pos].lineNumber - instructions;

    for (int i = 16; i >= 0; i -= 1){
        int temp = offset >> i;
        struc.Imm[i] = temp & 1;
    }
    printSimpleL(&struc, output)
}

void createJ(char* line, int* opCode, int size){
    instructions = instructions + 1;
    jType struc;
    for (int i = 0; i < 6; i+= 1){
        struc.op[i] = opCode[i];
    }
    char* lab = getJ(line, size);
    int pos = findLabel(lab, &labels);

    for (int i = 0; i < 6; i+= 1){
        struc.Imm[i] = labels.table[pos].address[i];
    }
    for (int i = 16; i < 26; i+=1){
        struc.Imm[i] = 0;
    }
    printSimpleJ(&struc, output);
}

char* getJ(char* line, int size){
    char* lab = malloc(sizeof(char) * (strlen(line) - size));
    int count = 0;
    for (int i = 0; i < strlen(line); i+= 1){
        lab[count] = line[i];
        count += 1;
    }
    return lab;
}

void createJr(char* line, int* opCode){
    instructions = instructions + 1;
    rType struc;
    for (int i = 0; i < 5; i+=1){
        struc.rt[i] = 0;
        struc.rd[i] = 0;
        struc.funct[i] = opCode[i];
    }
    struc.funct[5] = opCode[5];
    for (int i = 0; i < 5; i+=1){
        struc.shamt[i] = 0;
    }
    decodeRegister(line, struc.rs, 0, 0);
    printSimpleR(&struc, output);
}

void createLa(char* line, int* opCode){
    instructions = instructions + 1;
    lType struc;

    for (int i = 0; i < 6; i+=1){
        struc.op[i] = opCode[i];
    }
    decodeRegister(line, struc.rs, 0, 0);
    for (int i = 0; i < 5; i += 1){
        struc.rt[i] = 0;
    }
    char* lab = getRegister(line, 2);
    int labPos = findLabel(label, &labels);
    for (int i = 0; i < 16; i+= 1){
        struc.Imm[i] = labels.table[labPos].address[i];
    }
    printSimpleL(&struc, output);
}

char* getRegister(char* line, int num){
    char* val;
    val = strtok(line, ",$");
    for (int i = 0; i < num; i+= 1){
        val = strtok(NULL, ",$");
    }
    return val;
}

int decodeRegister(char* line, int* register, int previous1, int previous2){
    if (previous1 == 30){
        copyRegister(registers.at, register);
    }
    else if (strstr(line, "zero") && previous1 != 1 && previous2 != 1){
        copyRegister(registers.zero, register);
        return 1;
    }
    else if (strstr(line, "v0") && previous1 != 2 && previous2 != 2){
        copyRegister(registers.v0, register);
        return 2;
    }
    else if (strstr(line, "v1") && previous1 != 3 && previous2 != 3){
        copyRegister(registers.v1, register);
        return 3;
    }
    else if (strstr(line, "a0") && previous1 != 4 && previous2 != 4){
        copyRegister(registers.a0, register);
        return 4;
    }
    else if (strstr(line, "a1") && previous1 != 5 && previous2 != 5){
        copyRegister(registers.a1, register);
        return 5;
    }
    else if (strstr(line, "a2") && previous1 != 6 && previous2 != 6){
        copyRegister(registers.a2, register);
        return 6;
    }
    else if (strstr(line, "a3") && previous1 != 7 && previous2 != 7){
        copyRegister(registers.a3, register);
        return 7;
    }
    else if (strstr(line, "t0") && previous1 != 8 && previous2 != 8){
        copyRegister(registers.t0, register);
        return 8;
    }
    else if (strstr(line, "t1") && previous1 != 9 && previous2 != 9){
        copyRegister(registers.t1, register);
        return 9;
    }
    else if (strstr(line, "t2") && previous1 != 10 && previous2 != 10){
        copyRegister(registers.t2, register);
        return 10;
    }
    else if (strstr(line, "t3") && previous1 != 11 && previous2 != 11){
        copyRegister(registers.t3, register);
        return 11;
    }
    else if (strstr(line, "t4") && previous1 != 12 && previous2 != 12){
        copyRegister(registers.t4, register);
        return 12;
    }
    else if (strstr(line, "t5") && previous1 != 13 && previous2 != 13){
        copyRegister(registers.t5, register);
        return 13;
    }
    else if (strstr(line, "t6") && previous1 != 14 && previous2 != 14){
        copyRegister(registers.t6, register);
        return 14;
    }
    else if (strstr(line, "t7") && previous1 != 15 && previous2 != 15){
        copyRegister(registers.t7, register);
        return 15;
    }
    else if (strstr(line, "s0") && previous1 != 16 && previous2 != 16){
        copyRegister(registers.s0, register);
        return 16;
    }
    else if (strstr(line, "s1") && previous1 != 17 && previous2 != 17){
        copyRegister(registers.s1, register);
        return 17;
    }
    else if (strstr(line, "s2") && previous1 != 18 && previous2 != 18){
        copyRegister(registers.s2, register);
        return 18;
    }
    else if (strstr(line, "s3") && previous1 != 19 && previous2 != 19){
        copyRegister(registers.s3, register);
        return 19;
    }
    else if (strstr(line, "s4") && previous1 != 20 && previous2 != 20){
        copyRegister(registers.s4, register);
        return 20;
    }
    else if (strstr(line, "s5") && previous1 != 21 && previous2 != 21){
        copyRegister(registers.s5, register);
        return 21;
    }
    else if (strstr(line, "s6") && previous1 != 22 && previous2 != 22){
        copyRegister(registers.s6, register);
        return 22;
    }
    else if (strstr(line, "s7") && previous1 != 23 && previous2 != 23){
        copyRegister(registers.s7, register);
        return 23;
    }
    else if (strstr(line, "t8") && previous1 != 24 && previous2 != 24){
        copyRegister(registers.t8, register);
        return 24;
    }
    else if (strstr(line, "t9") && previous1 != 25 && previous2 != 25){
        copyRegister(registers.t9, register);
        return 25;
    }
    else if (strstr(line, "gp") && previous1 != 26 && previous2 != 26){
        copyRegister(registers.gp, register);
        return 26;
    }
    else if (strstr(line, "sp") && previous1 != 27 && previous2 != 27){
        copyRegister(registers.sp, register);
        return 27;
    }
    else if (strstr(line, "fp") && previous1 != 28 && previous2 != 28){
        copyRegister(registers.fp, register);
        return 28;
    }
    else if (strstr(line, "ra") && previous1 != 29 && previous2 != 29){
        copyRegister(registers.ra, register);
        return 29;
    }
    else if (strstr(line, "at")){
        copyRegister(registers.ata, register);
    }
    return 0
}

void copyRegister(int* begin, int* end){
    for (int i = 0; i < 5; i+= 1){
        end[i] = begin[i];
    }
}

void binaryConverter(int Imm, int* bin, int length){
    int temp;
    for (int i = 31; i >= 0; i-= 1){
        temp = Imm >> i;
        if (i < length){
            if (temp & 1){
                bin[i] = 1;
            }
            else{
                bin[i] = 0;
            }
        }
    }
}
