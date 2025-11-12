# GTlib Architecture

## E-comOS Philosophy

GTlib follows E-comOS three core philosophies:

1. **Everything is a Process** - Window manager runs as separate service process
2. **Everything is an Object** - Windows and widgets are objects with IDs
3. **Everything is a Service** - GTlib communicates via IPC with window manager service

## Architecture

```
┌─────────────────┐
│  Application    │
└────────┬────────┘
         │ GTlib API
┌────────▼────────┐
│   GTlib Client  │
│   (This lib)    │
└────────┬────────┘
         │ IPC Messages
┌────────▼────────┐
│ Window Manager  │
│    Service      │
│   (wm_service)  │
└────────┬────────┘
         │
┌────────▼────────┐
│    Terminal     │
└─────────────────┘
```

## IPC Message Flow

- `GT_IPC_CREATE_WINDOW` → Create window object in WM service
- `GT_IPC_DRAW_CHAR` → Send draw command to WM service
- `GT_IPC_EVENT_KEY` → Receive keyboard events from WM service
- `GT_IPC_REFRESH_WINDOW` → Request window refresh

## Object Model

- Each window has unique ID assigned by WM service
- Widgets are child objects of windows
- All operations go through IPC to maintain process isolation
