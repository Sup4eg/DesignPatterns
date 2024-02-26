#include <string>
#include <iostream>

using namespace std;

namespace Generative {

  class Product {

  public:
	virtual ~Product() {}
	virtual string Operation() const = 0;
  };


  class ConcreteProduct1 : public Product {
  public:
	string Operation() const override {
	  return "{Result of the ConcreteProduct1}";
	}
  };

  class ConcreteProduct2 : public Product {
  public:
	string Operation() const override {
	  return "{Result of the ConcreteProduct2}";
	}
  };

  class Creator {

  public:
	virtual ~Creator() {}
	virtual Product* FactoryMethod() const = 0;
	string SomeOperation() const {
	  Product* product = this->FactoryMethod();
	  string result = "Creator: The same creator's code has just worked with "
		+ product->Operation();
	  delete product;
	  return result;
	}
  };

  class ConcreteCreator1 : public Creator {
  public:
	Product* FactoryMethod() const override {
	  return new ConcreteProduct1();
	}
  };

  class ConcreteCreator2 : public Creator {
  public:
	Product* FactoryMethod() const override {
	  return new ConcreteProduct2();
	}
  };

  void ClientCodeFactoryMethod(const Creator& creator) {
	cout << "Client: I'm not aware of the creator's class, but it still works.\n" << creator.SomeOperation() << endl;
  }

  extern void testFactoryMethod() {
	cout << "App: Launched with the ConcreteCreator1.\n";
	ConcreteCreator1* creator = new ConcreteCreator1();
	ClientCodeFactoryMethod(*creator);
  }

}

