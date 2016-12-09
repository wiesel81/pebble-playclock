#include <pebble.h>

// The following variables can and should be used in the project's .c-file
extern Window *window;
extern Layer *layerWindow;
extern GRect windowBounds;
extern int windowHeight;
extern int windowWidth;
extern Layer *layerCanvas;

// The following functions has to be implemented in the project's .c-file
extern void appLoad(Window *window);
extern void appUnload(Window *window);
extern void appDrawCanvasGraphics(Layer *layer, GContext *ctx);
extern void appClickConfigProvider(void *context);

// The following function may be used from the project's .c-file
void intTo2DigitText(int value, char *buf);
