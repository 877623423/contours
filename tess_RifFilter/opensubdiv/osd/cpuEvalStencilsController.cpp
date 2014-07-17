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

#include "../osd/cpuEvalStencilsController.h"

#include <cassert>

namespace OpenSubdiv {
namespace OPENSUBDIV_VERSION {

OsdCpuEvalStencilsController::OsdCpuEvalStencilsController() {
}

OsdCpuEvalStencilsController::~OsdCpuEvalStencilsController() {
}

int 
OsdCpuEvalStencilsController::_UpdateValues( OsdCpuEvalStencilsContext * context ) {

    int result=0;

    FarStencilTables const * stencils = context->GetStencilTables();

    int nstencils = stencils->GetNumStencils();
    if (not nstencils)
        return result;
    
    OsdVertexBufferDescriptor ctrlDesc = _currentBindState.controlDataDesc,
                              outDesc = _currentBindState.outputDataDesc;
    
    // make sure that we have control data to work with
    if (not ctrlDesc.CanEval(outDesc))
        return 0;

    real const * ctrl = _currentBindState.controlData + ctrlDesc.offset;

    real * out = _currentBindState.outputData + outDesc.offset;

    if ((not ctrl) or (not out))
        return result;

    int const * sizes = &stencils->GetSizes().at(0),
              * index = &stencils->GetControlIndices().at(0);
    
    real const * weight = &stencils->GetWeights().at(0);

    for (int i=0; i<nstencils; ++i) {

        memset(out, 0, outDesc.length*sizeof(real));
        
        for (int j=0; j<sizes[i]; ++j, ++index, ++weight) {
        
            real const * cv = ctrl + (*index)*ctrlDesc.stride;

            for (int k=0; k<outDesc.length; ++k) {
                out[k] += cv[k] * (*weight);
            }
        }
        out += outDesc.stride;
    }
    
    return nstencils;
}

int 
OsdCpuEvalStencilsController::_UpdateDerivs( OsdCpuEvalStencilsContext * context ) {

    int result=0;

    FarStencilTables const * stencils = context->GetStencilTables();

    int nstencils = stencils->GetNumStencils();
    if (not nstencils)
        return result;
    
    OsdVertexBufferDescriptor ctrlDesc = _currentBindState.controlDataDesc,
                              duDesc = _currentBindState.outputDuDesc,
                              dvDesc = _currentBindState.outputDvDesc;
    
    // make sure that we have control data to work with
    if (not (ctrlDesc.CanEval(duDesc) and ctrlDesc.CanEval(dvDesc)))
        return 0;

    real const * ctrl = _currentBindState.controlData + ctrlDesc.offset;

    real * du = _currentBindState.outputUDeriv + duDesc.offset,
          * dv = _currentBindState.outputVDeriv + dvDesc.offset;

    if ((not ctrl) or (not du) or (not dv))
        return result;

    int const * sizes = &stencils->GetSizes().at(0),
              * index = &stencils->GetControlIndices().at(0);
    
    real const * duweight = &stencils->GetDuWeights().at(0),
                * dvweight = &stencils->GetDvWeights().at(0);
                           
    for (int i=0; i<nstencils; ++i) {

        memset(du, 0, duDesc.length*sizeof(real));
        memset(dv, 0, dvDesc.length*sizeof(real));
        
        for (int j=0; j<sizes[i]; ++j, ++index, ++duweight, ++dvweight) {
        
            real const * cv = ctrl + (*index)*ctrlDesc.stride;
        
            for (int k=0; k<duDesc.length; ++k) {
                du[k] += cv[k] * (*duweight);
                dv[k] += cv[k] * (*dvweight);
            }
        }
        du += duDesc.stride;
        dv += dvDesc.stride;
    }
    
    return nstencils;
}

void
OsdCpuEvalStencilsController::Synchronize() {
}


}  // end namespace OPENSUBDIV_VERSION
}  // end namespace OpenSubdiv
