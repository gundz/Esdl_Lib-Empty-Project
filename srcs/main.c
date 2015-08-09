#include <easy_sdl.h>

#define SPEED 3
#define SIZE_X 50
#define SIZE_Y 50

void					test(t_esdl *esdl)
{
	static SDL_Rect		rect = {0, 0, SIZE_X, SIZE_Y};
	static SDL_Texture 	*square = NULL;
	SDL_Surface			*surf;
	static int			dirX = 1;
	static int			dirY = 1;

	if (square == NULL)
	{
		surf = Esdl_create_surface(SIZE_X, SIZE_Y);
		Esdl_draw_square(surf, rect, 0xFFFFFFFF);
		square = SDL_CreateTextureFromSurface(esdl->en.ren, surf);
	}

	if (rect.x + SIZE_X >= esdl->en.rx || rect.x < 0)
		dirX *= -1;
	if (rect.y + SIZE_Y >= esdl->en.ry || rect.y < 0)
		dirY *= -1;

	rect.x += (dirX * SPEED);
	rect.y += (dirY * SPEED);

	SDL_RenderClear(esdl->en.ren);
	SDL_RenderCopy(esdl->en.ren, square, NULL, &rect);
	SDL_RenderPresent(esdl->en.ren);
}

int					main(int argc, char **argv)
{
	t_esdl			esdl;

	if (Esdl_init(&esdl, 640, 480, 60, "Engine") == -1)
		return (-1);
	while (esdl.run)
	{
		Esdl_update_window_info(&esdl);
		Esdl_update_events(&esdl.en.in, &esdl.run);

		test(&esdl);

		Esdl_fps_limit(&esdl);
		Esdl_fps_counter(&esdl);
	}
	Esdl_quit(&esdl);
	(void)argc;
	(void)argv;
	return (0);
}