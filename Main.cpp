#include "framework.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    //MainWindow mainWindow;
    MainWindow mainWindow(hInstance);

    if (!mainWindow.Create(L"PolySense", WS_OVERLAPPEDWINDOW))
    {
        return 0;
    }

    ShowWindow(mainWindow.Window(), nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_CREATE:
    {
        CreateMenus();

        /*Create the button to populate the list - to be changed to automate in a
         loop til stopped is clicked? This button can be used to close the window or do something*/
            m_hwndBtnStart = CreateWindow(
                L"BUTTON", // Predefined class; Unicode assumed
                L"Start", // Button text
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
                    // Size and position values are placeholders, button will be moved to an appropriate position in WM_SIZE
                0, // x position
                0, // y position
                50, // Button width
                50, // Button height
                m_hwnd, // Parent window
                NULL, // No menu.
                (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE),
                NULL); // Pointer not needed.  */

           
            m_hwndBtnStop = CreateWindow(
                L"BUTTON", // Predefined class; Unicode assumed
                L"Stop", // Button text
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles
                // Size and position values are placeholders, button will be moved to an appropriate position in WM_SIZE
                0, // x position
                0, // y position
                50, // Button width
                50, // Button height
                m_hwnd, // Parent window
                NULL, // No menu.
                (HINSTANCE)GetWindowLongPtr(m_hwnd, GWLP_HINSTANCE),
                NULL); // Pointer not needed.  */

        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        EndPaint(m_hwnd, &ps);

    }
    case WM_SIZE:
    {
        //Get the Client Area (The draw are of the main window m_hwnd)
        RECT rect;
        GetClientRect(m_hwnd, &rect);
        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;


        //Define the button size
        int btnwidthX = 50; //width
        int btnheightY = 50; //height
        int spacer = 10; //spacing

        int btnStartX = width - btnwidthX - spacer;
        int btnStartY = height - btnheightY - spacer;
        int btnStopX = btnStartX - btnwidthX - spacer;
        int btnStopY = btnStartY;
        
        // Move the button to the new position
        MoveWindow(m_hwndBtnStart, btnStopX, btnStopY, btnwidthX, btnheightY , TRUE);
        MoveWindow(m_hwndBtnStop, btnStartX, btnStartY, btnwidthX, btnheightY, TRUE);
    }
    return 0;

    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return TRUE;
}

void MainWindow::CreateMenus()
{
    hMenu = CreateMenu(); //the whole menu items
    HMENU hFileMenu = CreateMenu();
    HMENU hEditMenu = CreateMenu();
    HMENU hViewMenu = CreateMenu();
    HMENU hModulesMenu = CreateMenu();
    HMENU hRecorderMenu = CreateMenu();
    HMENU hToolsMenu = CreateMenu();
    HMENU hOptionsMenu = CreateMenu();
    HMENU hUserMenu = CreateMenu();
    HMENU hAbout = CreateMenu(); //popups


    //Add the menu items before applying the menu popup it-self
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, L"New...");
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_OPEN, L"Open...");
    AppendMenu(hFileMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_SAVE, L"Save");
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_SAVEAS, L"Save As...");
    AppendMenu(hFileMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, L"Exit");
    //Now you can Add the Actual File menu that the user first clicks in the App
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"File");

    //Fill hEditMenu with Strings
    AppendMenu(hEditMenu, MF_STRING, EDIT_MENU_COMMENT, L"Comments...");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hEditMenu, L"Edit");

    //Fill hViewMenu with Strings
    //AppendMenu(hViewMenu, MF_STRING, VIEW_MENU_TEMPERATURE, L"Temperature"); // To be moved into a dedecated menu popup
    AppendMenu(hViewMenu, MF_STRING, VIEW_MENU_TOOLBAR, L"Show Toolbar"); 
    AppendMenu(hViewMenu, MF_STRING, VIEW_MENU_TASKBAR, L"Show Taskbar");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hViewMenu, L"View");

    //Sensor Menu Popup
    AppendMenu(hModulesMenu, MF_STRING, MODULE_MENU_DHT11, L"DHT11...");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hModulesMenu, L"Modules");
                        
    AppendMenu(hRecorderMenu, MF_STRING, RECORDER_MENU_RECORD, L"Record"); //To record a timeline with sensor data
    AppendMenu(hRecorderMenu, MF_STRING, RECORDER_MENU_PLAY, L"Play");
    AppendMenu(hRecorderMenu, MF_STRING, RECORDER_MENU_STOP, L"Stop");
    AppendMenu(hRecorderMenu, MF_STRING, RECORDER_MENU_PAUSE, L"Pause");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hRecorderMenu, L"Recorder");


    AppendMenu(hToolsMenu, MF_STRING, TOOLS_MENU_OPTIONS, L"Options...");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hToolsMenu, L"Tools");


    AppendMenu(hUserMenu, MF_STRING, USERS_MENU_LOGIN, L"Log In...");
    AppendMenu(hUserMenu, MF_STRING, USERS_MENU_LOGOFF, L"Log Out");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hUserMenu, L"User");

    AppendMenu(hAbout, MF_STRING, ABOUT_MENU_ABOUT, L"About...");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hAbout, L"About");


    SetMenu(m_hwnd, hMenu);

}
void MainWindow::CreateToolBar()
{
    //TODO:: Create the tool bar buttons and apply images etc... 
}
;