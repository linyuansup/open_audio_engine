#ifndef OPEN_AUDIO_ENGINE_STEREO_DATA_H
#define OPEN_AUDIO_ENGINE_STEREO_DATA_H

#include <stdlib.h>
#include <string>
#include <cmath>

#include "audio_file/AudioFile.h"

class StereoData
{
public:
	int start_sample;
	float* left;
	float* right;
	int size;

public:
	~StereoData();
	StereoData(int size, int start_sample);
	StereoData(std::string path, int start_sample);
	int end_sample();
};

#endif