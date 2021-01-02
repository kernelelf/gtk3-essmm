#include <gtk/gtk.h>
#include <glib.h>
#include <unistd.h>
#include <stdio.h>

struct Windows {
	GtkWidget *main_window;
	GtkWidget *splash_window;

};

static struct Windows *windows = NULL;
GtkApplication *app = NULL;

gboolean
splash_activity()
{
	g_print("splash_activity called");
	return FALSE;
}

static void 
create_splash_window()
{
	windows->splash_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_assert(windows->splash_window);
	
	gtk_window_set_resizable (GTK_WINDOW (windows->splash_window), FALSE);
	gtk_window_set_decorated (GTK_WINDOW (windows->splash_window), FALSE);
	gtk_window_set_default_size (GTK_WINDOW (windows->splash_window),
		180, 50);

	gtk_widget_show_all (windows->splash_window);
	gtk_application_add_window (app, GTK_WINDOW (windows->splash_window));
}

static void
on_activate(GtkApplication* app)
{
	g_assert(app);
	windows = g_malloc(sizeof windows);
	g_assert(windows);

	windows->main_window = NULL;
	windows->splash_window = NULL;

	create_splash_window();
	g_timeout_add(0,splash_activity, NULL);
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
