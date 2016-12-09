#include <pebble.h>

#define COLOR_BGCOLOR_DEFAULT GColorBlack
#define COLOR_FORECOLOR_DEFAULT GColorWhite
#define STROKE_WIDTH 2
#define BUTTON_LONG_PRESSED_DURATION_DEFAULT 1000 // in milliseconds
#define STATE_MSG_VIBRATION_ON "VIBE ON"
#define STATE_MSG_VIBRATION_OFF "VIBE OFF"
#define STATE_MSG_VIBRATION_BUTTON_ON "VIBE ON BUTTON ON"
#define STATE_MSG_VIBRATION_BUTTON_OFF "VIBE ON BUTTON OFF"
#define VIBE_SHORT 150
#define VIBE_LONG 400
#define VIBE_PAUSE 200
#define VIBE_ENABLED_DEFAULT true
#define VIBE_ON_NOTIFICATION_ENABLED_DEFAULT true
#define VIBE_DEFAULT_INDEX 1
#define VIBE_OFF_PATTERN_INDEX 0
#define VIBE_ON_TIMER_EXPIRED_PATTERN_INDEX_DEFAULT 2
#define VIBE_ON_BUTTON_PRESSED_PATTERN_INDEX_DEFAULT 0
#define VIBE_ON_BUTTON_STARTS_DEFAULT_TIMER_PATTERN_INDEX_DEFAULT 1
#define VIBE_ON_BUTTON_STARTS_SHORT_TIMER_PATTERN_INDEX_DEFAULT 3

#define FONT_DEFAULT FONT_KEY_GOTHIC_18
#define FONT_DEFAULT_SIZE 22 // additional space needed for letters like 'g' 
#define FONT_TICKER FONT_KEY_ROBOTO_BOLD_SUBSET_49
#define FONT_TICKER_SIZE 64 // why not 49???

#define NOTIFICATION_MAX 5
#define NOTIFICATION_MSG_MAX_LEN 40

#define SETTINGS_KEY_VERSION 1
#define SETTINGS_KEY 100
#define SETTINGS_KEY_NOTIFICATION_MSG_START 1001

typedef struct Notification {
	int second;
	bool onDefaultTimerEnabled;
	bool onShortTimerEnabled;
	int vibePatternIndex;
	char *stateMessage;
} __attribute__((__packed__)) Notification;

// Structure containing our settings
typedef struct ClaySettings {
	bool vibesEnabled;
	bool vibesOnNotificationsEnabled;
	int vibesOnTimerExpiredPatternIndex;
	int vibesOnButtonPressedPatternIndex;
	int vibesOnButtonStartsDefaultTimerPatternIndex;
	int vibesOnButtonStartsShortTimerPatternIndex;
	Notification notifications[NOTIFICATION_MAX];
} __attribute__((__packed__)) ClaySettings;

// The following function may be used from the project's .c-file
void initSettings(void);
bool isVibesEnabled(void);
bool invertVibesEnabled(void);
bool isVibesOnNotificationsEnabled(void);
const VibePattern *getVibesOnTimerExpiredPattern(void);
const VibePattern *getOnButtonPressedVibePattern(void);
bool invertVibesOnButtonPressedEnabled(void);
const VibePattern *getOnButtonStartsDefaultTimerVibePattern(void);
const VibePattern *getOnButtonStartsShortTimerVibePattern(void);
const Notification *getNotification(int, bool);
const VibePattern *getVibesNotificationPattern(const Notification *);
char *getNotificationStateMessage(const Notification *);
int getButtonPressedLongDuration(void);
GColor getBackgroundColor(void);
GColor getForegroundColor(void);
char *getStateMessageVibesOn(void);
char *getStateMessageVibesOff(void);
char *getStateMessageVibesOnButtonPressedOn(void);
char *getStateMessageVibesOnButtonPressedOff(void);
