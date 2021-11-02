# win32api.dll
 A dll to mess with some basic win32 api functions. Can be used in GMS1.4 and GMS2(currently being tested)

**Disclaimer: the releases may not be as up to date as the .dll file in bin>Debug>GM_getFGwindow.dll **

# win32Api_GM
win32ApiGM is a dll / extension for GameMaker: Studio to interact with the windows api. You can use Messageboxes, execute (restricted) shell commands, make a window blinking in the taskbar or change the icon of the game window in runtime.
## Feature list:

 

 - set window width and height
 - check if there's a window with a requested name opened
 - get the title of the currently focused window at any time
 - show messageboxes: 
	 - "Normal" messageboxes with just an OK button,
	 - messageboxes with yes and no button,
	 - messageboxes with a continue, try again and cancel button
- set the game's main window icon to any icon file
- execute the windows shell (shellExecuteEx)
- set the window's icon in taskbar as flashing
	- this can either be done to the main game window or any window if you pass it's title 
- set window position on screen
- set window title
- Experimental: Get information on the current device: Number of processors and username

## Documentation
Documentation will be fully available soon, there are some functions lacking further explanation right now.
***note: void return type means the returned value is arbitrary and not useful.
Also, the datatype "double" is synonym to real, float, ty_real, same with string being synonym to ty_string or char****

## ⚠️(not up-to-date!) dll functions (when using the raw dll)
|function name|parameters (first to last)  |returns|description|
|--|--|--|--|
| setWindowTitle| (windowTitle: string)|void|Sets the current game window's title|
|setWindowOptions|(x: double, y: double, width: double, height: double)|void|Sets the game window's position and width on the screen
|getProcessors|()|double|Returns the number of processors
|getUser|()|string|Returns the username as a string (Currently WIP, may not work as expected)
|checkWindowName|(windowName: string, returnValue: double)|double|Returns a 1 if the window with title specified in windowName is found, else 0, returnValue must be passed as 1
|getWindowNameC|()|string|Returns the title of the currently focused window
|showMessageboxOk|(headline: string, bodytext: string)|void|Shows a messagebox with OK button and the specified text
|showMessageboxCTC|(headline: string, bodytext: string, returnVal: double)|double|If the user pressed "cancel" returns 0, "try again" = 1, "continue" = 2
|showMessageboxYN|(headline: string, bodytext: string, returnVal: double)|double| returns "yes" = 1, "no" = 0
|setWindowIcon|(icopath: string)|void|sets the icon to the ico file specified in icopath.. Remember to use double backslashes!
|shellExecEx|(verb: string, file: string, showtype: string)|void|Executes a shell ([ShellExecute](https://docs.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-shellexecutea)). "[showtype](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow)" is an integer value passed as a string.
|setFlashingSelf|(flashCount: double, flashRateMillis: double)|void|Flashes the window icon in the taskbar flashCount amount of times [with flashRateMillis](https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-flashwinfo) rate
|setFlashingName|(windowName: string, flashCount: double, flashRateMillis: double)|void|Does the same thing as *self but this time to another window that has windowName as its title

