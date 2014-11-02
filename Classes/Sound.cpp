#include "Sound.h"

Sound * Sound::m_sound = NULL;

Sound * Sound::getInstance()
{
	if(m_sound == NULL)
	{
		m_sound = new Sound();
	}

	return m_sound;
}

void Sound::freeInstance()
{
	if(m_sound != NULL)
	{
		delete m_sound;
		m_sound = NULL;
	}
}

Sound::Sound()
{
	//预先加载声音，参数是声音文件
	auto audio = SimpleAudioEngine::getInstance();
	//预先加载音乐的函数在win32下是空的实现 播放的效果是滞后的 在android上没有问题
	audio->preloadBackgroundMusic(getMusic(MUSIC_TYPE_BACKGROUND));
	audio->preloadBackgroundMusic(getMusic(MUSIC_TYPE_BIG_SPACESHIP_FLYING));
	//加载音效 在win32下加载音效没有什么效果，播放出来是滞后的，但是在android上没有滞后的问题
	audio->preloadEffect(getEffect(EFFECT_TYPE_BULLET));
	audio->preloadEffect(getEffect(EFFECT_TYPE_BUTTON));
	audio->preloadEffect(getEffect(EFFECT_TYPE_ENEMY1_DOWN));
	audio->preloadEffect(getEffect(EFFECT_TYPE_ENEMY2_DOWN));
	audio->preloadEffect(getEffect(EFFECT_TYPE_ENEMY3_DOWN));
	audio->preloadEffect(getEffect(EFFECT_TYPE_GAME_OVER));
	audio->preloadEffect(getEffect(EFFECT_TYPE_GET_UFO));
	audio->preloadEffect(getEffect(EFFECT_TYPE_OUT_PORP));
	//设置声音的大小0.0-1.0 在win32下也是空的实现
	audio->setBackgroundMusicVolume(0.5f);
}

//获取音效和音乐的文件
char * Sound::getMusic(MUSIC_TYPE type)
{
	switch(type)
	{
	case MUSIC_TYPE_BACKGROUND:
		//获取不同平台下的文件
		return "sound/game_music.mp3";
		break;
	case MUSIC_TYPE_BIG_SPACESHIP_FLYING:
		return "sound/big_spaceship_flying.mp3";
		break;
	}
	return NULL;
}

char * Sound::getEffect(EFFECT_TYPE type)
{
	switch(type)
	{
	case EFFECT_TYPE_BUTTON:
		return "sound/button.mp3";
		break;
	case EFFECT_TYPE_BULLET:
		return "sound/bullet.mp3";
		break;
	case EFFECT_TYPE_ENEMY1_DOWN:
		return "sound/enemy1_down.mp3";
		break;
	case EFFECT_TYPE_ENEMY2_DOWN:
		return "sound/enemy2_down.mp3";
		break;
	case EFFECT_TYPE_ENEMY3_DOWN:
		return "sound/enemy3_down.mp3";
		break;
	case EFFECT_TYPE_GAME_OVER:
		return "sound/game_over.mp3";
		break;
	case	EFFECT_TYPE_GET_UFO:
		return "sound/get_double_laser.mp3";
		break;
	case EFFECT_TYPE_OUT_PORP:
		return "sound/out_porp.mp3";
		break;
	default:
		return NULL;
	}
}

//播放音乐和音效
void Sound::playEffect(EFFECT_TYPE type)
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect(this->getEffect(type));
}
	
void Sound::playBgMusic(MUSIC_TYPE type)
{
	auto audio = SimpleAudioEngine::getInstance();
	if(!audio->isBackgroundMusicPlaying())
	{
		audio->playBackgroundMusic(this->getMusic(type),true);
	}
	else
	{
		audio->resumeBackgroundMusic();
	}
}
