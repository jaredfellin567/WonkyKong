#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

StudentWorld::StudentWorld(std::string assetPath, Player* player): GameWorld(assetPath), m_player(player){}

StudentWorld::~StudentWorld(){
    cleanUp();
}

int StudentWorld::init()
{
    if(getLevel() > 99){
        return GWSTATUS_PLAYER_WON;
    }
    string curLevel;
    
    if (getLevel() < 10) {
        curLevel += "level0" + std::to_string(getLevel()) + ".txt";  // Manually add leading zero
    } else {
        curLevel += "level" + std::to_string(getLevel()) + ".txt";
    }
    
    Level lev(assetPath());
    
    Level::LoadResult result = lev.loadLevel(curLevel);
    
    if (result == Level::load_fail_bad_format){
    return GWSTATUS_LEVEL_ERROR;
    }
    else if(result == Level::load_fail_file_not_found){
        return GWSTATUS_PLAYER_WON;
    }
    
    for(int r = 0; r < 20; r++){
        for(int c = 0; c < 20; c++){
            Level::MazeEntry me = lev.getContentsOf(c, r);
            switch (me)
            {
                case Level::floor:
                    m_actors.push_back(new Floor(IID_FLOOR, c, r, this, false, 0, 1.0));
                    m_floors.push_back(new Floor(IID_FLOOR, c, r, this, 0, 1.0));
                    break;
                case Level::player:
                    m_player = new Player(IID_PLAYER, c, r, this, false, 0, 1.0);
                    break;
                case Level::empty:
                    break;
                case Level::ladder:
                    m_actors.push_back(new Ladder(IID_LADDER, c, r, this, false, 0, 1.0));
                    m_ladders.push_back(new Ladder(IID_LADDER, c, r, this, false, 0, 1.0));
                    break;
                case Level::bonfire:
                    m_actors.push_back(new Bonfire(IID_BONFIRE, c, r, this, false, 0, 1.0));
                    break;
                case Level::garlic:
                    m_actors.push_back(new GarlicGoodie(IID_GARLIC_GOODIE, c, r, this, false, 0, 1.0));
                    break;
                case Level::extra_life:
                    m_actors.push_back(new ExtraLifeGoodie(IID_GARLIC_GOODIE, c, r, this, false, 0, 1.0));
                    break;
                case Level::koopa:
                    m_actors.push_back(new Koopa(IID_KOOPA, c, r, this, true, 0, 1.0));
                    break;
                case Level::fireball:
                    m_actors.push_back(new FireBall(IID_FIREBALL, c, r, this, true, 0, 1.0));
                    break;
                case Level::left_kong:
                    m_actors.push_back(new Kong(IID_KONG, c, r, this, true, 180, 1.0));
                    break;
                case Level::right_kong:
                    m_actors.push_back(new Kong(IID_KONG, c, r, this, true, 0, 1.0));
                    break;
            }
        }
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you type q
    
    setGameStatText(updateDisplayText());
    
    if(m_player->isDead()){
        return GWSTATUS_PLAYER_DIED;
    }
    m_player->doSomething();
    
    for(Actor* i : m_actors){
        if(!i->isDead()){
            i->doSomething();
        }
    }
    
    if(m_finishedLevel){
        m_finishedLevel = false;
        return GWSTATUS_FINISHED_LEVEL;
    }
    
    for (std::vector<Actor*>::iterator it = m_actors.begin(); it != m_actors.end(); ) {
        if ((*it)->isDead()) {
            delete *it; 
            it = m_actors.erase(it);
        } else {
            ++it;
        }
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    for (Actor* i : m_actors) {
        delete i;
    }
    m_actors.clear();
    
    for (Floor* i : m_floors) {
        delete i;
    }
    m_floors.clear();
    
    for (Ladder* i : m_ladders){
        delete i;
    }
    m_ladders.clear();
    
    if (m_player) {
        delete m_player;
        m_player = nullptr;
    }
}


bool StudentWorld::floorHere(int x, int y){
    for(Floor* i : m_floors){
        if(i->getX() == x && i->getY() == y){
            return true;
        }
    }
    return false;
}

bool StudentWorld::ladderHere(int x, int y){
    for(Ladder* i : m_ladders){
        if(i->getX() == x && i->getY() == y){
            return true;
        }
    }
    return false;
}

bool StudentWorld::playerHere(int x, int y){
    if(m_player->getX() == x && m_player->getY() == y){
        return true;
    }
    return false;
    
}


Player* StudentWorld::getPlayer(){
    return m_player;
}

void StudentWorld::burpKill(int x, int y){
    for(Actor* i : m_actors){
        if(i->isEnemy()){
            if(i->getX() == x && i->getY() == y){
                if(i->dropItem()){
                    if(dynamic_cast<Koopa*>(i)){
                        m_actors.push_back(new ExtraLifeGoodie(IID_EXTRA_LIFE_GOODIE, i->getX(), i->getY(), this, false, 0, 1.0));
                    }
                    else if(dynamic_cast<FireBall*>(i)){
                        m_actors.push_back(new GarlicGoodie(IID_GARLIC_GOODIE, i->getX(), i->getY(), this, false, 0, 1.0));
                    }
                }
                playSound(SOUND_ENEMY_DIE);
                i->kill();
                increaseScore(100);
            }
        }
    }
}

void StudentWorld::createBurp(int x, int y, int dir){
    m_actors.push_back(new Burp(IID_BURP, x, y, this, false, dir, 1.0));
    playSound(SOUND_BURP);
}

void StudentWorld::freezePlayer(){
    m_player->freeze();
}

void StudentWorld::killPlayer(){
    decLives();
    m_player->kill();
    playSound(SOUND_PLAYER_DIE);
}

void StudentWorld::createBarrel(int x, int y, int dir){
    if(dir == 0){
        m_actors.push_back(new Barrel(IID_GARLIC_GOODIE, x + 2, y, this, true, dir, 1.0));
    }
    else{
        m_actors.push_back(new Barrel(IID_GARLIC_GOODIE, x - 2, y, this, true, dir, 1.0));
    }
}

void StudentWorld::destroyBarrel(){
    for(Actor* i : m_actors){
        if(dynamic_cast<Barrel*>(i)){
            i->kill();
            return;
        }
    }
}

bool StudentWorld::barrelHere(int x, int y){
    for(Actor* i : m_actors){
        if(dynamic_cast<Barrel*>(i)){
            if(i->getX() == x && i->getY() == y){
                return true;
            }
        }
    }
    return false;
}

bool StudentWorld::playerClose(int x, int y){
    if(sqrt(pow((m_player->getX() - x), 2) + pow((m_player->getY() - y), 2)) <= 2){
        return true;
    }
    return false;
}

void StudentWorld::finishedLevel(bool x){
    m_finishedLevel = true;
}

std::string StudentWorld::updateDisplayText(){
    
    ostringstream oss;
    
    oss << "  Score: ";
    oss.fill('0');
    oss << setw(7) << getScore() << endl;
    oss.fill('0');
    oss << "  Level: ";
    oss << setw(2) << getLevel() << endl;
    oss.fill('0');
    oss << "  Lives: ";
    oss << setw(2) << getLives() << endl;
    oss.fill('0');
    oss << "  Burps: ";
    oss << setw(2) << m_player->getBurps() << endl;
    
    oss << "                                     " << endl;
    string s = oss.str();
    
    return s;
}

bool StudentWorld::collideWithPlayer(int prevX, int prevY, int x, int y){
    bool passed_x = (prevX <= m_player->getX() && m_player->getX() <= x) || (prevX >= m_player->getX() && m_player->getX() >= x);

    bool passed_y = (prevY <= m_player->getY() && m_player->getY() <= y) || (prevY >= m_player->getY() && m_player->getY() >= y);

    return passed_x && passed_y;
}
void StudentWorld::setPlayerPrevX(int x){
    m_playerPrevX = x;
}

void StudentWorld::setPlayerPrevY(int y){
    m_playerPrevY = y;
}
