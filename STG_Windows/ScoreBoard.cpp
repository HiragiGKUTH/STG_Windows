#include "ScoreBoard.hpp"
#include "System.hpp"

ScoreBoard::ScoreBoard()
{
	gr = LoadGraph("assets/img/background/board00.png");
}

void ScoreBoard::Update()
{

}

void ScoreBoard::Draw()
{
	DrawGraph(0, 0, gr, true);
}

void ScoreBoard::All()
{
	Update();
	Draw();
}