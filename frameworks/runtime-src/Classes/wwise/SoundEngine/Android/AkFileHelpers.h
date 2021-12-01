/*******************************************************************************
The content of this file includes portions of the AUDIOKINETIC Wwise Technology
released in source code form as part of the SDK installer package.

Commercial License Usage

Licensees holding valid commercial licenses to the AUDIOKINETIC Wwise Technology
may use this file in accordance with the end user license agreement provided 
with the software or, alternatively, in accordance with the terms contained in a
written agreement between you and Audiokinetic Inc.

  Version: v2021.1.4  Build: 7707
  Copyright (c) 2006-2021 Audiokinetic Inc.
*******************************************************************************/
//////////////////////////////////////////////////////////////////////
//
// AkFileHelpers.h
//
// Platform-specific helpers for files.
//
//////////////////////////////////////////////////////////////////////

#ifndef _AK_FILE_HELPERS_H_
#define _AK_FILE_HELPERS_H_

#include <AK/Tools/Common/AkAssert.h>
#include <AK/SoundEngine/Common/IAkStreamMgr.h>
#include <android/asset_manager.h>
#include "../Common/AkFileLocationBase.h"
#include "../Common/AkFileHelpersBase.h"
#include <AK/Tools/Common/AkListBareLight.h>
#include <AK/SoundEngine/Common/AkStreamMgrModule.h>
#include <jni.h>

#include <sys/stat.h> 
#include <sys/errno.h>

typedef struct zip zip_t;

struct ANativeActivity;

// On Android, there are different ways to access the file system.
// If the file is inside the APK, it needs to be accessed through the Android Asset Manager,
// APK Expansion Files (OBB) are stored in a specific location and may need to be uncompressed.
// Files can also be accessed directly using POSIX file system functions.

// Each file location implementation will inherit this class and implement
// location-specific file IO (open, read, write) and directory helpers.
// These are equivalent to CAkFileHelpers for other platforms but in this case,
// each file location uses a specific API for IO so we add these functions to
// the CAkFileLocationBase interface.
class CAkFileLocation : public CAkFileLocationBase
{
public:
	CAkFileLocation() : pNextLightItem(NULL)
	{}

	virtual AKRESULT OpenFile( 
		const AkOSChar* in_pszFilename,     // File name.
		AkOpenMode      in_eOpenMode,       // Open mode.		
		bool            in_bOverlappedIO,	// Use FILE_FLAG_OVERLAPPED flag.
		bool            in_bUnbufferedIO,   // Use FILE_FLAG_NO_BUFFERING flag.
		AkFileDesc &	out_descFile        // Returned file identifier/handle.
		) = 0;

	// Wrapper for system file handle closing.
	virtual AKRESULT CloseFile( AkFileHandle in_hFile ) = 0;

	virtual AKRESULT Write(
		AkFileHandle &	in_hFile,			        // File descriptor.
		void *					in_pData,           // Data to be written.
		AkIOTransferInfo &		io_transferInfo		// Synchronous data transfer info. 
		){return AK_Fail;}

	//
	// Simple platform-independent API to open and read files using AkFileHandles, 
	// with blocking calls and minimal constraints.
	// ---------------------------------------------------------------------------

	// Open file to use with ReadBlocking().
	AKRESULT OpenBlocking(
		const AkOSChar* in_pszFilename,     // File name.
		AkFileDesc &  out_descFile           // Returned file handle.
		)
	{
		return OpenFile( 
			in_pszFilename,
			AK_OpenModeRead,
			false,
			false, 
			out_descFile );
	}

	// Simple blocking read method.
	virtual AKRESULT ReadBlocking(
		AkFileHandle &	in_hFile,			// Returned file identifier/handle.
		void *			in_pBuffer,			// Buffer. Must be aligned on CAkFileHelpers::s_uRequiredBlockSize boundary.
		AkUInt32		in_uPosition,		// Position from which to start reading.
		AkUInt32		in_uSizeToRead,		// Size to read. Must be a multiple of CAkFileHelpers::s_uRequiredBlockSize.
		AkUInt32 &		out_uSizeRead		// Returned size read.        
		) = 0;

	CAkFileLocation *pNextLightItem;

	// Required block size for reads (used by ReadBlocking() below).
	static const AkUInt32 s_uRequiredBlockSize = 1;
};

//
// Specific implementations
// (see CAkFileHelpers below for top-level wrapper)
// ------------------------------------------------------

class CAkAPKLocation : public CAkFileLocation
{
public:
	~CAkAPKLocation();
	virtual AKRESULT OpenFile( 
        const AkOSChar* in_pszFilename,     // File name.
        AkOpenMode      in_eOpenMode,       // Open mode.
        bool            in_bOverlappedIO,	// Use FILE_FLAG_OVERLAPPED flag.
        bool            in_bUnbufferedIO,   // Use FILE_FLAG_NO_BUFFERING flag.
        AkFileDesc &  out_descFile           // Returned file identifier/handle.
        );

	// Wrapper for system file handle closing.
	virtual AKRESULT CloseFile( AkFileHandle in_hFile );

	// Simple blocking read method.
	virtual AKRESULT ReadBlocking(
        AkFileHandle &	in_hFile,			// Returned file identifier/handle.
		void *			in_pBuffer,			// Buffer. Must be aligned on CAkFileHelpers::s_uRequiredBlockSize boundary.
		AkUInt32		in_uPosition,		// Position from which to start reading.
		AkUInt32		in_uSizeToRead,		// Size to read. Must be a multiple of CAkFileHelpers::s_uRequiredBlockSize.
		AkUInt32 &		out_uSizeRead		// Returned size read.        
		);


	/// Returns AK_Success if the directory is valid, AK_Fail if not.
	/// For validation purposes only.
	virtual AKRESULT CheckDirectoryExists( const AkOSChar* in_pszBasePath );

	AKRESULT InitAssetManager(JNIEnv*  lJNIEnv, jobject& in_jActivity);

private:
	jobject m_jNativeManagerRef;
	AAssetManager*  ms_assetManager;
};

class CAkOBBLocation : public CAkFileLocation
{
public:

	CAkOBBLocation();
	virtual ~CAkOBBLocation();

	virtual AKRESULT OpenFile( 
        const AkOSChar* in_pszFilename,     // File name.
        AkOpenMode      in_eOpenMode,       // Open mode.
        bool            in_bOverlappedIO,	// Use FILE_FLAG_OVERLAPPED flag.
        bool            in_bUnbufferedIO,   // Use FILE_FLAG_NO_BUFFERING flag.
        AkFileDesc &  out_descFile           // Returned file identifier/handle.
        );

	// Wrapper for system file handle closing.
	virtual AKRESULT CloseFile( AkFileHandle in_hFile );

	// Simple blocking read method.
	virtual AKRESULT ReadBlocking(
        AkFileHandle &	in_hFile,			// Returned file identifier/handle.
		void *			in_pBuffer,			// Buffer. Must be aligned on CAkFileHelpers::s_uRequiredBlockSize boundary.
		AkUInt32		in_uPosition,		// Position from which to start reading.
		AkUInt32		in_uSizeToRead,		// Size to read. Must be a multiple of CAkFileHelpers::s_uRequiredBlockSize.
		AkUInt32 &		out_uSizeRead		// Returned size read.        
		);

	/// Returns AK_Success if the directory is valid, AK_Fail if not.
	/// For validation purposes only.
	virtual AKRESULT CheckDirectoryExists( const AkOSChar* in_pszBasePath );

	AKRESULT FindObbPath(JNIEnv* lJNIEnv, jobject& in_jActivity);
	void SetObbPath(const AkOSChar* in_pszObbPath) { AKPLATFORM::SafeStrCpy( m_szObbPath, in_pszObbPath, AK_MAX_PATH ); }

private:
	zip_t *m_zip;
	AkOSChar m_szObbPath[AK_MAX_PATH];
};

class CAkPOSIXLocation : public CAkFileLocation
{
public:

	virtual AKRESULT OpenFile( 
		const AkOSChar* in_pszFilename,     // File name.
		AkOpenMode      in_eOpenMode,       // Open mode.
		bool            in_bOverlappedIO,	// Use FILE_FLAG_OVERLAPPED flag.
		bool            in_bUnbufferedIO,   // Use FILE_FLAG_NO_BUFFERING flag.
		AkFileDesc &  out_descFile           // Returned file identifier/handle.
		);	

	// Wrapper for system file handle closing.
	virtual AKRESULT CloseFile( AkFileHandle in_hFile );

	// Simple blocking read method.
	virtual AKRESULT ReadBlocking(
		AkFileHandle &	in_hFile,			// Returned file identifier/handle.
		void *			in_pBuffer,			// Buffer. Must be aligned on CAkFileHelpers::s_uRequiredBlockSize boundary.
		AkUInt32		in_uPosition,		// Position from which to start reading.
		AkUInt32		in_uSizeToRead,		// Size to read. Must be a multiple of CAkFileHelpers::s_uRequiredBlockSize.
		AkUInt32 &		out_uSizeRead		// Returned size read.        
		);

	virtual AKRESULT Write(
		AkFileHandle &	in_hFile,			        // File descriptor.
		void *					in_pData,           // Data to be written.
		AkIOTransferInfo &		io_transferInfo		// Synchronous data transfer info. 
		);

	/// Returns AK_Success if the directory is valid, AK_Fail if not.
	/// For validation purposes only.
	virtual AKRESULT CheckDirectoryExists( const AkOSChar* in_pszBasePath );

	// Only valid on a writable location. See CAkFileHelpers::GetDefaultWritablePath()
	static AKRESULT CreateEmptyDirectory( const AkOSChar* in_pszDirectoryPath );
	static AKRESULT RemoveEmptyDirectory( const AkOSChar* in_pszDirectoryPath );
};

//
// File location top-level wrapper for Android
// ------------------------------------------------------

// Implements IO for multiple locations on Android (APK, OBB, POSIX).
// Redirects IO operations to the appropriate CAkFileLocationBaseAndroid.
// Common/CAkMultipleFileLocation.h cannot be used directly on Android
// since each file location needs to be accessed with a different API.
class CAkFileHelpers : public CAkFileHelpersBase
{
public:

	CAkFileHelpers();

	/// Initialize the Android IO systems for reading APK and OBB.  
	virtual AKRESULT Init(
		JavaVM* java_vm,		///< The Java VM pointer
		jobject& in_jActivity	///< The Activity, as given by android_app->activity->clazz (or any other method).);
	);

	virtual void Term();

	AKRESULT OpenFile( 
		const AkOSChar* in_pszFilename,     // File name.
		AkOpenMode      in_eOpenMode,       // Open mode.
		AkFileSystemFlags * in_pFlags,
		bool            in_bOverlappedIO,	// Use FILE_FLAG_OVERLAPPED flag.
		bool            in_bUnbufferedIO,   // Use FILE_FLAG_NO_BUFFERING flag.
		AkFileDesc &    out_fileDesc          // Returned file identifier/handle.
		);

	AKRESULT OpenFile( 
		AkFileID        in_fileID,			// File id.
		AkOpenMode      in_eOpenMode,       // Open mode.
		AkFileSystemFlags * in_pFlags,
		bool            in_bOverlappedIO,	// Use FILE_FLAG_OVERLAPPED flag.
		bool            in_bUnbufferedIO,   // Use FILE_FLAG_NO_BUFFERING flag.
		AkFileDesc &    out_fileDesc          // Returned file identifier/handle.
		);

	inline AKRESULT Write(
		AkFileDesc &			in_fileDesc,        // File descriptor.
		void *					in_pData,           // Data to be written.
		AkIOTransferInfo &		io_transferInfo		// Synchronous data transfer info. 
		)
	{
		CAkFileLocation* pLoc = (CAkFileLocation*)in_fileDesc.pCustomParam;
		return pLoc->Write(in_fileDesc.hFile, in_pData, io_transferInfo);
	}

	// Open file to use with ReadBlocking().
	inline AKRESULT OpenBlocking(
		const AkOSChar* in_pszFilename,     // File name.
		AkFileDesc &    out_fileDesc           // Returned file handle.
		)
	{
		return OpenFile( 
			in_pszFilename,
			AK_OpenModeRead,
			NULL,
			false,
			false, 
			out_fileDesc );
	}

	// Wrapper for system file handle closing.
	inline void CloseFile( AkFileDesc & out_fileDesc )
	{
		CAkFileLocation* pLoc = (CAkFileLocation*)out_fileDesc.pCustomParam;
		pLoc->CloseFile(out_fileDesc.hFile);
	}

	// Simple blocking read method.
	inline AKRESULT ReadBlocking(
		AkFileDesc & in_fileDesc,			// Returned file identifier/handle.
		void *			in_pBuffer,			// Buffer. Must be aligned on CAkFileHelpers::s_uRequiredBlockSize boundary.
		AkUInt32		in_uPosition,		// Position from which to start reading.
		AkUInt32		in_uSizeToRead,		// Size to read. Must be a multiple of CAkFileHelpers::s_uRequiredBlockSize.
		AkUInt32 &		out_uSizeRead		// Returned size read.        
		)
	{
		CAkFileLocation* pLoc = (CAkFileLocation*)in_fileDesc.pCustomParam;
		return pLoc->ReadBlocking(in_fileDesc.hFile, in_pBuffer, in_uPosition, in_uSizeToRead, out_uSizeRead);
	}

	/// Sets the base path for file loading (banks and streamed files).  
	/// This path must be inside the app's APK or OBB, relative to the standard "assets" directory of the archive.  
	/// The same path is used for both APK and OBB.
	AKRESULT SetBasePath(const AkOSChar* in_pszPath);

	/// Adds a alternative path for file loading.  This path can be anywhere in the file system (but not inside APK and OBB)
	/// Multiple paths can be specified.  Last path specified is first to be searched for files.
	AKRESULT AddBasePath(const AkOSChar* in_pszPath);

	static AKRESULT GetDefaultWritablePath(ANativeActivity* in_activity, AkOSChar* out_path, size_t path_size);
	
	/// Returns AK_Success if the directory is valid, AK_Fail if not.
	/// For validation purposes only.
	/// Some platforms may return AK_NotImplemented, in this case you cannot rely on it.
	AKRESULT CheckDirectoryExists( const AkOSChar* in_pszBasePath );

	// Only valid on a writable location. See CAkFileHelpers::GetDefaultWritablePath()
	static AKRESULT CreateEmptyDirectory( const AkOSChar* in_pszDirectoryPath );
	static AKRESULT RemoveEmptyDirectory( const AkOSChar* in_pszDirectoryPath );

	AKRESULT GetFullFilePath(
		const AkOSChar*		in_pszFileName,		// File name.
		AkFileSystemFlags * in_pFlags,			// Special flags. Can be NULL.
		AkOpenMode			in_eOpenMode,		// File open mode (read, write, ...).
		AkOSChar*			out_pszFullFilePath);
	// my
	static CAkFileHelpers* CAkFileHelpers_;

	static CAkFileHelpers* instance() {
		return CAkFileHelpers_;
	}
	
	static AKRESULT Open(
		const AkOSChar* in_pszFileName,     // File name.
		AkOpenMode      in_eOpenMode,       // Open mode.
		bool			in_bOverlapped,		// Overlapped IO
		AkFileDesc& out_fileDesc		// File descriptor
	) {
		return CAkFileHelpers::instance()->OpenFile(in_pszFileName,in_eOpenMode, nullptr, in_bOverlapped, in_bOverlapped, out_fileDesc);
	}

	static AKRESULT MyCheckDirectoryExists(const AkOSChar* in_pszBasePath) {
		return CAkFileHelpers::instance()->CheckDirectoryExists(in_pszBasePath);
	}
	// end my

protected:
	AkListBareLight<CAkFileLocation> m_Locations;
	CAkAPKLocation m_APKLocation;	//There is always an APK.
	CAkOBBLocation m_OBBLocation;	//There is sometimes an OBB
};


#endif //_AK_FILE_HELPERS_H_
