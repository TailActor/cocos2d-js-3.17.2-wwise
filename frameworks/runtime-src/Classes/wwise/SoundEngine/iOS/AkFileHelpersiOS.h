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

#ifndef _AK_FILE_HELPERS_IOS_H_
#define _AK_FILE_HELPERS_IOS_H_

#include <AK/SoundEngine/Common/AkTypes.h>
#include <AK/Tools/Common/AkPlatformFuncs.h>

class CAkFileHelpersiOS
{
public:
	static AKRESULT GetDefaultWritablePath(AkOSChar* out_pszPath, AkUInt32 in_pathMaxSize)
	{
		return AK_NotImplemented; // todo: implement (WG-49033)
	}
};

#endif //_AK_FILE_HELPERS_IOS_H_
