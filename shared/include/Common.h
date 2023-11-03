#pragma once

#include <Eigen/Dense>
#include <float.h>

#define MIN_PARALLEL_SIZE 64

#ifdef USE_DOUBLE
    typedef double Real;

#else
    typedef float Real;
#endif

using Vector3r = Eigen::Matrix<Real, 3, 1, Eigen::DontAlign>;
