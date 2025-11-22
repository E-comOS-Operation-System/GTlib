/*
    GTLib Example - Simple TUI Demo
*/
#include "include/ecomos-gtlib.h"
#include <stdio.h>
#include <unistd.h>

void button_clicked(gt_widget_t *widget, void *user_data) {
    (void)widget;
    (void)user_data;
    // In screen show the button is clicked
    printf("\033[25;1H\033[K");
    printf("Button clicked! Press any key to continue...");
    fflush(stdout);
}

int main(void) {
    // Initialize GTlib
    if (gt_init() != 0) {
        fprintf(stderr, "Failed to initialize GTlib\n");
        return 1;
    }
    
    // Create main window
    gt_window_t *window = gt_create_window(5, 3, 60, 15, "GTlib Demo");
    if (!window) {
        gt_cleanup();
        return 1;
    }
    
    gt_show_window(window);
    
    // Draw window border and title
    gt_clear_window(window);
    gt_draw_border(window, GT_COLOR_CYAN, GT_COLOR_DEFAULT, GT_ATTR_BOLD);
    gt_draw_string(window, 2, 0, "GTlib Demo", 
                  GT_COLOR_YELLOW, GT_COLOR_DEFAULT, GT_ATTR_BOLD);
    
    // Create widgets
    gt_create_label(window, 2, 2, "Welcome to GTlib!", 
                   GT_COLOR_GREEN, GT_COLOR_DEFAULT, GT_ATTR_BOLD);
    
    gt_create_label(window, 2, 4, "This is a TUI library demo", 
                   GT_COLOR_WHITE, GT_COLOR_DEFAULT, GT_ATTR_NORMAL);
    
    gt_create_button(window, 10, 7, 15, 3, "Click Me", button_clicked, NULL);
    
    gt_create_textbox(window, 10, 11, 30, 3, "Type here...", 50);
    
    // Render all widgets
    gt_render_all_widgets(window);
    gt_refresh_window(window);
    
    // Wait for user input
    gt_event_t event;
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("Use arrow keys to navigate, ENTER to click, ESC to exit...\n");
    
    while (1) {
        if (gt_wait_event(&event, 100) == 0) {
            if (event.type == GT_EVENT_KEY_PRESS) {
                switch (event.data.key) {
                    case GT_KEY_ESC:
                        goto exit_loop;
                    case GT_KEY_UP:
                    case GT_KEY_LEFT:
                        gt_focus_prev_widget(window);
                        gt_render_all_widgets(window);
                        gt_refresh_window(window);
                        break;
                    case GT_KEY_DOWN:
                    case GT_KEY_RIGHT:
                        gt_focus_next_widget(window);
                        gt_render_all_widgets(window);
                        gt_refresh_window(window);
                        break;
                    case GT_KEY_ENTER:
                        gt_activate_focused_widget(window);
                        break;
                }
            }
        }
    }
    
    exit_loop:
    
    // Cleanup
    gt_destroy_window(window);
    gt_cleanup();
    
    return 0;
}
