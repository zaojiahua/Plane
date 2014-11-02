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
	//Ԥ�ȼ��������������������ļ�
	auto audio = SimpleAudioEngine::getInstance();
	//Ԥ�ȼ������ֵĺ�����win32���ǿյ�ʵ�� ���ŵ�Ч�����ͺ�� ��android��û������
	audio->preloadBackgroundMusic(getMusic(MUSIC_TYPE_BACKGROUND));
	audio->preloadBackgroundMusic(getMusic(MUSIC_TYPE_BIG_SPACESHIP_FLYING));
	//������Ч ��win32�¼�����Чû��ʲôЧ�������ų������ͺ�ģ�������android��û���ͺ������
	audio->preloadEffect(getEffect(EFFECT_TYPE_BULLET));
	audio->preloadEffect(getEffect(EFFECT_TYPE_BUTTON));
	audio->preloadEffect(getEffect(EFFECT_TYPE_ENEMY1_DOWN));
	audio->preloadEffect(getEffect(EFFECT_TYPE_ENEMY2_DOWN));
	audio->preloadEffect(getEffect(EFFECT_TYPE_ENEMY3_DOWN));
	audio->preloadEffect(getEffect(EFFECT_TYPE_GAME_OVER));
	audio->preloadEffect(getEffect(EFFECT_TYPE_GET_UFO));
	audio->preloadEffect(getEffect(EFFECT_TYPE_OUT_PORP));
	//���������Ĵ�С0.0-1.0 ��win32��Ҳ�ǿյ�ʵ��
	audio->setBackgroundMusicVolume(0.5f);
}

//��ȡ��Ч�����ֵ��ļ�
char * Sound::getMusic(MUSIC_TYPE type)
{
	switch(type)
	{
	case MUSIC_TYPE_BACKGROUND:
		//��ȡ��ͬƽ̨�µ��ļ�
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		return "sound/game_music.mp3";
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		return "sound/game_music.mp3";
#endif
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

//�������ֺ���Ч
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
