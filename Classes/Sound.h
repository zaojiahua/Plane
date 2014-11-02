#ifndef _SOUND_H_
#define _SOUND_H_
#include "cocos2d.h"
//��������
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

//���õ���������Ϊö������
enum MUSIC_TYPE
{
	//��Ϸ�ı������� game_music.mp3
	MUSIC_TYPE_BACKGROUND,
	//���ĵл�����ʱ��ı������� big_spaceship_flying.mp3
	MUSIC_TYPE_BIG_SPACESHIP_FLYING,
};

//���õ���������Ϊö������
enum EFFECT_TYPE
{
	//�����˵���ťʱ�����Ч button.mp3
	EFFECT_TYPE_BUTTON,
	//�����ӵ�ʱ�����Ч bullet.mp3
	EFFECT_TYPE_BULLET,
	//�л�ը�ٵ���Ч enemy1_down.mp3 enemy2_down.mp3 enemy3_down.mp3
	EFFECT_TYPE_ENEMY1_DOWN,
	EFFECT_TYPE_ENEMY2_DOWN,
	EFFECT_TYPE_ENEMY3_DOWN,
	//��Ϸ���� game_over.mp3
	EFFECT_TYPE_GAME_OVER,
	//���UFO���� get_double_laser.mp3
	EFFECT_TYPE_GET_UFO,
	//���߳���ʱ�����Ч out_porp.mp3
	EFFECT_TYPE_OUT_PORP
};

//����������
class Sound
{
public:
	static Sound * getInstance();
	static void freeInstance();
private:
	static Sound * m_sound;
	Sound();
	//���ݲ�ͬ�����ֺ���Ч���ͻ����Ӧƽ̨�µ��ļ�
	char * getMusic(MUSIC_TYPE type);
	char * getEffect(EFFECT_TYPE type);
public:
	//�����Ĳ��ź�ֹͣ
	void playEffect(EFFECT_TYPE type);
	void playBgMusic(MUSIC_TYPE type);
};

#endif