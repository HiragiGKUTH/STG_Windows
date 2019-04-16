//操作プレイヤーに関してのクラスです。
//それだけ。

#include "System.hpp"
#include "Player.hpp"
#include "Keyboard.hpp"
#include "GV.h"

Player::Player()
{
		//プレイヤーに関して初期化
	LoadDivGraph("assets/img/char/Reimudot.png",30,10,3,64,96,gr[0],true);
	LoadDivGraph("assets/img/char/Marisadot.png",15,5,3,64,96,gr[1],true);
	hitgr = LoadGraph("assets/img/char/Hitbox1.png");
	GetGraphSize(gr[0][0], &imgX, &imgY);

	knd = 1;
	move = 1.0f;
	cnt = 0;
	state = 0;
	flag = 0;
	animCnt = 0;
	SPEED = 8.0;
	x = (FIELD_X + FIELDSIZE_X) / 2 + FIELD_X / 2;
	y = 900;

		//プレイヤーのショットに関して初期化
	LoadDivGraph("assets/img/bullet/bullet_p.png",3,3,1,21,256,shotgr,true);
	for (int i = 0; i < SHOT_MAX; i++)
	{
		shot[i].x = 0.0f;
		shot[i].y = 0.0f;
		shot[i].ang = 0.0f;
		shot[i].cnt = 0;
		shot[i].knd = 0;
		shot[i].flag = false;
		GetGraphSize(shotgr[0],&shot[i].imgX,&shot[i].imgY);
		shot[i].collision = 64.0f;
	}

}

Player::~Player()
{

}

void Player::Move()
{
		//キー状態格納
	int up = Keyboard::Instance()->GetPressingCount(KEY_INPUT_UP);
	int down = Keyboard::Instance()->GetPressingCount(KEY_INPUT_DOWN);
	int left = Keyboard::Instance()->GetPressingCount(KEY_INPUT_LEFT);
	int right = Keyboard::Instance()->GetPressingCount(KEY_INPUT_RIGHT);
	int shift = Keyboard::Instance()->GetPressingCount(KEY_INPUT_LSHIFT);
	
		//斜め移動判定
	if (left > 1 || right > 1)
	{
		if (up > 1 || down > 1)
		{
			move = 0.71f;
		}
		else {
			move = 1.0f;
		}
	}
	else if (up > 1 || down > 1)
	{
		move = 1.0f;
	}
	if(shift > 1) move*=0.6f;

		//移動判定
	if(left > 1)
		{x -= SPEED*move;}
	if (right > 1)
		{x += SPEED*move;}
	if (up > 1)
		{y -= SPEED*move;}
	if (down > 1)
		{y += SPEED*move;}

		//画面内に収める
	if(x - imgX/2 < FIELD_X) x = (float)FIELD_X + imgX/2;
	if(FIELD_X + FIELDSIZE_X < x + imgX/2) x = (float)FIELD_X + FIELDSIZE_X - imgX/2;
	if (y - imgY / 2 < FIELD_Y) y = (float)FIELD_Y + imgY / 2;
	if (FIELD_Y + FIELDSIZE_Y < y + imgY / 2) y = (float)FIELD_Y + FIELDSIZE_Y - imgY / 2;

}

void Player::Animation()
{
	int up = Keyboard::Instance()->GetPressingCount(KEY_INPUT_UP);
	int down = Keyboard::Instance()->GetPressingCount(KEY_INPUT_DOWN);
	int left = Keyboard::Instance()->GetPressingCount(KEY_INPUT_LEFT);
	int right = Keyboard::Instance()->GetPressingCount(KEY_INPUT_RIGHT);
	if(cnt%10 == 0)
	{ 
		animCnt = cnt%70/10;
		switch (animCnt)
		{
			case 5:
				animCnt = 3;
				break;
		
			case 6:
				animCnt = 2;
				break;
		
			case 7:
				animCnt = 1;
				break;
		}
	
		if (left > 1)
		{
			animCnt = cnt%30/10+5;
	
			if (left > 10 * 3)
			{
				animCnt = cnt%20/10+8;
			}
		}
		if (right > 1)
		{
			animCnt = cnt % 30 / 10 + 10;

			if (right > 10 * 3)
			{
				animCnt = cnt % 20 / 10 + 13;
			}
		}
	}
	DrawFormatStringF(x+50,y+50,GetColor(255,255,255),"Anim:%d",animCnt);
}

void Player::Shot()
{
	if (cnt % 1 == 0 && Keyboard::Instance()->GetPressingCount(KEY_INPUT_Z) > 1)
	{
		for (int i = 0; i < SHOT_MAX; i++)
		{
			if (shot[i].flag == false)
			{
				shot[i].flag = true;
				shot[i].ang = 0;
				if(cnt % 2 == 0)
				{
					shot[i].x = x+24;
					shot[i].y = y - shot[i].imgY/2;
				}
				else {
					shot[i].x = x-24;
					shot[i].y = y - shot[i].imgY / 2;
				}
				break;
			}
		}
	}
	for (int i = 0; i < SHOT_MAX; i++)
	{
		if (shot[i].flag == true)
		{
			shot[i].y -= 48.0f;
			if (shot[i].y < FIELD_Y - shot[i].imgY / 2) shot[i].flag = false;
		}
	}
}

void Player::Update()
{
	cnt++;
	Player::Move();
	Player::Shot();
	Player::Animation();
}

void Player::Draw()
{
	SetDrawArea(FIELD_X,FIELD_Y,FIELD_X + FIELDSIZE_X,FIELD_Y + FIELDSIZE_Y);


	DrawRotaGraphF(x,y,1.0f,0.0f,gr[knd][animCnt],true,false);

	SetDrawBlendMode(DX_BLENDMODE_ADD, 128);
	for (int i = 0; i < SHOT_MAX; i++)
	{
		if(shot[i].flag == true)
			DrawRotaGraphF(shot[i].x,shot[i].y,1.0,shot[i].ang,shotgr[shot[i].knd],true,false);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,255);


	SetDrawAreaFull();
}

void Player::GetPlayerPos(double *x, double *y)
{
	*x = this->x;
	*y = this->y;
}

void Player::All()
{
	Update();
	Draw();
}