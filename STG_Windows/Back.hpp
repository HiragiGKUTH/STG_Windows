#pragma once

class Back
{
	int backgr;
	int x,y;
	int cnt;
	int score;

private:
	void Update();
	void Draw();

public:
	Back();
	~Back();
	void All();
};