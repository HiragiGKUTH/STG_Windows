//このファイルはすべてのソースファイルから参照されます。
//Dxlibとか多重インクルードさせたら面倒くさいことになるので、
//防止策あるらしいですが、理屈がよくわからんので使ってません。

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