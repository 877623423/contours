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

#include "../osd/cpuComputeContext.h"
#include "../osd/cpuComputeController.h"
#include "../osd/cpuKernel.h"

namespace OpenSubdiv {
namespace OPENSUBDIV_VERSION {


OsdCpuComputeController::OsdCpuComputeController() {
}

OsdCpuComputeController::~OsdCpuComputeController() {
}

void
OsdCpuComputeController::ApplyBilinearFaceVerticesKernel(
    FarKernelBatch const &batch, void * clientdata) const {

    OsdCpuComputeContext * context =
        static_cast<OsdCpuComputeContext*>(clientdata);
    assert(context);

    OsdCpuComputeFace(
        context->GetVertexDescriptor(),
        context->GetCurrentVertexBuffer(),
        context->GetCurrentVaryingBuffer(),
        (const int*)context->GetTable(FarSubdivisionTables<OsdVertex>::F_IT)->GetBuffer(),
        (const int*)context->GetTable(FarSubdivisionTables<OsdVertex>::F_ITa)->GetBuffer(),
        batch.GetVertexOffset(), batch.GetTableOffset(), batch.GetStart(), batch.GetEnd());
}

void
OsdCpuComputeController::ApplyBilinearEdgeVerticesKernel(
    FarKernelBatch const &batch, void * clientdata) const {

    OsdCpuComputeContext * context =
        static_cast<OsdCpuComputeContext*>(clientdata);
    assert(context);

    OsdCpuComputeBilinearEdge(
        context->GetVertexDescriptor(),
        context->GetCurrentVertexBuffer(),
        context->GetCurrentVaryingBuffer(),
        (const int*)context->GetTable(FarSubdivisionTables<OsdVertex>::E_IT)->GetBuffer(),
        batch.GetVertexOffset(), batch.GetTableOffset(), batch.GetStart(), batch.GetEnd());
}

void
OsdCpuComputeController::ApplyBilinearVertexVerticesKernel(
    FarKernelBatch const &batch, void * clientdata) const {

    OsdCpuComputeContext * context =
        static_cast<OsdCpuComputeContext*>(clientdata);
    assert(context);

    OsdCpuComputeBilinearVertex(
        context->GetVertexDescriptor(),
        context->GetCurrentVertexBuffer(),
        context->GetCurrentVaryingBuffer(),
        (const int*)context->GetTable(FarSubdivisionTables<OsdVertex>::V_ITa)->GetBuffer(),
        batch.GetVertexOffset(), batch.GetTableOffset(), batch.GetStart(), batch.GetEnd());
}

void
OsdCpuComputeController::ApplyCatmarkFaceVerticesKernel(
    FarKernelBatch const &batch, void * clientdata) const {

    OsdCpuComputeContext * context =
        static_cast<OsdCpuComputeContext*>(clientdata);
    assert(context);

    OsdCpuComputeFace(
        context->GetVertexDescriptor(),
        context->GetCurrentVertexBuffer(),
        context->GetCurrentVaryingBuffer(),
        (const int*)context->GetTable(FarSubdivisionTables<OsdVertex>::F_IT)->GetBuffer(),
        (const int*)context->GetTable(FarSubdivisionTables<OsdVertex>::F_ITa)->GetBuffer(),
        batch.GetVertexOffset(), batch.GetTableOffset(), batch.GetStart(), batch.GetEnd());
}

void
OsdCpuComputeController::ApplyCatmarkEdgeVerticesKernel(
    FarKernelBatch const &batch, void * clientdata) const {

    OsdCpuComputeContext * context =
        static_cast<OsdCpuComputeContext*>(clientdata);
    assert(context);

    OsdCpuComputeEdge(
        context->GetVertexDescriptor(),
        context->GetCurrentVertexBuffer(),
        context->GetCurrentVaryingBuffer(),
        (const int*)context->GetTable(FarSubdivisionTables<OsdVertex>::E_IT)->GetBuffer(),
        (const real*)context->GetTable(FarSubdivisionTables<OsdVertex>::E_W)->GetBuffer(),
        batch.GetVertexOffset(), batch.GetTableOffset(), batch.GetStart(), batch.GetEnd());
}

void
OsdCpuComputeController::ApplyCatmarkVertexVerticesKernelB(
    FarKernelBatch const &batch, void * clientdata) const {

    OsdCpuComputeContext * context =
        static_cast<OsdCpuComputeContext*>(clientdata);
    assert(context);

    OsdCpuComputeVertexB(
        context->GetVertexDescriptor(),
        context->GetCurrentVertexBuffer(),
        context->GetCurrentVaryingBuffer(),
        (const int*)context->GetTable(FarSubdivisionTables<OsdVertex>::V_ITa)->GetBuffer(),
        (const int*)context->GetTable(FarSubdivisionTables<OsdVertex>::V_IT)->GetBuffer(),
        (const real*)context->GetTable(FarSubdivisionTables<OsdVertex>::V_W)->GetBuffer(),
        batch.GetVertexOffset(), batch.GetTableOffset(), batch.GetStart(), batch.GetEnd());
}

void
OsdCpuComputeController::ApplyCatmarkVertexVerticesKernelA1(
    FarKernelBatch const &batch, void * clientdata) const {

    OsdCpuComputeContext * context =
        static_cast<OsdCpuComputeContext*>(clientdata);
    assert(context);

    OsdCpuComputeVertexA(
        context->GetVertexDescriptor(),
        context->GetCurrentVertexBuffer(),
        context->GetCurrentVaryingBuffer(),
        (const int*)context->GetTable(FarSubdivisionTables<OsdVertex>::V_ITa)->GetBuffer(),
        (const real*)context->GetTable(FarSubdivisionTables<OsdVertex>::V_W)->GetBuffer(),
        batch.GetVertexOffset(), batch.GetTableOffset(), batch.GetStart(), batch.GetEnd(), false);
}

void
OsdCpuComputeController::ApplyCatmarkVertexVerticesKernelA2(
    FarKernelBatch const &batch, void * clientdata) const {

    OsdCpuComputeContext * context =
        static_cast<OsdCpuComputeContext*>(clientdata);
    assert(context);

    OsdCpuComputeVertexA(
        context->GetVertexDescriptor(),
        context->GetCurrentVertexBuffer(),
        context->GetCurrentVaryingBuffer(),
        (const int*)context->GetTable(FarSubdivisionTables<OsdVertex>::V_ITa)->GetBuffer(),
        (const real*)context->GetTable(FarSubdivisionTables<OsdVertex>::V_W)->GetBuffer(),
        batch.GetVertexOffset(), batch.GetTableOffset(), batch.GetStart(), batch.GetEnd(), true);
}

void
OsdCpuComputeController::ApplyLoopEdgeVerticesKernel(
    FarKernelBatch const &batch, void * clientdata) const {

    OsdCpuComputeContext * context =
        static_cast<OsdCpuComputeContext*>(clientdata);
    assert(context);

    OsdCpuComputeEdge(
        context->GetVertexDescriptor(),
        context->GetCurrentVertexBuffer(),
        context->GetCurrentVaryingBuffer(),
        (const int*)context->GetTable(FarSubdivisionTables<OsdVertex>::E_IT)->GetBuffer(),
        (const real*)context->GetTable(FarSubdivisionTables<OsdVertex>::E_W)->GetBuffer(),
        batch.GetVertexOffset(), batch.GetTableOffset(), batch.GetStart(), batch.GetEnd());
}

void
OsdCpuComputeController::ApplyLoopVertexVerticesKernelB(
    FarKernelBatch const &batch, void * clientdata) const {

    OsdCpuComputeContext * context =
        static_cast<OsdCpuComputeContext*>(clientdata);
    assert(context);

    OsdCpuComputeLoopVertexB(
        context->GetVertexDescriptor(),
        context->GetCurrentVertexBuffer(),
        context->GetCurrentVaryingBuffer(),
        (const int*)context->GetTable(FarSubdivisionTables<OsdVertex>::V_ITa)->GetBuffer(),
        (const int*)context->GetTable(FarSubdivisionTables<OsdVertex>::V_IT)->GetBuffer(),
        (const real*)context->GetTable(FarSubdivisionTables<OsdVertex>::V_W)->GetBuffer(),
        batch.GetVertexOffset(), batch.GetTableOffset(), batch.GetStart(), batch.GetEnd());
}

void
OsdCpuComputeController::ApplyLoopVertexVerticesKernelA1(
    FarKernelBatch const &batch, void * clientdata) const {

    OsdCpuComputeContext * context =
        static_cast<OsdCpuComputeContext*>(clientdata);
    assert(context);

    OsdCpuComputeVertexA(
        context->GetVertexDescriptor(),
        context->GetCurrentVertexBuffer(),
        context->GetCurrentVaryingBuffer(),
        (const int*)context->GetTable(FarSubdivisionTables<OsdVertex>::V_ITa)->GetBuffer(),
        (const real*)context->GetTable(FarSubdivisionTables<OsdVertex>::V_W)->GetBuffer(),
        batch.GetVertexOffset(), batch.GetTableOffset(), batch.GetStart(), batch.GetEnd(), false);
}

void
OsdCpuComputeController::ApplyLoopVertexVerticesKernelA2(
    FarKernelBatch const &batch, void * clientdata) const {

    OsdCpuComputeContext * context =
        static_cast<OsdCpuComputeContext*>(clientdata);
    assert(context);

    OsdCpuComputeVertexA(
        context->GetVertexDescriptor(),
        context->GetCurrentVertexBuffer(),
        context->GetCurrentVaryingBuffer(),
        (const int*)context->GetTable(FarSubdivisionTables<OsdVertex>::V_ITa)->GetBuffer(),
        (const real*)context->GetTable(FarSubdivisionTables<OsdVertex>::V_W)->GetBuffer(),
        batch.GetVertexOffset(), batch.GetTableOffset(), batch.GetStart(), batch.GetEnd(), true);
}

void
OsdCpuComputeController::ApplyVertexEdits(
    FarKernelBatch const &batch, void * clientdata) const {

    OsdCpuComputeContext * context =
        static_cast<OsdCpuComputeContext*>(clientdata);
    assert(context);

    const OsdCpuHEditTable *edit = context->GetEditTable(batch.GetTableIndex());
    assert(edit);

    const OsdCpuTable * primvarIndices = edit->GetPrimvarIndices();
    const OsdCpuTable * editValues = edit->GetEditValues();

    if (edit->GetOperation() == FarVertexEdit::Add) {
        OsdCpuEditVertexAdd(context->GetVertexDescriptor(),
                            context->GetCurrentVertexBuffer(),
                            edit->GetPrimvarOffset(),
                            edit->GetPrimvarWidth(),
                            batch.GetVertexOffset(), 
                            batch.GetTableOffset(), 
                            batch.GetStart(), 
                            batch.GetEnd(),
                            static_cast<unsigned int*>(primvarIndices->GetBuffer()),
                            static_cast<real*>(editValues->GetBuffer()));
    } else if (edit->GetOperation() == FarVertexEdit::Set) {
        OsdCpuEditVertexSet(context->GetVertexDescriptor(),
                            context->GetCurrentVertexBuffer(),
                            edit->GetPrimvarOffset(),
                            edit->GetPrimvarWidth(),
                            batch.GetVertexOffset(), 
                            batch.GetTableOffset(), 
                            batch.GetStart(), 
                            batch.GetEnd(),
                            static_cast<unsigned int*>(primvarIndices->GetBuffer()),
                            static_cast<real*>(editValues->GetBuffer()));
    }
}

void
OsdCpuComputeController::Synchronize() {
}

}  // end namespace OPENSUBDIV_VERSION
}  // end namespace OpenSubdiv
