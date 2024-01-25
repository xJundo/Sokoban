/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "my.h"
#include "sokoban.h"

//stty sane reset terminal affichage

static int move_up_box(map_t *map_info)
{
    int i = map_info->p_x - 1;
    int j = map_info->p_y;

    if (i - 1 > 0
        && j < my_strlen(map_info->map[i - 1])
        && map_info->map[i - 1][j] != '\0'
        && map_info->map[i - 1][j] != '#'
        && map_info->map[i - 1][j] != 'X') {
        map_info->b_x = i;
        map_info->b_y = j;
        map_info->map[i][j] = ' ';
        map_info->map[map_info->b_x - 1][map_info->b_y] = 'X';
        return 0;
    }
    return 1;
}

int move_up(map_t *map_info, int i, int j)
{
    if (i - 1 > 0 && j < my_strlen(map_info->map[i - 1])
        && map_info->map[i - 1][j] != '\0'
        && map_info->map[i - 1][j] != '#') {
        map_info->p_x = i;
        map_info->p_y = j;
        if (map_info->map[i - 1][j] == 'X' && move_up_box(map_info) == 1)
            return 1;
        map_info->map[i][j] = ' ';
        map_info->map[map_info->p_x - 1][map_info->p_y] = 'P';
        return 1;
        }
    return 0;
}

static int move_down_box(map_t *map_info)
{
    int i = map_info->p_x + 1;
    int j = map_info->p_y;

    if (i + 1 < map_info->nb_lines
        && j < my_strlen(map_info->map[i + 1])
        && map_info->map[i + 1][j] != '\0'
        && map_info->map[i + 1][j] != '#'
        && map_info->map[i + 1][j] != 'X') {
        map_info->b_x = i;
        map_info->b_y = j;
        map_info->map[i][j] = ' ';
        map_info->map[map_info->b_x + 1][map_info->b_y] = 'X';
        return 0;
    }
    return 1;
}

int move_down(map_t *map_info, int *i, int j)
{
    if (*i + 1 < map_info->nb_lines
        && j < my_strlen(map_info->map[*i + 1])
        && map_info->map[*i + 1][j] != '\0'
        && map_info->map[*i + 1][j] != '#') {
        map_info->p_x = *i;
        map_info->p_y = j;
        if (map_info->map[*i + 1][j] == 'X'
        && move_down_box(map_info) == 1)
            return 1;
        map_info->map[*i][j] = ' ';
        map_info->map[map_info->p_x + 1][map_info->p_y] = 'P';
        *i += 1;
        return 1;
    }
    return 0;
}

static int move_left_box(map_t *map_info)
{
    int i = map_info->p_x;
    int j = map_info->p_y - 1;

    if (map_info->map[i][j - 1] != '\0'
        && map_info->map[i][j - 1] != '#'
        && map_info->map[i][j - 1] != 'X') {
        map_info->b_x = i;
        map_info->b_y = j;
        map_info->map[i][j] = ' ';
        map_info->map[map_info->b_x][map_info->b_y - 1] = 'X';
        return 0;
    }
    return 1;
}

int move_left(map_t *map_info, int i, int j)
{
    if (map_info->map[i][j - 1] != '\0'
        && map_info->map[i][j - 1] != '#') {
        map_info->p_x = i;
        map_info->p_y = j;
        if (map_info->map[i][j - 1] == 'X'
            && move_left_box(map_info) == 1)
            return 1;
        map_info->map[i][j] = ' ';
        map_info->map[map_info->p_x][map_info->p_y - 1] = 'P';
        return 1;
    }
    return 0;
}

static int move_right_box(map_t *map_info)
{
    int i = map_info->p_x;
    int j = map_info->p_y + 1;

    if (map_info->map[i][j + 1] != '\0'
        && map_info->map[i][j + 1] != '#'
        && map_info->map[i][j + 1] != 'X') {
        map_info->b_x = i;
        map_info->b_y = j;
        map_info->map[i][j] = ' ';
        map_info->map[map_info->b_x][map_info->b_y + 1] = 'X';
        return 0;
    }
    return 1;
}

int move_right(map_t *map_info, int i, int *j)
{
        if (map_info->map[i][*j + 1] != '\0' &&
            map_info->map[i][*j + 1] != '#') {
            map_info->p_x = i;
            map_info->p_y = *j;
            if (map_info->map[i][*j + 1] == 'X'
            && move_right_box(map_info) == 1)
                return 1;
            map_info->map[i][*j] = ' ';
            map_info->map[map_info->p_x][map_info->p_y + 1] = 'P';
            *j += 1;
            return 1;
    }
    return 0;
}
