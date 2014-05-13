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

CaptureManager *g_pEngine = NULL;
HPOWERNOTIFY    g_hPowerNotify = NULL;
HPOWERNOTIFY    g_hPowerNotifyMonitor = NULL;
SYSTEM_POWER_CAPABILITIES   g_pwrCaps;
bool            g_fSleepState = false;

wchar_t appdir[MAX_PATH];

bool cameraInited = false;
bool cameraRecord = true;

int cameraCode;
wchar_t* cameraFilename;

bool cameraFullScreen = false;
int cameraButtonSize = 60;
int cameraButtonHalf = 30;

Devices devices;
IMFActivate* selectedDevice = NULL;
int selectedDeviceRank = 0;

struct Zone
{
	int center;
	int top;
	Rect rect;
	WCHAR* default;
	WCHAR* selected;
	bool isSelected;
};

Zone closeZone;
Zone deviceZone;
Zone videoZone;
Zone stillZone;
Zone recordZone;

void SetupApp()
{
	GetModuleFileNameW(NULL, appdir, MAX_PATH);
	PathRemoveFileSpec(appdir);
}

void InitDevices()
{
    IMFAttributes *pAttributes = NULL;

    HRESULT hr = MFCreateAttributes(&pAttributes, 1);
    if (FAILED(hr))
    {
        goto done;
    }

    // Ask for source type = video capture devices
    hr = pAttributes->SetGUID(MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE, MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID);
    if (FAILED(hr))
    {
        goto done;
    }

    // Enumerate devices.
    hr = MFEnumDeviceSources(pAttributes, &devices.ppDevices, &devices.count);
    if (FAILED(hr))
    {
        goto done;
    }

done:
    SafeRelease(&pAttributes);
    if (FAILED(hr))
    {
        ShowError(NULL, IDS_ERR_SET_DEVICE, hr);
    }
}

HRESULT SelectDevice(HWND hPreview, int rank)
{
	HRESULT hr = g_pEngine->InitializeCaptureManager(hPreview, devices.ppDevices[rank]);
    if (! FAILED(hr))
	{
		SafeRelease(&selectedDevice);
		selectedDevice = devices.ppDevices[rank];
		selectedDevice->AddRef();
		selectedDeviceRank = rank;
	}
    return hr;
}

wchar_t* AppFile(wchar_t* file, wchar_t* filename)
{
	PathCombine(file, appdir, filename);
	return file;
}

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
        if (g_pEngine->IsRecording() != bRecording)
        {
            bRecording = g_pEngine->IsRecording();
        }

        if (g_pEngine->IsPreviewing() != bPreviewing)
        {
            bPreviewing = g_pEngine->IsPreviewing();
        }

        BOOL bEnableRecording = TRUE;
        BOOL bEnablePhoto = TRUE;

        if (bRecording)
        {
        }
        else if (g_pEngine->IsPreviewing())
        {
        }
        else
        {
            bEnableRecording = FALSE;
        }

        if (!g_pEngine->IsPreviewing() || g_pEngine->IsPhotoPending())
        {
            bEnablePhoto = FALSE;
        }
    }


    BOOL OnCreate(HWND hwnd, LPCREATESTRUCT /*lpCreateStruct*/)
    {
        BOOL                fSuccess = FALSE;
        IMFAttributes*      pAttributes = NULL;
        HRESULT             hr = S_OK;

        hPreview = CreatePreviewWindow(GetModuleHandle(NULL), hwnd);
        if (hPreview == NULL)
        {
            goto done;
        }

        if (FAILED(CaptureManager::CreateInstance(hwnd, &g_pEngine)))
        {
            goto done;
        }
    
        hr = SelectDevice(hPreview, selectedDeviceRank);
        if (FAILED(hr))
        {
            ShowError(hwnd, IDS_ERR_SET_DEVICE, hr);
            goto done;
        }

        // Register for connected standy changes.  This should come through the normal
        // WM_POWERBROADCAST messages that we're already handling below.
        // We also want to hook into the monitor on/off notification for AOAC (SOC) systems.
        g_hPowerNotify = RegisterSuspendResumeNotification((HANDLE)hwnd, DEVICE_NOTIFY_WINDOW_HANDLE);
        g_hPowerNotifyMonitor = RegisterPowerSettingNotification((HANDLE)hwnd, &GUID_MONITOR_POWER_ON, DEVICE_NOTIFY_WINDOW_HANDLE);
        ZeroMemory(&g_pwrCaps, sizeof(g_pwrCaps));
        GetPwrCapabilities(&g_pwrCaps);

        UpdateUI(hwnd);
        fSuccess = TRUE;

    done:
        SafeRelease(&pAttributes);
        return fSuccess;
    }

	void PaintZone(Graphics* grpx, Zone* zone)
	{
		wchar_t file[MAX_PATH];
	    Image* image = new Image(AppFile(file, (zone->isSelected) ? zone->selected : zone->default));
	    grpx->DrawImage(image,zone->rect);
	}

    void OnPaint(HWND hwnd)
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
		
		HBRUSH hBrush;
		hBrush = CreateSolidBrush(RGB(0,0,0));
        FillRect(hdc, &ps.rcPaint, hBrush);
		
	    Graphics grpx(hdc);

		// Background
		wchar_t file[MAX_PATH];
		RECT windowrect;
		GetClientRect(hwnd, &windowrect);
		Rect rect;
		rect.X = windowrect.left;
		rect.Y = windowrect.bottom - 252;
		rect.Width = windowrect.right - windowrect.left;
		rect.Height = 252;
	    Image* image = new Image(AppFile(file, L"images\\ath-tool-bg.png"));
	    grpx.DrawImage(image,rect);

		if (cameraRecord)
		{
			PaintZone(&grpx, &closeZone);
			PaintZone(&grpx, &deviceZone);
			PaintZone(&grpx, &videoZone);
			PaintZone(&grpx, &stillZone);
			PaintZone(&grpx, &recordZone);
		}
		else
		{
		}

        EndPaint(hwnd, &ps);
    }

	void sizeZone(Zone* zone, RECT* windowrect)
	{
		zone->rect.X = (windowrect->right - windowrect->left) / 2 + zone->center - cameraButtonHalf;
		zone->rect.Y = windowrect->bottom - cameraButtonSize - 10 + zone->top;
		zone->rect.Width = cameraButtonSize;
		zone->rect.Height = cameraButtonSize;
	}

    void OnSize(HWND hwnd, UINT state, int cx, int cy)
    {        
        if (state == SIZE_RESTORED || state == SIZE_MAXIMIZED)
        {
			RECT windowrect;
			GetClientRect(hwnd, &windowrect);
			
			sizeZone(&closeZone, &windowrect);
			sizeZone(&deviceZone, &windowrect);
			sizeZone(&videoZone, &windowrect);
			sizeZone(&stillZone, &windowrect);
			sizeZone(&recordZone, &windowrect);
            
			cy -= (cameraButtonSize + 20);
            MoveWindow(hPreview, 0, 0, cx, cy, TRUE);

			InvalidateRect(hwnd, NULL, 0);
        }        
    }

    void OnDestroy(HWND hwnd)
    {
        delete g_pEngine;
        g_pEngine = NULL;
        if (g_hPowerNotify)
        {
            UnregisterSuspendResumeNotification (g_hPowerNotify);
            g_hPowerNotify = NULL;
        }
        PostQuitMessage(0);
    }


    void OnStartRecord(HWND hwnd)
    {
		
        wchar_t filename[MAX_PATH];

        // Get the path to the Documents folder.
        IShellItem *psi = NULL;
        PWSTR pszFolderPath = NULL;

        HRESULT hr = SHCreateItemInKnownFolder(FOLDERID_Documents, 0, NULL, IID_PPV_ARGS(&psi));
        if (FAILED(hr))
        {
            goto done;
        }

        hr = psi->GetDisplayName(SIGDN_FILESYSPATH, &pszFolderPath);
        if (FAILED(hr))
        {
            goto done;
        }

        // Construct a file name based on the current time.

        SYSTEMTIME time;
        GetLocalTime(&time);

        hr = StringCchPrintf(filename, MAX_PATH, L"MyVideo%04u_%02u%02u_%02u%02u%02u.mp4",
            time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
        if (FAILED(hr))
        {
            goto done;
        }

        LPTSTR path = PathCombine(VideoFileName, pszFolderPath, filename);
        if (path == NULL)
        {
            hr = E_FAIL;
            goto done;
        }

        hr = g_pEngine->StartRecord(VideoFileName);
        if (FAILED(hr))
        {
            goto done;
        }

done:
        if (FAILED(hr))
        {
            ShowError(hwnd, IDS_ERR_RECORD, hr);
        }
        UpdateUI(hwnd);
    }

    void OnStopRecord(HWND hwnd)
    {
        HRESULT hr = g_pEngine->StopRecord();
        if (FAILED(hr))
        {
            ShowError(hwnd, IDS_ERR_RECORD, hr);
        }
        UpdateUI(hwnd);
    }

    void OnTakePhoto(HWND hwnd)
    {
        wchar_t filename[MAX_PATH];

        // Get the path to the Documents folder.
        IShellItem *psi = NULL;
        PWSTR pszFolderPath = NULL;

        HRESULT hr = SHCreateItemInKnownFolder(FOLDERID_Documents, 0, NULL, IID_PPV_ARGS(&psi));
        if (FAILED(hr))
        {
            goto done;
        }

        hr = psi->GetDisplayName(SIGDN_FILESYSPATH, &pszFolderPath);
        if (FAILED(hr))
        {
            goto done;
        }

        // Construct a file name based on the current time.

        SYSTEMTIME time;
        GetLocalTime(&time);

        hr = StringCchPrintf(filename, MAX_PATH, L"MyPhoto%04u_%02u%02u_%02u%02u%02u.jpg",
            time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
        if (FAILED(hr))
        {
            goto done;
        }

        LPTSTR path = PathCombine(PhotoFileName, pszFolderPath, filename);
        if (path == NULL)
        {
            hr = E_FAIL;
            goto done;
        }

        hr = g_pEngine->TakePhoto(path);
        if (FAILED(hr))
        {
            goto done;
        }

done:
        SafeRelease(&psi);
        CoTaskMemFree(pszFolderPath);

        if (FAILED(hr))
        {
            ShowError(hwnd, IDS_ERR_PHOTO, hr);
        }
        UpdateUI(hwnd);
    }

	BOOL inZone(Zone* zone, int x, int y)
	{
		return zone->rect.Contains(x, y);
	}

	void ButtonClick()
	{
		wchar_t file[MAX_PATH];
		PlaySound(AppFile(file, L"sounds\\button.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}


	void captureClose(HWND hwnd)
	{
		if (g_pEngine->IsRecording())
		{
			ButtonClick();
			OnStopRecord(hwnd);
			recordZone.isSelected = false;
			InvalidateRect(hwnd, NULL, 0);
			cameraCode = 0;
			cameraFilename = VideoFileName;
			PostQuitMessage(0);
		}
		else
		{
			ButtonClick();
			cameraCode = 0;
			cameraFilename = L"";
			PostQuitMessage(0);
		}
	}


	void captureDevice(HWND hwnd)
	{
		ButtonClick();
		g_pEngine->StopPreview();
		SelectDevice(hPreview, (selectedDeviceRank + 1) % devices.count);
	}


	void captureVideo(HWND hwnd)
	{
		if (!g_pEngine->IsRecording())
		{
			ButtonClick();
			videoZone.isSelected = true;
			stillZone.isSelected = false;
			InvalidateRect(hwnd, NULL, 0);
		}
	}


	void captureStill(HWND hwnd)
	{
		if (!g_pEngine->IsRecording())
		{
			ButtonClick();
			videoZone.isSelected = false;
			stillZone.isSelected = true;
			InvalidateRect(hwnd, NULL, 0);
		}
	}


	void recordAction(HWND hwnd)
	{
		if (g_pEngine->IsPreviewing())
		{
			if (videoZone.isSelected)
			{
				if (g_pEngine->IsRecording())
				{
					ButtonClick();
					OnStopRecord(hwnd);
					recordZone.isSelected = false;
					InvalidateRect(hwnd, NULL, 0);
					RedrawWindow(hwnd, NULL, NULL, 0);
					cameraCode = 1;
					cameraFilename = VideoFileName;
					Sleep(500);
					PostQuitMessage(0);
				}
				else
				{
					ButtonClick();
					recordZone.isSelected = true;
					InvalidateRect(hwnd, NULL, 0);
					OnStartRecord(hwnd);
				}
			}
			else
			{
				ButtonClick();
				recordZone.isSelected = true;
				InvalidateRect(hwnd, NULL, 0);
				RedrawWindow(hwnd, NULL, NULL, RDW_ERASENOW | RDW_UPDATENOW);
				OnTakePhoto(hwnd);
				recordZone.isSelected = false;
				InvalidateRect(hwnd, NULL, 0);
				RedrawWindow(hwnd, NULL, NULL, 0);
				cameraCode = 2;
				cameraFilename = PhotoFileName;
				Sleep(500);
				PostQuitMessage(0);
			}
		}
	}


    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        HANDLE_MSG(hwnd, WM_CREATE,  OnCreate);
        HANDLE_MSG(hwnd, WM_PAINT,   OnPaint);
        HANDLE_MSG(hwnd, WM_SIZE,    OnSize);
        HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);

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
					else if (inZone(&deviceZone, x, y))
						captureDevice(hwnd);
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

        case WM_APP_CAPTURE_EVENT:
            {
                if (g_pEngine)
                {
					GUID guidType;
					IMFMediaEvent *pEvent = reinterpret_cast<IMFMediaEvent*>(wParam);
					pEvent->GetExtendedType(&guidType);
					/*
					// For debugging events
					if (guidType == MF_CAPTURE_ENGINE_INITIALIZED) ShowDebug(L"INITIALIZED");
					else if (guidType == MF_CAPTURE_ENGINE_PREVIEW_STARTED) ShowDebug(L"PREVIEW_STARTED");
					else if (guidType == MF_CAPTURE_ENGINE_PREVIEW_STOPPED) ShowDebug(L"PREVIEW_STOPPED");
					else if (guidType == MF_CAPTURE_ENGINE_RECORD_STARTED) ShowDebug(L"RECORD_STARTED");
					else if (guidType == MF_CAPTURE_ENGINE_RECORD_STOPPED) ShowDebug(L"RECORD_STOPPED");
					else if (guidType == MF_CAPTURE_ENGINE_PHOTO_TAKEN) ShowDebug(L"PHOTO_TAKEN");
					else if (guidType == MF_CAPTURE_ENGINE_ERROR) ShowDebug(L"ERROR");
					*/
                    HRESULT hr = g_pEngine->OnCaptureEvent(wParam, lParam);
                    if (FAILED(hr))
                    {
                        ShowError(hwnd, g_pEngine->ErrorID(), hr);
                        InvalidateRect(hwnd, NULL, FALSE);
                    }

					if (guidType == MF_CAPTURE_ENGINE_INITIALIZED)
					{
						g_pEngine->StartPreview();
					}
                }

                UpdateUI(hwnd);
            }
            return 0;
        case WM_POWERBROADCAST:
            {
                switch (wParam)
                {
                case PBT_APMSUSPEND:
                    DbgPrint(L"++WM_POWERBROADCAST++ Stopping both preview & record stream.\n");
                    g_fSleepState = true;
                    g_pEngine->SleepState(g_fSleepState);
                    g_pEngine->StopRecord();
                    g_pEngine->StopPreview();
                    g_pEngine->DestroyCaptureEngine();
                    DbgPrint(L"++WM_POWERBROADCAST++ streams stopped, capture engine destroyed.\n");
                    break;
                case PBT_APMRESUMEAUTOMATIC:
                    DbgPrint(L"++WM_POWERBROADCAST++ Reinitializing capture engine.\n");
                    g_fSleepState = false;
                    g_pEngine->SleepState(g_fSleepState);
                    g_pEngine->InitializeCaptureManager(hPreview, selectedDevice);
                    break;
                case PBT_POWERSETTINGCHANGE:
                    {
                        // We should only be in here for GUID_MONITOR_POWER_ON.
                        POWERBROADCAST_SETTING* pSettings = (POWERBROADCAST_SETTING*)lParam;

                        // If this is a SOC system (AoAc is true), we want to check our current
                        // sleep state and based on whether the monitor is being turned on/off,
                        // we can turn off our media streams and/or re-initialize the capture
                        // engine.
                        if (pSettings != NULL && g_pwrCaps.AoAc && pSettings->PowerSetting == GUID_MONITOR_POWER_ON)
                        {
                            DWORD   dwData = *((DWORD*)pSettings->Data);
                            if (dwData == 0 && !g_fSleepState)
                            {
                                // This is a AOAC machine, and we're about to turn off our monitor, let's stop recording/preview.
                                DbgPrint(L"++WM_POWERBROADCAST++ Stopping both preview & record stream.\n");
                                g_fSleepState = true;
                                g_pEngine->SleepState(g_fSleepState);
                                g_pEngine->StopRecord();
                                g_pEngine->StopPreview();
                                g_pEngine->DestroyCaptureEngine();
                                DbgPrint(L"++WM_POWERBROADCAST++ streams stopped, capture engine destroyed.\n");
                            }
                            else if (dwData != 0 && g_fSleepState)
                            {
                                DbgPrint(L"++WM_POWERBROADCAST++ Reinitializing capture engine.\n");
                                g_fSleepState = false;
                                g_pEngine->SleepState(g_fSleepState);
                                g_pEngine->InitializeCaptureManager(hPreview, selectedDevice);
                            }
                        }
                    }
                    break;
                case PBT_APMRESUMESUSPEND:
                default:
                    // Don't care about this one, we always get the resume automatic so just
                    // latch onto that one.
                    DbgPrint(L"++WM_POWERBROADCAST++ (wParam=%u,lParam=%u)\n", wParam, lParam);
                    break;
                }
            }
            return 1;
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

int Adjust(int center)
{
	return center * cameraButtonSize / 30;
}

void SetupZones(bool firstTime)
{
	closeZone.center = Adjust(-240);
	closeZone.top = -4;
	closeZone.default = L"images\\ath-tool-reject.png";
	closeZone.selected = L"images\\ath-tool-reject_selected.png";
	closeZone.isSelected = false;

	deviceZone.center = Adjust(-120);
	deviceZone.top = 0;
	deviceZone.default = L"images\\ath-tool-capture.png";
	deviceZone.selected = L"images\\ath-tool-capture_selected.png";
	deviceZone.isSelected = false;

	videoZone.center = Adjust(-20);
	videoZone.top = 0;
	videoZone.default = L"images\\ath-tool-video.png";
	videoZone.selected = L"images\\ath-tool-video_selected.png";
	if (firstTime)
		videoZone.isSelected = true;

	stillZone.center = Adjust(20);
	stillZone.top = 0;
	stillZone.default = L"images\\ath-tool-still.png";
	stillZone.selected = L"images\\ath-tool-still_selected.png";
	if (firstTime)
		stillZone.isSelected = false;
	
	recordZone.center = Adjust(120);
	recordZone.top = 0;
	recordZone.default = L"images\\ath-tool-record.png";
	recordZone.selected = L"images\\ath-tool-record_selected.png";
	recordZone.isSelected = false;
}

DWORD WINAPI CreateWindowThreaded( LPVOID lpParam ) 
{
	HWND hwnd = CreateMainWindow(NULL);

	if (cameraFullScreen)
		MakeWindowFullscreen(hwnd);

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
	bool bCoInit = false, bMFStartup = false;

	SetupApp();

	GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;

    // Initialize the common controls
    const INITCOMMONCONTROLSEX icex = { sizeof(INITCOMMONCONTROLSEX), ICC_WIN95_CLASSES };
    InitCommonControlsEx(&icex); 

    // Note: The shell common File dialog requires apartment threading.
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (FAILED(hr))
    {
        goto done;
    }
    bCoInit = true;

	// start up GDI+ -- only need to do this once per process at startup
    Status ret = GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    if (ret != Ok)
    {
        goto done;
    }

	// shut down - only once per process
    // GdiplusShutdown(gdiplusToken);

    hr = MFStartup(MF_VERSION);
    if (FAILED(hr))
    {
        goto done;
    }

    bMFStartup = true;
	
	InitDevices();

done:
    if (FAILED(hr))
    {
        ShowError(NULL, L"Failed to start application", hr);
    }
    if (bMFStartup)
    {
        MFShutdown();
    }
    if (bCoInit)
    {
        CoUninitialize();
    }
}

__declspec(dllexport) void __cdecl CameraCapture(bool startfullscreen, int buttonsize, CameraDoneCallback callback)
{
	bool firstTime = ! cameraInited;

	if (! cameraInited)
	{
		CameraInit();
		cameraInited = true;
	}
	
	cameraCode = 0;
	cameraFilename = L"";
	
	cameraFullScreen = startfullscreen;
	cameraButtonSize = buttonsize;
	cameraButtonHalf = buttonsize / 2;

	SetupZones(firstTime);

    HANDLE thread = CreateThread(NULL, 0, CreateWindowThreaded, NULL, 0, 0);
	WaitForSingleObject(thread,INFINITE);

    g_pEngine->DestroyCaptureEngine();
	
	callback(cameraCode, cameraFilename);
}
