#ifndef OPEN_AUDIO_ENGINE_API_H
#define OPEN_AUDIO_ENGINE_API_H

#ifdef EXPORTED_FUNCTION_VISIBILITY
#ifdef _WIN32
#define EXAPI extern "C" __declspec(dllexport)
#else
#define EXAPI extern "C" __attribute__((visibility("default")))
#endif
#else
#define EXAPI
#endif

#include <string>

#include "playback.h"

EXAPI int init();
EXAPI int get_device_count();
EXAPI AudioDevice* get_devices();
EXAPI int setup(int device_id, int sample_rate, int frame_per_buffer);
EXAPI int add_mono_track();
EXAPI int remove_mono_track(int track_id);
EXAPI int add_stereo_track();
EXAPI int remove_stereo_track(int track_id);
EXAPI int add_mono_content(int track_id, char* path, int start_sample);
EXAPI int remove_mono_content(int track_id, int content_id);
EXAPI int change_mono_content_pos(int track_id, int content_id, int start_sample);
EXAPI int add_stereo_content(int track_id, char* path, int start_sample);
EXAPI int remove_stereo_content(int track_id, int content_id);
EXAPI int change_stereo_content_pos(int track_id, int content_id, int start_sample);
EXAPI int add_locker(int start_sample, int length);
EXAPI int remove_lock(int id);
EXAPI int play(int sample);
EXAPI int stop();
EXAPI int mute_mono_track(int track_id);
EXAPI int demute_mono_track(int track_id);
EXAPI int mute_stereo_track(int track_id);
EXAPI int demute_stereo_track(int track_id);
EXAPI int get_current_sample();
EXAPI int set_mono_track_volume(int track_id, double volume);
EXAPI int set_stereo_track_volume(int track_id, double volume);
EXAPI int set_mono_track_pan(int track_id, double pan);
EXAPI int set_stereo_track_pan(int track_id, double pan);

#endif