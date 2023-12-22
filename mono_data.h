#ifndef OPEN_AUDIO_ENGINE_MONO_DATA_H
#define OPEN_AUDIO_ENGINE_MONO_DATA_H

#include <stdlib.h>
#include <string>

#include "audio_file/AudioFile.h"

class MonoData
{
public:
	float* data;
	int start_sample;
	int size;

public:
	~MonoData();
	MonoData(int size, int start_sample);
	MonoData(std::string path, int start_sample);
	int end_sample();
};

#endif