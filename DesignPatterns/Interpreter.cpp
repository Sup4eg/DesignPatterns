#include <iostream>

using namespace std;
namespace GameDev {

  class Expression {
  public:
	virtual ~Expression() {}
	virtual double evaluate() = 0;
  };

  class NumberExpression : public Expression {
  private:
	double value_;

  public:
	NumberExpression(double value) : value_(value) {}

	virtual double evaluate() override {
	  return value_;
	}
  };

  class AdditionExpression : public Expression {
  private:
	Expression* left_;
	Expression* right_;

  public:
	AdditionExpression(Expression* left, Expression* right)
	  : left_(left), right_(right) {}

	virtual double evaluate() override {
	  double left = left_->evaluate();
	  double right = right_->evaluate();
	  return  left + right;
	}
  };

}