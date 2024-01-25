/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include "my.h"
#include "sokoban.h"

//stty sane reset terminal affichage

static void condi_bad_char(map_t *map_info, int i, int j)
{
    if (map_info->map[i][j] != 'P'
        && map_info->map[i][j] != 'X' && map_info->map[i][j] != '#'
        && map_info->map[i][j] != 'O' && map_info->map[i][j] != ' ') {
        write(2, &map_info->map[i][j], 1);
        my_putstr_error(" isn't allowed in map.\nDo './my_sokoban -h'\n");
        exit(84);
    }
}

static void bad_char(map_t *map_info)
{
    for (int i = 0; map_info->map[i] != NULL; i++) {
        for (int j = 0; map_info->map[i][j] != '\0'; j++) {
            condi_bad_char(map_info, i, j);
        }
    }
}

int check_error(map_t *map_info)
{
    struct stat s;
    int fd = open(map_info->av[1], O_RDONLY);

    if (fd != - 1 && stat(map_info->av[1], &s) != -1) {
        if (s.st_size <= 0)
            exit(84);
        map_info->buffer = malloc(sizeof(char) * (s.st_size + 1));
        read(fd, map_info->buffer, s.st_size);
        map_info->buffer[s.st_size] = '\0';
        map_info->map = my_str_to_word_array(map_info->buffer);
    } else {
        my_putstr_error("argument is not a file or directory\n");
        exit(84);
    }
    bad_char(map_info);
    return 1;
}

static int find_player_and_do(map_t *map_info, char ch, int *i, int *j)
{
    if (map_info->map[*i][*j] == 'P') {
        if (ch == 2)
            move_down(map_info, i, *j);
        if (ch == 3)
            move_up(map_info, *i, *j);
        if (ch == 5)
            move_right(map_info, *i, j);
        if (ch == 4)
            move_left(map_info, *i, *j);
        if (ch == ' ') {
            free(map_info->map);
            map_info->map = my_str_to_word_array(map_info->buffer);
        }
    }
    return 0;
}

void print_map_when_lose(map_t *map_info, char ch)
{
    for (int i = 0; map_info->map[i] != NULL; i++) {
        for (int j = 0; map_info->map[i][j] != '\0'; j++) {
            find_player_and_do(map_info, ch, &i, &j);
        }
    }
}

int main_game(map_t *map_info)
{
    char ch = getch();

    map_info->moved = ch;
    for (int i = 0; map_info->map[i] != NULL; i++) {
        for (int j = 0; map_info->map[i][j] != '\0'; j++)
            find_player_and_do(map_info, ch, &i, &j);
    }
    if (show_sol_and_check_win(map_info))
        return 1;
    if (check_lose(map_info))
        return -1;
    return 0;
}

static void print_start(map_t *map_info, char const *enlarge)
{
    if (LINES < map_info->nb_lines || COLS < map_info->biggest_line)
        mvprintw(LINES / 2, (COLS / 2 - (my_strlen(enlarge) / 2)), enlarge);
    else {
        clear();
        for (int i = 0; map_info->map[i] != NULL; i++) {
            printw("%s\n", map_info->map[i]);
        }
    }
}

static void init_start(map_t *map_info, char *const enlarge)
{
    if (map_info->ac != 2) {
        my_putstr_error("Please, enter only 1 argument\n");
        exit(84);
    }
    check_help(map_info);
    check_error(map_info);
    get_max(map_info);
    initscr();
    refresh();
    print_start(map_info, enlarge);
    keypad(stdscr, TRUE);
    noecho();
}

int print_game_change(map_t *map_info, char *const enlarge)
{
    if (LINES < map_info->nb_lines || COLS < map_info->biggest_line) {
        mvprintw(LINES / 2, (COLS / 2 - (my_strlen(enlarge) / 2)), enlarge);
    } else {
        for (int i = 0; map_info->map[i] != NULL; i++)
            printw("%s\n", map_info->map[i]);
        return main_game(map_info);
    }
    return 0;
}

int my_sokoban(int argc, char **argv)
{
    WINDOW *box;
    char enlarge[] = "Please, enlarge the screen size.";
    map_t map_info = init_struct(argc, argv);
    int win = 0;

    init_start(&map_info, enlarge);
    while (1) {
        clear();
        win = print_game_change(&map_info, enlarge);
        if (win == -1 || win == 1) {
            print_last_move(&map_info);
            break;
        }
        refresh();
    }
    endwin();
    free_map(&map_info);
    if (win == -1)
        exit(1);
    return 0;
}
