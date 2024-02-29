#include <string_view>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
namespace Behavioral {
  class Strategy {
  public:
	virtual ~Strategy() = default;
	virtual string doAlgorithm(string_view data) const = 0;
  };

  class Context {
  private:
	unique_ptr<Strategy> strategy_;
  public:
	explicit Context(unique_ptr<Strategy>&& strategy = nullptr) : strategy_(move(strategy)) {}
	void setStrategy(unique_ptr<Strategy>&& strategy) {
	  strategy_ = move(strategy);
	}
	void doSomeBusinessLogic() const {
	  if (strategy_) {
		cout << "Context: Sorting data using the strategy (not sure how it'll do it)\n";
		string result = strategy_->doAlgorithm("aecbd");
		cout << result << "\n";
	  }
	  else {
		cout << "Context: Strategy is not set.\n";
	  }
	}
  };

  class ConcreteStrategyA : public Strategy {
  public:
	string doAlgorithm(string_view data) const override {
	  string result(data);
	  sort(result.begin(), result.end());
	  return result;
	}
  };

  class ConcreteStrategyB : public Strategy {
	string doAlgorithm(string_view data) const override {
	  string result(data);
	  sort(result.begin(), result.end(), greater<>());
	  return result;
	}
  };

  void clientCodeStrategy() {
	Context context (make_unique<ConcreteStrategyA>());
	cout << "Client: Strategy is set to normal sorting.\n";
	context.doSomeBusinessLogic();
	cout << "\n";
	cout << "Client: Strategy is set to reverse sorting.\n";
	context.setStrategy(make_unique<ConcreteStrategyB>());
	context.doSomeBusinessLogic();
  }

  extern void testStrategy() {
	clientCodeStrategy();
  }
}