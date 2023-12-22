#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_DECODING
#define MA_NO_ENCODING
#define MA_NO_RESOURCE_MANAGER
#define MA_NO_NODE_GRAPH
#define MA_NO_GENERATION

#include "playback.h"

void clean_data(float *data, int size)
{
    for (int i = 0; i < size; i++)
    {
        data[i] = 0;
    }
}

void data_callback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount)
{
    float *out = (float *)pOutput;
    Playback *playback = (Playback *)pDevice->pUserData;
    if (!playback->playing)
    {
        clean_data(out, frameCount * 2);
        return;
    }
    auto dataset = playback->editor->get(playback->position, frameCount);
    if (dataset == nullptr)
    {
        clean_data(out, frameCount * 2);
        return;
    }
    for (int i = 0; i < frameCount; i++)
    {
        out[i * 2] = dataset->left[i];
        out[i * 2 + 1] = dataset->right[i];
    }
    delete dataset;
    playback->position += frameCount;
    return;
}

Playback::Playback()
{
    ma_context context;
    if (ma_context_init(NULL, 0, NULL, &context) != MA_SUCCESS)
    {
        throw;
    }
    editor = new Editor();
    if (ma_context_get_devices(&context, &playback_devices, &device_num, NULL, NULL) != MA_SUCCESS)
    {
        throw;
    }
    devices = (AudioDevice *)malloc(sizeof(AudioDevice) * device_num);
    for (ma_uint32 iDevice = 0; iDevice < device_num; iDevice++)
    {
        devices[iDevice].id = iDevice;
        devices[iDevice].name = playback_devices[iDevice].name;
        // TODO: Get API name
    }
}

int Playback::setup(int device_id, int sample_rate, int frame_per_buffer)
{
    this->sample_rate = sample_rate;
    ma_device_config device_config = ma_device_config_init(ma_device_type_playback);
    device_config.playback.pDeviceID = &playback_devices[device_id].id;
    device_config.playback.format = ma_format_f32;
    device_config.playback.channels = 2;
    device_config.sampleRate = sample_rate;
    device_config.dataCallback = data_callback;
    device_config.pUserData = this;
    device_config.periodSizeInFrames = frame_per_buffer;

    if (ma_device_init(NULL, &device_config, &device) != MA_SUCCESS)
    {
        return -1;
    }
    ma_device_start(&device);
    return 0;
}
