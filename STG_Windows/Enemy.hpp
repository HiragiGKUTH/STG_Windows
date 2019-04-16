#pragma once
#include <list>

class Enemy
{
		//�G
	int kind;						//�G�̎��
	float x,y;						//���W
	float speed;					//����
	float vx, vy;					//���x
	float ang;						//�p�x
	float collisionrad;				//�G�̓����蔻��̔��a
	int gr[24];						//�O���t�B�b�N�n���h��
	int imgX,imgY;					//�摜�̃T�C�Y
		//�s���p�^�[������p
	int in_time,stop_time,shot_time,out_time;
	int cnt;						//�J�E���^
	int s_cnt;						//�G�����ܑł��Ă���e�̐��̕ێ��p
	int shot_kind,move_kind;		//�ړ��p�^�[���A�e���p�^�[���̕ێ��p
	bool endflag;					//�G�����ł������̃t���O
	bool startflag;					//�G���������ꂽ���̃t���O
	bool shotflag;					//�G���V���b�g�����Ă邩�ǂ����̃t���O

		//�e
	typedef struct
	{
		float x, y;		//���W
		float vx, vy;	//���x
		float ang;		//�p�x
		float speed;	//����
		float colrad;	//�����蔻��̔��a
		int kind;		//�e�̎��
		int cnt;		//�J�E���^
		bool flag;		//���݂��邩�̃t���O
	}Shot;

	std::list<Shot> shot;
	int s_gr[16];

		//�e�p�p�����[�^(�g�p���邩�ǂ����͔C��)
	int s1;
	int s2;
	int s3;
	int s4;
	float sf1;
	float sf2;
	float sf3;
	float sf4;
	bool s_end;	//�e�����I���������̃t���O

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