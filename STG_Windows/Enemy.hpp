#pragma once
#include <list>

class Enemy
{
		//敵
	int kind;						//敵の種類
	float x,y;						//座標
	float speed;					//速さ
	float vx, vy;					//速度
	float ang;						//角度
	float collisionrad;				//敵の当たり判定の半径
	int gr[24];						//グラフィックハンドル
	int imgX,imgY;					//画像のサイズ
		//行動パターン制御用
	int in_time,stop_time,shot_time,out_time;
	int cnt;						//カウンタ
	int s_cnt;						//敵がいま打っている弾の数の保持用
	int shot_kind,move_kind;		//移動パターン、弾幕パターンの保持用
	bool endflag;					//敵が消滅したかのフラグ
	bool startflag;					//敵が生成されたかのフラグ
	bool shotflag;					//敵がショットを撃てるかどうかのフラグ

		//弾
	typedef struct
	{
		float x, y;		//座標
		float vx, vy;	//速度
		float ang;		//角度
		float speed;	//早さ
		float colrad;	//あたり判定の半径
		int kind;		//弾の種類
		int cnt;		//カウンタ
		bool flag;		//存在するかのフラグ
	}Shot;

	std::list<Shot> shot;
	int s_gr[16];

		//弾用パラメータ(使用するかどうかは任意)
	int s1;
	int s2;
	int s3;
	int s4;
	float sf1;
	float sf2;
	float sf3;
	float sf4;
	bool s_end;	//弾幕が終了したかのフラグ

	void Update();
		void Move();
		void Enter_shot();
		void Move_shot();

	void Draw();

public:
	bool All();
	bool IsDestroyed();
	bool Init();
	int GetStartCount();
	void GetEnemyPos(double *x, double *y);
	double GetEnemyRad();
	Enemy(float arg_x, float arg_y, int arg_in_time, int arg_move_kind, int arg_shot_kind);
	~Enemy();
};