#pragma once

#include "../common.hpp"
#if APPLE
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif

using namespace std;

class AudioManager {
public:
	AudioManager();
	~AudioManager();

	void playSound(const string &name);
	void stopSound(const string &name);
	void stopAllSounds();
private:
	ALCdevice *device;
	ALCcontext *context;
	std::unordered_map<std::string, ALuint> soundSources;

	void playSoundInternal(const string &name);
};