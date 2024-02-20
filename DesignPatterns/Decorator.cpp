#include <iostream>
#include <string>

using namespace std;

namespace Structural {
  class Component {
  public:
	virtual ~Component() {}
	virtual string operation() const = 0;
  };

  class ConcreteComponent : public Component {
  public:
	string operation() const override {
	  return "ConcreteComponent";
	}
  };

  class Decorator : public Component {
  protected:
	Component* component_;
  public:
	Decorator(Component* component) : component_(component) {}
	string operation() const override {
	  return component_->operation();
	}
  };

  class ConcreteDecoratorA : public Decorator {
  public:
	ConcreteDecoratorA(Component* component) : Decorator(component) {}
	string operation() const override {
	  return "ConcreteDecoratorA(" + Decorator::operation() + ")";
	}
  };

  class ConcreteDecoratorB : public Decorator {
  public:
	ConcreteDecoratorB(Component* component) : Decorator(component) {}
	string operation() const override {
	  return "ConcreteDecoratorB(" + Decorator::operation() + ")";
	}
  };

  void clientCode(Component* component) {
	cout << "RESULT: " << component->operation();
  }

  extern void testDecorator() {
	Component* simple = new ConcreteComponent;
	cout << "Client: I've got a simple component:\n";
	clientCode(simple);
	cout<< "\n\n";

	Component* decorator1 = new ConcreteDecoratorA(simple);
	Component* decorator2 = new ConcreteDecoratorB(decorator1);
	cout << "Client: Now I've got a decorated component:\n";
	clientCode(decorator2);
	cout << endl;

	delete simple;
	delete decorator1;
	delete decorator2;
  }
}

