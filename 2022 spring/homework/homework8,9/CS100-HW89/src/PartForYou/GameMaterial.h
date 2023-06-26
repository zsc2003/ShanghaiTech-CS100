#ifndef GAMEMATERIAL_H__
#define GAMEMATERIAL_H__

#include "ObjectBase.h"
#include "GameWorld.h"
class GameWorld;

class Explosion : public GameObject {
public:
	Explosion(int x, int y, GameWorld* world);
	int GetTimes() const;
	void SetTimes(int new_time);
	virtual int NewX() override;
	virtual int NewY() override;
	virtual void dosomething(int x, int y) override;
private:
	int update_times;
};

class Goodie : public GameObject {
public:
	Goodie(int id, int x, int y, GameWorld* world, int opt);
	virtual int NewX() override;
	virtual int NewY() override;
	virtual void dosomething(int x, int y) override;
	virtual void step3() = 0;
};

class HPGoodie : public Goodie {
public:
	HPGoodie(int x, int y, GameWorld* world);
	virtual void step3() override;
};

class PowerUpGoodie : public Goodie {
public:
	PowerUpGoodie(int x, int y, GameWorld* world);
	virtual void step3() override;
};

class MeteorGoodie : public Goodie {
public:
	MeteorGoodie(int x, int y, GameWorld* world);
	virtual void step3() override;
};
#endif // GAMEMATERIAL_H__