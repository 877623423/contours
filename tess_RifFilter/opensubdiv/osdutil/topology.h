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
#ifndef OSDUTIL_TOPOLOGY_H
#define OSDUTIL_TOPOLOGY_H

#include "../version.h"

#include <vector>
#include <string>

namespace OpenSubdiv {
namespace OPENSUBDIV_VERSION {

// A value struct that holds annotations on a subdivision surface
// such as creases, boundaries, holes, corners, hierarchical edits, etc.
//
// For OpenSubdiv documentation on tags, see:
// See http://graphics.pixar.com/opensubdiv/docs/subdivision_surfaces.html#hierarchical-edits
//
class OsdUtilTagData {
public:
    enum TagType {
        // The strings in comments are the strings as specified by renderman
        
        CORNER,                            // "corner"        
        CREASE,                            // "crease"        
        CREASE_METHOD,                     // "creasemethod"        
        FACE_VARYING_INTERPOLATE_BOUNDARY, // "facevaryinginterpolateboundary"
        FACE_VARYING_PROPOGATE_CORNERS,    // "facevaryingpropagatecorners"
        HOLE,                              // "hole"
        INTERPOLATE_BOUNDARY,              // "interpolateboundary"
        SMOOTH_TRIANGLES,                  // "smoothtriangles"
        VERTEX_EDIT,                       // "vertexedit"
        EDGE_EDIT,                         // "edgeedit"
    };

    // returns false on error, parses rman spec strings to enum values
    static bool TagTypeFromString(TagType *t,
                                  const std::string &str);

    // Indices is the vertices of the mesh that will be tagged as corners.
    // If numSharpness == 1, the single sharpness value applies for all vertices
    // If numSharpness == numIndices, there is a per-vertex sharpness
    bool AddCorner(int *indices, int numIndices,
                   real *sharpness, int numSharpness);

    // Indices is a sequential series of mesh vertex indices that bound
    // the edges to be tagged with sharpness.  
    //
    // If numSharpness == 1, the single sharpness value applies for all edges
    // If numSharpness == numIndices, there is a per-edge sharpness that
    // will be interpolated along the crease
    bool AddCrease(int *indices, int numIndices,
                   real *sharpness, int numSharpness);
        
    // Either "normal" or "chaikin"
    bool AddCreaseMethod(const std::string &value);

    // 0 == OpenSubdiv::HbrMesh<T>::k_InterpolateBoundaryNone
    // 1 == OpenSubdiv::HbrMesh<T>::k_InterpolateBoundaryEdgeAndCorner
    // 2 == OpenSubdiv::HbrMesh<T>::k_InterpolateBoundaryEdgeOnly    
    bool AddInterpolateBoundary(int value);

    // Specify which faces on the coarse mesh should be "holes",
    // as if the limit surface for those faces is cut away from
    // from the rest of the surface.
    bool AddHole(int *indices, int numIndices);

    
    
    std::vector<TagType> tags;

    // For each tag, numArgs will have three integer values.
    // They are, in order, (#IntArgs, #FloatArgs, #StringArgs)
    std::vector<int> numArgs;
    
    std::vector<int> intArgs;
    std::vector<real> floatArgs;
    std::vector<std::string> stringArgs;
};

// A value struct intended to hold within it topology for the base mesh
// of a subdivision surface, and any annotation tags.
// It is used to initialize classes that create and operate on subdivs.
//
class OsdUtilSubdivTopology {
  public:

    OsdUtilSubdivTopology();
    ~OsdUtilSubdivTopology();    

    // XXX Would be great for these members to be private with accessors
    std::string name;
    int numVertices;
    int refinementLevel;
    std::vector<int> indices;
    std::vector<int> nverts;
    std::vector<std::string> vvNames;
    std::vector<std::string> fvNames;
    std::vector<real> fvData;
    OsdUtilTagData tagData;

    void AddFace(int numVertsInFace, int *verts) {
        nverts.push_back(numVertsInFace);
        for (int i=0; i<numVertsInFace; ++i)
            indices.push_back(verts[i]);
    }
    
    // Initialize using raw types. 
    //
    // This is useful for automated tests initializing with data like:
    // int nverts[] = { 4, 4, 4, 4, 4, 4};
    //
    bool Initialize(
        int numVertices,
        const int *nverts, int numFaces,
        const int *indices, int indicesLen,
        int levels,
        std::string *errorMessage);

    

    // checks indices etc to ensure that mesh isn't in a
    // broken state. Returns false on error, and will populate
    // errorMessage (if non-NULL) with a descriptive error message
    bool IsValid(std::string *errorMessage = NULL) const;

    // for debugging, print the contents of the topology to stdout
    void Print() const;

    bool ReadFromObjFile( char const * fname,
                          std::vector<real> *pointPositions,
                          std::string *errorMessage = NULL);
    
    bool ParseFromObjString( char const * shapestr, int axis,
                             std::vector<real> *pointPositions,
                             std::string *errorMessage = NULL);

    bool WriteObjFile(
        const char *filename, const real *positions,
        std::string *errorMessage = NULL);
    
};

}  // end namespace OPENSUBDIV_VERSION
using namespace OPENSUBDIV_VERSION;

}  // end namespace OpenSubdiv


#endif /* OSDUTIL_TOPOLOGY_H */
