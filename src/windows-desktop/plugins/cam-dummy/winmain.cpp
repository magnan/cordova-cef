// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.

#include "Capture.h"
#include "resource.h"

#include "Camera.h"

#include <shlobj.h>
#include <Shlwapi.h>
#include <powrprof.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

// Include the v6 common controls in the manifest
#pragma comment(linker, \
    "\"/manifestdependency:type='Win32' "\
    "name='Microsoft.Windows.Common-Controls' "\
    "version='6.0.0.0' "\
    "processorArchitecture='*' "\
    "publicKeyToken='6595b64144ccf1df' "\
    "language='*'\"")

bool cameraInited = false;
bool cameraRecord = true;

int cameraCode;
wchar_t* cameraFilename;

struct Zone
{
	int left;
	int top;
	Rect rect;
	WCHAR* default;
	WCHAR* selected;
	bool isSelected;
};

Zone closeZone;
Zone videoZone;
Zone stillZone;
Zone recordZone;

// Implements the window procedure for the main application window.

namespace MainWindow
{
    HWND hPreview = NULL;
    bool bRecording = false;
    bool bPreviewing = false;
     
    wchar_t VideoFileName[MAX_PATH];
    wchar_t PhotoFileName[MAX_PATH];

    BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
    void OnPaint(HWND hwnd);
    void OnSize(HWND hwnd, UINT state, int cx, int cy);
    void OnDestroy(HWND hwnd);
    void OnChooseDevice(HWND hwnd);
    void OnStartRecord(HWND hwnd);
    void OnStopRecord(HWND hwnd);

    void UpdateUI(HWND hwnd)
    {
    }

    BOOL OnCreate(HWND hwnd, LPCREATESTRUCT /*lpCreateStruct*/)
    {
        hPreview = CreatePreviewWindow(GetModuleHandle(NULL), hwnd);
        return FALSE;
    }

	void PaintZone(Graphics* grpx, Zone* zone)
	{
	    Image* image = new Image((zone->isSelected) ? zone->selected : zone->default);
	    grpx->DrawImage(image,zone->rect);
	}

    void OnPaint(HWND hwnd)
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
		
		HBRUSH hBrush;
		hBrush = CreateSolidBrush(RGB(0,0,200));
        FillRect(hdc, &ps.rcPaint, hBrush);
		
	    Graphics grpx(hdc);

		// Background
		RECT windowrect;
		GetClientRect(hwnd, &windowrect);
		Rect rect;
		rect.X = windowrect.left;
		rect.Y = windowrect.bottom - 252;
		rect.Width = windowrect.right - windowrect.left;
		rect.Height = 252;
	    Image* image = new Image(L"C:\\images\\ath-tool-bg.png");
	    grpx.DrawImage(image,rect);

		if (cameraRecord)
		{
			PaintZone(&grpx, &closeZone);
			PaintZone(&grpx, &videoZone);
			PaintZone(&grpx, &stillZone);
			PaintZone(&grpx, &recordZone);
		}

        EndPaint(hwnd, &ps);
    }

	void sizeZone(Zone* zone, RECT* windowrect)
	{
		zone->rect.X = (windowrect->right - windowrect->left) / 2 + zone->left;
		zone->rect.Y = windowrect->bottom - 40 + zone->top;
		zone->rect.Width = 30;
		zone->rect.Height = 30;
	}

    void OnSize(HWND hwnd, UINT state, int cx, int cy)
    {        
        if (state == SIZE_RESTORED || state == SIZE_MAXIMIZED)
        {
			RECT windowrect;
			GetClientRect(hwnd, &windowrect);
			
			sizeZone(&closeZone, &windowrect);
			sizeZone(&videoZone, &windowrect);
			sizeZone(&stillZone, &windowrect);
			sizeZone(&recordZone, &windowrect);
            
			cy -= 50;
            MoveWindow(hPreview, 0, 0, cx, cy, TRUE);

			InvalidateRect(hwnd, NULL, 0);
        }        
    }

    void OnDestroy(HWND hwnd)
    {
        PostQuitMessage(0);
    }


    void OnStartRecord(HWND hwnd)
    {
    }

    void OnStopRecord(HWND hwnd)
    {
    }

    void OnStopPreview(HWND hwnd)
    {
    }

    void OnStartPreview (HWND hwnd)
    {
    }

    void OnTakePhoto(HWND hwnd)
    {
    }

	BOOL inZone(Zone* zone, int x, int y)
	{
		return zone->rect.Contains(x, y);
	}

	void captureClose(HWND hwnd)
	{
		if (recordZone.isSelected)
		{
			OnStopRecord(hwnd);
			recordZone.isSelected = false;
			InvalidateRect(hwnd, NULL, 0);
			cameraCode = 0;
			cameraFilename = VideoFileName;
			PostQuitMessage(0);
		}
		else
		{
			cameraCode = 0;
			cameraFilename = L"";
			PostQuitMessage(0);
		}
	}

	void captureVideo(HWND hwnd)
	{
		videoZone.isSelected = true;
		stillZone.isSelected = false;
		InvalidateRect(hwnd, NULL, 0);
	}


	void captureStill(HWND hwnd)
	{
		videoZone.isSelected = false;
		stillZone.isSelected = true;
		InvalidateRect(hwnd, NULL, 0);
	}


	void recordAction(HWND hwnd)
	{
		if (videoZone.isSelected)
		{
			if (!recordZone.isSelected)
			{
				OnStopRecord(hwnd);
				recordZone.isSelected = false;
				InvalidateRect(hwnd, NULL, 0);
				cameraCode = 1;
				cameraFilename = VideoFileName;
				PostQuitMessage(0);
			}
			else
			{
				recordZone.isSelected = true;
				InvalidateRect(hwnd, NULL, 0);
				OnStartRecord(hwnd);
			}
		}
		else
		{
			recordZone.isSelected = true;
			InvalidateRect(hwnd, NULL, 0);
			RedrawWindow(hwnd, NULL, NULL, RDW_ERASENOW | RDW_UPDATENOW);
			OnTakePhoto(hwnd);
			recordZone.isSelected = false;
			InvalidateRect(hwnd, NULL, 0);
			RedrawWindow(hwnd, NULL, NULL, 0);
			cameraCode = 2;
			cameraFilename = PhotoFileName;
			PostQuitMessage(0);
		}
	}


    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        HANDLE_MSG(hwnd, WM_PAINT,   OnPaint);
        HANDLE_MSG(hwnd, WM_SIZE,    OnSize);
        HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);

		case WM_CREATE:
			{
				OnCreate(hwnd, (LPCREATESTRUCT) lParam);
			}
			return 0;

        case WM_ERASEBKGND:
            return 1;

		case WM_MOUSEMOVE:
			{
				SetCursor(LoadCursor(NULL, IDC_ARROW));
			}
			return 0;

		case WM_LBUTTONDOWN:
			{
				int x = GET_X_LPARAM(lParam);
				int y = GET_Y_LPARAM(lParam);

				if (cameraRecord)
				{
					if (inZone(&closeZone, x, y))
						captureClose(hwnd);
					else if (inZone(&videoZone, x, y))
						captureVideo(hwnd);
					else if (inZone(&stillZone, x, y))
						captureStill(hwnd);
					else if (inZone(&recordZone, x, y))
						recordAction(hwnd);
				}
				else
				{
				}
			}
			return 0;

		case WM_CLOSE:
			return 0;
		}

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
};

HWND CreateMainWindow(HINSTANCE hInstance)
{
    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Capture Engine Window Class";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc   = MainWindow::WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU1);

    RegisterClass(&wc);

    // Create the window.
    return CreateWindowEx(0, CLASS_NAME, L"Capture Application",
        WS_OVERLAPPEDWINDOW & ~(WS_SYSMENU), CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL);
};

void MakeWindowFullscreen(HWND hwnd)
{
    SetWindowLong(hwnd, GWL_STYLE, 
                  GetWindowLong(hwnd, GWL_STYLE) & ~(WS_CAPTION | WS_THICKFRAME));
    SetWindowLong(hwnd, GWL_EXSTYLE, 
                  GetWindowLong(hwnd, GWL_EXSTYLE) & ~(WS_EX_DLGMODALFRAME | 
                  WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE));

    MONITORINFO monitor_info;
    monitor_info.cbSize = sizeof(monitor_info);
    GetMonitorInfo(MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST),
                                     &monitor_info);
    SetWindowPos(hwnd, NULL, 
                 monitor_info.rcMonitor.left, 
                 monitor_info.rcMonitor.top,
                 monitor_info.rcMonitor.right - monitor_info.rcMonitor.left,
                 monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top,
                 SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
}

void SetupZones(bool firstTime)
{
	closeZone.left = -270;
	closeZone.top = -4;
	closeZone.default = L"C:\\images\\ath-tool-reject.png";
	closeZone.selected = L"C:\\images\\ath-tool-reject_selected.png";
	closeZone.isSelected = false;

	videoZone.left = -100;
	videoZone.top = 0;
	videoZone.default = L"C:\\images\\ath-tool-video.png";
	videoZone.selected = L"C:\\images\\ath-tool-video_selected.png";
	if (firstTime)
		videoZone.isSelected = true;

	stillZone.left = -60;
	stillZone.top = 0;
	stillZone.default = L"C:\\images\\ath-tool-still.png";
	stillZone.selected = L"C:\\images\\ath-tool-still_selected.png";
	if (firstTime)
		stillZone.isSelected = false;
	
	recordZone.left = 100;
	recordZone.top = 0;
	recordZone.default = L"C:\\images\\ath-tool-record.png";
	recordZone.selected = L"C:\\images\\ath-tool-record_selected.png";
	recordZone.isSelected = false;
}

bool cameraFullScreen = false;

DWORD WINAPI CreateWindowThreaded( LPVOID lpParam ) 
{
	HWND hwnd = CreateMainWindow(NULL);

	if (cameraFullScreen)
		MakeWindowFullscreen(hwnd);
	
	MainWindow::OnStartPreview(hwnd);

    ShowWindow(hwnd, SW_RESTORE);

    // Run the message loop.
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

	return 0;
}

void CameraInit()
{
	GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;

    // Initialize the common controls
    const INITCOMMONCONTROLSEX icex = { sizeof(INITCOMMONCONTROLSEX), ICC_WIN95_CLASSES };
    InitCommonControlsEx(&icex); 

    // Note: The shell common File dialog requires apartment threading.
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	// start up GDI+ -- only need to do this once per process at startup
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

__declspec(dllexport) void __cdecl CameraCapture(bool startfullscreen, CameraDoneCallback callback)
{
	bool firstTime = ! cameraInited;

	if (! cameraInited)
	{
		CameraInit();
		cameraInited = true;
	}

	SetupZones(firstTime);
	
	cameraCode = 0;
	cameraFilename = L"";

	cameraFullScreen = startfullscreen;

    HANDLE thread = CreateThread(NULL, 0, CreateWindowThreaded, NULL, 0, 0);
	WaitForSingleObject(thread,INFINITE);
	
	callback(cameraCode, cameraFilename);
}
