#include "visualization.h"

namespace Visualize
{

    igl::opengl::glfw::Viewer g_viewer;
    igl::opengl::glfw::imgui::ImGuiMenu menu;

    // meshes in the scene
    std::vector<std::pair<Eigen::MatrixXd, Eigen::MatrixXi>> g_geometry;
    std::vector<unsigned int> g_id; // id into ligibl for these meshes

    // pointers to q and qdot
    Eigen::VectorXd const *g_q;
    Eigen::VectorXd const *g_qdot;

    // cache for phase space data
    std::deque<std::pair<float, float>> g_state;
}

igl::opengl::glfw::Viewer &Visualize::viewer()
{
    return g_viewer;
}

bool Visualize::plot_phase_space(const char *label,
                                 ImVec2 q_bounds,
                                 ImVec2 q_dot_bounds,
                                 const Eigen::VectorXd &q,
                                 const Eigen::VectorXd &q_dot)
{
    using namespace ImGui;

    unsigned int cache_size = 10000;
    unsigned int num_lines = 5; // always odd number because I want lines to cross at 0,0

    ImGuiContext &g = *GImGui;
    const ImGuiStyle &style = g.Style;

    if (g_state.size() > cache_size)
    {
        g_state.pop_front();
    }

    // updating plotting cache

    return false;
}

void Visualize::setup(const Eigen::VectorXd &q,
                      const Eigen::VectorXd &qdot)
{
    g_q = &q;
    g_qdot = &qdot;

    // add new menu for phase space plotting

    // add content to the default menu window
}

void Visualize::add_object_to_scene(const Eigen::MatrixXd &V,
                                    const Eigen::MatrixXi &F,
                                    Eigen::RowVector3d color)
{
    // add mesh to libigl and store id for access later
    if (g_geometry.size() == 0)
    {
        g_id.push_back(0);
    }
    else
    {
        g_id.push_back(g_viewer.append_mesh());
    }

    g_viewer.data().set_mesh(V, F);
    g_viewer.data().set_colors(color);

    // add mesh to geometry vector
    g_geometry.push_back(std::make_pair(V, F));
}

void Visualize::rigid_transform_1d(unsigned int id, double x)
{
    // reset vertex positions
    for (unsigned int ii = 0; ii < g_geometry[id].first.rows(); ++ii)
    {
        g_viewer.data_list[g_id[id]].V(ii, 0) = g_geometry[id].first(ii, 0) + x;
    }
    // tell viewer to update
    g_viewer.data_list[g_id[id]].dirty |= igl::opengl::MeshGL::DIRTY_POSITION;
}

void Visualize::scale_x(unsigned int id, double x)
{
    // reset vertex positions
    for (unsigned int ii = 0; ii < g_geometry[id].first.rows(); ++ii)
    {
        g_viewer.data_list[g_id[id]].V(ii, 0) = x * g_geometry[id].first(ii, 0);
    }
    // tell viewer to update
    g_viewer.data_list[g_id[id]].dirty |= igl::opengl::MeshGL::DIRTY_POSITION;
}
