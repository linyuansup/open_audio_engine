#ifndef OPEN_AUDIO_ENGINE_EDITOR_H
#define OPEN_AUDIO_ENGINE_EDITOR_H

#include <unordered_map>

#include "mono_track.h"
#include "stereo_track.h"
#include "locker.h"

class Editor
{
private:
	int mono_track_id;
	int stereo_track_id;
	int locker_id;
	std::unordered_map<int, MonoTrack*> mono_tracks;
	std::unordered_map<int, StereoTrack*> stereo_tracks;
	std::unordered_map<int, Locker*> lockers;

public:
	int add_mono_track(MonoTrack* track);
	int add_stereo_track(StereoTrack* track);
	int add_locker(Locker* locker);
	void remove_mono_track(int id);
	void remove_stereo_track(int id);
	void remove_locker(int id);
	MonoTrack* get_mono_track(int id);
	StereoTrack* get_stereo_track(int id);
	StereoData* get(int start_sample, int length);
	~Editor();
};

#endif