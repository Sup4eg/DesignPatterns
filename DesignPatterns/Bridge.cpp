#include <iostream>
#include <string>

using namespace std;

namespace Structural {

  class Implementation {
	public:
	virtual ~Implementation() {}
	virtual string operationImplementation() const = 0;
  };

  class ConcreteImplementationA : public Implementation {
  public:
	string operationImplementation() const override {
	  return "ConcreteImplementationA: Here's the result on the platform A.\n";
	}
  };

  class ConcreteImplementationB : public Implementation {
  public:
	string operationImplementation() const override {
	  return "ConcreteImplementationB: Here's the result on the platform B.\n";
	}
  };

  class Abstraction {
  protected:
	Implementation* implementation_;

  public:
	Abstraction(Implementation* implementation) : implementation_(implementation) {}

	virtual ~Abstraction() {}

	virtual string operation() const {
	  return "Abstraction: Base operation with:\n" + this->implementation_->operationImplementation();
	}
  };

  class ExtendedAbstraction : public Abstraction {
  public:
	  ExtendedAbstraction(Implementation* implementation) : Abstraction(implementation) {}

	  string operation() const override {
		return "ExtendedAbstraction: Extended operation with:\n" + this->implementation_->operationImplementation();
	  }
  };

  void clientCodeBridge(const Abstraction& abstraction) {
	cout << abstraction.operation();
  }

  extern void testBridge() {
	Implementation* implementation = new ConcreteImplementationA;
	Abstraction* abstraction = new Abstraction(implementation);
	clientCodeBridge(*abstraction);
	cout << endl;

	delete implementation;
	delete abstraction;

	implementation = new ConcreteImplementationB;
	abstraction = new ExtendedAbstraction(implementation);
	clientCodeBridge(*abstraction);

	delete implementation;
	delete abstraction;
  }
}