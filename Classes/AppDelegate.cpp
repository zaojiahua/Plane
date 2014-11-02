#include "AppDelegate.h"
#include "StartGame.h"

USING_NS_CC;

AppDelegate::AppDelegate() 
{

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview)
	{
		//����һ�´��ڵ�����
        glview = GLView::create("Plane By XiaoTa");
		//���ô��ڵĴ�С
		glview->setFrameSize(400,600);
        director->setOpenGLView(glview);
    }

	//���䷽��
	//getFrameSize()���ʵ����Ļ�Ĵ�С
	 Size frameSize = glview->getFrameSize();
	 //����д�ľ���һ������Ϊ����ͼƬ������ͼƬ�Ĵ�С�������ԭ����Ƿŵ�����С������ʲôΪ���գ���Ȼ����
	 //����������ͼƬΪ���գ�ʲôͼƬ��󣬵�Ȼ�Ǳ���ͼƬ�ˣ��Ժ�������ͼ��ʱ���õľ������µ�����ߴ�
	 Size winSize=CCSize(480,852);

	 //����͸���һ���ȣ�ͨ������ȣ�������ĵ����߼��ֱ��ʵĴ�С
	 float widthRate = frameSize.width/winSize.width;
	 float heightRate = frameSize.height/winSize.height;

	 //�����if�е���䣬˵���߼��ĸ߶��е���ˣ��Ͱ��߼��ĸ���С���Ϳ��һ���ı���
    if (widthRate > heightRate)
	{
		//��ߴ����ǰ�������������߼��ֱ��ʵĴ�С��Ҳ����ͨ��getWinSize()�õ��Ĵ�С
		glview->setDesignResolutionSize(winSize.width,
			winSize.height*heightRate/widthRate, ResolutionPolicy::NO_BORDER);
	}
    else
	{
		glview->setDesignResolutionSize(winSize.width*widthRate/heightRate, winSize.height,
			ResolutionPolicy::NO_BORDER);
	}

	//���ú���ʾ֡��
    //director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);

	//����������������
    auto scene = StartGame::createScene();
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
