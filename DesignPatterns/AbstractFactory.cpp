#include <string>
#include <iostream>

using namespace std;

namespace Generative {

  class AbstractProductA {
  public:
	virtual ~AbstractProductA() {}
	virtual std::string UsefulFunctionA() const = 0;
  };


  class ConcreteProductA1 : public AbstractProductA {
  public:
	std::string UsefulFunctionA() const override {
	  return "The result of the product A1.";
	}
  };

  class ConcreteProductA2 : public AbstractProductA {
  public:
	std::string UsefulFunctionA() const override {
	  return "The result of the product A2.";
	}
  };

  class AbstractProductB {
  public:
	virtual ~AbstractProductB() {};
	virtual std::string UsefulFunctionB() const = 0;
	virtual std::string AnotherUsefulFunctionB(const AbstractProductA& collaborator) const = 0;
  };

  class ConcreteProductB1 : public AbstractProductB {
  public:
	std::string UsefulFunctionB() const override {
	  return "The result of the product B1.";
	}

	std::string AnotherUsefulFunctionB(const AbstractProductA& collaborator) const override {
	  const std::string result = collaborator.UsefulFunctionA();
	  return "The result of the B1 collaborating with (" + result + ")";
	}
  };

  class ConcreteProductB2 : public AbstractProductB {
  public:
	std::string UsefulFunctionB() const override {
	  return "The result of the product B2.";
	}

	std::string AnotherUsefulFunctionB(const AbstractProductA& collaborator) const override {
	  const std::string result = collaborator.UsefulFunctionA();
	  return "The result of the B2 collaborating with (" + result + ")";
	}
  };

  class AbstractFactory {
  public:
	  virtual AbstractProductA* CreateProductA() const = 0;
	  virtual AbstractProductB* CreateProductB() const = 0;
  };

  class ConcreteFactory1 : public AbstractFactory {
  public:
	AbstractProductA* CreateProductA() const override {
		  return new ConcreteProductA1();
	  }

	AbstractProductB* CreateProductB() const override {
		  return new ConcreteProductB1();
	  }
  };

  class ConcreteFactory2 : public AbstractFactory {
  public:
	AbstractProductA* CreateProductA() const override {
		  return new ConcreteProductA2();
	  }

	AbstractProductB* CreateProductB() const override {
		  return new ConcreteProductB2();
	  }
  };

  void ClientCodeAbstractFactory(const AbstractFactory& factory) {
	  const AbstractProductA* productA = factory.CreateProductA();
	  const AbstractProductB* productB = factory.CreateProductB();
	  cout << productB->UsefulFunctionB() << endl;
	  cout << productB->AnotherUsefulFunctionB(*productA) << endl;
	  delete productA;
	  delete productB;
  }


  extern void testAbstractFactory() {
    cout << "Client: Test client code with the first factory type:\n";
    ConcreteFactory1* f1 = new ConcreteFactory1();
	ClientCodeAbstractFactory(*f1);
	delete f1;
	cout << endl;
	cout << "Client: Test client code with the second factory type:\n";
	ConcreteFactory2* f2 = new ConcreteFactory2();
	ClientCodeAbstractFactory(*f2);
	delete f2;
  }

}
