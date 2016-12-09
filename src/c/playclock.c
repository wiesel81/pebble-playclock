#include <pebble.h>
#include "main.h"
#include "playclock.h"
#include "settings.h"

static TextLayer *layerHeadline; // Layer for displaying headline
static TextLayer *layerCountdown; // Layer for displaying countdown
static TextLayer *layerState; // Layer for displaying state or messages
static TextLayer *layerButtonUp; // Layer for up-button description
// static TextLayer *layerButtonSelect; // Layer for select-button description
static TextLayer *layerButtonDown; // Layer for down-button description
static ActionBarLayer *layerActionBar;

static Timer timer;

static void handleSecondTick(struct tm *, TimeUnits);

static void vibrate(const VibePattern *pattern) {
	if(pattern != NULL) {
		vibes_enqueue_custom_pattern(*pattern);
	}
}

// TODO: implement motion sensor (accelerometer) with regard to settings
// https://developer.pebble.com/guides/events-and-services/accelerometer/

static void setTimer(const TimerInfo *newTimerInfo) {
	if(timer.info->state == STATE_RUNNING && newTimerInfo->state != STATE_RUNNING) {
		tick_timer_service_unsubscribe();
	} else if(timer.info->state != STATE_RUNNING && newTimerInfo->state == STATE_RUNNING) {
		tick_timer_service_subscribe(SECOND_UNIT, handleSecondTick);
	}
	timer.info = newTimerInfo;
	timer.value = timer.info->startValue;
	timer.stateMessage = timer.info->stateMessage;
	intTo2DigitText(timer.value, timer.valueDisplay);
	text_layer_set_text(layerCountdown, timer.valueDisplay);
	text_layer_set_text(layerState, timer.stateMessage);
}

static void decrementTimer(void) {
	timer.value--;
	if(timer.value > 0) {
		intTo2DigitText(timer.value, timer.valueDisplay);
		text_layer_set_text(layerCountdown, timer.valueDisplay);
		const Notification *notification = getNotification(timer.value, timer.info->startValue == TIMER_SHORT);
		if(notification != NULL) {
			vibrate(getVibesNotificationPattern(notification));
			char *stateMessage = getNotificationStateMessage(notification);
			if(stateMessage != NULL && stateMessage[0] != '\0') {
				timer.stateMessage = stateMessage;
				text_layer_set_text(layerState, timer.stateMessage);
			}
		}
	} else {
		vibrate(getVibesOnTimerExpiredPattern());
		if(timer.info->startValue == TIMER_SHORT) {
			setTimer(&TIMER_EXPIRED_SHORT);
		} else {
			setTimer(&TIMER_EXPIRED_DEFAULT);
		}
	}
}

// Event occurs every second
static void handleSecondTick(struct tm *t, TimeUnits unitsChanged) {
	decrementTimer();
}

static void onUpClick(ClickRecognizerRef recognizer, void *context) {
	vibrate(getOnButtonStartsDefaultTimerVibePattern());
	setTimer(&TIMER_RUNNING_DEFAULT);
}

static void onUpLongClick(ClickRecognizerRef recognizer, void *context) {
	vibrate(getOnButtonPressedVibePattern());
	setTimer(&TIMER_PRESET_DEFAULT);
}

static void onSelectClick(ClickRecognizerRef recognizer, void *context) {
	if(timer.info->state == STATE_PRESET) {
		vibrate(getOnButtonPressedVibePattern());
		if(timer.info->startValue == TIMER_SHORT) {
			vibrate(getOnButtonStartsShortTimerVibePattern());
			setTimer(&TIMER_RUNNING_SHORT);
		} else {
			vibrate(getOnButtonStartsDefaultTimerVibePattern());
			setTimer(&TIMER_RUNNING_DEFAULT);
		}
	} else if(timer.info->state == STATE_STANDBY) {
		if(invertVibesEnabled()) {
			timer.stateMessage = getStateMessageVibesOn();
		} else {
			timer.stateMessage = getStateMessageVibesOff();
		}
		text_layer_set_text(layerState, timer.stateMessage);
		vibrate(getOnButtonPressedVibePattern());
	} // else: button is disabled in all other states
}

static void onSelectLongClick(ClickRecognizerRef recognizer, void *context) {
	vibrate(getOnButtonPressedVibePattern());
	if(timer.info->isRunning) {
		if(timer.info->startValue == TIMER_SHORT) {
			setTimer(&TIMER_STOPPED_SHORT);
		} else {
			setTimer(&TIMER_STOPPED_DEFAULT);
		}
	} else if(timer.info->state == STATE_STANDBY) {
		if(invertVibesOnButtonPressedEnabled()) {
			timer.stateMessage = getStateMessageVibesOnButtonPressedOn();
		} else {
			timer.stateMessage = getStateMessageVibesOnButtonPressedOff();
		}
		text_layer_set_text(layerState, timer.stateMessage);
		vibrate(getOnButtonPressedVibePattern());
	} else {
		setTimer(&TIMER_STANDBY);
	}
}

static void onDownClick(ClickRecognizerRef recognizer, void *context) {
	vibrate(getOnButtonStartsShortTimerVibePattern());
	setTimer(&TIMER_RUNNING_SHORT);
}

static void onDownLongClick(ClickRecognizerRef recognizer, void *context) {
	vibrate(getOnButtonPressedVibePattern());
	setTimer(&TIMER_PRESET_SHORT);
}

void appClickConfigProvider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, onUpClick);
	window_long_click_subscribe(BUTTON_ID_UP, getButtonPressedLongDuration(), onUpLongClick, NULL);
  window_single_click_subscribe(BUTTON_ID_SELECT, onSelectClick);
	window_long_click_subscribe(BUTTON_ID_SELECT, getButtonPressedLongDuration(), onSelectLongClick, NULL);
  window_single_click_subscribe(BUTTON_ID_DOWN, onDownClick);
	window_long_click_subscribe(BUTTON_ID_DOWN, getButtonPressedLongDuration(), onDownLongClick, NULL);
}

void appDrawCanvasGraphics(Layer *layer, GContext *ctx) {
  graphics_context_set_stroke_color(ctx, getForegroundColor());
  graphics_context_set_fill_color(ctx, getForegroundColor());
  graphics_context_set_stroke_width(ctx, 2);
	graphics_context_set_antialiased(ctx, false);

	graphics_draw_line(ctx, GPoint(0, MSG_BOX_HEIGHT(windowHeight)), GPoint(MSG_BOX_WIDTH(windowWidth), MSG_BOX_HEIGHT(windowHeight)));
	graphics_draw_line(ctx, GPoint(BTN_DESC_X_LEFT(windowWidth), 0), GPoint(BTN_DESC_X_LEFT(windowWidth), windowHeight));
	graphics_draw_line(ctx, GPoint(BTN_DESC_X_LEFT(windowWidth), BTN_DESC_HEIGHT(windowHeight)), GPoint(windowWidth, BTN_DESC_HEIGHT(windowHeight)));
	graphics_draw_line(ctx, GPoint(BTN_DESC_X_LEFT(windowWidth), windowHeight-(BTN_DESC_HEIGHT(windowHeight))), GPoint(windowWidth, windowHeight-(BTN_DESC_HEIGHT(windowHeight))));
	graphics_draw_line(ctx, GPoint(0, windowHeight-MSG_BOX_HEIGHT(windowHeight)), GPoint(MSG_BOX_WIDTH(windowWidth), windowHeight-MSG_BOX_HEIGHT(windowHeight)));
}

void updateGUI() {
	window_set_background_color(window, getBackgroundColor());

	// Update headline
	text_layer_set_text_color(layerHeadline, getForegroundColor());
	text_layer_set_text(layerHeadline, TEXT_HEADLINE);

	// Update description of buttons
	text_layer_set_text_color(layerButtonUp, getForegroundColor());
	text_layer_set_text_color(layerButtonDown, getForegroundColor());
	
	// Update countdown
	text_layer_set_text_color(layerCountdown, getForegroundColor());
	
	// Update state
	text_layer_set_text_color(layerState, getForegroundColor());
	
	// Update timer
	setTimer(&TIMER_STANDBY);
}

void appLoad(Window *window) {
	GFont basicFont = fonts_get_system_font(FONT_DEFAULT);
	GFont timerFont = fonts_get_system_font(FONT_TICKER);
	
	// Initialize headline
	layerHeadline = text_layer_create(GRect(0, ((MSG_BOX_HEIGHT(windowHeight)-FONT_DEFAULT_SIZE)/2)+MSG_BOX_LAYER_Y_CORRECTION(windowHeight), MSG_BOX_WIDTH(windowWidth)-MSG_BOX_LAYER_X_CORRECTION(windowWidth), FONT_DEFAULT_SIZE)); 
	text_layer_set_background_color(layerHeadline, GColorClear);	
	text_layer_set_font(layerHeadline, basicFont);
	text_layer_set_text_alignment(layerHeadline, PBL_IF_RECT_ELSE(GTextAlignmentCenter, GTextAlignmentRight));	
	layer_add_child(layerWindow, text_layer_get_layer(layerHeadline));

	// Initialize description of buttons
	layerButtonUp = text_layer_create(GRect(BTN_DESC_X_LEFT(windowWidth), BTN_DESC_Y_TOP(windowHeight)+BTN_DESC_LAYER_Y_CORRECTION(windowHeight), BTN_DESC_WIDTH(windowWidth), FONT_DEFAULT_SIZE));
	text_layer_set_background_color(layerButtonUp, GColorClear);
	text_layer_set_font(layerButtonUp, basicFont);
	text_layer_set_text_alignment(layerButtonUp, GTextAlignmentCenter);
  layer_add_child(layerWindow, text_layer_get_layer(layerButtonUp));
	char *countdownTimeDefault = malloc(sizeof(char) * 2);
	intTo2DigitText(TIMER_DEFAULT, countdownTimeDefault);
	text_layer_set_text(layerButtonUp, countdownTimeDefault);

	layerButtonDown = text_layer_create(GRect(BTN_DESC_X_LEFT(windowWidth), windowHeight-BTN_DESC_Y_TOP(windowHeight)-BTN_DESC_LAYER_Y_CORRECTION(windowHeight), BTN_DESC_WIDTH(windowWidth), FONT_DEFAULT_SIZE));
	text_layer_set_background_color(layerButtonDown, GColorClear);
	text_layer_set_font(layerButtonDown, basicFont);
	text_layer_set_text_alignment(layerButtonDown, GTextAlignmentCenter);
  layer_add_child(layerWindow, text_layer_get_layer(layerButtonDown));
	char *countdownTimeShort = malloc(sizeof(char) * 2);
	intTo2DigitText(TIMER_SHORT, countdownTimeShort);
	text_layer_set_text(layerButtonDown, countdownTimeShort);

	// Initialize countdown
  layerCountdown = text_layer_create(GRect(0, (windowHeight/2)-(FONT_TICKER_SIZE/2), windowWidth-BTN_DESC_WIDTH(windowWidth), FONT_TICKER_SIZE)); 
	text_layer_set_background_color(layerCountdown, GColorClear);
	text_layer_set_font(layerCountdown, timerFont);
	text_layer_set_text_alignment(layerCountdown, GTextAlignmentCenter);
  layer_add_child(layerWindow, text_layer_get_layer(layerCountdown));

	// Initialize state
	layerState = text_layer_create(GRect(0, windowHeight-((MSG_BOX_HEIGHT(windowHeight)+FONT_DEFAULT_SIZE)/2)-MSG_BOX_LAYER_Y_CORRECTION(windowHeight), MSG_BOX_WIDTH(windowWidth)-MSG_BOX_LAYER_X_CORRECTION(windowWidth), FONT_DEFAULT_SIZE)); 
	text_layer_set_background_color(layerState, GColorClear);
	text_layer_set_font(layerState, basicFont);
	text_layer_set_text_alignment(layerState, PBL_IF_RECT_ELSE(GTextAlignmentCenter, GTextAlignmentRight));	
	layer_add_child(layerWindow, text_layer_get_layer(layerState));

	// Initialize timer
	timer.info = &TIMER_STANDBY;
	if(timer.valueDisplay == NULL) {
		timer.valueDisplay = malloc(sizeof(char) * 2);
	}
	
	// Initialize settings
	initSettings();

	// Initialize GUI
	updateGUI();
}

void appUnload(Window *window) {
	text_layer_destroy(layerHeadline);
	text_layer_destroy(layerCountdown);
	text_layer_destroy(layerState);
	text_layer_destroy(layerButtonUp);
	text_layer_destroy(layerButtonDown);
	action_bar_layer_destroy(layerActionBar);
}
