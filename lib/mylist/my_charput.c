/*
** EPITECH PROJECT, 2023
** my putchar
** File description:
** put charachter
*/

#include <unistd.h>
#include "mylist.h"

void my_charput(char c)
{
    write(1, &c, 1);
}
