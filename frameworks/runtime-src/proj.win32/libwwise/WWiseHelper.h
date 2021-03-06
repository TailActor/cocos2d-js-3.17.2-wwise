#pragma once

#include <AK/SoundEngine/Common/AkTypes.h>
#include <AK/SoundEngine/Common/AkMemoryMgr.h>		// Memory Manager
#include <AK/SoundEngine/Common/AkModule.h>		// Default memory and stream managers
#include <AK/SoundEngine/Common/IAkStreamMgr.h>		// Streaming Manager
#include <AK/SoundEngine/Common/AkSoundEngine.h>	// Sound engine
#include <AK/MusicEngine/Common/AkMusicEngine.h>	// Music Engine
#include <AK/SoundEngine/Common/AkStreamMgrModule.h>	// AkStreamMgrModule
//#include "../../WwiseProject/GeneratedSoundBanks/Wwise_IDs.h"// IDs generated by Wwise

#ifndef AK_OPTIMIZED
#include <AK/Comm/AkCommunication.h>			// Communication between Wwise and the game (excluded in release build)
#endif

#ifdef AK_ANDROID
#include "../../Classes/wwise/SoundEngine/Android/AkFilePackageLowLevelIOBlocking.h"
#elif defined AK_APPLE
#include "../../../SoundEngine/POSIX/AkFilePackageLowLevelIOBlocking.h"// Low level io
#define  LOGAK                      CCLOG
#define  LOGAKW                     CCLOG
#else
#include "AkFilePackageLowLevelIOBlocking.h"  // $(WWISESDK)\samples\SoundEngine\Win32
#endif


namespace WWISE {
	bool initialize(void* mgr, AkOSChar* pstrBankpath = NULL);
	void terminate();
	void update();
}


class Wwise
{
public:
	static Wwise& Instance();
	CAkFilePackageLowLevelIOBlocking& IOManager();
	CAkFilePackageLowLevelIOBlocking* GetLowLevelIOHandler() { return m_pLowLevelIO; }

	void GetDefaultSettings(AkMemSettings& out_memSettings,
		AkStreamMgrSettings& out_stmSettings,
		AkDeviceSettings& out_deviceSettings,
		AkInitSettings& out_initSettings,
		AkPlatformInitSettings& out_platformInitSettings,
		AkMusicSettings& out_musicInit);

	void Term();

	bool Init(AkMemSettings& in_memSettings,
		AkStreamMgrSettings& in_stmSettings,
		AkDeviceSettings& in_deviceSettings,
		AkInitSettings& in_initSettings,
		AkPlatformInitSettings& in_platformInitSettings,
		AkMusicSettings& in_musicInit,
		AkOSChar* in_soundBankPath,
		AkOSChar* in_szErrorBuffer,         ///< - Buffer where error details will be written (if the function returns false)
		unsigned int            in_unErrorBufferCharCount ///< - Number of characters available in in_szErrorBuffer, including terminating NULL character
	);

	const bool GetCommunicationEnabled();

private:
	Wwise();
	Wwise(Wwise const&) {};
	Wwise& operator=(Wwise const&);
	~Wwise();

	bool InitWwise(AkMemSettings& in_memSettings,
		AkStreamMgrSettings& in_stmSettings,
		AkDeviceSettings& in_deviceSettings,
		AkInitSettings& in_initSettings,
		AkPlatformInitSettings& in_platformInitSettings,
		AkMusicSettings& in_musicInit,
		AkOSChar* in_szErrorBuffer,            ///< - Buffer where error details will be written (if the function returns false)
		unsigned int            in_unErrorBufferCharCount	///< - Number of characters available in in_szErrorBuffer, including terminating NULL character
	);

	void TermWwise();

	CAkFilePackageLowLevelIOBlocking* m_pLowLevelIO;
};

