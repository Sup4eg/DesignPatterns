
namespace Generative {
  extern void testFactoryMethod();
  extern void testAbstractFactory();
  extern void testBuilder();
  extern void testPrototype();
  extern void testSingleton();
}

namespace Structural {
  extern void testAdapter();
}

int main() {
  Structural::testAdapter();
  return 0;
}