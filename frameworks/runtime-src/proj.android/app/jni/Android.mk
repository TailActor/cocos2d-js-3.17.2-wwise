LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
SDK_LIB_DIR := ../../../Classes/wwise/prebuilt/Android/Android_armeabi-v7a/Debug/lib
ifneq ($(AK_CONFIG), Release)
	LOCAL_MODULE            := CommunicationCentral
	LOCAL_SRC_FILES         := $(SDK_LIB_DIR)/libCommunicationCentral.a 
	include $(PREBUILT_STATIC_LIBRARY)
	include $(CLEAR_VARS)
else
	LOCAL_EXPORT_CFLAGS 	+= -DAK_OPTIMIZED
endif

LOCAL_MODULE            := AkMemoryMgr
LOCAL_SRC_FILES         := $(SDK_LIB_DIR)/libAkMemoryMgr.a 
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkSoundEngine
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkSoundEngine.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkMeterFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkMeterFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkMotionGeneratorSource
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkMotionGeneratorSource.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkMotionSink
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkMotionSink.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkMotionSourceSource
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkMotionSourceSource.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkPeakLimiterFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkPeakLimiterFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkHarmonizerFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkHarmonizerFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkStereoDelayFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkStereoDelayFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkMusicEngine
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkMusicEngine.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkTimeStretchFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkTimeStretchFX.a
include $(PREBUILT_STATIC_LIBRARY)

# include $(CLEAR_VARS)
# LOCAL_MODULE            := McDSPLimiterFX
# LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libMcDSPLimiterFX.a
# include $(PREBUILT_STATIC_LIBRARY)

# include $(CLEAR_VARS)
# LOCAL_MODULE            := AkConvolutionReverbFX
# LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkConvolutionReverbFX.a
# include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkCompressorFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkCompressorFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkFlangerFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkFlangerFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkPitchShifterFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkPitchShifterFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkSoundSeedImpactFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkSoundSeedImpactFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkSoundSeedWindSource
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkSoundSeedWindSource.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkSoundSeedWooshSource
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkSoundSeedWooshSource.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkSpatialAudio
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkSpatialAudio.a
include $(PREBUILT_STATIC_LIBRARY)

# include $(CLEAR_VARS)
# LOCAL_MODULE            := McDSPFutzBoxFX
# LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libMcDSPFutzBoxFX.a
# include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkRoomVerbFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkRoomVerbFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkSineSource
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkSineSource.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkSilenceSource
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkSilenceSource.a
include $(PREBUILT_STATIC_LIBRARY)

# include $(CLEAR_VARS)
# LOCAL_MODULE            := AkSynthOne
# LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkSynthOne.a
# include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkParametricEQFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkParametricEQFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkVorbisDecoder
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkVorbisDecoder.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AuroHeadphoneFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAuroHeadphoneFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkToneSource
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkToneSource.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkExpanderFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkExpanderFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkGuitarDistortionFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkGuitarDistortionFX.a
include $(PREBUILT_STATIC_LIBRARY)

# include $(CLEAR_VARS)
# LOCAL_MODULE            := AkSoundSeedWoosh
# LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkSoundSeedWoosh.a
# include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkTremoloFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkTremoloFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkMatrixReverbFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkMatrixReverbFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkStreamMgr
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkStreamMgr.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkDelayFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkDelayFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkAudioInputSource
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkAudioInputSource.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkSynthOneSource
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkSynthOneSource.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkGainFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkGainFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkOpusDecoder
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkOpusDecoder.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkRecorderFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkRecorderFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := AkReflectFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libAkReflectFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := iZHybridReverbFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libiZHybridReverbFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := iZTrashBoxModelerFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libiZTrashBoxModelerFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := iZTrashDelayFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libiZTrashDelayFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := iZTrashDistortionFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libiZTrashDistortionFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := iZTrashDynamicsFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libiZTrashDynamicsFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := iZTrashFiltersFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libiZTrashFiltersFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := iZTrashMultibandDistortionFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libiZTrashMultibandDistortionFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := MasteringSuiteFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libMasteringSuiteFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := McDSPFutzBoxFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libMcDSPFutzBoxFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := McDSPLimiterFX
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libMcDSPLimiterFX.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := zip
LOCAL_SRC_FILES 		:= $(SDK_LIB_DIR)/libzip.a
include $(PREBUILT_STATIC_LIBRARY)


include $(CLEAR_VARS)

LOCAL_MODULE := cocos2djs_shared

LOCAL_MODULE_FILENAME := libcocos2djs

LOCAL_SRC_FILES := hellojavascript/main.cpp \
                   ../../../Classes/AppDelegate.cpp \
                   ../../../proj.win32/libwwise/sceneBase.cpp \
                   ../../../proj.win32/libwwise/WWiseHelper.cpp \
                   ../../../Classes/wwise/SoundEngine/Common/AkMultipleFileLocation.cpp \
                   ../../../Classes/wwise/SoundEngine/Common/AkFilePackageLUT.cpp \
                   ../../../Classes/wwise/SoundEngine/Common/AkFilePackage.cpp \
                   ../../../Classes/wwise/SoundEngine/Common/AkFileLocationBase.cpp \
                   ../../../Classes/wwise/SoundEngine/Common/AkDefaultLowLevelIODispatcher.cpp \
                   ../../../Classes/wwise/SoundEngine/Android/AkDefaultIOHookBlocking.cpp \
                   ../../../Classes/wwise/SoundEngine/Android/AkDefaultIOHookDeferred.cpp \
                   ../../../Classes/wwise/SoundEngine/Android/AkFileHelpers.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes \
                    ../../../Classes/wwise/include \
                    ../../../Classes/wwise/SoundEngine/Common \
                    ../../../Classes/wwise/SoundEngine/Android \
                    ../../../Classes/wwise/SoundEngine/Android/libzip/lib \
                    ../../../proj.win32 \
                    ../../../proj.win32/libwwise

LOCAL_STATIC_LIBRARIES := ccjs_static
LOCAL_STATIC_LIBRARIES += AkAudioInputSource
LOCAL_STATIC_LIBRARIES += AkCompressorFX
LOCAL_STATIC_LIBRARIES += AkDelayFX
LOCAL_STATIC_LIBRARIES += AkExpanderFX
LOCAL_STATIC_LIBRARIES += AkFlangerFX
LOCAL_STATIC_LIBRARIES += AkGainFX
LOCAL_STATIC_LIBRARIES += AkGuitarDistortionFX
LOCAL_STATIC_LIBRARIES += AkHarmonizerFX
LOCAL_STATIC_LIBRARIES += AkMatrixReverbFX
LOCAL_STATIC_LIBRARIES += AkMemoryMgr
LOCAL_STATIC_LIBRARIES += AkMeterFX
LOCAL_STATIC_LIBRARIES += AkMotionGeneratorSource
LOCAL_STATIC_LIBRARIES += AkMotionSink
LOCAL_STATIC_LIBRARIES += AkMotionSourceSource
LOCAL_STATIC_LIBRARIES += AkMusicEngine
LOCAL_STATIC_LIBRARIES += AkOpusDecoder
LOCAL_STATIC_LIBRARIES += AkParametricEQFX
LOCAL_STATIC_LIBRARIES += AkPeakLimiterFX
LOCAL_STATIC_LIBRARIES += AkPitchShifterFX
LOCAL_STATIC_LIBRARIES += AkRecorderFX
LOCAL_STATIC_LIBRARIES += AkReflectFX
LOCAL_STATIC_LIBRARIES += AkRoomVerbFX
LOCAL_STATIC_LIBRARIES += AkSilenceSource
LOCAL_STATIC_LIBRARIES += AkSineSource
LOCAL_STATIC_LIBRARIES += AkSoundEngine
LOCAL_STATIC_LIBRARIES += AkSoundSeedImpactFX
LOCAL_STATIC_LIBRARIES += AkSoundSeedWindSource
LOCAL_STATIC_LIBRARIES += AkSoundSeedWooshSource
LOCAL_STATIC_LIBRARIES += AkSpatialAudio
LOCAL_STATIC_LIBRARIES += AkStereoDelayFX
LOCAL_STATIC_LIBRARIES += AkStreamMgr
LOCAL_STATIC_LIBRARIES += AkSynthOneSource
LOCAL_STATIC_LIBRARIES += AkTimeStretchFX
LOCAL_STATIC_LIBRARIES += AkToneSource
LOCAL_STATIC_LIBRARIES += AkTremoloFX
LOCAL_STATIC_LIBRARIES += AkVorbisDecoder
LOCAL_STATIC_LIBRARIES += AuroHeadphoneFX
LOCAL_STATIC_LIBRARIES += AkSynthOneSource
LOCAL_STATIC_LIBRARIES += AkStereoDelayFX
LOCAL_STATIC_LIBRARIES += iZHybridReverbFX
LOCAL_STATIC_LIBRARIES += iZTrashBoxModelerFX
LOCAL_STATIC_LIBRARIES += iZTrashDelayFX
LOCAL_STATIC_LIBRARIES += iZTrashDistortionFX
LOCAL_STATIC_LIBRARIES += iZTrashDynamicsFX
LOCAL_STATIC_LIBRARIES += iZTrashFiltersFX
LOCAL_STATIC_LIBRARIES += iZTrashMultibandDistortionFX
LOCAL_STATIC_LIBRARIES += MasteringSuiteFX
LOCAL_STATIC_LIBRARIES += McDSPFutzBoxFX
LOCAL_STATIC_LIBRARIES += McDSPLimiterFX
LOCAL_STATIC_LIBRARIES += zip

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_DEBUG=2 -DCOCOS2D_JAVASCRIPT

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, ../../../../cocos2d-x)
$(call import-add-path, ../../../../cocos2d-x/cocos)
$(call import-add-path, ../../../../cocos2d-x/external)
# $(call import-add-path, ../../../Classes/wwise/SoundEngine/Android)

$(call import-module, scripting/js-bindings/proj.android)
# $(call import-module, libzip/lib)