#include "minihsell.h"

void add_token(t_token **list, char *word, char *type)
{
  t_token *token = malloc(sizeof(t_token));

  token -> content = strdup(word);
  token -> type = type;
  token -> next = NULL;
  add_list(list, token);
}

int handle_word(t_token **tokens, char *str)
{
    int i = 0;
    int start = 0;
    char *word;

    while (str[i] && !strchr(" |<>", str[i]))
    {
        if (str[i] == '\'' || str[i] == '\"')
        {
            i += find_quote_end(&str[i], str[i]);
        }
        else
            i++;
    }
    word = strndup(str, i);
    add_token(tokens, word, "WORD");
    free(word);
    return (i);
}

int handle_redirect(t_token **tokens, char *str)
{
  int i;
  char *word;
  
  i = 0;
  if (str[i] == '>' && str[i + 1] == '>')
  {
    word = strndup(str, (i + 2));
    add_token(tokens, word, "APPEND");
    return (2);
  }
  else if (str[i] == '<' && str[i + 1] == '<')
  {
    word = strndup(str, (i + 2));
    add_token(tokens, word, "HEREDOC");
    return (2);
  }
  else if (str[i] == '>')
  {
    word = strndup(str, (i + 1));
    add_token(tokens, word, "REDIR_OUT");
  }
  else if (str[i] == '<')
  {
    word = strndup(str, (i + 1));
    add_token(tokens, word, "REDIR_IN");
  }
  free(word);
  return (i + 1);
}

int find_quote_end(char *str, char quote)
{
    int i = 1;
    while (str[i] && str[i] != quote)
        i++;
    if (str[i] == quote)
        return (i + 1);
    return (i);
}

void print_tokens(t_token *list)
{
  int i;

  i = 0;
  if (!list)
  {
    printf("Lista vazia!\n");
    return;
  }
  while (list != NULL)
  {
    printf("%s = ",list -> type);
    printf("%s\n",list -> content );
    list = list->next; 
    i++;
  }
}

t_token *lexer(char *input) 
{
    int i = 0;
    t_token *tokens = NULL;

    while (input[i]) 
    {
        while (input[i] && (input[i] == ' ' || (input[i] >= 9 && input[i] <= 13)))
            i++; 
        if (!input[i]) break;

        if (input[i] == '|')
        {
            add_token(&tokens, "|", "PIPE");
            i++;
        }
        else if (input[i] == '>' || input[i] == '<')
            i += handle_redirect(&tokens, &input[i]);
        else
            i += handle_word(&tokens, &input[i]);
    }
    return (tokens);
}

void add_list(t_token **list,t_token *token)
{
  t_token *last;

  if (!token) 
        return;
  if (*list == NULL)
  {
    *list = token;
    return;
  }
  last = ft_lstlast(*list);
  last -> next = token;
}

t_token	*ft_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*
***************************
$Mine -> 'aaa'sss|"ss"
WORD = 'aaa'sss|
WORD = "ss"
*/

int main(int argc, char *argv[], char *envp[])
{
    char *line;
    t_token *tokens_list;
    while (1)
    {
        line = readline("$Mine -> ");
        if (!line)
            exit(0);   
        tokens_list = lexer(line);
        add_history(line);
        print_tokens(tokens_list);
        handle_expansion(tokens_list);
        free(line);
    }
}


void handle_expansion(t_token *list)
{
  while (list != NULL)
  {
    if (strchr(list -> content,'$'))
    {
     //TODO
    }
    list = list->next; 
  }
}

/*
void expansion(char *token_content)
{
  int i;
  int quotes;

  quotes = 0;
  i = 0;
  while (token_content[i])
  {
    if (token_content[i] == '\'')
      quotes = 1;
    else if (token_content[i] == '\"')
      quotes = 2;

  }
  
}
  */