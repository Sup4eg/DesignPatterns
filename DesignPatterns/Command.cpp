#include <iostream>

using namespace std;
namespace Behavior {
  class Command {
  public:
	virtual ~Command() {}
	virtual void execute() const = 0;
  };

  class SimpleCommmand : public Command {
  private:
	string payload_;
  public:
	explicit SimpleCommmand(string const& payload) : payload_(payload) {}
	void execute() const override {
	  cout << "SimpleCommand: See, I can do simple things like printing (" << payload_ << ")\n";
	}
  };

  class Receiver {
  public:
	void doSomething(string const& a) {
	  cout << "Receiver: Working on (" << a << ")\n";
	}

	void doSomethingElse(string const& b) {
	  cout << "Receiver: Also working on (" << b << ")\n";
	}
  };

  class ComplexCommand : public Command {
  private:
	Receiver* receiver_;
	string a_;
	string b_;
  public:
	ComplexCommand(Receiver* receiver, string const& a, string const& b) : receiver_(receiver), a_(a), b_(b) {}
	void execute() const override {
	  cout << "ComplexCommand: Complex stuff should be done by a receiver object\n";
	  receiver_->doSomething(a_);
	  receiver_->doSomethingElse(b_);
	}
  };

  class Invoker {
  private:
	Command* onStart_;
	Command* onFinish_;

  public:
	~Invoker() {
	  delete onStart_;
	  delete onFinish_;
	}

	void setOnStart(Command* command) {
	  onStart_ = command;
	}

	void setOnFinish(Command* command) {
	  onFinish_ = command;
	}

	void doSomethingImportant() {
	  cout << "Invoker: Does anybody want something done before I begin?\n";
	  if (this->onStart_) {
		this->onStart_->execute();
	  }
	  cout << "Invoker: ...doing something really important...\n";
	  cout << "Invoker: Does anybody want something done after I finish?\n";
	  if (this->onFinish_) {
		this->onFinish_->execute();
	  }
	}
  };

  extern void testCommand() {
	Invoker* invoker = new Invoker;
	invoker->setOnStart(new SimpleCommmand("Say Hi!"));
	Receiver* receiver = new Receiver;
	invoker->setOnFinish(new ComplexCommand(receiver, "Send email", "Save report"));
	invoker->doSomethingImportant();

	delete invoker;
	delete receiver;
  }

};
