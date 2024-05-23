class Breed;

class Monster {

  friend class Breed;

private:
  int health_;
  Breed& breed_;
  Monster(Breed& breed);

public:
  const char* getAttack();
};

class Breed {
private:
  int health_;
  const char* attack_;
  Breed* parent_ = nullptr; //parent

public:
  Monster* newMonster();
  Breed(Breed* parent, int health, const char* attack) : health_(health), attack_(attack) {
	if (parent) {
	  if (health == 0) health_ = parent->getHealth();
	  if (!attack) attack_ = parent->getAttack();
	}
  }

  int getHealth() { return health_; }
  const char* getAttack() { return attack_; }
};

Monster::Monster(Breed& breed) : health_(breed.getHealth()), breed_(breed) {}
const char* Monster::getAttack() { return breed_.getAttack(); }
Monster* Breed::newMonster() { return new Monster(*this); }