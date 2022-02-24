#include "stdafx.h"
#include "CmdFlowStreamers.h"
#include "XMLStreamer.h"

//////////////////////////////////////////////////////////////////////////

namespace Streamers {

	// A simple singleton to replace the one removed from boost pool
	template <typename T>
	struct singleton_default
	{
	private:
		singleton_default() {}

		struct force_static
		{
			// According to boost documentation, this ensures instance() is called before main()
			//   which keeps threading race issues from happening
			force_static() { singleton_default<T>:instance(); }
			static void fake_call() {}
		};

	public:
		typedef T object_type;

		static object_type& instance()
		{
			static T inst{};

			// According to boost documentation this forces instantiation, and makes it exist before
			//   main()
			force_static::fake_call();

			return inst;
		}
	private:
		T m_instance = 0;

	};
}

//////////////////////////////////////////////////////////////////////////

namespace WriteStreamer
{
	CmdFlowWriteStreamer& Get()
	{
		return Streamers::singleton_default<CmdFlowWriteStreamer>::instance();
	}

	bool IsOK()
	{
		return Get().IsWriterOK();
	}

	void	CmdBegin( D3D10DDI_HDEVICE hDevice_, Commands::Command* pCmd_, const char* szName_  )
	{
		Get().WriteCommandBegin( pCmd_, szName_ );
		Get().WriteReference( "hDevice", hDevice_ );
	}

	void	CmdEnd()
	{
		Get().WriteCommandEnd();
	}

	void	DeviceStateBegin()
	{
		Get().DeviceStateBlockBegin();
	}

	void	DeviceStateEnd()
	{
		Get().DeviceStateBlockEnd();
	}

	void	Comment	( char* szComment_, ... )
	{
#ifndef FINAL_RELEASE
		if (!IsOK())
			return;

		static char szBuff[ MAX_PATH ];	

		if( szComment_ != "" )
		{
			va_list args;
			va_start( args, szComment_ );
			vsprintf( szBuff, szComment_, args );
			va_end( args );
		}
		else
			szBuff[0] = '\0';			

		Get().WriteComment( szBuff );
#endif
	}
};

//////////////////////////////////////////////////////////////////////////

namespace ReadStreamer
{
	CmdFlowReadStreamer& Get()
	{
		return Streamers::singleton_default<CmdFlowReadStreamer>::instance();
	}

	void	CmdBegin( D3D10DDI_HDEVICE& hDevice_  )
	{
		Get().ReadReference( hDevice_ );
	}

	void	CmdEnd()
	{
	}

	void	Skip()
	{
		Get().Skip( );
	}
};

//////////////////////////////////////////////////////////////////////////