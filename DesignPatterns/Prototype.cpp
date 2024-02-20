#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

namespace Generative {

  enum Type {
	PROTOTYPE_1 = 0,
	RPOTOTYPE_2
  };

  class Prototype {
  protected:
	string prototypeName_{};
	float prototypeField_{};

  public:
	Prototype() {}

	Prototype(string prototypeName) : prototypeName_(prototypeName) {}

	virtual ~Prototype() {}

	virtual Prototype* clone() const = 0;

	virtual void method(float prototypeField) {
	  this->prototypeField_ = prototypeField;
	  cout << "Call method from " << prototypeName_ << " with field " << prototypeField << endl;
	}
  };

  class ConcretePrototype1 : public Prototype {
  private:
	float ConcretePrototypeField1_;
  public:
	ConcretePrototype1(string prototypeName, float ConcretePrototypeField1) : Prototype(prototypeName), ConcretePrototypeField1_(ConcretePrototypeField1) {
	}

	Prototype* clone() const {
	  return new ConcretePrototype1(*this);
	}
  };

  class ConcretePrototype2 : public Prototype {
  private:
	float ConcretePrototypeField2_;
  public:
	ConcretePrototype2(string prototypeName, float ConcretePrototypeField2) : Prototype(prototypeName), ConcretePrototypeField2_(ConcretePrototypeField2) {
	}

	Prototype* clone() const {
	  return new ConcretePrototype2(*this);
	}
  };

  class PrototypeFactory {
  private:
	unordered_map<Type, Prototype*, hash<int>> prototypes_;

  public:
	PrototypeFactory() {
	  prototypes_[Type::PROTOTYPE_1] = new ConcretePrototype1("PROTOTYPE_1", 50.f);
	  prototypes_[Type::RPOTOTYPE_2] = new ConcretePrototype2("PROTOTYPE_2", 60.f);
	}

	~PrototypeFactory() {
	  delete prototypes_[Type::PROTOTYPE_1];
	  delete prototypes_[Type::RPOTOTYPE_2];
	}

	Prototype* createPrototype(Type type) {
	  return prototypes_[type]->clone();
	}
  };

  void client(PrototypeFactory& prototypeFactory) {
	cout << "Let's create a prototype 1" << endl;
	Prototype* prototype = prototypeFactory.createPrototype(Type::PROTOTYPE_1);
	prototype->method(90);
	delete prototype;
	cout << endl;

	cout << "Let's create a prototype 2" << endl;
	prototype = prototypeFactory.createPrototype(Type::RPOTOTYPE_2);
	prototype->method(10);
	delete prototype;
  }

  extern void testPrototype() {
	PrototypeFactory* prototypeFactory = new PrototypeFactory();
	client(*prototypeFactory);
	delete prototypeFactory;
  }

}