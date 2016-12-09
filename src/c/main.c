#include <pebble.h>
#include "main.h"

Window *window;
Layer *layerWindow;
GRect windowBounds;
int windowHeight;
int windowWidth;
Layer *layerCanvas;

void intTo2DigitText(int value, char *buf) {
	snprintf(buf, sizeof(buf), "%02d", value);
}

static void init(void) {
	// Initialize window and button click provider
  window = window_create();
	// appClickConfigProvider() must be implemented in project's .c-file
	window_set_click_config_provider(window, appClickConfigProvider);
	// appLoad() and appUnload() must be implemented in project's .c-file
  window_set_window_handlers(window, (WindowHandlers) {
    .load = appLoad,
    .unload = appUnload,
  });
	
	// Initialize global window variables and canvas
	layerWindow = window_get_root_layer(window);
	windowBounds = layer_get_unobstructed_bounds(layerWindow);
	layerCanvas = layer_create(windowBounds);
	windowHeight = layer_get_bounds(layerCanvas).size.h;
	windowWidth = layer_get_bounds(layerCanvas).size.w;
  layer_set_update_proc(layerCanvas, appDrawCanvasGraphics);
  layer_add_child(layerWindow, layerCanvas);
	
	// Deactivate vibes not sent from this timer
	vibes_cancel();
	
  window_stack_push(window, true);
}

static void deinit(void) {
	layer_destroy(layerCanvas);
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
