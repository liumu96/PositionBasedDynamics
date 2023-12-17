#include "SimulationModel.h"

#include "Constraints.h"

using namespace PBD;
using namespace GenParam;

SimulationModel::SimulationModel()
{
    m_contactStiffnessRigidBody = 1.0;
    m_contactStiffnessParticleRigidBody = 100.0;

    m_clothSimulationMethod = 2;
    m_clothBendingMethod = 2;
    m_cloth_stiffness = static_cast<Real>(1.0);
    m_cloth_bendingStiffness = static_cast<Real>(0.01);
    m_cloth_xxStiffness = static_cast<Real>(1.0);
    m_cloth_yyStiffness = static_cast<Real>(1.0);
    m_cloth_xyStiffness = static_cast<Real>(1.0);
    m_cloth_xyPoissonRatio = static_cast<Real>(0.3);
    m_cloth_yxPoissonRatio = static_cast<Real>(0.3);
    m_cloth_normalizeShear = false;
    m_cloth_normalizeStretch = false;

    m_solidSimulationMethod = 2;
    m_solid_stiffness = static_cast<Real>(1.0);
    m_solid_poissonRatio = static_cast<Real>(0.3);
    m_solid_volumeStiffness = static_cast<Real>(1.0);
    m_solid_normalizeShear = false;
    m_solid_normalizeStretch = false;

    m_rod_stretchingStiffness = static_cast<Real>(1.0);
    m_rod_shearingStiffnessX = static_cast<Real>(1.0);
    m_rod_shearingStiffnessY = static_cast<Real>(1.0);
    m_rod_bendingStiffnessX = static_cast<Real>(0.5);
    m_rod_bendingStiffnessY = static_cast<Real>(0.5);
    m_rod_twistingStiffness = static_cast<Real>(0.5);

    m_groupsInitialized = false;

    m_rigidBodyContactConstraints.reserve(10000);
    m_particleRigidBodyContactConstraints.reserve(10000);
    m_particleSolidContactConstraints.reserve(10000);

    m_clothSimMethodChanged = nullptr;
    m_solidSimMethodChanged = nullptr;
}

SimulationModel::~SimulationModel(void)
{
    cleanup();
}

void SimulationModel::init()
{
    initParameters();
}

void SimulationModel::cleanup()
{
    // todo
}

void SimulationModel::initParameters()
{
    ParameterObject::initParameters();

    // todo
}

ParticleData &SimulationModel::getParticles()
{
    return m_particles;
}

void SimulationModel::addTriangleModel(
    const unsigned int nPoints,
    const unsigned int nFaces,
    Vector3r *points,
    unsigned int *indices,
    const TriangleModel::ParticleMesh::UVIndices &uvIndices,
    const TriangleModel::ParticleMesh::UVs &uvs)
{
    TriangleModel *triModel = new TriangleModel();
    m_triangleModels.push_back(triModel);

    unsigned int startIndex = m_particles.size();
    m_particles.reserve(startIndex + nPoints);

    for (unsigned int i = 0; i < nPoints; i++)
        m_particles.addVertex(points[i]);

    triModel->initMesh(nPoints, nFaces, startIndex, indices, uvIndices, uvs);

    // Update normals
    triModel->updateMeshNormals(m_particles);
}

void SimulationModel::addRegularTriangleModel(const int width, const int height,
                                              const Vector3r &translation,
                                              const Matrix3r &rotation,
                                              const Vector2r &scale)
{
    TriangleModel::ParticleMesh::UVs uvs;
    uvs.resize(width * height);

    const Real dy = scale[1] / (Real)(height - 1);
    const Real dx = scale[0] / (Real)(width - 1);

    std::vector<Vector3r> points;
    points.resize(width * height);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            const Real y = (Real)dy * i;
            const Real x = (Real)dx * j;
            points[i * width + j] = rotation * Vector3r(x, y, 0.0) + translation;

            uvs[i * width + j][0] = x / scale[0];
            uvs[i * width + j][1] = y / scale[1];
        }
    }
    const int nIndices = 6 * (height - 1) * (width - 1);

    TriangleModel::ParticleMesh::UVIndices uvIndices;
    uvIndices.resize(nIndices);

    std::vector<unsigned int> indices;
    indices.resize(nIndices);
    int index = 0;
    for (int i = 0; i < height - 1; i++)
    {
        for (int j = 0; j < width - 1; j++)
        {
            int helper = 0;
            if (i % 2 == j % 2)
                helper = 1;

            indices[index] = i * width + j;
            indices[index + 1] = i * width + j + 1;
            indices[index + 2] = (i + 1) * width + j + helper;

            uvIndices[index] = i * width + j;
            uvIndices[index + 1] = i * width + j + 1;
            uvIndices[index + 2] = (i + 1) * width + j + helper;
            index += 3;

            indices[index] = (i + 1) * width + j + 1;
            indices[index + 1] = (i + 1) * width + j;
            indices[index + 2] = i * width + j + 1 - helper;

            uvIndices[index] = (i + 1) * width + j + 1;
            uvIndices[index + 1] = (i + 1) * width + j;
            uvIndices[index + 2] = i * width + j + 1 - helper;
            index += 3;
        }
    }

    const unsigned int nPoints = height * width;
    const unsigned int nFaces = nIndices / 3;
    const auto modelIndex = m_triangleModels.size();
    addTriangleModel(nPoints, nFaces, points.data(), indices.data(), uvIndices, uvs);
    const auto offset = m_triangleModels[modelIndex]->getIndexOffset();

    ParticleData &pd = getParticles();
    for (unsigned int i = offset; i < offset + m_triangleModels[modelIndex]->getParticleMesh().numVertices(); i++)
        pd.setMass(i, 1.0);
}
