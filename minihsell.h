#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef enum e_type {
    WORD,      
    PIPE,      
    APPEND,
    HEREDOC,
    REDIR_OUT,
    REDIR_IN,  
    ENV        
} t_type;

typedef struct s_token {
    char            *content;
    char          *type;
    struct s_token  *next;
} t_token;