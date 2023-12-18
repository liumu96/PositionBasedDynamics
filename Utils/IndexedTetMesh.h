#pragma once

#include <vector>
#include <array>
#include "Common/Common.h"

namespace Utilities
{
    class IndexedTetMesh
    {
    public:
        struct Edge
        {
            std::array<unsigned int, 2> m_vert;
        };

        struct Face
        {
            // edge indices
            std::array<unsigned int, 3> m_edges;
            // tet indices
            std::array<unsigned int, 2> m_tets;
        };

        struct Tet
        {
            std::array<unsigned int, 6> m_edges;
            std::array<unsigned int, 4> m_faces;
        };

    public:
        typedef std::vector<unsigned int> Tets;
        typedef std::vector<unsigned int> Faces;
        typedef std::vector<Tet> TetData;
        typedef std::vector<Face> FaceData;
        typedef std::vector<Edge> Edges;
        typedef std::vector<std::vector<unsigned int>> VerticesTets;
        typedef std::vector<std::vector<unsigned int>> VerticesFaces;
        typedef std::vector<std::vector<unsigned int>> VerticesEdges;

    protected:
        unsigned int m_numPoints;
        Tets m_tetIndices;
        Faces m_faceIndices;
        Edges m_edges;
        FaceData m_faces;
        TetData m_tets;
        VerticesTets m_verticesTets;
        VerticesFaces m_verticesFaces;
        VerticesEdges m_verticesEdges;

    public:
        IndexedTetMesh();
        ~IndexedTetMesh();

        void release();

        const Tets &getTets() const { return m_tetIndices; }
        Tets &getTets() { return m_tetIndices; }

        unsigned int numVertices() const { return m_numPoints; }
    };
}