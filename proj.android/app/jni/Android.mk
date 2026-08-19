LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := MyGame_shared
LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
                   $(LOCAL_PATH)/../../../Classes/Core.cpp \
                   $(LOCAL_PATH)/../../../Classes/CoreGlobals.cpp \
                   $(LOCAL_PATH)/../../../Classes/Func_Bar.cpp \
                   $(LOCAL_PATH)/../../../Classes/Func_Battle.cpp \
                   $(LOCAL_PATH)/../../../Classes/Func_Cmf.cpp \
                   $(LOCAL_PATH)/../../../Classes/Func_Combat.cpp \
                   $(LOCAL_PATH)/../../../Classes/Func_Demo.cpp \
                   $(LOCAL_PATH)/../../../Classes/Func_Draw.cpp \
                   $(LOCAL_PATH)/../../../Classes/Func_Graphics.cpp \
                   $(LOCAL_PATH)/../../../Classes/Func_Input.cpp \
                   $(LOCAL_PATH)/../../../Classes/Func_Item.cpp \
                   $(LOCAL_PATH)/../../../Classes/Func_Map.cpp \
                   $(LOCAL_PATH)/../../../Classes/Func_Math.cpp \
                   $(LOCAL_PATH)/../../../Classes/Func_Menu.cpp \
                   $(LOCAL_PATH)/../../../Classes/Func_Movement.cpp \
                   $(LOCAL_PATH)/../../../Classes/Func_Net.cpp \
                   $(LOCAL_PATH)/../../../Classes/Content.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/MapLink.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/MapBlob.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/CmfLink.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/CmfBlob.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/DataPackCheck.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/DataCount.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/WaveData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/UIData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/TextData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/SkillData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/ShopData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/RouletteData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/RewardData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/QuestData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/ObjectData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/MapData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/ItemData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/ImgData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/HeroData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/GameData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/GachaData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/FontData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/DropData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/DemoData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/CollectionData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/CmfData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/CastleData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/BattleData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/AlphaData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/EnemyData.cpp \
                   $(LOCAL_PATH)/../../../Classes/Data/DataPack.cpp \
                   $(LOCAL_PATH)/../../../Classes/Func_Object.cpp \
                   $(LOCAL_PATH)/../../../Classes/Func_Roulette.cpp \
                   $(LOCAL_PATH)/../../../Classes/Func_Sound.cpp \
                   $(LOCAL_PATH)/../../../Classes/Func_System.cpp \
                   $(LOCAL_PATH)/../../../Classes/Func_Text.cpp \
                   $(LOCAL_PATH)/../../../Classes/Func_Utility.cpp \
                   $(LOCAL_PATH)/../../../Classes/NativeInterface.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

LOCAL_STATIC_LIBRARIES := cc_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module, cocos)