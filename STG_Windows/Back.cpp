//�w�i��`�悷��N���X
//�w�i�͂����摜���������̂ŕ��u


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
