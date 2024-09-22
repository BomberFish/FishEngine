#include "FileSystem.hpp"

#define DATA_DIR "data"

using namespace std;
namespace stdfs = std::filesystem;


FileSystem::FileSystem(string rootPath) {
	this->rootPath = rootPath;
	if(!stdfs::is_directory(stdfs::path(rootPath))) {
		string msg = "Data directory not found: ";
		msg += DATA_DIR;
		
		throw runtime_error(msg);
	}
}

FileSystem::~FileSystem() {}

string FileSystem::GetPath(const string &path) {
	string filePath = string(this->rootPath) + "/" + path;
	// printf("Path: %s\n", filePath.c_str());
	return filePath;
}

string FileSystem::GetShaderPath(const string &path) {
	string shaderPath = GetPath("shaders/" + path);
	// printf("Shader path: %s\n", shaderPath.c_str());
	return shaderPath;
}

string FileSystem::GetTexturePath(const string &path) {
	string texturePath = GetPath("textures/" + path);
	// printf("Texture path: %s\n", texturePath.c_str());
	return texturePath;
}

string FileSystem::GetModelPath(const string &path) {
	string modelPath = GetPath("models/" + path);
	// printf("Model path: %s\n", modelPath.c_str());
	return modelPath;
}

string FileSystem::GetAudioPath(const string &path) {
	string audioPath = GetPath("audio/" + path);
	// printf("Audio path: %s\n", audioPath.c_str());
	return audioPath;
}
