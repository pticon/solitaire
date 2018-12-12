#include <gtk/gtk.h>

#include "gui.h"
#include "game.h"

/* called when window is closed
 */
void handler_on_window_main_destroy(void)
{
	gui_destroy();
}

/* called when the new button is clicked
 */
void handler_new_button_clicked(GtkButton *button, gpointer data)
{
	game_reset();

	gui_update(UPDATE_TRUE);
}

/* called when a toggled button is clicked
 */
void handler_cell_toggled(GtkToggleButton *button, gpointer data)
{
	int	i,
		j;

	gui_get_button_toggled_index(button, &i, &j);

	if ( game_update(i, j) )
		gui_update(UPDATE_TRUE);
}
