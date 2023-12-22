#ifndef OPEN_AUDIO_ENGINE_MONO_TRACK_H
#define OPEN_AUDIO_ENGINE_MONO_TRACK_H

#include <unordered_map>
#include <cmath>

#include "mono_data.h"

class MonoTrack {
private:
	int id = 0;
	std::unordered_map<int, MonoData*> dataset;

public:
	double volume;
	double pan;
	bool mute;

private:
	void copy(MonoData* dst, MonoData* src);

public:
	int add(MonoData* data);
	void remove(int id);
	MonoData* get_data(int id);
	MonoData* get(int start_sample, int length);
	~MonoTrack();
};

#endif