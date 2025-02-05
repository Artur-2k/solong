#include "so_long.h"
#include "stdbool.h"

typedef struct s_game
{
    // map stuff
    char **map;
    int height;
    int width;

    // player
    int x;
    int y;
    // game options
    int nColectables;

    
} t_game;

bool ParseInput(int ac, char **av)
{
    if (ac != 2) return (ft_putstr_fd("Bad args\n", 2) ,true); // solong av1 av2

    if (ft_strlen(av[1]) <= 4) (ft_putstr_fd("Bad args\n", 2) ,true); // .ber 

    // ola.ber0 len 7
    // 01234567 .ber i=7-4=3
    if (ft_strcmp(".ber", &av[1][ft_strlen(av[1]) - 4]))
        (ft_putstr_fd("Bad args\n", 2) ,true) // av1.ber

    return false; // all good
} 

bool CheckFile(char **av)
{
    // valid file
    int fd = open(av[1], O_RDONLY);
    if (fd < 0)
        return true;
    
    // can we read from it
    if (read(fd, NULL, 0) < 0)
        return true;

    close(fd);
    return false;
}

bool GetDimensions(int fd, t_game* game)
{
    int fd = open(filePath, O_RDONLY);
    if (fd < 0)
        return (ft_putstr_fd("Open error\n", 2), return true);
    
    char *line = get_next_line(fd);
    game->width = ft_strlen(line);
    if (game->width < 3) // min map width (1x1)
        return (ft_putstr_fd("Map error\n", 2), close(fd), return true);

    while (line)
    {
        game->height++;
        free(line);
        line = get_next_line(fd);
        int lineLen = ft_strlen(line);
        // compare len
        if (lineLen != game->width) return (ft_putstr_fd("Map error\n", 2), close(fd), return true);
    }

    close(fd);

    // min map height 
    if (game->height < 3) return (ft_putstr_fd("Map error\n", 2), return true);
    else return false;
}

bool ReadMapToBuffer(char *filePath, t_game *game)
{
    // Anything?, same width each row?, fetch dimensions
    if (GetDimensions(fd, game)) return (close(fd), reeturn true);

    game->map = (char**)malloc(sizeof(char*) * (game->height ));
    if (!game->map) return (ft_putstr_fd("Malloc error\n", 2), true);

    int fd = open(filePath, O_RDONLY);
    if (fd < 0)
        return (ft_putstr_fd("Open error\n", 2), free(game->map), return true);

    // is this correct? xd     
    for (int i = 0; i < game->height; i++)
        map[i] = get_next_line(fd);

    close(fd);
    return false; 
}

void FreeMap(t_game *game)
{
    for (int i = 0; i < game->height; i++)
    {
        if (game->map[i])
            free(game->map[i]);
    }
    if (game->map)
        free(game->map);
    return ;
}

bool CheckMap(t_game *game)
{
    bool hasPlayer = false;
    bool hasExit = false;

    for (int y = 0; y < game->height; y++)
    {
        for (int x = 0; x < game->width; x++)
        {
            if (!ft_strchr("PCE10\n", game->map[y][x]))
                return ((ft_putstr_fd("Map error\n", 2), FreeMap(game), return true));
            
            if (game->map[y][x] == 'P')
            {
                if (hasPlayer) // double player
                    return ((ft_putstr_fd("Map error\n", 2), FreeMap(game), return true));
                hasPlayer = true;
            }
            else if (game->map[y][x] == 'E')
            {
                if (hasExit) // double player
                    return ((ft_putstr_fd("Map error\n", 2), FreeMap(game), return true));
                hasExit = true;
            }
            else if (game->map[y][x] == 'C')
                game->nColectables++;
        }
    }
    if (!hasPlayer || !hasExit || !game->nColectables) 
        return ((ft_putstr_fd("Map error\n", 2), FreeMap(game), return true));
    else return false;
}

int main(int ac, char **av)
{
    // PARSE
    // no args, arg len, arg termination
    if (ParseInput(ac, av)) return 1;

    // Can open file and stuff
    if (CheckFile(av)) return 2;

    t_game game;
    // init to 0
    ft_memset(game, 0, sizeof(game));

    // check dimensions and store map
    if (ReadMapToBuffer(av[1], &game)) return 3;

    // check for exit, player, colectables and bad chars on the map
    if (CheckMap(av)) return 3;


    FreeMap(&game);
    return 0;
}