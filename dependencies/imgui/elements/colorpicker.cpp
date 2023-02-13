#include "../../../renderer/renderer.hpp"

#include "../libs/imgui_tricks.hpp"

#include <map>

bool DrawCircleClr(const ImRect& bb, float xoffset, ImColor clr, bool selected)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	window->DrawList->AddCircleFilled(bb.Min + ImVec2(19 + xoffset, 9), 7, clr, 32);

	if (selected)
		window->DrawList->AddCircle(bb.Min + ImVec2(19 + xoffset, 9), 9, ImColor(211, 211, 211), 32);

	bool bPressed = false;
	if (ImGui::IsMouseHoveringRect(bb.Min + ImVec2(10 + xoffset, 0), bb.Min + ImVec2(28 + xoffset, 18)) && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
		bPressed = true;
	}

	return bPressed;
}

void renderer::imgui::elements::functions::color_picker(const char* identifier, float* col)
{
	return color_picker(identifier, (ImColor*)col);
}

void renderer::imgui::elements::functions::color_picker(const char* identifier, ImColor* col)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return;
	ImGui::PushID(identifier);

	int flags = 0;
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(identifier);
	

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size = ImGui::CalcItemSize({ 318, 18 }, 318, 18);

	const ImRect bb(pos, pos + size);

	ImGui::ItemSize(bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
	{
		ImGui::PopID();
		return;
	}

	ImColor clrs[] = {
		ImColor(176, 75, 81),
		ImColor(127, 128, 246),
		ImColor(211, 243, 107),
		ImColor(255, 199, 97),
		ImColor(47, 219, 188),
		ImColor(47, 29, 188),
		ImColor(47, 219, 88),
	};

	for (unsigned i = 0; i < _ARRAYSIZE(clrs); ++i)
	{
		if (DrawCircleClr(bb, 20.f * i, clrs[i], clrs[i] == *col))
			*col = clrs[i];
	}
	
	ImGui::SetNextWindowSize({ 245.f,  200.f });
	if (ImGui::BeginPopup("popup", ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar))
	{
		ImGui::SetCursorPos({ 10,10 });
		{

			ImGui::ColorPicker4("##coloredit", (float*)col, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview);
		}
		ImGui::EndPopup();
	}

	ImGui::RenderColorRectWithAlphaCheckerboard(window->DrawList, bb.Max - ImVec2(28, 18), bb.Max - ImVec2(12, 2), *col, 3.5f, ImVec2(0, 0), 18);
	window->DrawList->AddText(bb.Max - ImVec2(32 + ImGui::CalcTextSize("Custom").x, 18), ImColor(211, 211, 211), "Custom");

	
	if (ImGui::IsMouseHoveringRect(bb.Max - ImVec2(32 + ImGui::CalcTextSize("Custom").x, 18), bb.Max - ImVec2(12, 2)) && ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
		ImGui::OpenPopup("popup");
	}

	ImGui::PopID();
}
