﻿#include "cocos2d.h"
//#ifdef 	COCOS_INTEGRATION
//#include "cocos2d.h"
//#else
//#include <stdio.h>  // vsprintf...
//#endif // COCOS_INTEGRATION
#include "avg_log.h"
#include "WWiseHelper.h"
#include <AK/Wwise_IDs.h>
#include <AK/SoundEngine/Common/AkTypes.h>
#include <wchar.h>

#ifdef AK_IOS
#include "SoundInput.h"
#include "Platform.h"
#endif // AK_IOS
#ifndef AK_OPTIMIZED
#include <AK/Comm/AkCommunication.h> // Communication between Wwise and the game (excluded in release build)
#endif // AK_OPTIMIZED
#ifdef AK_MOTION
#include <AK/MotionEngine/Common/AkMotionEngine.h>	// Motion Engine (required only for playback of Motion objects)
#endif // AK_MOTION

#ifdef AK_ANDROID
#include "android/asset_manager.h"
#include <android/log.h>
//#define  ANDROID_LOG_DEBUG    "Wwise"
#define  LOG_TAG    "Wwise"
#define __AK_OSCHAR_SNPRINTF 	snprintf
#define  LOGAK(...)  		__android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
void LOGAKW(AkOSChar* _Buffer)
{
	char szBuff[1024] = { 0 };
	AKPLATFORM::AkWideCharToChar((const wchar_t*)_Buffer, 1024, szBuff);
	//__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, (const char*)&szBuff);
	__android_log_print(ANDROID_LOG_DEBUG, "LOGAKW : ", "%s", (const char*)&szBuff);
	//LOGAK((const char*)szBuff);
}
#elif WIN32
#define __AK_OSCHAR_SNPRINTF    	_snwprintf
#pragma warning(disable:4996)   // to avoid C4996	'_snwprintf': This function or variable may be unsafe. Consider using _snwprintf_s instead.
void LOGAK(char* format, ...)
{
	char buffer[1000];

	va_list argptr;
	va_start(argptr, format);
	vsprintf_s(buffer, format, argptr);
	va_end(argptr);
	OutputDebugStringA(buffer);
}
void LOGAKW(TCHAR* format, ...)
{
	TCHAR buffer[1000];

	va_list argptr;
	va_start(argptr, format);
	wvsprintf(buffer, format, argptr);
	va_end(argptr);
	OutputDebugString(buffer);
}
#elif defined(AK_APPLE) //__APPLE__
#define __AK_OSCHAR_SNPRINTF
//#define  LOGAK                      CCLOG
//#define  LOGAKW                     CCLOG
#else
#error undefied platform
#endif

// Ak core libs
//#if defined(WIN32)
//#pragma comment( lib, "AkMemoryMgr")
//#pragma comment( lib, "AkSoundEngine")
//#pragma comment( lib, "AkStreamMgr")
//#pragma comment( lib, "AkMusicEngine")
//#pragma comment( lib, "dxguid.lib")	//DirectSound
//#ifdef _DEBUG    
//#pragma comment( lib, "CommunicationCentral")
//#endif
//#endif
//// plugins
//#define AK_PLUGINS
//#include <AK/Plugin/AllPluginsRegistrationHelpers.h>	// Plug-ins
//#if defined(WIN32)
////#pragma comment( lib, "AkConvolutionReverbFX.lib")
//#pragma comment( lib, "AkFlangerFX.lib")
//#pragma comment( lib, "AkTremoloFX.lib")
//#pragma comment( lib, "AuroHeadphoneFX.lib")
////#pragma comment( lib, "IOSONOProximityMixer.lib")
////#pragma comment( lib, "AkMotionGenerator.lib")
//#pragma comment( lib, "AkSineSource.lib")
////#pragma comment( lib, "AkSoundSeedWind.lib")
//#pragma comment( lib, "AkStereoDelayFX.lib")
//#pragma comment( lib, "AkGuitarDistortionFX.lib")
////#pragma comment( lib, "AkRumble.lib")
//#pragma comment( lib, "AkSilenceSource.lib")
////#pragma comment( lib, "AuroPannerMixer.lib")
//#pragma comment( lib, "AkPeakLimiterFX.lib")
//#pragma comment( lib, "iZTrashBoxModelerFX.lib")
//#pragma comment( lib, "AkSoundSeedImpactFX.lib")
//#pragma comment( lib, "AkRoomVerbFX.lib")
//#pragma comment( lib, "iZTrashDelayFX.lib")
//#pragma comment( lib, "McDSPLimiterFX.lib")
//#pragma comment( lib, "McDSPFutzBoxFX.lib")
//#pragma comment( lib, "AkParametricEQFX.lib")
//#pragma comment( lib, "AkToneSource.lib")
//#pragma comment( lib, "AkMatrixReverbFX.lib")
//#pragma comment( lib, "AkCompressorFX.lib")
//#pragma comment( lib, "AkAudioInputSource.lib")
////#pragma comment( lib, "AkSoundSeedWoosh.lib")
////#pragma comment( lib, "CrankcaseAudioREVModelPlayerFX.lib")
//#pragma comment( lib, "iZTrashMultibandDistortionFX.lib")
//#pragma comment( lib, "iZHybridReverbFX.lib")
//#pragma comment( lib, "AkPitchShifterFX.lib")
//#pragma comment( lib, "iZTrashDynamicsFX.lib")
//#pragma comment( lib, "iZTrashDistortionFX.lib")
//#pragma comment( lib, "AkDelayFX.lib")
//#pragma comment( lib, "AkGainFX.lib")
//#pragma comment( lib, "AkVorbisDecoder.lib")
//#pragma comment( lib, "AkMeterFX.lib")
//#pragma comment( lib, "iZTrashFiltersFX.lib")
////#pragma comment( lib, "AkSynthOne.lib")
////#pragma comment( lib, "AkMP3Source.lib")
//#pragma comment( lib, "AkHarmonizerFX.lib")
//#pragma comment( lib, "AkTimeStretchFX.lib")
//#pragma comment( lib, "AkExpanderFX.lib")
//#pragma comment( lib, "Msacm32.lib") // Microsoft ACM Library
//#endif

#if defined(WIN32)
#pragma comment( lib, "AkAudioInputSource")
#pragma comment( lib, "AkAutobahn")
#pragma comment( lib, "AkCompressorFX")
#pragma comment( lib, "AkDelayFX")
#pragma comment( lib, "dxguid.lib")	//DirectSound
#pragma comment( lib, "CommunicationCentral")
#pragma comment( lib, "AkExpanderFX")
#endif
// plugins
#define AK_PLUGINS
#include <AK/Plugin/AllPluginsRegistrationHelpers.h>	// Plug-ins
#if defined(WIN32)
#pragma comment( lib, "AkFlangerFX")
#pragma comment( lib, "AkGainFX")
#pragma comment( lib, "AkGuitarDistortionFX")
#pragma comment( lib, "AkHarmonizerFX")
#pragma comment( lib, "AkMatrixReverbFX")
#pragma comment( lib, "AkMemoryMgr")
#pragma comment( lib, "AkMeterFX")
#pragma comment( lib, "AkMotionGeneratorSource")
#pragma comment( lib, "AkMotionSink")
#pragma comment( lib, "AkMotionSourceSource")
#pragma comment( lib, "AkMusicEngine")
#pragma comment( lib, "AkOpusDecoder")
#pragma comment( lib, "AkParametricEQFX")
#pragma comment( lib, "AkPeakLimiterFX")
#pragma comment( lib, "AkPitchShifterFX")
#pragma comment( lib, "AkRecorderFX")
#pragma comment( lib, "AkReflectFX")
#pragma comment( lib, "AkRoomVerbFX")
#pragma comment( lib, "AkSilenceSource")
#pragma comment( lib, "AkSineSource")
#pragma comment( lib, "AkSoundEngine")
#pragma comment( lib, "AkSoundSeedImpactFX")
#pragma comment( lib, "AkSoundSeedWindSource")
#pragma comment( lib, "AkSoundSeedWooshSource")
#pragma comment( lib, "AkSpatialAudio")
#pragma comment( lib, "AkStereoDelayFX")
#pragma comment( lib, "AkStreamMgr")
#pragma comment( lib, "AkSynthOneSource")
#pragma comment( lib, "AkTimeStretchFX")
#pragma comment( lib, "AkToneSource")
#pragma comment( lib, "AkTremoloFX")
#pragma comment( lib, "AkVorbisDecoder")
#pragma comment( lib, "AuroHeadphoneFX")
#pragma comment( lib, "iZHybridReverbFX")
#pragma comment( lib, "iZTrashBoxModelerFX")
#pragma comment( lib, "iZTrashDelayFX")
#pragma comment( lib, "iZTrashDistortionFX")
#pragma comment( lib, "iZTrashDynamicsFX")
#pragma comment( lib, "iZTrashFiltersFX")
#pragma comment( lib, "MasteringSuiteFX")
#pragma comment( lib, "McDSPFutzBoxFX")
#pragma comment( lib, "McDSPLimiterFX")
#pragma comment( lib, "Msacm32.lib") // Microsoft ACM Library
#pragma comment( lib, "SFLib")
#endif

static const AkUInt32 kMaxNumPools = 20;
static const AkUInt32 kDefaultPoolSize = 2 * 1024 * 1024;
static const AkUInt32 kLEngineDefaultPoolSize = 1 * 1024 * 1024;

#ifdef AK_WIN
#ifdef _DEBUG
#define MY_SOUND_BANK_PATH L"E://proj//WwiseProjects//WwiseDemo2//GeneratedSoundBanks//Windows//"  // Please change this path to yours
//#define MY_SOUND_BANK_PATH L"E:\\proj\\WwiseProjects\\WwiseDemo\\GeneratedSoundBanks\\Windows"
#else
#define MY_SOUND_BANK_PATH L"Wwise/"
#endif
#elif defined AK_ANDROID
//const AkOSChar MY_SOUND_BANK_PATH[] = AKTEXT("/data/data/com.example.cocos_sdk_demo/files");
const AkOSChar MY_SOUND_BANK_PATH[] = AKTEXT("res");
#elif defined AK_APPLE
#include "TargetConditionals.h"
#if TARGET_OS_IPHONE
// iOS
#define MY_SOUND_BANK_PATH g_szBasePath //"iOS/"
#else
// MacOS
#define MY_SOUND_BANK_PATH "Mac/"
#endif
#else
#error undefied platform
#endif

#ifdef AK_IOS
AkAudioSessionCategoryOptions GetAudioSessionCategoryOptionBitMask(bool in_bMixWithOthers, bool in_bDuckOthers, bool in_bAllowBluetooth, bool in_bDefaultToSpeaker)
{
	AkInt32 mask = 0;
	if (in_bMixWithOthers)
	{
		mask |= (1 << 0);
	}
	else
	{
		mask |= (0 << 0);
	}

	if (in_bDuckOthers)
	{
		mask |= (1 << 1);
	}
	else
	{
		mask |= (0 << 1);
	}

	if (in_bAllowBluetooth)
	{
		mask |= (1 << 2);
	}
	else
	{
		mask |= (0 << 2);
	}

	if (in_bDefaultToSpeaker)
	{
		mask |= (1 << 3);
	}
	else
	{
		mask |= (0 << 3);
	}

	return (AkAudioSessionCategoryOptions)mask;
}

static AKRESULT DemoInterruptCallback(bool in_bEnterInterruption, void* in_pCookie)
{
	// Be careful with any pause/resume events posted in this callback, along with those
	// posted in other user callbacks. The interruption and source change notifications
	// on iOS can happen on top of each other, causing some of the events to miss being
	// processed.
	// E.g., There is no need for pause/resume here because suspend/wakeup will be called
	// in the sound engine, taking care of pauses/resumes automatically.
	if (in_bEnterInterruption)
	{
		//        NSLog(@"IntegrationDemo: Interruption: User callback, before interruption happens.");
	}
	else
	{
		// This case is called after the user dismisses the interruption from phone calls or alarms.
		// However, it is not called if the interruption is from remote-controlled music app.
		// It is handled by source change callback.
		//       NSLog(@"IntegrationDemo: Interruption: User callback, after interruption is done.");
	}

	return AK_Success;
}
#endif

// Custom alloc/free functions. These are declared as "extern" in AkMemoryMgr.h
// and MUST be defined by the game developer.
namespace AK
{
#ifndef AK_MAC
	void* AllocHook(size_t in_size)
	{
		return malloc(in_size);
	}
	void FreeHook(void* in_ptr)
	{
		free(in_ptr);
	}
#endif
#ifdef WIN32
	// Note: VirtualAllocHook() may be used by I/O pools of the default implementation
	// of the Stream Manager, to allow "true" unbuffered I/O (using FILE_FLAG_NO_BUFFERING
	// - refer to the Windows SDK documentation for more details). This is NOT mandatory;
	// you may implement it with a simple malloc().
	void* VirtualAllocHook(
		void* in_pMemAddress,
		size_t in_size,
		AkUInt32 in_dwAllocationType,
		AkUInt32 in_dwProtect
	)
	{
		return VirtualAlloc(in_pMemAddress, in_size, in_dwAllocationType, in_dwProtect);
	}

	void VirtualFreeHook(
		void* in_pMemAddress,
		size_t in_size,
		AkUInt32 in_dwFreeType
	)
	{
		VirtualFree(in_pMemAddress, in_size, in_dwFreeType);
	}
#endif
}

namespace {
	//	Wwise		    m_wwise;
	AkMemSettings	    m_memSettings;
	AkStreamMgrSettings	    m_stmSettings;
	AkDeviceSettings	    m_deviceSettings;
	AkInitSettings	    m_initSettings;
	AkPlatformInitSettings  m_platformInitSettings;
	AkMusicSettings	    m_musicInit;
	AkOSChar		    m_strError[1024];
}

namespace WWISE {
	bool initialize(void* mgr, AkOSChar* strBankpath)
	{
		mylog("<Wwise::Init> start 000");
		Wwise::Instance().GetDefaultSettings(m_memSettings, m_stmSettings, m_deviceSettings, m_initSettings, m_platformInitSettings, m_musicInit);
#ifdef AK_ANDROID
		//Wwise::Instance().GetLowLevelIOHandler()->SetAssetManager((AAssetManager*)mgr);
		JavaVM* jvm = cocos2d::JniHelper::getJavaVM();
		if (!jvm)
		{
			LOGAK("<Wwise::Init> Failed to get JVM. Aborted.");
			return false;
		}
		m_platformInitSettings.pJavaVM = jvm;
		// Get activity.
		JNIEnv* env = cocos2d::JniHelper::getEnv();
		if (!env)
		{
			LOGAK("<Wwise::Init> Failed to get JNIEnv to retrieve Activity. Aborted.");
			return false;
		}
		//jclass classID = env->FindClass("org/cocos2dx/cpp/AppActivity");
		//jclass classID = env->FindClass("com/example/cocos_sdk_demo/MainActivity");
		jclass classID = env->FindClass("org/cocos2dx/lib/Cocos2dxActivity");
		if (!classID)
		{
			LOGAK("<Wwise::Init> Failed to find class AppActivity to retrieve Activity. Aborted.");
			return false;
		}
		mylog("<Wwise::Init> start 111");
		jmethodID methodID = env->GetStaticMethodID(classID, "getInstance", "()Ljava/lang/Object;");
		if (!methodID)
		{
			LOGAK("<Wwise::Init> Failed to find method getInstance to retrieve Activity. Aborted.");
			return false;
		}
		mylog("<Wwise::Init> start 222");
		m_platformInitSettings.jActivity = env->CallStaticObjectMethod(classID, methodID);
		mylog("<Wwise::Init> start 333");
		// Wwise::Instance().GetLowLevelIOHandler()->InitAndroidIO(m_platformInitSettings.pJavaVM, m_platformInitSettings.jActivity);
#endif
		mylog("<Wwise::Init> start 444");
		const AkOSChar* pstrBankpath = (AkOSChar*)strBankpath ? strBankpath : MY_SOUND_BANK_PATH;
		mylog("<Wwise::Init> start");
		if (!Wwise::Instance().Init(m_memSettings, m_stmSettings, m_deviceSettings, m_initSettings, m_platformInitSettings, m_musicInit,
			(AkOSChar*)pstrBankpath, m_strError, sizeof(m_strError))) {
			mylog("<Wwise::Init> failed");
			LOGAKW(m_strError);
			abort();
		}
		mylog("<Wwise::Init> success");

		AK::SoundEngine::SetRTPCValue(AK::GAME_PARAMETERS::RPM, (AkRtpcValue)255);

		return true;
	}
	void terminate()
	{
		Wwise::Instance().Term();
	}
	void update()
	{
		AK::SoundEngine::RenderAudio();
	}
}

Wwise& Wwise::Instance()
{
	static Wwise wwise;
	return wwise;
}

Wwise::Wwise() {
	m_pLowLevelIO = new CAkFilePackageLowLevelIOBlocking();
}

Wwise::~Wwise()
{
	delete m_pLowLevelIO;
	m_pLowLevelIO = NULL;
}

CAkFilePackageLowLevelIOBlocking& Wwise::IOManager()
{
	return *m_pLowLevelIO;
}

bool Wwise::Init(AkMemSettings& in_memSettings,
	AkStreamMgrSettings& in_stmSettings,
	AkDeviceSettings& in_deviceSettings,
	AkInitSettings& in_initSettings,
	AkPlatformInitSettings& in_platformInitSettings,
	AkMusicSettings& in_musicInit,
	AkOSChar* in_soundBankPath,
	AkOSChar* in_szErrorBuffer,
	unsigned int            in_unErrorBufferCharCount)
{
	bool bSuccess;
	AKRESULT hr;
	AKRESULT ret;
	std::string path;
#if  defined(AK_IOS)
	// Allow other applications to play sounds while the integration demo executes.
	in_platformInitSettings.audioSession.eCategory = AkAudioSessionCategoryPlayAndRecord;
	//	platformInitSettings.audioSession.eCategory = AkAudioSessionCategorySoloAmbient;
	//	platformInitSettings.audioSession.eCategory = AkAudioSessionCategoryAmbient;

	if (in_platformInitSettings.audioSession.eCategory == AkAudioSessionCategoryPlayAndRecord)
	{
		g_bEnableMicDemo = true;
		in_platformInitSettings.audioSession.eCategoryOptions = GetAudioSessionCategoryOptionBitMask(true, false, true, true);
	}
	else
	{
		g_bEnableMicDemo = false;
		in_platformInitSettings.audioSession.eCategoryOptions = GetAudioSessionCategoryOptionBitMask(true, true, false, false);
	}

	// Optimization.
	in_platformInitSettings.uSampleRate = AUDIO_SAMPLE_RATE;
	g_uSamplesPerFrame = in_initSettings.uNumSamplesPerFrame;

	in_platformInitSettings.audioCallbacks.inputCallback = SoundInput::AudioInputCallback;
	in_platformInitSettings.audioCallbacks.inputCallbackCookie = (void*)&SoundInput::Instance();

	in_platformInitSettings.audioCallbacks.interruptionCallback = DemoInterruptCallback;
#endif

	// my
#ifdef AK_ANDROID
	m_pLowLevelIO->Init(in_platformInitSettings.pJavaVM, in_platformInitSettings.jActivity);
#endif
	// end my

	// Initialize Wwise
	bSuccess = InitWwise(in_memSettings, in_stmSettings, in_deviceSettings, in_initSettings, in_platformInitSettings, in_musicInit, in_szErrorBuffer, in_unErrorBufferCharCount);
	if (!bSuccess) {
		mylog("Wwise::Init InitWwise failed");
		goto cleanup;
	}

	mylog("Wwise::Init in_soundBankPath : %s", in_soundBankPath);

	// Set the path to the SoundBank Files.
	hr = m_pLowLevelIO->SetBasePath(in_soundBankPath);
	if (hr != AK_Success) {
		mylog("Wwise::Init SetBasePath failed");
	} else {
		mylog("Wwise::Init SetBasePath success");
	}

	// Set global language. Low-level I/O devices can use this string to find language-specific assets.
	//if (AK::StreamMgr::SetCurrentLanguage(AKTEXT("English(US)")) != AK_Success)
	//{
	//	mylog("Wwise::Init SetCurrentLanguage failed");
	//	goto cleanup;
	//} else {
	//	mylog("Wwise::Init SetCurrentLanguage success");
	//}

	path = std::string((char*)in_soundBankPath) + "/Init.bnk";
	mylog("Wwise::Init isFileExist path : %s", path.data());
	if (cocos2d::FileUtils::getInstance()->isFileExist(path)) {
		mylog("Wwise::Init isFileExist true");
	} else {
		mylog("Wwise::Init isFileExist false");
	}

	AkBankID bankID;
	//if (AK::SoundEngine::LoadBank("Init.bnk", AK_DEFAULT_POOL_ID, bankID) != AK_Success)
	ret = AK::SoundEngine::LoadBank("Init.bnk", bankID);
	//ret = AK::SoundEngine::LoadBank(path.data(), bankID);
	if (ret != AK_Success)
	{
		//SetLoadFileErrorMessage("Init.bnk");
		//LOGAK("<Wwise::Init> Cannot load Init.bnk! error");
//#ifdef 	COCOS_INTEGRATION
//		cocos2d::MessageBox("Cannot load Init.bnk!", "Error");
//#endif
		mylog("Wwise::Init LoadBank Init.bnk failed ret : %d", ret);
		return false;
	}

	mylog("Wwise::Init LoadBank Init.bnk success");
	return true;

cleanup:
	Term();
	return false;
}

void Wwise::Term()
{
	TermWwise();
}

void Wwise::GetDefaultSettings(AkMemSettings& out_memSettings,
	AkStreamMgrSettings& out_stmSettings,
	AkDeviceSettings& out_deviceSettings,
	AkInitSettings& out_initSettings,
	AkPlatformInitSettings& out_platformInitSettings,
	AkMusicSettings& out_musicInit)
{
	AK::MemoryMgr::GetDefaultSettings(out_memSettings);

	//out_memSettings.uMaxNumPools = kMaxNumPools;
	AK::StreamMgr::GetDefaultSettings(out_stmSettings);

	AK::StreamMgr::GetDefaultDeviceSettings(out_deviceSettings);

	AK::SoundEngine::GetDefaultInitSettings(out_initSettings);
	//out_initSettings.uDefaultPoolSize = kDefaultPoolSize;

	AK::SoundEngine::GetDefaultPlatformInitSettings(out_platformInitSettings);
	//out_platformInitSettings.uLEngineDefaultPoolSize = kLEngineDefaultPoolSize;

	AK::MusicEngine::GetDefaultInitSettings(out_musicInit);
}

const bool Wwise::GetCommunicationEnabled() {
#if !defined AK_OPTIMIZED && !defined INTEGRATIONDEMO_DISABLECOMM
	return true;
#else
	return false;
#endif
}

bool Wwise::InitWwise(AkMemSettings& in_memSettings,
	AkStreamMgrSettings& in_stmSettings,
	AkDeviceSettings& in_deviceSettings,
	AkInitSettings& in_initSettings,
	AkPlatformInitSettings& in_platformInitSettings,
	AkMusicSettings& in_musicInit,
	AkOSChar* in_szErrorBuffer,
	unsigned int            in_unErrorBufferCharCount)
{
	//
	// Create and initialize an instance of the default memory manager. Note
	// that you can override the default memory manager with your own. Refer
	// to the SDK documentation for more information.
	//

	AKRESULT res = AK::MemoryMgr::Init(&in_memSettings);
	if (res != AK_Success)
	{
		mylog("Wwise::InitWwise MemoryMgr::Init failed");
		__AK_OSCHAR_SNPRINTF(in_szErrorBuffer, in_unErrorBufferCharCount, AKTEXT("AK::MemoryMgr::Init() returned AKRESULT %d"), res);
		LOGAKW(in_szErrorBuffer);
		return false;
	}

	//
	// Create and initialize an instance of the default streaming manager. Note
	// that you can override the default streaming manager with your own. Refer
	// to the SDK documentation for more information.
	//

	// Customize the Stream Manager settings here.

	if (!AK::StreamMgr::Create(in_stmSettings))
	{
		mylog("Wwise::InitWwise StreamMgr::Create failed");
		AKPLATFORM::SafeStrCpy(in_szErrorBuffer, AKTEXT("AK::StreamMgr::Create() failed"), in_unErrorBufferCharCount);
		LOGAKW(in_szErrorBuffer);
		return false;
	}

	//
	// Create a streaming device with blocking low-level I/O handshaking.
	// Note that you can override the default low-level I/O module with your own. Refer
	// to the SDK documentation for more information.
	//

	// CAkFilePackageLowLevelIOBlocking::Init() creates a streaming device
	// in the Stream Manager, and registers itself as the File Location Resolver.
	res = m_pLowLevelIO->Init(in_deviceSettings);
	if (res != AK_Success)
	{
		mylog("Wwise::InitWwise m_pLowLevelIO->Init failed");
		__AK_OSCHAR_SNPRINTF(in_szErrorBuffer, in_unErrorBufferCharCount, AKTEXT("m_lowLevelIO.Init() returned AKRESULT %d"), res);
		LOGAKW(in_szErrorBuffer);
		return false;
	}

	//
	// Create the Sound Engine
	// Using default initialization parameters
	//

	res = AK::SoundEngine::Init(&in_initSettings, &in_platformInitSettings);
	if (res != AK_Success)
	{
		mylog("Wwise::InitWwise SoundEngine::Init failed");
		__AK_OSCHAR_SNPRINTF(in_szErrorBuffer, in_unErrorBufferCharCount, AKTEXT("AK::SoundEngine::Init() returned AKRESULT %d"), res);
		LOGAKW(in_szErrorBuffer);
		return false;
	}

	//
	// Initialize the music engine
	// Using default initialization parameters
	//

	res = AK::MusicEngine::Init(&in_musicInit);
	if (res != AK_Success)
	{
		mylog("Wwise::InitWwise MusicEngine::Init failed");
		__AK_OSCHAR_SNPRINTF(in_szErrorBuffer, in_unErrorBufferCharCount, AKTEXT("AK::MusicEngine::Init() returned AKRESULT %d"), res);
		LOGAKW(in_szErrorBuffer);
		return false;
	}

#if defined(NDK_DEBUG) || defined(AK_DEBUG) || defined(_DEBUG)
	//
	// Initialize communications (not in release build!)
	//
	if (GetCommunicationEnabled()) {
		AkCommSettings commSettings;
		AK::Comm::GetDefaultInitSettings(commSettings);
		res = AK::Comm::Init(commSettings);
		if (res != AK_Success)
		{
			mylog("Wwise::InitWwise Comm::Init failed");
			__AK_OSCHAR_SNPRINTF(in_szErrorBuffer, in_unErrorBufferCharCount, AKTEXT("AK::Comm::Init() returned AKRESULT %d. Communication between the Wwise authoring application and the game will not be possible."), res);
			LOGAKW(in_szErrorBuffer);
		}
	}
#endif

#ifdef AK_PLUGINS
	//
	// Register plugins
	/// Note: This a convenience method for rapid prototyping.
	/// To reduce executable code size register/link only the plug-ins required by your game
	res = AK::SoundEngine::RegisterAllPlugins();
	if (res != AK_Success)
	{
		mylog("Wwise::InitWwise SoundEngine::RegisterAllPlugins failed");
		__AK_OSCHAR_SNPRINTF(in_szErrorBuffer, in_unErrorBufferCharCount, AKTEXT("AK::SoundEngine::RegisterAllPlugins() returned AKRESULT %d."), res);
	}
#endif

	mylog("Wwise::InitWwise success");
	return true;
}

void Wwise::TermWwise()
{
	//#ifndef AK_OPTIMIZED
#if defined(NDK_DEBUG) || defined(AK_DEBUG) || defined(_DEBUG)
	// Terminate communications between Wwise and the game
	if (GetCommunicationEnabled()) {
		AK::Comm::Term();
	}
#endif
	// Terminate the music engine
	AK::MusicEngine::Term();

	// Terminate the sound engine
	if (AK::SoundEngine::IsInitialized())
	{
		AK::SoundEngine::Term();
	}

	// Terminate the streaming device and streaming manager
	// CAkFilePackageLowLevelIOBlocking::Term() destroys its associated streaming device 
	// that lives in the Stream Manager, and unregisters itself as the File Location Resolver.
	if (AK::IAkStreamMgr::Get())
	{
		m_pLowLevelIO->Term();
		AK::IAkStreamMgr::Get()->Destroy();
	}

	// Terminate the Memory Manager
	if (AK::MemoryMgr::IsInitialized())
	{
		AK::MemoryMgr::Term();
	}

}
