//このプログラムはHiragi-GKUTHが個人的にゲームを作りたいがために作成されたものです。
//DxLib使用、コメント足りなくて読みにくいかも、申し訳ないです。
//Copyright © 2016-2017 Hiragi-GKUTH All Rights Reserved.

#include "GV.h"
#include "Fps.hpp"
#include "Manager.hpp"
#include "Keyboard.hpp"
#include "System.hpp"

bool SystemLoop();


Fps fps; 

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
	SetGraphMode(DISPX,DISPY,32);
	//ChangeWindowMode(true);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);


	Manager game;

	while (SystemLoop())
	{
		game.All();
	}
	DxLib_End();
	return 0;
}

bool SystemLoop()
{
	fps.Update();
	fps.Draw();
	
	if (ProcessMessage() == 0 && ScreenFlip() == 0 && ClearDrawScreen() == 0 &&
		clsDx() == 0 && Keyboard::Instance()->Update() &&
		Keyboard::Instance()->GetPressingCount(KEY_INPUT_ESCAPE) == 0 &&
		System::Instance()->Update() == true)
		return true;
	else
		return false;
}
