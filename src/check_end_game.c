/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "my.h"
#include "sokoban.h"

//stty sane reset terminal affichage

void print_last_move(map_t *map_info)
{
    clear();
    for (int i = 0; map_info->map[i] != NULL; i++)
        printw("%s\n", map_info->map[i]);
    refresh();
}

void free_map(map_t *map_info)
{
    for (int i = 0; map_info->map[i] != NULL; i++)
        free(map_info->map[i]);
    free(map_info->map);
}

int show_sol_and_check_win(map_t *map_info)
{
    int i;
    int j;
    int box_on_sol = 0;

    for (nodes_t *temp = map_info->all_solution;
        temp != NULL; temp = temp->next) {
        i = ((position_t *)temp->data)->x;
        j = ((position_t *)temp->data)->y;
        if (map_info->map[i][j] != 'X'
            && map_info->map[i][j] != 'P')
            map_info->map[i][j] = 'O';
        if (map_info->map[i][j] == 'X') {
            box_on_sol += 1;
        }
    }
    if (box_on_sol == map_info->nb_solution)
        return 1;
    return 0;
}

static int check_bd(map_t *map_info, int i, int j)
{
    if (i + 1 < map_info->nb_lines
        && j < my_strlen(map_info->map[i + 1])
        && map_info->map[i + 1][j] != '\0') {
        if (map_info->map[i + 1][j] == '#'
            || map_info->map[i + 1][j] == 'X') {
            return 1;
        }
    }
    return 0;
}

static int check_br(map_t *map_info, int i, int j)
{
    if (map_info->map[i][j + 1] != '\0') {
        if (map_info->map[i][j + 1] == '#'
            || map_info->map[i][j + 1] == 'X') {
            return 1;
        }
    }
    return 0;
}

static int check_bl(map_t *map_info, int i, int j)
{
    if (map_info->map[i][j - 1] != '\0') {
        if (map_info->map[i][j - 1] == '#'
            || map_info->map[i][j - 1] == 'X') {
            return 1;
        }
    }
    return 0;
}

static int check_bu(map_t *map_info, int i, int j)
{
    if (i - 1 >= 0 && j < my_strlen(map_info->map[i - 1])
        && map_info->map[i - 1][j] != '\0') {
        if (map_info->map[i - 1][j] == '#'
        || map_info->map[i - 1][j] == 'X') {
            return 1;
        }
    }
    return 0;
}

static int count_box_blocked(map_t *map_info, int i, int j)
{
    if (map_info->map[i][j] == 'X') {
        if ((check_bd(map_info, i, j) && check_br(map_info, i, j))
            || (check_bu(map_info, i, j) && check_br(map_info, i, j))
            || (check_bd(map_info, i, j) && check_bl(map_info, i, j))
            || (check_bu(map_info, i, j) && check_bl(map_info, i, j))) {
            map_info->nb_blocked += 1;
        }
    }
    return 0;
}

int check_lose(map_t *map_info)
{
    map_info->nb_blocked = 0;
    for (int i = 0; map_info->map[i] != NULL; i ++) {
        for (int j = 0; map_info->map[i][j] != '\0'; j++)
            count_box_blocked(map_info, i, j);
    }
    if (map_info->nb_box == map_info->nb_blocked) {
        return (1);
    }
    return 0;
}
