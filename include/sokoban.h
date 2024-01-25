/*
** EPITECH PROJECT, 2023
** Libmy
** File description:
** Store libmy functions prototypes
*/
#ifndef MY_SOKOBAN_SOKOBAN_H
    #define MY_SOKOBAN_SOKOBAN_H
    #include <ncurses.h>
    #include <stdlib.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include <fcntl.h>

typedef struct pos {
    int x;
    int y;
} position_t;

typedef struct nodes {
    void *data;
    struct nodes *next;
} nodes_t ;

typedef struct map {
    int ac;
    char **av;
    char **map;
    char *buffer;
    int biggest_line;
    int nb_lines;

    int p_x;
    int p_y;
    int b_x;
    int b_y;
    int nb_solution;
    nodes_t *all_solution;
    int nb_box;
    nodes_t *all_crosses;
    int nb_blocked;
    char moved;
} map_t;

int main_game(map_t *);
int check_help(map_t *);
int check_error(map_t *map_info);
int my_sokoban(int argc, char **argv);
void free_map(map_t *map_info);
void print_map_when_lose(map_t *map_info, char ch);
void print_last_move(map_t *map_info);

map_t init_struct(int argc, char **argv);
void get_max(map_t *map_info);

int show_sol_and_check_win(map_t *map_info);
int check_lose(map_t *map_info);

int move_up(map_t *map_info, int i, int j);
int move_down(map_t *map_info, int *i, int j);
int move_left(map_t *map_info, int i, int j);
int move_right(map_t *map_info, int i, int *j);




#endif //MY_SOKOBAN_SOKOBAN_H
