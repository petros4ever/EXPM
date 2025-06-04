#include <gtk/gtk.h>
#include <sqlite3.h>
#include <stdio.h>

void on_login_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget**)data;
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(entries[1]));

    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc = sqlite3_open("mydatabase.db", &db);

    if (rc != SQLITE_OK) {
        g_print("Σφάλμα σύνδεσης στη βάση δεδομένων!\n");
        return;
    }

    // Έλεγχος αν ο χρήστης υπάρχει στη βάση
    const char *sql = "SELECT * FROM Users WHERE Name = ? AND Password = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW) {
        g_print("Επιτυχής σύνδεση! Μετάβαση στην νέα οθόνη...\n");
        // Εδώ μπορείς να δημιουργήσεις ένα νέο GTK παράθυρο
        GtkWidget *new_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(new_window), "Καλώς ήρθες!");
        gtk_window_set_default_size(GTK_WINDOW(new_window), 400, 200);
        gtk_widget_show_all(new_window);
    } else {
        g_print("Λάθος στοιχεία! Παρακαλώ δοκιμάστε ξανά.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main(int argc, char **argv) {
    GtkWidget *window, *grid, *label_user, *label_pass, *entry_user, *entry_pass, *button;
    GtkWidget *entries[2];

    gtk_init(&argc, &argv);
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Login");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    label_user = gtk_label_new("Όνομα Χρήστη:");
    label_pass = gtk_label_new("Κωδικός:");

    entry_user = gtk_entry_new();
    entry_pass = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry_pass), FALSE);

    entries[0] = entry_user;
    entries[1] = entry_pass;

    button = gtk_button_new_with_label("Σύνδεση");
    g_signal_connect(button, "clicked", G_CALLBACK(on_login_clicked), entries);

    gtk_grid_attach(GTK_GRID(grid), label_user, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_user, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), label_pass, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_pass, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 2, 2, 1);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(window);
    
    gtk_main();
    return 0;
}
