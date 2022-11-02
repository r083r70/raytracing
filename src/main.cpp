
#include "core/app.h"
#include "core/layer.h"
#include "core/renderer.h"
#include "core/texture.h"

#include "imgui.h"

class MainScreen : public kettle::Layer
{
#define UINT_TO_VOIDPTR(value) (void*)(intptr_t)value

	virtual void tick() override
	{
		ImGui::Begin("Image");
		// Get RealSize
		const uint32_t width = ImGui::GetWindowContentRegionMax().x - ImGui::GetWindowContentRegionMin().x;
		const uint32_t height = ImGui::GetWindowContentRegionMax().y - ImGui::GetWindowContentRegionMin().y;

		// Show Image stretched to RealSize
		const raytracing::Texture& texture = raytracing::Renderer::get()->getTexture();
		ImGui::Image(UINT_TO_VOIDPTR(texture.get()), ImVec2(width, height), ImVec2(0, 1), ImVec2(1, 0));

		// Resize Image to RealSize
		raytracing::Renderer::get()->setImageSize(width, height);
		ImGui::End();

        ImGui::Begin("Stats");
        const float lastUpdate = raytracing::Renderer::get()->getLastUpdate();
        ImGui::Text("Last Update: %.3f", lastUpdate);
		ImGui::End();
	}
};

int main(void)
{
    kettle::App app{"Raytracer", 512, 512};
	app.pushLayer<raytracing::Renderer>();
	app.pushLayer<MainScreen>();
	app.run();
}