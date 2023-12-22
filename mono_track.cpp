#include "mono_track.h"

void MonoTrack::copy(MonoData* dst, MonoData* src)
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
		dst->data[j + k] += src->data[i + k];
	}
}

int MonoTrack::add(MonoData* data)
{
	long current_id = id;
	id++;
	dataset[id] = data;
	return current_id;
}

void MonoTrack::remove(int id)
{
	auto v = dataset.find(id);
	if (v != dataset.end())
	{
		delete (*v).second;
		dataset.erase(id);
	}
}

MonoData* MonoTrack::get_data(int id)
{
	return dataset[id];
}

MonoData* MonoTrack::get(int start_sample, int length)
{
	if (mute)
	{
		return nullptr;
	}
	int end_sample = start_sample + length;
	MonoData* content = new MonoData(length, start_sample);
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
		content->data[i] *= volumn_change;
	}
	return content;
}

MonoTrack::~MonoTrack()
{
	for (const auto& pair : dataset) {
		delete pair.second;
	}
	dataset.clear();
}
