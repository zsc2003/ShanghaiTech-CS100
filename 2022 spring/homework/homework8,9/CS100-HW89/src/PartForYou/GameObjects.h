#ifndef GAMEOBJECTS_H__
#define GAMEOBJECTS_H__

#include "ObjectBase.h"
#include "GameWorld.h"
class GameWorld;

class GameObject : public ObjectBase {
public:
	GameObject(int imageID, int x, int y, int direction, int layer, double size, GameWorld *world,int new_opt);
	bool GetState() const;
	void SetState(bool flag);
	virtual void Update() override;
	virtual int NewX() = 0;
	virtual int NewY() = 0;
	virtual void dosomething(int x, int y) = 0;
	int GetOpt() const;
	GameWorld* GetWorld() const;
private:
	bool state;//true alive flase dead
	GameWorld *my_world;
	int opt;
	//dawnbreaker 1, star 2, blue bullet 3, red bullet 4, meteor 5, HPGoodie 6, PowerUpGoodie 7
	//MeteorGoodie 8, alpha 9, sigma 10, omega 11 ,Explosion 12
};

class Star : public GameObject {
public:
	Star(int x, int y, double size, GameWorld* world);
	virtual int NewX() override;
	virtual int NewY() override;
	virtual void dosomething(int x, int y) override;
};

class Dawnbreaker : public GameObject {
public:
	Dawnbreaker(GameWorld* world);
	virtual int NewX() override;
	virtual int NewY() override;
	virtual void dosomething(int x, int y) override;

	int Gethp() const;
	int Getenergy() const;
	virtual void Sethp(int new_hp);
	virtual void Setenergy(int newenergy);
	virtual int Getlevel_up() const;
	virtual void Setlevel_up(int new_level_up);
	
private:
	int hp;
	int energy;
	int level_up;
};


#endif // GAMEOBJECTS_H__