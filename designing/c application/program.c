#include <gtk/gtk.h>
#include <sqlite3.h>
#include <stdio.h>

typedef struct {
    int user_id;
    int book_id;
} PurchaseData;

void add_book_to_db(GtkWidget *widget, gpointer data) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc = sqlite3_open("mydatabase.db", &db);
    
    if (rc != SQLITE_OK) {
        g_print("❌ Σφάλμα σύνδεσης στη βάση δεδομένων!\n");
        return;
    }

    GtkWidget **entries = (GtkWidget**)data;
    const gchar *name = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const gchar *author = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    const gchar *price_str = gtk_entry_get_text(GTK_ENTRY(entries[2]));
    const gchar *category = gtk_entry_get_text(GTK_ENTRY(entries[3]));

    // Έλεγχος αν όλα τα πεδία έχουν συμπληρωθεί
    if (!name || !author || !price_str || !category || g_strcmp0(name, "") == 0 || g_strcmp0(author, "") == 0 || g_strcmp0(price_str, "") == 0 || g_strcmp0(category, "") == 0) {
        g_print("⚠️ Παρακαλώ συμπληρώστε όλα τα πεδία!\n");
        return;
    }

    float price = atof(price_str); // Μετατροπή σε float

    // SQL εντολή για προσθήκη νέου βιβλίου
    const char *sql = "INSERT INTO book (Name, author, price, category) VALUES (?, ?, ?, ?)";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, author, -1, SQLITE_STATIC);
        sqlite3_bind_double(stmt, 3, price);
        sqlite3_bind_text(stmt, 4, category, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            g_print("✅ Το βιβλίο προστέθηκε επιτυχώς!\n");
        } else {
            g_print("❌ Αποτυχία προσθήκης βιβλίου!\n");
        }
    } else {
        g_print("❌ Σφάλμα SQL: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void open_add_book_window() {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Προσθήκη Βιβλίου");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), box);

    GtkWidget *entry_name = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_name), "Τίτλος Βιβλίου");
    GtkWidget *entry_author = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_author), "Συγγραφέας");
    GtkWidget *entry_price = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_price), "Τιμή (€)");
    GtkWidget *entry_category = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_category), "Κατηγορία");

    GtkWidget *save_button = gtk_button_new_with_label("Αποθήκευση");

    // **Δημιουργούμε δυναμική μνήμη για τα GtkEntry**
    GtkWidget **entries = g_malloc(4 * sizeof(GtkWidget*));
    entries[0] = entry_name;
    entries[1] = entry_author;
    entries[2] = entry_price;
    entries[3] = entry_category;

    // **Συνδέουμε το κουμπί "Αποθήκευση" με add_book_to_db()**
    g_signal_connect(save_button, "clicked", G_CALLBACK(add_book_to_db), entries);

    gtk_box_pack_start(GTK_BOX(box), entry_name, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), entry_author, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), entry_price, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), entry_category, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(box), save_button, FALSE, FALSE, 5);

    gtk_widget_show_all(window);
}

void show_purchased_books(GtkWidget *container, int user_id) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc = sqlite3_open("mydatabase.db", &db);

    if (rc != SQLITE_OK) {
        g_print("Σφάλμα σύνδεσης στη βάση δεδομένων!\n");
        return;
    }

    // SQL για εμφάνιση των βιβλίων που αγόρασε ο χρήστης
    const char *sql = "SELECT book.Name, book.author, book.price "
                      "FROM bought_books "
                      "JOIN book ON bought_books.book_id = book.ID "
                      "WHERE bought_books.user_id = ?";
    
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, user_id);

    if (rc != SQLITE_OK) {
        g_print("Σφάλμα στην εκτέλεση του ερωτήματος: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *name = (const char*)sqlite3_column_text(stmt, 0);
        const char *author = (const char*)sqlite3_column_text(stmt, 1);
        float price = (float)sqlite3_column_double(stmt, 2);

        // Δημιουργία ετικέτας με πληροφορίες για το αγορασμένο βιβλίο
        gchar *book_info = g_strdup_printf("📖 %s - %s (%.2f€)", name, author, price);
        GtkWidget *label = gtk_label_new(book_info);
        g_free(book_info);

        gtk_container_add(GTK_CONTAINER(container), label);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    gtk_widget_show_all(container);
}

void on_buy_clicked(GtkWidget *widget, gpointer data) {
    PurchaseData *purchase = (PurchaseData*)data; // Μετατροπή σε σωστό struct
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc = sqlite3_open("mydatabase.db", &db); 

    if (rc != SQLITE_OK) {
        g_print("Σφάλμα σύνδεσης στη βάση δεδομένων!\n");
        return;
    }

    // SQL εντολή για εισαγωγή στην βάση
    const char *sql = "INSERT INTO bought_books (user_id, book_id) VALUES (?, ?)";
    
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        g_print("Σφάλμα SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_int(stmt, 1, purchase->user_id);
    sqlite3_bind_int(stmt, 2, purchase->book_id);

    if (sqlite3_step(stmt) == SQLITE_DONE) {
        g_print("Το βιβλίο αγοράστηκε επιτυχώς!\n");
    } else {
        g_print("Η αγορά απέτυχε!\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    g_free(purchase); // Απελευθέρωση μνήμης
}

void show_books(GtkWidget *container, int user_id) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc = sqlite3_open("mydatabase.db", &db);

    if (rc != SQLITE_OK) {
        g_print("Σφάλμα σύνδεσης στη βάση δεδομένων!\n");
        return;
    }

    const char *sql = "SELECT ID, Name, author, price FROM book";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        g_print("Σφάλμα στην εκτέλεση του ερωτήματος!\n");
        sqlite3_close(db);
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int book_id = sqlite3_column_int(stmt, 0);
        const char *name = (const char*)sqlite3_column_text(stmt, 1);
        const char *author = (const char*)sqlite3_column_text(stmt, 2);
        float price = (float)sqlite3_column_double(stmt, 3);

        GtkWidget *row_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
        gtk_container_add(GTK_CONTAINER(container), row_box);

        gchar *book_info = g_strdup_printf("📖 %s - %s (%.2f€)", name, author, price);
        GtkWidget *label = gtk_label_new(book_info);
        g_free(book_info);

        GtkWidget *buy_button = gtk_button_new_with_label("Αγορά");

        // Δημιουργία δομής `PurchaseData`
        PurchaseData *purchase = g_malloc(sizeof(PurchaseData));
        purchase->user_id = user_id;
        purchase->book_id = book_id;

        g_signal_connect(buy_button, "clicked", G_CALLBACK(on_buy_clicked), purchase);

        gtk_box_pack_start(GTK_BOX(row_box), label, FALSE, FALSE, 5);
        gtk_box_pack_start(GTK_BOX(row_box), buy_button, FALSE, FALSE, 5);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    gtk_widget_show_all(container);
}

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
        int user_id = sqlite3_column_int(stmt, 0); // Ανάκτηση του user_id από τη βάση
        // Εδώ μπορείς να δημιουργήσεις ένα νέο GTK παράθυρο
        GtkWidget *new_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        if(g_strcmp0(username, "admin") == 0)
        {
            gtk_window_set_title(GTK_WINDOW(new_window), "Καλώς ήρθες admin!");
            gtk_window_set_default_size(GTK_WINDOW(new_window), 400, 200);
            GtkWidget *button_add_book = gtk_button_new_with_label("➕ Προσθήκη Βιβλίου");
            g_signal_connect(button_add_book, "clicked", G_CALLBACK(open_add_book_window), NULL);
            GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
            gtk_container_add(GTK_CONTAINER(new_window), box);
            gtk_box_pack_start(GTK_BOX(box), button_add_book, FALSE, FALSE, 5);
            gtk_widget_show_all(new_window);
        }
        else{
           
            gtk_window_set_default_size(GTK_WINDOW(new_window), 400, 200);

            // Δημιουργία κεντρικού box container
            GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
            gtk_container_add(GTK_CONTAINER(new_window), box);

            // Δημιουργία ετικέτας καλωσορίσματος
            gchar *welcome_msg = g_strdup_printf("Καλώς ήρθες, %s!", username);
            GtkWidget *label = gtk_label_new(welcome_msg);
            g_free(welcome_msg); // Απελευθέρωση μνήμης

            gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 5); // Προσθήκη της ετικέτας στο Box

           // Εμφάνιση των βιβλίων μέσα στο ίδιο Box
           show_books(box,user_id); 
           show_purchased_books(box, user_id);
            gtk_window_set_title(GTK_WINDOW(new_window), "Βιβλία");
           gtk_widget_show_all(new_window);
        }
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
