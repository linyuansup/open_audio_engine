#include "main.h"

int main()
{
	int res = init();
	if (res != 0)
	{
		return -1;
	}
	res = setup(4, 48000, 480);
	if (res != 0)
	{
		return -1;
	}
	{
		int track = add_mono_track();
		set_mono_track_pan(track, 1);
		res = add_mono_content(track, "D:\\93601\\Desktop\\中文.wav", 0);
		if (res != 0)
		{
			return -1;
		}
	}
	{
		int track = add_mono_track();
		set_mono_track_pan(track, -1);
		res = add_mono_content(track, "D:\\93601\\Desktop\\中文.wav", 60000);
		if (res != 0)
		{
			return -1;
		}
	}
	res = play(0);
	if (res != 0)
	{
		return -1;
	}
	getchar();
	return 0;
}