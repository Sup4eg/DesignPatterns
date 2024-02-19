#include <vector>
#include <string>
#include <iostream>

using namespace std;

namespace Generative {

  class Product1 {
  public:
	vector<string> parts_;

	void listParts() const {
	  cout << "Product parts: ";
	  for (size_t i = 0; i < parts_.size(); i++) {
		if (parts_[i] == parts_.back()) {
		  cout << parts_[i];
		}
		else {
		  cout << parts_[i] << ", ";
		}
	  }
	  cout << "\n\n";
	}
  };

  class Builder {

  public:
	virtual ~Builder() {}
	virtual void producePartA() const = 0;
	virtual void producePartB() const = 0;
	virtual void producePartC() const = 0;

  };

  class ConcreteBuilder1 : public Builder {

  private:
	Product1* product;

  public:
	ConcreteBuilder1() {
	  this->reset();
	}

	~ConcreteBuilder1() {
	  delete product;
	}

	void reset() {
	  this->product = new Product1();
	}

	void producePartA() const override {
	  this->product->parts_.push_back("PartA1");
	}

	void producePartB() const override {
	  this->product->parts_.push_back("PartB1");
	}

	void producePartC() const override {
	  this->product->parts_.push_back("PartC1");
	}

	Product1* getProduct() {
	  Product1* result = this->product;
	  this->reset();
	  return result;
	}
  };

  class Director {

  private:
	Builder* builder;

  public:
	void setBuilder(Builder* builder) {
	  this->builder = builder;
	}

	void buildMinimalViableProduct() {
	  this->builder->producePartA();
	}

	void buildFullFeaturedProduct() {
	  this->builder->producePartA();
	  this->builder->producePartB();
	  this->builder->producePartC();
	}
  };

  void clientCode(Director& director) {
	ConcreteBuilder1* builder = new ConcreteBuilder1();
	director.setBuilder(builder);
	cout << "Standard basic product:\n";
	director.buildMinimalViableProduct();

	Product1* p = builder->getProduct();
	p->listParts();
	delete p;

	cout << "Standard full featured product:\n";
	director.buildFullFeaturedProduct();


	p = builder->getProduct();
	p->listParts();
	delete p;

	cout << "Custom product:\n";
	builder->producePartA();
	builder->producePartC();
	p = builder->getProduct();
	p->listParts();
	delete p;

	delete builder;
  }


  extern void testBuilder() {
	Director* director = new Director();
	clientCode(*director);
	delete director;
  }

}