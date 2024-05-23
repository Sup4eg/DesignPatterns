class Audio {
public:
  virtual ~Audio() {}
  virtual void playSound(int soundID) = 0;
  virtual void stopSound(int soundID) = 0;
  virtual void stopAllSounds() = 0;
};

class ConsoleAudio : public Audio {
public:
  virtual void playSound(int soundID) override {
	// Play sound using console audio
  }

  virtual void stopSound(int soundID) override {
	// Stop sound using console audio
  }

  virtual void stopAllSounds() override {
	// Stop all sounds using console audio
  }
};

class NullAudio : public Audio {
public:
  virtual void playSound(int soundID) override {
	// Do nothing
  }

  virtual void stopSound(int soundID) override {
	// Do nothing
  }

  virtual void stopAllSounds() override {
	// Do nothing
  }
};

//Logging here
class LoggedAudio : public Audio {
private:
  void log(const char* message) {
	// Log message
  }
  Audio& wrapped_;
public:

  LoggedAudio(Audio& wrapped) : wrapped_(wrapped) {}

  virtual void playSound(int soundID) override {
	log("play sound");
	wrapped_.playSound(soundID);
  }

  virtual void stopSound(int soundID) override {
	log("stop sound");
	wrapped_.stopSound(soundID);
  }

  virtual void stopAllSounds() override {
	log("stop all sounds");
	wrapped_.stopAllSounds();
  }
};

class Locator {
public:
  
  static void initialize() {
	service_ = &nullService_;
  }
  
  static Audio& getAudio() {
	return *service_;
  }

  static void provide(Audio* service) {
	if (service == nullptr) {
	  service_ = &nullService_;
	}
	else {
	  service_ = service;
	}
  }

private:
  static Audio* service_;
  static NullAudio nullService_;
};

Audio* Locator::service_ = nullptr;
NullAudio Locator::nullService_;

void enableAudioLogging() {
  Locator::provide(new LoggedAudio(Locator::getAudio()));
  
}