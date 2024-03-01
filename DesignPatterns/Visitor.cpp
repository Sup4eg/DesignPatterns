#include <iostream>
#include <string>
#include <array>

using namespace std;
namespace Behavioral {
  class ConcreteComponentA;
  class ConcreteComponentB;

  class Visitor {
  public:
	virtual void visitConcreteComponentA(const ConcreteComponentA* element) const = 0;
	virtual void visitConcreteComponentB(const ConcreteComponentB* element) const = 0;
  };

  class Component {
  public:
	virtual ~Component() = default;
	virtual void accept(Visitor* visitor) const = 0;
  };

  class ConcreteComponentA : public Component {
  public:
	void accept(Visitor* visitor) const override {
	  visitor->visitConcreteComponentA(this);
	}
	string exclusiveMethodOfConcreteComponentA() const {
	  return "A";
	}
  };

  class ConcreteComponentB : public Component {
  public:
	void accept(Visitor* visitor) const override {
	  visitor->visitConcreteComponentB(this);
	}
	string specialMethodOfConcreteComponentB() const {
	  return "B";
	}
  };

  class ConcreteVisitor1 : public Visitor {
  public:
	void visitConcreteComponentA(const ConcreteComponentA* element) const override {
	  cout << element->exclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor1\n";
	}
	void visitConcreteComponentB(const ConcreteComponentB* element) const override {
	  cout << element->specialMethodOfConcreteComponentB() << " + ConcreteVisitor1\n";
	}
  };

  class ConcreteVisitor2 : public Visitor {
  public:
	void visitConcreteComponentA(const ConcreteComponentA* element) const override {
	  cout << element->exclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor2\n";
	}
	void visitConcreteComponentB(const ConcreteComponentB* element) const override {
	  cout << element->specialMethodOfConcreteComponentB() << " + ConcreteVisitor2\n";
	}
  };

  void clientCodeVisitor(array<const Component*, 2> components, Visitor* visitor) {
	for (const Component* comp : components) {
	  comp->accept(visitor);
	}
  }

  extern void testVisitor() {
	array<const Component*, 2> components = { new ConcreteComponentA, new ConcreteComponentB };
	cout << "The client code works with all visitors via the base Visitor interface:\n";
	ConcreteVisitor1* visitor1 = new ConcreteVisitor1;
	clientCodeVisitor(components, visitor1);
	cout << "\n";
	cout << "It allows the same client code to work with different types of visitors:\n";
	ConcreteVisitor2* visitor2 = new ConcreteVisitor2;
	clientCodeVisitor(components, visitor2);
	for (const Component* comp : components) {
	  delete comp;
	}
	delete visitor1;
	delete visitor2;
  }
}