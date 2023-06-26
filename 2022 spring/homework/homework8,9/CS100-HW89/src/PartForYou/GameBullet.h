#ifndef GAMEBULLET_H__
#define GAMEBULLET_H__

#include "ObjectBase.h"
#include "GameWorld.h"
class GameWorld;


class Bullet : public GameObject {
public:
	Bullet(int imageID, int x, int y, int direction, int layer, double size, int set_power, GameWorld* world, int opt);
	virtual int NewX() = 0;
	virtual int NewY() = 0;
	virtual void dosomething(int x, int y) = 0;
	int GetPower() const;
private:
	int power;
};

class Blue_Bullet : public Bullet {
public:
	Blue_Bullet(int x, int y, double size, int set_power, GameWorld* world);
	virtual void dosomething(int x, int y) override;
	void step3();
	virtual int NewX() override;
	virtual int NewY() override;
};

class Red_Bullet : public Bullet {
public:
	Red_Bullet(int x, int y, int direction, int set_power, GameWorld* world);
	virtual void dosomething(int x, int y) override;
	void step3();
	virtual int NewX() override;
	virtual int NewY() override;
};

class Meteor : public Bullet {
public:
	Meteor(int x, int y, GameWorld* world);
	virtual void dosomething(int x, int y) override;
	void step3();
	virtual int NewX() override;
	virtual int NewY() override;
};

#endif // GAMEBULLET_H__