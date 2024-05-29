class Particle {
private:
  int frameLeft_ = 0;
  double x_ = 0.f, y_ = 0.f;
  double xVel_ = 0.f, yVel_ = 0.f;

public:
  Particle() : frameLeft_(0) {}

  void init(double x, double y, double xVel, double yVel, int lifetime) {
	x_ = x;
	y_ = y;
	xVel_ = xVel;
	yVel_ = yVel;
	frameLeft_ = lifetime;
  }

  void animate() {
	if (!inUse()) return;

	frameLeft_--;
	x_ += xVel_;
	y_ += yVel_;
  }

  bool inUse() const { return frameLeft_ > 0; }
};


class ParticlePool {
private:
  static const int POOL_SIZE = 100;
  Particle particles_[POOL_SIZE];

public:
  void create(double x, double y, double xVel, double yVel, int lifetime);

  void animate() {
	for (int i = 0; i < POOL_SIZE; ++i) {
	  particles_[i].animate();
	}
  }
};

void ParticlePool::create(double x, double y, double xVel, double yVel, int lifetime) {
  for (int i = 0; i < POOL_SIZE; ++i) {
	if (!particles_[i].inUse()) {
	  particles_[i].init(x, y, xVel, yVel, lifetime);
	  return;
	}
  }
}