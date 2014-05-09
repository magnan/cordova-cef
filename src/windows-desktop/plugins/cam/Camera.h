typedef void (*CameraDoneCallback)(int, wchar_t*);

__declspec(dllexport) void __cdecl CameraCapture(bool, int, CameraDoneCallback);
