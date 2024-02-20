
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
}

int main() {
  Structural::testFacade();
  return 0;
}