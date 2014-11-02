#ifndef _SOUND_H_
#define _SOUND_H_
#include "cocos2d.h"
//声音引擎
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

//把用到的音乐做为枚举类型
enum MUSIC_TYPE
{
	//游戏的背景音乐 game_music.mp3
	MUSIC_TYPE_BACKGROUND,
	//最大的敌机飞行时候的背景音乐 big_spaceship_flying.mp3
	MUSIC_TYPE_BIG_SPACESHIP_FLYING,
};

//把用到的音乐做为枚举类型
enum EFFECT_TYPE
{
	//单击菜单按钮时候的音效 button.mp3
	EFFECT_TYPE_BUTTON,
	//发射子弹时候的音效 bullet.mp3
	EFFECT_TYPE_BULLET,
	//敌机炸毁的音效 enemy1_down.mp3 enemy2_down.mp3 enemy3_down.mp3
	EFFECT_TYPE_ENEMY1_DOWN,
	EFFECT_TYPE_ENEMY2_DOWN,
	EFFECT_TYPE_ENEMY3_DOWN,
	//游戏结束 game_over.mp3
	EFFECT_TYPE_GAME_OVER,
	//获得UFO道具 get_double_laser.mp3
	EFFECT_TYPE_GET_UFO,
	//道具出来时候的音效 out_porp.mp3
	EFFECT_TYPE_OUT_PORP
};

//声音处理类
class Sound
{
public:
	static Sound * getInstance();
	static void freeInstance();
private:
	static Sound * m_sound;
	Sound();
	//根据不同的音乐和音效类型获得相应平台下的文件
	char * getMusic(MUSIC_TYPE type);
	char * getEffect(EFFECT_TYPE type);
public:
	//声音的播放和停止
	void playEffect(EFFECT_TYPE type);
	void playBgMusic(MUSIC_TYPE type);
};

#endif