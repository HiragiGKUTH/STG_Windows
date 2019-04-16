//���̃t�@�C���͂��ׂẴ\�[�X�t�@�C������Q�Ƃ���܂��B
//Dxlib�Ƃ����d�C���N���[�h��������ʓ|���������ƂɂȂ�̂ŁA
//�h�~�􂠂�炵���ł����A�������悭�킩���̂Ŏg���Ă܂���B

#include "Singleton.h"
#include "DxLib.h"

class System : public Singleton<System>
{
private:
	int counter;
	int globaltime;
	int starttime;

	System();
	friend Singleton<System>;
public:

	bool Update();
	int GetCount();
	int GetTime();
};