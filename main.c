#include <gtk/gtk.h>
#include <glib.h>
#include <unistd.h>

struct Windows {
	GtkWidget *main_window;
	GtkWidget *splash_screen;

};

static struct Windows *windows = NULL;
GtkApplication *app = NULL;

gboolean
main_activity()
{

	return FALSE;
}

static void 
create_main_window()
{
	windows->main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_assert(windows->main_window);
	gtk_window_set_title (GTK_WINDOW (windows->main_window), 
		"Window");
	gtk_window_set_default_size (GTK_WINDOW (windows->main_window),
		200, 200);

	gtk_widget_show_all (windows->main_window);
	gtk_application_add_window(app, GTK_WINDOW (windows->main_window));
}

static void
on_activate(GtkApplication* app)
{
	g_assert(app);
	windows = g_malloc(sizeof windows);
	g_assert(windows);

	windows->main_window = NULL;
	windows->splash_screen = NULL;

	create_main_window();
	g_idle_add(main_activity, NULL);
}

int
main(int argc, char **argv)
{
	int status;

	gtk_init(&argc,&argv);

	app = gtk_application_new (NULL, G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);
	

	g_free(windows);

	return status;
}
