#define DIR_LEFT 0
#define DIR_RIGHT 1

class Volume {};

class Sprite {};

class World {
public:
  void resolveCollision(Volume& volume, int& x, int& y, int& velocity) {}
};

class Graphics {
public:
  void draw(Sprite& sprite, int x, int y) {}
};

class Controller {
public:
  static int getJoystickDirection() { return 0; }
};

class GameObject;

class InputComponent {
private:
  static const int WALK_ACCELERATION = 1;
public:
  virtual ~InputComponent() {}
  virtual void update(GameObject& obj) = 0;
};

class PhysicsComponent {
public:
  virtual ~PhysicsComponent() {}
  virtual void update(GameObject& obj, World& world) = 0;
};

class GraphicsComponent {
public:
  virtual ~GraphicsComponent() {}
  virtual void update(GameObject& obj, Graphics& graphics) = 0;
};

class GameObject {
private:
  InputComponent* input_;
  GraphicsComponent* graphics_;
  PhysicsComponent* physics_;

public:

  int velocity = 0;
  int x = 0, y = 0;

  GameObject(InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics) : input_(input), physics_(physics), graphics_(graphics) {}

  void update(World& world, Graphics& graphics) {
	input_->update(*this);
	physics_->update(*this, world);
	graphics_->update(*this, graphics);
  }
};



class PlayerInputComponent : public InputComponent {
private:
  static const int WALK_ACCELERATION = 1;
public:
  virtual void update(GameObject& obj) override {
	switch (Controller::getJoystickDirection()) {
	case DIR_LEFT:
	  obj.velocity -= WALK_ACCELERATION;
	  break;
	case DIR_RIGHT:
	  obj.velocity += WALK_ACCELERATION;
	  break;
	}
  }
};


class DemoInputComponent : public InputComponent {
public:
  virtual void update(GameObject& obj) override {
	// AI to automatically control obj
  }
};


class BjornPhysicsComponent : public PhysicsComponent {
private:
  Volume volume_;
public:
  virtual void update(GameObject& obj, World& world) {
	obj.x += obj.velocity;
	world.resolveCollision(volume_, obj.x, obj.y, obj.velocity);
  }
};


class BjornGraphicsComponent : public GraphicsComponent {
private:
private:
  Sprite spriteStand_;
  Sprite spriteWalkLeft_;
  Sprite spriteWalkRight_;
public:
  virtual void update(GameObject& obj, Graphics& graphics) {
	Sprite* sprite = &spriteStand_;
	if (obj.velocity < 0) {
	  sprite = &spriteWalkLeft_;
	}
	else if (obj.velocity > 0) {
	  sprite = &spriteWalkRight_;
	}
	graphics.draw(*sprite, obj.x, obj.y);
  }
};

GameObject* createBjorn() {
  return new GameObject(new PlayerInputComponent(), new BjornPhysicsComponent(), new BjornGraphicsComponent());
}
