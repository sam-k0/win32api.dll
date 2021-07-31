# getWindowName
 A DLL to get the title of the currently focused window in GameMaker. Idk why you'd ever need this but why not.

## char* getWindowNameC();

    external_define("GM_getFGwindow.dll","getWindowNameC",dll_cdecl,ty_string,0);
    var result = external_call("getWindowNameC");
    external_free("GM_getFGwindow.dll");

where `result` will now be the title of whatever window is currently the foreground one.

## int checkWindowName(const char* windowName);

    var checkname = "owo"
    external_define("GM_getFGwindow.dll","checkWindowName",dll_cdecl,ty_real,1,ty_string);
    var result = external_call("checkWindowName","owo");
    external_free("GM_getFGwindow.dll");

where `result` will be <0 if the window title specified in `checkname` is not found. If it is found, result will be >0.

For further reference, check the sourcecode, main.cpp. You'll understand.


