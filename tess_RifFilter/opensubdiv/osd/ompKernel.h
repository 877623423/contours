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

#ifndef OSD_OMP_KERNEL_H
#define OSD_OMP_KERNEL_H

#include "../version.h"

namespace OpenSubdiv {
namespace OPENSUBDIV_VERSION {

struct OsdVertexDescriptor;

void OsdOmpComputeFace(OsdVertexDescriptor const &vdesc,
                       real * vertex, real * varying,
                       const int *F_IT, const int *F_ITa,
                       int vertexOffset, int tableOffset,
                       int start, int end);

void OsdOmpComputeEdge(OsdVertexDescriptor const &vdesc,
                       real *vertex, real * varying,
                       const int *E_IT, const real *E_ITa,
                       int vertexOffset, int tableOffset,
                       int start, int end);

void OsdOmpComputeVertexA(OsdVertexDescriptor const &vdesc,
                          real *vertex, real * varying,
                          const int *V_ITa, const real *V_IT,
                          int vertexOffset, int tableOffset,
                          int start, int end, int pass);

void OsdOmpComputeVertexB(OsdVertexDescriptor const &vdesc,
                          real *vertex, real * varying,
                          const int *V_ITa, const int *V_IT, const real *V_W,
                          int vertexOffset, int tableOffset,
                          int start, int end);

void OsdOmpComputeLoopVertexB(OsdVertexDescriptor const &vdesc,
                              real *vertex, real * varying,
                              const int *V_ITa, const int *V_IT,
                              const real *V_W,
                              int vertexOffset, int tableOffset,
                              int start, int end);

void OsdOmpComputeBilinearEdge(OsdVertexDescriptor const &vdesc,
                               real *vertex, real * varying,
                               const int *E_IT,
                               int vertexOffset, int tableOffset,
                               int start, int end);

void OsdOmpComputeBilinearVertex(OsdVertexDescriptor const &vdesc,
                                 real *vertex, real * varying,
                                 const int *V_ITa,
                                 int vertexOffset, int tableOffset,
                                 int start, int end);

void OsdOmpEditVertexAdd(OsdVertexDescriptor const &vdesc, real *vertex,
                         int primVarOffset, int primVarWidth,
                         int vertexOffset, int tableOffset,
                         int start, int end,
                         const unsigned int *editIndices,
                         const real *editValues);

void OsdOmpEditVertexSet(OsdVertexDescriptor const &vdesc, real *vertex,
                         int primVarOffset, int primVarWidth,
                         int vertexOffset, int tableOffset,
                         int start, int end,
                         const unsigned int *editIndices,
                         const real *editValues);

}  // end namespace OPENSUBDIV_VERSION
using namespace OPENSUBDIV_VERSION;

}  // end namespace OpenSubdiv

#endif  // OSD_OMP_KERNEL_H
