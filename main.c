#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

void print(char *token, int start, int end)
{
  if (token[start] == '>')
    write(1,"GREAT -> ",9);
  else if (token[start] == '|')
    write(1,"PIPE -> ",8);
  else
    write(1,"WORD -> ",8);
  while (start < end)
  {
    write(1,&token[start],1);
    start++;
  }
  write(1,"\n",1);
}


int is_special(char *str, int i)
{
  if (str[i] == '>' && str[i + 1] == '>')
    {
      print(">>",0,2);
      return (1);
    }
  else if (str[i] == '<' && str[i + 1] == '<')
    {
      print("<<",0,2);
      return (1);
    }
  else if (str[i] == '>')
    print(">",0,1);
  else if (str[i] == '<')
    print("<",0,1);
  else if (str[i] == '|')
    print("|",0,1);
  return (0);  
}

int is_alfa(char c)
{
  if (c == '|'  || c == '>' || c == '<' || c == ' ' || c == '\t')
    return (0);
  return (1);    
}

void lexer(char *s)
{
  int i;
  int start;
  int token;
  
  i = 0;
  token = 0;
  while (s[i])
  {
    start = i;
    while (is_alfa(s[i]) && s[i])
    {
      token = 1;
      i++;
    }
    if (token)
    {
      print(s, start, i);
      token = 0;
    }
    if (s[i] == '|' || s[i] == '>' || s[i] == '<')
      i += is_special(s,i);
    if (!s[i])
      break;
    i++;  
  }
}

int main()
{
    char *line;

    while (1)
    {
        line = readline("$Mineshell -> ");
        if (!line)
            exit(0);
        if (line != "")    
            lexer(line);
        add_history(line);
        free(line);
    }
}