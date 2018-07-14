#include "enemy.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Enemy::Enemy(int maxhp, int hp, int att, int def, Posn p, char icon)
	: Character{maxhp, hp, att, def, p, icon}, nearPlayer{false} {}

SubscriptionType Enemy::getSubType() const {
	// cerr << "enemy subtype" << endl;
	return SubscriptionType::Enemy;
}

char Enemy::getType() const {
	return this->getIcon();
}

void Enemy::notify(Subject *whoNotified) {
  this->nearPlayer = true;
}

bool Enemy::isNearPlayer() const {
  return this->nearPlayer;
}

void Enemy::setNearPlayer(bool b) {
  this->nearPlayer = b;
}

bool Enemy::isHostile() const {
  return true;
}

void Enemy::checkEnemyDead(Player *killer) {
  if(this->getHp() == 0) {
    int addedGold = 2;
    if(rand() % 2 == 0){
      addedGold = 1;
    }
    Treasure t{killer->getCurPos(), addedGold, "drop"};
    t.use(*killer);
  }
}

int Enemy::attackedBy(Shade *p) {
  return this->defaultAttack(p);
}

int Enemy::attackedBy(Drow *p) {
  return this->defaultAttack(p);
}

int Enemy::attackedBy(Goblin *p) {
  return this->defaultAttack(p);
}

int Enemy::attackedBy(Vampire *p) {
  p->setHp(p->getHp() + 5); // gain 5 HP every attack
  return this->defaultAttack(p);
}

int Enemy::attackedBy(Troll *p) {
  return this->defaultAttack(p);
}

int Enemy::attackedBy(Ghost *p) {
  return this->defaultAttack(p);
}
