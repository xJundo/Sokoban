/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "my.h"
#include "sokoban.h"

//stty sane reset terminal affichage


int check_help(map_t *map)
{
    if (my_strcmp(map->av[1], "-h") == 0) {
        my_printf("USAGE\n     ./my_sokoban map\nDESCRIPTION\n     map"
        "  file representing the warehouse map,"
        " containing ‘#’ for walls,\n          ‘P’ for the player,"
        " ‘X’ for boxes and ‘O’ for storage locations.\n");
        exit(0);
    }
    return 0;
}

map_t init_struct(int argc, char **argv)
{
    map_t mapinfo = {0};

    mapinfo.ac = argc;
    mapinfo.av = argv;
    return mapinfo;
}

void add_in_list(nodes_t **liste, void *data)
{
    nodes_t *new = malloc(sizeof(nodes_t));

    new->data = data;
    new->next = *liste;
    *liste = new;
}

static void count_x(map_t *map_info, int i, int j)
{
    position_t *pos;

    if (map_info->map[i][j] == 'X') {
        map_info->nb_box += 1;
        pos = malloc(sizeof(position_t));
        pos->x = i;
        pos->y = j;
        add_in_list(&map_info->all_crosses, pos);
    }
}

void get_coord_x_and_o(map_t *map_info, int i)
{
    position_t *pos;

    for (int j = 0; map_info->map[i][j] != '\0'; j++) {
        if (map_info->map[i][j] == 'O') {
            map_info->nb_solution += 1;
            pos = malloc(sizeof(position_t));
            pos->x = i;
            pos->y = j;
            add_in_list(&map_info->all_solution, pos);
        }
        count_x(map_info, i, j);
    }
}

void get_max(map_t *map_info)
{
    map_info->biggest_line = my_strlen(map_info->map[0]);
    for (int i = 0; map_info->map[i] != NULL; i++) {
        map_info->biggest_line =
        my_strlen(map_info->map[i]) > map_info->biggest_line
        ? my_strlen(map_info->map[i]) : map_info->biggest_line;
        map_info->nb_lines = i + 1;
    }
    for (int i = 0; map_info->map[i] != NULL; i++) {
        get_coord_x_and_o(map_info, i);
    }
    if (map_info->nb_box < map_info->nb_solution)
        exit(84);
}
