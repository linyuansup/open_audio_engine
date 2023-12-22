#ifndef OPEN_AUDIO_ENGINE_STEREO_TRACK_H
#define OPEN_AUDIO_ENGINE_STEREO_TRACK_H

#include <unordered_map>

#include "stereo_data.h"

class StereoTrack
{
private:
	int id = 0;
	std::unordered_map<int, StereoData*> dataset;

public:
	double volume;
	double pan;
	bool mute;

private:
	void copy(StereoData* dst, StereoData* src);

public:
	int add(StereoData* data);
	StereoData* get_data(int id);
	void remove(int id);
	StereoData* get(int start_sample, int length);
	~StereoTrack();
};

#endif