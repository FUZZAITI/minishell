#include "minihsell.h"

t_token *new_token(t_token_type type, char *token, int start, int end)
{
    t_token *node;
    int      i;
    int      len;

    len = end - start;
    node = malloc(sizeof(t_token));
    node->type = type;
    node->value = malloc(len + 1);
    i = 0;
    while (i < len)
    {
        node->value[i] = token[start + i];
        i++;
    }
    node->value[i] = '\0';
    node->next = NULL;

    return (node);
}