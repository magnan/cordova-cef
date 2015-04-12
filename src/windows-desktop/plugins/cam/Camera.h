typedef void (*CameraDoneCallback)(int, wchar_t*);

extern "C" __declspec(dllexport) void __cdecl CameraCapture(const char*, const char*, bool, int, CameraDoneCallback);
