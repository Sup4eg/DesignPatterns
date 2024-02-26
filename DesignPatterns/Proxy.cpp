#include <iostream>

using namespace std;

namespace Structural {

  class Subject {
  public:
	virtual void request() const = 0;
  };

  class RealSubject : public Subject {
  public: 
	void request() const override {
	  cout << "RealSubject: Handling request.\n";
	}
  };

  class Proxy : public Subject {
  private:
	RealSubject* realSubject_;

	bool checkAccess() const {
	  cout << "Proxy: Checking access prior to firing a real request.\n";
	  return true;
	}

	bool logAccess() const {
	  cout << "Proxy: Logging the time of request.\n";
	  return true;
	}

  public:
	Proxy(RealSubject* realSubject) : realSubject_(new RealSubject(*realSubject_)) {
	}

	~Proxy() {
	  delete realSubject_;
	}

	void request() const override {
	  if (this->checkAccess()) {
		this->realSubject_->request();
		this->logAccess();
	  }
	}
  };

  void clientCodeProxy(const Subject& subject) {
	subject.request();
  }

  extern void testProxy() {
	cout << "Client: Executing the client code with a real subject:\n";
	RealSubject* realSubject = new RealSubject;
	clientCodeProxy(*realSubject);

	cout << "\n";
	cout << "Client: Executing the same client code with a proxy:\n";
	Proxy* proxy = new Proxy(realSubject);
	clientCodeProxy(*proxy);

	delete realSubject;
	delete proxy;
  }

}