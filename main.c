#include <gtk/gtk.h>

#include "gui.h"
#include "game.h"


int main(int argc, char *argv[])
{
	game_init();

	gui_init(argc, argv);

	gui_update(UPDATE_TRUE);

	gui_show();

	return 0;
}
