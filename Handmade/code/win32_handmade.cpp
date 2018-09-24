#include <windows.h>

LRESULT CALLBACK 
MainWindowCallback(HWND   Window,
				   UINT   Message,
				   WPARAM wParam,
				   LPARAM lParam)
{
	LRESULT Result = 0;
	
	
	switch(Message)
	{
		case WM_SIZE:
		{
			OutputDebugStringA("WM_SIZE\n");
		}break;
		
		case WM_DESTROY:
		{
			OutputDebugStringA("WN_DESTROY\n");
		}break;
		
		case WM_CLOSE:
		{
			OutputDebugStringA("WN_CLOSE\n");
		}break;
		
		case WM_ACTIVATEAPP:
		{
			OutputDebugStringA("WN_ACTIVATEAPP\n");
		}break;

		case WM_PAINT:
		{
			PAINTSTRUCT Paint;
			HDC DeviceContext = BeginPaint(Window, &Paint);
			int x = Paint.rcPaint.left;
			int y = Paint.rcPaint.top;
			LONG Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
			LONG Width = Paint.rcPaint.left - Paint.rcPaint.right;
			static DWORD Operation = WHITENESS;
			PatBlt(DeviceContext, x, y, Height, Width, Operation);
			if(Operation == WHITENESS)
			{
				Operation = BLACKNESS;
			}
			else
			{
				Operation = WHITENESS;
			}
			
			EndPaint(Window, &Paint);
		}break;
		
		default:
		{
//			OutputDebufStringA("default\n");
			Result = DefWindowProc(Window, Message, wParam, lParam);
		}break;
	}
	
	return Result;
}

int CALLBACK 
WinMain(HINSTANCE Instance,
		HINSTANCE PrevInstance,
		LPSTR     CommandLine,
		int       ShowCode)
{
	WNDCLASS WindowClass = {};
	
	//TODO: Check id HREDRAW/VREDRAW/OWNDC still matter
	WindowClass.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	WindowClass.lpfnWndProc = MainWindowCallback;
	WindowClass.hInstance = Instance;
//  WindowClass.hIcon = ;
	WindowClass.lpszClassName = "HandmadeHeroWindowClass";
	
	if(RegisterClass(&WindowClass))
	{
		HWND WindowHandle =
		
		CreateWindowEx(
			0,
			WindowClass.lpszClassName,
			"Handmade Hero",
			WS_OVERLAPPEDWINDOW|WS_VISIBLE,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			0,
			0,
			WindowClass.hInstance,
			0);
		if(WindowHandle)
		{
			MSG Message;
			for(;;)
			{
				BOOL MessageResult = GetMessage(&Message, 0, 0, 0);
				if(MessageResult > 0)
				{
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}
				else
				{
					break;
				}
			}
			
		}
		else
		{
			//TODO: Logging
		}
	}
	else
	{
		//TODO: Logging
	}
	
	
	return 0;
}	
