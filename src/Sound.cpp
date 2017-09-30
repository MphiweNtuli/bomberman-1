#include "Sound.hpp"

void Sound::loadEffects(void)
{
    this->effects = new Mix_Chunk*[NUM_EFFECTS];
    (this->effects)[EFFECT_WALK] = Mix_LoadWAV("sounds/walk.ogg");
    (this->effects)[EFFECT_SCROLL] = Mix_LoadWAV("sounds/scroll.ogg");
    (this->effects)[EFFECT_ENTER] = Mix_LoadWAV("sounds/enter.ogg");
}

void Sound::loadMusic(void)
{
    this->music = new Mix_Music*[NUM_MUSIC];
    (this->music)[MUSIC_BACK] = Mix_LoadMUS("sounds/background.wav");
    (this->music)[MUSIC_MENU1] = Mix_LoadMUS("sounds/menu.ogg");
}

Sound::Sound(void)
{
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, SOUND_CHANNELS, SOUND_CHUNK_SIZE);
    loadEffects();
    loadMusic();
}

Sound::~Sound(void)
{
    int loop;

    loop = 0;
    while (loop < NUM_EFFECTS)
        Mix_FreeChunk((this->effects)[loop++]);
    delete[] this->effects;
    loop = 0;
    while (loop < NUM_MUSIC)
        Mix_FreeMusic((this->music)[loop++]);
    delete[] this->music;
    Mix_CloseAudio();
}

void Sound::playEffectOnce(int effect, int channel)
{
    
    Mix_PlayChannel(channel, (this->effects)[effect], 0);
}

void Sound::playEffectLoop(int effect, int loop)
{
    Mix_PlayChannel(DEFAULT_CHANNEL, (this->effects)[effect], loop);
}

void Sound::playEffectForvever(int effect)
{
    Mix_PlayChannel(DEFAULT_CHANNEL, (this->effects)[effect], -1);
}

int Sound::musicIsPlaying()
{
    return (Mix_PlayingMusic());
}

void Sound::playMusicOnce(int music)
{
    Mix_PlayMusic((this->music)[music], 1);
}

void Sound::playMusicLoop(int music, int loop)
{
    Mix_PlayMusic((this->music)[music], loop);
}

void Sound::playMusicForvever(int music)
{
    if (!musicIsPlaying())
    {
        Mix_FadeInMusic((this->music)[music], -1, 4000);
        _currently_playing = music;
    }
    else
    {
        if (_currently_playing != music)
        {
            Mix_FadeInMusic((this->music)[music], -1, 4000);
            _currently_playing = music;
        }
    }
}

void Sound::stopMusic(int fade_time)
{
    _fade_time = fade_time;
    Mix_FadeOutMusic(500);
}

void Sound::stopEffect(int channel)
{
    Mix_HaltChannel(channel);
}

int Sound::getCurrentlyPlaying()
{
    return (_currently_playing);
}

Mix_Chunk **Sound::getEffects(void)
{
    return (this->effects);
}

Mix_Music **Sound::getMusic(void)
{
    return (this->music);
}

void Sound::operator=(Sound *rhs)
{
    this->effects = rhs->getEffects();
    this->music = rhs->getMusic();
    this->_currently_playing = rhs->getCurrentlyPlaying();
}
