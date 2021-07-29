


#include <Windows.h>
#include <stdio.h>
#include <string>

#define GMEXPORT extern "C" __declspec(dllexport)

GMEXPORT std::string GMgetWindowName() {
    TCHAR title[500];

    GetWindowText(GetForegroundWindow(), title, 500);

    std::string titlestr = title;
    return titlestr;
}
