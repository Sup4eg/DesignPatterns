
//5
namespace Generative {
  extern void testFactoryMethod();
  extern void testAbstractFactory();
  extern void testBuilder();
  extern void testPrototype();
  extern void testSingleton();
}

//7
namespace Structural {
  extern void testAdapter();
  extern void testDecorator();
  extern void testFacade();
  extern void testProxy();
  extern void testFlyweight();
  extern void testBridge();
  extern void testComposite();
}

namespace Behavior {
  extern void testChainOfResponsibility();
  extern void testCommand();
  extern void testMediator();
  extern void testIterator();
  extern void testMemento();
}

int main() {
  Behavior::testMemento();
  return 0;
}