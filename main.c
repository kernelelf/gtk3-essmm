#include <gtk/gtk.h>
#include <glib.h>
#include <unistd.h>
#include <stdio.h>

struct Windows {
	GtkWidget *main_window;
	GtkWidget *splash_window;

};

struct Windows_Res {
	GtkWidget *progress_bar;
};

struct Thread_ST {
	GThread *thread;

};

static struct Windows *windows = NULL;
static struct Windows_Res *windows_res = NULL;
static struct Thread_ST *thread_st = NULL;

GtkApplication *app = NULL;


static void update_splash_window();
static void remove_splash_window();
static void update_splash_window_progress_bar(gdouble,gchar*);
static void init_splash_window();
static void show_splash_window();
static void init_main_window();
static void show_main_window();

static gpointer
Thread_main()
{

	/* This is a thread, from here this function
	 * is going to be run inside a new process
	 * with a new stack flame and PC.
	 * */

	/* Simulate a program in executation */	
	update_splash_window_progress_bar(0.2,"Work in progress");
	g_usleep(1500000);
	update_splash_window_progress_bar(0.5,"Working...");
	g_usleep(2000000);
	update_splash_window_progress_bar(0.8,"Work near of the end");
	g_usleep(2000000);
	update_splash_window_progress_bar(1.0,"Work finished");
	g_usleep(1000000);

	remove_splash_window();

	g_print("INIT MAIN WINDOW\n");
	init_main_window();
	show_main_window();

	return NULL;
}

static void
init_main_window()
{
	windows->main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	g_assert(windows->main_window);
	
	gtk_window_set_default_size (GTK_WINDOW (windows->main_window),
			480,640);
}

static void
show_main_window()
{

	gtk_application_add_window (app, GTK_WINDOW (windows->main_window));

	gtk_widget_show_all (windows->main_window);

}


static void
init_splash_window()
{
	GtkWidget *fixed = NULL;
	
	windows->splash_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_assert (windows->splash_window);
	
	gtk_window_set_resizable (GTK_WINDOW (windows->splash_window), FALSE);
	gtk_window_set_decorated (GTK_WINDOW (windows->splash_window), FALSE);
	gtk_window_set_default_size (GTK_WINDOW (windows->splash_window),
		300, 150);
	
	fixed = gtk_fixed_new();

	windows_res->progress_bar = gtk_progress_bar_new();
	gtk_progress_bar_set_fraction (
		GTK_PROGRESS_BAR (windows_res->progress_bar), 
		(double)0.0);
	gtk_progress_bar_set_text (
		GTK_PROGRESS_BAR (windows_res->progress_bar),
		NULL);
	gtk_progress_bar_set_show_text (
		GTK_PROGRESS_BAR (windows_res->progress_bar),TRUE);

	gtk_fixed_put (GTK_FIXED (fixed), windows_res->progress_bar,
		(double)75.0,(double)120.0);

	gtk_container_add (GTK_CONTAINER (windows->splash_window),
		fixed);
}

static void
remove_splash_window()
{

	gtk_application_remove_window (app,
		GTK_WINDOW (windows->splash_window));
	gtk_window_close (GTK_WINDOW (windows->splash_window));
}

static void
show_splash_window()
{

	gtk_application_add_window (app, GTK_WINDOW (windows->splash_window));
	gtk_widget_show_all (windows->splash_window);

}


/* Func created for concetual porposes */

static void
update_splash_window()
{
	
}

static void
update_splash_window_progress_bar(gdouble porc, gchar *pbar_string)
{

	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(
		windows_res->progress_bar), porc);

	gtk_progress_bar_set_text (GTK_PROGRESS_BAR(
		windows_res->progress_bar), pbar_string);

}

static void
on_activate(GtkApplication* app)
{
	g_assert (app);
	windows = g_malloc (sizeof windows);
	windows_res = g_malloc (sizeof windows_res);
	thread_st = g_malloc (sizeof thread_st);

	g_assert (windows);
	g_assert (windows_res);
	g_assert (thread_st);

	windows->main_window = NULL;
	windows->splash_window = NULL;
	thread_st->thread = NULL;
	windows_res->progress_bar = NULL;

	/* Inicialize the first window (Splash Screen) with 
	 * all yours components and create a thred
	 * */

	g_print("INIT SPLASH WINDOW\n");
	init_splash_window();
	show_splash_window();
	update_splash_window();

	thread_st->thread = g_thread_new ("MAIN_THREAD",Thread_main,NULL);
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
	g_free(windows_res);
	g_free(thread_st);

	return status;
}
