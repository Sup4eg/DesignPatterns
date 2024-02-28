#include <iostream>
#include <list>
#include <string>

using namespace std;
namespace Behavioral {

  class IObserver {
  public:
	virtual void update(const string& messageFromSubject) = 0;
	virtual ~IObserver() = default;
  };

  class ISubject {
  public:
	virtual void attach(IObserver* observer) = 0;
	virtual void detach(IObserver* observer) = 0;
	virtual void notify() = 0;
	virtual ~ISubject() = default;
  };


  class Subject : public ISubject {
  private:
	list<IObserver*> listObservers_;
	string message_;
  public:
	virtual ~Subject() {
	  cout << "Goodbye, I was the Subject." << endl;
	}
	virtual void attach(IObserver* observer) override {
	  listObservers_.push_back(observer);
	}
	virtual void detach(IObserver* observer) override {
	  listObservers_.remove(observer);
	}
	virtual void notify() override {
	  list<IObserver*>::iterator iterator = listObservers_.begin();
	  howManyObserver();
	  while (iterator != listObservers_.end()) {
		(*iterator)->update(message_);
		++iterator;
	  }
	}
	void createMessage(string message = "Empty") {
	  this->message_ = message;
	  notify();
	}
	void howManyObserver() {
	  cout << "There are " << listObservers_.size() << " observers in the list." << endl;
	}
	void someBusinessLogic() {
	  this->message_ = "change message message";
	  notify();
	  cout << "I'm about to do some thing important" << endl;
	}
  };

  class Observer : public IObserver {
  private:
	string messageFromSubject_;
	Subject& subject_;
	static int staticNumber_;
	int number_;

  public:
	Observer(Subject& subject) : subject_(subject) {
	  this->subject_.attach(this);
	  cout << "Hi, I'm the Observer \"" << ++Observer::staticNumber_ << "\"." << endl;
	  this->number_ = Observer::staticNumber_;
	}
	virtual ~Observer() {
	  cout << "Goodbye, I was the Observer \"" << this->number_ << "\"." << endl;
	}
	virtual void update(const string& messageFromSubject) override {
	  messageFromSubject_ = messageFromSubject;
	  printInfo();
	}
	void removeMeFromTheList() {
	  subject_.detach(this);
	  cout << "Observer \"" << number_ << "\" removed from the list." << endl;
	}
	void printInfo() {
	  cout << "Observer \"" << this->number_ << "\": a new message is available --> " << this->messageFromSubject_ << endl;
	}
  };

  int Observer::staticNumber_ = 0;

  void clientCodeObserver() {
	Subject* subject = new Subject;
	Observer* observer1 = new Observer(*subject);
	Observer* observer2 = new Observer(*subject);
	Observer* observer3 = new Observer(*subject);
	Observer* observer4;
	Observer* observer5;

	subject->createMessage("Hello World! :D");
	observer3->removeMeFromTheList();

	subject->createMessage("The weather is hot today! :p");
	observer4 = new Observer(*subject);

	observer2->removeMeFromTheList();
	observer5 = new Observer(*subject);

	subject->createMessage("My new car is great! ;)");
	observer5->removeMeFromTheList();

	observer4->removeMeFromTheList();
	observer1->removeMeFromTheList();

	delete observer5;
	delete observer4;
	delete observer3;
	delete observer2;
	delete observer1;
	delete subject;
  }

  extern void testObserver() {
	clientCodeObserver();
  }

}
