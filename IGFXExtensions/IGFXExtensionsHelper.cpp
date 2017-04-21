/////////////////////////////////////////////////////////////////////////////////////////////
// Copyright 2017 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");// you may not use this file except in compliance with the License.// You may obtain a copy of the License at//// http://www.apache.org/licenses/LICENSE-2.0//// Unless required by applicable law or agreed to in writing, software// distributed under the License is distributed on an "AS IS" BASIS,// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.// See the License for the specific language governing permissions and// limitations under the License.
/////////////////////////////////////////////////////////////////////////////////////////////

#include "IGFXExtensionsHelper.h"

using namespace ID3D10;

namespace IGFX
{
	//--------------------------------------------------------------------------------------
	// Initialize Intel extensions (if available)
	//--------------------------------------------------------------------------------------
	HRESULT Init( ID3D11Device *pd3dDevice )
	{
		CAPS_EXTENSION intelExtCaps;

		ZeroMemory( &intelExtCaps, sizeof(CAPS_EXTENSION) );

		if ( !pd3dDevice )
			return E_FAIL;
		
		if( S_OK != GetExtensionCaps( pd3dDevice, &intelExtCaps ) )
			return E_FAIL;
		
		if( intelExtCaps.DriverVersion < EXTENSION_INTERFACE_VERSION_1_0 )
			return E_FAIL;

		return S_OK;
	}

	//--------------------------------------------------------------------------------------
	// Get the available hardware extensions available on this system
	//--------------------------------------------------------------------------------------
	Extensions getAvailableExtensions( ID3D11Device *pd3dDevice )
	{
		CAPS_EXTENSION intelExtCaps;
		Extensions extensions = {0};

		ZeroMemory( &intelExtCaps, sizeof(CAPS_EXTENSION) );

		if ( pd3dDevice )
		{
			if( S_OK == GetExtensionCaps( pd3dDevice, &intelExtCaps ) )
			{
				if( intelExtCaps.DriverVersion >= EXTENSION_INTERFACE_VERSION_1_0 )
				{
					extensions.DirectResourceAccess = true;
					extensions.PixelShaderOrdering = true;
				}
			}
		}

		return extensions;
	}

	//--------------------------------------------------------------------------------------
	// Create a resource that can be directly accessed by the CPU
	//--------------------------------------------------------------------------------------
	HRESULT CreateGPUSharedTexture2D( ID3D11Device *pd3dDevice, const D3D11_TEXTURE2D_DESC *tex2d, ID3D11Texture2D **pGPUSharedTexture2D, D3D11_SUBRESOURCE_DATA *initData )
	{
		HRESULT hr = S_OK;

		// Enable the extension
		hr = SetDirectAccessResouceExtension( 
			pd3dDevice,
			0 );

		if( S_OK == hr )
		{
			// Create the GPU texture
			hr = pd3dDevice->CreateTexture2D(
				tex2d,
				&initData[0],
				pGPUSharedTexture2D );
		}

		return hr;
	}

	//--------------------------------------------------------------------------------------
	// Create a false binding resource to bypass Runtime Restriction of only mapping
	// STAGING resources.
	//--------------------------------------------------------------------------------------
	HRESULT CreateCPUSharedTexture2D( ID3D11Device *pd3dDevice, const D3D11_TEXTURE2D_DESC *tex2d, ID3D11Texture2D **pCPUSharedTexture2D )
	{
		HRESULT hr = S_OK;

		// Enable the extension
		hr = SetDirectAccessResouceExtension(
			pd3dDevice,
			0 );

		if( S_OK == hr )
		{
			// Create the CPU texture
			hr = pd3dDevice->CreateTexture2D( 
				tex2d,
				NULL,
				pCPUSharedTexture2D );
		}

		return hr;
	}

	//--------------------------------------------------------------------------------------
	// Create a resource that can be directly accessed by the CPU
	//--------------------------------------------------------------------------------------
	HRESULT CreateSharedTexture2D( ID3D11Device *pd3dDevice, const D3D11_TEXTURE2D_DESC *tex2d_cpu, ID3D11Texture2D **pCPUSharedTexture2D, const D3D11_TEXTURE2D_DESC *tex2d_gpu, ID3D11Texture2D **pGPUSharedTexture2D, D3D11_SUBRESOURCE_DATA *initData )
	{
		HRESULT hr = S_OK;

		hr = IGFX::CreateGPUSharedTexture2D( pd3dDevice, tex2d_gpu, pGPUSharedTexture2D, initData );
		if ( FAILED(hr) )
			return hr;

		hr = IGFX::CreateCPUSharedTexture2D( pd3dDevice, tex2d_cpu, pCPUSharedTexture2D );
		if ( FAILED(hr) )
			return hr;

		return hr;
	}
}
