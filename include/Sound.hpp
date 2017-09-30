#ifndef SOUND_CLASS_HPP
#define SOUND_CLASS_HPP

#include "Bomberman.hpp"

#define SOUND_CHANNELS 2
#define SOUND_CHUNK_SIZE 4096

/* Channels */
#define WALK_CHANNEL 1
#define SCROLL_CHANNEL 2
#define ENTER_CHANNEL 3
#define DEFAULT_CHANNEL -1

/* Effects */
#define NUM_EFFECTS 3

#define EFFECT_WALK 0
#define EFFECT_SCROLL 1
#define EFFECT_ENTER 2

/* Music */
#define NUM_MUSIC 3

#define MUSIC_BACK 0
#define MUSIC_MENU1 1
#define MUSIC_MENU2 2

class Sound
{
    private:
        int _fade_time;
        Mix_Music **music;
        Mix_Chunk **effects;
        int _currently_playing;
    
        void loadEffects(void);
        void loadMusic(void);

    public:
        Sound(void);
        ~Sound(void);

        void playEffectOnce(int effect, int channel);
        void playEffectLoop(int effect, int loop);
        void playEffectForvever(int effect);

        int musicIsPlaying();
        void playMusicOnce(int music);
        void playMusicLoop(int music, int loop);
        void playMusicForvever(int music);

        void stopMusic(int fade_time);
        void stopEffect(int channel);

        int getCurrentlyPlaying();
        Mix_Chunk **getEffects(void);
        Mix_Music **getMusic(void);

        void operator=(Sound *rhs);
};

#endif
