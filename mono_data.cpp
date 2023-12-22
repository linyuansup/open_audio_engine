#include "mono_data.h"

MonoData::~MonoData()
{
	if (data != nullptr)
	{
		free(data);
		data = nullptr;
	}
}

MonoData::MonoData(int size, int start_sample) : size(size), start_sample(start_sample)
{
	data = (float*)malloc(sizeof(float) * size);
	for (int i = 0; i < size; i++) {
		data[i] = 0;
	}
}

MonoData::MonoData(std::string path, int start_sample) : start_sample(start_sample)
{
	AudioFile<float>* audio = new AudioFile<float>;
	audio->load(path);
	auto samples = audio->samples[0];
	size = samples.size();
	data = (float*)malloc(sizeof(float) * size);
	for (int i = 0; i < size; i++) {
		data[i] = samples[i];
	}
	delete audio;
}

int MonoData::end_sample()
{
	return start_sample + size;
}
