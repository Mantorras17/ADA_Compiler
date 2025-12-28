#include <stdio.h>
#include "parser.tab.h"
#include "code.h"
#include "hashTable.h"
#include "typeChecker.h"
#include "genMIPS.h"

void yyrestart(FILE *input_file);

void get_asm_file_name(char *asm_file, const char *file) {
    const char *filename = file;
    int i = 0;
    for (int j = 0; filename[j] && filename[j] != '.'; j++) {
        asm_file[i++] = filename[j];
    }
    asm_file[i++] = '.';
    asm_file[i++] = 's';
    asm_file[i] = '\0';
}

int main(int argc, char** argv) {
    int status = 0;

    if (argc <= 1) {
        fprintf(stderr, "Usage: %s <input.adb> [input2.adb ...]\n", argv[0]);
        return 1;
    }

    const char* path = argv[1];
    FILE* f = fopen(path, "r");
        
    if (!f) {
        fprintf(stderr, "Error: could not open file '%s'\n", path);
        status = 1;
        return status;
    }
        
    char asm_file[256];
    get_asm_file_name(asm_file, path);
    FILE* f_out = fopen(asm_file, "w");
        
    if (!f_out) {
        fprintf(stderr, "Error: could not create output file '%s'\n", asm_file);
        fclose(f);
        status = 1;
        return status;
    }
        
    yyin = f;
    yyrestart(yyin);
    yyline = 1;
    root = NULL;
        
    if (yyparse() == 0) {
	printf("\n--- Abstract Syntax Tree ---\n");
        print_stm(root, 0);
        printf("\n--- Type Checking ---\n");

        Hash_table t = empty_table();
        if (checkStm(t, root)) {
	    printf("Type checking passed\n");
        } else {
             printf("Type checking failed\n");
             fclose(f);
             fclose(f_out);
             return 1;
        }
            
        printf("\n--- Intermediate Code ---\n");
        Hash_table symbol_table = empty_table();
        InstrList icode = compileStm(symbol_table, root);
        printListInstr(icode);
            
        printf("\n--- MIPS Assembly Code ---\n");
        printf("(Writing to %s)\n", asm_file);
        print_mips(f_out, icode);
            
        printf("Successfully generated %s\n", asm_file);
     } else {
        fprintf(stderr, "Parse error in %s\n", path);
        return 1;
     }
    fclose(f);
    fclose(f_out);
    
    printf("\n==================== Compilation Complete ====================\n\n");
    return status;
}
