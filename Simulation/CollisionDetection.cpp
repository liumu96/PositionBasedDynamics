#include "CollisionDetection.h"
#include "Simulation/IDFactory.h"

using namespace PBD;

using namespace GenParam;

int CollisionDetection::CONTACT_TOLERANCE = -1;

int CollisionDetection::CollisionObjectWithoutGeometry::TYPE_ID = IDFactory::getId();

const unsigned int CollisionDetection::RigidBodyContactType = 0;
const unsigned int CollisionDetection::ParticleContactType = 1;
const unsigned int CollisionDetection::ParticleRigidBodyContactType = 2;
const unsigned int CollisionDetection::ParticleSolidContactType = 3;

const unsigned int CollisionDetection::CollisionObject::RigidBodyCollisionObjectType = 0;
const unsigned int CollisionDetection::CollisionObject::TriangleModelCollisionObjectType = 1;
const unsigned int CollisionDetection::CollisionObject::TetModelCollisionObjectType = 2;

CollisionDetection::CollisionDetection() : m_collisionObjects()
{
    m_collisionObjects.reserve(1000);
    m_contactCB = NULL;
    m_solidContactCB = NULL;
    m_tolerance = static_cast<Real>(0.01);
}

CollisionDetection::~CollisionDetection()
{
    cleanup();
}

void CollisionDetection::initParameters()
{
    ParameterObject::initParameters();

    CONTACT_TOLERANCE = createNumericParameter("contactTolerance", "Contact tolerance", &m_tolerance);
    setGroup(CONTACT_TOLERANCE, "Simulation|Contact");
    setDescription(CONTACT_TOLERANCE, "Tolerance of the collision detection");
    static_cast<NumericParameter<Real> *>(getParameter(CONTACT_TOLERANCE))->setMinValue(0.0);
}

void CollisionDetection::cleanup()
{
    for (unsigned int i = 0; i < m_collisionObjects.size(); i++)
        delete m_collisionObjects[i];
    m_collisionObjects.clear();
}

void CollisionDetection::setContactCallback(CollisionDetection::ContactCallbackFunction val, void *userData)
{
    m_contactCB = val;
    m_contactCBUserData = userData;
}

void CollisionDetection::setSolidContactCallback(CollisionDetection::SolidContactCallbackFunction val, void *userData)
{
    m_solidContactCB = val;
    m_solidContactCBUserData = userData;
}