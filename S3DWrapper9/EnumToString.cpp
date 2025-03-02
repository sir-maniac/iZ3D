/* IZ3D_FILE: $Id: Trace.cpp 3062 2010-03-15 02:44:50Z dragon $ 
*
* Project : iZ3D Stereo Driver
* Copyright (C) iZ3D Inc. 2002 - 2010
*
* $Author: dragon $
* $Revision: 3062 $
* $Date: 2010-03-15 05:44:50 +0300$
* $LastChangedBy: dragon $
* $URL: svn://svn.neurok.ru/dev/driver/trunk/S3DWrapper9/Trace.cpp $
*/

#include "stdafx.h"
#include "d3dumddi.h"
#include "D3DInterfaceMethods.h"
#include "..\ZLOg\Detail\Utils.h"

const TCHAR *GetMatrixString(CONST D3DMATRIX *mat, bool bTranspose)
{
	if (!bTranspose)
		return ZLOG_DBG_SPRINTF(
		_T("%12.7f %12.7f %12.7f %12.7f\n")
		_T("%12.7f %12.7f %12.7f %12.7f\n")
		_T("%12.7f %12.7f %12.7f %12.7f\n")
		_T("%12.7f %12.7f %12.7f %12.7f\n"),
		mat->_11, mat->_12, mat->_13, mat->_14,
		mat->_21, mat->_22, mat->_23, mat->_24,
		mat->_31, mat->_32, mat->_33, mat->_34,
		mat->_41, mat->_42, mat->_43, mat->_44 );
	else
		return ZLOG_DBG_SPRINTF(
		_T("%12.7f %12.7f %12.7f %12.7f\n")
		_T("%12.7f %12.7f %12.7f %12.7f\n")
		_T("%12.7f %12.7f %12.7f %12.7f\n")
		_T("%12.7f %12.7f %12.7f %12.7f\n"),
		mat->_11, mat->_21, mat->_31, mat->_41,
		mat->_12, mat->_22, mat->_32, mat->_42,
		mat->_13, mat->_23, mat->_33, mat->_43,
		mat->_14, mat->_24, mat->_34, mat->_44 );
}

const TCHAR *GetFormatString(D3DFORMAT format) 
{
	switch (format) 
	{
		UNPACK_VALUE_T(D3DFMT_UNKNOWN);
		UNPACK_VALUE_T(D3DFMT_R8G8B8);
		UNPACK_VALUE_T(D3DFMT_A8R8G8B8);
		UNPACK_VALUE_T(D3DFMT_X8R8G8B8);
		UNPACK_VALUE_T(D3DFMT_R5G6B5);
		UNPACK_VALUE_T(D3DFMT_X1R5G5B5);
		UNPACK_VALUE_T(D3DFMT_A1R5G5B5);
		UNPACK_VALUE_T(D3DFMT_A4R4G4B4);
		UNPACK_VALUE_T(D3DFMT_R3G3B2);
		UNPACK_VALUE_T(D3DFMT_A8);
		UNPACK_VALUE_T(D3DFMT_A8R3G3B2);
		UNPACK_VALUE_T(D3DFMT_X4R4G4B4);
		UNPACK_VALUE_T(D3DFMT_A2B10G10R10);
		UNPACK_VALUE_T(D3DFMT_A8B8G8R8);
		UNPACK_VALUE_T(D3DFMT_X8B8G8R8);
		UNPACK_VALUE_T(D3DFMT_G16R16);
		UNPACK_VALUE_T(D3DFMT_A2R10G10B10);
		UNPACK_VALUE_T(D3DFMT_A16B16G16R16);
		UNPACK_VALUE_T(D3DFMT_A8P8);
		UNPACK_VALUE_T(D3DFMT_P8);
		UNPACK_VALUE_T(D3DFMT_L8);
		UNPACK_VALUE_T(D3DFMT_A8L8);
		UNPACK_VALUE_T(D3DFMT_A4L4);
		UNPACK_VALUE_T(D3DFMT_V8U8);
		UNPACK_VALUE_T(D3DFMT_L6V5U5);
		UNPACK_VALUE_T(D3DFMT_X8L8V8U8);
		UNPACK_VALUE_T(D3DFMT_Q8W8V8U8);
		UNPACK_VALUE_T(D3DFMT_V16U16);
		UNPACK_VALUE_T(D3DFMT_A2W10V10U10);
		UNPACK_VALUE_T(D3DFMT_UYVY);
		UNPACK_VALUE_T(D3DFMT_R8G8_B8G8);
		UNPACK_VALUE_T(D3DFMT_YUY2);
		UNPACK_VALUE_T(D3DFMT_G8R8_G8B8);
		UNPACK_VALUE_T(D3DFMT_DXT1);
		UNPACK_VALUE_T(D3DFMT_DXT2);
		UNPACK_VALUE_T(D3DFMT_DXT3);
		UNPACK_VALUE_T(D3DFMT_DXT4);
		UNPACK_VALUE_T(D3DFMT_DXT5);
		UNPACK_VALUE_T(D3DFMT_D16_LOCKABLE);
		UNPACK_VALUE_T(D3DFMT_D32);
		UNPACK_VALUE_T(D3DFMT_D15S1);
		UNPACK_VALUE_T(D3DFMT_D24S8);
		UNPACK_VALUE_T(D3DFMT_D24X8);
		UNPACK_VALUE_T(D3DFMT_D24X4S4);
		UNPACK_VALUE_T(D3DFMT_D16);
		UNPACK_VALUE_T(D3DFMT_D32F_LOCKABLE);
		UNPACK_VALUE_T(D3DFMT_D24FS8);
		UNPACK_VALUE_T(D3DFMT_L16);
		UNPACK_VALUE_T(D3DFMT_VERTEXDATA);
		UNPACK_VALUE_T(D3DFMT_INDEX16);
		UNPACK_VALUE_T(D3DFMT_INDEX32);
		UNPACK_VALUE_T(D3DFMT_Q16W16V16U16);
		UNPACK_VALUE_T(D3DFMT_MULTI2_ARGB8);
		UNPACK_VALUE_T(D3DFMT_R16F);
		UNPACK_VALUE_T(D3DFMT_G16R16F);
		UNPACK_VALUE_T(D3DFMT_A16B16G16R16F);
		UNPACK_VALUE_T(D3DFMT_R32F);
		UNPACK_VALUE_T(D3DFMT_G32R32F);
		UNPACK_VALUE_T(D3DFMT_A32B32G32R32F);
		UNPACK_VALUE_T(D3DFMT_CxV8U8);
	};

	return ZLOG_DBG_SPRINTF( _T("\'%c%c%c%c\'"), 
									  (TCHAR)(format & 0xFF), 
									  (TCHAR)((format >> 8) & 0xFF), 
									  (TCHAR)((format >> 16) & 0xFF), 
									  (TCHAR)((format >> 24) & 0xFF) );
}


const TCHAR *GetResourceTypeString(D3DRESOURCETYPE ResType) 
{
	switch (ResType) 
	{
		UNPACK_VALUE_T(D3DRTYPE_SURFACE);
		UNPACK_VALUE_T(D3DRTYPE_VOLUME);
		UNPACK_VALUE_T(D3DRTYPE_TEXTURE);
		UNPACK_VALUE_T(D3DRTYPE_VOLUMETEXTURE);
		UNPACK_VALUE_T(D3DRTYPE_CUBETEXTURE);
		UNPACK_VALUE_T(D3DRTYPE_VERTEXBUFFER);
		UNPACK_VALUE_T(D3DRTYPE_INDEXBUFFER);
	}
	return _T("UNKNOWN");
}


const TCHAR *GetCubeMapFaceTypeString(D3DCUBEMAP_FACES FaceType) 
{
	switch (FaceType) 
	{
	case D3DCUBEMAP_FACE_POSITIVE_X: return _T("+X");    
	case D3DCUBEMAP_FACE_NEGATIVE_X: return _T("-X");    
	case D3DCUBEMAP_FACE_POSITIVE_Y: return _T("+Y");    
	case D3DCUBEMAP_FACE_NEGATIVE_Y: return _T("-Y");    
	case D3DCUBEMAP_FACE_POSITIVE_Z: return _T("+Z");    
	case D3DCUBEMAP_FACE_NEGATIVE_Z: return _T("-Z");    
	}
	return _T("UNKNOWN");
}

const TCHAR *GetMultiSampleString(D3DMULTISAMPLE_TYPE MultiSample)
{
	switch(MultiSample)
	{
		UNPACK_VALUE_T(D3DMULTISAMPLE_NONE);
		UNPACK_VALUE_T(D3DMULTISAMPLE_NONMASKABLE);
		UNPACK_VALUE_T(D3DMULTISAMPLE_2_SAMPLES);
		UNPACK_VALUE_T(D3DMULTISAMPLE_3_SAMPLES);
		UNPACK_VALUE_T(D3DMULTISAMPLE_4_SAMPLES);
		UNPACK_VALUE_T(D3DMULTISAMPLE_5_SAMPLES);
		UNPACK_VALUE_T(D3DMULTISAMPLE_6_SAMPLES);
		UNPACK_VALUE_T(D3DMULTISAMPLE_7_SAMPLES);
		UNPACK_VALUE_T(D3DMULTISAMPLE_8_SAMPLES);
		UNPACK_VALUE_T(D3DMULTISAMPLE_9_SAMPLES);
		UNPACK_VALUE_T(D3DMULTISAMPLE_10_SAMPLES);
		UNPACK_VALUE_T(D3DMULTISAMPLE_11_SAMPLES);
		UNPACK_VALUE_T(D3DMULTISAMPLE_12_SAMPLES);
		UNPACK_VALUE_T(D3DMULTISAMPLE_13_SAMPLES);
		UNPACK_VALUE_T(D3DMULTISAMPLE_14_SAMPLES);
		UNPACK_VALUE_T(D3DMULTISAMPLE_15_SAMPLES);
		UNPACK_VALUE_T(D3DMULTISAMPLE_16_SAMPLES);
		UNPACK_VALUE_T(D3DMULTISAMPLE_FORCE_DWORD);
	};
	return _T("UNKNOWN");
}

const TCHAR *GetUsageString(DWORD Usage) 
{
	if (Usage == 0) 
	{
		return _T("0");
	}
	std::basic_string<TCHAR> str;
	str.reserve(300);
	MERGE_VALUE_T(Usage, D3DUSAGE_RENDERTARGET);
	MERGE_VALUE_T(Usage, D3DUSAGE_DEPTHSTENCIL);
	MERGE_VALUE_T(Usage, D3DUSAGE_DYNAMIC);
	MERGE_VALUE_T(Usage, D3DUSAGE_AUTOGENMIPMAP);
	MERGE_VALUE_T(Usage, D3DUSAGE_DMAP);
	MERGE_VALUE_T(Usage, D3DUSAGE_WRITEONLY);
	MERGE_VALUE_T(Usage, D3DUSAGE_SOFTWAREPROCESSING);
	MERGE_VALUE_T(Usage, D3DUSAGE_DONOTCLIP); 
	MERGE_VALUE_T(Usage, D3DUSAGE_POINTS); 
	MERGE_VALUE_T(Usage, D3DUSAGE_RTPATCHES); 
	MERGE_VALUE_T(Usage, D3DUSAGE_NPATCHES); 
	return ZLOG_DBG_SPRINTF( str.c_str() );
}

const TCHAR *GetPoolString(DWORD Pool) 
{
	switch (Pool) 
	{
		UNPACK_VALUE_T(D3DPOOL_DEFAULT);
		UNPACK_VALUE_T(D3DPOOL_MANAGED);
		UNPACK_VALUE_T(D3DPOOL_SYSTEMMEM);
		UNPACK_VALUE_T(D3DPOOL_SCRATCH);
	};
	return _T("UNKNOWN");
}

const TCHAR *GetTransformTypeString(D3DTRANSFORMSTATETYPE State) 
{
	switch (State) 
	{
		UNPACK_VALUE_T(D3DTS_VIEW );
		UNPACK_VALUE_T(D3DTS_PROJECTION );
		UNPACK_VALUE_T(D3DTS_TEXTURE0 );
		UNPACK_VALUE_T(D3DTS_TEXTURE1 );
		UNPACK_VALUE_T(D3DTS_TEXTURE2 );
		UNPACK_VALUE_T(D3DTS_TEXTURE3 );
		UNPACK_VALUE_T(D3DTS_TEXTURE4 );
		UNPACK_VALUE_T(D3DTS_TEXTURE5 );
		UNPACK_VALUE_T(D3DTS_TEXTURE6 );
		UNPACK_VALUE_T(D3DTS_TEXTURE7 );
		UNPACK_VALUE_T(D3DTS_WORLD);
	default:
		if (State >= 256 && State < 512)
			return _T("D3DTS_WORLDMATRIXn");
	};
	return _T("UNKNOWN");
}

const TCHAR *GetClearRectString(DWORD Count, CONST D3DRECT *pRects)
{
	if (pRects == NULL)
	{
		return _T("NULL");
	}
	std::basic_string<TCHAR> str;
	str.reserve(100 * Count);
	for (ULONG i = 0; i < Count; i++)
	{
		str += std::basic_string<TCHAR>( ZLOG_DBG_SPRINTF( _T("\n\t")
										  _T("pRects[%d].x1 = %d, ")
										  _T("pRects[%d].y1 = %d, ")
										  _T("pRects[%d].x2 = %d, ")
										  _T("pRects[%d].y2 = %d\n\t"),
										  i, pRects[i].x1,
										  i, pRects[i].y1,
										  i, pRects[i].x2,
										  i, pRects[i].y2 ) );
	}
	return ZLOG_DBG_SPRINTF( str.c_str() );
}

const TCHAR *GetClearFlagsString(DWORD Flags)
{
	if (Flags == 0) 
	{
		return _T("0");
	}
	std::basic_string<TCHAR> str;
	str.reserve(70);
	MERGE_VALUE_T(Flags, D3DCLEAR_TARGET);
	MERGE_VALUE_T(Flags, D3DCLEAR_ZBUFFER);
	MERGE_VALUE_T(Flags, D3DCLEAR_STENCIL);
	return ZLOG_DBG_SPRINTF( str.c_str() );
}

const TCHAR * GetLockedRectString( CONST D3DLOCKED_RECT* pLockedRect )
{
	if (pLockedRect == NULL)
	{
		return _T("NULL");
	}
	return ZLOG_DBG_SPRINTF(_T("(pBits = %p, Pitch = %d)"),	
		pLockedRect->pBits, pLockedRect->Pitch);
}

const TCHAR *GetLockFlagString(DWORD Flags)
{
	if (Flags == 0) 
	{
		return _T("0");
	}
	std::basic_string<TCHAR> str;
	str.reserve(200);
	MERGE_VALUE_T(Flags, D3DLOCK_DISCARD);
	MERGE_VALUE_T(Flags, D3DLOCK_DONOTWAIT);
	MERGE_VALUE_T(Flags, D3DLOCK_NO_DIRTY_UPDATE);
	MERGE_VALUE_T(Flags, D3DLOCK_NOOVERWRITE);
	MERGE_VALUE_T(Flags, D3DLOCK_NOSYSLOCK);
	MERGE_VALUE_T(Flags, D3DLOCK_READONLY);
	return ZLOG_DBG_SPRINTF( str.c_str() );
}

const TCHAR *GetPrimitiveTypeString( D3DPRIMITIVETYPE PrimitiveType ) 
{
	switch (PrimitiveType)
	{
		UNPACK_VALUE_T(D3DPT_POINTLIST);
		UNPACK_VALUE_T(D3DPT_LINELIST);
		UNPACK_VALUE_T(D3DPT_LINESTRIP);
		UNPACK_VALUE_T(D3DPT_TRIANGLELIST);
		UNPACK_VALUE_T(D3DPT_TRIANGLESTRIP);
		UNPACK_VALUE_T(D3DPT_TRIANGLEFAN);
	};
	return _T("UNKNOWN");
}

const TCHAR *GetTextureFilterTypeString(D3DTEXTUREFILTERTYPE Filter)
{
	switch (Filter)
	{
		UNPACK_VALUE_T(D3DTEXF_NONE);
		UNPACK_VALUE_T(D3DTEXF_POINT);
		UNPACK_VALUE_T(D3DTEXF_LINEAR);
		UNPACK_VALUE_T(D3DTEXF_ANISOTROPIC);
		UNPACK_VALUE_T(D3DTEXF_PYRAMIDALQUAD);
		UNPACK_VALUE_T(D3DTEXF_GAUSSIANQUAD);
	};
	return _T("UNKNOWN");
}

const TCHAR* GetFVFString(DWORD FVF) 
{
	if (FVF == 0) 
	{
		return _T("0");
	}
	std::basic_string<TCHAR> str;
	str.reserve(500);
	DWORD Position = FVF & D3DFVF_POSITION_MASK;
	switch (Position)
	{
		UNPACK_MERGE_VALUE_T(D3DFVF_XYZ);
		UNPACK_MERGE_VALUE_T(D3DFVF_XYZRHW);
		UNPACK_MERGE_VALUE_T(D3DFVF_XYZB1);
		UNPACK_MERGE_VALUE_T(D3DFVF_XYZB2);
		UNPACK_MERGE_VALUE_T(D3DFVF_XYZB3);
		UNPACK_MERGE_VALUE_T(D3DFVF_XYZB4);
		UNPACK_MERGE_VALUE_T(D3DFVF_XYZB5);
		UNPACK_MERGE_VALUE_T(D3DFVF_XYZW);
	};

	MERGE_VALUE_T(FVF, D3DFVF_NORMAL);
	MERGE_VALUE_T(FVF, D3DFVF_PSIZE);
	MERGE_VALUE_T(FVF, D3DFVF_DIFFUSE);
	MERGE_VALUE_T(FVF, D3DFVF_SPECULAR);

	DWORD TexCount = FVF & D3DFVF_TEXCOUNT_MASK;
	switch (TexCount)
	{
		UNPACK_MERGE_VALUE_T(D3DFVF_TEX0);
		UNPACK_MERGE_VALUE_T(D3DFVF_TEX1);
		UNPACK_MERGE_VALUE_T(D3DFVF_TEX2);
		UNPACK_MERGE_VALUE_T(D3DFVF_TEX3);
		UNPACK_MERGE_VALUE_T(D3DFVF_TEX4);
		UNPACK_MERGE_VALUE_T(D3DFVF_TEX5);
		UNPACK_MERGE_VALUE_T(D3DFVF_TEX6);
		UNPACK_MERGE_VALUE_T(D3DFVF_TEX7);
		UNPACK_MERGE_VALUE_T(D3DFVF_TEX8);
	};

	MERGE_VALUE_T(FVF, D3DFVF_RESERVED0);
	MERGE_VALUE_T(FVF, D3DFVF_LASTBETA_UBYTE4);
	MERGE_VALUE_T(FVF, D3DFVF_LASTBETA_D3DCOLOR);
	MERGE_VALUE_T(FVF, D3DFVF_RESERVED2);
	return ZLOG_DBG_SPRINTF( str.c_str() );
}

const TCHAR *GetDisplayModeString(const D3DDISPLAYMODE *pMode)
{
	if (!pMode)
	{
		return _T("NULL");
	}
	return ZLOG_DBG_SPRINTF(
		_T("Width = %d, Height = %d, RefreshRate = %d, Format = %s"),
		pMode->Width, pMode->Height, pMode->RefreshRate, GetFormatString(pMode->Format));
}

const TCHAR *GetDisplayModeExString(const D3DDISPLAYMODEEX *pMode)
{
	if (!pMode)
	{
		return _T("NULL");
	}
	return ZLOG_DBG_SPRINTF(
		_T("\n\tWidth = %d, Height = %d, RefreshRate = %d, Format = %s, ScanLineOrdering = %d\n\t"),
		pMode->Width, pMode->Height, pMode->RefreshRate, GetFormatString(pMode->Format), pMode->ScanLineOrdering);
}

const TCHAR *GetDisplayModeRotationString(const D3DDISPLAYROTATION *pRotation)
{
	if (!pRotation)
	{
		return _T("NULL");
	}

	switch (*pRotation)
	{
		UNPACK_VALUE_T(D3DDISPLAYROTATION_IDENTITY);
		UNPACK_VALUE_T(D3DDISPLAYROTATION_90);
		UNPACK_VALUE_T(D3DDISPLAYROTATION_180);
		UNPACK_VALUE_T(D3DDISPLAYROTATION_270);
	};
	return _T("UNKNOWN");
}

const TCHAR *GetSwapEffectString(D3DSWAPEFFECT SwapEffect)
{
	switch (SwapEffect)
	{
		UNPACK_VALUE_T(D3DSWAPEFFECT_DISCARD);
		UNPACK_VALUE_T(D3DSWAPEFFECT_FLIP);
		UNPACK_VALUE_T(D3DSWAPEFFECT_COPY);
	};
	return _T("UNKNOWN");
}

const TCHAR *GetPresentFlagString(DWORD Flags)
{
	if (Flags == 0) 
	{
		return _T("0");
	}
	std::basic_string<TCHAR> str;
	str.reserve(100);
	MERGE_VALUE_T(Flags, D3DPRESENTFLAG_LOCKABLE_BACKBUFFER);
	MERGE_VALUE_T(Flags, D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL);
	MERGE_VALUE_T(Flags, D3DPRESENTFLAG_DEVICECLIP);
	MERGE_VALUE_T(Flags, D3DPRESENTFLAG_VIDEO);
	return ZLOG_DBG_SPRINTF( str.c_str() );
}

const TCHAR *GetPresentationIntervalString(UINT Present)
{
	if (Present == 0) 
	{
		return _T("0");
	}
	std::basic_string<TCHAR> str;
	str.reserve(200);
	MERGE_VALUE_T(Present, D3DPRESENT_INTERVAL_DEFAULT);
	MERGE_VALUE_T(Present, D3DPRESENT_INTERVAL_ONE);
	MERGE_VALUE_T(Present, D3DPRESENT_INTERVAL_TWO);
	MERGE_VALUE_T(Present, D3DPRESENT_INTERVAL_THREE);
	MERGE_VALUE_T(Present, D3DPRESENT_INTERVAL_FOUR);
	MERGE_VALUE_T(Present, D3DPRESENT_INTERVAL_IMMEDIATE);
	return ZLOG_DBG_SPRINTF( str.c_str() );
}

const TCHAR *GetFlipIntervalString( DWORD Interval ) 
{
	switch ( Interval )
	{	
		UNPACK_VALUE_T(D3DDDI_FLIPINTERVAL_IMMEDIATE);
		UNPACK_VALUE_T(D3DDDI_FLIPINTERVAL_ONE);
		UNPACK_VALUE_T(D3DDDI_FLIPINTERVAL_TWO);
		UNPACK_VALUE_T(D3DDDI_FLIPINTERVAL_THREE);
		UNPACK_VALUE_T(D3DDDI_FLIPINTERVAL_FOUR);
	}
	return _T("UNKNOWN");
}

const TCHAR *GetPresentFlagsString(UINT Present)
{
	if (Present == 0) 
	{
		return _T("0");
	}
	std::basic_string<TCHAR> str;
	str.reserve(100);
	MERGE_VALUE_T(Present, D3DPRESENT_DONOTWAIT);
	MERGE_VALUE_T(Present, D3DPRESENT_LINEAR_CONTENT);
	//UNPACK_DEFINE(Present, D3DPRESENT_DONOTFLIP);
	return ZLOG_DBG_SPRINTF( str.c_str() );
}

const TCHAR *GetPresentationParametersString(const D3DPRESENT_PARAMETERS *pPresentationParameters)
{
	return ZLOG_DBG_SPRINTF(
		_T("\n\tBackBufferWidth = %u\n\t")
		_T("BackBufferHeight = %u\n\t")
		_T("BackBufferFormat = %s\n\t")
		_T("BackBufferCount = %u\n\t")
		_T("MultiSampleType = %s\n\t")
		_T("MultiSampleQuality = %d\n\t")
		_T("SwapEffect = %s\n\t")
		_T("hDeviceWindow = %p\n\t")
		_T("Windowed = %1d\n\t")
		_T("EnableAutoDepthStencil = %1d\n\t")
		_T("AutoDepthStencilFormat = %s\n\t")
		_T("Flags = %s\n\t")
		_T("FullScreen_RefreshRateInHz = %u\n\t")
		_T("PresentationInterval = %s\n\t"), 
		pPresentationParameters->BackBufferWidth, 
		pPresentationParameters->BackBufferHeight,
		GetFormatString(pPresentationParameters->BackBufferFormat),
		pPresentationParameters->BackBufferCount,
		GetMultiSampleString(pPresentationParameters->MultiSampleType),
		pPresentationParameters->MultiSampleQuality,
		GetSwapEffectString(pPresentationParameters->SwapEffect),
		pPresentationParameters->hDeviceWindow,
		pPresentationParameters->Windowed,
		pPresentationParameters->EnableAutoDepthStencil,
		GetFormatString(pPresentationParameters->AutoDepthStencilFormat),
		GetPresentFlagString(pPresentationParameters->Flags),
		pPresentationParameters->FullScreen_RefreshRateInHz,
		GetPresentationIntervalString(pPresentationParameters->PresentationInterval));
}

const TCHAR *GetRenderStateString(D3DRENDERSTATETYPE state) 
{
	switch (state)
	{
		UNPACK_VALUE_T(D3DRS_ZENABLE);
		UNPACK_VALUE_T(D3DRS_FILLMODE);
		UNPACK_VALUE_T(D3DRS_SHADEMODE);
		UNPACK_VALUE_T(D3DRS_ZWRITEENABLE);
		UNPACK_VALUE_T(D3DRS_ALPHATESTENABLE);
		UNPACK_VALUE_T(D3DRS_LASTPIXEL);
		UNPACK_VALUE_T(D3DRS_SRCBLEND);
		UNPACK_VALUE_T(D3DRS_DESTBLEND);
		UNPACK_VALUE_T(D3DRS_CULLMODE);
		UNPACK_VALUE_T(D3DRS_ZFUNC);
		UNPACK_VALUE_T(D3DRS_ALPHAREF);
		UNPACK_VALUE_T(D3DRS_ALPHAFUNC);
		UNPACK_VALUE_T(D3DRS_DITHERENABLE);
		UNPACK_VALUE_T(D3DRS_ALPHABLENDENABLE);
		UNPACK_VALUE_T(D3DRS_FOGENABLE);
		UNPACK_VALUE_T(D3DRS_SPECULARENABLE);
		UNPACK_VALUE_T(D3DRS_FOGCOLOR);
		UNPACK_VALUE_T(D3DRS_FOGTABLEMODE);
		UNPACK_VALUE_T(D3DRS_FOGSTART);
		UNPACK_VALUE_T(D3DRS_FOGEND);
		UNPACK_VALUE_T(D3DRS_FOGDENSITY);
		UNPACK_VALUE_T(D3DRS_RANGEFOGENABLE);
		UNPACK_VALUE_T(D3DRS_STENCILENABLE);
		UNPACK_VALUE_T(D3DRS_STENCILFAIL);
		UNPACK_VALUE_T(D3DRS_STENCILZFAIL);
		UNPACK_VALUE_T(D3DRS_STENCILPASS);
		UNPACK_VALUE_T(D3DRS_STENCILFUNC);
		UNPACK_VALUE_T(D3DRS_STENCILREF);
		UNPACK_VALUE_T(D3DRS_STENCILMASK);
		UNPACK_VALUE_T(D3DRS_STENCILWRITEMASK);
		UNPACK_VALUE_T(D3DRS_TEXTUREFACTOR);
		UNPACK_VALUE_T(D3DRS_WRAP0);
		UNPACK_VALUE_T(D3DRS_WRAP1);
		UNPACK_VALUE_T(D3DRS_WRAP2);
		UNPACK_VALUE_T(D3DRS_WRAP3);
		UNPACK_VALUE_T(D3DRS_WRAP4);
		UNPACK_VALUE_T(D3DRS_WRAP5);
		UNPACK_VALUE_T(D3DRS_WRAP6);
		UNPACK_VALUE_T(D3DRS_WRAP7);
		UNPACK_VALUE_T(D3DRS_CLIPPING);
		UNPACK_VALUE_T(D3DRS_LIGHTING);
		UNPACK_VALUE_T(D3DRS_AMBIENT);
		UNPACK_VALUE_T(D3DRS_FOGVERTEXMODE);
		UNPACK_VALUE_T(D3DRS_COLORVERTEX);
		UNPACK_VALUE_T(D3DRS_LOCALVIEWER);
		UNPACK_VALUE_T(D3DRS_NORMALIZENORMALS);
		UNPACK_VALUE_T(D3DRS_DIFFUSEMATERIALSOURCE);
		UNPACK_VALUE_T(D3DRS_SPECULARMATERIALSOURCE);
		UNPACK_VALUE_T(D3DRS_AMBIENTMATERIALSOURCE);
		UNPACK_VALUE_T(D3DRS_EMISSIVEMATERIALSOURCE);
		UNPACK_VALUE_T(D3DRS_VERTEXBLEND);
		UNPACK_VALUE_T(D3DRS_CLIPPLANEENABLE);
		UNPACK_VALUE_T(D3DRS_POINTSIZE);
		UNPACK_VALUE_T(D3DRS_POINTSIZE_MIN);
		UNPACK_VALUE_T(D3DRS_POINTSPRITEENABLE);
		UNPACK_VALUE_T(D3DRS_POINTSCALEENABLE);
		UNPACK_VALUE_T(D3DRS_POINTSCALE_A);
		UNPACK_VALUE_T(D3DRS_POINTSCALE_B);
		UNPACK_VALUE_T(D3DRS_POINTSCALE_C);
		UNPACK_VALUE_T(D3DRS_MULTISAMPLEANTIALIAS);
		UNPACK_VALUE_T(D3DRS_MULTISAMPLEMASK);
		UNPACK_VALUE_T(D3DRS_PATCHEDGESTYLE);
		UNPACK_VALUE_T(D3DRS_DEBUGMONITORTOKEN);
		UNPACK_VALUE_T(D3DRS_POINTSIZE_MAX);
		UNPACK_VALUE_T(D3DRS_INDEXEDVERTEXBLENDENABLE);
		UNPACK_VALUE_T(D3DRS_COLORWRITEENABLE);
		UNPACK_VALUE_T(D3DRS_TWEENFACTOR);
		UNPACK_VALUE_T(D3DRS_BLENDOP);
		UNPACK_VALUE_T(D3DRS_POSITIONDEGREE);
		UNPACK_VALUE_T(D3DRS_NORMALDEGREE);
		UNPACK_VALUE_T(D3DRS_SCISSORTESTENABLE);
		UNPACK_VALUE_T(D3DRS_SLOPESCALEDEPTHBIAS);
		UNPACK_VALUE_T(D3DRS_ANTIALIASEDLINEENABLE);
		UNPACK_VALUE_T(D3DRS_MINTESSELLATIONLEVEL);
		UNPACK_VALUE_T(D3DRS_MAXTESSELLATIONLEVEL);
		UNPACK_VALUE_T(D3DRS_ADAPTIVETESS_X);
		UNPACK_VALUE_T(D3DRS_ADAPTIVETESS_Y);
		UNPACK_VALUE_T(D3DRS_ADAPTIVETESS_Z);
		UNPACK_VALUE_T(D3DRS_ADAPTIVETESS_W);
		UNPACK_VALUE_T(D3DRS_ENABLEADAPTIVETESSELLATION);
		UNPACK_VALUE_T(D3DRS_TWOSIDEDSTENCILMODE);
		UNPACK_VALUE_T(D3DRS_CCW_STENCILFAIL);
		UNPACK_VALUE_T(D3DRS_CCW_STENCILZFAIL);
		UNPACK_VALUE_T(D3DRS_CCW_STENCILPASS);
		UNPACK_VALUE_T(D3DRS_CCW_STENCILFUNC);
		UNPACK_VALUE_T(D3DRS_COLORWRITEENABLE1);
		UNPACK_VALUE_T(D3DRS_COLORWRITEENABLE2);
		UNPACK_VALUE_T(D3DRS_COLORWRITEENABLE3);
		UNPACK_VALUE_T(D3DRS_BLENDFACTOR);
		UNPACK_VALUE_T(D3DRS_SRGBWRITEENABLE);
		UNPACK_VALUE_T(D3DRS_DEPTHBIAS);
		UNPACK_VALUE_T(D3DRS_WRAP8);
		UNPACK_VALUE_T(D3DRS_WRAP9);
		UNPACK_VALUE_T(D3DRS_WRAP10);
		UNPACK_VALUE_T(D3DRS_WRAP11);
		UNPACK_VALUE_T(D3DRS_WRAP12);
		UNPACK_VALUE_T(D3DRS_WRAP13);
		UNPACK_VALUE_T(D3DRS_WRAP14);
		UNPACK_VALUE_T(D3DRS_WRAP15);
		UNPACK_VALUE_T(D3DRS_SEPARATEALPHABLENDENABLE);
		UNPACK_VALUE_T(D3DRS_SRCBLENDALPHA);
		UNPACK_VALUE_T(D3DRS_DESTBLENDALPHA);
		UNPACK_VALUE_T(D3DRS_BLENDOPALPHA);
	};
	return _T("UNKNOWN");
}

const TCHAR *GetTextureStageStateTypeString( D3DTEXTURESTAGESTATETYPE Type ) 
{
	switch ( Type )
	{	
		UNPACK_VALUE_T(D3DTSS_COLOROP);
		UNPACK_VALUE_T(D3DTSS_COLORARG1);
		UNPACK_VALUE_T(D3DTSS_COLORARG2);
		UNPACK_VALUE_T(D3DTSS_ALPHAOP);
		UNPACK_VALUE_T(D3DTSS_ALPHAARG1);
		UNPACK_VALUE_T(D3DTSS_ALPHAARG2);
		UNPACK_VALUE_T(D3DTSS_BUMPENVMAT00);
		UNPACK_VALUE_T(D3DTSS_BUMPENVMAT01);
		UNPACK_VALUE_T(D3DTSS_BUMPENVMAT10);
		UNPACK_VALUE_T(D3DTSS_BUMPENVMAT11);
		UNPACK_VALUE_T(D3DTSS_TEXCOORDINDEX);
		UNPACK_VALUE_T(D3DTSS_BUMPENVLSCALE);
		UNPACK_VALUE_T(D3DTSS_BUMPENVLOFFSET);
		UNPACK_VALUE_T(D3DTSS_TEXTURETRANSFORMFLAGS);
		UNPACK_VALUE_T(D3DTSS_COLORARG0);
		UNPACK_VALUE_T(D3DTSS_ALPHAARG0);
		UNPACK_VALUE_T(D3DTSS_RESULTARG);
		UNPACK_VALUE_T(D3DTSS_CONSTANT);
	}
	return _T("UNKNOWN");
}

const TCHAR *GetSamplerStateTypeString(D3DSAMPLERSTATETYPE Type)
{
	switch (Type)
	{
		UNPACK_VALUE_T(D3DSAMP_ADDRESSU);
		UNPACK_VALUE_T(D3DSAMP_ADDRESSV);
		UNPACK_VALUE_T(D3DSAMP_ADDRESSW);
		UNPACK_VALUE_T(D3DSAMP_BORDERCOLOR);
		UNPACK_VALUE_T(D3DSAMP_MAGFILTER);
		UNPACK_VALUE_T(D3DSAMP_MINFILTER);
		UNPACK_VALUE_T(D3DSAMP_MIPFILTER);
		UNPACK_VALUE_T(D3DSAMP_MIPMAPLODBIAS);
		UNPACK_VALUE_T(D3DSAMP_MAXMIPLEVEL);
		UNPACK_VALUE_T(D3DSAMP_MAXANISOTROPY);
		UNPACK_VALUE_T(D3DSAMP_SRGBTEXTURE);
		UNPACK_VALUE_T(D3DSAMP_ELEMENTINDEX);
		UNPACK_VALUE_T(D3DSAMP_DMAPOFFSET);
	}
	return _T("UNKNOWN");
}

const TCHAR *GetOffsetString(const SIZE *pOffset)
{
	if (!pOffset)
	{
		return _T("NULL");
	}
	return ZLOG_DBG_SPRINTF(
		_T("(X = %d, Y = %d)"), pOffset->cx, pOffset->cy);
}

const TCHAR *GetViewPortString(const D3DVIEWPORT9 *pViewport)
{
	if (!pViewport)
	{
		return _T("NULL");
	}
	return ZLOG_DBG_SPRINTF(
		_T("X = %d, Y = %d, Width = %d, Height = %d, MinZ = %6.4f, MaxZ = %6.4f"), 
		pViewport->X, pViewport->Y, pViewport->Width, pViewport->Height, pViewport->MinZ, pViewport->MaxZ);
}

const TCHAR *GetDeviceTypeString(D3DDEVTYPE DeviceType)
{
	switch (DeviceType)
	{
		UNPACK_VALUE_T(D3DDEVTYPE_HAL);
		UNPACK_VALUE_T(D3DDEVTYPE_NULLREF);
		UNPACK_VALUE_T(D3DDEVTYPE_REF);
		UNPACK_VALUE_T(D3DDEVTYPE_SW);
	}
	return _T("UNKNOWN");
}

const TCHAR *GetBehaviorFlagsString(DWORD BehaviorFlags) 
{
	if (BehaviorFlags == 0) 
	{
		return _T("0");
	}
	std::basic_string<TCHAR> str;
	str.reserve(500);
	MERGE_VALUE_T(BehaviorFlags, D3DCREATE_FPU_PRESERVE);
	MERGE_VALUE_T(BehaviorFlags, D3DCREATE_MULTITHREADED);
	MERGE_VALUE_T(BehaviorFlags, D3DCREATE_PUREDEVICE);
	MERGE_VALUE_T(BehaviorFlags, D3DCREATE_SOFTWARE_VERTEXPROCESSING);
	MERGE_VALUE_T(BehaviorFlags, D3DCREATE_HARDWARE_VERTEXPROCESSING);
	MERGE_VALUE_T(BehaviorFlags, D3DCREATE_MIXED_VERTEXPROCESSING);
	MERGE_VALUE_T(BehaviorFlags, D3DCREATE_DISABLE_DRIVER_MANAGEMENT);
	MERGE_VALUE_T(BehaviorFlags, D3DCREATE_ADAPTERGROUP_DEVICE);
	MERGE_VALUE_T(BehaviorFlags, D3DCREATE_DISABLE_DRIVER_MANAGEMENT_EX);
	MERGE_VALUE_T(BehaviorFlags, D3DCREATE_NOWINDOWCHANGES);
	return ZLOG_DBG_SPRINTF( str.c_str() );
}

const TCHAR *GetPipelineString(PIPELINE Pipeline)
{
	switch (Pipeline)
	{
		UNPACK_VALUE_T(Fixed);
		UNPACK_VALUE_T(Shader);
		UNPACK_VALUE_T(RHW);
		UNPACK_VALUE_T(RHWEmul);
	};
	return _T("UNKNOWN");
}

const TCHAR *GetTextureTypeString(TextureType Type)
{
	switch (Type)
	{
		UNPACK_VALUE_T(Mono);
		UNPACK_VALUE_T(Stereo);
		UNPACK_VALUE_T(Cleared);
	};
	return _T("UNKNOWN");
}

const TCHAR* GetDirect3D9MethodName(int id)
{
	using namespace IDirect3D9MethodNames;
	switch(id)
	{
		/*** IUnknown methods ***/						
	case _QueryInterface_:				return _T("IDirect3D9::QueryInterface");
	case _AddRef_:						return _T("IDirect3D9::AddRef");
	case _Release_:						return _T("IDirect3D9::Release");

		/*** IDirect3D9 methods ***/						
	case _GetAdapterCount_:				return _T("IDirect3D9::GetAdapterCount");
	case _GetAdapterIdentifier_:		return _T("IDirect3D9::GetAdapterIdentifier");
	case _GetAdapterModeCount_:			return _T("IDirect3D9::GetAdapterModeCount");
	case _EnumAdapterModes_:			return _T("IDirect3D9::EnumAdapterModes");
	case _GetAdapterDisplayMode_:		return _T("IDirect3D9::GetAdapterDisplayMode");
	case _CheckDeviceType_:				return _T("IDirect3D9::CheckDeviceType");
	case _CheckDeviceFormat_:			return _T("IDirect3D9::CheckDeviceFormat");
	case _CheckDeviceMultiSampleType_:	return _T("IDirect3D9::CheckDeviceMultiSampleType");
	case _CheckDepthStencilMatch_:		return _T("IDirect3D9::CheckDepthStencilMatch");
	case _CheckDeviceFormatConversion_: return _T("IDirect3D9::CheckDeviceFormatConversion");
	case _GetDeviceCaps_:				return _T("IDirect3D9::GetDeviceCaps");
	case _GetAdapterMonitor_:			return _T("IDirect3D9::GetAdapterMonitor");
	case _CreateDevice_:				return _T("IDirect3D9::CreateDevice");

		/*** IDirect3D9Ex  methods ***/						
	case _GetAdapterModeCountEx_:		return _T("IDirect3D9::GetAdapterModeCountEx");
	case _EnumAdapterModesEx_:			return _T("IDirect3D9::EnumAdapterModesEx");
	case _GetAdapterDisplayModeEx_:		return _T("IDirect3D9::GetAdapterDisplayModeEx");
	case _CreateDeviceEx_:				return _T("IDirect3D9::CreateDeviceEx");
	case _GetAdapterLUID_:				return _T("IDirect3D9::GetAdapterLUID");

	default:							return _T("IDirect3D9::OTHER");
	}
}

const TCHAR* GetSwapChain9MethodName(int id)
{
	using namespace IDirect3DSwapChain9MethodNames;
	switch(id)
	{
		/*** IUnknown methods ***/						
	case _QueryInterface_:				return _T("IDirect3DSwapChain9::QueryInterface");
	case _AddRef_:						return _T("IDirect3DSwapChain9::AddRef");
	case _Release_:						return _T("IDirect3DSwapChain9::Release");

		/*** IDirect3DSwapChain9 methods ***/						
	case _Present_:						return _T("IDirect3DSwapChain9::Present");
	case _GetFrontBufferData_:			return _T("IDirect3DSwapChain9::GetFrontBufferData");
	case _GetBackBuffer_:				return _T("IDirect3DSwapChain9::GetBackBuffer");
	case _GetRasterStatus_:				return _T("IDirect3DSwapChain9::GetRasterStatus");
	case _GetDisplayMode_:				return _T("IDirect3DSwapChain9::GetDisplayMode");
	case _GetDevice_:					return _T("IDirect3DSwapChain9::GetDevice");
	case _GetPresentParameters_:		return _T("IDirect3DSwapChain9::GetPresentParameters");

		/*** IDirect3DSwapChain9Ex  methods ***/						
	case _GetLastPresentCount_:			return _T("IDirect3DSwapChain9::GetLastPresentCount");
	case _GetPresentStats_:				return _T("IDirect3DSwapChain9::GetPresentStats");
	case _GetDisplayModeEx_:			return _T("IDirect3DSwapChain9::GetDisplayModeEx");

	default:							return _T("IDirect3DSwapChain9::OTHER");
	}
}

const TCHAR* GetD3DDevice9MethodName(int id)
{
	using namespace IDirect3DDevice9MethodNames;
	switch(id)
	{
		/*** IUnknown methods ***/						
	case _QueryInterface_:				return _T("IDirect3DDevice9::QueryInterface");
	case _AddRef_:						return _T("IDirect3DDevice9::AddRef");
	case _Release_:						return _T("IDirect3DDevice9::Release");

		/*** IDirect3DDevice9 methods ***/
	case _TestCooperativeLevel_:		return _T("IDirect3DDevice9::TestCooperativeLevel");
	case _GetAvailableTextureMem_:		return _T("IDirect3DDevice9::GetAvailableTextureMem");
	case _EvictManagedResources_:		return _T("IDirect3DDevice9::EvictManagedResources");
	case _GetDirect3D_:					return _T("IDirect3DDevice9::GetDirect3D");
	case _GetDeviceCaps_:				return _T("IDirect3DDevice9::GetDeviceCaps");
	case _GetDisplayMode_:				return _T("IDirect3DDevice9::GetDisplayMode");
	case _GetCreationParameters_:		return _T("IDirect3DDevice9::GetCreationParameters");
	case _SetCursorProperties_:			return _T("IDirect3DDevice9::SetCursorProperties");
	case _SetCursorPosition_:			return _T("IDirect3DDevice9::SetCursorPosition");
	case _ShowCursor_:					return _T("IDirect3DDevice9::ShowCursor");
	case _CreateAdditionalSwapChain_:	return _T("IDirect3DDevice9::CreateAdditionalSwapChain");
	case _GetSwapChain_:				return _T("IDirect3DDevice9::GetSwapChain");
	case _GetNumberOfSwapChains_:		return _T("IDirect3DDevice9::GetNumberOfSwapChains");
	case _Reset_:						return _T("IDirect3DDevice9::Reset");
	case _Present_:						return _T("IDirect3DDevice9::Present");
	case _GetBackBuffer_:				return _T("IDirect3DDevice9::GetBackBuffer");
	case _GetRasterStatus_:				return _T("IDirect3DDevice9::GetRasterStatus");
	case _SetDialogBoxMode_:			return _T("IDirect3DDevice9::SetDialogBoxMode");
	case _SetGammaRamp_:				return _T("IDirect3DDevice9::SetGammaRamp");
	case _GetGammaRamp_:				return _T("IDirect3DDevice9::GetGammaRamp");
	case _CreateTexture_:				return _T("IDirect3DDevice9::CreateTexture");
	case _CreateVolumeTexture_:			return _T("IDirect3DDevice9::CreateVolumeTexture");
	case _CreateCubeTexture_:			return _T("IDirect3DDevice9::CreateCubeTexture");
	case _CreateVertexBuffer_:			return _T("IDirect3DDevice9::CreateVertexBuffer");
	case _CreateIndexBuffer_:			return _T("IDirect3DDevice9::CreateIndexBuffer");
	case _CreateRenderTarget_:			return _T("IDirect3DDevice9::CreateRenderTarget");
	case _CreateDepthStencilSurface_:	return _T("IDirect3DDevice9::CreateDepthStencilSurface");
	case _UpdateSurface_:				return _T("IDirect3DDevice9::UpdateSurface");
	case _UpdateTexture_:				return _T("IDirect3DDevice9::UpdateTexture");
	case _GetRenderTargetData_:			return _T("IDirect3DDevice9::GetRenderTargetData");
	case _GetFrontBufferData_:			return _T("IDirect3DDevice9::GetFrontBufferData");
	case _StretchRect_:					return _T("IDirect3DDevice9::StretchRect");
	case _ColorFill_:					return _T("IDirect3DDevice9::ColorFill");
	case _CreateOffscreenPlainSurface_: return _T("IDirect3DDevice9::CreateOffscreenPlainSurface");
	case _SetRenderTarget_:				return _T("IDirect3DDevice9::SetRenderTarget");
	case _GetRenderTarget_:				return _T("IDirect3DDevice9::GetRenderTarget");
	case _SetDepthStencilSurface_:		return _T("IDirect3DDevice9::SetDepthStencilSurface");
	case _GetDepthStencilSurface_:		return _T("IDirect3DDevice9::GetDepthStencilSurface");
	case _BeginScene_:					return _T("IDirect3DDevice9::BeginScene");
	case _EndScene_:					return _T("IDirect3DDevice9::EndScene");
	case _Clear_:						return _T("IDirect3DDevice9::Clear");
	case _SetTransform_:				return _T("IDirect3DDevice9::SetTransform");
	case _GetTransform_:				return _T("IDirect3DDevice9::GetTransform");
	case _MultiplyTransform_:			return _T("IDirect3DDevice9::MultiplyTransform");
	case _SetViewport_:					return _T("IDirect3DDevice9::SetViewport");
	case _GetViewport_:					return _T("IDirect3DDevice9::GetViewport");
	case _SetMaterial_:					return _T("IDirect3DDevice9::SetMaterial");
	case _GetMaterial_:					return _T("IDirect3DDevice9::GetMaterial");
	case _SetLight_:					return _T("IDirect3DDevice9::SetLight");
	case _GetLight_:					return _T("IDirect3DDevice9::GetLight");
	case _LightEnable_:					return _T("IDirect3DDevice9::LightEnable");
	case _GetLightEnable_:				return _T("IDirect3DDevice9::GetLightEnable");
	case _SetClipPlane_:				return _T("IDirect3DDevice9::SetClipPlane");
	case _GetClipPlane_:				return _T("IDirect3DDevice9::GetClipPlane");
	case _SetRenderState_:				return _T("IDirect3DDevice9::SetRenderState");
	case _GetRenderState_:				return _T("IDirect3DDevice9::GetRenderState");
	case _CreateStateBlock_:			return _T("IDirect3DDevice9::CreateStateBlock");
	case _BeginStateBlock_:				return _T("IDirect3DDevice9::BeginStateBlock");
	case _EndStateBlock_:				return _T("IDirect3DDevice9::EndStateBlock");
	case _SetClipStatus_:				return _T("IDirect3DDevice9::SetClipStatus");
	case _GetClipStatus_:				return _T("IDirect3DDevice9::GetClipStatus");
	case _GetTexture_:					return _T("IDirect3DDevice9::GetTexture");
	case _SetTexture_:					return _T("IDirect3DDevice9::SetTexture");
	case _GetTextureStageState_:		return _T("IDirect3DDevice9::GetTextureStageState");
	case _SetTextureStageState_:		return _T("IDirect3DDevice9::SetTextureStageState");
	case _GetSamplerState_:				return _T("IDirect3DDevice9::GetSamplerState");
	case _SetSamplerState_:				return _T("IDirect3DDevice9::SetSamplerState");
	case _ValidateDevice_:				return _T("IDirect3DDevice9::ValidateDevice");
	case _SetPaletteEntries_:			return _T("IDirect3DDevice9::SetPaletteEntries");
	case _GetPaletteEntries_:			return _T("IDirect3DDevice9::GetPaletteEntries");
	case _SetCurrentTexturePalette_:	return _T("IDirect3DDevice9::SetCurrentTexturePalette");
	case _GetCurrentTexturePalette_:	return _T("IDirect3DDevice9::GetCurrentTexturePalette");
	case _SetScissorRect_:				return _T("IDirect3DDevice9::SetScissorRect");
	case _GetScissorRect_:				return _T("IDirect3DDevice9::GetScissorRect");
	case _SetSoftwareVertexProcessing_:	return _T("IDirect3DDevice9::SetSoftwareVertexProcessing");
	case _GetSoftwareVertexProcessing_: return _T("IDirect3DDevice9::GetSoftwareVertexProcessing");
	case _SetNPatchMode_:				return _T("IDirect3DDevice9::SetNPatchMode");
	case _GetNPatchMode_:				return _T("IDirect3DDevice9::GetNPatchMode");
	case _DrawPrimitive_:				return _T("IDirect3DDevice9::DrawPrimitive");
	case _DrawIndexedPrimitive_:		return _T("IDirect3DDevice9::DrawIndexedPrimitive");
	case _DrawPrimitiveUP_:				return _T("IDirect3DDevice9::DrawPrimitiveUP");
	case _DrawIndexedPrimitiveUP_:		return _T("IDirect3DDevice9::DrawIndexedPrimitiveUP");
	case _ProcessVertices_:				return _T("IDirect3DDevice9::ProcessVertices");
	case _CreateVertexDeclaration_:		return _T("IDirect3DDevice9::CreateVertexDeclaration");
	case _SetVertexDeclaration_:		return _T("IDirect3DDevice9::SetVertexDeclaration");
	case _GetVertexDeclaration_:		return _T("IDirect3DDevice9::GetVertexDeclaration");
	case _SetFVF_:						return _T("IDirect3DDevice9::SetFVF");
	case _GetFVF_:						return _T("IDirect3DDevice9::GetFVF");
	case _CreateVertexShader_:			return _T("IDirect3DDevice9::CreateVertexShader");
	case _SetVertexShader_:				return _T("IDirect3DDevice9::SetVertexShader");
	case _GetVertexShader_:				return _T("IDirect3DDevice9::GetVertexShader");
	case _SetVertexShaderConstantF_:	return _T("IDirect3DDevice9::SetVertexShaderConstantF");
	case _GetVertexShaderConstantF_:	return _T("IDirect3DDevice9::GetVertexShaderConstantF");
	case _SetVertexShaderConstantI_:	return _T("IDirect3DDevice9::SetVertexShaderConstantI");
	case _GetVertexShaderConstantI_:	return _T("IDirect3DDevice9::GetVertexShaderConstantI");
	case _SetVertexShaderConstantB_:	return _T("IDirect3DDevice9::SetVertexShaderConstantB");
	case _GetVertexShaderConstantB_:	return _T("IDirect3DDevice9::GetVertexShaderConstantB");
	case _SetStreamSource_:				return _T("IDirect3DDevice9::SetStreamSource");
	case _GetStreamSource_:				return _T("IDirect3DDevice9::GetStreamSource");
	case _SetStreamSourceFreq_:			return _T("IDirect3DDevice9::SetStreamSourceFreq");
	case _GetStreamSourceFreq_:			return _T("IDirect3DDevice9::GetStreamSourceFreq");
	case _SetIndices_:					return _T("IDirect3DDevice9::SetIndices");
	case _GetIndices_:					return _T("IDirect3DDevice9::GetIndices");
	case _CreatePixelShader_:			return _T("IDirect3DDevice9::CreatePixelShader");
	case _SetPixelShader_:				return _T("IDirect3DDevice9::SetPixelShader");
	case _GetPixelShader_:				return _T("IDirect3DDevice9::GetPixelShader");
	case _SetPixelShaderConstantF_:		return _T("IDirect3DDevice9::SetPixelShaderConstantF");
	case _GetPixelShaderConstantF_:		return _T("IDirect3DDevice9::GetPixelShaderConstantF");
	case _SetPixelShaderConstantI_:		return _T("IDirect3DDevice9::SetPixelShaderConstantI");
	case _GetPixelShaderConstantI_:		return _T("IDirect3DDevice9::GetPixelShaderConstantI");
	case _SetPixelShaderConstantB_:		return _T("IDirect3DDevice9::SetPixelShaderConstantB");
	case _GetPixelShaderConstantB_:		return _T("IDirect3DDevice9::GetPixelShaderConstantB");
	case _DrawRectPatch_:				return _T("IDirect3DDevice9::DrawRectPatch");
	case _DrawTriPatch_:				return _T("IDirect3DDevice9::DrawTriPatch");
	case _DeletePatch_:					return _T("IDirect3DDevice9::DeletePatch");
	case _CreateQuery_:					return _T("IDirect3DDevice9::CreateQuery");
	default:							return _T("IDirect3DDevice9::OTHER");
	}
}

const TCHAR * GetQueryTypeString( D3DQUERYTYPE Type )
{
	switch (Type)
	{
	case D3DQUERYTYPE_VCACHE:				return _T("D3DQUERYTYPE_VCACHE");
	case D3DQUERYTYPE_RESOURCEMANAGER:		return _T("D3DQUERYTYPE_RESOURCEMANAGER");
	case D3DQUERYTYPE_VERTEXSTATS:			return _T("D3DQUERYTYPE_VERTEXSTATS");
	case D3DQUERYTYPE_EVENT:				return _T("D3DQUERYTYPE_EVENT");
	case D3DQUERYTYPE_OCCLUSION:			return _T("D3DQUERYTYPE_OCCLUSION");
	case D3DQUERYTYPE_TIMESTAMP:			return _T("D3DQUERYTYPE_TIMESTAMP");
	case D3DQUERYTYPE_TIMESTAMPDISJOINT:	return _T("D3DQUERYTYPE_TIMESTAMPDISJOINT");
	case D3DQUERYTYPE_TIMESTAMPFREQ:		return _T("D3DQUERYTYPE_TIMESTAMPFREQ");
	case D3DQUERYTYPE_PIPELINETIMINGS:		return _T("D3DQUERYTYPE_PIPELINETIMINGS");
	case D3DQUERYTYPE_INTERFACETIMINGS:		return _T("D3DQUERYTYPE_INTERFACETIMINGS");
	case D3DQUERYTYPE_VERTEXTIMINGS:		return _T("D3DQUERYTYPE_VERTEXTIMINGS");
	case D3DQUERYTYPE_PIXELTIMINGS:			return _T("D3DQUERYTYPE_PIXELTIMINGS");
	case D3DQUERYTYPE_BANDWIDTHTIMINGS:		return _T("D3DQUERYTYPE_BANDWIDTHTIMINGS");
	case D3DQUERYTYPE_CACHEUTILIZATION:		return _T("D3DQUERYTYPE_CACHEUTILIZATION");
	case D3DQUERYTYPE_MEMORYPRESSURE:		return _T("D3DQUERYTYPE_MEMORYPRESSURE");
	};
	return _T("UNKNOWN");
}
