#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

typedef enum e_token_type
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,     
    TOKEN_REDIR_OUT,    
    TOKEN_APPEND,       
    TOKEN_HEREDOC       
}   t_token_type;

typedef struct s_token
{
    t_token_type      type;
    char              *value;   
    struct s_token    *next;
}   t_token;