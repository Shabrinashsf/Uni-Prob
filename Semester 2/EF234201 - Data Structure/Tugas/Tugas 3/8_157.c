#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct
{
    int top;
    char items[MAX];
} Stack;

void init(Stack *s)
{
    s->top = -1;
}

int isEmpty(Stack *s)
{
    return s->top == -1;
}

char peek(Stack *s)
{
    return s->items[s->top];
}

void push(Stack *s, char c)
{
    if (s->top < MAX - 1)
    {
        s->items[++(s->top)] = c;
    }
}

char pop(Stack *s)
{
    if (!isEmpty(s))
    {
        return s->items[s->top--];
    }
    return '\0';
}

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

void infixToPostfix(char *infix, char *postfix)
{
    Stack s;
    init(&s);
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++)
    {
        char token = infix[i];

        if (isdigit(token))
        {
            postfix[j++] = token;
        }
        else if (token == '(')
        {
            push(&s, token);
        }
        else if (token == ')')
        {
            while (!isEmpty(&s) && peek(&s) != '(')
            {
                postfix[j++] = pop(&s);
            }
            pop(&s); // Hapus '(' dari stack
        }
        else
        {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(token))
            {
                postfix[j++] = pop(&s);
            }
            push(&s, token);
        }
    }

    while (!isEmpty(&s))
    {
        postfix[j++] = pop(&s);
    }
    postfix[j] = '\0';
}

int main()
{
    char infix[MAX] = "(2+3)*(8/4)-6";
    char postfix[MAX];

    infixToPostfix(infix, postfix);
    printf("Postfix: %s\n", postfix);

    return 0;
}
