//#pragma once
#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// Windows Header Files
#include <windows.h>

//com control for comunicating with hardware (developer board Arduino)
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib") //Essensial to go with the #include <commctrl.h> but 
//i don't know why it insists as this is part of the project to communicate with COM (USB) port???
//My Headers
#include "MenuIDs.h"
#include "BaseWindow.h"
#include "MappedList.h"

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#endif