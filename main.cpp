#include <iostream>
#include <visualization.h>

#include <Eigen/Dense>

#include <igl/readOBJ.h>

// simulation parameters
Eigen::VectorXd q;
Eigen::VectorXd v;

double mass = 1.0;
double stiffness = 100.0;
double dt = 1e-2;
int integrator_type = 0;

bool simulate(igl::opengl::glfw::Viewer &viewer)
{
    // take a time step
    auto force = [](Eigen::VectorXd &f, Eigen::VectorXd &q, Eigen::VectorXd &v) {

    };
    return false;
}

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        if (argv[1] == std::string("be"))
        {
            integrator_type = 1;
        }

        if (argv[1] == std::string("se"))
        {
            integrator_type = 2;
        }

        if (argv[1] == std::string("rk"))
        {
            integrator_type = 3;
        }
    }

    // Load data for animations
    Eigen::MatrixXd V_bunny;
    Eigen::MatrixXi F_bunny;

    // read model
    igl::readOBJ("../data/bunny.obj", V_bunny, F_bunny);

    // setup simulation variables
    q.resize(1);
    v.resize(1);

    v(0) = 0;
    q(0) = 1;

    // setup libigl viewer and activate
    Visualize::setup(q, v);
    Visualize::viewer().callback_post_draw = &simulate;
    Visualize::add_object_to_scene(V_bunny, F_bunny, Eigen::RowVector3d(244, 165, 230) / 255.);
    Visualize::viewer().launch();

    return 0;
}