//背景を描画するクラス
//背景はいい画像が見つからんので放置


#include "System.hpp"
#include "Back.hpp"

Back::Back()
{
	backgr = LoadGraph("assets/img/background/poolwater.jpg");
	x = 0;
	y = 0;
	cnt = 0;
}

Back::~Back()
{

}

void Back::Update()
{

}

void Back::Draw()
{
	DrawGraph(x,y,backgr,true);
}

void Back::All()
{
	Update();
	Draw();
}
