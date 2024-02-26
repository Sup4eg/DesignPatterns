#include <string>
#include <iostream>

using namespace std;
namespace Structural {

  class Target {
  public:
	virtual ~Target() = default;

	virtual std::string request() const {
	  return "Target: The default target's behavior.";
	}
  };

  class Adaptee {
  public:
	std::string specificRequest() const {
	  return ".eetpadA eht fo roivaheb laicepS";
	}
  };

  class Adapter : public Target {
	private:
	  Adaptee* adaptee_;

  public:
	Adapter(Adaptee* adaptee) : adaptee_(adaptee) {}
	string request() const override {
	  string to_reverse = adaptee_->specificRequest();
	  reverse(to_reverse.begin(), to_reverse.end());
	  return "Adapter: (TRANSLATED) " + to_reverse;
	}
  };

  void clientCodeAdapter(const Target* target) {
	cout << target->request();
  }

  extern void testAdapter() {
	cout << "Client: I can work just fine with the Target objects:\n";
	Target* target = new Target;
	clientCodeAdapter(target);
	cout << "\n\n";

	Adaptee* adaptee = new Adaptee;
	cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
	cout << "Adaptee: " << adaptee->specificRequest();
	cout << "\n\n";
	cout << "Client: But I can work with it via the Adapter:\n";
	Adapter* adapter = new Adapter(adaptee);
	clientCodeAdapter(adapter);
	cout << "\n";

	delete target;
	delete adaptee;
	delete adapter;
  }

}