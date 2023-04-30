enum
{
    STATEMENT,
    SCOPE
};

#define FLIP_MODE(mode) mode = !mode 

typedef struct s_statement_list statement_list;
typedef struct s_scope scope;
typedef struct s_scope_list scope_list;

struct s_statement_list {
    statement** list;
    uint32_t count;
    uint32_t size;
};

void add_statement_to_list(statement_list* s, statement* target)
{
    //resize list

    s->list[s->size++] = target;

    if(target != NULL) s->count++;
}

struct s_scope_list {
    scope** list;
    uint32_t count;
    uint32_t size;
};

void add_scope_to_list(scope_list* s, scope* target)
{
    //resize list


    s->list[s->size++] = target;

    if(target != NULL) s->count++;
}

struct s_scope {
    char* comment;

    statement_list statements;
    scope_list scopes;

    char active_list;
};

void add_statement_to_scope(scope* s, statement* target)
{
    if(s->active_list == SCOPE)
        add_statement_to_list(&(s->scopes), NULL);

    add_statement_to_list(&(s->statements), target);
    s->active_list = STATEMENT;
}

void add_scope_to_scope(scope* s, scope* target)
{
    if(s->active_list == STATEMENT)
        add_statement_to_list(&(s->statements), NULL);

    add_scope_to_list(&(s->scopes), target);
    s->active_list = SCOPE;
}

void output_scope(FILE* fp, scope* s)
{
    if(s->comment)
        fprintf(fp, "/*%s*/\n", s->comment);

    fprintf(fp, "\n{\n");

    uint32_t statement_counter = 0;
    uint32_t scope_counter = 0;
    char reading_mode = STATEMENT;
    while(statement_counter <= s->statements.size && scope_counter <= s->scopes.size)
    {
        if(reading_mode = STATEMENT)
        {
            //reading statements
            if(s->statements.list)
            {
                output_statement(fp, s->statements.list[statement_counter]);
                statement_counter++; continue;
            }
            else
            {
                statement_counter++; FLIP_MODE(reading_mode); continue;
            }
        }
        else
        {
            //reading scopes
            if(s->scopes.list)
            {
                output_scope(fp, s->scopes.list[scope_counter]);
                scope_counter++; continue;
            }
            else
            {
                scope_counter++; FLIP_MODE(reading_mode); continue;
            }
        }
    }

    fprintf(fp, "\n}\n");
}