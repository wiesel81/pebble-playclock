#include <pebble.h>
#include "settings.h"

uint32_t vibeSegementsShort[] = { VIBE_SHORT };
static const VibePattern VIBE_PATTERN_SHORT = { .durations = vibeSegementsShort, .num_segments = ARRAY_LENGTH(vibeSegementsShort) };
uint32_t vibeSegementsLong[] = { VIBE_LONG };
static const VibePattern VIBE_PATTERN_LONG = { .durations = vibeSegementsLong, .num_segments = ARRAY_LENGTH(vibeSegementsLong) };
uint32_t vibeSegementsShortShort[] = { VIBE_SHORT, VIBE_PAUSE, VIBE_SHORT };
static const VibePattern VIBE_PATTERN_SHORT_SHORT = { .durations = vibeSegementsShortShort, .num_segments = ARRAY_LENGTH(vibeSegementsShortShort) };
uint32_t vibeSegementsShortLong[] = { VIBE_SHORT, VIBE_PAUSE, VIBE_LONG };
static const VibePattern VIBE_PATTERN_SHORT_LONG = { .durations = vibeSegementsShortLong, .num_segments = ARRAY_LENGTH(vibeSegementsShortLong) };
uint32_t vibeSegementsLongShort[] = { VIBE_LONG, VIBE_PAUSE, VIBE_SHORT };
static const VibePattern VIBE_PATTERN_LONG_SHORT = { .durations = vibeSegementsLongShort, .num_segments = ARRAY_LENGTH(vibeSegementsLongShort) };
uint32_t vibeSegementsLongLong[] = { VIBE_LONG, VIBE_PAUSE, VIBE_LONG };
static const VibePattern VIBE_PATTERN_LONG_LONG = { .durations = vibeSegementsLongLong, .num_segments = ARRAY_LENGTH(vibeSegementsLongLong) };
uint32_t vibeSegementsShortShortShort[] = { VIBE_SHORT, VIBE_PAUSE, VIBE_SHORT, VIBE_PAUSE, VIBE_SHORT };
static const VibePattern VIBE_PATTERN_SHORT_SHORT_SHORT = { .durations = vibeSegementsShortShortShort, .num_segments = ARRAY_LENGTH(vibeSegementsShortShortShort) };
//uint32_t vibeSegementsVeryLong[] = { 600 };
//static const VibePattern VIBE_PATTERN_VERY_LONG = { .durations = vibeSegementsVeryLong, .num_segments = ARRAY_LENGTH(vibeSegementsVeryLong) };

																							// 0	// 1									// 2								// 3											// 4											// 5											// 6											// 7
static const VibePattern *VIBE_PATTERNS[] = { NULL, &VIBE_PATTERN_SHORT, &VIBE_PATTERN_LONG, &VIBE_PATTERN_SHORT_SHORT, &VIBE_PATTERN_SHORT_LONG, &VIBE_PATTERN_LONG_SHORT, &VIBE_PATTERN_LONG_LONG, &VIBE_PATTERN_SHORT_SHORT_SHORT };

static ClaySettings settings = { VIBE_ENABLED_DEFAULT,
																VIBE_ON_NOTIFICATION_ENABLED_DEFAULT,
																VIBE_ON_TIMER_EXPIRED_PATTERN_INDEX_DEFAULT,
																VIBE_OFF_PATTERN_INDEX,
																VIBE_ON_BUTTON_STARTS_DEFAULT_TIMER_PATTERN_INDEX_DEFAULT,
																VIBE_ON_BUTTON_STARTS_SHORT_TIMER_PATTERN_INDEX_DEFAULT,
																// Notifications [second, onDefaultTimerEnabled, onShortTimerEnabled, vibePatternIndex, stateMessage]
																{ { 25, true, false, 1, "BALL READY?" },
																	{ 10, true, true, 3, "10\" WARNING!" },
																	{ 5, true, true, 3, "5\" WARNING!" },
																	{ 0, false, false, 0, "" },
																	{ 0, false, false, 0, "" }
																}
															 };
const int settingsVersionCurrent = 1;

// TODO: add version to storage and migrate storage data if necessary
// https://developer.pebble.com/guides/events-and-services/persistent-storage/

// TODO: add settings for motion sensor (enable / disable, vibration pattern on starting default / short timer)

// Read settings from persistent storage
static void loadSettings(void) {
	if(persist_exists(SETTINGS_KEY)) {
		persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
		for(int i = 0; i < NOTIFICATION_MAX; i++) {
			settings.notifications[i].stateMessage = malloc(NOTIFICATION_MSG_MAX_LEN + 1);
			persist_read_string(SETTINGS_KEY_NOTIFICATION_MSG_START + i, settings.notifications[i].stateMessage, NOTIFICATION_MSG_MAX_LEN);
		}
	}
}

// Delete the settings from persistent storage
static void deleteSettings(void) {
	if(persist_exists(SETTINGS_KEY)) {
		persist_delete(SETTINGS_KEY);
		for(int i = 0; i < NOTIFICATION_MAX; i++) {
			persist_delete(SETTINGS_KEY_NOTIFICATION_MSG_START + i);
		}
	}
}

// Save the settings to persistent storage
static void saveSettings(void) {
  persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
	for(int i = 0; i < NOTIFICATION_MAX; i++) {
		persist_write_string(SETTINGS_KEY_NOTIFICATION_MSG_START + i, settings.notifications[i].stateMessage);
	}
	persist_write_int(SETTINGS_KEY_VERSION, settingsVersionCurrent);
}

// Handle the response from AppMessage
static void inboxReceivedHandler(DictionaryIterator *iter, void *context) {
	// Handle global section
	Tuple *vibesEnabled = dict_find(iter, MESSAGE_KEY_VibesEnabled);
	if(vibesEnabled) {
		settings.vibesEnabled = vibesEnabled->value->int32 == 1;
	}
	Tuple *vibesOnNotificationsEnabled = dict_find(iter, MESSAGE_KEY_VibesOnNotificationsEnabled);
	if(vibesOnNotificationsEnabled) {
		settings.vibesOnNotificationsEnabled = vibesOnNotificationsEnabled->value->int32 == 1;
	}
	Tuple *vibesOnTimerExpiredPatternIndex = dict_find(iter, MESSAGE_KEY_VibesOnTimerExpiredPatternIndex);
	if(vibesOnTimerExpiredPatternIndex) {
		settings.vibesOnTimerExpiredPatternIndex = atoi(vibesOnTimerExpiredPatternIndex->value->cstring);
	}
	
	// Handle button section
	Tuple *vibesOnButtonPressedPatternIndex = dict_find(iter, MESSAGE_KEY_VibesOnButtonPressedPatternIndex);
	if(vibesOnButtonPressedPatternIndex) {
		settings.vibesOnButtonPressedPatternIndex = atoi(vibesOnButtonPressedPatternIndex->value->cstring);
	}
	Tuple *vibesOnButtonStartsDefaultTimerPatternIndex = dict_find(iter, MESSAGE_KEY_VibesOnButtonStartsDefaultTimerPatternIndex);
	if(vibesOnButtonStartsDefaultTimerPatternIndex) {
		settings.vibesOnButtonStartsDefaultTimerPatternIndex = atoi(vibesOnButtonStartsDefaultTimerPatternIndex->value->cstring);
	}
	Tuple *vibesOnButtonStartsShortTimerPatternIndex = dict_find(iter, MESSAGE_KEY_VibesOnButtonStartsShortTimerPatternIndex);
	if(vibesOnButtonStartsShortTimerPatternIndex) {
		settings.vibesOnButtonStartsShortTimerPatternIndex = atoi(vibesOnButtonStartsShortTimerPatternIndex->value->cstring);
	}
	
	// Handle notification sections
	Tuple *notification_1_Second = dict_find(iter, MESSAGE_KEY_Notification_1_Second);
	if(notification_1_Second) {
		settings.notifications[0].second = notification_1_Second->value->int32;
	}
	Tuple *notification_1_OnDefaultTimerEnabled = dict_find(iter, MESSAGE_KEY_Notification_1_OnDefaultTimerEnabled);
	if(notification_1_OnDefaultTimerEnabled) {
		settings.notifications[0].onDefaultTimerEnabled = notification_1_OnDefaultTimerEnabled->value->int32 == 1;
	}
	Tuple *notification_1_OnShortTimerEnabled = dict_find(iter, MESSAGE_KEY_Notification_1_OnShortTimerEnabled);
	if(notification_1_OnShortTimerEnabled) {
		settings.notifications[0].onShortTimerEnabled = notification_1_OnShortTimerEnabled->value->int32 == 1;
	}
	Tuple *notification_1_VibePatternIndex = dict_find(iter, MESSAGE_KEY_Notification_1_VibePatternIndex);
	if(notification_1_VibePatternIndex) {
		settings.notifications[0].vibePatternIndex = atoi(notification_1_VibePatternIndex->value->cstring);
	}
	Tuple *notification_1_StateMessage = dict_find(iter, MESSAGE_KEY_Notification_1_StateMessage);
	if(notification_1_StateMessage) {
		settings.notifications[0].stateMessage = notification_1_StateMessage->value->cstring;
	}

	Tuple *notification_2_Second = dict_find(iter, MESSAGE_KEY_Notification_2_Second);
	if(notification_2_Second) {
		settings.notifications[1].second = notification_2_Second->value->int32;
	}
	Tuple *notification_2_OnDefaultTimerEnabled = dict_find(iter, MESSAGE_KEY_Notification_2_OnDefaultTimerEnabled);
	if(notification_2_OnDefaultTimerEnabled) {
		settings.notifications[1].onDefaultTimerEnabled = notification_2_OnDefaultTimerEnabled->value->int32 == 1;
	}
	Tuple *notification_2_OnShortTimerEnabled = dict_find(iter, MESSAGE_KEY_Notification_2_OnShortTimerEnabled);
	if(notification_2_OnShortTimerEnabled) {
		settings.notifications[1].onShortTimerEnabled = notification_2_OnShortTimerEnabled->value->int32 == 1;
	}
	Tuple *notification_2_VibePatternIndex = dict_find(iter, MESSAGE_KEY_Notification_2_VibePatternIndex);
	if(notification_2_VibePatternIndex) {
		settings.notifications[1].vibePatternIndex = atoi(notification_2_VibePatternIndex->value->cstring);
	}
	Tuple *notification_2_StateMessage = dict_find(iter, MESSAGE_KEY_Notification_2_StateMessage);
	if(notification_2_StateMessage) {
		settings.notifications[1].stateMessage = notification_2_StateMessage->value->cstring;
	}

	Tuple *notification_3_Second = dict_find(iter, MESSAGE_KEY_Notification_3_Second);
	if(notification_3_Second) {
		settings.notifications[2].second = notification_3_Second->value->int32;
	}
	Tuple *notification_3_OnDefaultTimerEnabled = dict_find(iter, MESSAGE_KEY_Notification_3_OnDefaultTimerEnabled);
	if(notification_3_OnDefaultTimerEnabled) {
		settings.notifications[2].onDefaultTimerEnabled = notification_3_OnDefaultTimerEnabled->value->int32 == 1;
	}
	Tuple *notification_3_OnShortTimerEnabled = dict_find(iter, MESSAGE_KEY_Notification_3_OnShortTimerEnabled);
	if(notification_3_OnShortTimerEnabled) {
		settings.notifications[2].onShortTimerEnabled = notification_3_OnShortTimerEnabled->value->int32 == 1;
	}
	Tuple *notification_3_VibePatternIndex = dict_find(iter, MESSAGE_KEY_Notification_3_VibePatternIndex);
	if(notification_3_VibePatternIndex) {
		settings.notifications[2].vibePatternIndex = atoi(notification_3_VibePatternIndex->value->cstring);
	}
	Tuple *notification_3_StateMessage = dict_find(iter, MESSAGE_KEY_Notification_3_StateMessage);
	if(notification_3_StateMessage) {
		settings.notifications[2].stateMessage = notification_3_StateMessage->value->cstring;
	}

	Tuple *notification_4_Second = dict_find(iter, MESSAGE_KEY_Notification_4_Second);
	if(notification_4_Second) {
		settings.notifications[3].second = notification_4_Second->value->int32;
	}
	Tuple *notification_4_OnDefaultTimerEnabled = dict_find(iter, MESSAGE_KEY_Notification_4_OnDefaultTimerEnabled);
	if(notification_4_OnDefaultTimerEnabled) {
		settings.notifications[3].onDefaultTimerEnabled = notification_4_OnDefaultTimerEnabled->value->int32 == 1;
	}
	Tuple *notification_4_OnShortTimerEnabled = dict_find(iter, MESSAGE_KEY_Notification_4_OnShortTimerEnabled);
	if(notification_4_OnShortTimerEnabled) {
		settings.notifications[3].onShortTimerEnabled = notification_4_OnShortTimerEnabled->value->int32 == 1;
	}
	Tuple *notification_4_VibePatternIndex = dict_find(iter, MESSAGE_KEY_Notification_4_VibePatternIndex);
	if(notification_4_VibePatternIndex) {
		settings.notifications[3].vibePatternIndex = atoi(notification_4_VibePatternIndex->value->cstring);
	}
	Tuple *notification_4_StateMessage = dict_find(iter, MESSAGE_KEY_Notification_4_StateMessage);
	if(notification_4_StateMessage) {
		settings.notifications[3].stateMessage = notification_4_StateMessage->value->cstring;
	}

	Tuple *notification_5_Second = dict_find(iter, MESSAGE_KEY_Notification_5_Second);
	if(notification_5_Second) {
		settings.notifications[4].second = notification_5_Second->value->int32;
	}
	Tuple *notification_5_OnDefaultTimerEnabled = dict_find(iter, MESSAGE_KEY_Notification_5_OnDefaultTimerEnabled);
	if(notification_5_OnDefaultTimerEnabled) {
		settings.notifications[4].onDefaultTimerEnabled = notification_5_OnDefaultTimerEnabled->value->int32 == 1;
	}
	Tuple *notification_5_OnShortTimerEnabled = dict_find(iter, MESSAGE_KEY_Notification_5_OnShortTimerEnabled);
	if(notification_5_OnShortTimerEnabled) {
		settings.notifications[4].onShortTimerEnabled = notification_5_OnShortTimerEnabled->value->int32 == 1;
	}
	Tuple *notification_5_VibePatternIndex = dict_find(iter, MESSAGE_KEY_Notification_5_VibePatternIndex);
	if(notification_5_VibePatternIndex) {
		settings.notifications[4].vibePatternIndex = atoi(notification_5_VibePatternIndex->value->cstring);
	}
	Tuple *notification_5_StateMessage = dict_find(iter, MESSAGE_KEY_Notification_5_StateMessage);
	if(notification_5_StateMessage) {
		settings.notifications[4].stateMessage = notification_5_StateMessage->value->cstring;
	}

  // Save the new settings to persistent storage
  saveSettings();
}

void initSettings(void) {
	//APP_LOG(APP_LOG_LEVEL_DEBUG, "init settings");
	loadSettings();

	// Listen for AppMessages
	app_message_register_inbox_received(inboxReceivedHandler);
	app_message_open(512, 512);
}

bool isVibesEnabled(void) {
	return settings.vibesEnabled;
}

bool invertVibesEnabled(void) {
	settings.vibesEnabled = !settings.vibesEnabled;
	saveSettings();
	return settings.vibesEnabled;
}

bool isVibesOnNotificationsEnabled(void) {
	return (settings.vibesEnabled && settings.vibesOnNotificationsEnabled);
}

const VibePattern *getVibesOnTimerExpiredPattern(void) {
	if(settings.vibesEnabled) {
		return VIBE_PATTERNS[settings.vibesOnTimerExpiredPatternIndex];
	}
	return NULL;
}

const VibePattern *getOnButtonPressedVibePattern(void) {
	if(settings.vibesEnabled) {
		return VIBE_PATTERNS[settings.vibesOnButtonPressedPatternIndex];
	}
	return NULL;
}

bool invertVibesOnButtonPressedEnabled(void) {
	if(settings.vibesOnButtonPressedPatternIndex > VIBE_OFF_PATTERN_INDEX) {
		settings.vibesOnButtonPressedPatternIndex = VIBE_OFF_PATTERN_INDEX;
	} else {
		settings.vibesOnButtonPressedPatternIndex = VIBE_DEFAULT_INDEX;
	}
	saveSettings();
	return (settings.vibesOnButtonPressedPatternIndex > VIBE_OFF_PATTERN_INDEX);
}

const VibePattern *getOnButtonStartsDefaultTimerVibePattern(void) {
	if(settings.vibesEnabled) {
		if(settings.vibesOnButtonStartsDefaultTimerPatternIndex > VIBE_OFF_PATTERN_INDEX) {
			return VIBE_PATTERNS[settings.vibesOnButtonStartsDefaultTimerPatternIndex];
		}
	}
	return VIBE_PATTERNS[settings.vibesOnButtonPressedPatternIndex];
}

const VibePattern *getOnButtonStartsShortTimerVibePattern(void) {
	if(settings.vibesEnabled) {
		if(settings.vibesOnButtonStartsShortTimerPatternIndex > VIBE_OFF_PATTERN_INDEX) {
			return VIBE_PATTERNS[settings.vibesOnButtonStartsShortTimerPatternIndex];
		}
	}
	return VIBE_PATTERNS[settings.vibesOnButtonPressedPatternIndex];
}

const Notification *getNotification(int second, bool isShortTimer) {
	for(int i = 0; i < NOTIFICATION_MAX; i++) {
		if(settings.notifications[i].second == second && ((!isShortTimer && settings.notifications[i].onDefaultTimerEnabled) || (isShortTimer && settings.notifications[i].onShortTimerEnabled))) {
			return &settings.notifications[i];
		}
	}
	return NULL;
}

const VibePattern *getVibesNotificationPattern(const Notification *notification) {
	if(notification != NULL && settings.vibesEnabled && settings.vibesOnNotificationsEnabled) {
		return VIBE_PATTERNS[notification->vibePatternIndex];
	}
	return NULL;
}

char *getNotificationStateMessage(const Notification *notification) {
	if(notification != NULL) {
		return notification->stateMessage;
	}
	return NULL;
}

int getButtonPressedLongDuration(void) {
	return BUTTON_LONG_PRESSED_DURATION_DEFAULT;
}

GColor getBackgroundColor(void) {
	return COLOR_BGCOLOR_DEFAULT;
}

GColor getForegroundColor(void) {
	return COLOR_FORECOLOR_DEFAULT;
}

char *getStateMessageVibesOn(void) {
	return STATE_MSG_VIBRATION_ON;
}

char *getStateMessageVibesOff(void) {
	return STATE_MSG_VIBRATION_OFF;
}

char *getStateMessageVibesOnButtonPressedOn(void) {
	return STATE_MSG_VIBRATION_BUTTON_ON;
}

char *getStateMessageVibesOnButtonPressedOff(void) {
	return STATE_MSG_VIBRATION_BUTTON_OFF;
}
