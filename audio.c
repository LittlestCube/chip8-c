#include "chip8.h"

void SDLAudioCallback(void *UserData, Uint8 *AudioData, int Length)
{
	// Clear our audio buffer to silence.
	memset(AudioData, 0, Length);
}

void playAudio()
{
	SDL_PauseAudio(0);
}

void pauseAudio()
{
	SDL_PauseAudio(1);
}

void initAudio(int buffer_size)
{
	SDL_AudioSpec AudioSettings = {0};
	
	int samples_per_second = 48000;
	int ToneHz = 256;
	int16_t ToneVolume = 3000;
	uint32_t RunningSampleIndex = 0;
	int SquareWavePeriod = samples_per_second / ToneHz;
	int HalfSquareWavePeriod = SquareWavePeriod / 2;
	int BytesPerSample = sizeof(int16_t) * 2;
	
	int BytesToWrite = 800 * BytesPerSample;
	
	void *SoundBuffer = malloc(BytesToWrite);
	int16_t *SampleOut = (int16_t *)SoundBuffer;
	int SampleCount = BytesToWrite/BytesPerSample;
	
	for(int SampleIndex = 0; SampleIndex < SampleCount; ++SampleIndex)
	{
		int16_t SampleValue = ((RunningSampleIndex++ / HalfSquareWavePeriod) % 2) ? ToneVolume : -ToneVolume;
		*SampleOut++ = SampleValue;
		*SampleOut++ = SampleValue;
	}
	
	AudioSettings.freq = samples_per_second;
	AudioSettings.format = AUDIO_U8;
	AudioSettings.channels = 2;
	AudioSettings.samples = buffer_size;
	AudioSettings.callback = &SDLAudioCallback;
	
	SDL_OpenAudio(&AudioSettings, 0);
	
	if (AudioSettings.format != AUDIO_U8)
	{
		printf("E: could not initialize audio.");
		return;
	}
	
	SDL_QueueAudio(1, SoundBuffer, BytesToWrite);
	free(SoundBuffer);
	
	playAudio();
}