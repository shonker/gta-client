#include "../../../renderer/renderer.hpp"

#include "../libs/imgui_tricks.hpp"

void renderer::imgui::elements::functions::separator()
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size = ImGui::CalcItemSize({ 318, 1 }, 318, 1);

	const ImRect bb(pos, pos + size);
	ImGui::ItemSize(bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, 0))
		return;

	window->DrawList->AddLine(bb.Min, bb.Min + ImVec2(318, 0), ImColor(228, 228, 230, 7), 1);
}