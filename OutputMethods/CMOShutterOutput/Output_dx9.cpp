/* IZ3D_FILE: $Id: Output_dx9.cpp$ 
*
* Project : iZ3D Stereo Driver
* Copyright (C) iZ3D Inc. 2002 - 2010
*
*/
// CMOShutterOutput.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Output_dx9.h"
#include "S3DWrapper9\BaseSwapChain.h"

using namespace DX9Output;

#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
					   DWORD  ul_reason_for_call,
					   LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

#ifdef _MANAGED
#pragma managed(pop)
#endif

OUTPUT_API void* CALLBACK CreateOutputDX9(DWORD mode, DWORD spanMode)
{
	return new CMOShutterOutput(mode, spanMode);
}

OUTPUT_API DWORD CALLBACK GetOutputCaps()
{
	return odShutterMode; // Use Presenter
}

OUTPUT_API void CALLBACK GetOutputName(char* name, DWORD size)
{
	strcpy_s(name, size, "CMI Shutter mode");
}

OUTPUT_API BOOL CALLBACK EnumOutputModes(DWORD num, char* name, DWORD size)
{
	switch(num)
	{
	case 0:
		strcpy_s(name, size, "Force 120Hz");
		return TRUE;
	case 1:
		strcpy_s(name, size, "Force 100Hz");
		return TRUE;
	case 2:
		strcpy_s(name, size, "Force 60Hz");
		return TRUE;
	case 3:
		strcpy_s(name, size, "Force 55Hz");
		return TRUE;
	case 4:
		strcpy_s(name, size, "Force 50Hz");
		return TRUE;
	default:
		return FALSE;
	}
}

CMOShutterOutput::CMOShutterOutput( DWORD mode, DWORD spanMode )
:	OutputMethod(mode, spanMode)
{
}

CMOShutterOutput::~CMOShutterOutput	()
{
}

int CMOShutterOutput::GetPreferredRefreshRate() const
{
	switch(m_OutputMode)
	{
	case 0:
		return 120;
	case 1:
		return 100;
	case 2:
		return 60;
	case 3:
		return 55;
	case 4:
		return 50;
	}
	return 0;
}

HRESULT CMOShutterOutput::MarkSurface( int view, IDirect3DSurface9* pView, RECT* pDestRect )
{
	HRESULT hResult = S_OK;
	unsigned int		dIndx	= (view == 0 || view == 2 ? 0 : 1);
	const	D3DCOLOR	markColor[2] = {
		D3DCOLOR_XRGB( 0xFF, 0xFF, 0xFF ),
		D3DCOLOR_XRGB( 0x00, 0x00, 0x00 )
	};
	const	RECT		markRect[2] = {							// LONG    left, top, right, bottom;
		//{ 0,  0, 10, 10 },									// DEBUG ONLY!
		//{ 10, 0, 20, 10 }										// DEBUG ONLY!
		{ 0, 0, 1, 1 },
		{ 1, 0, 2, 1 }
	};

	unsigned int curIdx = dIndx;
	RECT rect;
	CONST RECT* pRect = &markRect[ 0 ];
	if (pDestRect)
	{
		rect		 = markRect[ 0 ];
		rect.left	+= pDestRect->left;
		rect.top	+= pDestRect->top;
		rect.right	+= pDestRect->left;
		rect.bottom	+= pDestRect->top;
		pRect = &rect;
	}
	NSCALL(m_pd3dDevice->ColorFill( pView, pRect, markColor[ curIdx  ]   ) );

	if (view != 2)
		curIdx = dIndx ^ 1;
	pRect = &markRect[ 1 ];
	if (pDestRect)
	{
		rect		 = markRect[ 1 ];
		rect.left	+= pDestRect->left;
		rect.top	+= pDestRect->top;
		rect.right	+= pDestRect->left;
		rect.bottom	+= pDestRect->top;
		pRect = &rect;
	}
	NSCALL(m_pd3dDevice->ColorFill( pView, pRect, markColor[ curIdx  ]   ) );

	return hResult;
}

HRESULT CMOShutterOutput::Output(bool bLeft, CBaseSwapChain* pSwapChain, RECT* pDestRect)
{
	HRESULT hResult = S_OK;
	IDirect3DSurface9* view = pSwapChain->GetViewRT(bLeft);
	RECT* pViewRect = pSwapChain->GetViewRect(bLeft);
	IDirect3DSurface9* primary = pSwapChain->GetPresenterBackBuffer();
	int idx = 2;
	if(pSwapChain->IsStereoActive())
		idx = bLeft ? 0 : 1;
	MarkSurface( idx, view, pViewRect );
	NSCALL(m_pd3dDevice->StretchRect( view, pViewRect, primary, pDestRect, D3DTEXF_NONE ));
	return	hResult;
}

bool CMOShutterOutput::FindAdapter( LPDIRECT3D9 pDirect3D9, UINT DeviceNum, D3DDEVTYPE &DeviceType, UINT Adapters[2] )
{
	OutputMethod::FindAdapter(pDirect3D9, DeviceNum, DeviceType, Adapters);

	// Find the DirectX method of adapter ordinal, that is the CMO's
	UINT AdapterCount = pDirect3D9->GetAdapterCount();
	DISPLAY_DEVICEA			MonitorDevice;
	MonitorDevice.cb = sizeof( DISPLAY_DEVICEA );
	for( UINT i = 0; i < AdapterCount; i++ ) {
		D3DADAPTER_IDENTIFIER9	Adapter_Identify;
		pDirect3D9->GetAdapterIdentifier( i, 0, &Adapter_Identify );
		for( int j=0; EnumDisplayDevicesA(Adapter_Identify.DeviceName, j, &MonitorDevice, 0x0 ); j++ ) {
			if( (MonitorDevice.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP) &&
				(strstr( MonitorDevice.DeviceID, "NXG0D24" ) ||
				strstr( MonitorDevice.DeviceID, "CMO1590" ) ||			// CMO 50Hz Model
				strstr( MonitorDevice.DeviceID, "VSC" )  ||
				strstr( MonitorDevice.DeviceID, "MSIAE12")) ) {			// Model name: AE2420_3D, Manufacturer: MSI
					// Found the CMO PnP id.
					Adapters[0] = i;
					return true;
			}
		}
	}

#ifndef FINAL_RELEASE
	return true;
#else
	return false;
#endif
}
