# Compiled Firmware Version Notes
This folder is meant to store incremental, working versions of keyboard firmware as I add features.  Keeping these in source control instead of compiling them as-needed removes environment setup difficulties and simply allows for downloading of a new file and flashing directly with QMK Toolbox, which can be executed without an installer.  This gives the benefit of being able to flash my keyboards on work (and other non-personal) machines without leaving anything behind.

## GMMK Pro
### Version 1
This is the initial version that I based off of files in the repo made by `gourdo1` and `jonavin`.  The features listed below are supported:

- Keymap has 3 layers
	- The base layer (0) simply matches the Domikey keycaps that I use, with the following special cases:
		- [Func] => Activates the function layer (described below) when held
		- [Code] => Activates the code layer (described below) when held
        - [Rotary press] => Mute/unmute output audio
        - [Rotary right/left] => Increase/decrease output audio master volume
	- The function layer (1) supports the following functions (all keys not listed are set to `TRANSPARENT`):
		- [ESC] => Reset keyboard (acts like USB unplug/plug)
		- [GUI] => Enables/disables the GUI (Windows key) keycode [Default is `Enabled`]
		- [SPACE] => Clears the board EEPROM, setting all memory values to default
		- [N] => Enables/Disables N-key rollover [Default is `Enabled`]
		- [L] => Activates the Key Lock feature (https://docs.qmk.fm/#/feature_key_lock)
		- [=] => Opens the Calculator app by sending the `CALC` keycode
		- [\\] => Forces keyboard into bootloader mode for flashing new firmware
		- [Rotary press] => Enables/disables RGB [Default is `Enabled`]
		- [Rotary right/left] => Increase/decrease RGB brightness
		- [UP / DOWN] => Increase/decrease RGB animation speed
		- [LEFT / RIGHT] => Iterate through all supported RGB animations
	- The code layer (2) supports the following functions (all keys not listed are set to `TRANSPARENT`):
		- None at this time
- RGB is just a simple all-LEDs-included setup
