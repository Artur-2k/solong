# include "mlx.h"
# include "../lib/minilibx-linux/mlx_int.h"
# include <X11/keysym.h>
# include "libft.h"

#include "stdbool.h"
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdarg.h>
# include <limits.h>

#define HEIGHT 800
#define WIDTH 600
#define TSIZE 32

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

    // mlx stuff
    void *mlx_ptr;
    void *win_ptr;
    void *img_ptr;
    char *img_addr;
    int line_len;
    int endina;
    int bpp;
} t_game;

bool ParseInput(int ac, char **av)
{
    if (ac != 2) return (ft_putstr_fd("Bad args\n", 2) ,true); // solong av1 av2

    if (ft_strlen(av[1]) <= 4) return (ft_putstr_fd("Bad args\n", 2), true); // .ber 

    // ola.ber0 len 7
    // 01234567 .ber i=7-4=3
    if (ft_strncmp(".ber", &av[1][ft_strlen(av[1]) - 4], 4))
        return (ft_putstr_fd("Bad args\n", 2), true); // av1.ber

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

// this because getnextline gives still reachable if we stop mid reading for some reason
void    finishReading(int fd)
{
    char *line;
    while(true)
    {
        line =get_next_line(fd);
        if (line)
            free(line);
        else
            break ;
    }
}

bool GetDimensions(char *filePath, t_game* game)
{
    int fd = open(filePath, O_RDONLY);
    if (fd < 0)
        return (ft_putstr_fd("Open error\n", 2), true);
    
    char *line = get_next_line(fd);
    if (!line) return (ft_putstr_fd("Error\n", 2), close(fd), true);
    game->width = ft_strlen(line);
    if (line[game->width - 1] == '\n')
    {
        game->width--; // remove the \n from width
        line[game->width] = '\0'; // trim the nl
    }

    if (game->width < 3) // min map width (1x1)
        return (ft_putstr_fd("Map error\n", 2),free(line),finishReading(fd), close(fd), true);

    while (true)
    {
        game->height++;
        free(line);
        line = get_next_line(fd);
        if (!line) break;
        int lineLen = ft_strlen(line);
        if (line[lineLen - 1] == '\n')
        {
            lineLen--;
            line[lineLen] = '\0'; // trim the nl
        } 
        // compare len
        if (lineLen != game->width) return (ft_putstr_fd("Map error2\n", 2), free(line), finishReading(fd), close(fd), true);
    }

    close(fd);

    // min map height 
    if (game->height < 3) return (ft_putstr_fd("Map error\n", 2), true);
    else return false;
}

bool ReadMapToBuffer(char *filePath, t_game *game)
{
    // Anything?, same width each row?, fetch dimensions
    if (GetDimensions(filePath, game)) return true;

    game->map = (char**)malloc(sizeof(char*) * (game->height ));
    if (!game->map) return (ft_putstr_fd("Malloc error\n", 2), true);

    int fd = open(filePath, O_RDONLY);
    if (fd < 0)
        return (ft_putstr_fd("Open error\n", 2), free(game->map), true);

    // is this correct? xd     
    for (int i = 0; i < game->height; i++)
        game->map[i] = get_next_line(fd);

    close(fd);
    return false; 
}

void FreeMap(char **map, int height)
{
    for (int i = 0; i < height; i++)
    {
        if (map[i])
            free(map[i]);
    }
    if (map)
        free(map);
    return ;
}

bool CheckMapContents(t_game *game)
{
    bool hasPlayer = false;
    bool hasExit = false;

    for (int y = 0; y < game->height; y++)
    {
        for (int x = 0; x < game->width; x++)
        {
            if (!ft_strchr("PCE10\n", game->map[y][x]))
                return ((ft_putstr_fd("Map error\n", 2), FreeMap(game->map, game->height), true));
            
            if (game->map[y][x] == 'P')
            {
                if (hasPlayer) // double player
                    return ((ft_putstr_fd("Map error\n", 2), FreeMap(game->map, game->height), true));
                game->map[y][x] = '0'; // clear for renderer
                game->x = x; // fetch for renderer
                game->y = y; // fetch for renderer
                hasPlayer = true;
            }
            else if (game->map[y][x] == 'E')
            {
                if (hasExit) // double exit
                    return ((ft_putstr_fd("Map error\n", 2), FreeMap(game->map, game->height), true));
                hasExit = true;
            }
            else if (game->map[y][x] == 'C')
                game->nColectables++;
        }
    }
    if (!hasPlayer || !hasExit || !game->nColectables) 
        return ((ft_putstr_fd("Map error\n", 2), FreeMap(game->map, game->height), true));
    else return false;
}

bool FloodFill(char **map, t_game *game, int y, int x, char to_fill)
{
    if (x < 0 || y < 0 || y >= game->height || x >= game->width)
        return true; // if out of bounds === map not closed

    if (map[y][x] != to_fill && !ft_strchr("ECP", map[y][x])) // wall
        return false;
    
    map[y][x] = 'x'; // 0s in the game->map will become F!!!

    bool edge = false;
    edge |= FloodFill(map, game, y, x - 1, to_fill);
    edge |= FloodFill(map, game, y, x + 1, to_fill);
    edge |= FloodFill(map, game, y - 1, x, to_fill);
    edge |= FloodFill(map, game, y + 1, x, to_fill);
    return edge;
}

static bool CheckMapClosed(t_game *game)
{
    char **mapCopy = malloc(sizeof(char *) * game->height);
    //todo error checking
    for (int i = 0; i < game->height; i++)
    {
        mapCopy[i] = ft_strdup(game->map[i]);
        //todo error checking
    }
    bool passedTest = FloodFill(mapCopy, game, game->y, game->x, '0'); 
    FreeMap(mapCopy, game->height);
    return (passedTest);
}


// dst => the address of the pixels in memory
// we adjust the offset of the with our x,y coords of the pixel along with the
// line_len and the bpp and just apply to that pixel the respective color
void	put_pixel_to_img(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
	{
		dst = game->img_addr + (y * game->line_len + x * (game->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

// Draws a filled square at (x, y) with TILE_SIZE
void draw_square(t_game *game, int x, int y, int color) {
    int i, j;
    
    for (i = 0; i < TSIZE; i++) {
        for (j = 0; j < TSIZE; j++) {
            put_pixel_to_img(game, x + j, y + i, color);
        }
    }
}

// Renders the map
void RenderMap(t_game *game)
{
    for (int y = 0; y < game->height; y++)
    {
        for (int x = 0; x < game->width; x++) 
        {
            if (game->map[y][x] == '1')
                draw_square(game, x * (TSIZE + 1), y * (TSIZE + 1), 0x0000FF); // wall
            else if (game->map[y][x] == 'C')
                draw_square(game, x * (TSIZE + 1), y * (TSIZE + 1), 0x00FFFF); // colectable
            else if (game->map[y][x] == 'E')
                draw_square(game, x * (TSIZE + 1), y * (TSIZE + 1), 0xFFFF00); // Exit
            else
                draw_square(game, x * (TSIZE + 1), y * (TSIZE + 1), 0xFFFFFF); // walkable space
        }
    }

    // Draw Player
    draw_square(game, game->x * (TSIZE + 1), game->y * (TSIZE + 1), 0xFF00FF); // player

}

int ExitGame(t_game *game)
{
   	if (game->map)
		FreeMap(game->map, game->height);
	if (game->img_ptr)
		mlx_destroy_image(game->mlx_ptr, game->img_ptr);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
    exit (0);
}

void MoveUp(t_game *game)
{
    int newY = game->y - 1;
    if (newY < 0 || newY >= game->height) return ;

    if (game->map[newY][game->x] == '1' || 
        game->map[newY][game->x] == '\n' || 
        game->map[newY][game->x] == '\0')
        return ;
    
    game->y--;
    // todo moves print here
    if (game->map[game->y][game->x] == 'C')
    {
        game->nColectables--;
        game->map[game->y][game->x] = '0';
    }
    else if (game->map[game->y][game->x] == 'E')
    {
        if (game->nColectables == 0)
        {
            ft_putstr_fd("YOU WIN\n", 1);
            ExitGame(game);
        }
    }
}
void MoveDown(t_game *game)
{
    int newY = game->y + 1;
    if (newY < 0 || newY >= game->height) return ;

    if (game->map[newY][game->x] == '1' || 
        game->map[newY][game->x] == '\n' || 
        game->map[newY][game->x] == '\0')
        return ;
    
    game->y++;
    // todo moves print here
    if (game->map[game->y][game->x] == 'C')
    {
        game->nColectables--;
        game->map[game->y][game->x] = '0';
    }
    else if (game->map[game->y][game->x] == 'E')
    {
        if (game->nColectables == 0)
        {
            ft_putstr_fd("YOU WIN\n", 1);
            ExitGame(game);
        }
    }
}
void MoveRight(t_game *game)
{
    int newX = game->x + 1;
    if (newX < 0 || newX >= game->width) return ;

    if (game->map[game->y][newX] == '1' || 
        game->map[game->y][newX] == '\n' || 
        game->map[game->y][newX] == '\0')
        return ;
    
    game->x++;
    // todo moves print here
    if (game->map[game->y][game->x] == 'C')
    {
        game->nColectables--;
        game->map[game->y][game->x] = '0';
    }
    else if (game->map[game->y][game->x] == 'E')
    {
        if (game->nColectables == 0)
        {
            ft_putstr_fd("YOU WIN\n", 1);
            ExitGame(game);
        }
    }
}
void MoveLeft(t_game *game)
{
    int newX = game->x - 1;
    if (newX < 0 || newX >= game->width) return ;

    if (game->map[game->y][newX] == '1' || 
        game->map[game->y][newX] == '\n' || 
        game->map[game->y][newX] == '\0')
        return ;
    
    game->x--;
    // todo moves print here
    if (game->map[game->y][game->x] == 'C')
    {
        game->nColectables--;
        game->map[game->y][game->x] = '0';
    }
    else if (game->map[game->y][game->x] == 'E')
    {
        if (game->nColectables == 0)
        {
            ft_putstr_fd("YOU WIN\n", 1);
            ExitGame(game);
        }
    }
}

int ReadKeys(int key, t_game *game)
{
    if ((key == XK_w || key == XK_W) && game->y > 0)
        MoveUp(game);
    if ((key == XK_s || key == XK_S)  && game->y < game->height - 1)
        MoveDown(game);
    if ((key == XK_a || key == XK_A)  && game->x > 0)
        MoveLeft(game);
    if ((key == XK_d || key == XK_D)  && game->y > 0)
        MoveRight(game);
    if (key == XK_Escape)
        ExitGame(game);
    
    
    RenderMap(game);
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_ptr, 0, 0);
    mlx_destroy_image(game->mlx_ptr, game->img_ptr);
    game->img_ptr = mlx_new_image(game->mlx_ptr, WIDTH, HEIGHT);
    game->img_addr = mlx_get_data_addr(game->img_ptr, &game->bpp, &game->line_len, &game->endina);
    return 0;
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
    ft_memset(&game, 0, sizeof(game));

    // check dimensions and store map
    if (ReadMapToBuffer(av[1], &game)) return 3;

    // check for exit, player, colectables and bad chars on the map
    if (CheckMapContents(&game)) return 4;

    if (CheckMapClosed(&game)) return 5;

    // MINILIBX
    game.mlx_ptr = mlx_init();
    // todo error check
    game.win_ptr = mlx_new_window(game.mlx_ptr, WIDTH, HEIGHT, "so long");
    //todo error check
    game.img_ptr = mlx_new_image(game.mlx_ptr, WIDTH, HEIGHT);
    //todo error check
    game.img_addr = mlx_get_data_addr(game.img_ptr, &game.bpp, &game.line_len, &game.endina);
    //todo error check

    // Draw map
    RenderMap(&game);

    mlx_hook(game.win_ptr, DestroyNotify, 1L << 0, ExitGame, &game);
    mlx_key_hook(game.win_ptr, ReadKeys, &game);
    mlx_loop(game.mlx_ptr);

    return 0;
}