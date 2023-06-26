#include "GameWorld.h"
#include "GameObjects.h"
#include "GameObjects.cpp"
#include "GamePlanes.h"
#include <cmath>

GameWorld::GameWorld() {
	lives = 3;
	enemy = 0;
	meteor = 0;
	onScreen = 0;
	my_world = this;
	dawnbreaker = nullptr;
}

GameWorld::~GameWorld() {
	if (dawnbreaker != nullptr)
	{
		delete dawnbreaker;
		dawnbreaker = nullptr;
	}
	for (auto it = li.begin();it != li.end();)
	{
		delete* it;
		it = li.erase(it);
	}
}

int GameWorld::Getlives() const {
	return lives;
}
void GameWorld::Setlives(int new_lives) {
	lives = new_lives;
}
int GameWorld::Getmeteor() const {
	return meteor;
}
void GameWorld::Setmeteor(int new_meteor) {
	meteor = new_meteor;
}
int GameWorld::GetEnemy() const {
	return enemy;
}
void GameWorld::ModifyEnemy(bool flag) {
	if (flag == false)
		enemy = 0;
	else
		enemy++;
}
int GameWorld::GetOnScreen() const {
	return onScreen;
}
void GameWorld::SetOnScreen(int new_onScreen){
	onScreen = new_onScreen;
}
void GameWorld::AddElement(GameObject* new_element)  {
	li.push_back(new_element);
}
void GameWorld::Setdawnbreaker(Dawnbreaker* new_dawnbreaker) {
	if (dawnbreaker != nullptr)
		delete dawnbreaker;
	dawnbreaker = new_dawnbreaker;
}
Dawnbreaker* GameWorld::Getdawnbreaker() {
	return dawnbreaker;
}
bool GameWorld::crash(GameObject* object1, GameObject* object2)
{
	double x1 = (double)object1->GetX(), y1 = (double)object1->GetY();
	double x2 = (double)object2->GetX(), y2 = (double)object2->GetY();
	double s1 = object1->GetSize(), s2 = object2->GetSize();
	x1 -= x2, y1 -= y2;
	double d = sqrt(x1 * x1 + y1 * y1);
	if (d < 30.0 * (s1 + s2))
		return true;
	return false;
}
std::list<GameObject*>::iterator GameWorld::GetBegin() { return li.begin(); }
std::list<GameObject*>::iterator GameWorld::GetEnd() { return li.end(); }
void GameWorld::Init() {
	ModifyEnemy(false);
	Setmeteor(0);
	SetOnScreen(0);
	//创建一只全新的“破晓号”
	Dawnbreaker* dawnbreaker = new Dawnbreaker(my_world);
	Setdawnbreaker(dawnbreaker);
	// std::cout << dawnbreaker->Gethp() << '\n';
	//30颗星星
	for (int i = 1;i <= 30;++i)
	{
		int x = randInt(0, WINDOW_WIDTH - 1);
		int y = randInt(0, WINDOW_HEIGHT - 1);
		double size = (double)randInt(10, 40) / 100.0;
		GameObject* star = new Star(x, y, size, my_world);
		li.push_back(star);
	}
}

LevelStatus GameWorld::Update() {
	//1.为 GameWorld 生成新的星空背景
	int posibility = randInt(1, 30);
	if (posibility == 6)//1/30的几率生产,6为随便选的数字
	{
		int x = randInt(0, WINDOW_WIDTH - 1);
		int y = WINDOW_HEIGHT - 1;
		double size = (double)randInt(10, 40) / 100.0;	
		GameObject* star = new Star(x, y, size, my_world);
		li.push_back(star);
	}

	//2.为 GameWorld 生成新的敌机
	int required = 3 * GetLevel();
	int toDestroy = required - GetEnemy();
	int maxOnScreen = (5 + GetLevel()) / 2;
	int allowed = std::min(toDestroy, maxOnScreen);
	int onScreen = GetOnScreen();
	int possibility = randInt(1, 100);
	int set_new = allowed - onScreen;

	//std::cout << GetEnemy() << ' ' << toDestroy << ' ' << onScreen << ' ' << set_new << '\n';

	//3.若在上一步中确定生成敌机，则需要进一步随机决定此敌机的种类
	if ((set_new > 0) && (possibility <= set_new) && onScreen < maxOnScreen)
	{
//		std::cout << GetOnScreen() << '\n';

		double P1 = 6;
		double P2 = 2 * std::max(GetLevel() - 1, 0);
		double P3 = 3 * std::max(GetLevel() - 2, 0);

		int alpha = (int)(P1 * 100.0 / (P1 + P2 + P3));
		int sigma = (int)(P2 * 100.0 / (P1 + P2 + P3));
		int omega = (int)(P3 * 100.0 / (P1 + P2 + P3));
		//std::cout << P1<<' '<<P2<<' '<<P3<<' '<<alpha << '\n';
		possibility = randInt(1, 100);
		int x = randInt(0, WINDOW_WIDTH - 1);
		int y = WINDOW_HEIGHT - 1;
		if (possibility <= alpha)
		{
			int hp = 20 + 2 * GetLevel();
			int attack = 4 + GetLevel();
			int speed = 2 + (int)(GetLevel() / 5);
			GameObject* alphatron = new Alphatron(x, y, my_world, hp, attack, speed);
			li.push_back(alphatron);
			SetOnScreen(GetOnScreen() + 1);
		}
		else if (possibility <= alpha + sigma)
		{
			int hp = 25 + 5 * GetLevel();
			int attack = 0;
			int speed = 2 + (int)(GetLevel() / 5);
			GameObject* sigmatron = new Sigmatron(x, y, my_world, hp, attack, speed);
			li.push_back(sigmatron);
			SetOnScreen(GetOnScreen() + 1);
		}
		else
		{
			int hp = 20 + GetLevel();
			int attack = 2 + 2 * GetLevel();
			int speed = 3 + (int)(GetLevel() / 4);
			GameObject* omegatron = new Omegatron(x, y, my_world, hp, attack, speed);
			li.push_back(omegatron);
			SetOnScreen(GetOnScreen() + 1);
		}
	}

	//4.遍历所有游戏对象(GameObject)，并依次调用它们的 Update()函数
	Getdawnbreaker()->Update();
	for (auto it = li.begin();it != li.end();it++)
		(*it)->Update();

	//5.检测关卡是否失败(破晓号被击毁)
	if (Getdawnbreaker()->GetState() == false)
	{
		lives -= 1;
		//	std::cout << lives << '\n';
		return LevelStatus::DAWNBREAKER_DESTROYED;
	}
		

	//6.检测关卡是否胜利
	if (GetEnemy() == 3 * GetLevel())
		return LevelStatus::LEVEL_CLEARED;

	//7.再次遍历所有游戏对象，将需要删除的对象从你的存储容器中移除
	if (Getdawnbreaker()->GetState() == false)
	{
		delete Getdawnbreaker();
		Setdawnbreaker(nullptr);
	}
	for (auto it = li.begin();it != li.end();)
	{
		if ((*it)->GetState() == false)
		{
			delete (*it);
			it = li.erase(it);
		}
		else
			it++;
	}

	//8.根据破晓号的状态和关卡状态，显示底部的状态栏
	std::string message = "HP: " + std::to_string(Getdawnbreaker()->Gethp()) + "/100   Meteors: "
	+ std::to_string(Getmeteor()) + "   Lives: " + std::to_string(Getlives()) + "   Level: "
	+ std::to_string(GetLevel()) + "   Enemies: " + std::to_string(GetEnemy()) + "/" + std::to_string(3 * GetLevel())
	+ "   Score: " + std::to_string(GetScore());
	SetStatusBarMessage(message);

	return LevelStatus::ONGOING;
}

void GameWorld::CleanUp() {
	if (dawnbreaker != nullptr)
	{
		delete dawnbreaker;
		dawnbreaker = nullptr;
	}
	for (auto it = li.begin();it != li.end();)
	{
		delete *it;
		it = li.erase(it);
	}
	SetOnScreen(0);
	ModifyEnemy(false);
	Setmeteor(0);
}


bool GameWorld::IsGameOver() const {
	if (Getlives() <= 0)
		return true;
	return false;
}