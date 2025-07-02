#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


GtkWidget *display;
char input_buffer[256] = "";
double first_operand = 0;
double second_operand = 0;
char operator = '\0';
gboolean new_calculation = TRUE;

void update_display(const char *text) {
    gtk_entry_set_text(GTK_ENTRY(display), text);
}


double calculate(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b != 0) return a / b;
            else return 0; 
        default: return 0;
    }
}


void on_digit_clicked(GtkWidget *widget, gpointer data) {
    const char *digit = (const char *)data;
    
    if (new_calculation) {
        strcpy(input_buffer, "");
        new_calculation = FALSE;
    }
    
    
    if (strlen(input_buffer) < 20) {
        strcat(input_buffer, digit);
        update_display(input_buffer);
    }
}


void on_operator_clicked(GtkWidget *widget, gpointer data) {
    const char *op = (const char *)data;
    
    if (strlen(input_buffer) > 0) {
        first_operand = atof(input_buffer);
        operator = op[0];
        strcpy(input_buffer, "");
        new_calculation = FALSE;
    }
}


void on_equals_clicked(GtkWidget *widget, gpointer data) {
    if (strlen(input_buffer) > 0 && operator != '\0') {
        second_operand = atof(input_buffer);
        double result = calculate(first_operand, second_operand, operator);
        
        
        if (result == (int)result) {
            sprintf(input_buffer, "%.0f", result);
        } else {
            sprintf(input_buffer, "%.6g", result);
        }
        
        update_display(input_buffer);
        operator = '\0';
        new_calculation = TRUE;
    }
}


void on_clear_clicked(GtkWidget *widget, gpointer data) {
    strcpy(input_buffer, "");
    first_operand = 0;
    second_operand = 0;
    operator = '\0';
    new_calculation = TRUE;
    update_display("0");
}


void on_decimal_clicked(GtkWidget *widget, gpointer data) {
    if (new_calculation) {
        strcpy(input_buffer, "0");
        new_calculation = FALSE;
    }
    
    
    if (strstr(input_buffer, ".") == NULL && strlen(input_buffer) < 20) {
        if (strlen(input_buffer) == 0) {
            strcat(input_buffer, "0");
        }
        strcat(input_buffer, ".");
        update_display(input_buffer);
    }
}


GtkWidget* create_button(const char *label, GCallback callback, gpointer data) {
    GtkWidget *button = gtk_button_new_with_label(label);
    gtk_widget_set_size_request(button, 60, 60);
    g_signal_connect(button, "clicked", callback, data);
    return button;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculator BY MISTAAA"); 
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    
   
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);
    
    
    display = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(display), "0");
    gtk_entry_set_alignment(GTK_ENTRY(display), 1.0); 
    gtk_editable_set_editable(GTK_EDITABLE(display), FALSE);
    gtk_widget_set_size_request(display, -1, 50);
    
  
    GtkCssProvider *css_provider = gtk_css_provider_new();
    const char *css_data = "entry { font-size: 18px; font-weight: bold; }";
    gtk_css_provider_load_from_data(css_provider, css_data, -1, NULL);
    GtkStyleContext *context = gtk_widget_get_style_context(display);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css_provider), 
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    gtk_box_pack_start(GTK_BOX(vbox), display, FALSE, FALSE, 0);
    
    
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_box_pack_start(GTK_BOX(vbox), grid, TRUE, TRUE, 0);
    

    gtk_grid_attach(GTK_GRID(grid), create_button("C", G_CALLBACK(on_clear_clicked), NULL), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), create_button("/", G_CALLBACK(on_operator_clicked), "/"), 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), create_button("*", G_CALLBACK(on_operator_clicked), "*"), 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), create_button("-", G_CALLBACK(on_operator_clicked), "-"), 3, 0, 1, 1);
    
    // Row 1: 7, 8, 9, +
    gtk_grid_attach(GTK_GRID(grid), create_button("7", G_CALLBACK(on_digit_clicked), "7"), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), create_button("8", G_CALLBACK(on_digit_clicked), "8"), 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), create_button("9", G_CALLBACK(on_digit_clicked), "9"), 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), create_button("+", G_CALLBACK(on_operator_clicked), "+"), 3, 1, 1, 1);
    
    // Row 2: 4, 5, 6
    gtk_grid_attach(GTK_GRID(grid), create_button("4", G_CALLBACK(on_digit_clicked), "4"), 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), create_button("5", G_CALLBACK(on_digit_clicked), "5"), 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), create_button("6", G_CALLBACK(on_digit_clicked), "6"), 2, 2, 1, 1);
    
    // Row 3: 1, 2, 3
    gtk_grid_attach(GTK_GRID(grid), create_button("1", G_CALLBACK(on_digit_clicked), "1"), 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), create_button("2", G_CALLBACK(on_digit_clicked), "2"), 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), create_button("3", G_CALLBACK(on_digit_clicked), "3"), 2, 3, 1, 1);
    
    // Row 4: 0, ., =
    gtk_grid_attach(GTK_GRID(grid), create_button("0", G_CALLBACK(on_digit_clicked), "0"), 0, 4, 2, 1); // 0 spans 2 columns
    gtk_grid_attach(GTK_GRID(grid), create_button(".", G_CALLBACK(on_decimal_clicked), NULL), 2, 4, 1, 1);
    
    
    GtkWidget *equals_btn = create_button("=", G_CALLBACK(on_equals_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), equals_btn, 3, 2, 1, 3);
    
    
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    
    gtk_widget_show_all(window);
    
    
    gtk_main();
    
    return 0;
}
