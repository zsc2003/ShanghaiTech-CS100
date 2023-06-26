#ifndef GAMEPLANES_H__
#define GAMEPLANES_H__

#include "ObjectBase.h"
#include "GameWorld.h"
class GameWorld;

class Planes : public GameObject {
public:
	Planes(int id, int x, int y, GameWorld* world, int new_hp, int new_attack, int new_speed,int opt,int energy);
	virtual int NewX() override;
	virtual int NewY() override;
	virtual void dosomething(int x, int y) override;
	void step3();
	int Gethp() const;
	void Sethp(int new_hp);
	int GetAttack() const;
	void SetAttack(int new_attack);
	int GetSpeed() const;
	void SetSpeed(int new_speed);
	int GetPolicy() const;
	void SetPolicy(int new_policy);
	int GetPolicyTime() const;
	void SetPolicyTime(int new_policy_time);
	int GetEnergy() const;
	void SetEnergy(int new_energy);
	virtual void Attack() = 0;
	virtual void Destory() = 0;
private:
	int hp, attack, speed;
	int policy, policy_time;//0 无 1 左下 2 正下 3 右下
	int energy;
};

class Alphatron :public Planes {
public:
	Alphatron(int x, int y, GameWorld* world, int hp, int attack, int speed);
	virtual void Attack();
	virtual void Destory();
};

class Sigmatron :public Planes {
public:
	Sigmatron(int x, int y, GameWorld* world, int hp, int attack, int speed);
	virtual void Attack();
	virtual void Destory();
};

class Omegatron :public Planes {
public:
	Omegatron(int x, int y, GameWorld* world, int hp, int attack, int speed);
	virtual void Attack();
	virtual void Destory();
};


#endif // GAMEPLANES_H__