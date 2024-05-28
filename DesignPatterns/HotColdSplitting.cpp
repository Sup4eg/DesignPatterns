class Vector {};
class LootType {};

class Animation;
class LootDrop;

class AIComponent {
public:
  void update() {}

private:
  Animation* animation_;
  double energy_;
  Vector goalPos_;

  //rarer eventualities
  LootDrop* loot_;
};

class LootDrop {
  
  friend class AIComponent;
  
  LootType drop_;
  int minDrops_;
  int maxDrops_;
  double chanceOfDrop_;
};