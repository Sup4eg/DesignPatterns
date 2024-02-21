
//5
namespace Generative {
  extern void testFactoryMethod();
  extern void testAbstractFactory();
  extern void testBuilder();
  extern void testPrototype();
  extern void testSingleton();
}

namespace Structural {
  extern void testAdapter();
  extern void testDecorator();
  extern void testFacade();
  extern void testProxy();
  extern void testFlyweight();
  extern void testBridge();
}

int main() {
  Structural::testBridge();
  return 0;
}