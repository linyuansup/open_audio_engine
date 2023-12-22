#include "api.h"

Playback *playback = nullptr;

EXAPI int init()
{
	try
	{
		playback = new Playback();
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int get_device_count()
{
	return playback->device_num;
}

EXAPI AudioDevice *get_devices()
{
	return playback->devices;
}

EXAPI int setup(int device_id, int sample_rate, int frame_per_buffer)
{
	try
	{
		return playback->setup(device_id, sample_rate, frame_per_buffer);
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int add_mono_track()
{
	try
	{
		return playback->editor->add_mono_track(new MonoTrack());
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int remove_mono_track(int track_id)
{
	try
	{
		playback->editor->remove_mono_track(track_id);
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int add_stereo_track()
{
	try
	{
		return playback->editor->add_stereo_track(new StereoTrack());
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int remove_stereo_track(int track_id)
{
	try
	{
		playback->editor->remove_stereo_track(track_id);
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int add_mono_content(int track_id, char *path, int start_sample)
{
	try
	{
		playback->editor->get_mono_track(track_id)->add(new MonoData(path, start_sample));
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int remove_mono_content(int track_id, int content_id)
{
	try
	{
		playback->editor->get_mono_track(track_id)->remove(content_id);
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int change_mono_content_pos(int track_id, int content_id, int start_sample)
{
	try
	{
		playback->editor->get_mono_track(track_id)->get_data(content_id)->start_sample = start_sample;
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int add_stereo_content(int track_id, char *path, int start_sample)
{
	try
	{
		playback->editor->get_stereo_track(track_id)->add(new StereoData(path, start_sample));
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int remove_stereo_content(int track_id, int content_id)
{
	try
	{
		playback->editor->get_stereo_track(track_id)->remove(content_id);
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int change_stereo_content_pos(int track_id, int content_id, int start_sample)
{
	try
	{
		playback->editor->get_stereo_track(track_id)->get_data(content_id)->start_sample = start_sample;
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int add_locker(int start_sample, int length)
{
	try
	{
		playback->editor->add_locker(new Locker(start_sample, length));
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int remove_lock(int id)
{
	try
	{
		playback->editor->remove_locker(id);
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int play(int sample)
{
	try
	{
		playback->position = sample;
		playback->playing = true;
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int stop()
{
	try
	{
		playback->playing = false;
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int mute_mono_track(int track_id)
{
	try
	{
		playback->editor->get_mono_track(track_id)->mute = true;
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int demute_mono_track(int track_id)
{
	try
	{
		playback->editor->get_mono_track(track_id)->mute = false;
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int mute_stereo_track(int track_id)
{
	try
	{
		playback->editor->get_stereo_track(track_id)->mute = true;
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int demute_stereo_track(int track_id)
{
	try
	{
		playback->editor->get_stereo_track(track_id)->mute = false;
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int get_current_sample()
{
	try
	{
		return playback->position;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int set_mono_track_volume(int track_id, double volume)
{
	try
	{
		playback->editor->get_mono_track(track_id)->volume = volume;
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int set_stereo_track_volume(int track_id, double volume)
{
	try
	{
		playback->editor->get_stereo_track(track_id)->volume = volume;
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int set_mono_track_pan(int track_id, double pan)
{
	try
	{
		playback->editor->get_mono_track(track_id)->pan = pan;
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}

EXAPI int set_stereo_track_pan(int track_id, double pan)
{
	try
	{
		playback->editor->get_stereo_track(track_id)->pan = pan;
		return 0;
	}
	catch (const std::exception &)
	{
		return -1;
	}
}
