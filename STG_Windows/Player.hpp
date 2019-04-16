
#define SHOT_MAX 256

class Player
{
		//プレイヤー自体について
	float x,y;		//座標

	int imgX,imgY;	//キャラサイズ
	float collision;//当たり判定半径
	int gr[3][15];		//プレイヤーグラフィックハンドル
	int hitgr;		//ヒットボックスグラフィックハンドル

	float move;	//移動係数

	int knd;		//プレイヤーの種類
	int cnt;		//カウンタ
	int state;		//プレイヤーの状態
	int flag;		//生きてるか
	int animCnt;	//アニメーション用カウンタ
	int img;		//表示すべき画像を示す変数

	float SPEED;


		//プレイヤーショットについて
	typedef struct
	{
		float x;
		float y;
		float ang;
		int cnt;
		int imgX;
		int imgY;
		float collision;
		int knd;
		bool flag;
	}Shot;

	Shot shot[SHOT_MAX];
	int shotgr[3];

private:
	virtual void Update();
		void Move();
		void Animation();
		void Shot();

	void Draw();

public:
	Player();
	~Player();
	void All();
	void GetPlayerPos(double *x, double *y);
};
