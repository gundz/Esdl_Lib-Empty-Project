#include <easy_sdl.h>

#define SPEED 3
#define SIZE_X 50
#define SIZE_Y 50

typedef struct			s_data
{
	t_esdl				*esdl;
	SDL_Texture			*square;
}						t_data;

void					test(t_data *data)
{
	static SDL_Rect		rect = {0, 0, SIZE_X, SIZE_Y};
	static int			dirX = 1;
	static int			dirY = 1;

	if (rect.x + SIZE_X >= data->esdl->en.rx || rect.x < 0)
		dirX *= -1;
	if (rect.y + SIZE_Y >= data->esdl->en.ry || rect.y < 0)
		dirY *= -1;

	rect.x += (dirX * SPEED);
	rect.y += (dirY * SPEED);

	SDL_RenderClear(data->esdl->en.ren);
	SDL_RenderCopy(data->esdl->en.ren, data->square, NULL, &rect);
	SDL_RenderPresent(data->esdl->en.ren);
}

void				init(t_data *data)
{
	SDL_Surface		*surf;
	SDL_Rect		rect = {0, 0, SIZE_X, SIZE_Y};

	surf = Esdl_create_surface(SIZE_X, SIZE_Y);
	Esdl_draw_square(surf, rect, 0xFFFFFFFF);
	data->square = SDL_CreateTextureFromSurface(data->esdl->en.ren, surf);
	SDL_FreeSurface(surf);
}

void				quit(t_data *data)
{
	SDL_DestroyTexture(data->square);
}

int					main(int argc, char **argv)
{
	t_data			data;
	t_esdl			esdl;

	data.esdl = &esdl;

	if (Esdl_init(&esdl, 640, 480, 60, "Engine") == -1)
		return (-1);
	init(&data);
	while (esdl.run)
	{
		Esdl_update_events(&esdl.en.in, &esdl.run);

		test(&data);

		Esdl_fps_limit(&esdl);
		Esdl_fps_counter(&esdl);
	}
	quit(&data);
	Esdl_quit(&esdl);
	(void)argc;
	(void)argv;
	return (0);
}
