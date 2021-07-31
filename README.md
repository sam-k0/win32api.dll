# win32api.dll
 A DLL to get the title of the currently focused window in GameMaker. Idk why you'd ever need this but why not.

## char* getWindowNameC();
```gml
external_define("GM_getFGwindow.dll","getWindowNameC",dll_cdecl,ty_string,0);
var result = external_call("getWindowNameC");
external_free("GM_getFGwindow.dll");
```
where `result` will now be the title of whatever window is currently the foreground one.

## int checkWindowName(const char* windowName);

```gml
var checkname = "owo"
external_define("GM_getFGwindow.dll","checkWindowName",dll_cdecl,ty_real,1,ty_string);
var result = external_call("checkWindowName","owo");
external_free("GM_getFGwindow.dll");
```
where `result` will be <0 if the window title specified in `checkname` is not found. If it is found, result will be >0.

## int showMessageboxCTC(const char* passedHandle, const char* headline, const char* bodytext)

This will show a messagebox with the buttons Cancel, Try again and continue.
for `passedHandle` you'll have to pass `window_handle()` from gms as this is the window handle of the game window

Headline and bodytext are ty_strings to gm and do what their name suggests.

The function returns 0 (Cancel button pressed), 1 (Try Again pressed), 2 (Continue button pressed) as an ty_real.

## showMessageboxYN(const char* passedHandle, const char* headline, const char* bodytext)

The same as above but with Yes and No button.

Returns 0 (No pressed), 1 (Yes pressed)

## setWindowIcon(const char* passedHandle, const char* icopath)

Takes (again) the game window handle (`window_handle()`) and a ty_string to the local icon path.
* You can also use this to reset the current icon I think.. Just pass an empty string ("")

returns ty_real <0 if failed or 1 if successful.



For further reference, check the sourcecode, main.cpp. You'll understand.


