#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//cc main.c -lreadline

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

void add_list(t_token **list,t_token *token);
void add_token(t_token **list, char *word, char *type);
int handle_word(t_token **list, char *str);
int handle_redirect(t_token **tokens, char *str);
int handle_quotes(t_token **tokens, char *str);
t_token *lexer(char *input);
t_token	*ft_lstlast(t_token *lst);
t_token	*ft_lstlast(t_token *lst);