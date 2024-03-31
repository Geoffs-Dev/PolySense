//#pragma once
#ifndef MAPPEDLIST_H
#define MAPPEDLIST_H
#include "framework.h"


class MappedList : public BaseWindow<MainWindow>
{
public:
    //void OnInit();
    void OnCreate(HWND hListView);
    void AppendList();

    MappedList() : m_hListView(NULL) {};

    //HANDLES
    HWND m_hListView = {};
};

#endif