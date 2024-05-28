#include <cassert>

class Particle {
public:
  void update() {}
  bool isActive() { return true; }
};

class ParticleSystem {
private:
  static const int MAX_PARTICLES = 1000;
  int numParticles_ = 0;
  int numActive_ = 0;
  Particle particles_[MAX_PARTICLES]{};
public:
  ParticleSystem() : numParticles_(0) {}
  void update();
  void activateParticle(int index);
  void deactivateParticle(int index);
};

void ParticleSystem::activateParticle(int index) {
  assert(index >= numActive_);

  // Swap it with the first inactive particle
  // right after the active ones.

  Particle temp = particles_[numActive_];
  particles_[numActive_] = particles_[index];
  particles_[index] = temp;

  numActive_++;
}

void ParticleSystem::deactivateParticle(int index) {
  assert(index < numActive_);

  // Swap it with the last active particle.

  numActive_--;

  Particle temp = particles_[numActive_];
  particles_[numActive_] = particles_[index];
  particles_[index] = temp;

}

void ParticleSystem::update() {
  for (int i = 0; i < numActive_; ++i) {
	particles_[i].update();
  }
}
