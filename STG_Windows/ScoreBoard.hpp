#pragma once

class ScoreBoard
{
private:
	int gr;
	int score;

private:
	void Update();
	void Draw();

public:
	ScoreBoard();
	void All();
};