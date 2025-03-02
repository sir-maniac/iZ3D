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
#include "DumpManager.h"
#include "IL/il.h"
#include "CommandDumper.h"

// {88D955D4-E26F-4092-8023-44D4621A92DD}
static const GUID BaseStereoRenderer_GUID = 
{ 0x88D955D4, 0xE26F, 0x4092, { 0x80, 0x23, 0x44, 0xD4, 0x62, 0x1A, 0x92, 0xDD } };
// {84822405-E987-4723-987F-7C11E6D1DA7E}
static const GUID SurfaceRevision_GUID = 
{ 0x84822405, 0xe987, 0x4723, { 0x98, 0x7f, 0x7c, 0x11, 0xe6, 0xd1, 0xda, 0x7e } };
// {CCDB1CDD-1401-48cf-A763-6E362EB394D8}
static const GUID TextureType_GUID = 
{ 0xccdb1cdd, 0x1401, 0x48cf, { 0xa7, 0x63, 0x6e, 0x36, 0x2e, 0xb3, 0x94, 0xd8 } };
// {E414E9A3-E63A-48dc-9740-864F45287E6F}
static const GUID McClaud_GUID = 
{ 0xe414e9a3, 0xe63a, 0x48dc, { 0x97, 0x40, 0x86, 0x4f, 0x45, 0x28, 0x7e, 0x6f } };

UINT BitsPerPixel( D3DFORMAT fmt )
{
	UINT fmtU = (UINT)fmt;
	switch( fmtU )
	{
	case D3DFMT_A32B32G32R32F:
		return 128;

	case D3DFMT_A16B16G16R16:
	case D3DFMT_Q16W16V16U16:
	case D3DFMT_A16B16G16R16F:
	case D3DFMT_G32R32F:
		return 64;

	case D3DFMT_A8R8G8B8:
	case D3DFMT_X8R8G8B8:
	case D3DFMT_A2B10G10R10:
	case D3DFMT_A8B8G8R8:
	case D3DFMT_X8B8G8R8:
	case D3DFMT_G16R16:
	case D3DFMT_A2R10G10B10:
	case D3DFMT_Q8W8V8U8:
	case D3DFMT_V16U16:
	case D3DFMT_X8L8V8U8:
	case D3DFMT_A2W10V10U10:
	case D3DFMT_D32:
	case D3DFMT_D24S8:
	case D3DFMT_D24X8:
	case D3DFMT_D24X4S4:
	case D3DFMT_D32F_LOCKABLE:
	case D3DFMT_D24FS8:
	case D3DFMT_INDEX32:
	case D3DFMT_G16R16F:
	case D3DFMT_R32F:
		return 32;

	case D3DFMT_R8G8B8:
	case FOURCC_DF24:
		return 24;

	case D3DFMT_A4R4G4B4:
	case D3DFMT_X4R4G4B4:
	case D3DFMT_R5G6B5:
	case D3DFMT_L16:
	case D3DFMT_A8L8:
	case D3DFMT_X1R5G5B5:
	case D3DFMT_A1R5G5B5:
	case D3DFMT_A8R3G3B2:
	case D3DFMT_V8U8:
	case D3DFMT_CxV8U8:
	case D3DFMT_L6V5U5:
	case D3DFMT_G8R8_G8B8:
	case D3DFMT_R8G8_B8G8:
	case D3DFMT_D16_LOCKABLE:
	case D3DFMT_D15S1:
	case D3DFMT_D16:
	case D3DFMT_INDEX16:
	case D3DFMT_R16F:
	case D3DFMT_YUY2:
	case D3DFMT_A8P8:
	case FOURCC_DF16:
		return 16;

	case D3DFMT_R3G3B2:
	case D3DFMT_A8:
	case D3DFMT_P8:
	case D3DFMT_L8:
	case D3DFMT_A4L4:
		return 8;

	case D3DFMT_DXT1:
	case FOURCC_ATI1:
		return 4;
	case D3DFMT_DXT2:
	case D3DFMT_DXT3:
	case D3DFMT_DXT4:
	case D3DFMT_DXT5:
	case FOURCC_ATI2:
		return  8;

		// From DX docs, reference/d3d/enums/d3dformat.asp
		// (note how it says that D3DFMT_R8G8_B8G8 is "A 16-bit packed RGB format analogous to UYVY (U0Y0, V0Y1, U2Y2, and so on)")
	case D3DFMT_UYVY:
		return 16;

		// http://msdn.microsoft.com/library/default.asp?url=/library/en-us/directshow/htm/directxvideoaccelerationdxvavideosubtypes.asp
	case MAKEFOURCC( 'A', 'I', '4', '4' ):
	case MAKEFOURCC( 'I', 'A', '4', '4' ):
		return 8;

	case MAKEFOURCC( 'Y', 'V', '1', '2' ):
		return 12;

	case MAKEFOURCC( 'N', 'U', 'L', 'L' ):
		return 0;

	default:
		//assert(FALSE); // unhandled format
		return 32;
	}
}

bool IsCompressedFormat( D3DFORMAT Format )
{
	if (Format == D3DFMT_DXT1 ||
		Format == D3DFMT_DXT2 ||
		Format == D3DFMT_DXT3 ||
		Format == D3DFMT_DXT4 ||
		Format == D3DFMT_DXT5 ||
		Format == FOURCC_ATI1 ||
		Format == FOURCC_ATI2)
	{
		return true;
	}
	return false;
}

UINT GetVertexCount(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount)
{
	switch (PrimitiveType)
	{
	case D3DPT_LINELIST:
		return PrimitiveCount * 2;
	case D3DPT_LINESTRIP:
		return PrimitiveCount + 1;
	case D3DPT_TRIANGLELIST:
		return PrimitiveCount * 3;
	case D3DPT_TRIANGLESTRIP:
	case D3DPT_TRIANGLEFAN:
		return PrimitiveCount + 2;
	}
	return PrimitiveCount;
}

HRESULT LoadTextureFromResource(LPDIRECT3DDEVICE9 pd3dDevice, HMODULE hModule, TCHAR* strResName, TCHAR* strResType, D3DXIMAGE_INFO* pSrcInfo, LPDIRECT3DTEXTURE9* ppTex)
{
	HRESULT hr;
	HRSRC	rsrc;
	HGLOBAL hgData;
	LPVOID	pvData;
	DWORD	cbData;

	rsrc = FindResource( hModule, strResName, strResType );
	if( rsrc != NULL )
	{
		cbData = SizeofResource( hModule, rsrc );
		if( cbData > 0 )
		{
			hgData = LoadResource( hModule, rsrc );
			if( hgData != NULL )
			{
				pvData = LockResource( hgData );
				if( pvData != NULL )
				{
					if( FAILED( hr = D3DXCreateTextureFromFileInMemoryEx(
						pd3dDevice, pvData, cbData, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 
						1, 0, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, 
						D3DX_FILTER_NONE, 0, pSrcInfo, NULL, ppTex ) ) )
					{
						return hr;
					}
				}
			}
		}
	}

	if( *ppTex == NULL)
		return E_FAIL;

	return S_OK;
}

CONST TCHAR* GetStereoImageFileExtension( )
{
	switch (gInfo.ScreenshotType)
	{
	case 1: // PNG
		return _T(".pns");
	case 2: // BMP
		return _T(".bmp");
	case 3: // DDS
		return _T(".dds");
	default: // JPG
		return _T(".jps");
	}
}

CONST TCHAR* GetImageFileExtension( )
{
	switch (gInfo.ScreenshotType)
	{
	case 1: // PNG
		return _T(".png");
	case 2: // BMP
		return _T(".bmp");
	case 3: // DDS
		return _T(".dds");
	default: // JPG
		return _T(".jpg");
	}
}

D3DXIMAGE_FILEFORMAT GetImageFileFormat( )
{
	switch (gInfo.ScreenshotType)
	{
	case 1: // PNG
		return D3DXIFF_PNG;
	case 2: // BMP
		return D3DXIFF_BMP;
	case 3: // DDS
		return D3DXIFF_DDS;
	default: // JPG
		return D3DXIFF_JPG;
	}
}

DWORD GetILImageFileFormat( )
{
	switch (gInfo.ScreenshotType)
	{
	case 1: // PNG
		return IL_PNG;
	case 2: // BMP
		return IL_BMP;
	case 3: // DDS
		return IL_DDS;
	default: // JPG
		return IL_JPG;
	}
}

void GetCubemapPosition( D3DCUBEMAP_FACES face, int &x, int &y, int &r )
{
	switch(face)
	{
	case D3DCUBEMAP_FACE_POSITIVE_X: // rotate right 90
		x = 2; y = 1; r = 1;
		break;
	case D3DCUBEMAP_FACE_NEGATIVE_X: // rotate left 90
		x = 0; y = 1; r = -1;
		break;
	case D3DCUBEMAP_FACE_POSITIVE_Y: // rotate left or right 90
		x = 3; y = 1; r = 1;
		break;
	case D3DCUBEMAP_FACE_NEGATIVE_Y:
		x = 1; y = 1; r = 0;
		break;
	case D3DCUBEMAP_FACE_POSITIVE_Z:
		x = 1; y = 0; r = 0;
		break;
	case D3DCUBEMAP_FACE_NEGATIVE_Z: // rotate 180
		x = 1; y = 2; r = 2;
		break;
	}
}

HRESULT SaveCubeTextureToFile(LPTSTR pDestFile, LPDIRECT3DCUBETEXTURE9 pSrcTexture, D3DXIMAGE_FILEFORMAT DestFormat)
{
	INSIDE;
	HRESULT hResult = S_OK;
	D3DSURFACE_DESC desc;
	NSCALL(pSrcTexture->GetLevelDesc(0, &desc));
	CComPtr<IDirect3DDevice9>  pDevice;
	pSrcTexture->GetDevice(&pDevice);
	CComPtr<IDirect3DSurface9> offScreenSurface;
	if (desc.Usage & D3DUSAGE_RENDERTARGET)
	{
		hResult = pDevice->CreateRenderTarget(4 * desc.Width, 3 * desc.Height, desc.Format, 
			D3DMULTISAMPLE_NONE, 0, FALSE, &offScreenSurface, NULL);
		if (SUCCEEDED(hResult))
		{  
			for (int i = 0; i < 6; i++)
			{
				CComPtr<IDirect3DSurface9> pSurf;
				pSrcTexture->GetCubeMapSurface((D3DCUBEMAP_FACES)i, 0, &pSurf);
				int x, y, r;
				GetCubemapPosition((D3DCUBEMAP_FACES)i, x, y, r);
				RECT DestRect;
				SetRect(&DestRect, x * desc.Width, y * desc.Height, (x + 1) * desc.Width, (y + 1) * desc.Height);
				hResult = pDevice->StretchRect(pSurf, NULL, offScreenSurface, &DestRect, D3DTEXF_NONE);
				if (FAILED(hResult))
					break;
			}
		}
	}
	else
	{
		hResult = pDevice->CreateOffscreenPlainSurface(4 * desc.Width, 3 * desc.Height, desc.Format, D3DPOOL_SYSTEMMEM, &offScreenSurface, NULL);
		if (SUCCEEDED(hResult))
		{  
			D3DLOCKED_RECT LockedRect;
			hResult = offScreenSurface->LockRect(&LockedRect, NULL, D3DLOCK_DISCARD);
			if (SUCCEEDED(hResult))
			{  
				for (int i = 0; i < 6; i++)
				{
					CComPtr<IDirect3DSurface9> pSurf;
					pSrcTexture->GetCubeMapSurface((D3DCUBEMAP_FACES)i, 0, &pSurf);
					int x, y, r;
					GetCubemapPosition((D3DCUBEMAP_FACES)i, x, y, r);
					D3DLOCKED_RECT LockedFace;
					hResult = pSurf->LockRect(&LockedFace, NULL, D3DLOCK_READONLY);
					if (SUCCEEDED(hResult))
					{  
						SIZE_T ll = desc.Width * BitsPerPixel(desc.Format) / 8;
						PBYTE pDst = (PBYTE)LockedRect.pBits + y * desc.Height * LockedRect.Pitch + x * ll;
						PBYTE pSrc = (PBYTE)LockedFace.pBits;

						for (UINT j = 0; j < desc.Height; j++)
						{
							memcpy(pDst, pSrc, ll);
							pSrc += LockedFace.Pitch;	
							pDst += LockedRect.Pitch;					 
						}

						hResult = pSurf->UnlockRect();
					}
					else
						break;
				}
				hResult = offScreenSurface->UnlockRect();
			}
		}
	}
	if (SUCCEEDED(hResult)) {
		if (DestFormat == D3DXIFF_FORCE_DWORD)
		{
			DestFormat = GetImageFileFormat( );
			_tcscat_s(pDestFile, MAX_PATH, GetImageFileExtension());
		}
		hResult = D3DXSaveSurfaceToFile(pDestFile, DestFormat, offScreenSurface, NULL, NULL);
	}
	else 
	{
		DEBUG_TRACE3(_T("\tFailed dump volume: Type = %s, Format = %s, Pool = %s\n"), 
			GetResourceTypeString(desc.Type), GetFormatString(desc.Format), 
			GetPoolString(desc.Pool));
	}
	return hResult;
}

HRESULT SaveTextureToFile(LPTSTR pDestFile, LPDIRECT3DBASETEXTURE9 pSrcTexture, D3DXIMAGE_FILEFORMAT DestFormat)
{
	D3DRESOURCETYPE type = pSrcTexture->GetType();
	switch(type)
	{
	case D3DRTYPE_TEXTURE:
		{
			CComPtr<IDirect3DSurface9> s;
			((IDirect3DTexture9*)pSrcTexture)->GetSurfaceLevel(0, &s);
			return SaveSurfaceToFile(pDestFile, s, DestFormat);
		}
	case D3DRTYPE_VOLUMETEXTURE:
		{
			CComPtr<IDirect3DVolume9> v;
			((IDirect3DVolumeTexture9*)pSrcTexture)->GetVolumeLevel(0, &v);
			return SaveVolumeToFile(pDestFile, v, DestFormat);
		}
	case D3DRTYPE_CUBETEXTURE:
		//return SaveCubeTextureToFile(pDestFile, (IDirect3DCubeTexture9*)pSrcTexture, DestFormat);
		break;
	}
	DEBUG_MESSAGE(_T("%s: Unsupported texture type - %s.\n"), _T( __FUNCTION__ ), GetResourceTypeString(type) );
	return E_FAIL;
}

HRESULT	SaveSurfaceToFile(LPTSTR pDestFile, LPDIRECT3DSURFACE9 pSrcSurface, D3DXIMAGE_FILEFORMAT DestFormat, const RECT *pSrcRect)
{
#ifndef FINAL_RELEASE
	if (DestFormat == D3DXIFF_FORCE_DWORD) {
		_tcscat_s(pDestFile, MAX_PATH, GetImageFileExtension());
	}
	DumpManager::Get().AddSurface(pDestFile, pSrcSurface);
#endif
	return S_OK;
}

HRESULT	SaveVolumeToFile(LPTSTR pDestFile, LPDIRECT3DVOLUME9 pSrcVolume, D3DXIMAGE_FILEFORMAT DestFormat)
{
	HRESULT hResult = S_OK;
	D3DVOLUME_DESC desc;
	NSCALL(pSrcVolume->GetDesc(&desc));
	if (desc.Type != D3DRTYPE_VOLUME)
		return E_FAIL;
	CComPtr<IDirect3DDevice9>  pDevice;
	pSrcVolume->GetDevice(&pDevice);
	UINT n = (UINT)floor(sqrt(1.0f * desc.Width * desc.Height * desc.Depth));
	UINT nHeight = n / desc.Height; // vertical count
	UINT nWidth = (UINT)ceil(1.0f * desc.Depth / nHeight); // horizontal count
	CComPtr<IDirect3DSurface9> offScreenSurface;
	hResult = pDevice->CreateOffscreenPlainSurface(nWidth * desc.Width, nHeight * desc.Height, desc.Format, D3DPOOL_SYSTEMMEM, &offScreenSurface, NULL);
	if (SUCCEEDED(hResult))
	{  
		D3DLOCKED_BOX LockedVolume;
		hResult = pSrcVolume->LockBox(&LockedVolume, NULL, D3DLOCK_READONLY);
		if (SUCCEEDED(hResult))
		{  
			D3DLOCKED_RECT LockedRect;
			hResult = offScreenSurface->LockRect(&LockedRect, NULL, D3DLOCK_DISCARD);
			if (SUCCEEDED(hResult))
			{  
				PBYTE pDstBase = (PBYTE)LockedRect.pBits;
				PBYTE pSrc = (PBYTE)LockedVolume.pBits;
				PBYTE pSrcSlice = (PBYTE)LockedVolume.pBits;
				SIZE_T ll = desc.Width * BitsPerPixel(desc.Format) / 8;
				UINT destX = 0;
				UINT destY = 0;
				for (UINT i = 0; i < desc.Depth; i++)
				{
					for (UINT j = 0; j < desc.Height; j++)
					{
						PBYTE pDst = pDstBase + j * LockedRect.Pitch;
						memcpy(pDst, pSrc, ll);
						pSrc += LockedVolume.RowPitch;						 
					}

					destX++;
					if (destX != nWidth)
						pDstBase += ll;
					else
					{
						destX = 0;
						destY++;
						pDstBase = (PBYTE)LockedRect.pBits + destY * desc.Height * LockedRect.Pitch;
					}
					pSrcSlice += LockedVolume.SlicePitch;
					pSrc = pSrcSlice;
				}
				hResult = offScreenSurface->UnlockRect();
			}
			hResult = pSrcVolume->UnlockBox();
		}

	}
	if (SUCCEEDED(hResult)) {
		if (DestFormat == D3DXIFF_FORCE_DWORD)
		{
			DestFormat = GetImageFileFormat();
			_tcscat_s(pDestFile, MAX_PATH, GetImageFileExtension());
		}
		hResult = D3DXSaveSurfaceToFile(pDestFile, DestFormat, offScreenSurface, NULL, NULL);
	}
	else 
	{
		DEBUG_TRACE3(_T("\tFailed dump volume: Type = %s, Format = %s, Pool = %s\n"), 
			GetResourceTypeString(desc.Type), GetFormatString(desc.Format), 
			GetPoolString(desc.Pool));
	}
	return hResult;
}

MIDL_INTERFACE("B4F9D240-FEC6-4f5a-9046-32739F20973D")
ISurfaceName: public IUnknown
{
#ifdef _UNICODE
	std::wstring m_Name;
#else
	std::string m_Name;
#endif
public:
	inline void SetName(LPCTSTR Name) { m_Name = Name; }
	inline LPCTSTR	GetName() { return m_Name.c_str(); }
};

class CSurfaceName: 
	public ISurfaceName,
	public CComObjectRoot,
	public CComCoClass<CSurfaceName>
{
public:
	BEGIN_COM_MAP(CSurfaceName)
		COM_INTERFACE_ENTRY(ISurfaceName)
	END_COM_MAP()
};

void SetObjectName(IDirect3DSurface9 *pSurface, LPCTSTR Name)
{
	CComPtr<ISurfaceName> pSurfaceName;
	CSurfaceName::CreateInstance(&pSurfaceName);
	pSurfaceName->SetName(Name? Name: _T("Unknown"));
	if (pSurface) 
	{
		pSurface->SetPrivateData(__uuidof(ISurfaceName), pSurfaceName, sizeof(IUnknown *), D3DSPD_IUNKNOWN);
	}
}

LPCTSTR GetObjectName(IDirect3DSurface9 *pSurface)
{
	CComPtr<ISurfaceName> pSurfaceName;
	DWORD size = sizeof(IUnknown *);
	if (pSurface) 
	{
		pSurface->GetPrivateData(__uuidof(ISurfaceName), (void *)&pSurfaceName, &size); 
	}
	if (pSurfaceName)
	{
		return pSurfaceName->GetName();
	}
	return _T("");
}

void SetObjectName(IDirect3DVolume9 *pSurface, LPCTSTR Name)
{
	CComPtr<ISurfaceName> pSurfaceName;
	CSurfaceName::CreateInstance(&pSurfaceName);
	pSurfaceName->SetName(Name? Name: _T("Unknown"));
	if (pSurface) 
	{
		pSurface->SetPrivateData(__uuidof(ISurfaceName), pSurfaceName, sizeof(IUnknown *), D3DSPD_IUNKNOWN);
	}
}

LPCTSTR GetObjectName(IDirect3DVolume9 *pSurface)
{
	CComPtr<ISurfaceName> pSurfaceName;
	DWORD size = sizeof(IUnknown *);
	if (pSurface) 
	{
		pSurface->GetPrivateData(__uuidof(ISurfaceName), (void *)&pSurfaceName, &size); 
	}
	if (pSurfaceName)
	{
		return pSurfaceName->GetName();
	}
	return _T("");
}

void SetObjectName(IDirect3DTexture9 *pTexture, LPCTSTR Name)
{
	CComPtr<ISurfaceName> pSurfaceName;
	CSurfaceName::CreateInstance(&pSurfaceName);
	pSurfaceName->SetName(Name);
	if (pTexture) 
	{
		pTexture->SetPrivateData(__uuidof(ISurfaceName), pSurfaceName, sizeof(IUnknown *), D3DSPD_IUNKNOWN);
		TCHAR buffer[128];
		for (DWORD i = 0; i < pTexture->GetLevelCount(); i++)
		{
			_sntprintf_s(buffer, _TRUNCATE, _T("%sL%d"), Name, i);
			CComPtr<IDirect3DSurface9> pSurface;
			pTexture->GetSurfaceLevel(i, &pSurface);
			SetObjectName(pSurface, buffer);
		}
	}
}

LPCTSTR GetObjectName(IDirect3DTexture9 *pTexture)
{
	CComPtr<ISurfaceName> pSurfaceName;
	DWORD size = sizeof(IUnknown *);
	if (pTexture) 
	{
		pTexture->GetPrivateData(__uuidof(ISurfaceName), (void *)&pSurfaceName, &size); 
	}
	if (pSurfaceName)
	{
		return pSurfaceName->GetName();
	}
	return _T("");
}

void SetObjectName(IDirect3DVolumeTexture9 *pTexture, LPCTSTR Name)
{
	CComPtr<ISurfaceName> pSurfaceName;
	CSurfaceName::CreateInstance(&pSurfaceName);
	pSurfaceName->SetName(Name);
	if (pTexture) 
	{
		pTexture->SetPrivateData(__uuidof(ISurfaceName), pSurfaceName, sizeof(IUnknown *), D3DSPD_IUNKNOWN);
		TCHAR buffer[128];
		for (DWORD i = 0; i < pTexture->GetLevelCount(); i++)
		{
			_sntprintf_s(buffer, _TRUNCATE, _T("%sL%d"), Name, i);
			CComPtr<IDirect3DVolume9> pSurface;
			pTexture->GetVolumeLevel(i, &pSurface);
			SetObjectName(pSurface, buffer);
		}
	}
}

LPCTSTR GetObjectName(IDirect3DVolumeTexture9 *pTexture)
{
	CComPtr<ISurfaceName> pSurfaceName;
	DWORD size = sizeof(IUnknown *);
	if (pTexture) 
	{
		pTexture->GetPrivateData(__uuidof(ISurfaceName), (void *)&pSurfaceName, &size); 
	}
	if (pSurfaceName)
	{
		return pSurfaceName->GetName();
	}
	return _T("");
}

void SetObjectName(IDirect3DCubeTexture9 *pTexture, LPCTSTR Name)
{
	CComPtr<ISurfaceName> pSurfaceName;
	CSurfaceName::CreateInstance(&pSurfaceName);
	pSurfaceName->SetName(Name);
	if (pTexture) 
	{
		pTexture->SetPrivateData(__uuidof(ISurfaceName), pSurfaceName, sizeof(IUnknown *), D3DSPD_IUNKNOWN);
		TCHAR buffer[128];
		for (DWORD j = 0; j < 6; j++)
			for (DWORD i = 0; i < pTexture->GetLevelCount(); i++)
			{
				_sntprintf_s(buffer, _TRUNCATE, _T("%sF%sL%d"), Name, 
					GetCubeMapFaceTypeString((D3DCUBEMAP_FACES)j), i);
				CComPtr<IDirect3DSurface9> pSurface;
				pTexture->GetCubeMapSurface((D3DCUBEMAP_FACES)j, i, &pSurface);
				SetObjectName(pSurface, buffer);
			}
	}
}

void SetObjectName(IDirect3DBaseTexture9 *pTexture, LPCTSTR Name)
{
	CComPtr<ISurfaceName> pSurfaceName;
	CSurfaceName::CreateInstance(&pSurfaceName);
	pSurfaceName->SetName(Name);
	CComPtr<IDirect3DSurface9> pSurface;
	if (pTexture) 
	{
		pTexture->SetPrivateData(__uuidof(ISurfaceName), pSurfaceName, sizeof(IUnknown *), D3DSPD_IUNKNOWN);
	}
}

LPCTSTR GetObjectName(IDirect3DBaseTexture9 *pTexture)
{
	CComPtr<ISurfaceName> pSurfaceName;
	DWORD size = sizeof(IUnknown *);
	if (pTexture) 
	{
		pTexture->GetPrivateData(__uuidof(ISurfaceName), (void *)&pSurfaceName, &size); 
	}
	if (pSurfaceName)
	{
		return pSurfaceName->GetName();
	}
	return _T("");
}

bool IsMcClaud(IDirect3DSurface9 *pSurface)
{
	DWORD data;
	DWORD size = sizeof(data);
	if (pSurface) 
	{
		if(SUCCEEDED(pSurface->GetPrivateData(McClaud_GUID, (void *)&data, &size)))
			return true;
	}
	return false;
}

HRESULT	SetMcClaudFlag(IDirect3DSurface9 *pSurface)
{
	DWORD data;
	DWORD size = sizeof(data);
	if (pSurface) 
	{
		return pSurface->SetPrivateData(McClaud_GUID, (void *)&data, size, 0);
	}
	return E_FAIL;
}

HRESULT	ClearMcClaudFlag(IDirect3DSurface9 *pSurface)
{
	if (pSurface) 
	{
		return pSurface->FreePrivateData(McClaud_GUID);
	}
	return E_FAIL;
}

IDirect3DBaseTexture9 *GetParentTexture(IDirect3DSurface9* pSurf, IDirect3DBaseTexture9** ppTex)
{
	*ppTex = NULL;
	_ASSERT(pSurf != NULL);
	HRESULT hr = pSurf->GetContainer(IID_IDirect3DBaseTexture9, (void**)ppTex);
	return *ppTex;
}

IDirect3DTexture9 *GetParentTexture(IDirect3DSurface9* pSurf, IDirect3DTexture9** ppTex)
{
	*ppTex = NULL;
	_ASSERT(pSurf != NULL);
	HRESULT hr = pSurf->GetContainer(IID_IDirect3DTexture9, (void**)ppTex);
	return *ppTex;
}

HRESULT GetStereoObject(IDirect3DBaseTexture9 *pLeft, IDirect3DBaseTexture9 **ppRight)
{
	_ASSERT(pLeft);
	DWORD size = sizeof(IUnknown *);
	*ppRight = 0;
	return pLeft->GetPrivateData(BaseStereoRenderer_GUID, (void *)ppRight, &size); 
}

HRESULT GetStereoObject(IDirect3DTexture9 *pLeft, IDirect3DTexture9 **ppRight)
{
	_ASSERT(pLeft);
	DWORD size = sizeof(IUnknown *);
	*ppRight = 0;
	return pLeft->GetPrivateData(BaseStereoRenderer_GUID, (void *)ppRight, &size); 
}

HRESULT GetStereoObject(IDirect3DSurface9 *pLeft, IDirect3DSurface9 **ppRight)
{
	_ASSERT(pLeft);
	DWORD size = sizeof(IUnknown *);
	*ppRight = 0;
	return pLeft->GetPrivateData(BaseStereoRenderer_GUID, (void *)ppRight, &size); 
}

HRESULT SetStereoObject(IDirect3DBaseTexture9 *pLeft, IDirect3DBaseTexture9 *pRight)
{
	_ASSERT(pLeft);
	if (pRight)
		return pLeft->SetPrivateData(BaseStereoRenderer_GUID, pRight, sizeof(IUnknown *), D3DSPD_IUNKNOWN);
	else
		return pLeft->SetPrivateData(BaseStereoRenderer_GUID, &pRight, sizeof(IUnknown *), 0);
}

HRESULT SetStereoObject(IDirect3DSurface9 *pLeft, IDirect3DSurface9 *pRight)
{
	_ASSERT(pLeft);
	if (pRight)
		return pLeft->SetPrivateData(BaseStereoRenderer_GUID, pRight, sizeof(IUnknown *), D3DSPD_IUNKNOWN);
	else
		return pLeft->SetPrivateData(BaseStereoRenderer_GUID, &pRight, sizeof(IUnknown *), 0);
}

HRESULT SetStereoObject(IDirect3DTexture9 *pLeft, IDirect3DTexture9 *pRight)
{
	_ASSERT(pLeft);
	HRESULT hResult = S_OK;
	if (pRight)
	{
		NSCALL(pLeft->SetPrivateData(BaseStereoRenderer_GUID, pRight, sizeof(IUnknown *), D3DSPD_IUNKNOWN));
		for (DWORD i = 0; i < pLeft->GetLevelCount(); i++)
		{
			CComPtr<IDirect3DSurface9> pLeftSurface;
			NSCALL(pLeft->GetSurfaceLevel( i, &pLeftSurface ));
			CComPtr<IDirect3DSurface9> pRightSurface;
			NSCALL(pRight->GetSurfaceLevel( i, &pRightSurface ));
			NSCALL(SetStereoObject(pLeftSurface, pRightSurface));
		}
		return hResult;
	}
	else
		return pLeft->SetPrivateData(BaseStereoRenderer_GUID, &pRight, sizeof(IUnknown *), 0);
}

void FreeStereoObject(IDirect3DBaseTexture9 *pLeft)
{
	_ASSERT(pLeft);
	pLeft->FreePrivateData(BaseStereoRenderer_GUID);
}

void FreeStereoObject(IDirect3DSurface9 *pLeft)
{
	_ASSERT(pLeft);
	pLeft->FreePrivateData(BaseStereoRenderer_GUID);
}

void FreeStereoObject(IDirect3DTexture9 *pLeft)
{
	_ASSERT(pLeft);
	pLeft->FreePrivateData(BaseStereoRenderer_GUID);

	for (DWORD i = 0; i < pLeft->GetLevelCount(); i++)
	{
		CComPtr<IDirect3DSurface9> pLeftSurface;
		pLeft->GetSurfaceLevel( i, &pLeftSurface );
		FreeStereoObject(pLeftSurface);
	}
}

void SetSurfaceRevision(IDirect3DSurface9* pSurf, DWORD rev)
{
	_ASSERT(pSurf);
	HRESULT hr = pSurf->SetPrivateData(SurfaceRevision_GUID, (void *)&rev, sizeof DWORD, 0);
	DEBUG_TRACE3(_T("\tSetSurfaceRevision(%d) %p [%s]\n"), rev, pSurf, GetObjectName(pSurf));
	_ASSERT(SUCCEEDED(hr));
}

DWORD GetSurfaceRevision(IDirect3DSurface9* pSurf)
{
	_ASSERT(pSurf);
	DWORD size = sizeof DWORD;
	DWORD rev;
	if (FAILED(pSurf->GetPrivateData(SurfaceRevision_GUID, (void *)&rev, &size)))
		rev = 0;
	DEBUG_TRACE3(_T("\tGetSurfaceRevision() %p [%s] = %d\n"), pSurf, GetObjectName(pSurf), rev);
	return rev;
}

void IncSurfaceRevision(IDirect3DSurface9* pSurf)
{
	_ASSERT(pSurf);
	DWORD rev = GetSurfaceRevision(pSurf);
	rev++;
	SetSurfaceRevision(pSurf, rev);
}

TextureType GetSurfaceType(IDirect3DSurface9 *pTexture)
{
	TextureType val = Mono;
	DWORD size = sizeof(TextureType);
	_ASSERT(pTexture != NULL);
	if(SUCCEEDED(pTexture->GetPrivateData(TextureType_GUID, (void *)&val, &size)))
		DEBUG_TRACE3(_T("\tpSurface %p [%s]: TextureType = %s\n"), pTexture, GetObjectName(pTexture), GetTextureTypeString(val));
	return val;
}

TextureType GetTextureType(IDirect3DBaseTexture9 *pTexture)
{
	TextureType val = Mono;
	DWORD size = sizeof(TextureType);
	_ASSERT(pTexture != NULL);
	if(SUCCEEDED(pTexture->GetPrivateData(TextureType_GUID, (void *)&val, &size)))
		DEBUG_TRACE3(_T("\tpTexture %p [%s]: TextureType = %s\n"), pTexture, GetObjectName(pTexture), GetTextureTypeString(val));
	return val;
}

bool SetSurfaceType(IDirect3DSurface9 *pTexture, TextureType textureType)
{
	_ASSERT(pTexture != NULL);
	return SUCCEEDED(pTexture->SetPrivateData(TextureType_GUID, (void *)&textureType, sizeof(TextureType), 0));
}

bool SetTextureType(IDirect3DBaseTexture9 *pTexture, TextureType textureType)
{
	_ASSERT(pTexture != NULL);
	return SUCCEEDED(pTexture->SetPrivateData(TextureType_GUID, (void *)&textureType, sizeof(TextureType), 0));
}

UINT GetCubeTextureSize(IDirect3DCubeTexture9 *pTex)
{
	_ASSERT(pTex);
	CComPtr<IDirect3DSurface9> pSurface;
	pTex->GetCubeMapSurface((D3DCUBEMAP_FACES) 0, 0, &pSurface);
	D3DSURFACE_DESC Desc;
	pSurface->GetDesc(&Desc);
	UINT size = GetSurfaceSize(Desc);
	for (DWORD i = 1; i < pTex->GetLevelCount(); i++)
	{
		Desc.Width = Desc.Width > 2 ? Desc.Width / 2 : 1;
		Desc.Height = Desc.Height > 2 ? Desc.Height / 2 : 1;
		size += GetSurfaceSize(Desc);
	}
	return size * 6;
}

UINT GetVolumeSize(IDirect3DVolume9 *pSurf)
{
	_ASSERT(pSurf);
	D3DVOLUME_DESC Desc;
	pSurf->GetDesc(&Desc);
	return GetVolumeSize(Desc);
}

UINT GetVolumeTextureSize(IDirect3DVolumeTexture9 *pTex)
{
	_ASSERT(pTex);
	CComPtr<IDirect3DVolume9> pVolume;
	pTex->GetVolumeLevel(0, &pVolume);
	D3DVOLUME_DESC Desc;
	pVolume->GetDesc(&Desc);
	UINT size = GetVolumeSize(Desc);
	for (DWORD i = 1; i < pTex->GetLevelCount(); i++)
	{
		Desc.Width = Desc.Width > 2 ? Desc.Width / 2 : 1;
		Desc.Height = Desc.Height > 2 ? Desc.Height / 2 : 1;
		Desc.Depth = Desc.Depth > 2 ? Desc.Depth / 2 : 1;
		size += GetVolumeSize(Desc);
	}
	return size;
}

UINT GetTextureSize(IDirect3DTexture9 *pTex)
{
	if (pTex == NULL)
		return 0;
	CComPtr<IDirect3DSurface9> pSurface;
	pTex->GetSurfaceLevel(0, &pSurface);
	D3DSURFACE_DESC Desc;
	pSurface->GetDesc(&Desc);
	UINT size = GetSurfaceSize(Desc);
	for (DWORD i = 1; i < pTex->GetLevelCount(); i++)
	{
		Desc.Width = Desc.Width > 2 ? Desc.Width / 2 : 1;
		Desc.Height = Desc.Height > 2 ? Desc.Height / 2 : 1;
		size += GetSurfaceSize(Desc);
	}
	return size;
}

UINT GetTextureSize( IDirect3DBaseTexture9* pTexture ) 
{
	CComQIPtr<IDirect3DTexture9> pTex(pTexture);
	if (pTex)
		return GetTextureSize(pTex);
	else
	{
		CComQIPtr<IDirect3DCubeTexture9> pCubeTex(pTexture);
		if (pCubeTex)
			return GetCubeTextureSize(pCubeTex);
		else
		{
			CComQIPtr<IDirect3DVolumeTexture9> pVolTex(pTexture);
			if (pVolTex)
				return GetVolumeTextureSize(pVolTex);
		}
	}
	return 0;
}

UINT GetTextureFirstSurfaceSize( IDirect3DBaseTexture9* pTexture ) 
{
	CComQIPtr<IDirect3DTexture9> pTex(pTexture);
	if (pTex)
	{
		D3DSURFACE_DESC Desc;
		pTex->GetLevelDesc(0, &Desc);
		return GetSurfaceSize(Desc);
	} 
	else
	{
		CComQIPtr<IDirect3DCubeTexture9> pCubeTex(pTexture);
		if (pCubeTex)
		{
			D3DSURFACE_DESC Desc;
			pCubeTex->GetLevelDesc(0, &Desc);
			return GetSurfaceSize(Desc);
		}
		else
		{
			CComQIPtr<IDirect3DVolumeTexture9> pVolTex(pTexture);
			if (pVolTex)
			{
				D3DVOLUME_DESC Desc;
				pVolTex->GetLevelDesc(0, &Desc);
				return GetVolumeSize(Desc);
			} 
		}
	}
	return 0;
}

UINT GetSurfaceSize(IDirect3DSurface9 *pSurf)
{
	if (pSurf == NULL)
		return 0;
	D3DSURFACE_DESC Desc;
	pSurf->GetDesc(&Desc);
	return GetSurfaceSize(Desc);
}
