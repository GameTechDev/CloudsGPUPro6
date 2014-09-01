//--------------------------------------------------------------------------------------
// Copyright 2013 Intel Corporation
// All Rights Reserved
//
// Permission is granted to use, copy, distribute and prepare derivative works of this
// software for any purpose and without fee, provided, that the above copyright notice
// and this statement appear in all copies.  Intel makes no representations about the
// suitability of this software for any purpose.  THIS SOFTWARE IS PROVIDED "AS IS."
// INTEL SPECIFICALLY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, AND ALL LIABILITY,
// INCLUDING CONSEQUENTIAL AND OTHER INDIRECT DAMAGES, FOR THE USE OF THIS SOFTWARE,
// INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PROPRIETARY RIGHTS, AND INCLUDING THE
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  Intel does not
// assume any responsibility for any errors which may appear in this software nor any
// responsibility to update it.
//--------------------------------------------------------------------------------------


#include "CPUTGeometryShaderDX11.h"
#include "CPUTAssetLibraryDX11.h"

CPUTGeometryShaderDX11 *CPUTGeometryShaderDX11::CreateGeometryShader(
    const cString        &name,
    ID3D11Device         *pD3dDevice,
    const cString        &shaderMain,
    const cString        &shaderProfile
)
{
    ID3DBlob             *pCompiledBlob = NULL;
    ID3D11GeometryShader *pNewGeometryShader = NULL;

    CPUTAssetLibraryDX11 *pAssetLibrary = (CPUTAssetLibraryDX11*)CPUTAssetLibrary::GetAssetLibrary();
    CPUTResult result = pAssetLibrary->CompileShaderFromFile(name, shaderMain, shaderProfile, &pCompiledBlob);
    ASSERT( CPUTSUCCESS(result), _L("Error compiling Geometry shader:\n\n") );

    // Create the Geometry shader
    // TODO: Move to Geometry shader class
    HRESULT hr = pD3dDevice->CreateGeometryShader( pCompiledBlob->GetBufferPointer(), pCompiledBlob->GetBufferSize(), NULL, &pNewGeometryShader );
    ASSERT( SUCCEEDED(hr), _L("Error creating Geometry shader:\n\n") );
    // cString DebugName = _L("CPUTAssetLibraryDX11::GetGeometryShader ")+name;
    // CPUTSetDebugName(pNewGeometryShader, DebugName);

    CPUTGeometryShaderDX11 *pNewCPUTGeometryShader = new CPUTGeometryShaderDX11( pNewGeometryShader, pCompiledBlob );

    // add shader to library
    pAssetLibrary->AddGeometryShader(name + shaderMain + shaderProfile, pNewCPUTGeometryShader);
    // pNewCPUTGeometryShader->Release(); // We've added it to the library, so release our reference

    // return the shader (and blob)
    return pNewCPUTGeometryShader;
}

//--------------------------------------------------------------------------------------
CPUTGeometryShaderDX11 *CPUTGeometryShaderDX11::CreateGeometryShaderFromMemory(
    const cString        &name,
    ID3D11Device         *pD3dDevice,
    const cString        &shaderMain,
    const cString        &shaderProfile,
    const char           *pShaderSource
)
{
    ID3DBlob             *pCompiledBlob = NULL;
    ID3D11GeometryShader *pNewGeometryShader = NULL;

    CPUTAssetLibraryDX11 *pAssetLibrary = (CPUTAssetLibraryDX11*)CPUTAssetLibrary::GetAssetLibrary();
    CPUTResult result = pAssetLibrary->CompileShaderFromMemory(pShaderSource, shaderMain, shaderProfile, &pCompiledBlob);
    ASSERT( CPUTSUCCESS(result), _L("Error creating Geometry shader:\n\n") );

    // Create the Geometry shader
    // TODO: Move to Geometry shader class
    HRESULT hr = pD3dDevice->CreateGeometryShader( pCompiledBlob->GetBufferPointer(), pCompiledBlob->GetBufferSize(), NULL, &pNewGeometryShader );
    ASSERT( SUCCEEDED(hr), _L("Error compiling Geometry shader:\n\n") );
    // cString DebugName = _L("CPUTAssetLibraryDX11::GetGeometryShader ")+name;
    // CPUTSetDebugName(pNewGeometryShader, DebugName);

    CPUTGeometryShaderDX11 *pNewCPUTGeometryShader = new CPUTGeometryShaderDX11( pNewGeometryShader, pCompiledBlob );

    // add shader to library
    pAssetLibrary->AddGeometryShader(name + shaderMain + shaderProfile, pNewCPUTGeometryShader);
    // pNewCPUTGeometryShader->Release(); // We've added it to the library, so release our reference

    // return the shader (and blob)
    return pNewCPUTGeometryShader;
}
