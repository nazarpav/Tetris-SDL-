#include"Tetris.h"

int main(int argc, char* argv[])
{
	HWND windowHandle = GetConsoleWindow();
	ShowWindow(windowHandle, SW_HIDE);
	Tetris t(768,1024);
	t.StartGame();
	return 0;
}