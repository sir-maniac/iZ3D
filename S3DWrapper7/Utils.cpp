#include "stdafx.h"
#include "d3dx9mesh.h"

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
	case FOURCC_DF32:
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
	case FOURCC_AI44:
	case FOURCC_IA44:
		return 8;

	case FOURCC_YV12:
		return 12;

	case FOURCC_NULL:
		return 0;

	default:
		//assert(FALSE); // unhandled format
		return 32;
	}
}


D3DFORMAT DD2D3DFormat(const DDPIXELFORMAT *DDPixelFormat)
{
	if(DDPixelFormat->dwFlags & DDPF_PALETTEINDEXED8)
	{
		return D3DFMT_P8;
	}
	else if(DDPixelFormat->dwFlags & (DDPF_PALETTEINDEXED1 | DDPF_PALETTEINDEXED2 | DDPF_PALETTEINDEXED4) )
	{
		DEBUG_MESSAGE("DDPF_PALETTEINDEXED1 to DDPF_PALETTEINDEXED4 are not supported by D3D (yet). Returning D3DFMT_P8\n");
		return D3DFMT_P8;
	}
	else if(DDPixelFormat->dwFlags & DDPF_RGB)
	{
		switch(DDPixelFormat->dwRGBBitCount)
		{
		case 8:
			/* This is the only format that can match here */
			return D3DFMT_R3G3B2;

		case 16:
			/* Read the Color masks */
			if( (DDPixelFormat->dwRBitMask == 0xF800) &&
				(DDPixelFormat->dwGBitMask == 0x07E0) &&
				(DDPixelFormat->dwBBitMask == 0x001F) )
			{
				return D3DFMT_R5G6B5;
			}

			if( (DDPixelFormat->dwRBitMask == 0x7C00) &&
				(DDPixelFormat->dwGBitMask == 0x03E0) &&
				(DDPixelFormat->dwBBitMask == 0x001F) )
			{
				if( (DDPixelFormat->dwFlags & DDPF_ALPHAPIXELS) &&
					(DDPixelFormat->dwRGBAlphaBitMask == 0x8000))
					return D3DFMT_A1R5G5B5;
				else
					return D3DFMT_X1R5G5B5;
			}

			if( (DDPixelFormat->dwRBitMask == 0x0F00) &&
				(DDPixelFormat->dwGBitMask == 0x00F0) &&
				(DDPixelFormat->dwBBitMask == 0x000F) )
			{
				if( (DDPixelFormat->dwFlags & DDPF_ALPHAPIXELS) &&
					(DDPixelFormat->dwRGBAlphaBitMask == 0xF000))
					return D3DFMT_A4R4G4B4;
				else
					return D3DFMT_X4R4G4B4;
			}

			if( (DDPixelFormat->dwFlags & DDPF_ALPHAPIXELS) &&
				(DDPixelFormat->dwRGBAlphaBitMask == 0xFF00) &&
				(DDPixelFormat->dwRBitMask == 0x00E0) &&
				(DDPixelFormat->dwGBitMask == 0x001C) &&
				(DDPixelFormat->dwBBitMask == 0x0003) )
			{
				return D3DFMT_A8R3G3B2;
			}
			DEBUG_MESSAGE("16 bit RGB Pixel format does not match\n");
			return D3DFMT_UNKNOWN;

		case 24:
			return D3DFMT_R8G8B8;

		case 32:
			/* Read the Color masks */
			if( (DDPixelFormat->dwRBitMask == 0x00FF0000) &&
				(DDPixelFormat->dwGBitMask == 0x0000FF00) &&
				(DDPixelFormat->dwBBitMask == 0x000000FF) )
			{
				if( (DDPixelFormat->dwFlags & DDPF_ALPHAPIXELS) &&
					(DDPixelFormat->dwRGBAlphaBitMask == 0xFF000000))
					return D3DFMT_A8R8G8B8;
				else
					return D3DFMT_X8R8G8B8;

			}
			DEBUG_MESSAGE("32 bit RGB pixel format does not match\n");

		default:
			DEBUG_MESSAGE("Invalid dwRGBBitCount in Pixelformat structure\n");
			return D3DFMT_UNKNOWN;
		}
	}
	else if( (DDPixelFormat->dwFlags & DDPF_ALPHA) )
	{
		/* Alpha only Pixelformat */
		switch(DDPixelFormat->dwAlphaBitDepth)
		{
		case 1:
		case 2:
		case 4:
			DEBUG_MESSAGE("Unsupported Alpha-Only bit depth 0x%x\n", DDPixelFormat->dwAlphaBitDepth);
		case 8:
			return D3DFMT_A8;

		default:
			DEBUG_MESSAGE("Invalid AlphaBitDepth in Alpha-Only Pixelformat\n");
			return D3DFMT_UNKNOWN;
		}
	}
	else if(DDPixelFormat->dwFlags & DDPF_LUMINANCE)
	{
		/* Luminance-only or luminance-alpha */
		if(DDPixelFormat->dwFlags & DDPF_ALPHAPIXELS)
		{
			/* Luminance with Alpha */
			switch(DDPixelFormat->dwLuminanceBitCount)
			{
			case 4:
				if(DDPixelFormat->dwAlphaBitDepth == 4)
					return D3DFMT_A4L4;
				DEBUG_MESSAGE("Unknown Alpha / Luminance bit depth combination\n");
				return D3DFMT_UNKNOWN;

			case 6:
				DEBUG_MESSAGE("A luminance Pixelformat shouldn't have 6 luminance bits. Returning D3DFMT_L6V5U5 for now!!\n");
				return D3DFMT_L6V5U5;

			case 8:
				if(DDPixelFormat->dwAlphaBitDepth == 8)
					return D3DFMT_A8L8;
				DEBUG_MESSAGE("Unknown Alpha / Lumincase bit depth combination\n");
				return D3DFMT_UNKNOWN;
			}
		}
		else
		{
			/* Luminance-only */
			switch(DDPixelFormat->dwLuminanceBitCount)
			{
			case 6:
				DEBUG_MESSAGE("A luminance Pixelformat shouldn't have 6 luminance bits. Returning D3DFMT_L6V5U5 for now!!\n");
				return D3DFMT_L6V5U5;

			case 8:
				return D3DFMT_L8;

			default:
				DEBUG_MESSAGE("Unknown luminance-only bit depth 0x%x\n", DDPixelFormat->dwLuminanceBitCount);
				return D3DFMT_UNKNOWN;
			}
		}
	}
	else if(DDPixelFormat->dwFlags & DDPF_ZBUFFER)
	{
		/* Z buffer */
		if(DDPixelFormat->dwFlags & DDPF_STENCILBUFFER)
		{
			switch(DDPixelFormat->dwZBufferBitDepth)
			{
			case 8:
				DEBUG_MESSAGE("8 Bits Z+Stencil buffer pixelformat is not supported. Returning D3DFMT_UNKNOWN\n");
				return D3DFMT_UNKNOWN;

			case 15:
				DEBUG_MESSAGE("15 bit depth buffer not handled yet, assuming 16 bit\n");
			case 16:
				if(DDPixelFormat->dwStencilBitDepth == 1)
					return D3DFMT_D15S1;

				DEBUG_MESSAGE("Don't know how to handle a 16 bit Z buffer with %d bit stencil buffer pixelformat\n", DDPixelFormat->dwStencilBitDepth);
				return D3DFMT_UNKNOWN;

			case 24:
				DEBUG_MESSAGE("Don't know how to handle a 24 bit depth buffer with stencil bits\n");
				return D3DFMT_D24S8;

			case 32:
				if(DDPixelFormat->dwStencilBitDepth == 8)
					return D3DFMT_D24S8;
				else
					return D3DFMT_D24X4S4;

			default:
				DEBUG_MESSAGE("Unknown Z buffer depth %d\n", DDPixelFormat->dwZBufferBitDepth);
				return D3DFMT_UNKNOWN;
			}
		}
		else
		{
			switch(DDPixelFormat->dwZBufferBitDepth)
			{
			case 8:
				DEBUG_MESSAGE("8 Bit Z buffers are not supported. Trying a 16 Bit one\n");
				return D3DFMT_D16;

			case 16:
				return D3DFMT_D16;

			case 24:
				DEBUG_MESSAGE("24 Bit depth buffer, treating like a 32 bit one\n");
			case 32:
				if(DDPixelFormat->dwZBitMask == 0x00FFFFFF) {
					return D3DFMT_D24X8;
				} else if(DDPixelFormat->dwZBitMask == 0xFFFFFFFF) {
					return D3DFMT_D32;
				}
				DEBUG_MESSAGE("Unhandled 32 bit depth buffer bitmasks, returning D3DFMT_D24X8\n");
				return D3DFMT_D24X8; /* That's most likely to make games happy */

			default:
				DEBUG_MESSAGE("Unsupported Z buffer depth %d\n", DDPixelFormat->dwZBufferBitDepth);
				return D3DFMT_UNKNOWN;
			}
		}
	}
	else if(DDPixelFormat->dwFlags & DDPF_FOURCC)
	{
		switch(DDPixelFormat->dwFourCC)
		{
		case D3DFMT_UYVY:
		case D3DFMT_YUY2:
		case FOURCC_YV12:
		case D3DFMT_DXT1:
		case D3DFMT_DXT2:
		case D3DFMT_DXT3:
		case D3DFMT_DXT4:
		case D3DFMT_DXT5:
		case D3DFMT_G8R8_G8B8:
		case D3DFMT_R8G8_B8G8:
			return (D3DFORMAT)DDPixelFormat->dwFourCC;
		}
		DEBUG_MESSAGE("Unknown Pixelformat FourCC!\n");
		return D3DFMT_UNKNOWN;  /* Abuse this as an DEBUG_MESSAGEor value */
	}
	else if(DDPixelFormat->dwFlags & DDPF_BUMPDUDV)
	{
		if( (DDPixelFormat->dwBumpBitCount         == 16        ) &&
			(DDPixelFormat->dwBumpDuBitMask        == 0x000000ff) &&
			(DDPixelFormat->dwBumpDvBitMask        == 0x0000ff00) &&
			(DDPixelFormat->dwBumpLuminanceBitMask == 0x00000000) )
		{
			return D3DFMT_V8U8;
		}
		else if ( (DDPixelFormat->dwBumpBitCount         == 16        ) &&
			(DDPixelFormat->dwBumpDuBitMask        == 0x0000001f) &&
			(DDPixelFormat->dwBumpDvBitMask        == 0x000003e0) &&
			(DDPixelFormat->dwBumpLuminanceBitMask == 0x0000fc00) )
		{
			return D3DFMT_L6V5U5;
		}
	}

	DEBUG_MESSAGE("Unknown Pixelformat!\n");
	return D3DFMT_UNKNOWN;
}

void D3DFromat2DD(DDPIXELFORMAT *DDPixelFormat, D3DFORMAT format)
{
    DWORD Size = DDPixelFormat->dwSize;
    DEBUG_TRACE3("Converting D3DFORMAT %d to DDRAW\n", format);

    if(Size==0) return;

    memset(DDPixelFormat, 0x00, Size);
    DDPixelFormat->dwSize = Size;
    switch(format)
    {
        case D3DFMT_R8G8B8:
            DDPixelFormat->dwFlags = DDPF_RGB;
            DDPixelFormat->dwFourCC = 0;
            DDPixelFormat->dwRGBBitCount = 24;
            DDPixelFormat->dwRBitMask = 0x00ff0000;
            DDPixelFormat->dwGBitMask = 0x0000ff00;
            DDPixelFormat->dwBBitMask = 0x000000ff;
            DDPixelFormat->dwRGBAlphaBitMask = 0x0;
            break;

        case D3DFMT_A8R8G8B8:
            DDPixelFormat->dwFlags = DDPF_RGB | DDPF_ALPHAPIXELS;
            DDPixelFormat->dwFourCC = 0;
            DDPixelFormat->dwRGBBitCount = 32;
            DDPixelFormat->dwRBitMask = 0x00ff0000;
            DDPixelFormat->dwGBitMask = 0x0000ff00;
            DDPixelFormat->dwBBitMask = 0x000000ff;
            DDPixelFormat->dwRGBAlphaBitMask = 0xff000000;
            break;

        case D3DFMT_X8R8G8B8:
            DDPixelFormat->dwFlags = DDPF_RGB;
            DDPixelFormat->dwFourCC = 0;
            DDPixelFormat->dwRGBBitCount = 32;
            DDPixelFormat->dwRBitMask = 0x00ff0000;
            DDPixelFormat->dwGBitMask = 0x0000ff00;
            DDPixelFormat->dwBBitMask = 0x000000ff;
            DDPixelFormat->dwRGBAlphaBitMask = 0x0;
            break;

        case D3DFMT_X8B8G8R8:
            DDPixelFormat->dwFlags = DDPF_RGB;
            DDPixelFormat->dwFourCC = 0;
            DDPixelFormat->dwRGBBitCount = 32;
            DDPixelFormat->dwRBitMask = 0x000000ff;
            DDPixelFormat->dwGBitMask = 0x0000ff00;
            DDPixelFormat->dwBBitMask = 0x00ff0000;
            DDPixelFormat->dwRGBAlphaBitMask = 0x0;
            break;

        case D3DFMT_R5G6B5:
            DDPixelFormat->dwFlags = DDPF_RGB;
            DDPixelFormat->dwFourCC = 0;
            DDPixelFormat->dwRGBBitCount = 16;
            DDPixelFormat->dwRBitMask = 0xF800;
            DDPixelFormat->dwGBitMask = 0x07E0;
            DDPixelFormat->dwBBitMask = 0x001F;
            DDPixelFormat->dwRGBAlphaBitMask = 0x0;
            break;

        case D3DFMT_X1R5G5B5:
            DDPixelFormat->dwFlags = DDPF_RGB;
            DDPixelFormat->dwFourCC = 0;
            DDPixelFormat->dwRGBBitCount = 16;
            DDPixelFormat->dwRBitMask = 0x7C00;
            DDPixelFormat->dwGBitMask = 0x03E0;
            DDPixelFormat->dwBBitMask = 0x001F;
            DDPixelFormat->dwRGBAlphaBitMask = 0x0;
            break;

        case D3DFMT_A1R5G5B5:
            DDPixelFormat->dwFlags = DDPF_RGB | DDPF_ALPHAPIXELS;
            DDPixelFormat->dwFourCC = 0;
            DDPixelFormat->dwRGBBitCount = 16;
            DDPixelFormat->dwRBitMask = 0x7C00;
            DDPixelFormat->dwGBitMask = 0x03E0;
            DDPixelFormat->dwBBitMask = 0x001F;
            DDPixelFormat->dwRGBAlphaBitMask = 0x8000;
            break;

        case D3DFMT_A4R4G4B4:
            DDPixelFormat->dwFlags = DDPF_RGB | DDPF_ALPHAPIXELS;
            DDPixelFormat->dwFourCC = 0;
            DDPixelFormat->dwRGBBitCount = 16;
            DDPixelFormat->dwRBitMask = 0x0F00;
            DDPixelFormat->dwGBitMask = 0x00F0;
            DDPixelFormat->dwBBitMask = 0x000F;
            DDPixelFormat->dwRGBAlphaBitMask = 0xF000;
            break;

        case D3DFMT_R3G3B2:
            DDPixelFormat->dwFlags = DDPF_RGB;
            DDPixelFormat->dwFourCC = 0;
            DDPixelFormat->dwRGBBitCount = 8;
            DDPixelFormat->dwRBitMask = 0xE0;
            DDPixelFormat->dwGBitMask = 0x1C;
            DDPixelFormat->dwBBitMask = 0x03;
            DDPixelFormat->dwLuminanceAlphaBitMask = 0x0;
            break;

        case D3DFMT_P8:
            DDPixelFormat->dwFlags = DDPF_PALETTEINDEXED8 | DDPF_RGB;
            DDPixelFormat->dwFourCC = 0;
            DDPixelFormat->dwRGBBitCount = 8;
            DDPixelFormat->dwRBitMask = 0x00;
            DDPixelFormat->dwGBitMask = 0x00;
            DDPixelFormat->dwBBitMask = 0x00;
            break;

        case D3DFMT_A8:
            DDPixelFormat->dwFlags = DDPF_ALPHA;
            DDPixelFormat->dwFourCC = 0;
            DDPixelFormat->dwAlphaBitDepth = 8;
            DDPixelFormat->dwRBitMask = 0x0;
            DDPixelFormat->dwZBitMask = 0x0;
            DDPixelFormat->dwStencilBitMask = 0x0;
            DDPixelFormat->dwLuminanceAlphaBitMask = 0x0;
            break;

        case D3DFMT_A8R3G3B2:
            DDPixelFormat->dwFlags = DDPF_RGB | DDPF_ALPHAPIXELS;
            DDPixelFormat->dwFourCC = 0;
            DDPixelFormat->dwRGBBitCount = 16;
            DDPixelFormat->dwRBitMask = 0x00E0;
            DDPixelFormat->dwGBitMask = 0x001C;
            DDPixelFormat->dwBBitMask = 0x0003;
            DDPixelFormat->dwRGBAlphaBitMask = 0xF000;
            break;

        case D3DFMT_X4R4G4B4:
            DDPixelFormat->dwFlags = DDPF_RGB;
            DDPixelFormat->dwFourCC = 0;
            DDPixelFormat->dwRGBBitCount = 16;
            DDPixelFormat->dwRBitMask = 0x0F00;
            DDPixelFormat->dwGBitMask = 0x00F0;
            DDPixelFormat->dwBBitMask = 0x000F;
            DDPixelFormat->dwRGBAlphaBitMask = 0x0;
            return;

        /* How are Z buffer bit depth and Stencil buffer bit depth related?
         */
        case D3DFMT_D16:
            DDPixelFormat->dwFlags = DDPF_ZBUFFER;
            DDPixelFormat->dwFourCC = 0;
            DDPixelFormat->dwZBufferBitDepth = 16;
            DDPixelFormat->dwStencilBitDepth = 0;
            DDPixelFormat->dwZBitMask = 0x0000FFFF;
            DDPixelFormat->dwStencilBitMask = 0x0;
            DDPixelFormat->dwRGBZBitMask = 0x00000000;
            break;

        case D3DFMT_D32:
            DDPixelFormat->dwFlags = DDPF_ZBUFFER;
            DDPixelFormat->dwFourCC = 0;
            DDPixelFormat->dwZBufferBitDepth = 32;
            DDPixelFormat->dwStencilBitDepth = 0;
            DDPixelFormat->dwZBitMask = 0xFFFFFFFF;
            DDPixelFormat->dwStencilBitMask = 0x0;
            DDPixelFormat->dwRGBZBitMask = 0x00000000;
            break;

        case D3DFMT_D24X4S4:
            DDPixelFormat->dwFlags = DDPF_ZBUFFER | DDPF_STENCILBUFFER;
            DDPixelFormat->dwFourCC = 0;
            /* Should I set dwZBufferBitDepth to 32 here? */
            DDPixelFormat->dwZBufferBitDepth = 32;
            DDPixelFormat->dwStencilBitDepth = 4;
            DDPixelFormat->dwZBitMask = 0x00FFFFFF;
            DDPixelFormat->dwStencilBitMask = 0x0F000000;
            DDPixelFormat->dwRGBAlphaBitMask = 0x0;
            break;

        case D3DFMT_D24S8:
            DDPixelFormat->dwFlags = DDPF_ZBUFFER | DDPF_STENCILBUFFER;
            DDPixelFormat->dwFourCC = 0;
            /* Should I set dwZBufferBitDepth to 32 here? */
            DDPixelFormat->dwZBufferBitDepth = 32;
            DDPixelFormat->dwStencilBitDepth = 8;
            DDPixelFormat->dwZBitMask = 0x00FFFFFFFF;
            DDPixelFormat->dwStencilBitMask = 0xFF000000;
            DDPixelFormat->dwRGBAlphaBitMask = 0x0;
            break;

        case D3DFMT_D24X8:
            DDPixelFormat->dwFlags = DDPF_ZBUFFER;
            DDPixelFormat->dwFourCC = 0;
            DDPixelFormat->dwZBufferBitDepth = 32;
            DDPixelFormat->dwStencilBitDepth = 0;
            DDPixelFormat->dwZBitMask = 0x00FFFFFFFF;
            DDPixelFormat->dwStencilBitMask = 0x00000000;
            DDPixelFormat->dwRGBAlphaBitMask = 0x0;

            break;
        case D3DFMT_D15S1:
            DDPixelFormat->dwFlags = DDPF_ZBUFFER | DDPF_STENCILBUFFER;
            DDPixelFormat->dwFourCC = 0;
            DDPixelFormat->dwZBufferBitDepth = 16;
            DDPixelFormat->dwStencilBitDepth = 1;
            DDPixelFormat->dwZBitMask = 0x7fff;
            DDPixelFormat->dwStencilBitMask = 0x8000;
            DDPixelFormat->dwRGBAlphaBitMask = 0x0;
            break;

        case D3DFMT_UYVY:
        case D3DFMT_YUY2:
            DDPixelFormat->dwYUVBitCount = 16;
            DDPixelFormat->dwFlags = DDPF_FOURCC;
            DDPixelFormat->dwFourCC = format;
            break;

        case FOURCC_YV12:
            DDPixelFormat->dwYUVBitCount = 12;
            DDPixelFormat->dwFlags = DDPF_FOURCC;
            DDPixelFormat->dwFourCC = format;
            break;

        case D3DFMT_DXT1:
        case D3DFMT_DXT2:
        case D3DFMT_DXT3:
        case D3DFMT_DXT4:
        case D3DFMT_DXT5:
        case D3DFMT_MULTI2_ARGB8:
        case D3DFMT_G8R8_G8B8:
        case D3DFMT_R8G8_B8G8:
            DDPixelFormat->dwFlags = DDPF_FOURCC;
            DDPixelFormat->dwFourCC = format;
            break;

        /* Luminance */
        case D3DFMT_L8:
            DDPixelFormat->dwFlags = DDPF_LUMINANCE;
            DDPixelFormat->dwFourCC = 0;
            DDPixelFormat->dwLuminanceBitCount = 8;
            DDPixelFormat->dwLuminanceBitMask = 0xff;
            DDPixelFormat->dwBumpDvBitMask = 0x0;
            DDPixelFormat->dwBumpLuminanceBitMask = 0x0;
            DDPixelFormat->dwLuminanceAlphaBitMask = 0x0;
            break;

        case D3DFMT_A4L4:
            DDPixelFormat->dwFlags = DDPF_ALPHAPIXELS | DDPF_LUMINANCE;
            DDPixelFormat->dwFourCC = 0;
            DDPixelFormat->dwLuminanceBitCount = 4;
            DDPixelFormat->dwLuminanceBitMask = 0x0f;
            DDPixelFormat->dwBumpDvBitMask = 0x0;
            DDPixelFormat->dwBumpLuminanceBitMask = 0x0;
            DDPixelFormat->dwLuminanceAlphaBitMask = 0xf0;
            break;

        case D3DFMT_A8L8:
            DDPixelFormat->dwFlags = DDPF_ALPHAPIXELS | DDPF_LUMINANCE;
            DDPixelFormat->dwFourCC = 0;
            DDPixelFormat->dwLuminanceBitCount = 16;
            DDPixelFormat->dwLuminanceBitMask = 0x00ff;
            DDPixelFormat->dwBumpDvBitMask = 0x0;
            DDPixelFormat->dwBumpLuminanceBitMask = 0x0;
            DDPixelFormat->dwLuminanceAlphaBitMask = 0xff00;
            break;

        /* Bump mapping */
        case D3DFMT_V8U8:
            DDPixelFormat->dwFlags = DDPF_BUMPDUDV;
            DDPixelFormat->dwFourCC = 0;
            DDPixelFormat->dwBumpBitCount = 16;
            DDPixelFormat->dwBumpDuBitMask =         0x000000ff;
            DDPixelFormat->dwBumpDvBitMask =         0x0000ff00;
            DDPixelFormat->dwBumpLuminanceBitMask =  0x00000000;
            DDPixelFormat->dwLuminanceAlphaBitMask = 0x00000000;
            break;

        case D3DFMT_L6V5U5:
            DDPixelFormat->dwFlags = DDPF_BUMPDUDV;
            DDPixelFormat->dwFourCC = 0;
            DDPixelFormat->dwBumpBitCount = 16;
            DDPixelFormat->dwBumpDuBitMask =         0x0000001f;
            DDPixelFormat->dwBumpDvBitMask =         0x000003e0;
            DDPixelFormat->dwBumpLuminanceBitMask =  0x0000fc00;
            DDPixelFormat->dwLuminanceAlphaBitMask = 0x00000000;
            break;

        default:
            DEBUG_MESSAGE("Can't translate this Pixelformat %d\n", format);
    }
}

UINT GetPrimitiveCount(D3DPRIMITIVETYPE PrimitiveType, UINT VertexCount)
{
	switch (PrimitiveType)
	{
	case D3DPT_LINELIST:
		return VertexCount / 2;
	case D3DPT_LINESTRIP:
		return VertexCount - 1;
	case D3DPT_TRIANGLELIST:
		return VertexCount / 3;
	case D3DPT_TRIANGLESTRIP:
	case D3DPT_TRIANGLEFAN:
		return VertexCount - 2;
	}
	return VertexCount;
}

DWORD GetVertexSize(DWORD FVF)
{
	DWORD vertexSize;// = D3DXGetFVFVertexSize(FVF);
	//return vertexSize;
	vertexSize = 0;
	DWORD Position = FVF & D3DFVF_POSITION_MASK;
	switch (Position)
	{
	case D3DFVF_XYZ:
		vertexSize += 3 * 4;
		break;
	case D3DFVF_XYZRHW:
	case D3DFVF_XYZW:
	case D3DFVF_XYZB1:
		vertexSize += 4 * 4;
		break;
	case D3DFVF_XYZB2:
		vertexSize += 5 * 4;
		break;
	case D3DFVF_XYZB3:
		vertexSize += 6 * 4;
		break;
	case D3DFVF_XYZB4:
		vertexSize += 7 * 4;
		break;
	case D3DFVF_XYZB5:
		vertexSize += 8 * 4;
		break;
	};

	if (FVF & D3DFVF_NORMAL)
		vertexSize += 3 * 4;
	if (FVF & D3DFVF_DIFFUSE)
		vertexSize += 4;
	if (FVF & D3DFVF_SPECULAR)
		vertexSize += 4;
	if (FVF & D3DFVF_RESERVED1)
		vertexSize += 4;
	
#define GET_TEXCOUNT_FROM_FVF() \
	(((FVF) & D3DFVF_TEXCOUNT_MASK) >> D3DFVF_TEXCOUNT_SHIFT)

#define GET_TEXCOORD_SIZE_FROM_FVF(tex_num) \
	((((FVF >> (16 + (2 * tex_num))) + 1) & 0x03) + 1)

	DWORD TexCount = GET_TEXCOUNT_FROM_FVF();     
	for (DWORD i = 0; i < TexCount; i++)
	{
		vertexSize += GET_TEXCOORD_SIZE_FROM_FVF(i) * 4;
	}

#undef GET_TEXCOUNT_FROM_FVF
#undef GET_TEXCOORD_SIZE_FROM_FVF

	return vertexSize;
}