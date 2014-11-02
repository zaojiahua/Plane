#ifndef _SCORE_SCENE_H_
#define _SCORE_SCENE_H_
#include "cocos2d.h"
//使用tableview必须包含扩展库
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

//分数榜场景，使用tableview必须继承以下的类
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
	//实现上述接口需要实现的虚函数如下，这里有非常重要的一点就是函数的参数index原来2.x的版本类型为
	//unsigned int而现在改为了ssize_t类型，必须写这个类型，用原来的类型会出现错误，本人就是因为这个错误
	//耽误了很多的时间
	void tableCellTouched(TableView *table,TableViewCell * cell){}; //这里是设置当我们点击每个cell的时候触发的函数，这里我把它置为空的实现，因为我们只是需要读取分数的记录
	TableViewCell * tableCellAtIndex(TableView * table,ssize_t index);
	Size tableCellSizeForIndex(TableView * table,ssize_t index);
	//3.0的返回值有所不同
	ssize_t numberOfCellsInTableView(TableView * table);
	//继承ScrollViewDelegate接口需要覆写的方法，这里把方法的实现留空
	void scrollViewDidScroll(ScrollView * ){};
	void scrollViewDidZoom(ScrollView *){};
	//对android返回键的响应
	void onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent);
private:
	//设备尺寸
	Size size;
};

#endif