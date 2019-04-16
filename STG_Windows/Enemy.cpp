//敵のクラス。
//移動やショットなどの制御、描画等


#include "Enemy.hpp"
#include "GV.h"
#include "System.hpp"
#include <cmath>


Enemy::Enemy(float arg_x, float arg_y, int arg_in_time, int arg_move_kind, int arg_shot_kind)
{
	LoadDivGraph("assets/img/char/Enemy.png", 24, 6, 4, 64, 64, gr, true);	//キャラ画像の読み込み
	GetGraphSize(gr[0], &imgX, &imgY);								//キャラのサイズを取得

																	//初期位置設定
	x = arg_x;
	y = arg_y;
	vx = 0.0f;
	vy = 0.0f;
	ang = 0.0f;
	collisionrad = 16.0;

	//移動タイミング設定
	in_time = arg_in_time;

	//カウンタ、フラグ、敵の種類を初期化
	move_kind = arg_move_kind;
	shot_kind = arg_shot_kind;
	cnt = 0;
	s_cnt = 0;
	endflag = false;
	shotflag = false;

	LoadDivGraph("./assets/img/bullet/bullet01.png", 16, 4, 4, 64, 64, s_gr, true);



	//弾のパラメータ初期化
	s1 = 0;
	s2 = 0;
	s3 = 0;
	s4 = 0;
	sf1 = 0;
	sf2 = 0;
	sf3 = 0;
	sf4 = 0;
	s_end = false;
}

bool Enemy::IsDestroyed()
{
	return endflag;
}

bool Enemy::Init()
{
	return true;
}
	
	//更新
void Enemy::Update()
{
	cnt++;
	s_cnt = 0;
	Move();
	Enter_shot();
	Move_shot();

		//デバッグ用
	printfDx("%d shots.\n", shot.size());
		//敵が持つ弾が無く、かつ画面外に出たらこの敵を消すフラグを立てる
	if (120 < this->cnt && shot.empty())
	{
		if (this->x + this->imgX < FIELD_X || FIELD_X + FIELDSIZE_X < this->x + this->imgX ||
			this->y + this->imgY < FIELD_Y || FIELD_Y + FIELDSIZE_Y < this->y + this->imgY)
			this->endflag = true;
	}
}

	//敵キャラ移動
void Enemy::Move()
{
	int gcnt = System::Instance()->GetCount();
	int gtime = System::Instance()->GetTime();
		//switch文により行動パターン分け
	switch (move_kind)
	{
		case 0:	//降りてきて撃ってそのまま帰る
		{
			stop_time = 90;
			out_time = 180;
			if (0 <= cnt && cnt < 90)
			{
				speed = 5.0f;
				ang = TRANS_RAD(90);
			}
			else if (stop_time <= cnt && cnt < out_time)
			{
				speed = 0.0f;
				shotflag = true;
			}
			else if (out_time <= cnt)
			{
				speed = 5.0f;
				ang = TRANS_RAD(270);
				shotflag = false;
			}
			break;
		}
		case 1:	//降りてきて右回転して帰る
		{
			stop_time = 90;
			out_time = 260;
			if (0 <= cnt && cnt < 90)
			{
				speed = 4.0f;
				ang = TRANS_RAD(90);
			}
			else if (stop_time <= cnt && cnt < out_time)
			{
				speed = 3.5f;
				ang = TRANS_RAD(90 + (cnt - stop_time));
				shotflag = true;
			}
			else if (out_time <= cnt)
			{
				speed = 4.0f;
				ang = TRANS_RAD(90 + (out_time - stop_time));
				shotflag = false;
			}
			break;
		}
		case 2:	//降りてきて左回転して帰る
		{
			stop_time = 90;
			out_time = 260;
			if (0 <= cnt && cnt < 90)
			{
				speed = 4.0f;
				ang = TRANS_RAD(90);
			}
			else if (stop_time <= cnt && cnt < out_time)
			{
				speed = 3.5f;
				ang = TRANS_RAD(90 - (cnt - stop_time));
				shotflag = true;
			}
			else if (out_time <= cnt)
			{
				speed = 4.0f;
				ang = TRANS_RAD(90 - (out_time - stop_time));
				shotflag = false;
			}
			break;
		}
		case 64://デバッグ用
		{
			stop_time = 90;
			out_time = 9000;
			if (0 <= cnt && cnt < 90)
			{
				speed = 5.0f;
				ang = TRANS_RAD(90);
			}
			else if (stop_time <= cnt && cnt < out_time)
			{
				speed = 0.0f;
				shotflag = true;
			}
			else if (out_time <= cnt)
			{
				speed = 5.0f;
				ang = TRANS_RAD(270);
				shotflag = false;
			}
			break;
		}

		default:
		{
			printfDx("Error:move_kind %d is not exist", move_kind);
			break;
		}
	}
		//実際に移動させる
	this->vx = cos(this->ang)*this->speed;
	this->vy = sin(this->ang)*this->speed;
	this->x += this->vx;
	this->y += this->vy;

}

	//敵ショットの登録
void Enemy::Enter_shot()
{
	if (shotflag)	//敵が弾を打てる状態なら弾を登録
	{
		Shot tmp;	//プッシュ用
		switch (shot_kind)	//弾幕の種類分け
		{
			case 0:	//全方位弾
			{
				const int way = 18;
				if (this->cnt % 1 == 0)
				{
					for (int i = 0; i < way; i++)
					{
						int kind = i%14;
						
						tmp.ang = TRANS_RAD((float)i*(360/way));
						tmp.x = this->x;
						tmp.y = this->y;
						tmp.cnt = 0;
						tmp.kind = kind;
						tmp.flag = true;
						tmp.speed = 3.0f;
						tmp.colrad = 15;
						shot.push_back(tmp);
					}
				}
				break;
			}

			case 1:	//前方バラマキ弾
			{
				if (cnt % 4 == 0)
				{
					tmp.ang = TRANS_RAD(cnt);
					tmp.x = x;
					tmp.y = y+50;
					tmp.cnt = 0;
					tmp.kind = GetRand(15);
					tmp.flag = true;
					tmp.speed = 5.0f;
					tmp.colrad = 15;
					shot.push_back(tmp);
				}
				break;
			}


			default:
				break;
		}
	}
}

	//敵ショットの移動
void Enemy::Move_shot()
{
	for (auto itr = shot.begin(); itr != shot.end();)
	{
		if (!(itr->x + 16 < FIELD_X || FIELD_X + FIELDSIZE_X < itr->x - 16||
			  itr->y + 16 < FIELD_Y || FIELD_Y + FIELDSIZE_Y < itr->y - 16))
		{
			switch (shot_kind)
			{
				case 0:
				{
					//直線移動させるので何もなし
					break;
				}

				case 1:
				{
					break;
				}

				case 2:
				{
					break;
				}

				case 3:
				{
					break;
				}
			}



				//実際に移動させる
			itr->vx = cos(itr->ang)*itr->speed;
			itr->vy = sin(itr->ang)*itr->speed;
			itr->x += itr->vx;
			itr->y += itr->vy;
			itr->cnt++;
			itr++;
		}
		else {
			itr = shot.erase(itr);
		}
	}
}

	//敵キャラの描画
void Enemy::Draw()
{
		//敵キャラおよび敵ショットはゲーム画面内でのみ描画させる
	SetDrawArea(FIELD_X, FIELD_Y, FIELD_X + FIELDSIZE_X, FIELD_Y + FIELDSIZE_Y);
	SetDrawMode(DX_DRAWMODE_ANISOTROPIC);
	for (auto itr = shot.begin(); itr != shot.end();)
	{
		DrawRotaGraphF(itr->x, itr->y, 0.8f, itr->ang + 3.14159/2, s_gr[itr->kind], true, false);
		itr++;
	}


	int img=0;
	if (!endflag)
	{
		img = cnt%30/10;
		DrawRotaGraphF(x,y,2.0,0.0,gr[img],true,false);
		DrawFormatStringF(x + 20, y + 20, GetColor(255, 255, 255), "%d Shots", s_cnt);
	}

	SetDrawMode(DX_DRAWMODE_NEAREST);
	SetDrawAreaFull();
}

int Enemy::GetStartCount()
{
	return in_time;
}

	//すべて呼ぶ関数
bool Enemy::All()
{
	Update();
	Draw();
	return true;
}

Enemy::~Enemy()
{

}

void Enemy::GetEnemyPos(double *x, double *y)
{
	*x = this->x;
	*y = this->y;
}

double Enemy::GetEnemyRad()
{
	return collisionrad;
}