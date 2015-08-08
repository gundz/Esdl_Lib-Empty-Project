#include <easy_sdl.h>


void					test(t_esdl *esdl)
{
	static SDL_Rect		rect = {0, 0, 200, 200};
	static SDL_Texture 	*square = NULL;
	SDL_Surface			*surf;

	if (square == NULL)
	{
		surf = Esdl_create_surface(200, 200);
		Esdl_draw_square(surf, rect, 0xFFFFFFFF);
		square = SDL_CreateTextureFromSurface(esdl->en.ren, surf);
	}
	if (rect.x >= esdl->en.rx - 200)
		rect.x = 0;
	if (rect.y >= esdl->en.ry - 200)
		rect.y = 0;
	rect.x++;
	rect.y++;
	SDL_RenderClear(esdl->en.ren);
	SDL_RenderCopy(esdl->en.ren, square, NULL, &rect);
	SDL_RenderPresent(esdl->en.ren);
}

int					main(int argc, char **argv)
{
	t_esdl			esdl;

	if (Esdl_init(&esdl) == -1)
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