#include <cassert>

using namespace std;
namespace GameDev {


  enum Instruction {
	INST_SET_HEALTH = 0x00,
	INST_GET_HEALTH = 0x01,
	INST_SET_WISDOM = 0x02,
	INST_GET_WISDOM = 0x03,
	INST_SET_AGILITY = 0x04,
	INST_GET_AGILITY = 0x05,
	INST_PLAY_SOUND = 0x06,
	INST_SPAWN_PARTICLES = 0x07,
	INST_LITERAL = 0x08,
	INST_ADD = 0x09,
	DIVIDE = 0x0A
  };

  namespace API {
	void setHealth(int wizard, int amount) {}
	int getHealth(int wizard) { return 0; }
	void setWisdom(int wizard, int amount) {}
	int getWisdom(int wizard) { return 0; }
	void setAgility(int wizard, int amount) {}
	int  getAgility(int wizard) { return 0; }

	void playSound(int soundId) {}
	void spawnParticles(int particleId) {}
  }

  class VM {
  public:
	VM() : stackSize_(0) {}

	void interpret(char bytecode[], int size) {
	  for (int i = 0; i < size; ++i) {
		char instruction = bytecode[i];
		switch (instruction) {
		case INST_SET_HEALTH:
		  int amount = pop();
		  int wizard = pop();
		  API::setHealth(wizard, amount);
		  break;
		case  INST_GET_HEALTH:
		  int wizard = pop();
		  int health = API::getHealth(wizard);
		  push(health);
		  break;
		case INST_SET_WISDOM:
		  int amount = pop();
		  int wizard = pop();
		  API::setWisdom(wizard, amount);
		  break;
		case INST_GET_WISDOM:
		  int wizard = pop();
		  int wisdom = API::getWisdom(wizard);
		  push(wisdom);
		  break;
		case INST_SET_AGILITY:
		  int amount = pop();
		  int wizard = pop();
		  API::setAgility(wizard, amount);
		  break;
		case INST_GET_AGILITY:
		  int wizard = pop();
		  int agility = API::getAgility(wizard);
		  push(agility);
		  break;
		case INST_PLAY_SOUND:
		  API::playSound(pop());
		  break;
		case INST_SPAWN_PARTICLES:
		  API::spawnParticles(pop());
		  break;
		case INST_LITERAL:
		  int value = bytecode[++i];
		  push(value);
		  break;
		case INST_ADD:
		  int b = pop();
		  int a = pop();
		  push(a + b);
		  break;
		}
	  }
	}

  private:
	static const int MAX_STACK = 128;
	int stackSize_ = 0;
	int stack_[MAX_STACK]{};

  private:
	void push(int value) {
	  assert(stackSize_ < MAX_STACK);
	  stack_[stackSize_++] = value;
	}

	int pop() {
	  assert(stackSize_ > 0);
	  return stack_[--stackSize_];
	}
  };

}