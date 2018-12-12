#include <gtk/gtk.h>

#include "gui.h"
#include "game.h"

#define GLADE_FILENAME		"window.glade"
#define GLADE_IMG_FILENAME	"ball-green.png"

#define GLADE_MAIN_WINDOW_ID	"window_main"
#define GLADE_GRID_ID		"grid"


static GtkBuilder	*builder; 
static GtkWidget	*main_window;
static GtkGrid		*grid;
static GdkPixbuf	*pixbuf;


int gui_init(int argc, char *argv[])
{
	GError	*err = NULL;

	gtk_init(&argc, &argv);

	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, GLADE_FILENAME, NULL);

	main_window = GTK_WIDGET(gtk_builder_get_object(builder, GLADE_MAIN_WINDOW_ID));
	gtk_builder_connect_signals(builder, NULL);

	grid = GTK_GRID(gtk_builder_get_object(builder, GLADE_GRID_ID));

	pixbuf = gdk_pixbuf_new_from_file(GLADE_IMG_FILENAME, &err);

	return 0;
}

void gui_show(void)
{
	gtk_widget_show(main_window);
	gtk_main();
}

static void gui_update_cell(GtkWidget *widget, const struct cell *cell, enum gui_update_toggle state)
{
	switch ( cell->state )
	{
		case CELL_STATE_EMPTY:
		if ( state )
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), FALSE);
		gtk_button_set_image(GTK_BUTTON(widget), NULL);
		break;

		case CELL_STATE_FILLED:
		if ( state )
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(widget), TRUE);
		gtk_button_set_image(GTK_BUTTON(widget), gtk_image_new_from_pixbuf(pixbuf));
		break;
	}
}

void gui_update(enum gui_update_toggle state)
{
	GtkWidget	*cell;
	int		i,
			j;

	for ( i = 0 ; i < BOARD_X_MAX ; i++ )
		for ( j = 0 ; j < BOARD_Y_MAX ; j++)
			if ( (cell = gtk_grid_get_child_at(grid, j, i)) != NULL )
				gui_update_cell(cell, &board[i][j], state);
}

void gui_destroy(void)
{
	g_object_unref(builder);

	gtk_main_quit();
}

void gui_get_button_toggled_index(const GtkToggleButton *button, int *x, int *y)
{
	int		i,
			j;

	for ( i = 0 ; i < BOARD_X_MAX ; i++ )
		for ( j = 0 ; j < BOARD_Y_MAX ; j++)
			if ( GTK_TOGGLE_BUTTON(gtk_grid_get_child_at(grid, j, i)) == button )
			{
				*x = i;
				*y = j;

				break;
			}
}
