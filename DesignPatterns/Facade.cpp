#include <string>
#include <iostream>

using namespace std;

namespace Structural {
  
  class Subsystem1 {
  public: 
	string operation1() const {
	  return "Subsystem1: Ready!\n";
	}

	string operationN() const {
	  return "Subsystem1: Go!\n";
	}
  };

  class Subsystem2 {
  public:
	string operation1() const {
	  return "Subsystem2: Get ready!\n";
	}
	
	string operationZ() const {
	  return "Subsystem2: Fire!\n";
	}
  };

  class Facade {
  private:
	Subsystem1* subsystem1_;
	Subsystem2* subsystem2_;

  public:
	Facade(Subsystem1* subsystem1 = nullptr, Subsystem2* subsystem2 = nullptr) {
	  subsystem1_ = subsystem1 ? subsystem1 : new Subsystem1;
	  subsystem2_ = subsystem2 ? subsystem2 : new Subsystem2;
	}

	~Facade() {
	  delete subsystem1_;
	  delete subsystem2_;
	}

	string operation() {
	  string result = "Facade initializes subsystems:\n";
	  result += subsystem1_->operation1();
	  result += subsystem2_->operation1();
	  result += "Facade orders subsystems to perform the action:\n";
	  result += subsystem1_->operationN();
	  result += subsystem2_->operationZ();
	  return result;
	}
  };

  void clientCodeFacade(Facade* facade) {
	cout << facade->operation();
  }

  extern void testFacade() {
	Subsystem1* subsystem1 = new Subsystem1;
	Subsystem2* subsystem2 = new Subsystem2;
	Facade* facade = new Facade(subsystem1, subsystem2);
	clientCodeFacade(facade);
	delete facade;
  }

}
