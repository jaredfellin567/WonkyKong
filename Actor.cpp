#include "Actor.h"
#include "StudentWorld.h"
using namespace std;
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

Actor::Actor(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir, double size): GraphObject(imageID, startX, startY, dir, size), m_world(world), m_enemyStatus(enemy), isAlive(true){}

Actor::~Actor() {

}

bool Actor::isDead(){
    return !isAlive;
}

void Actor::kill(){
    isAlive = false;
}


int Actor::getTickCount(){
    return m_tickCounter;
}

void Actor::incTickCount(){
    m_tickCounter++;
}

void Actor::setTickCount(int x){
    m_tickCounter = x;
}

StudentWorld* Actor::getWorld(){
    return m_world;
}

bool Actor::isEnemy(){
    return m_enemyStatus;
}

bool Actor::dropItem(){
    if(randInt(1, 3) == 1){
        return true;
    }
    return false;
}

//Floor implementations

Floor::Floor(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir, double size): Actor(IID_FLOOR, startX, startY, world, false, dir, size){}

Floor::~Floor() {

}

void Floor::doSomething() {
}

//Player implementations
Player::Player(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir, double size): Actor(IID_PLAYER, startX, startY, world, false, dir, size){}

Player::~Player() {
}

void Player::incBurps(){
    m_burps += 5;
}

void Player::decBurps(){
    m_burps--;
}

int Player::getBurps(){
    return m_burps;
}

bool Player::isFrozen(){
    return m_freeze;
}

void Player::freeze(){
    m_freeze = true;
    m_freezeCount = 50;
}

void Player::doSomething(){
    if(isDead()){
        return;
    }
    
    if(isFrozen() && m_freezeCount > 0){
        m_freezeCount--;
        return;
    }
    
    if(m_freezeCount == 0){
        m_freeze = false;
    }
    
    if(m_jumpPattern > 0){
        if(getWorld()->ladderHere(getX(), getY())){
            m_jumpPattern = 0;
            return;
        }
        switch (m_jumpPattern){
            case 1:
                if(getDirection() == right){
                    if(!getWorld()->floorHere(getX() + 1, getY())){
                        moveTo(getX() + 1, getY());
                        m_jumpPattern++;
                    }
                    else{
                        m_jumpPattern = 0;
                    }
                }
                else{
                    if(!getWorld()->floorHere(getX() - 1, getY())){
                        moveTo(getX() - 1, getY());
                        m_jumpPattern++;
                    }
                    else{
                        m_jumpPattern = 0;
                    }
                }
            break;
        case 2:
                if(getDirection() == right){
                    if(!getWorld()->floorHere(getX() + 1, getY())){
                        moveTo(getX() + 1, getY());
                        m_jumpPattern++;
                    }
                    else{
                        m_jumpPattern = 0;
                    }
                }
                else{
                    if(!getWorld()->floorHere(getX() - 1, getY())){
                        moveTo(getX() - 1, getY());
                        m_jumpPattern++;
                    }
                    else{
                        m_jumpPattern = 0;
                    }
                }
            break;
        case 3:
            if(getDirection() == right){
                if(!getWorld()->floorHere(getX() + 1, getY())){
                    moveTo(getX() + 1, getY());
                    m_jumpPattern++;
                }
                else{
                    m_jumpPattern = 0;
                }
            }
            else{
                if(!getWorld()->floorHere(getX() - 1, getY())){
                    moveTo(getX() - 1, getY());
                    m_jumpPattern++;
                }
                else{
                    m_jumpPattern = 0;
                }
            }
            break;
        case 4:
            if(!getWorld()->floorHere(getX(), getY() - 1)){
                moveTo(getX(), getY() - 1);
            }
            m_jumpPattern = 0;
            break;
        }
        return;
    }
    
    if(!getWorld()->floorHere(getX(), getY() - 1) && !getWorld()->ladderHere(getX(), getY() - 1) && !getWorld()->ladderHere(getX(), getY())){
        moveTo(getX(), getY() - 1);
        return;
    }

    int input;
    if(getWorld()->getKey(input)){
        switch(input){
        case KEY_PRESS_RIGHT:
            if(getDirection() != right){
                setDirection(right);
            }
            else if(!getWorld()->floorHere(getX() + 1, getY())){
                getWorld()->setPlayerPrevX(getX());
                moveTo(getX() + 1, getY());
            }
                break;
        case KEY_PRESS_LEFT:
            if(getDirection() != left){
                setDirection(left);
            }
            else if(!getWorld()->floorHere(getX() - 1, getY())){
                getWorld()->setPlayerPrevX(getX());
                moveTo(getX() - 1, getY());
            }
            break;
        case KEY_PRESS_UP:
                if(getWorld()->ladderHere(getX(), getY()) && !getWorld()->floorHere(getX(), getY() + 1)){
                    moveTo(getX(), getY() + 1);
                }
                
            break;
        case KEY_PRESS_DOWN:
                if(getWorld()->ladderHere(getX(), getY() - 1) || !getWorld()->floorHere(getX(), getY() - 1)){
                    moveTo(getX(), getY() - 1);
                }
            break;
        case KEY_PRESS_SPACE:
                getWorld()->playSound(SOUND_JUMP);
                if(!getWorld()->floorHere(getX(), getY() + 1)){
                    moveTo(getX(), getY() + 1);
                    m_jumpPattern++;
                }
                break;
        case KEY_PRESS_TAB:
                if(m_burps > 0){
                    m_burps--;
                    if(getDirection() == right){
                        getWorld()->createBurp(getX() + 1, getY(), 0);
                    }
                    else{
                        getWorld()->createBurp(getX() - 1, getY(), 180);
                    }
                }
                break;
        default:
            break;
    }
}
}

//Ladder Implementations

Ladder::Ladder(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir, double size): Actor(IID_LADDER, startX, startY, world, false, dir, size){}

Ladder::~Ladder(){
    
}

void Ladder::doSomething(){
    
}

//Bonfire Implementations

Bonfire::Bonfire(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir, double size): Actor(IID_BONFIRE, startX, startY, world, false, dir, size){}

Bonfire::~Bonfire(){
    
}

void Bonfire::doSomething(){
    increaseAnimationNumber();
    if(getWorld()->playerHere(getX(), getY())){
        getWorld()->killPlayer();
    }
    if(getWorld()->barrelHere(getX(), getY())){
        getWorld()->destroyBarrel();
    }
}

//GarlicGoodie Implementation

GarlicGoodie::GarlicGoodie(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir, double size): Actor(IID_GARLIC_GOODIE, startX, startY, world, false, dir, size){}

GarlicGoodie::~GarlicGoodie(){
    
}

void GarlicGoodie::doSomething(){
    if(getWorld()->playerHere(getX(), getY())){
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->getPlayer()->incBurps();
        getWorld()->increaseScore(25);
        kill();
    }
}

//ExtraLifeGoodie Implementation

ExtraLifeGoodie::ExtraLifeGoodie(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir, double size): Actor(IID_EXTRA_LIFE_GOODIE, startX, startY, world, false, dir, size){}

ExtraLifeGoodie::~ExtraLifeGoodie(){
    
}

void ExtraLifeGoodie::doSomething(){
    
    if(isDead()){
        return;
    }
    
    if(getWorld()->playerHere(getX(), getY())){
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->incLives();
        getWorld()->increaseScore(50);
        kill();
    }
}

//Koopa Implementation

Koopa::Koopa(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir, double size): Actor(IID_KOOPA, startX, startY, world, true, dir, size) {}

Koopa::~Koopa(){
    
}

void Koopa::doSomething(){
    
    
    if(isDead()){
        return;
    }
    
    incTickCount();
    
    if(m_freezeCooldown > 0){
        m_freezeCooldown--;
    }
    
    if(m_freezeCooldown == 0){
        if(getWorld()->playerHere(getX(), getY())){
            getWorld()->freezePlayer();
            m_freezeCooldown = 50;
        }
    }
    
    if(getTickCount() >= 10){
        setTickCount(0);
        if(getDirection() == right){
            if(!getWorld()->floorHere(getX() + 1, getY()) && (getWorld()->floorHere(getX() + 1, getY() - 1) || getWorld()->ladderHere(getX() + 1, getY() - 1))){
                if(m_freezeCooldown == 0 && getWorld()->collideWithPlayer(getX(), getY(), getX() + 1, getY())){
                    getWorld()->freezePlayer();
                    m_freezeCooldown = 50;
                }
                moveTo(getX() + 1, getY());
            }
            else{
                setDirection(left);
            }
        }
        else{
            if(!getWorld()->floorHere(getX() - 1, getY()) && (getWorld()->floorHere(getX() - 1, getY() - 1) || getWorld()->ladderHere(getX() - 1, getY() - 1))){
                if(m_freezeCooldown == 0 && getWorld()->collideWithPlayer(getX(), getY(), getX() - 1, getY())){
                    getWorld()->freezePlayer();
                    m_freezeCooldown = 50;
                }
                moveTo(getX() - 1, getY());
            }
            else{
                setDirection(right);
            }
        }
    }
}

//Burp implementaion

Burp::Burp(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir, double size): Actor(IID_BURP, startX, startY, world, false, dir, size){}

Burp::~Burp(){}

void Burp::doSomething(){
    if(isDead()){
        return;
    }
    
    if(m_lifetime == 0){
        kill();
        return;
    }
    
    m_lifetime--;
    getWorld()->burpKill(getX(), getY());
}

//Fireball Implementation

FireBall::FireBall(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir, double size): Actor(IID_FIREBALL, startX, startY, world, true, dir, size){}

FireBall::~FireBall(){}

void FireBall::doSomething(){
    if(isDead()){
        return;
    }
    
    if(getWorld()->playerHere(getX(), getY())){
        getWorld()->killPlayer();
        return;
    }
    
    incTickCount();
    
    if(getTickCount() >= 10){
    if(getWorld()->ladderHere(getX(), getY()) && !m_climbingDown){
            int x = randInt(1, 3);
            if(x == 1 || m_climbingUp){
                if(getWorld()->collideWithPlayer(getX(), getY(), getX(), getY() + 1)){
                    getWorld()->killPlayer();
                }
                moveTo(getX(), getY() + 1);
                m_climbingUp = true;
                setTickCount(0);
                return;
            }
    }
    else if(getWorld()->ladderHere(getX(), getY() - 1) && !m_climbingUp){
            int x = randInt(1, 3);
            if(!m_climbingUp && (x == 1 || m_climbingDown)){
                if(getWorld()->collideWithPlayer(getX(), getY(), getX(), getY() - 1)){
                    getWorld()->killPlayer();
                }
                moveTo(getX(), getY() - 1);
                m_climbingDown = true;
                setTickCount(0);
                return;
            }
    }
    else
    {
        m_climbingDown = false;
        m_climbingUp = false;
    }
        setTickCount(0);
        if(getDirection() == right){
            if(!getWorld()->floorHere(getX() + 1, getY()) && (getWorld()->floorHere(getX() + 1, getY() - 1) || getWorld()->ladderHere(getX() + 1, getY() - 1))){
                if(getWorld()->collideWithPlayer(getX(), getY(), getX() + 1, getY())){
                    getWorld()->killPlayer();
                }
                moveTo(getX() + 1, getY());
            }
            else{
                setDirection(left);
            }
        }
        else{
            if(!getWorld()->floorHere(getX() - 1, getY()) && (getWorld()->floorHere(getX() - 1, getY() - 1) || getWorld()->ladderHere(getX() - 1, getY() - 1))){
                if(getWorld()->collideWithPlayer(getX(), getY(), getX() - 1, getY())){
                    getWorld()->killPlayer();
                }
                moveTo(getX() - 1, getY());
            }
            else{
                setDirection(right);
            }
        }
    }
}

//Barrel Implementation

Barrel::Barrel(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir, double size): Actor(IID_BARREL, startX, startY, world, true, dir, size){}

Barrel::~Barrel(){}

void Barrel::doSomething(){
    
    if(isDead()){
        return;
    }
    
    incTickCount();
    
    if(getWorld()->playerHere(getX(), getY())){
        getWorld()->killPlayer();
        return;
    }
    
    if(!getWorld()->floorHere(getX(), getY() - 1)){
        moveTo(getX(), getY() - 1);
        setTickCount(0);
        if(getWorld()->floorHere(getX(), getY() - 1)){
            if(getDirection() == right){
                setDirection(left);
            }
            else{
                setDirection(right);
            }
        }
    }
    
    
    
    if(getTickCount() >= 10){
        setTickCount(0);
        if(getDirection() == right){
            if(!getWorld()->floorHere(getX() + 1, getY())){
                if(getWorld()->collideWithPlayer(getX(), getY(), getX() + 1, getY())){
                    getWorld()->killPlayer();
                }
                moveTo(getX() + 1, getY());
            }
            else{
                setDirection(left);
            }
        }
        else{
            if(!getWorld()->floorHere(getX() - 1, getY())){
                if(getWorld()->collideWithPlayer(getX(), getY(), getX() - 1, getY())){
                    getWorld()->killPlayer();
                }
                moveTo(getX() - 1, getY());
            }
            else{
                setDirection(right);
            }
        }
    }
}

//Kong Implementations

Kong::Kong(int imageID, int startX, int startY, StudentWorld* world, bool enemy, int dir, double size): Actor(IID_KONG, startX, startY, world, false, dir, size){}

Kong::~Kong(){}

void Kong::doSomething(){
    if(isDead()){
        return;
    }
    
    increaseAnimationNumber();
    incTickCount();
    
    if(getTickCount() == max(200 - 50 * getWorld()->getLevel(), 50) && !m_fleeState){
        setTickCount(0);
        getWorld()->createBarrel(getX(), getY(), getDirection());
    }
    
    if(getWorld()->playerClose(getX(), getY())){
        m_fleeState = true;
    }
    
    if(m_fleeState){
        if(getTickCount() >= 5){
            setTickCount(0);
            if(getY() != 20){
                moveTo(getX(), getY() + 1);
            }
            else{
                getWorld()->playSound(SOUND_FINISHED_LEVEL);
                getWorld()->finishedLevel(true);
                getWorld()->increaseScore(1000);
            }
        }
    }
    
}
