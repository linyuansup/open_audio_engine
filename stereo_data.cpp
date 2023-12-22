#include "stereo_data.h"

StereoData::~StereoData()
{
	if (left != nullptr)
	{
		free(left);
		left = nullptr;
	}
	if (right != nullptr)
	{
		free(right);
		right = nullptr;
	}
}

StereoData::StereoData(int size, int start_sample) : size(size), start_sample(start_sample)
{
	left = (float*)malloc(sizeof(float) * size);
	right = (float*)malloc(sizeof(float) * size);
	for (int i = 0; i < size; i++) {
		left[i] = 0;
		right[i] = 0;
	}
}

StereoData::StereoData(std::string path, int start_sample) : start_sample(start_sample)
{
	AudioFile<float>* audio = new AudioFile<float>;
	audio->load(path);
	auto left_samples = audio->samples[0];
	auto right_samples = audio->samples[1];
	size = left_samples.size();
	left = (float*)malloc(sizeof(float) * size);
	right = (float*)malloc(sizeof(float) * size);
	for (int i = 0; i < size; i++) {
		left[i] = left_samples[i];
		right[i] = right_samples[i];
	}
	delete audio;
}

int StereoData::end_sample()
{
	return start_sample + size;
}
