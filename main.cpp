
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <vector>
#define GMEXPORT extern "C" __declspec(dllexport)

/*
TODO: Change return types from int to double.
Check window flashing functions. Check.
Check Icon function.
*/



HWND resolveHandle(const char* _passedHandle)
{
    std::string hstr(_passedHandle);
    HWND parentHwnd = (HWND)std::stoull(hstr);

    return parentHwnd;
}

//char* returnValPtr = &returnVal[0]; // Convert from string to char*

GMEXPORT double initTest(double Parameter) // Geht / testfunktion
{
    return Parameter*2;
}

GMEXPORT double checkWindowName(const char* windowName, double returnValue) // geht / returns 1 yes 0 no
{
    // Checks if a window with a certain title exists
    returnValue = 0;
    // get handle to the searched window name
    HWND winHandle = FindWindow(NULL,windowName);
    // check if handle is null...
    if(winHandle == NULL)
    {
        returnValue = 0;
        return returnValue;
    }
    returnValue = 1;
    return returnValue;
}

GMEXPORT char* getWindowNameC()  // Geht sicher / Returns string
{
    // Shows the title of the currently focused window
    char title[500]; // get the
    GetWindowText(GetForegroundWindow(), title, 500);
    // typecast to char
    char* titleptr = title;
    return titleptr;
}

GMEXPORT double showMessageboxOk(const char* passedHandle, const char* headline, const char* bodytext)
{   // Not sure about return.. Wahrschreinlich random bullshit
    // Takes game maker window handle, headline, body text
    // returns whatever the msgbox id is.
    int msgboxID = MessageBox(
        resolveHandle(passedHandle),
        bodytext,
        headline,
        MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON2
    );

    return (double)msgboxID;
}


GMEXPORT int showMessageboxTest(const char* passedHandle) // Geht / Testfunktion
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

GMEXPORT double showMessageboxCTC(const char* passedHandle, const char* headline, const char* bodytext, double returnVal) // Geht / Janky
{   // Operational / tut was sie soll wenn man glueck hat
    // this will show a messagebox with a continue, try again and cancel button.
    returnVal = 0; // Normalized button output value 0-2
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


GMEXPORT double showMessageboxYN(const char* passedHandle, const char* headline, const char* bodytext, double returnVal)// geht
{   // shows a messagebox with yes and no button, returns 0 for no and 1 for yes
    returnVal = 0;
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

GMEXPORT double setWindowIcon( const char* icopath) // Geht.
{   // sets an icon to the game window. Returns 1 if success and <0 if not
    // Reference: http://www.cplusplus.com/forum/windows/188709/
    HWND handle = GetActiveWindow();
    double returnVal = 0;
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
        return returnVal;
        // Stricon is empty. return.
    }
    else
    {
        hWindowIcon =(HICON)LoadImage(NULL, stricon.c_str(), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
        hWindowIconBig =(HICON)LoadImage(NULL, stricon.c_str(), IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
        SendMessage( HWND(handle), WM_SETICON, ICON_SMALL, (LPARAM)hWindowIcon );
        SendMessage( HWND(handle), WM_SETICON, ICON_BIG, (LPARAM)hWindowIconBig );
    }
    return returnVal;
}

GMEXPORT double shellExec(const char* passedHandle, const char* lpOperation, const char* lpFile) //???
{
    double returnVal = 1;
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
    return returnVal;
}


GMEXPORT double shellExecEx(const char* Verb, const char* File, const char* Showtype) // geht sicher, Showtype ist typecast zu int.
{
    // Takes the Showtype as string : https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow
    double returnVal = 1;
    ShellExecute(
                 NULL,
                 Verb, // For example "open"
                 File, // "C:\\Windows\\system32\\mspaint.exe"
                 NULL,
                 NULL,
                 std::stoi(Showtype)
                 );
    return returnVal;
}

GMEXPORT double setFlashingSelf(double flashCount, double flashRateMillis) // geht
{   // Sets own window to flashing
    HWND hHandle = GetActiveWindow(); // Set handle to passed handle
    FLASHWINFO pf;                     // instanciate a struct of type flash window info
    pf.cbSize = sizeof(FLASHWINFO);
    pf.hwnd = hHandle;
    pf.dwFlags = FLASHW_TIMER|FLASHW_TRAY; // (or FLASHW_ALL to flash and if it is not minimized)
    pf.uCount = (UINT)flashCount;
    pf.dwTimeout = (DWORD)flashRateMillis;

    FlashWindowEx(&pf);
    return flashCount;
}

GMEXPORT double setFlashingName(const char* windowName, double flashCount, double flashRateMillis) // Geht
{   // Takes window name and flashes it.
    HWND hHandle = FindWindow(NULL,windowName); // Set handle to passed handle
    FLASHWINFO pf;                     // instanciate a struct of type flash window info
    pf.cbSize = sizeof(FLASHWINFO);
    pf.hwnd = hHandle;
    pf.dwFlags = FLASHW_TIMER|FLASHW_TRAY; // (or FLASHW_ALL to flash and if it is not minimized)
    pf.uCount = (UINT)flashCount;
    pf.dwTimeout = (DWORD)flashRateMillis;

    FlashWindowEx(&pf);
    return flashCount;
}


