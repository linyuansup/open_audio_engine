#include "editor.h"

int Editor::add_mono_track(MonoTrack* track)
{
	auto current_id = mono_track_id;
	mono_track_id++;
	mono_tracks[current_id] = track;
	return current_id;
}

int Editor::add_stereo_track(StereoTrack* track)
{
	auto current_id = stereo_track_id;
	stereo_track_id++;
	stereo_tracks[current_id] = track;
	return current_id;
}

int Editor::add_locker(Locker* locker)
{
	auto current_id = locker_id;
	locker_id++;
	lockers[current_id] = locker;
	return current_id;
}

void Editor::remove_mono_track(int id)
{
	auto v = mono_tracks.find(id);
	if (v != mono_tracks.end())
	{
		delete (*v).second;
		mono_tracks.erase(id);
	}
}

void Editor::remove_stereo_track(int id)
{
	auto v = stereo_tracks.find(id);
	if (v != stereo_tracks.end())
	{
		delete (*v).second;
		stereo_tracks.erase(id);
	}
}

void Editor::remove_locker(int id)
{
	auto v = lockers.find(id);
	if (v != lockers.end())
	{
		delete (*v).second;
		lockers.erase(id);
	}
}

MonoTrack* Editor::get_mono_track(int id)
{
	return mono_tracks[id];
}

StereoTrack* Editor::get_stereo_track(int id)
{
	return stereo_tracks[id];
}

StereoData* Editor::get(int start_sample, int length)
{
	int end_sample = start_sample + length;
	for (const auto& pair : lockers) {
		auto part = pair.second;
		if (part->start_sample + part->size < end_sample || part->start_sample > end_sample)
		{
			return nullptr;
		}
	}
	auto content = new StereoData(length, 0);
	for (const auto& pair : mono_tracks) {
		auto data = pair.second->get(start_sample, length);
		if (data == nullptr)
		{
			continue;
		}
		double left_dec = 1, right_dec = 1;
		double pan = pair.second->pan;
		if (pan > 0) {
			left_dec = 1 - abs(pan);
		}
		else if (pan < 0) {
			right_dec = 1 - abs(pan);
		}
		for (int i = 0; i < length; i++) {
			content->left[i] += (data->data[i] * left_dec);
			content->right[i] += (data->data[i] * right_dec);
		}
		delete data;
	}
	for (const auto& pair : stereo_tracks) {
		auto data = pair.second->get(start_sample, length);
		if (data == nullptr)
		{
			continue;
		}
		double left_dec = 1, right_dec = 1;
		double pan = pair.second->pan;
		if (pan > 0) {
			left_dec = 1 - abs(pan);
		}
		else if (pan < 0) {
			right_dec = 1 - abs(pan);
		}
		for (int i = 0; i < length; i++) {
			content->left[i] += (data->left[i] * left_dec);
			content->right[i] += (data->right[i] * right_dec);
		}
		delete data;
	}
	return content;
}

Editor::~Editor()
{
	for (const auto& pair : mono_tracks) {
		delete pair.second;
	}
	mono_tracks.clear();
	for (const auto& pair : stereo_tracks) {
		delete pair.second;
	}
	stereo_tracks.clear();
	for (const auto& pair : lockers) {
		delete pair.second;
	}
	lockers.clear();
}
