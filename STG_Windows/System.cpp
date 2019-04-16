//プログラム全体で必要になる情報を取得するクラスです。
//それだｋ(ry

#include "System.hpp"

System::System()
{
	counter = 0;
	starttime = GetNowCount();
}

bool System::Update()
{
	counter++;
	globaltime = GetNowCount() - starttime;
	return true;
}

int System::GetCount()
{
	return counter;
}

int System::GetTime()
{
	return globaltime;
}

