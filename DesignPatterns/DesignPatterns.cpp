
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
}

int main() {
  Structural::testDecorator();
  return 0;
}