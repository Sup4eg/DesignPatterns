
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

namespace Behavioral {
  extern void testChainOfResponsibility();
}

int main() {
  Behavioral::testChainOfResponsibility();
  return 0;
}