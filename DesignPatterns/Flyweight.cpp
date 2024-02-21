#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

namespace Structural {
  
  struct SharedState {
	string brand_;
	string model_;
	string color_;

	SharedState(const string& brand, const string& model, const string& color) : brand_(brand), model_(model), color_(color) {}

	friend ostream& operator<<(ostream& os, const SharedState& ss) {
	  return os << "[ " << ss.brand_ << " " << ss.model_ << " " << ss.color_ << " ]";
	}

  };

  struct UniqueState {

	string owner_;
	string plates_;

	UniqueState(const string& owner, const string& plates) : owner_(owner), plates_(plates) {}

	friend ostream& operator<<(ostream& os, const UniqueState& us) {
	  return os << "[ " << us.owner_ << " " << us.plates_ << " ]";
	}
  };

  class Flyweight {
  private:
	SharedState* sharedState_;

  public:
	Flyweight(const SharedState* shared_state) : sharedState_(new SharedState(*shared_state)) {}

	Flyweight(const Flyweight& other) : sharedState_(new SharedState(*other.sharedState_)) {}

	~Flyweight() { 
	  delete sharedState_;
	}

	SharedState* sharedState() const {
	  return sharedState_; 
	}

	void operation(const UniqueState& unique_state) const {
	  cout << "Flyweight: Displaying shared (" << *sharedState_ << ") and unique (" << unique_state << ") state." << endl;
	}
  };

  class FlyweightFactory {
  private:
	unordered_map<string, Flyweight> flyweights_;

	string getKey(const SharedState& ss) const {
	  return ss.brand_ + "_" + ss.model_ + "_" + ss.color_;
	}

  public:
	FlyweightFactory(initializer_list<SharedState> sharedStates) {
	  for (const SharedState& ss : sharedStates) {
		this->flyweights_.insert(make_pair(this->getKey(ss), Flyweight(&ss)));
	  }
	}

	Flyweight getFlyweight(const SharedState& sharedState) {
	  string key = this->getKey(sharedState);
	  if (this->flyweights_.find(key) == this->flyweights_.end()) {
		cout << "FlyweightFactory: Can't find a flyweight, creating new one." << endl;
		this->flyweights_.insert(make_pair(key, Flyweight(&sharedState)));
	  }
	  else {
		cout << "FlyweightFactory: Reusing existing flyweight." << endl;
	  }
	  return this->flyweights_.at(key);
	}

	void listFlyweights() const {
	  size_t count = this->flyweights_.size();
	  cout << "FlyweightFactory: I have " << count << " flyweights:" << endl;
	  for (const auto& pair : this->flyweights_) {
		cout << pair.first << endl;
	  }
	}
  };

  void addCarToPoliceDatabase(FlyweightFactory& factory, const string& plates, const string& owner, const string& brand, const string& model, const string& color) {
	cout << "\nClient: Adding a car to database." << endl;
	const Flyweight& flyweight = factory.getFlyweight({ brand, model, color });
	flyweight.operation({owner, plates});
  }
  
  extern void testFlyweight() {
	FlyweightFactory* factory = new FlyweightFactory({
	  {"Chevrolet", "Camaro2018", "pink"},
	  {"Mercedes Benz", "C300", "black"},
	  {"Mercedes Benz", "C500", "red"},
	  {"BMW", "M5", "red"},
	  {"BMW", "X6", "white"}
	  });
	factory->listFlyweights();

	addCarToPoliceDatabase(*factory, "CL234IR", "James Doe", "BMW", "M5", "red");
	addCarToPoliceDatabase(*factory, "CL234IR", "James Doe", "BMW", "X1", "red");

	factory->listFlyweights();
	delete factory;
  }
}