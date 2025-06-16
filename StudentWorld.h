#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_
#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <vector>

class Actor;
class Player;
class Floor;
class Ladder;
class Koopa;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  StudentWorld(std::string assetPath, Player* player);
  ~StudentWorld();
  virtual int init();
  virtual int move();
  virtual void cleanUp();
  bool floorHere(int x, int y);
  bool ladderHere(int x, int y);
  bool playerHere(int x, int y);
    bool koopaHere(int x, int y);
  Player* getPlayer();
    Koopa* getKoopaAt(int x, int y);
    void burpKill(int x, int y);
    void createBurp(int x, int y, int dir);
    void freezePlayer();
    void killPlayer();
    void createBarrel(int x, int y, int dir);
    void destroyBarrel();
    bool barrelHere(int x, int y);
    bool playerClose(int x, int y);
    void finishedLevel(bool x);
    bool collideWithPlayer(int prevX, int prevY, int x, int y);
    void setPlayerPrevX(int x);
    void setPlayerPrevY(int x);
    std::string updateDisplayText();

private:
    Player* m_player;
    std::vector<Floor*> m_floors;
    std::vector<Ladder*> m_ladders;
    std::vector<Actor*> m_actors;
    std::vector<Koopa*> m_koopas;
    int m_playerPrevX;
    int m_playerPrevY;
    bool m_finishedLevel;
};

#endif // STUDENTWORLD_H_
