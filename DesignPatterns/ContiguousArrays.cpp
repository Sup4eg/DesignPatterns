//Contiguous arrays

class AIComponent;
class PhysicsComponent;
class RenderComponent;

class GameEntity {
private:
  AIComponent* ai_ = nullptr;
  PhysicsComponent* physics_ = nullptr;
  RenderComponent* render_ = nullptr;
public:
  GameEntity() {}
  GameEntity(AIComponent* ai, PhysicsComponent* physics, RenderComponent* render) : ai_(ai), physics_(physics), render_(render) {}

  AIComponent* ai() { return ai_; }
  PhysicsComponent* physics() { return physics_; }
  RenderComponent* render() { return render_; }
};

class AIComponent {
public:
  void update() {
	// AI logic
  }
};

class PhysicsComponent {
public:
  void update() {
	// Physics logic
  }
};

class RenderComponent {
public:
  void update() {
	// Render logic
  }
};

void classicalTestDataLocality() {
  bool gameOver = false;
  const int numEntities = 20;
  //mock entities
  GameEntity** entities = new GameEntity*[numEntities];

  while (!gameOver) {
	//Process AI
	for (int i = 0; i < numEntities; i++) {
	  entities[i]->ai()->update();
	}

	//Process Physics
	for (int i = 0; i < numEntities; i++) {
	  entities[i]->physics()->update();
	}

	//Draw to screen
	for (int i = 0; i < numEntities; i++) {
	  entities[i]->render()->update();
	}
  }
}

void testContiguousArrays() {
  const int MAX_ENTITIES = 20;
  bool gameOver = false;
  AIComponent* aiComponents = new AIComponent[MAX_ENTITIES];
  PhysicsComponent* physicsComponents = new PhysicsComponent[MAX_ENTITIES];
  RenderComponent* renderComponents = new RenderComponent[MAX_ENTITIES];

  while (!gameOver) {
	//Process AI
	for (int i = 0; i < MAX_ENTITIES; i++) {
	  aiComponents[i].update();
	}

	//Update Physics
	for (int i = 0; i < MAX_ENTITIES; i++) {
	  physicsComponents[i].update();
	}

	//Draw to screen
	for (int i = 0; i < MAX_ENTITIES; i++) {
	  renderComponents[i].update();
	}
  }
}