
// Platform Globals


static bool running = true;

// Platform Functions
bool platform_create_window(int width, int height, char* windowTitle);
void platform_update_window();

// Windows Platform
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

// Windows Globals
static HWND window;

// Windows Platform Implementations

LRESULT CALLBACK windows_window_callback(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) {
  LRESULT result = 0;

  switch(msg) {
    case WM_CLOSE: 
    {
      running = false;
      break;
    }

    default:
    {
      result = DefWindowProcA(window, msg, wParam, lParam);
    }
  }
  return result;
}

bool platform_create_window(int width, int height, char* windowTitle) {

  HINSTANCE instance = GetModuleHandleA(0);
  WNDCLASS wc = {};
  wc.hInstance = instance;
  wc.hIcon = LoadIcon(instance, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL,IDC_ARROW);
  wc.lpszClassName = windowTitle;
  wc.lpfnWndProc = windows_window_callback;

  if(!RegisterClassA(&wc)) {
    return false;
  }

  int dwStyle = WS_THICKFRAME;

  window = CreateWindowExA(0, windowTitle,windowTitle,dwStyle,100,100,width,height,NULL, NULL,instance,NULL);

  if(window == NULL) {
    return false;
  }

  ShowWindow(window,SW_SHOW);

  return true;

}

void platform_update_window() {
  MSG msg;
  while(PeekMessageA(&msg,window,0,0,PM_REMOVE)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
}

#endif

int main() {
  platform_create_window(1280,720, "Window Title");
  while (running) {
    platform_update_window();
  }

  return 0;
}