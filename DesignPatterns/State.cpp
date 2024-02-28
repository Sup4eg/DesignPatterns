#include <iostream>
#include <typeinfo>

using namespace std;
namespace Behavioral {

  class Context;

  class State {
  protected:
	Context* context_;
  public:
	virtual ~State() = default;
	void setContext(Context* context) {
	  this->context_ = context;
	}
	virtual void handle1() = 0;
	virtual void handle2() = 0;
  };

  class Context {
  private:
	State* state_;
  public:
	Context(State* state) : state_(nullptr) {
	  this->transitionTo(state);
	}
	~Context()
	{
	  delete state_;
	}
	void transitionTo(State* state) {
	  cout << "Context: Transition to " << typeid(*state).name() << ".\n";
	  if (this->state_ != nullptr) {
		delete this->state_;
	  }
	  this->state_ = state;
	  this->state_->setContext(this);
	}
	void request1() {
	  this->state_->handle1();
	}
	void request2() {
	  this->state_->handle2();
	}
  };

  class ConcreteStateA : public State {
  public:
	void handle1() override;
	void handle2() override {
	  cout << "ConcreteStateA handles request2.\n";
	}
  };

  class ConcreteStateB : public State {
  public:
	void handle1() override {
	  cout << "ConcreteStateB handles request1.\n";
	}
	void handle2() override {
	  cout << "ConcreteStateB handles request2.\n";
	  cout << "ConcreteStateB wants to change the state of the context.\n";
	  this->context_->transitionTo(new ConcreteStateA);
	}
  };

  void ConcreteStateA::handle1() {
	cout << "ConcreteStateA handles request1.\n";
	cout << "ConcreteStateA wants to change the state of the context.\n";
	this->context_->transitionTo(new ConcreteStateB);
  }

  void clientCodeState() {
	Context* context = new Context(new ConcreteStateA);
	 context->request1();
	 context->request2();
	 delete context;
  }

  extern void testState() {
	clientCodeState();
  }
}

