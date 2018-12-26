﻿#include "debug.h"
#include "Game.h"

#include "SceneManager.h"

#define WINDOW_CLASS_NAME L"Game"
#define MAIN_WINDOW_TITLE L"Game"
 

#include "Scene_1.h"
#include "Scene_Intro.h"


Game *game;
SceneManager * _sceneManager;




//
//
//class CSampleKeyHander: public KeyEventHandler
//{
//	virtual void KeyState(BYTE *states);
//	virtual void OnKeyDown(int KeyCode);
//	virtual void OnKeyUp(int KeyCode);
//};
//
//CSampleKeyHander * keyHandler; 
//
//void CSampleKeyHander::OnKeyDown(int KeyCode) // khi đè phím
//{
//	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
//
//	if (KeyCode == DIK_ESCAPE)
//		DestroyWindow(hWnd); // thoát
//
//	if (KeyCode == DIK_Q)
//		simon->SetPosition(SIMON_POSITION_DEFAULT);
//	
//	if (KeyCode == DIK_SPACE)
//	{ 
//			simon->Jump();
//	}
//
//	if (KeyCode == DIK_1)
//	{
//		DebugOut(L"[SIMON] X = %f , Y = %f \n", simon->GetX()+10, simon->GetY());
//	}
//
//	if (KeyCode == DIK_X)
//	{
//		//DebugOut(L"[SIMON] X = %f , Y = %f \n", simon->x + 10, simon->y);
//		simon->Attack(simon->_ListWeapon[0]);
//	}
// 
//}
//
//void CSampleKeyHander::OnKeyUp(int KeyCode) // khi buông phím
//{
//	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
//
//	switch (KeyCode)
//	{
//	case DIK_SPACE:
//		//simon->Sit();
//		break; 
//	}
//}
//
//void CSampleKeyHander::KeyState(BYTE *states)
//{
//
//	if (game->IsKeyDown(DIK_DOWN))
//	{ 
//		simon->Sit();
//
//		if (game->IsKeyDown(DIK_RIGHT))
//			simon->Right();
//
//		if (game->IsKeyDown(DIK_LEFT))
//			simon->Left();
//
//		return;
//	}
//	else
//		simon->Stop();
//
//
//	if (game->IsKeyDown(DIK_RIGHT))
//	{
//		simon->Right();
//		simon->Go();
//	}
//	else
//		if (game->IsKeyDown(DIK_LEFT))
//		{
//			simon->Left();
//			simon->Go();
//		}
//		else
//		{
//			simon->Stop();
//		}
//		//DebugOut(L"ahihihihi\n");
//	// disable control key when Mario die 
//	//if (mario->GetState() == MARIO_STATE_DIE) return;
//	//if (game->IsKeyDown(DIK_RIGHT))
//	//	mario->SetState(MARIO_STATE_WALKING_RIGHT);
//	//else if (game->IsKeyDown(DIK_LEFT))
//	//	mario->SetState(MARIO_STATE_WALKING_LEFT);
//	//else
//	//	mario->SetState(MARIO_STATE_IDLE);
//
//
//
//
//}
//
//
//
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
 
void LoadResources()
{
	_sceneManager->LoadResources();
}
 
void Update(DWORD dt)
{ 
	_sceneManager->Update(dt); 
}
 
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, D3DCOLOR_BACKGROUND); // D3DCOLOR_BACKGROUND biến toàn cục quản lí màu nền
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		 

		_sceneManager->Render();


		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{ 
			frameStart = now;

			game->ProcessKeyboard();
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, Window_Width, Window_Height);

	game = Game::GetInstance();
	game->Init(hWnd);

	_sceneManager = SceneManager::GetInstance();


	_sceneManager->SetScene(new Scene_1()); // vào màn 1
	 


	//keyHandler = new CSampleKeyHander();
	game->InitKeyboard(/*keyHandler*/);


	//LoadResources();
	

	SetWindowPos(hWnd, 0, 0, 0, Window_Width, Window_Height, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
 
	Run();

	return 0;
}