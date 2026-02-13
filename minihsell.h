#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef enum e_type {
    WORD,     
    PIPE,      
    REDIRECT, 
    ENV        
} t_type;

typedef struct s_token {
    char            *content;
    t_type          type;
    struct s_token  *next;
} t_token;