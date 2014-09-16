typedef void (*CameraDoneCallback)(int, wchar_t*);

extern void CameraCapture(bool, int, CameraDoneCallback);
