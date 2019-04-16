//�v���O�����S�̂ŕK�v�ɂȂ�����擾����N���X�ł��B
//���ꂾ��(ry

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

