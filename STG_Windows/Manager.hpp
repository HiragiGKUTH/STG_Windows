#include "Player.hpp"
#include "Enemy.hpp"
#include "Back.hpp"
#include "ScoreBoard.hpp"
#include <vector>
#include <memory>

class Manager
{
private:
	enum
	{
		E_SHOT,
		E_DESTROY,
		P_SHOT,
		P_DESTROY,
	};
	const int ENEMY_MAX = 16;

	std::shared_ptr<Back> back;
	std::shared_ptr<ScoreBoard> scoreboard;

	std::shared_ptr<Player> player;
	std::vector<std::shared_ptr<Enemy>> enemy;

		//敵データ読み込み用
	typedef struct
	{
		int ID;
		float x;
		float y;
		int in_time;
		int move_kind;
		int shot_kind;
	}EnemyData;

public:
	Manager();
	~Manager();
	void All();
	void LoadEnemyData();
	void CollisionAll();
};