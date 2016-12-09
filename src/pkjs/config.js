module.exports = [
  {
    "type": "heading",
    "defaultValue": "PLAYCLOCK Configuration",
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Global",
      },
			{
        "type": "toggle",
        "messageKey": "VibesEnabled",
        "label": "Enable vibration",
				"description": "If disabled, all other vibration settings are ignored.",
        "defaultValue": true,
      },
      {
        "type": "toggle",
        "messageKey": "VibesOnNotificationsEnabled",
        "label": "Enable vibration on notifications",
				"description": "If disabled, all custom vibration settings for notifications (except expired timer) are ignored.",
        "defaultValue": true,
      },
			{
				"type": "select",
				"messageKey": "VibesOnTimerExpiredPatternIndex",
				"label": 'Vibration pattern when timer expires, reaching 0"',
				"description": "Not affected by the 'Enable vibration on notifications' setting.",
				"defaultValue": "2",
				"options": [
					{ 
						"label": "Off", 
						"value": "0" 
					},
					{ 
						"label": "Short",
						"value": "1" 
					},
					{ 
						"label": "Long",
						"value": "2" 
					},
					{ 
						"label": "2x Short",
						"value": "3" 
					},
					{ 
						"label": "Short + Long",
						"value": "4" 
					},
					{ 
						"label": "Long + Short",
						"value": "5" 
					},
					{ 
						"label": "2x Long",
						"value": "6" 
					},
					{ 
						"label": "3x Short",
						"value": "7" 
					},
				],
			},
		],
	},
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Buttons",
      },
			{
				"type": "select",
				"messageKey": "VibesOnButtonPressedPatternIndex",
				"label": "Vibration pattern on pressing a button",
				"description": "If set to 'Off', vibration settings for starting a timer are still active.",
				"defaultValue": "0",
				"options": [
					{ 
						"label": "Off", 
						"value": "0" 
					},
					{ 
						"label": "Short",
						"value": "1" 
					},
					{ 
						"label": "Long",
						"value": "2" 
					},
					{ 
						"label": "2x Short",
						"value": "3" 
					},
					{ 
						"label": "Short + Long",
						"value": "4" 
					},
					{ 
						"label": "Long + Short",
						"value": "5" 
					},
					{ 
						"label": "2x Long",
						"value": "6" 
					},
					{ 
						"label": "3x Short",
						"value": "7" 
					},
				],
			},
			{
				"type": "select",
				"messageKey": "VibesOnButtonStartsDefaultTimerPatternIndex",
				"label": 'Vibration pattern on pressing a button to start the default timer (40")',
				"description": "If set to 'Off', a vibration for pressing a button may occur.",
				"defaultValue": "1",
				"options": [
					{ 
						"label": "Off", 
						"value": "0" 
					},
					{ 
						"label": "Short",
						"value": "1" 
					},
					{ 
						"label": "Long",
						"value": "2" 
					},
					{ 
						"label": "2x Short",
						"value": "3" 
					},
					{ 
						"label": "Short + Long",
						"value": "4" 
					},
					{ 
						"label": "Long + Short",
						"value": "5" 
					},
					{ 
						"label": "2x Long",
						"value": "6" 
					},
					{ 
						"label": "3x Short",
						"value": "7" 
					},
				],
			},
			{
				"type": "select",
				"messageKey": "VibesOnButtonStartsShortTimerPatternIndex",
				"label": 'Vibration pattern on pressing a button to start the short timer (25")',
				"description": "If set to 'Off', a vibration for pressing a button may occur.",
				"defaultValue": "3",
				"options": [
					{ 
						"label": "Off", 
						"value": "0" 
					},
					{ 
						"label": "Short",
						"value": "1" 
					},
					{ 
						"label": "Long",
						"value": "2" 
					},
					{ 
						"label": "2x Short",
						"value": "3" 
					},
					{ 
						"label": "Short - Long",
						"value": "4" 
					},
					{ 
						"label": "Long - Short",
						"value": "5" 
					},
					{ 
						"label": "2x Long",
						"value": "6" 
					},
					{ 
						"label": "3x Short",
						"value": "7" 
					},
				],
			},
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Notification 1"
      },
			{
				"type": "slider",
				"messageKey": "Notification_1_Second",
				"label": "The second this notification should occur.",
				"min": 0,
				"max": 39,
				"step": 1,
				"defaultValue": 25,
			},
      {
        "type": "toggle",
        "messageKey": "Notification_1_OnDefaultTimerEnabled",
        "label": 'Enable this notification for default timer (40").',
        "defaultValue": true,
      },
      {
        "type": "toggle",
        "messageKey": "Notification_1_OnShortTimerEnabled",
        "label": 'Enable this notification for short timer (25").',
        "defaultValue": false,
      },
			{
				"type": "select",
				"messageKey": "Notification_1_VibePatternIndex",
				"label": "Vibration pattern for this notification",
				"defaultValue": "1",
				"options": [
					{ 
						"label": "Off", 
						"value": "0" 
					},
					{ 
						"label": "Short",
						"value": "1" 
					},
					{ 
						"label": "Long",
						"value": "2" 
					},
					{ 
						"label": "2x Short",
						"value": "3" 
					},
					{ 
						"label": "Short - Long",
						"value": "4" 
					},
					{ 
						"label": "Long - Short",
						"value": "5" 
					},
					{ 
						"label": "2x Long",
						"value": "6" 
					},
					{ 
						"label": "3x Short",
						"value": "7" 
					},
				],
			},
			{
				"type": "input",
				"messageKey": "Notification_1_StateMessage",
				"label": "State message for this notification",
				"description": "If left empty, the state message is not changed when this notification occurs.",
				"defaultValue": "BALL READY?",
				"attributes": {
					"placeholder": "eg: WARNING!",
					"limit": 20
				}
			},
		],
	},
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Notification 2"
      },
			{
				"type": "slider",
				"messageKey": "Notification_2_Second",
				"label": "The second this notification should occur.",
				"min": 0,
				"max": 39,
				"step": 1,
				"defaultValue": 10,
			},
      {
        "type": "toggle",
        "messageKey": "Notification_2_OnDefaultTimerEnabled",
        "label": 'Enable this notification for default timer (40").',
        "defaultValue": true,
      },
      {
        "type": "toggle",
        "messageKey": "Notification_2_OnShortTimerEnabled",
        "label": 'Enable this notification for short timer (25").',
        "defaultValue": true,
      },
			{
				"type": "select",
				"messageKey": "Notification_2_VibePatternIndex",
				"label": "Vibration pattern for this notification",
				"defaultValue": "3",
				"options": [
					{ 
						"label": "Off", 
						"value": "0" 
					},
					{ 
						"label": "Short",
						"value": "1" 
					},
					{ 
						"label": "Long",
						"value": "2" 
					},
					{ 
						"label": "2x Short",
						"value": "3" 
					},
					{ 
						"label": "Short - Long",
						"value": "4" 
					},
					{ 
						"label": "Long - Short",
						"value": "5" 
					},
					{ 
						"label": "2x Long",
						"value": "6" 
					},
					{ 
						"label": "3x Short",
						"value": "7" 
					},
				],
			},
			{
				"type": "input",
				"messageKey": "Notification_2_StateMessage",
				"label": "State message for this notification",
				"description": "If left empty, the state message is not changed when this notification occurs.",
				"defaultValue": '10" WARNING!',
				"attributes": {
					"placeholder": "eg: WARNING!",
					"limit": 20
				}
			},
		]
	},
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Notification 3"
      },
			{
				"type": "slider",
				"messageKey": "Notification_3_Second",
				"label": "The second this notification should occur.",
				"min": 0,
				"max": 39,
				"step": 1,
				"defaultValue": 5,
			},
      {
        "type": "toggle",
        "messageKey": "Notification_3_OnDefaultTimerEnabled",
        "label": 'Enable this notification for default timer (40").',
        "defaultValue": true,
      },
      {
        "type": "toggle",
        "messageKey": "Notification_3_OnShortTimerEnabled",
        "label": 'Enable this notification for short timer (25").',
        "defaultValue": true,
      },
			{
				"type": "select",
				"messageKey": "Notification_3_VibePatternIndex",
				"label": "Vibration pattern for this notification",
				"defaultValue": "3",
				"options": [
					{ 
						"label": "Off", 
						"value": "0" 
					},
					{ 
						"label": "Short",
						"value": "1" 
					},
					{ 
						"label": "Long",
						"value": "2" 
					},
					{ 
						"label": "2x Short",
						"value": "3" 
					},
					{ 
						"label": "Short - Long",
						"value": "4" 
					},
					{ 
						"label": "Long - Short",
						"value": "5" 
					},
					{ 
						"label": "2x Long",
						"value": "6" 
					},
					{ 
						"label": "3x Short",
						"value": "7" 
					},
				],
			},
			{
				"type": "input",
				"messageKey": "Notification_3_StateMessage",
				"label": "State message for this notification",
				"description": "If left empty, the state message is not changed when this notification occurs.",
				"defaultValue": '5" WARNING!',
				"attributes": {
					"placeholder": "eg: WARNING!",
					"limit": 20
				}
			},
		]
	},
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Notification 4"
      },
			{
				"type": "slider",
				"messageKey": "Notification_4_Second",
				"label": "The second this notification should occur.",
				"min": 0,
				"max": 39,
				"step": 1,
				"defaultValue": 0,
			},
      {
        "type": "toggle",
        "messageKey": "Notification_4_OnDefaultTimerEnabled",
        "label": 'Enable this notification for default timer (40").',
        "defaultValue": false,
      },
      {
        "type": "toggle",
        "messageKey": "Notification_4_OnShortTimerEnabled",
        "label": 'Enable this notification for short timer (25").',
        "defaultValue": false,
      },
			{
				"type": "select",
				"messageKey": "Notification_4_VibePatternIndex",
				"label": "Vibration pattern for this notification",
				"defaultValue": "0",
				"options": [
					{ 
						"label": "Off", 
						"value": "0" 
					},
					{ 
						"label": "Short",
						"value": "1" 
					},
					{ 
						"label": "Long",
						"value": "2" 
					},
					{ 
						"label": "2x Short",
						"value": "3" 
					},
					{ 
						"label": "Short - Long",
						"value": "4" 
					},
					{ 
						"label": "Long - Short",
						"value": "5" 
					},
					{ 
						"label": "2x Long",
						"value": "6" 
					},
					{ 
						"label": "3x Short",
						"value": "7" 
					},
				],
			},
			{
				"type": "input",
				"messageKey": "Notification_4_StateMessage",
				"label": "State message for this notification",
				"description": "If left empty, the state message is not changed when this notification occurs.",
				"attributes": {
					"placeholder": "eg: WARNING!",
					"limit": 20
				}
			},
		]
	},
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Notification 5"
      },
			{
				"type": "slider",
				"messageKey": "Notification_5_Second",
				"label": "The second this notification should occur.",
				"min": 0,
				"max": 39,
				"step": 1,
				"defaultValue": 0,
			},
      {
        "type": "toggle",
        "messageKey": "Notification_5_OnDefaultTimerEnabled",
        "label": 'Enable this notification for default timer (40").',
        "defaultValue": false,
      },
      {
        "type": "toggle",
        "messageKey": "Notification_5_OnShortTimerEnabled",
        "label": 'Enable this notification for short timer (25").',
        "defaultValue": false,
      },
			{
				"type": "select",
				"messageKey": "Notification_5_VibePatternIndex",
				"label": "Vibration pattern for this notification",
				"defaultValue": "0",
				"options": [
					{ 
						"label": "Off", 
						"value": "0" 
					},
					{ 
						"label": "Short",
						"value": "1" 
					},
					{ 
						"label": "Long",
						"value": "2" 
					},
					{ 
						"label": "2x Short",
						"value": "3" 
					},
					{ 
						"label": "Short - Long",
						"value": "4" 
					},
					{ 
						"label": "Long - Short",
						"value": "5" 
					},
					{ 
						"label": "2x Long",
						"value": "6" 
					},
					{ 
						"label": "3x Short",
						"value": "7" 
					},
				],
			},
			{
				"type": "input",
				"messageKey": "Notification_5_StateMessage",
				"label": "State message for this notification",
				"description": "If left empty, the state message is not changed when this notification occurs.",
				"attributes": {
					"placeholder": "eg: WARNING!",
					"limit": 20
				}
			},
		]
	},
  {
    "type": "submit",
    "defaultValue": "Save Settings"
  },
];
