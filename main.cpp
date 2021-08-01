
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <vector>
#define GMEXPORT extern "C" __declspec(dllexport)

/*
TODO: Change return types from int to double.
Check window flashing functions.

*/



HWND resolveHandle(const char* _passedHandle)
{
    std::string hstr(_passedHandle);
    HWND parentHwnd = (HWND)std::stoull(hstr);

    return parentHwnd;
}

//char* returnValPtr = &returnVal[0]; // Convert from string to char*

GMEXPORT int checkWindowName(const char* windowName) {
    // Checks if a window with a certain title exists

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
    // Shows the title of the currently focused window
    char title[500]; // get the
    GetWindowText(GetForegroundWindow(), title, 500);
    // typecast to char
    char* titleptr = title;
    return titleptr;
}

GMEXPORT int showMessageboxOk(const char* passedHandle, const char* headline, const char* bodytext)
{
    // Takes game maker window handle, headline, body text
    // returns whatever the msgbox id is.
    int msgboxID = MessageBox(
        resolveHandle(passedHandle),
        bodytext,
        headline,
        MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON2
    );

    return msgboxID;
}


GMEXPORT int showMessageboxTest(const char* passedHandle)
{
    // Takes game maker window handle, headline, body text
    // returns whatever the msgbox id is.


    int msgboxID = MessageBox(
        resolveHandle(passedHandle),
        "Is this a body?",
        "Is this a headline?",
        MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON2
    );

    return msgboxID;
}

GMEXPORT int showMessageboxCTC(const char* passedHandle, const char* headline, const char* bodytext)
{
    // this will show a messagebox with a continue, try again and cancel button.
    int returnVal = 0; // Normalized button output value 0-2
    int msgboxID = MessageBox(
        resolveHandle(passedHandle),
        bodytext,
        headline,
        MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
    );


    switch (msgboxID)
    {
    case IDCANCEL:
        // TODO: add code
        returnVal = 0;
        break;
    case IDTRYAGAIN:
        // TODO: add code
        returnVal = 1;
        break;
    case IDCONTINUE:
        // TODO: add code
        returnVal = 2;
        break;
    }

    return returnVal;
}


GMEXPORT int showMessageboxYN(const char* passedHandle, const char* headline, const char* bodytext)
{   // shows a messagebox with yes and no button, returns 0 for no and 1 for yes
    int returnVal = 0;
    int msgboxID = MessageBox(
        resolveHandle(passedHandle),
        bodytext,
        headline,
        MB_ICONEXCLAMATION | MB_YESNO
    );

    if (msgboxID == IDYES)
    {
        // TODO: add code
        returnVal = 1;
    }

    return returnVal;
}

GMEXPORT int setWindowIcon(const char* passedHandle, const char* icopath) // Currently unstable
{   // sets an icon to the game window. Returns 1 if success and <0 if not
    // Reference: http://www.cplusplus.com/forum/windows/188709/
    HWND handle = resolveHandle(passedHandle);

    HICON hWindowIcon=NULL;
    HICON hWindowIconBig=NULL;
    std::string stricon = icopath;

    // If icon exists, destroy it

    if(hWindowIcon!=NULL)
        DestroyIcon(hWindowIcon);
    if(hWindowIconBig!=NULL)
        DestroyIcon(hWindowIconBig);
    // set new
    if(stricon=="")
    {
        return -1; // Stricon is empty. return.
    }
    else
    {
        hWindowIcon =(HICON)LoadImage(NULL, stricon.c_str(), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
        hWindowIconBig =(HICON)LoadImage(NULL, stricon.c_str(), IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
        SendMessage( HWND(handle), WM_SETICON, ICON_SMALL, (LPARAM)hWindowIcon );
        SendMessage( HWND(handle), WM_SETICON, ICON_BIG, (LPARAM)hWindowIconBig );
    }
    return 1;
}

GMEXPORT int shellExec(const char* passedHandle, const char* lpOperation, const char* lpFile)
{
    //Executes a shell command with parameters given.
    // https://docs.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-shellexecutea?redirectedfrom=MSDN
    ShellExecuteA(
                    resolveHandle(passedHandle),
                    lpOperation,
                    lpFile,
                    NULL,
                    NULL,
                    1
                  );
    return 1;
}


GMEXPORT int shellExecEx(const char* Verb, const char* File, const char* Showtype)
{
    // Takes the Showtype as string : https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow
    ShellExecute(
                 NULL,
                 Verb, // For example "open"
                 File, // "C:\\Windows\\system32\\mspaint.exe"
                 NULL,
                 NULL,
                 std::stoi(Showtype)
                 );
    return 1;
}

GMEXPORT int setFlashingHandle(const char* passedHandle, const char* flashCount, const char* flashRateMillis)
{
    HWND hHandle = resolveHandle(passedHandle); // Set handle to passed handle
    FLASHWINFO pf;                     // instanciate a struct of type flash window info
    pf.cbSize = sizeof(FLASHWINFO);
    pf.hwnd = hHandle;
    pf.dwFlags = FLASHW_TIMER|FLASHW_TRAY; // (or FLASHW_ALL to flash and if it is not minimized)
    pf.uCount = std::stoi(flashCount);
    pf.dwTimeout = std::stoi(flashRateMillis);

    FlashWindowEx(&pf);
    return 1;
}

GMEXPORT int setFlashingName(const char* windowName, const char* cnt, const char* rate) // Doesnt take the int values .. Just ignores it
{
    HWND hHandle = FindWindow(NULL,windowName); // Set handle to passed handle
    FLASHWINFO pf;                     // instanciate a struct of type flash window info
    pf.cbSize = sizeof(FLASHWINFO);
    pf.hwnd = hHandle;
    pf.dwFlags = FLASHW_TIMER|FLASHW_TRAY; // (or FLASHW_ALL to flash and if it is not minimized)
    pf.uCount = std::stoi(cnt);
    pf.dwTimeout = std::stoi(rate);

    FlashWindowEx(&pf);
    return 1;
}


GMEXPORT int setFlashingNameDefault(const char* windowName)
{
    HWND hHandle = FindWindow(NULL,windowName); // Set handle to passed handle
    FLASHWINFO pf;                     // instanciate a struct of type flash window info
    pf.cbSize = sizeof(FLASHWINFO);
    pf.hwnd = hHandle;
    pf.dwFlags = FLASHW_TIMER|FLASHW_TRAY; // (or FLASHW_ALL to flash and if it is not minimized)
    pf.uCount = 8;
    pf.dwTimeout = 80;

    FlashWindowEx(&pf);
    return 1;
}



GMEXPORT int setFlashingNormal(const char* passedHandle)
{
    HWND hHandle = resolveHandle(passedHandle); // Set handle to passed handle
    FLASHWINFO pf;                     // instanciate a struct of type flash window info
    pf.cbSize = sizeof(FLASHWINFO);
    pf.hwnd = hHandle;
    pf.dwFlags = FLASHW_TIMER|FLASHW_TRAY; // (or FLASHW_ALL to flash and if it is not minimized)
    pf.uCount = 8;
    pf.dwTimeout = 2000;

    FlashWindowEx(&pf);
    return 1;
}



