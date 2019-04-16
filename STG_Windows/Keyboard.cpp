//�L�[�{�[�h�̏����擾���邽�߂̃N���X
//�݌v��Dixq���̂𗬗p�A���������ς��Ă邩��
//Singleton�Ƃ��g���Ē��q����Ă݂�A�����͂��܂藝�����ĂȂ�

#include "Keyboard.hpp"
#include "System.hpp"

Keyboard::Keyboard()
{
	memset(mKeyPressingCount, 0, sizeof(mKeyPressingCount));
	memset(mKeyReleasingCount, 0, sizeof(mKeyReleasingCount));
}

//�X�V
bool Keyboard::Update()
{
	char nowKeyStatus[KEY_NUM];
	GetHitKeyStateAll(nowKeyStatus);       //���̃L�[�̓��͏�Ԃ��擾
	for (int i = 0; i<KEY_NUM; i++)
	{
		if (nowKeyStatus[i] != 0)
		{            //i�Ԃ̃L�[��������Ă�����
			if (mKeyReleasingCount[i] > 0)
			{//������J�E���^��0���傫�����
				mKeyReleasingCount[i] = 0;   //0�ɖ߂�
			}
			mKeyPressingCount[i]++;          //������J�E���^�𑝂₷
		}
		else
		{                             //i�Ԃ̃L�[��������Ă�����
			if (mKeyPressingCount[i] > 0)
			{ //������J�E���^��0���傫�����
				mKeyPressingCount[i] = 0;    //0�ɖ߂�
			}
			mKeyReleasingCount[i]++;         //������J�E���^�𑝂₷
		}
	}
	return true;
}

//keyCode�̃L�[��������Ă���t���[������Ԃ�
int Keyboard::GetPressingCount(int keyCode)
{
	if (!Keyboard::IsAvailableCode(keyCode))
	{
		return -1;
	}
	return mKeyPressingCount[keyCode];
}

//keyCode�̃L�[��������Ă���t���[������Ԃ�
int Keyboard::GetReleasingCount(int keyCode)
{
	if (!Keyboard::IsAvailableCode(keyCode))
	{
		return -1;
	}
	return mKeyReleasingCount[keyCode];
}

//keyCode���L���Ȓl���`�F�b�N����
bool Keyboard::IsAvailableCode(int keyCode)
{
	if (!(0 <= keyCode && keyCode<KEY_NUM))
	{
		return false;
	}
	return true;
}