typedef struct s_statement
{
    //what can a statement have?
    /*
    optional comment

    function calls
    operators
    declarations

    optional newline afterwards
    */

    char* comment;

    int has_newline;
}statement;

void output_statement(FILE* fp, statement* s)
{
    if(s->comment)
        fprintf(fp, "/*%s*/\n", s->comment);



    if(s->has_newline)
        fprintf(fp, "\n");
}