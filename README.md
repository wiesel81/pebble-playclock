# PlayClock
by Michael Krenn, American Football official in Austria.

Playclock for American Football officials working as on-field timekeeper based on the NCAA Rules 2016.

With this watchapp it is possible to operate the 40/25 on the field without taking a look at the watch and missing action. It works offline although most of the settings like notifications and vibration patterns are customizable via phone when connected.

Pressing the up- or down-button starts the 40- or 25-second countdown, giving a vibration signal as confirmation.
Pressing one of these buttons long allows to preset the timer, starting it with the select-button.
Pressing the select-button long stops the current countdown or activates standby-mode, which allows to enable/disable vibration using the select-button again.
5 notifications can be configured individually. Per default the playclock sends a vibration signal when 25 seconds left (ball ready?), at 10 and 5 seconds and, of course, when the timer expires.

## How it works
The back-button (the one on the left side) always closes the Playclock watchapp, so be careful not pressing it accidentally!

The 3 buttons on the right side always works as follows unless noted at the different state descriptions:

#### UP-Button (*1x short vibe*)
Starts 40" countdown (new state: *40" RUNNING*)
#### UP-Button pressed long
Presets timer to 40", not running (new state: *40" PRESET*)
#### SELECT-Button
Disabled - no action
#### SELECT-Button pressed long
Set PlayClock back to standby (new state: *STANDBY*)
#### DOWN-Button (*2x short vibes*)
Starts 25" countdown (new state: *25" RUNNING*)
#### DOWN-Button pressed long
Presets timer to 25", not running (new state: *25" PRESET*)

The timer can have the following states:

### STANDBY (start screen)
![STANDBY](doc/standby.png "STANDBY")
#### SELECT-Button
Vibration signals can be enabled / disabled immediately without connecting to the phone.

### 40" RUNNING
![40sec RUNNING](doc/40_running.png "40sec RUNNING")
#### SELECT-Button pressed long
Stops 40" countdown (new state: *40" STOPPED*)

### 40" EXPIRED (*1x long vibe*)
![40sec EXPIRED](doc/40_expired.png "40sec EXPIRED")

### 40" STOPPED
![40sec STOPPED](doc/40_stopped.png "40sec STOPPED")

### 40" PRESET
![40sec PRESET](doc/40_preset.png "40sec PRESET")
#### SELECT-Button (*1x short vibe*)
Starts 40" countdown (new state: *40" RUNNING*)

### 25" RUNNING / 25" EXPIRED / 25" STOPPED / 25" PRESET
The 25 second countdown works the same way as described for the 0 second countdown.

## Notifications
At least up to 5 notifications can be configured via smartphone. The following 3 notifications are set by default:

### BALL READY? (*1x short vibe*)
When the timer reads *25*, the state message changes from *40" RUNNING* to *BALL READY?* and a notification (one short vibration) is sent.
Of course this happens only when the default timer (40 seconds) is running.

### 10" WARINING! (*2x short vibe*)
When 10 seconds left, the state message *10" WARNING!* is displayed and a notification (two short vibrations) is sent.

### 5" WARINING! (*2x short vibe*)
When 5 seconds left, the state message *5" WARNING!* is displayed and a notification (two short vibrations) is sent.

## Settings
On the smartphone the vibration patterns, notifications and other features of the PlayClock can be configured very easily. Note that there is only communication from the smartphone to the Pebble watch implemented, not the other way! So enabling / disabling the vibration on the Pebble (SELECT-Button pressed in standby mode) is overwritten when the settings on the smartphone are saved the next time (while connected to the Pebble watch, of course).

![global settings](doc/settings_global.png "global settings")
![button settings](doc/settings_buttons.png "button settings")
![notification settings](doc/settings_notification1.png "notification settings")
![notification settings](doc/settings_notification.png "notification settings")
