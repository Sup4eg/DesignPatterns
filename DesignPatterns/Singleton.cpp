#include <mutex>
#include <iostream>

using namespace std;

namespace Generative {
  class Singleton {

  private:
	static Singleton* pinstance_;
	static mutex mutex_;

  protected:
	string value_;
	Singleton(const string value) : value_(value) {}
	~Singleton() {}

  public:
	Singleton(Singleton& other) = delete;
	void operator=(const Singleton&) = delete;
	static Singleton* getInstance(const string& value);

	void someBuisnessLogic() {}
	string value() const { return value_; }

  };

  Singleton* Singleton::pinstance_{nullptr};
  mutex Singleton::mutex_;

  Singleton* Singleton::getInstance(const string& value) {
	lock_guard<mutex> lock(mutex_);
	if (pinstance_ == nullptr) {
	  pinstance_ = new Singleton(value);
	}
	return pinstance_;
  }

  void threadFoo() {
	this_thread::sleep_for(chrono::milliseconds(1000));
	Singleton* singleton = Singleton::getInstance("Foo");
	cout << singleton->value() << endl;
  }

  void threadBar() {
	this_thread::sleep_for(chrono::milliseconds(1000));
	Singleton* singleton = Singleton::getInstance("Bar");
	cout << singleton->value() << endl;
  }

  extern void testSingleton() {
	cout << "If you see the same value, then singleton was reused (yay!)" << endl;
	cout << "If you see different values, then 2 singletons were created (booo!!)" << endl;
	thread t1(threadFoo);
	thread t2(threadBar);
	t1.join();
	t2.join();
  }
}