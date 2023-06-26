#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#include <list>

#include "WorldBase.h"
#include "GameObjects.h"
#include "ObjectBase.h"
class GameObject;
class Dawnbreaker;

class GameWorld : public WorldBase {
public:
	GameWorld();
	virtual ~GameWorld();

	virtual void Init() override;

	virtual LevelStatus Update() override;

	virtual void CleanUp() override;

	virtual bool IsGameOver() const override;

	int Getlives() const;
	void Setlives(int new_lives);
	int GetEnemy() const;
	void ModifyEnemy(bool flag);
	int Getmeteor() const;
	void Setmeteor(int new_meteor);
	int GetOnScreen() const;
	void SetOnScreen(int new_onScreen);
	void Setdawnbreaker(Dawnbreaker* new_dawnbreaker);
	Dawnbreaker* Getdawnbreaker();
	void AddElement(GameObject* new_element);
	bool crash(GameObject* object1, GameObject* object2);
	std::list<GameObject*>::iterator GetBegin();
	std::list<GameObject*>::iterator GetEnd();
private:
	std::list<GameObject*> li;
	Dawnbreaker* dawnbreaker;
	GameWorld* my_world;
	int lives;//共3命,不随关卡更新
	int enemy;//消灭敌机数
	int meteor;
	int onScreen;
};

#endif // !GAMEWORLD_H__