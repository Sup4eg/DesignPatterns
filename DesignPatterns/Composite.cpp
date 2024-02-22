#include <algorithm>
#include <iostream>
#include <list>
#include <string>

using namespace std;

namespace Structural {

  class Component {
  protected:
	Component* parent_;
  public:
	virtual ~Component() {}
	void setParent(Component* parent) {
	  this->parent_ = parent;
	}
	Component* getParent() const {
	  return this->parent_;
	}
	virtual void add(Component* component) {}
	virtual void remove(Component* component) {}
	virtual bool isComposite() const {
	  return false;
	}
	virtual string operation() const = 0;
  };

  class Leaf : public Component {
  public:
	string operation() const override {
	  return "Leaf";
	}
  };

  class Composite : public Component {
  protected:
	list<Component*> children_;
  
  public:
	void add(Component* component) override {
	  this->children_.push_back(component);
	  component->setParent(this);
	}

	void remove(Component* component) override {
	  children_.remove(component);
	  component->setParent(nullptr);
	}

	bool isComposite() const override {
	  return true;
	}

	string operation() const override {
	  string result;
	  for (const Component* c : children_) {
		if (c == children_.back()) {
		  result += c->operation();
		}
		else {
		  result += c->operation() + "+";
		}
	  }
	  return "Branch(" + result + ")";
	}
  };

  void clientCode1(Component* component) {
	cout << "RESULT: " << component->operation();
  }

  void clientCode2(Component* component1, Component* component2) {
	if (component1->isComposite()) {
	  component1->add(component2);
	}
	cout << "RESULT: " << component1->operation();
  }

  extern void testComposite() {

	//simple component

	Component* simple = new Leaf;
	cout << "Client: I've got a simple component:\n";
	clientCode1(simple);
	cout << "\n\n";

	//hard component

	Component* tree = new Composite;
	Component* branch1 = new Composite;

	Component* leaf1 = new Leaf;
	Component* leaf2 = new Leaf;
	Component* leaf3 = new Leaf;
	branch1->add(leaf1);
	branch1->add(leaf2);
	Component* branch2 = new Composite;
	branch2->add(leaf3);
	tree->add(branch1);
	tree->add(branch2);
	cout << "Client: Now I've got a composite tree:\n";
	clientCode1(tree);
	cout << "\n\n";

	cout << "Client: I don't need to check the components classes even when managing the tree:\n";
	clientCode2(tree, simple);
  	cout << "\n";

	delete simple;
	delete tree;
	delete branch1;
	delete branch2;
	delete leaf1;
	delete leaf2;
	delete leaf3;
  }

}