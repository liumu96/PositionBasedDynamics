#pragma once

#include "Common/Common.h"

namespace Utilities
{
    class IndexedFaceMesh
    {
    public:
        struct Edge
        {
            std::array<unsigned int, 2> m_face;
            std::array<unsigned int, 2> m_vert;
        };

    public:
        typedef std::vector<unsigned int> Faces;
        typedef std::vector<Vector3r> FaceNormals;
        typedef std::vector<Vector3r> VertexNormals;
        typedef std::vector<std::vector<unsigned int>> FacesEdges;
        typedef std::vector<Edge> Edges;
        typedef std::vector<std::vector<unsigned int>> VerticesEdges;
        typedef std::vector<std::vector<unsigned int>> VerticesFaces;
        typedef std::vector<unsigned int> UVIndices;
        typedef std::vector<Vector2r> UVs;

    protected:
        unsigned int m_numPoints;
        Faces m_indices;
        Edges m_edges;
        FacesEdges m_facesEdges;
        bool m_closed;
        UVIndices m_uvIndices;
        UVs m_uvs;
        VerticesFaces m_verticesFaces;
        VerticesEdges m_verticesEdges;
        const unsigned int m_verticesPerFace = 3u;
        FaceNormals m_normals;
        VertexNormals m_vertexNormals;

    public:
        void release();

        void initMesh(const unsigned int nPoints, const unsigned int nEdges, const unsigned int nFaces);
        void addFace(const unsigned int *const indices);
        void addFace(const int *const indices);

        unsigned int numVertices() const { return m_numPoints; }
        unsigned int numFaces() const { return (unsigned int)m_indices.size() / m_verticesPerFace; }

        void copyUVs(const UVIndices &uvIndices, const UVs &uvs);
        void buildNeighbors();

        template <class PositionData>
        void updateNormals(const PositionData &pd, const unsigned int offset);

        template <class PositionData>
        void updateVertexNormals(const PositionData &pd);
    };

    template <class PositionData>
    void IndexedFaceMesh::updateNormals(const PositionData &pd, const unsigned int offset)
    {
        m_normals.resize(numFaces());

#pragma omp parallel default(shared)
        {
#pragma omp for schedule(static)
            for (int i = 0; i < (int)numFaces(); i++)
            {
                // Get first three points of face
                const Vector3r &a = pd.getPosition(m_indices[m_verticesPerFace * i] + offset);
                const Vector3r &b = pd.getPosition(m_indices[m_verticesPerFace * i + 1] + offset);
                const Vector3r &c = pd.getPosition(m_indices[m_verticesPerFace * i + 2] + offset);

                // Create normal
                Vector3r v1 = b - a;
                Vector3r v2 = c - a;

                m_normals[i] = v1.cross(v2);
                m_normals[i].normalize();
                // fix normals of degenerate triangles that can become zero vectors
                if (m_normals[i].squaredNorm() < 1e-6f)
                    m_normals[i] = Vector3r::UnitX();
            }
        }
    }

    template <class PositionData>
    void IndexedFaceMesh::updateVertexNormals(const PositionData &pd)
    {
        m_vertexNormals.resize(numVertices());

        for (unsigned int i = 0; i < numVertices(); i++)
        {
            m_vertexNormals[i].setZero();
        }

        for (unsigned int i = 0u; i < numFaces(); i++)
        {
            const Vector3r &n = m_normals[i];
            m_vertexNormals[m_indices[m_verticesPerFace * i]] += n;
            m_vertexNormals[m_indices[m_verticesPerFace * i + 1]] += n;
            m_vertexNormals[m_indices[m_verticesPerFace * i + 2]] += n;
        }

        for (unsigned int i = 0; i < numVertices(); i++)
        {
            m_vertexNormals[i].normalize();
        }
    }

}