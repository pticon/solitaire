#ifndef __GUI_H__
#define __GUI_H__


int gui_init(int argc, char *argv[]);

void gui_show(void);

enum gui_update_toggle
{
	UPDATE_FALSE,
	UPDATE_TRUE,
};

void gui_update(enum gui_update_toggle state);

void gui_get_button_toggled_index(const GtkToggleButton *button, int *pi, int *pj);

void gui_destroy(void);


#endif /* __GUI_H__ */
