//
//   Copyright 2013 Pixar
//
//   Licensed under the Apache License, Version 2.0 (the "Apache License")
//   with the following modification; you may not use this file except in
//   compliance with the Apache License and the following modification to it:
//   Section 6. Trademarks. is deleted and replaced with:
//
//   6. Trademarks. This License does not grant permission to use the trade
//      names, trademarks, service marks, or product names of the Licensor
//      and its affiliates, except as required to comply with Section 4(c) of
//      the License and to reproduce the content of the NOTICE file.
//
//   You may obtain a copy of the Apache License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the Apache License with the above modification is
//   distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
//   KIND, either express or implied. See the Apache License for the specific
//   language governing permissions and limitations under the Apache License.
//

#ifndef FAR_CPU_EVALSTENCILS_CONTEXT_H
#define FAR_CPU_EVALSTENCILS_CONTEXT_H

#include "../version.h"

#include "../far/stencilTables.h"

#include "../osd/vertexDescriptor.h"
#include "../osd/nonCopyable.h"

namespace OpenSubdiv {
namespace OPENSUBDIV_VERSION {

///
/// \brief CPU stencils evaluation context
///
///
class OsdCpuEvalStencilsContext : OsdNonCopyable<OsdCpuEvalStencilsContext> {

public:
    /// \brief Creates an OsdCpuEvalStencilsContext instance
    ///
    /// @param stencils  a pointer to the FarStencilTables
    ///
    static OsdCpuEvalStencilsContext * Create(FarStencilTables const *stencils);

    /// \brief Binds control vertex data buffer
    ///
    /// Binding ensures that data buffers are properly inter-operated between
    /// Contexts and Controllers operating across multiple devices.
    ///
    /// @param controlDataDesc  A buffer descriptor for the control vertices
    ///                         data
    ///
    /// @param controlData      A buffer for the control vertices data
    ///
    template<class VERTEX_BUFFER>
    void BindControlData(OsdVertexBufferDescriptor const & controlDataDesc, VERTEX_BUFFER *controlData ) {

        _controlData = controlData ? controlData->BindCpuBuffer() : 0;
        _controlDataDesc = controlDataDesc;

    }

    /// \brief Binds output vertex data buffer
    ///
    /// Binding ensures that data buffers are properly inter-operated between
    /// Contexts and Controllers operating across multiple devices.
    ///
    /// @param outputDataDesc  A buffer descriptor for the output vertex 
    ///                        interpolated data
    ///
    /// @param outputData      A buffer for vertex interpolated data
    ///
    template<class VERTEX_BUFFER>
    void BindOutputData( OsdVertexBufferDescriptor const & outputDataDesc, VERTEX_BUFFER *outputData ) {

        _outputData = outputData ? outputData->BindCpuBuffer() : 0;
        _outputDataDesc = outputDataDesc;
    }
    
    /// \brief Binds output derivative vertex data buffer
    ///
    /// Binding ensures that data buffers are properly inter-operated between
    /// Contexts and Controllers operating across multiple devices.
    ///
    /// @param outputDuDesc  A buffer descriptor for the output U derivative
    ///                      vertex data
    ///
    /// @param outputDu      A buffer for the output U derivative data
    ///
    /// @param outputDvDesc  A buffer descriptor for the output V derivative
    ///                      vertex data
    ///
    /// @param outputDv      A buffer for the output V derivative data
    ///
    template<class VERTEX_BUFFER>
    void BindOutputDerivData( OsdVertexBufferDescriptor const & outputDuDesc, VERTEX_BUFFER *outputDu, 
                              OsdVertexBufferDescriptor const & outputDvDesc, VERTEX_BUFFER *outputDv ) {
                              
        _outputUDeriv = outputDu ? outputDu ->BindCpuBuffer() : 0;
        _outputVDeriv = outputDv ? outputDv->BindCpuBuffer() : 0;
        _outputDuDesc = outputDuDesc;
        _outputDvDesc = outputDvDesc;
    }

    /// \brief Unbinds any previously bound vertex and varying data buffers.
    void Unbind() {
       _controlData = 0;
       _controlDataDesc.Reset();

       _outputData = 0;
       _outputDataDesc.Reset();
      
       _outputUDeriv = 0;
       _outputDuDesc.Reset();
       
       _outputVDeriv = 0;
       _outputDvDesc.Reset();
    }

    /// \brief returns a pointer to the control vertex data
    real const * GetControlData() const {
        return _controlData;
    }

    /// \brief returns a pointer to the output vertex data
    real * GetOutputData() {
        return _outputData;
    }

    /// \brief returns a pointer to the output u-derivative vertex data
    real * GetOutputUDerivData() {
        return _outputUDeriv;
    }

    /// \brief returns a pointer to the output v-derivative vertex data
    real * GetOutputVDerivData() {
        return _outputVDeriv;
    }

    /// \brief Returns the vertex data descriptor for the control vertices buffer
    OsdVertexBufferDescriptor GetControlDataDescriptor() const {
        return _controlDataDesc;
    }

    /// \brief Returns the vertex data descriptor for the output vertices buffer
    OsdVertexBufferDescriptor GetOutputDataDescriptor() const {
        return _outputDataDesc;
    }

    /// \brief Returns the vertex data descriptor for the U derivatives data buffer
    OsdVertexBufferDescriptor GetDuDataDescriptor() const {
        return _outputDuDesc;
    }

    /// \brief Returns the vertex data descriptor for the V derivatives data buffer
    OsdVertexBufferDescriptor GetDvDataDescriptor() const {
        return _outputDvDesc;
    }
    

    /// \brief Returns the FarStencilTables applied
    FarStencilTables const * GetStencilTables() const {
        return _stencils;
    }

protected:

    OsdCpuEvalStencilsContext(FarStencilTables const *stencils);

private:
    
    FarStencilTables const * _stencils;

    OsdVertexBufferDescriptor _controlDataDesc,
                              _outputDataDesc,
                              _outputDuDesc,
                              _outputDvDesc;

    real * _controlData,
          * _outputData,
          * _outputUDeriv,
          * _outputVDeriv;
};

} // end namespace OPENSUBDIV_VERSION
using namespace OPENSUBDIV_VERSION;

} // end namespace OpenSubdiv

#endif // FAR_CPU_EVALSTENCILS_CONTEXT_H
