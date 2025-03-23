#include <stdio.h>
#include <ctype.h>

typedef enum
{
    START,
    BUILD_NUM,
    BUILD_ID,
    STOP
} STATE;

STATE transition(STATE current_state, char transition_char)
{
    switch (current_state)
    {
    case START:
        if (isdigit(transition_char))
        {
            return BUILD_NUM;
        }
        else if (isalpha(transition_char))
        {
            return BUILD_ID;
        }
        else if (transition_char == '.')
        {
            return STOP;
        }
        break;
    case BUILD_NUM:
        if (isdigit(transition_char))
        {
            return BUILD_NUM;
        }
        else if (isspace(transition_char))
        {
            return START;
        }
        break;
    case BUILD_ID:
        if (isalpha(transition_char) || transition_char == '_' || isdigit(transition_char))
        {
            return BUILD_ID;
        }
        else if (isspace(transition_char))
        {
            return START;
        }
        break;
    default:
        return STOP;
    }
    return current_state;
}

int main()
{
    STATE current_state = START;
    char buffer[256];
    int indexBuffer = 0;
    char transition_char;

    printf("Enter the data: ");
    do
    {
        scanf("%c", &transition_char);

        if (transition_char != ' ' && transition_char != '\n')
        {
            printf("%c", transition_char);
        }
        current_state = transition(current_state, transition_char);

        if (current_state == BUILD_NUM)
        {
            buffer[indexBuffer++] = transition_char;
        }
        else if (current_state == BUILD_ID)
        {
            buffer[indexBuffer++] = transition_char;
        }

        if (current_state == START)
        {
            if (indexBuffer > 0)
            {
                buffer[indexBuffer] = '\0';
                if (isdigit(buffer[0]))
                {
                    printf(" - Number\n");
                }
                else
                {
                    printf(" - Identifier\n");
                }
                indexBuffer = 0;
            }
        }

    } while (current_state != STOP);

    printf("\nSTOP\n");
}
