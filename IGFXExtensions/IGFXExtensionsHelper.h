/////////////////////////////////////////////////////////////////////////////////////////////
// Copyright 2017 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");// you may not use this file except in compliance with the License.// You may obtain a copy of the License at//// http://www.apache.org/licenses/LICENSE-2.0//// Unless required by applicable law or agreed to in writing, software// distributed under the License is distributed on an "AS IS" BASIS,// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.// See the License for the specific language governing permissions and// limitations under the License.
/////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <D3D11.h>
#include <D3DCompiler.h>

#include "ID3D10Extensions.h"

using namespace ID3D10;

namespace IGFX
{
	struct Extensions
	{
		bool PixelShaderOrdering; 
		bool DirectResourceAccess;
	};

	HRESULT Init( ID3D11Device *pDevice );

	Extensions getAvailableExtensions( ID3D11Device *pd3dDevice );

	HRESULT CreateCPUSharedTexture2D( ID3D11Device *pd3dDevice, const D3D11_TEXTURE2D_DESC *tex2d,   ID3D11Texture2D **pCPUSharedTexture2D );
	
	HRESULT CreateGPUSharedTexture2D( ID3D11Device *pd3dDevice, const D3D11_TEXTURE2D_DESC *tex2d,   ID3D11Texture2D **pGPUSharedTexture2D, D3D11_SUBRESOURCE_DATA *initData = NULL );

	HRESULT CreateSharedTexture2D( ID3D11Device *pd3dDevice, const D3D11_TEXTURE2D_DESC *tex2d_cpu, ID3D11Texture2D **pCPUSharedTexture2D, const D3D11_TEXTURE2D_DESC *tex2d_gpu, ID3D11Texture2D **pGPUSharedTexture2D, D3D11_SUBRESOURCE_DATA *initData = NULL );

}