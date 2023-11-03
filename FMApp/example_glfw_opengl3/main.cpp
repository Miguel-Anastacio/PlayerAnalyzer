#define GLEW_STATIC
#include <Windows.h>
#include "Application.h"

#ifdef _DEBUG

int main(int, char**)
{
    PlayerAnalyzer::Main();
}

#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    PlayerAnalyzer::Main();
}

#endif // DEBUG

