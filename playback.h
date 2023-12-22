#ifndef OPEN_AUDIO_ENGINE_PLAYBACK_H
#define OPEN_AUDIO_ENGINE_PLAYBACK_H

#include "editor.h"
#include "miniaudio.h"

void clean_data(float* data, int size);
void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);

struct AudioDevice
{
	int id;
	char* name;
};

class Playback
{
private:
	ma_device_info *playback_devices;
	ma_device device;

public:
	int position = 0;
	bool playing = false;
	AudioDevice* devices;
	unsigned int device_num = 0;
	Editor* editor;
	int sample_rate;

public:
	Playback();
	int setup(int device_id, int sample_rate, int frame_per_buffer);
};

#endif