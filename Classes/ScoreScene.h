#ifndef _SCORE_SCENE_H_
#define _SCORE_SCENE_H_
#include "cocos2d.h"
//ʹ��tableview���������չ��
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

//�����񳡾���ʹ��tableview����̳����µ���
class ScoreScene : public Layer,public TableViewDataSource,public TableViewDelegate
{
public:
	ScoreScene(void);
	~ScoreScene(void);
public:
	static Scene * createScene();
	bool init();
	CREATE_FUNC(ScoreScene);
public:
	//ʵ�������ӿ���Ҫʵ�ֵ��麯�����£������зǳ���Ҫ��һ����Ǻ����Ĳ���indexԭ��2.x�İ汾����Ϊ
	//unsigned int�����ڸ�Ϊ��ssize_t���ͣ�����д������ͣ���ԭ�������ͻ���ִ��󣬱��˾�����Ϊ�������
	//�����˺ܶ��ʱ��
	void tableCellTouched(TableView *table,TableViewCell * cell){}; //���������õ����ǵ��ÿ��cell��ʱ�򴥷��ĺ����������Ұ�����Ϊ�յ�ʵ�֣���Ϊ����ֻ����Ҫ��ȡ�����ļ�¼
	TableViewCell * tableCellAtIndex(TableView * table,ssize_t index);
	Size tableCellSizeForIndex(TableView * table,ssize_t index);
	//3.0�ķ���ֵ������ͬ
	ssize_t numberOfCellsInTableView(TableView * table);
	//�̳�ScrollViewDelegate�ӿ���Ҫ��д�ķ���������ѷ�����ʵ������
	void scrollViewDidScroll(ScrollView * ){};
	void scrollViewDidZoom(ScrollView *){};
	//��android���ؼ�����Ӧ
	void onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent);
private:
	//�豸�ߴ�
	Size size;
};

#endif