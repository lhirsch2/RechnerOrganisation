#include<stdio.h>

int i;
int X;
int digit = 0;
int buffer[16] = {0};
int* buffer_ptr = buffer;
int halt = 0;
int plus = 9999;
int multiplyer = 8888;
int newline = 7777;
int temp = 0;
int temp2 = 0;

void my_getchar()
{
    i = getchar();
}

void my_printf(int* value, int nl)
{
    printf("%d", *value);
    if (nl) printf("%d", newline);
}

void convert()
{
    if(digit) //X *= 10;
    {
        temp = 10;
        temp2 = X;
        temp -= 1;
        while (temp>0)
        {
            X += temp2;
            temp--;
        }
    }
    else X = 0;
    X = X + (i - 0x30);
    digit = 1;
}

void save()
{
    *buffer_ptr++ = X;
    digit = 0;
}

void add()
{
    X += *--buffer_ptr;
}

void multiply()
{
    temp = *--buffer_ptr;
    temp2 = X;
    temp -= 1;
    while (temp>0)
    {
        X += temp2;
        temp--;
    }
}

void check_char()
{
    int result_ctrl;
    int number_ctrl;
    int nl_ctrl;

    if (i==EOF)
    {
        my_printf(&newline, 0);
        halt = 1;
    }
    else if (i > 0x2f & i < 0x3a)
    {
        convert();
        number_ctrl = 1;
    }
    else if (i==0x0a)
    {
        save();
        if (result_ctrl == 0) my_printf(&X, 1);
        else my_printf(&newline, 0);
        result_ctrl = 0;
        number_ctrl = 0;
        nl_ctrl = 1;
    }
    else if (i==0x2b)
    {
        if (number_ctrl>0) my_printf(&X, 0);
        my_printf(&plus, 1);
        add();
        my_printf(&X, 0);
        result_ctrl = 1;
        nl_ctrl = 0;
        number_ctrl = 0;
    }
    else if (i==0x2a)
    {
        if (number_ctrl>0) my_printf(&X, 0);
        my_printf(&multiplyer, 1);
        multiply();
        my_printf(&X, 0);
        result_ctrl = 1;
        nl_ctrl = 0;
        number_ctrl = 0;
    }
}

int main()
{
A00:my_getchar();
    check_char();
    if (halt==0) goto A00;
    return 0;
}