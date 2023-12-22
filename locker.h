#ifndef OPEN_AUDIO_ENGINE_LOCKER_H
#define OPEN_AUDIO_ENGINE_LOCKER_H

class Locker
{
public:
	int start_sample;
	int size;

public:
	~Locker() = default;
	Locker(int start_sample, int size);
};

#endif