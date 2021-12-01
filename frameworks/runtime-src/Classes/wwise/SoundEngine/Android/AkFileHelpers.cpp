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

#include "AkFileHelpers.h"
#include <AK/SoundEngine/Common/IAkStreamMgr.h>
#include <AK/SoundEngine/Platforms/Android/AkAndroidSoundEngine.h>

#include <AK/Tools/Common/AkObject.h>
#include <AK/Tools/Android/AkJNIThread.h>

#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>
#include <android/native_activity.h>

#include <sys/stat.h>

#ifndef REMOVE_LIBZIP
#include <zip.h>
#endif

#ifdef AK_ANDROID
#include "android/asset_manager.h"
#include <android/log.h>
#define  LOG_TAG    "Wwise"
#define  LOGAK(...)  		__android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define LOGAK(...)   do {} while (0)
#endif

extern AkPlatformInitSettings g_PDSettings;

CAkFileHelpers* CAkFileHelpers::CAkFileHelpers_ = nullptr;

CAkFileHelpers::CAkFileHelpers()
{	
	LOGAK("CAkFileHelpers::CAkFileHelpers");
	CAkFileHelpers_ = this;
}

AKRESULT CAkFileHelpers::Init(JavaVM* java_vm, jobject& in_jActivity)
{
	LOGAK("CAkFileHelpers::Init");
	m_Locations.AddFirst(&m_APKLocation);
	m_Locations.AddFirst(&m_OBBLocation);

	if (java_vm == NULL || in_jActivity == 0)
		return AK_InvalidParameter;

	JNIEnv* lJNIEnv = NULL;
	java_vm->GetEnv((void**)&lJNIEnv, JNI_VERSION_1_6);
	bool bAttached = false;
	if (lJNIEnv == NULL)
	{
		JavaVMAttachArgs lJavaVMAttachArgs;
		lJavaVMAttachArgs.version = JNI_VERSION_1_6;
		lJavaVMAttachArgs.name = "NativeThread";
		lJavaVMAttachArgs.group = NULL;

		jint lResult = java_vm->AttachCurrentThread(&lJNIEnv, &lJavaVMAttachArgs);
		if (lResult == JNI_ERR)
			return AK_Fail;

		bAttached = true;
	}

	AKRESULT res = m_APKLocation.InitAssetManager(lJNIEnv, in_jActivity);
	if (res == AK_Success) {
		LOGAK("CAkFileHelpers::Init m_APKLocation.InitAssetManager success");
		res = m_OBBLocation.FindObbPath(lJNIEnv, in_jActivity);
	}
		
	
	if (bAttached)
		java_vm->DetachCurrentThread();
	LOGAK("CAkFileHelpers::Init res : %s", res ? "true" : "false");
	return res;
}

void CAkFileHelpers::Term()
{
	for(AkListBareLight<CAkFileLocation>::Iterator it = m_Locations.Begin(); it != m_Locations.End();)
	{
		CAkFileLocation *p = (*it);
		++it;
		if (p != &m_APKLocation && p != &m_OBBLocation)
			AkDelete(AkMemID_Streaming, p);
	}
	m_Locations.Term();
}

AKRESULT CAkFileHelpers::OpenFile( 
				  const AkOSChar* in_pszFilename,     // File name.
				  AkOpenMode      in_eOpenMode,       // Open mode.
				  AkFileSystemFlags * in_pFlags,      // Special flags. Can pass NULL.
				  bool            in_bOverlappedIO,	// Use FILE_FLAG_OVERLAPPED flag.
				  bool            in_bUnbufferedIO,   // Use FILE_FLAG_NO_BUFFERING flag.
				  AkFileDesc &    out_fileDesc           // Returned file identifier/handle.
				  )
{		
	LOGAK("CAkFileHelpers::OpenFile 111 in_pszFilename : %s", in_pszFilename);
	AKRESULT res = AK_FileNotFound;
	//Go through all locations in order.
	for(AkListBareLight<CAkFileLocation>::Iterator it = m_Locations.Begin(); it != m_Locations.End() && res != AK_Success; ++it)
	{
		AkOSChar szFullFilePath[AK_MAX_PATH];
		if ( (*it)->GetFullFilePath( in_pszFilename, in_pFlags, in_eOpenMode, szFullFilePath ) == AK_Success )
		{
			LOGAK("CAkFileHelpers::OpenFile 111 szFullFilePath : %s", szFullFilePath);
			res = (*it)->OpenFile(szFullFilePath, in_eOpenMode, in_bOverlappedIO, in_bUnbufferedIO, out_fileDesc);
			out_fileDesc.pCustomParam = (*it);			
		} else {
			LOGAK("CAkFileHelpers::OpenFile 111 GetFullFilePath failed");
		}
	}

	return res;
}

AKRESULT CAkFileHelpers::OpenFile( 
								  AkFileID        in_fileID,	
								  AkOpenMode      in_eOpenMode,       // Open mode.
								  AkFileSystemFlags * in_pFlags,      // Special flags. Can pass NULL.
								  bool            in_bOverlappedIO,	// Use FILE_FLAG_OVERLAPPED flag.
								  bool            in_bUnbufferedIO,   // Use FILE_FLAG_NO_BUFFERING flag.
								  AkFileDesc &    out_fileDesc           // Returned file identifier/handle.
								  )
{
	LOGAK("CAkFileHelpers::OpenFile 222 in_fileID : %d", in_fileID);
	AKRESULT res = AK_FileNotFound;
	//Go through all locations in order.
	for(AkListBareLight<CAkFileLocation>::Iterator it = m_Locations.Begin(); it != m_Locations.End() && res != AK_Success; ++it)
	{
		AkOSChar szFullFilePath[AK_MAX_PATH];
		if ( (*it)->GetFullFilePath( in_fileID, in_pFlags, in_eOpenMode, szFullFilePath ) == AK_Success )
		{
			LOGAK("CAkFileHelpers::OpenFile 222 szFullFilePath : %s", szFullFilePath);
			res = (*it)->OpenFile(szFullFilePath, in_eOpenMode, in_bOverlappedIO, in_bUnbufferedIO, out_fileDesc);
			out_fileDesc.pCustomParam = (*it);			
		} else {
			LOGAK("CAkFileHelpers::OpenFile 222 GetFullFilePath failed");
		}
	}

	return res;
}

AKRESULT CAkFileHelpers::SetBasePath(const AkOSChar* in_pszPath)
{
	LOGAK("CAkFileHelpers::SetBasePath");
	AKRESULT res = m_APKLocation.SetBasePath(in_pszPath);
	if (res != AK_Success)
		return res;

	LOGAK("CAkFileHelpers::SetBasePath m_APKLocation.SetBasePath success");

	res = m_OBBLocation.SetBasePath(in_pszPath);
	if (res != AK_Success)
		return res;

	LOGAK("CAkFileHelpers::SetBasePath m_OBBLocation.SetBasePath success");

	//Yes, this is checked AFTER the base path has been set on the location object.  It is legal that the directory doesn't exist at startup.  
	//However, an error code should be returned for information purposes so the client knows why the files are not found.
	return m_APKLocation.CheckDirectoryExists(in_pszPath);	
}

AKRESULT CAkFileHelpers::AddBasePath(const AkOSChar* in_pszPath)
{	
	if (!AK::IAkStreamMgr::Get())
		return AK_StreamMgrNotInitialized;

	CAkPOSIXLocation * pLoc = AkNew(AkMemID_Streaming, CAkPOSIXLocation());
	if (pLoc == NULL)
		return AK_InsufficientMemory;
	
	pLoc->SetBasePath(in_pszPath);	
	m_Locations.AddFirst(pLoc); //Last added is the first searched.

	//Yes, this is checked AFTER the base path has been set on the location object.  It is legal that the directory doesn't exist at startup.  
	//However, an error code should be returned for information purposes so the client knows why the files are not found.
	return pLoc->CheckDirectoryExists(in_pszPath);	
}

AKRESULT CAkFileHelpers::GetFullFilePath(
	const AkOSChar*		in_pszFileName,		// File name.
	AkFileSystemFlags * in_pFlags,			// Special flags. Can be NULL.
	AkOpenMode			in_eOpenMode,		// File open mode (read, write, ...).
	AkOSChar*			out_pszFullFilePath)
{	
	AKRESULT res;
	for(AkListBareLight<CAkFileLocation>::Iterator it = m_Locations.Begin(); it != m_Locations.End() && res != AK_Success; ++it)
	{
		AkOSChar szFullFilePath[AK_MAX_PATH];
		if ( (*it)->GetFullFilePath( in_pszFileName, in_pFlags, in_eOpenMode, szFullFilePath ) == AK_Success )
			return AK_Success;
	}
	return AK_Fail;
}

AKRESULT CAkFileHelpers::GetDefaultWritablePath(ANativeActivity* in_activity, char* out_path, size_t path_size)
{
	if (out_path == NULL)
		return AK_InsufficientMemory;

	out_path[0] = '\0';
	jobject jActivity = in_activity->clazz;
	JavaVM* lJavaVM = in_activity->vm;

	// This utility will release the JNI environment automatically
	AKPLATFORM::CAkJNIThread jThread(lJavaVM);
	if(!jThread.isAttached())
		return AK_Fail;

	JNIEnv* lJNIEnv = jThread.getEnv();

	// Resolve the Java classes needed to call the APIs
	jclass Context = lJNIEnv->FindClass("android/content/Context");
	jclass File = lJNIEnv->FindClass("java/io/File");
	if (Context == NULL || File == NULL)
		return AK_Fail;

	// Resolve the Java methods needed to call the APIs
	jmethodID GetExternalCacheDir = lJNIEnv->GetMethodID(Context, "getExternalCacheDir", "()Ljava/io/File;");
	jmethodID GetAbsolutePath = lJNIEnv->GetMethodID(File, "getAbsolutePath", "()Ljava/lang/String;");
	if (GetExternalCacheDir == NULL || GetAbsolutePath == NULL)
	    return AK_Fail;

	// Get the File object representing the cache path
	jobject ExternalCacheDir = lJNIEnv->CallObjectMethod(jActivity, GetExternalCacheDir);
	if (ExternalCacheDir == NULL) return AK_Fail;

	// Get the Java string representing the absolute path to the cache path
	jstring ExternalCacheDirPath = (jstring)lJNIEnv->CallObjectMethod(ExternalCacheDir, GetAbsolutePath);
	if (ExternalCacheDirPath == NULL) return AK_Fail;

	// Convert Java string to C-style string and copy it locally
	const char *cStr = lJNIEnv->GetStringUTFChars(ExternalCacheDirPath, NULL);
	if (cStr == NULL) return AK_Fail;
	AKPLATFORM::SafeStrCpy(out_path, cStr, path_size);
	lJNIEnv->ReleaseStringUTFChars(ExternalCacheDirPath, cStr);

	return AK_Success;
}

AKRESULT CAkFileHelpers::CheckDirectoryExists( const AkOSChar* in_pszBasePath )
{
	//Go through all locations in order.
	for (AkListBareLight<CAkFileLocation>::Iterator it = m_Locations.Begin(); it != m_Locations.End(); ++it)
	{
		if ( (*it)->CheckDirectoryExists( in_pszBasePath ) == AK_Success )
			return AK_Success;
	}

	return CAkPOSIXLocation().CheckDirectoryExists(in_pszBasePath);
}

AKRESULT CAkFileHelpers::CreateEmptyDirectory(const AkOSChar* in_pszDirectoryPath)
{
	// APK and OBB file locations are read-only, use POSIX file location
	return CAkPOSIXLocation::CreateEmptyDirectory(in_pszDirectoryPath);
}

AKRESULT CAkFileHelpers::RemoveEmptyDirectory( const AkOSChar* in_pszDirectoryPath )
{
	// APK and OBB file locations are read-only, use POSIX file location
	return CAkPOSIXLocation::RemoveEmptyDirectory(in_pszDirectoryPath);
}

//--------------------------------------------------------------------
CAkAPKLocation::~CAkAPKLocation()
{
	if (g_PDSettings.pJavaVM == NULL || m_jNativeManagerRef == 0)
		return;

	JNIEnv* lJNIEnv = NULL;
	g_PDSettings.pJavaVM->GetEnv((void**)&lJNIEnv, JNI_VERSION_1_6);
	bool bAttached = false;
	if (lJNIEnv == NULL)
	{
		JavaVMAttachArgs lJavaVMAttachArgs;
		lJavaVMAttachArgs.version = JNI_VERSION_1_6;
		lJavaVMAttachArgs.name = "NativeThread";
		lJavaVMAttachArgs.group = NULL;

		jint lResult = g_PDSettings.pJavaVM->AttachCurrentThread(&lJNIEnv, &lJavaVMAttachArgs);
		if (lResult == JNI_ERR)
			return;
		
		bAttached = true;
	}

	lJNIEnv->DeleteGlobalRef(m_jNativeManagerRef);

	if (bAttached)
		g_PDSettings.pJavaVM->DetachCurrentThread();
}

AKRESULT CAkAPKLocation::InitAssetManager(JNIEnv*  lJNIEnv, jobject& in_jActivity)
{	
	jclass obj_cls = lJNIEnv->GetObjectClass(in_jActivity);
	jmethodID asset_func = lJNIEnv->GetMethodID(obj_cls, "getAssets", "()Landroid/content/res/AssetManager;");
	jobject assetManager = lJNIEnv->CallObjectMethod(in_jActivity, asset_func, NULL);
	m_jNativeManagerRef = lJNIEnv->NewGlobalRef(assetManager);
	if (m_jNativeManagerRef == 0)
		return AK_Fail;
	
	ms_assetManager = AAssetManager_fromJava(lJNIEnv, assetManager);
	return ms_assetManager != NULL ? AK_Success : AK_Fail;
}

AKRESULT CAkAPKLocation::OpenFile( 
						  const AkOSChar* in_pszFilename,     // File name.
						  AkOpenMode      in_eOpenMode,       // Open mode.
						  bool            in_bOverlappedIO,	// Use FILE_FLAG_OVERLAPPED flag.
						  bool            in_bUnbufferedIO,   // Use FILE_FLAG_NO_BUFFERING flag.
						  AkFileDesc &  out_descFile           // Returned file identifier/handle.
						  )
{
	LOGAK("CAkAPKLocation::OpenFile in_pszFilename : %s", in_pszFilename);
	// Check parameters.
	if ( ! in_pszFilename )
	{
		AKASSERT( !"NULL file name" );
		return AK_InvalidParameter;
	}

	if ( ! ms_assetManager )
	{
		AKASSERT( !"Android Asset Manager is not set" );
		return AK_Fail;
	}	

	AAsset* asset = AAssetManager_open(ms_assetManager, in_pszFilename, AASSET_MODE_UNKNOWN);
	if (!asset) {
		LOGAK("CAkAPKLocation::OpenFile AAssetManager_open failed : %s", in_pszFilename);
		return AK_FileNotFound;
	}
	out_descFile.hFile = (AkFileHandle) asset;
	AkInt64 fileSize = AAsset_getLength((AAsset*)out_descFile.hFile);
	out_descFile.iFileSize			= fileSize;
	out_descFile.uSector			= 0;

	return AK_Success;
}

// Wrapper for system file handle closing.
AKRESULT CAkAPKLocation::CloseFile( AkFileHandle in_hFile )
{
	AAsset_close( (AAsset*) in_hFile);
	return AK_Success;
}	

// Simple blocking read method.
AKRESULT CAkAPKLocation::ReadBlocking(
							  AkFileHandle &	in_hFile,			// Returned file identifier/handle.
							  void *			in_pBuffer,			// Buffer. Must be aligned on CAkFileHelpers::s_uRequiredBlockSize boundary.
							  AkUInt32		in_uPosition,		// Position from which to start reading.
							  AkUInt32		in_uSizeToRead,		// Size to read. Must be a multiple of CAkFileHelpers::s_uRequiredBlockSize.
							  AkUInt32 &		out_uSizeRead		// Returned size read.        
							  )
{
	AKASSERT( in_uSizeToRead % s_uRequiredBlockSize == 0 && in_uPosition % s_uRequiredBlockSize == 0 );

	AAsset* asset = (AAsset*) in_hFile;
	// fpos_t pos = io_transferInfo.uFilePosition;
	if( AAsset_seek( asset, in_uPosition, SEEK_SET ) == -1 )
	{
		return AK_Fail;
	}

	out_uSizeRead = (AkUInt32) AAsset_read(asset, in_pBuffer, in_uSizeToRead);
	if( out_uSizeRead == in_uSizeToRead)
		return AK_Success;

	return AK_Fail;		
}

AKRESULT CAkAPKLocation::CheckDirectoryExists( const AkOSChar* in_pszBasePath )
{
	AAssetDir* pDir = AAssetManager_openDir(ms_assetManager, in_pszBasePath);	
	if (pDir)
	{
		AAssetDir_close(pDir);
		return AK_Success;
	}
	return AK_Fail;
}

//--------------------------------------------------------------------
CAkOBBLocation::CAkOBBLocation()
{	
	m_szObbPath[0] = '\0';
	m_zip = NULL;
}

CAkOBBLocation::~CAkOBBLocation()
{	
#ifndef REMOVE_LIBZIP
	if ( m_zip )
	{
		zip_close(m_zip);
		m_zip = NULL;
	}
#endif
}

AKRESULT CAkOBBLocation::FindObbPath(JNIEnv* lJNIEnv, jobject& in_jActivity)
{	
	jclass obj_cls = lJNIEnv->GetObjectClass(in_jActivity);
	if(obj_cls == 0)
	{
		AKPLATFORM::OutputDebugMsg("Can't get Activity class");
		return AK_Fail;
	}

	// Fetch the package info
	jmethodID getPackageName_func = lJNIEnv->GetMethodID(obj_cls, "getPackageName", "()Ljava/lang/String;");
	if(getPackageName_func == NULL)
	{
		AKPLATFORM::OutputDebugMsg("Can't find getPackageName on Activity class");
		return AK_Fail;
	}
	jstring packageName = (jstring)lJNIEnv->CallObjectMethod(in_jActivity, getPackageName_func);
	if(packageName == NULL)
	{
		AKPLATFORM::OutputDebugMsg("Call to getPackageName returned null");
		return AK_Fail;
	}

	jmethodID getPackageManager_func = lJNIEnv->GetMethodID(obj_cls, "getPackageManager", "()Landroid/content/pm/PackageManager;");
	if(getPackageManager_func == NULL)
	{
		AKPLATFORM::OutputDebugMsg("Can't find getPackageManager on Activity class");
		return AK_Fail;
	}
	jobject packageManager = lJNIEnv->CallObjectMethod(in_jActivity, getPackageManager_func, NULL);
	if(packageManager == NULL)
	{
		AKPLATFORM::OutputDebugMsg("Call to getPackageManager returned null");
		return AK_Fail;
	}
	jclass packageManager_cls = lJNIEnv->GetObjectClass(packageManager);

	jmethodID getPackageInfo_func = lJNIEnv->GetMethodID(packageManager_cls, "getPackageInfo", "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
	if(getPackageInfo_func == NULL)
	{
		AKPLATFORM::OutputDebugMsg("Can't find getPackageInfo on PackageManager class");
		return AK_Fail;
	}
	jobject packageInfo = lJNIEnv->CallObjectMethod(packageManager, getPackageInfo_func, packageName, 0, NULL);
	if(packageInfo == NULL)
	{
		AKPLATFORM::OutputDebugMsg("Call to getPackageInfo returned null");
		return AK_Fail;
	}
	jclass packageInfo_cls = lJNIEnv->GetObjectClass(packageInfo);

	jfieldID fieldVersionCode = lJNIEnv->GetFieldID(packageInfo_cls, "versionCode", "I");
	if(fieldVersionCode == NULL)
	{
		AKPLATFORM::OutputDebugMsg("Can't find versionCode field on PackageInfo");
		return AK_Fail;
	}
	jint versionCode = lJNIEnv->GetIntField(packageInfo, fieldVersionCode);

	// Fetch the external storage directory
	jclass classEnvironment = lJNIEnv->FindClass("android/os/Environment");
	if(classEnvironment == NULL)
	{
		AKPLATFORM::OutputDebugMsg("Can't find Environment class");
		return AK_Fail;
	}
	jmethodID getExternalStorageDirectory_func = lJNIEnv->GetStaticMethodID(classEnvironment, "getExternalStorageDirectory", "()Ljava/io/File;");
	if(getExternalStorageDirectory_func == NULL)
	{
		AKPLATFORM::OutputDebugMsg("Can't find getExternalStorageDirectory on Environment class");
		return AK_Fail;
	}
	jobject externalStorageDirectory = lJNIEnv->CallStaticObjectMethod(classEnvironment, getExternalStorageDirectory_func);
	if(externalStorageDirectory == NULL)
	{
		AKPLATFORM::OutputDebugMsg("Call to getExternalStorageDirectory return null");
		return AK_Fail;
	}
	jclass classFile = lJNIEnv->GetObjectClass(externalStorageDirectory);

	jmethodID getPath_func = lJNIEnv->GetMethodID(classFile, "getPath", "()Ljava/lang/String;");
	if(getPath_func == NULL)
	{
		AKPLATFORM::OutputDebugMsg("Can't find getPath on File class");
		return AK_Fail;
	}
	jstring externalStoragePath = (jstring)lJNIEnv->CallObjectMethod(externalStorageDirectory, getPath_func, NULL);
	if(externalStoragePath == NULL)
	{
		AKPLATFORM::OutputDebugMsg("Call to getPath returned null");
		return AK_Fail;
	}

	const AkOSChar *sz_externalStoragePath = lJNIEnv->GetStringUTFChars(externalStoragePath, NULL);
	const AkOSChar *sz_packageName = lJNIEnv->GetStringUTFChars(packageName, NULL);

	AK_OSPRINTF(m_szObbPath, AK_MAX_PATH, AKTEXT("%s/Android/obb/%s/main.%d.%s.obb"), sz_externalStoragePath, sz_packageName, (int)versionCode, sz_packageName);

	lJNIEnv->ReleaseStringUTFChars(externalStoragePath, sz_externalStoragePath);
	lJNIEnv->ReleaseStringUTFChars(packageName, sz_packageName);
	
	return AK_Success;
}

AKRESULT CAkOBBLocation::OpenFile( 
						  const AkOSChar* in_pszFilename,     // File name.
						  AkOpenMode      in_eOpenMode,       // Open mode.
						  bool            in_bOverlappedIO,	// Use FILE_FLAG_OVERLAPPED flag.
						  bool            in_bUnbufferedIO,   // Use FILE_FLAG_NO_BUFFERING flag.
						  AkFileDesc &  out_descFile           // Returned file identifier/handle.
						  )
{
	// Check parameters.
	if ( ! in_pszFilename )
	{
		AKPLATFORM::OutputDebugMsg( "NULL file name" );
		return AK_InvalidParameter;
	}
	
	if ( m_szObbPath[0] == 0 )
	{
		AKPLATFORM::OutputDebugMsg( "Android OBB path is not set" );
		return AK_Fail;
	}

#ifndef REMOVE_LIBZIP
	if ( ! m_zip )
	{		
		m_zip = zip_open(m_szObbPath, ZIP_RDONLY, NULL);		
		if ( ! m_zip )
		{			
			return AK_FileNotFound;
		}
	}	
	
	// OBB files need to prepend assets folder (normally asset manager does this)
	AkOSChar archivePath[AK_MAX_PATH];
	AKPLATFORM::SafeStrCpy( archivePath, "assets/", AK_MAX_PATH );
	AKPLATFORM::SafeStrCat( archivePath, in_pszFilename, AK_MAX_PATH );
	
	zip_file_t* file = zip_fopen(m_zip, archivePath, ZIP_FL_COMPRESSED);
	if ( ! file )
	{
		AKPLATFORM::OutputDebugMsg("Cannot find file in zip archive");
		return AK_FileNotFound;
	}
	
	zip_stat_t fileStats;
	zip_stat(m_zip, archivePath, 0, &fileStats);

	out_descFile.hFile = (AkFileHandle) file;
	AkInt64 fileSize = fileStats.size;
	out_descFile.iFileSize			= fileSize;
	out_descFile.uSector			= 0;

	return AK_Success;
#else	
	return AK_NotImplemented;
#endif
}

// Wrapper for system file handle closing.
AKRESULT CAkOBBLocation::CloseFile( AkFileHandle in_hFile )
{
#ifndef REMOVE_LIBZIP
	zip_fclose( (zip_file_t*) in_hFile);
#endif
	return AK_Success;
}	

#ifndef REMOVE_LIBZIP
#include "zipint.h" // IMPORT LIBRARY INTERNALS (FOR SEEKING)
#endif

// Simple blocking read method.
AKRESULT CAkOBBLocation::ReadBlocking(
							  AkFileHandle &	in_hFile,			// Returned file identifier/handle.
							  void *			in_pBuffer,			// Buffer. Must be aligned on CAkFileHelpers::s_uRequiredBlockSize boundary.
							  AkUInt32		in_uPosition,		// Position from which to start reading.
							  AkUInt32		in_uSizeToRead,		// Size to read. Must be a multiple of CAkFileHelpers::s_uRequiredBlockSize.
							  AkUInt32 &		out_uSizeRead		// Returned size read.        
							  )
{
#ifndef REMOVE_LIBZIP
	AKASSERT( in_uSizeToRead % s_uRequiredBlockSize == 0 && in_uPosition % s_uRequiredBlockSize == 0 );

	zip_file_t* file = (zip_file_t*) in_hFile;
	
	if( zip_source_seek( file->src, in_uPosition, SEEK_SET ) == -1 )
	{
		AKPLATFORM::OutputDebugMsg("Seeking in zip archive failed");
		return AK_Fail;
	}

	out_uSizeRead = (AkUInt32) zip_fread(file, in_pBuffer, in_uSizeToRead);
	if( out_uSizeRead == in_uSizeToRead)
		return AK_Success;
#endif
	return AK_Fail;		
}

AKRESULT CAkOBBLocation::CheckDirectoryExists( const AkOSChar* in_pszBasePath )
{
	// my
	// return AK_Fail; // Can't resolve nested folders in OBB zip
	return AK_Success;
	// end my
}

//--------------------------------------------------------------------

AKRESULT CAkPOSIXLocation::OpenFile( 
						  const AkOSChar* in_pszFilename,     // File name.
						  AkOpenMode      in_eOpenMode,       // Open mode.
						  bool            in_bOverlappedIO,	// Use FILE_FLAG_OVERLAPPED flag.
						  bool            in_bUnbufferedIO,   // Use FILE_FLAG_NO_BUFFERING flag.
						  AkFileDesc &  out_descFile           // Returned file identifier/handle.
						  )
{
	// Check parameters.
	if ( !in_pszFilename )
	{
		AKASSERT( !"NULL file name" );
		return AK_InvalidParameter;
	}

	char* mode;
	switch ( in_eOpenMode )
	{
	case AK_OpenModeRead:
		mode = (char*)"r"; 
		break;
	case AK_OpenModeWrite:
		mode = (char*)"w";
		break;
	case AK_OpenModeWriteOvrwr:
		mode = (char*)"w+";
		break;
	case AK_OpenModeReadWrite:
		mode = (char*)"a";
		break;
	default:
		AKASSERT( !"Invalid open mode" );
		out_descFile.hFile = NULL;
		return AK_InvalidParameter;
	}

	out_descFile.hFile = fopen( in_pszFilename , mode );

	if( !out_descFile.hFile )
		return AK_FileNotFound;

	struct stat buf;
	// Get Info about the file size
	if( stat(in_pszFilename, &buf) != 0)
		return AK_Fail;

	out_descFile.iFileSize = buf.st_size;

	return AK_Success;
}

// Wrapper for system file handle closing.
AKRESULT CAkPOSIXLocation::CloseFile( AkFileHandle in_hFile )
{
	if ( !fclose( in_hFile ) )
		return AK_Success;

	AKASSERT( !"Failed to close file handle" );
	return AK_Fail;
}

// Simple blocking read method.
AKRESULT CAkPOSIXLocation::ReadBlocking(
							  AkFileHandle &	in_hFile,			// Returned file identifier/handle.
							  void *			in_pBuffer,			// Buffer. Must be aligned on CAkFileHelpers::s_uRequiredBlockSize boundary.
							  AkUInt32		in_uPosition,		// Position from which to start reading.
							  AkUInt32		in_uSizeToRead,		// Size to read. Must be a multiple of CAkFileHelpers::s_uRequiredBlockSize.
							  AkUInt32 &		out_uSizeRead		// Returned size read.        
							  )
{
	AKASSERT( in_uSizeToRead % s_uRequiredBlockSize == 0 && in_uPosition % s_uRequiredBlockSize == 0 );
	if( fseek(in_hFile, in_uPosition, SEEK_SET ) )
	{
		return AK_Fail;
	}

	out_uSizeRead = fread( in_pBuffer, 1, in_uSizeToRead , in_hFile );
	if( out_uSizeRead == in_uSizeToRead )
	{
		return AK_Success;
	}
	return AK_Fail;		
}

AKRESULT CAkPOSIXLocation::Write(
	AkFileHandle &	in_hFile,			        // File descriptor.
	void *					in_pData,           // Data to be written.
	AkIOTransferInfo &		io_transferInfo		// Synchronous data transfer info. 
	)
{
	int retSeek = fseek(in_hFile, io_transferInfo.uFilePosition, SEEK_SET);
	if (retSeek != 0)
		return AK_Fail;
	size_t written = fwrite(in_pData, 1, io_transferInfo.uRequestedSize, in_hFile);
	return written == io_transferInfo.uRequestedSize ? AK_Success : AK_Fail;
}

AKRESULT CAkPOSIXLocation::CheckDirectoryExists( const AkOSChar* in_pszBasePath )
{
	struct stat status;
	stat( in_pszBasePath, &status );
	if( status.st_mode & S_IFDIR )
		return AK_Success;

	return AK_Fail;
}

AKRESULT CAkPOSIXLocation::CreateEmptyDirectory( const AkOSChar* in_pszDirectoryPath )
{
	int iErr = mkdir(in_pszDirectoryPath, S_IRWXU | S_IRWXG | S_IRWXO);
	if (iErr == -1 && errno != EEXIST)
		return AK_Fail;

	return AK_Success;
}

AKRESULT CAkPOSIXLocation::RemoveEmptyDirectory( const AkOSChar* in_pszDirectoryPath )
{
	int iErr = rmdir(in_pszDirectoryPath);
	if (iErr == -1)
		return AK_Fail;

	return AK_Success;
}
