#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <shobjidl.h>

HWND CreateTabControl(HWND hwndParent, HINSTANCE hInstance, int numTab, TCHAR** TabLabel);//TCHAR** means *TCHAR Label[]= {L"", L"", L""}
HWND CreateTabDisplayWindow(HWND hwndTab, HINSTANCE hInstance);
BOOL OnNotify(HWND hwndTab, HWND *hwndDisplay, LPARAM lParam, HINSTANCE hInstance);
HRESULT OnSize(HWND hwndTab, LPARAM lParam);
void DialogResize(HWND Rect, HWND hDlg);

