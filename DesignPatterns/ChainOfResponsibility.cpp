#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

namespace Behavior {

  class Handler {
  public:
	virtual Handler* setNext(Handler* handler) = 0;
	virtual string handle(string request) = 0;
  };

  class AbstractHandler : public Handler {
  private:
	Handler* nextHandler_;
  public:
	AbstractHandler() : nextHandler_(nullptr) {}

	Handler* setNext(Handler* handler) override {
	  this->nextHandler_ = handler;
	  return handler;
	}

	string handle(string request) override {
	  if (this->nextHandler_) {
		return this->nextHandler_->handle(request);
	  }
	  return {};
	}
  };

  class MonkeyHandler : public AbstractHandler {
  public:
	string handle(string request) override {
	  if (request == "Banana") {
		return "Monkey: I'll eat the " + request + ".\n";
	  }
	  else {
		return AbstractHandler::handle(request);
	  }
	}
  };

  class SquirrelHandler : public AbstractHandler {
  public:
	string handle(string request) override {
	  if (request == "Nut") {
		return "Squirrel: I'll eat the " + request + ".\n";
	  }
	  else {
		return AbstractHandler::handle(request);
	  }
	}
  };

  class DogHandler : public AbstractHandler {
  public:
	string handle(string request) override {
	  if (request == "MeatBall") {
		return "Dog: I'll eat the " + request + ".\n";
	  }
	  else {
		return AbstractHandler::handle(request);
	  }
	}
  };

  void clientCodeChainOfResponsibility(Handler& handler) {
	vector<string> food = { "Nut", "Banana", "Cup of coffee" };
	for (const string& f : food) {
	  cout << "Client: Who wants a " << f << "?\n";
	  const string result = handler.handle(f);
	  if (!result.empty()) {
		cout << " " << result;
	  }
	  else {
		cout << " " << f << " was left untouched.\n";
	  }
	}
  }

  extern void testChainOfResponsibility() {
	MonkeyHandler* monkey = new MonkeyHandler;
	SquirrelHandler* squirrel = new SquirrelHandler;
	DogHandler* dog = new DogHandler;
	monkey->setNext(squirrel)->setNext(dog);

	cout << "Chain: Monkey > Squirrel > Dog\n\n";
	clientCodeChainOfResponsibility(*monkey);
	cout << "\n";
	cout << "Subchain: Squirrel > Dog\n\n";
	clientCodeChainOfResponsibility(*squirrel);

	delete monkey;
	delete squirrel;
	delete dog;
  }

}