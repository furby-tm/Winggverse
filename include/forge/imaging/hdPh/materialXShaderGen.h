#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/materialXShaderGen.h"
/*
 * Copyright 2021 Forge. All Rights Reserved.
 *
 * The use of this software is subject to the terms of the
 * Forge license agreement provided at the time of installation
 * or download, or which otherwise accompanies this software in
 * either electronic or hard copy form.
 *
 * Portions of this file are derived from original work by Pixar
 * distributed with Universal Scene Description, a project of the
 * Academy Software Foundation (ASWF). https://www.aswf.io/
 *
 * Original Copyright (C) 2016-2021 Pixar.
 * Modifications copyright (C) 2020-2021 ForgeXYZ LLC.
 *
 * Forge. The Animation Software & Motion Picture Co.
 */
#ifndef FORGE_IMAGING_HD_PH_MATERIALX_SHADER_GEN_H
#define FORGE_IMAGING_HD_PH_MATERIALX_SHADER_GEN_H

#include "forge/forge.h"

#include <MaterialXGenGlsl/GlslShaderGenerator.h>

FORGE_NAMESPACE_BEGIN

/// \class HdPhMaterialXShaderGen
///
/// Generates a glslfx shader with a surfaceShader function for a MaterialX
/// network
class HdPhMaterialXShaderGen : public MaterialX::GlslShaderGenerator {
 public:
  HdPhMaterialXShaderGen(MaterialX::StringMap const &mxHdTextureMap);

  static MaterialX::ShaderGeneratorPtr create(
      MaterialX::StringMap const &mxHdTextureMap = MaterialX::StringMap())
  {
    return std::make_shared<HdPhMaterialXShaderGen>(mxHdTextureMap);
  }

  MaterialX::ShaderPtr generate(const std::string &shaderName,
                                MaterialX::ElementPtr mxElement,
                                MaterialX::GenContext &mxContext) const override;

 protected:
  void _EmitGlslfxShader(const MaterialX::ShaderGraph &mxGraph,
                         MaterialX::GenContext &mxContext,
                         MaterialX::ShaderStage &mxStage) const;

 private:
  /// These three helper functions generate the Glslfx Shader
  void _EmitGlslfxHeader(MaterialX::ShaderStage &mxStage) const;

  void _EmitMxFunctions(const MaterialX::ShaderGraph &mxGraph,
                        MaterialX::GenContext &mxContext,
                        MaterialX::ShaderStage &mxStage) const;

  void _EmitMxSurfaceShader(const MaterialX::ShaderGraph &mxGraph,
                            MaterialX::GenContext &mxContext,
                            MaterialX::ShaderStage &mxStage) const;

  // Helper functions to generate the conversion between Hd and Mx VertexData
  void _EmitMxInitFunction(MaterialX::VariableBlock const &vertexData,
                           MaterialX::ShaderStage &mxStage) const;

  void _EmitMxVertexDataDeclarations(MaterialX::VariableBlock const &block,
                                     std::string const &mxVertexDataName,
                                     std::string const &mxVertexDataVariable,
                                     std::string const &separator,
                                     MaterialX::ShaderStage &mxStage) const;

  std::string _EmitMxVertexDataLine(const MaterialX::ShaderPort *variable,
                                    std::string const &separator) const;

  // Overriding the MaterialX function to make sure we initialize some Mx
  // variables with the appropriate Hd Value.
  void emitVariableDeclarations(MaterialX::VariableBlock const &block,
                                std::string const &qualifier,
                                std::string const &separator,
                                MaterialX::GenContext &context,
                                MaterialX::ShaderStage &stage,
                                bool assignValue = true) const override;

  // Store MaterialX texture node names and their Hydra counterparts to
  // initialize the texture sampler values
  MaterialX::StringMap _mxHdTextureMap;
};

FORGE_NAMESPACE_END

#endif