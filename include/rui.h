#ifndef ECLIB_RUI_H
#define ECLIB_RUI_H

#include "ipc_message.h"
#include "error.h"
#include <stdint.h>
#include <stddef.h>

// --------------------------
// 1. RUI Command Codes (Program → RUI Requests)
// --------------------------
#define RUI_CMD_WINDOW_CREATE    0x3001  // Create window
#define RUI_CMD_WINDOW_CLOSE     0x3002  // Close window
#define RUI_CMD_DRAW_TEXT        0x3003  // Draw text
#define RUI_CMD_DRAW_BUTTON      0x3004  // Draw button
#define RUI_CMD_EVENT_REGISTER   0x3005  // Register event listener (e.g., click, keyboard)

// --------------------------
// 2. RUI Event Codes (RUI → Program Notifications)
// --------------------------
#define RUI_EVENT_CLICK          0x4001  // Mouse click event
#define RUI_EVENT_KEYDOWN        0x4002  // Keyboard keydown event
#define RUI_EVENT_WINDOW_CLOSE   0x4003  // Window closed event

// --------------------------
// 3. Basic Data Types (Common for UI)
// --------------------------
// Coordinates/Dimensions
typedef struct {
    int16_t x;  // X-axis coordinate (top-left corner of the screen is (0,0))
    int16_t y;  // Y-axis coordinate
} rui_point_t;

typedef struct {
    uint16_t width;  // Width
    uint16_t height; // Height
} rui_size_t;

// Color (RGB888)
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rui_color_t;

// --------------------------
// 4. Request Structures (Program → RUI)
// --------------------------
// Create Window Request
typedef struct {
    rui_point_t pos;    // Window position
    rui_size_t size;    // Window size
    char title[64];     // Window title
    rui_color_t bg_color; // Window background color
} rui_window_create_req_t;

// Create Window Response (RUI → Program, returns window ID)
typedef struct {
    uint32_t window_id; // Unique window ID (required for subsequent operations)
    eclib_err_t err;
} rui_window_create_resp_t;

// Draw Text Request
typedef struct {
    uint32_t window_id; // Target window ID
    rui_point_t pos;    // Text position (within the window)
    char text[256];     // Text content
    rui_color_t color;  // Text color
    uint8_t font_size;  // Font size (e.g., 12, 16)
} rui_draw_text_req_t;

// Register Event Listener Request (Program tells RUI: which events to listen for)
typedef struct {
    uint32_t window_id; // Target window ID
    uint16_t event_type;// Event to listen for (e.g., RUI_EVENT_CLICK)
} rui_event_register_req_t;

// --------------------------
// 5. Event Structures (RUI → Program)
// --------------------------
// Mouse Click Event Data
typedef struct {
    uint32_t window_id; // Window ID where the event occurred
    rui_point_t pos;    // Click position (within the window)
    uint8_t button;     // Click button (0=left, 1=right)
} rui_click_event_t;

// Keyboard Keydown Event Data
typedef struct {
    uint32_t window_id; // Window ID where the event occurred
    char key;           // Key pressed (e.g., 'a', '1')
    uint8_t is_ctrl;    // Whether Ctrl is pressed (0=no, 1=yes)
} rui_keydown_event_t;

// General Event Structure (Unified event format for easier parsing)
typedef struct {
    uint16_t event_type; // Event type (e.g., RUI_EVENT_CLICK)
    union {              // Specific event data (parsed based on type)
        rui_click_event_t click;
        rui_keydown_event_t keydown;
    } data;
} rui_event_t;

// --------------------------
// 6. ECLib Wrapper Interfaces (Directly callable by programs)
// --------------------------
// 1. Initialize RUI Communication (Retrieve RUI service PID, internally calls eclib_service_lookup)
eclib_err_t eclib_rui_init(void);

// 2. Create Window (Returns window ID, 0 on failure)
uint32_t eclib_rui_create_window(const rui_point_t* pos, const rui_size_t* size, 
                                const char* title, const rui_color_t* bg_color);

// 3. Close Window
eclib_err_t eclib_rui_close_window(uint32_t window_id);

// 4. Draw Text on Window
eclib_err_t eclib_rui_draw_text(uint32_t window_id, const rui_point_t* pos, 
                               const char* text, const rui_color_t* color, uint8_t font_size);

// 5. Register Event Listener (e.g., listen for window click events)
eclib_err_t eclib_rui_register_event(uint32_t window_id, uint16_t event_type);

// 6. Wait for and Retrieve RUI Events (Blocking, waits until an event is triggered)
eclib_err_t eclib_rui_wait_event(rui_event_t* event, uint32_t timeout_ms);

#endif // ECLIB_RUI_H