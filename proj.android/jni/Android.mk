LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/StartGame.cpp \
                   ../../Classes/MainGame.cpp \
                   ../../Classes/ScoreScene.cpp \
                   ../../Classes/GameOver.cpp \
		   ../../Classes/Pause.cpp \
		   ../../Classes/AboutMe.cpp \
                   ../../Classes/Layer/Background.cpp \
		   ../../Classes/Layer/UILayer.cpp \
                   ../../Classes/Player/Player.cpp \
                   ../../Classes/Enemy/EnemyBase.cpp \
                   ../../Classes/Bullet/Bullet.cpp \
                   ../../Classes/Manager/Manager.cpp \
                   ../../Classes/Ufo/Ufo.cpp \
                   ../../Classes/SaveData/SaveData.cpp \
                   ../../Classes/Sound/Sound.cpp \
                  
                   
		

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
				    $(LOCAL_PATH)/../../cocos2d/extensions \

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,2d)
$(call import-module,audio/android)
$(call import-module,Box2D)
$(call import-module,extensions)