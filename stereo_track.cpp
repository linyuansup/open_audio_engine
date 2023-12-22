#include "stereo_track.h"

void StereoTrack::copy(StereoData* dst, StereoData* src)
{
	int i = 0, j = 0, cp_length;
	if (src->start_sample <= dst->start_sample && src->end_sample() <= dst->end_sample())
	{
		i = dst->start_sample - src->start_sample;
		cp_length = src->end_sample() - dst->start_sample;
	}
	if (src->start_sample <= dst->start_sample && src->end_sample() >= dst->end_sample())
	{
		i = dst->start_sample - src->start_sample;
		cp_length = dst->size;
	}
	if (src->start_sample >= dst->start_sample && src->end_sample() <= dst->end_sample())
	{
		j = src->start_sample - dst->start_sample;
		cp_length = src->size;
	}
	if (src->start_sample >= dst->start_sample && src->end_sample() >= dst->end_sample())
	{
		j = src->start_sample - dst->start_sample;
		cp_length = dst->end_sample() - src->start_sample;
	}
	for (int k = 0; k < cp_length; k++) {
		dst->left[j + k] += src->left[i + k];
		dst->right[j + k] += src->right[i + k];
	}
}

int StereoTrack::add(StereoData* data)
{
	long current_id = id;
	id++;
	dataset[id] = data;
	return current_id;
}

StereoData* StereoTrack::get_data(int id)
{
	return dataset[id];
}

void StereoTrack::remove(int id)
{
	auto v = dataset.find(id);
	if (v != dataset.end())
	{
		delete (*v).second;
		dataset.erase(id);
	}
}

StereoData* StereoTrack::get(int start_sample, int length)
{
	if (mute)
	{
		return nullptr;
	}
	int end_sample = start_sample + length;
	StereoData* content = new StereoData(length, start_sample);
	if (content == nullptr)
	{
		throw std::bad_alloc();
	}
	for (const auto& pair : dataset) {
		auto part = pair.second;
		if (part->start_sample + part->size < end_sample || part->start_sample > end_sample)
		{
			continue;
		}
		copy(content, part);
	}
	double volumn_change = std::pow(10.0f, volume / 20.0f);
	for (int i = 0; i < length; i++)
	{
		content->left[i] *= volumn_change;
		content->right[i] *= volumn_change;
	}
	return content;
}

StereoTrack::~StereoTrack()
{
	for (const auto& pair : dataset) {
		delete pair.second;
	}
	dataset.clear();
}

