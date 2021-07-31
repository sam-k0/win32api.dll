


#include <Windows.h>
#include <stdio.h>
#include <string>

#define GMEXPORT extern "C" __declspec(dllexport)

GMEXPORT int checkWindowName(const char* windowName) {
    // get handle to the searched window name
    HWND winHandle = FindWindow(NULL,windowName);
    // check if handle is null...
    if(winHandle == NULL)
    {
        return -1;
    }
    return 1;
}

GMEXPORT char* getWindowNameC() {
    char title[500]; // get the
    GetWindowText(GetForegroundWindow(), title, 500);
    // typecast to char
    char* titleptr = title;
    return titleptr;
}
