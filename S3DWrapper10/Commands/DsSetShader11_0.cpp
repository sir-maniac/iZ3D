#include "stdafx.h"
#include "DsSetShader11_0.h"
#include "..\Streamer\CodeGenerator.h"
#include "D3DDeviceWrapper.h"
#include "ShaderWrapper.h"

namespace Commands
{

	void DsSetShader11_0::UpdateDeviceState( D3DDeviceWrapper *pWrapper, D3DDeviceState* pState )
	{
		pState->DS.m_Shader = this;

		pState->DS.m_IsStereoShader = false;
		if (hShader_.pDrvPrivate)
		{
			ShaderWrapper* pDSWrp = NULL;
			InitWrapper(hShader_, pDSWrp);
			if ( pDSWrp->IsMatrixFounded() )
				pState->DS.m_IsStereoShader = true;
		}
	}

	void DsSetShader11_0::Execute( D3DDeviceWrapper *pWrapper )
	{
		BEFORE_EXECUTE(this);
		pWrapper->OriginalDeviceFuncs11.pfnDsSetShader( pWrapper->hDevice, GET_SHADER_HANDLE(hShader_));
		AFTER_EXECUTE(this); 
	}

	bool DsSetShader11_0::WriteToFile( D3DDeviceWrapper *pWrapper ) const
	{
		return WriteToFileEx(pWrapper, "DsSetShader11_0");
	}
}

VOID ( APIENTRY DsSetShader11_0 )( D3D10DDI_HDEVICE  hDevice, D3D10DDI_HSHADER  hShader )
{	
	_ASSERT(D3D10_GET_WRAPPER()->GetD3DVersion() >= TD3DVersion_11_0);
#ifndef EXECUTE_IMMEDIATELY_G1
	Commands::DsSetShader11_0* command = new Commands::DsSetShader11_0( hShader );
	D3D10_GET_WRAPPER()->AddCommand(command);
#else
	{
		THREAD_GUARD_D3D10();
		D3D11_GET_ORIG().pfnDsSetShader( D3D10_DEVICE, GET_SHADER_HANDLE( hShader ) );
	}
#endif
}