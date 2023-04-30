#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "helpers/includes.c"
#include "semantics/includes.c"

int output_c_file(char* destination)
{
    FILE* fp;

    fp = fopen(destination, "w");
    if(fp == NULL) {
        char message[256];
        sprintf("Failed to open %s", destination);
        perror(message);
        return EXIT_FAILURE;
    }

    statement a;
    a.comment = "This is a statement comment.";

    scope aa;
    aa.comment = "This is a scope comment.";
    add_statement_to_scope(&aa, &a);
    
    scope bb;
    bb.comment = "This is another scope comment.";
    add_statement_to_scope(&bb, &a);

    add_scope_to_scope(&aa, &bb);

    output_scope(fp, &aa);

    

    fclose(fp);
    return EXIT_SUCCESS;
}