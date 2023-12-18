#include "imguiParameters.h"

#include "FunctionParameter.h"

using namespace PBD;
using namespace std;
using namespace GenParam;

string imguiParameters::m_format = "%.5f";
Real imguiParameters::m_step = static_cast<Real>(0.001);
Real imguiParameters::m_faststep = static_cast<Real>(0.01);
int imguiParameters::m_istep = 1;
int imguiParameters::m_ifaststep = 10;
std::vector<std::function<void()>> imguiParameters::m_setFcts;
std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::vector<imguiParameters::imguiParameter *>>>>> imguiParameters::m_imguiParams;

void imguiParameters::createRealParameter(imguiParameters::imguiParameter *param, ImGuiInputTextFlags flags, const std::string &helpText)
{
    // Real parameter
    imguiParameters::imguiNumericParameter<Real> *rparam = dynamic_cast<imguiParameters::imguiNumericParameter<Real> *>(param);
    if ((rparam != nullptr) && (rparam->getFct != nullptr))
    {
        Real value = rparam->getFct();
        InputReal(rparam->label.c_str(), &value, m_step, m_faststep, m_format.c_str(), flags);

        if (ImGui::IsItemDeactivatedAfterEdit())
        {
            if (rparam->minValue != std::numeric_limits<Real>::min())
                value = std::max(rparam->minValue, value);
            if (rparam->maxValue != std::numeric_limits<Real>::max())
                value = std::min(rparam->maxValue, value);
            if (rparam->setFct)
                rparam->setFct(value);
        }
        if (ImGui::IsItemHovered())
        {
            const char *formatString = "Tooltip Text: %s";
            ImGui::SetTooltip(formatString, helpText.c_str());
        }
    }
}

void imguiParameters::createBoolParameter(imguiParameters::imguiParameter *param, ImGuiInputTextFlags flags, const std::string &helpText)
{
    // bool parameter
    imguiParameters::imguiBoolParameter *bparam = dynamic_cast<imguiParameters::imguiBoolParameter *>(param);
    if ((bparam != nullptr) && (bparam->getFct != nullptr))
    {
        bool value = bparam->getFct();
        ImGui::Checkbox(bparam->label.c_str(), &value);

        if (ImGui::IsItemDeactivatedAfterEdit())
        {
            if (!bparam->readOnly)
            {
                if (bparam->setFct)
                    bparam->setFct(value);
            }
        }
        if (ImGui::IsItemHovered())
        {
            const char *formatString = "Tooltip Text: %s";
            ImGui::SetTooltip(formatString, helpText.c_str());
        }
    }
}

void imguiParameters::createStringParameter(imguiParameters::imguiParameter *param, ImGuiInputTextFlags flags, const std::string &helpText)
{
    // string parameter
    imguiParameters::imguiStringParameter *sparam = dynamic_cast<imguiParameters::imguiStringParameter *>(param);
    if ((sparam != nullptr) && (sparam->getFct != nullptr))
    {
        std::string str = sparam->getFct();
        const unsigned int buf_size = 1000;
        char value[buf_size];
        strcpy(value, str.c_str());

        ImGui::InputText(sparam->label.c_str(), value, buf_size, flags);

        if (ImGui::IsItemDeactivatedAfterEdit())
        {
            if (sparam->setFct)
                sparam->setFct(value);
        }
        if (ImGui::IsItemHovered())
        {
            const char *formatString = "Tooltip Text: %s";
            ImGui::SetTooltip(formatString, helpText.c_str());
        }
    }
}

void imguiParameters::createVec3rParameter(imguiParameters::imguiParameter *param, ImGuiInputTextFlags flags, const std::string &helpText)
{
    // vec3 parameter
    imguiParameters::imguiVec3rParameter *vparam = dynamic_cast<imguiParameters::imguiVec3rParameter *>(param);
    if ((vparam != nullptr) && (vparam->getFct != nullptr))
    {
        Vector3r value = vparam->getFct();
        ImGui::InputScalarN(vparam->label.c_str(), ImGuiDataType_Real, value.data(), 3, NULL, NULL, m_format.c_str(), flags);

        if (ImGui::IsItemDeactivatedAfterEdit())
        {
            if (vparam->setFct)
                vparam->setFct(value);
        }
        if (ImGui::IsItemHovered())
        {
            const char *formatString = "Tooltip Text: %s";
            ImGui::SetTooltip(formatString, helpText.c_str());
        }
    }
}

void imguiParameters::createVec3fParameter(imguiParameters::imguiParameter *param, ImGuiInputTextFlags flags, const std::string &helpText)
{
    // vec3 parameter
    imguiParameters::imguiVec3fParameter *vparam = dynamic_cast<imguiParameters::imguiVec3fParameter *>(param);
    if ((vparam != nullptr) && (vparam->getFct != nullptr))
    {
        Eigen::Vector3f value = vparam->getFct();
        ImGui::InputFloat3(vparam->label.c_str(), value.data(), m_format.c_str(), flags);

        if (ImGui::IsItemDeactivatedAfterEdit())
        {
            if (vparam->setFct)
                vparam->setFct(value);
        }
        if (ImGui::IsItemHovered())
        {
            const char *formatString = "Tooltip Text: %s";
            ImGui::SetTooltip(formatString, helpText.c_str());
        }
    }
}

bool imguiParameters::createEnumParameter(imguiParameters::imguiParameter *param, ImGuiInputTextFlags flags, const std::string &helpText)
{
    // enum parameter
    imguiParameters::imguiEnumParameter *eparam = dynamic_cast<imguiParameters::imguiEnumParameter *>(param);
    if ((eparam != nullptr) && (eparam->getFct != nullptr))
    {
        int value = eparam->getFct();
        const char *item_current = eparam->items[value].c_str();
        if (ImGui::BeginCombo(eparam->label.c_str(), item_current))
        {
            for (int n = 0; n < eparam->items.size(); n++)
            {
                bool is_selected = (item_current == eparam->items[n]);
                if (ImGui::Selectable(eparam->items[n].c_str(), is_selected))
                {
                    item_current = eparam->items[n].c_str();
                    if (!eparam->readOnly)
                    {
                        // stop the creation of the GUI since the change of an enum value
                        // could cause a change of the GUI
                        // store the callback function and call it at the end of the GUI function
                        m_setFcts.push_back([eparam, n]()
                                            { eparam->setFct(n); });
                        ImGui::EndCombo();
                        return true;
                    }
                }
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndCombo();
        }
        if (ImGui::IsItemHovered())
        {
            const char *formatString = "Tooltip Text: %s";
            ImGui::SetTooltip(formatString, helpText.c_str());
        }
    }
    return false;
}

void imguiParameters::createFunctionParameter(imguiParameters::imguiParameter *param, ImGuiInputTextFlags flags, const std::string &helpText)
{
    // bool parameter
    imguiParameters::imguiFunctionParameter *fparam = dynamic_cast<imguiParameters::imguiFunctionParameter *>(param);
    if ((fparam != nullptr) && (fparam->function != nullptr))
    {
        if (ImGui::Button(fparam->label.c_str()))
        {
            if (fparam->function)
                fparam->function();
        }
        if (ImGui::IsItemHovered())
        {
            const char *formatString = "Tooltip Text: %s";
            ImGui::SetTooltip(formatString, helpText.c_str());
        }
    }
}

void imguiParameters::createSubgroupParameters(const std::vector<std::pair<std::string, std::vector<imguiParameter *>>> &params)
{
    for (auto subgroup_index = 0; subgroup_index < params.size(); subgroup_index++)
    {
        auto subgroup = params[subgroup_index];
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{1.0f, 1.0f, 0.5f, 1.0f});
        if ((subgroup.first == "") || (ImGui::TreeNodeEx(subgroup.first.c_str(), ImGuiTreeNodeFlags_DefaultOpen)))
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{1.0f, 1.0f, 1.0f, 1.0f});
            for (int i = 0; i < subgroup.second.size(); i++)
            {
                imguiParameters::imguiParameter *param = subgroup.second[i];
                std::string helpText = param->description;
                if (param->readOnly)
                    helpText += " (read-only)";
                else if ((param->name != "") && (dynamic_cast<imguiParameters::imguiFunctionParameter *>(param) == nullptr)) // no key help text for function parameters
                    helpText += "\n\nkey in scene file:\n" + param->name;

                ImGuiInputTextFlags flags = 0;
                if (param->readOnly)
                {
                    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4{0.3f, 0.3f, 0.3f, 1.0f});
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.3f, 0.3f, 0.3f, 1.0f});
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{1.0f, 1.0f, 1.0f, 1.0f});
                    flags = ImGuiInputTextFlags_ReadOnly;
                }

                createRealParameter(param, flags, helpText);
                createNumericParameter<unsigned int>(param, flags, helpText);
                createNumericParameter<unsigned short>(param, flags, helpText);
                createNumericParameter<unsigned char>(param, flags, helpText);
                createNumericParameter<int>(param, flags, helpText);
                createNumericParameter<short>(param, flags, helpText);
                createNumericParameter<char>(param, flags, helpText);
                createBoolParameter(param, flags, helpText);
                createStringParameter(param, flags, helpText);
                createVec3rParameter(param, flags, helpText);
                createVec3fParameter(param, flags, helpText);
                createFunctionParameter(param, flags, helpText);
                if (createEnumParameter(param, flags, helpText))
                {
                    // stop the creation of the GUI since the change of an enum value
                    // could cause a change of the GUI
                    if (param->readOnly)
                        ImGui::PopStyleColor(3);
                    ImGui::PopStyleColor(1);
                    if (subgroup.first != "")
                        ImGui::TreePop();
                    ImGui::PopStyleColor(1);
                    return;
                }

                if (param->readOnly)
                    ImGui::PopStyleColor(3);
            }

            ImGui::PopStyleColor(1);
            if (subgroup.first != "")
                ImGui::TreePop();
            ImGui::Separator();
        }
        ImGui::PopStyleColor(1);
    }
}

void imguiParameters::createParameterGUI()
{
    // always show "General"
    for (auto group_index = 0; group_index < m_imguiParams.size(); group_index++)
    {
        auto &group = m_imguiParams[group_index];
        if (group.first == "General")
        {
            createSubgroupParameters(group.second);
        }
    }

    ImGui::Dummy(ImVec2(0, 20));

    ImGui::PushStyleColor(ImGuiCol_Tab, ImVec4{0.3f, 0.3f, 0.3f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_TabHovered, ImVec4{0.5f, 0.5f, 0.5f, 1.0f});
    ImGui::PushStyleColor(ImGuiCol_TabActive, ImVec4{0.0f, 0.3f, 0.6f, 1.0f});
    if (ImGui::BeginTabBar("TabBar", ImGuiTabBarFlags_None))
    {
        for (auto group_index = 0; group_index < m_imguiParams.size(); group_index++)
        {
            auto group = m_imguiParams[group_index];
            if (group.first == "General")
                continue;

            if (ImGui::BeginTabItem(group.first.c_str()))
            {
                ImGui::Dummy(ImVec2(0, 5));
                createSubgroupParameters(group.second);
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
    }
    ImGui::PopStyleColor(3);

    // deferred call of callback functions
    for (size_t i = 0; i < m_setFcts.size(); i++)
        m_setFcts[i]();
    m_setFcts.clear();
}