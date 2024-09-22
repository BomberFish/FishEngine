#include "AudioManager.hpp"

using namespace std;

// Function to load a .wav file (simplified for example purposes)
bool loadWavFile(const std::string &filename, std::vector<char> &buffer, ALenum &format, ALsizei &freq) {
    // Open file
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
		std::string msg = "Failed to open file: ";
		msg += filename;
		dialog::show(msg.c_str(), "Audio Error");
        fprintf(stderr, "%s\n", msg.c_str());
        return false;
    }

    // Read header
    char header[44];
    file.read(header, 44);

    // Extract format and frequency
    format = (header[22] == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    freq = *reinterpret_cast<int*>(header + 24);

    // Read data
    buffer.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    return true;
}

AudioManager::AudioManager() {
	device = alcOpenDevice(NULL);
	if (!device) {
		throw runtime_error("Failed to open audio device!");
	}

	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context)) {
		alcDestroyContext(context);
		alcCloseDevice(device);
		throw runtime_error("Failed to make audio context current!");
	}
}

AudioManager::~AudioManager() {
	alcMakeContextCurrent(NULL);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

void AudioManager::playSound(const std::string &name) {
    std::thread(&AudioManager::playSoundInternal, this, name).detach();
}

void AudioManager::playSoundInternal(const std::string &name) {
    std::string path = Common::FS->GetAudioPath(name);
    printf("Playing sound: %s\n", path.c_str());

    std::vector<char> bufferData;
    ALenum format;
    ALsizei freq;
    if (!loadWavFile(path, bufferData, format, freq)) {
        throw std::runtime_error("Failed to load audio file!");
    }

    ALuint buffer;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, bufferData.data(), bufferData.size(), freq);

    ALuint source;
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);

    soundSources[name] = source; // Store the source ID with the sound name

    alSourcePlay(source);
}

void AudioManager::stopSound(const std::string &name) {
    auto it = soundSources.find(name);
    if (it != soundSources.end()) {
        alSourceStop(it->second);
    }
}

void AudioManager::stopAllSounds() {
    for (const auto &pair : soundSources) {
        alSourceStop(pair.second);
    }
}