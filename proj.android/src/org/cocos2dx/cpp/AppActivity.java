/****************************************************************************

Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;

import cn.waps.AdInfo;
import cn.waps.AppConnect;
import cn.waps.UpdatePointsNotifier;
import cn.waps.extend.AppDetail;
import cn.waps.extend.QuitPopAd;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.LinearLayout;

public class AppActivity extends Cocos2dxActivity implements UpdatePointsNotifier{
	
	//用到的一些成员变量
	private static Handler handler; 
	private static Context mContext;
	private String app_id = "0171a39202ff2653c82f4d7ec4cde53a";
	
	protected void onCreate(Bundle savedInstanceState) {
		//先调用父类的onCreate方法
		super.onCreate(savedInstanceState);
		
		//给成员变量赋值
		mContext = this;
		handler = new AdHandler();
		
		initAds();
	}
	
	public void initAds(){
		//初始化广告
		AppConnect.getInstance(app_id,"baidu",this);
		// 预加载插屏广告内容(仅在使用到插屏广告的情况,才需要添加) 
		AppConnect.getInstance(this).initPopAd(this);
		// 预加载自定义广告内容(仅在使用了自定义广告、抽屉广告或迷你广告的情况,才需要添加) 
		AppConnect.getInstance(this).initAdInfo();
	}
	
	protected void onStop(){
		//关闭广告
		AppConnect.getInstance(this).close();
	}

	@Override
	public void getUpdatePoints(String arg0, int arg1) {
	}

	@Override
	public void getUpdatePointsFailed(String arg0) {
	}
	
	// 向handler发送要展示Banner的消息
	public static void showAdStatic(int adTag) {
		Message msg = handler.obtainMessage();
		// 私有静态的整型变量,开发者请自行定义值
		msg.what = adTag; 
		handler.sendMessage(msg); 
	}
	
	//根据传入的id，卸载广告
	public static void uninstallAd(int adTag){
		Message msg = handler.obtainMessage();
		// 私有静态的整型变量,开发者请自行定义值
		msg.what = adTag+100; 
		handler.sendMessage(msg);
	}
	
	class AdHandler extends Handler{
		//保存俩个layout，广告卸载的时候用
		private LinearLayout adBannerLayout=null;
		private LinearLayout adMiniLayout=null;
		
		public void handleMessage(Message msg) {
			switch (msg.what){
			case 0:
				// 显示推荐列表(综合) 
				AppConnect.getInstance(mContext).showOffers(mContext); 
				break;
			case 1:
				// 显示插屏广告
				// 判断插屏广告是否已初始化完成,用于确定是否能成功调用插屏广告 
				boolean hasPopAd = AppConnect.getInstance(mContext).hasPopAd(mContext); 
				if (hasPopAd) {
					AppConnect.getInstance(mContext).showPopAd(mContext); 
				}
				break; 
			case 2:
				// 显示推荐列表(软件) 
				AppConnect.getInstance(mContext).showAppOffers(mContext); 
				break;
			case 3:
				// 显示推荐列表(游戏) 
				AppConnect.getInstance(mContext).showGameOffers(mContext); 
				break;
			case 4:
				// 获取全部自定义广告数据
				break;
			case 5:
				// 获取一条自定义广告数据
				AdInfo adInfo = AppConnect.getInstance(mContext).getAdInfo(); 
				AppDetail.getInstanct().showAdDetail(mContext, adInfo); break;
			case 6:
				// 消费虚拟货币. 
				AppConnect.getInstance(mContext).spendPoints(10,AppActivity.this); 
				break;
			case 7:
				// 奖励虚拟货币 
				AppConnect.getInstance(mContext).awardPoints(10,AppActivity.this); 
				break;
			case 8:
				// 显示自家应用列表 
				AppConnect.getInstance(mContext).showMore(mContext);
				break; 
			case 9:
				// 根据指定的应用app_id展示其详情 
				AppConnect.getInstance(mContext).showMore(mContext,app_id); 
				break;
			case 10:
				// 调用功能广告接口(使用浏览器接口)
				String uriStr = "http://www.baidu.com"; AppConnect.getInstance(mContext).showBrowser(mContext,uriStr); 
				break;
			case 11:
				// 用户反馈
				AppConnect.getInstance(mContext).showFeedback(mContext);
				break; 
			case 12:
				// 退屏广告 
				QuitPopAd.getInstance().show(mContext);
				break;
			case 13:
				// banner
				AppConnect.getInstance(mContext).showBannerAd(mContext,getBannerAd());
				break;
			case 14:
				// 迷你广告
				AppConnect.getInstance(mContext).showMiniAd(mContext,getMiniAd(), 10);
				break;
			default:
				this.uninstallAd(msg.what-100);
				break;
			}
		}
		
		//添加互动广告
		private LinearLayout getBannerAd(){
			// 互动广告
			adBannerLayout = new LinearLayout(mContext);
			adBannerLayout.setOrientation(LinearLayout.VERTICAL);
			FrameLayout.LayoutParams lp_banner = new FrameLayout.LayoutParams(
			FrameLayout.LayoutParams.FILL_PARENT,
			FrameLayout.LayoutParams.WRAP_CONTENT);
			// 设置adBannerLayout的悬浮位置,具体的位置开发者根据需要设置 
			lp_banner.gravity = Gravity.BOTTOM | Gravity.CENTER_HORIZONTAL;
			AppActivity.this.addContentView(adBannerLayout, lp_banner);
			
			LinearLayout bannerLayout = new LinearLayout(mContext); 
			adBannerLayout.addView(bannerLayout);
			
			return bannerLayout;
		}
		
		//添加迷你广告
		private LinearLayout getMiniAd(){
			adMiniLayout = new LinearLayout(mContext); 
			adMiniLayout.setOrientation(LinearLayout.VERTICAL); 
			FrameLayout.LayoutParams lp_mini = new FrameLayout.LayoutParams(
			FrameLayout.LayoutParams.FILL_PARENT,
			FrameLayout.LayoutParams.WRAP_CONTENT);
			// 设置adMiniLayout的悬浮位置,具体的位置开发者根据需要设置 
			lp_mini.gravity = Gravity.TOP | Gravity.CENTER_HORIZONTAL; 
			AppActivity.this.addContentView(adMiniLayout, lp_mini);
			LinearLayout miniLayout = new LinearLayout(mContext); 
			adMiniLayout.addView(miniLayout);
			
			return miniLayout;
		}
		
		//在创建的广告的线程中卸载广告
		public void uninstallAd(int adTag){
			if(adTag == 13){
				adBannerLayout.setVisibility(View.INVISIBLE);
			}
			else if(adTag == 14){
				adMiniLayout.setVisibility(View.INVISIBLE);
			}
		}
	}
}
