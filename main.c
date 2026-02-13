#include "minihsell.h"

void add_token(t_token **list, char *word, char *type)
{
  t_token *token = malloc(sizeof(t_token));

  token -> content = word;
  token -> type = type;
  token -> next = NULL;
//  add_list(list, token);

   printf("%s = ",token -> type);
   printf("%s\n",token -> content );
}

int handle_word(t_token **list, char *str) 
{
    int i = 0;
    while (str[i] && !strchr(" |<>", str[i]))
        i++;
    
    char *word = strndup(str, i); 
    add_token(list, word, "WORD");
    free(word);
    return (i);
}
//while (str[i] && !strchr(" |<>\"'", str[i]))

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

int handle_quotes(t_token **tokens, char *str)
{
  int i;
  char *word;
  
  i = 1;
  while (str[i] && str[i] != str[0])
    i++; 
  if (str[i + 1] != ' ' && str[i + 1] != '|' && str[i + 1] != '<' && str[i + 1] != '>' && str[i + 1] != '\"' && str[i + 1] != '\'')
    i++; 
  while (str[i] && !strchr(" |<>\"'", str[i]))
        i++;  
  word = strndup(str, (i + 1)); 
  add_token(tokens, word, "WORD");
  free(word);
  return (i + 1);  
}

t_token *lexer(char *input) 
{
    int i = 0;
    t_token *tokens = NULL;

    while (input[i]) {
        while (input[i] == ' ' || (input[i] >= 9 && input[i] <= 13))
            i++; 

        if (input[i] == '|')
            add_token(&tokens, "|", "PIPE"), i++;
        else if (input[i] == '>' || input[i] == '<')
            i += handle_redirect(&tokens, &input[i]);
        else if (input[i] == '\'' || input[i] == '\"')
            i += handle_quotes(&tokens, &input[i]);
        else if (input[i])
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
void print_list(t_token **list)
{
  t_token *token;
  while (*list)
  {
    token = list;
    printf("%s = ",token -> type);
    printf("%s\n",token -> content);
  }
  
}
*/

int main()
{
    char *line;
    t_token *tokens_list;
    while (1)
    {
        line = readline("$Mine -> ");
        if (!line)
            exit(0);   
        lexer(line);
        add_history(line);
  //      print_list(tokens_list);
        free(line);
    }
}