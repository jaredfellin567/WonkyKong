#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject{
public:
    Actor(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir, double size = 1.0);
    
    virtual ~Actor();
    
    bool isDead();
    void kill();
    virtual void doSomething() = 0;
    StudentWorld* getWorld();
    bool isEnemy();
    int getTickCount();
    void incTickCount();
    void setTickCount(int x);
    bool dropItem();
    
private:
    bool isAlive;
    StudentWorld* m_world;
    bool m_enemyStatus;
    int m_tickCounter = 0;
};

class Floor : public Actor{
public:
    Floor(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir = 0, double size = 1.0);
    
    ~Floor();
    
    void doSomething();
};

class Player : public Actor{
public:
    Player(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir = 0, double size = 1.0);
    
    ~Player();
    
    void doSomething();
    
    void incBurps();
    void decBurps();
    int getBurps();
    bool isFrozen();
    void freeze();
    void thaw();
    
private:
    bool m_freeze;
    int m_jumpPattern = 0;
    int m_burps = 0;
    int m_freezeCount = 0;
};

class Ladder : public Actor{
public:
    Ladder(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir = 0, double size = 1.0);
    
    ~Ladder();
    
    void doSomething();
};

class Bonfire : public Actor{
public:
    Bonfire(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir = 0, double size = 1.0);
    
    ~Bonfire();
    
    void doSomething();
};

class GarlicGoodie : public Actor{
public:
    GarlicGoodie(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir = 0, double size = 1.0);
    
    ~GarlicGoodie();
    
    void doSomething();
};

class ExtraLifeGoodie : public Actor{
public:
    ExtraLifeGoodie(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir = 0, double size = 1.0);
    
    ~ExtraLifeGoodie();
    
    void doSomething();
};

class Koopa : public Actor{
public:
    Koopa(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir = 0, double size = 1.0);
    
    ~Koopa();
    
    void doSomething();
    
private:
    int m_freezeCooldown = 0;
    bool m_freeze = false;
};

class Burp : public Actor{
public:
    Burp(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir, double size = 1.0);
    
    ~Burp();
    
    void doSomething();
    
private:
    int m_lifetime = 5;
};

class FireBall : public Actor{
public:
    FireBall(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir, double size = 1.0);
    
    ~FireBall();
    
    void doSomething();
    
private:
    bool m_climbingDown;
    bool m_climbingUp;
};

class Barrel : public Actor{
public:
    Barrel(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir, double size = 1.0);
    
    ~Barrel();
    
    void doSomething();
};

class Kong : public Actor {
public:
    Kong(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir, double size = 1.0);
    
    ~Kong();
    
    void doSomething();
    
private:
    bool m_fleeState = false;
};

#endif // ACTOR_H_

