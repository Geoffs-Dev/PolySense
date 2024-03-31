#include "MappedList.h"

void MappedList::OnCreate(HWND m_hListView)
{
    {
        // Create the ListView control
        INITCOMMONCONTROLSEX icex;
        icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icex.dwICC = ICC_LISTVIEW_CLASSES;
        InitCommonControlsEx(&icex);

        //Create the listview
        m_hListView = CreateWindow(
            WC_LISTVIEW,
            TEXT("Temprature Sensor"),
            WS_VISIBLE | WS_CHILD | LVS_REPORT | LVS_SINGLESEL,
            0,
            0,
            800, //Width
            300, //Height
            m_hwnd,
            NULL,
            NULL,
            NULL);
    };
}

void MappedList::AppendList()
{
    // Add columns to the ListView control
    LVCOLUMN lvColumn;
    lvColumn.mask = LVCF_TEXT | LVCF_WIDTH;
    lvColumn.cx = 150;
    lvColumn.pszText = (LPWSTR)TEXT("Temperature");
    ListView_InsertColumn(m_hListView, 0, &lvColumn);
    lvColumn.cx = 150;
    lvColumn.pszText = (LPWSTR)TEXT("Humidity");
    ListView_InsertColumn(m_hListView, 1, &lvColumn);
    lvColumn.cx = 150;
    lvColumn.pszText = (LPWSTR)TEXT("Date");
    ListView_InsertColumn(m_hListView, 2, &lvColumn);
    lvColumn.cx = 150;
    lvColumn.pszText = (LPWSTR)TEXT("Time");
    ListView_InsertColumn(m_hListView, 3, &lvColumn);
}
