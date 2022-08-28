
#include "screens.h"

#include "core/app.h"
#include "core/log.h"
#include "math/vector.h"
#include "imgui.h"

#define UINT_TO_VOIDPTR(value) (void*)(intptr_t)value

namespace raytracing
{
    void MainMenuBarScreen::tick()
    {
        if (!ImGui::BeginMainMenuBar())
            return;
        
        ImGui::EndMainMenuBar();
    }

    ImageScreen::ImageScreen() : m_Texture(64, 64) {}

    void ImageScreen::tick()
    {
        if (!ImGui::Begin("Image"))
            return;

        // Get RealSize
        const uint32_t width = ImGui::GetWindowContentRegionMax().x - ImGui::GetWindowContentRegionMin().x;
        const uint32_t height = ImGui::GetWindowContentRegionMax().y - ImGui::GetWindowContentRegionMin().y;

        // Show Image stretched to RealSize
        const Texture& texture = App::get()->getRenderer().getTexture();
        ImGui::Image(UINT_TO_VOIDPTR(texture.get()), ImVec2(width, height), ImVec2(0, 1), ImVec2(1, 0));

        // Resize Image to RealSize
        App::get()->getRenderer().setImageSize(width, height);

        ImGui::End();
    }

    void StatsScreen::tick()
    {
        if (!ImGui::Begin("Stats"))
            return;

        const float lastUpdate = App::get()->getRenderer().getLastUpdate();
        ImGui::Text("Last Update: %.3f", lastUpdate);

        const float xMovement = cameraMovement("X");
        const float yMovement = cameraMovement("Y");
        const float zMovement = cameraMovement("Z");

        App::get()->getRenderer().moveCamera(Vector(xMovement, yMovement, zMovement));

        ImGui::End();
    }

    float StatsScreen::cameraMovement(const std::string& axesName)
    {
        ImGui::PushID(axesName.c_str());
        ImGui::Text("Camera Movements:");

        ImGui::Text(axesName.c_str());

        float value = 0.f;

        ImGui::SameLine();
        if (ImGui::Button("+"))
            value = 0.3f;

        ImGui::SameLine();
        if (ImGui::Button("-"))
            value = -0.3f;

        ImGui::PopID();
        return value;
    }
}