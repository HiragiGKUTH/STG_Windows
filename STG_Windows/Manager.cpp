//少なくともゲームのメインシーンにおいて各々を管理するためのクラスです。
//後々シーン管理なり始めたらなにかしらのクラスの継承先になる可能性があります。

#include "Manager.hpp"
#include "System.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>

Manager::Manager()
{
	player = std::shared_ptr<Player>(new Player());
	back = std::shared_ptr<Back>(new Back());
	scoreboard = std::shared_ptr<ScoreBoard>(new ScoreBoard());
	LoadEnemyData();
}

void Manager::All()
{
	int start = GetNowCount();

	CollisionAll();

	back->All();
	player->All();

	for (auto itr = enemy.begin();itr != enemy.end();)
	{
		auto tmp = *itr;
		if(tmp->GetStartCount() < System::Instance()->GetCount())
			tmp->All();

		if (tmp->IsDestroyed())
			itr = enemy.erase(itr);
		else
			itr++;
	}

	scoreboard->All();
	printfDx("Game %d ms.\n", GetNowCount() - start);
}

	//クソ設計過ぎて泣ける
void Manager::LoadEnemyData()
{
	std::ifstream EnemyCsv("./assets/csv/Enemy00.csv");	//ファイル開く
	std::string buf;	//バッファ
	EnemyData data;
	int row = 0;		//行
	int column = 0;		//列
	
	std::getline(EnemyCsv, buf);		//一行読み飛ばして
	buf.erase();						//バッファ削除

	while (std::getline(EnemyCsv,buf))	//ファイルの終端まで読み込む
	{
		column = 0;
		std::stringstream ss(buf);		//ストリームにして扱いやすくする
		std::string tmp[6];				//一時保存用

		for (column; column < 6; column++)	//9個の要素があるのでその分ループ
		{
			int value;		//代入用

			std::getline(ss, tmp[column], ',');		//分割して
			value = std::atoi(tmp[column].c_str());	//変換して代入

			switch (column)	//要素で分けてみたり
			{
					//ひたすら数字を数値に変換しつつデータをブチ込む
				case 0: data.ID = value; break;
				case 1: data.x = (float)value; break;
				case 2: data.y = (float)value; break;
				case 3: data.in_time = value; break;
				case 4: data.move_kind = value; break;
				case 5: data.shot_kind = value; break;
			}
		}
			//vectorにブチ込む
		enemy.push_back(std::shared_ptr<Enemy>(new Enemy(data.x, data.y, data.in_time, data.move_kind, data.shot_kind)));
	}

}

void Manager::CollisionAll()
{
	double px, py;
	double ex, ey;
	player->GetPlayerPos(&px, &py);
	for (auto itr = enemy.begin(); itr != enemy.end();)
	{
		auto tmp = *itr;
		tmp->GetEnemyPos(&ex, &ey);

	}
}

Manager::~Manager()
{

}