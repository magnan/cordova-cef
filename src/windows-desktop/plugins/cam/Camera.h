typedef void (*CameraDoneCallback)(int, wchar_t*);

extern "C" __declspec(dllexport) void __cdecl CameraCapture(bool, int, CameraDoneCallback);
