#ifndef __HANDLER_H__
#define __HANDLER_H__

void handler_on_window_main_destroy(void);

void handler_new_button_clicked(GtkButton *button, gpointer data);

void handler_cell_toggled(GtkToggleButton *button, gpointer data);

#endif /* __HANDLER_H__ */
