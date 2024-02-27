#pragma warning(disable : 4996)

#include <string>
#include <iostream>
#include <vector>

using namespace std;
namespace Behavior {
  class Memento {
  public:
	virtual ~Memento() {}
	virtual string state() const = 0;
	virtual string getName() const = 0;
	virtual string date() const = 0;
  };

  class ConcreteMemento : public Memento {
  private:
	string state_;
	string date_;
  public:
	ConcreteMemento(const string& state) : state_(state) {
	  this->state_ = state;
	  time_t now = time(0);
	  this->date_ = ctime(&now);
	}

	string state() const override {
	  return this->state_;
	}

	string getName() const override {
	  return this->date_ + " / (" + this->state_.substr(0, 9) + "...)";
	}

	string date() const override {
	  return this->date_;
	}
  };

  class Originator {

  private:
	string state_;

	string generateRandomString(int length = 10) {
	  const char alphanum[] = "0123456789" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz";
	  int stringLength = sizeof(alphanum) - 1;
	  string randomString;
	  for (int i = 0; i < length; i++) {
		randomString += alphanum[rand() % stringLength];
	  }
	  return randomString;
	}

  public:
	Originator(string state) : state_(state) {
	  cout << "Originator: My initial state is: " << state_ << endl;
	}

	void doSomething() {
	  cout << "Originator: I'm doing something important." << endl;
	  this->state_ = this->generateRandomString(30);
	  cout << "Originator: and my state has changed to: " << this->state_ << endl;
	}

	Memento* save() {
	  return new ConcreteMemento(this->state_);
	}

	void restore(Memento* memento) {
	  this->state_ = memento->state();
	  cout << "Originator: My state has changed to: " << this->state_ << endl;
	}

  };

  class Caretaker {

  private:
	vector<Memento*> mementos_;
	Originator* originator_;

  public:
	Caretaker(Originator* originator) : originator_(originator) {}

	~Caretaker()
	{
	  for (auto m : mementos_) delete m;
	}

	void backup() {
	  cout << "Caretaker: Saving Originator's state..." << endl;
	  this->mementos_.push_back(this->originator_->save());
	}

	void undo() {
	  if (!this->mementos_.size()) {
		return;
	  }
	  Memento* memento = this->mementos_.back();
	  this->mementos_.pop_back();
	  cout << "Caretaker: Restoring state to: " << memento->getName() << endl;
	  try {
		this->originator_->restore(memento);
	  }
	  catch (...) {
		this->undo();
	  }
	}

	void showHistory() const {
	  cout << "Caretaker: Here's the list of mementos:" << endl;
	  for (Memento* memento : this->mementos_) {
		cout << memento->getName() << endl;
	  }
	}
  };

  void clientCodeMemento() {
	Originator* originator = new Originator("Super-duper-super-puper-super.");
	Caretaker* caretaker = new Caretaker(originator);
	caretaker->backup();
	originator->doSomething();
	caretaker->backup();
	originator->doSomething();
	caretaker->backup();
	originator->doSomething();
	cout << "\n";
	caretaker->showHistory();
	cout << "\nClient: Now, let's rollback!\n\n";
	caretaker->undo();
	cout << "\nClient: Once more!\n\n";
	caretaker->undo();


	delete originator;
	delete caretaker;
  }

  extern void testMemento() {
	srand(static_cast<unsigned int>(time(0)));
	clientCodeMemento();
  }

}