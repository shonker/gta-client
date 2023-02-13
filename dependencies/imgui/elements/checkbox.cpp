#include "../../../renderer/renderer.hpp"

#include "../libs/imgui_tricks.hpp"

void renderer::imgui::elements::functions::checkbox(const char* label, const char* desc, bool& v)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return;

	int flags = 0;
	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const char* text_display_end = ImGui::FindRenderedTextEnd(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, text_display_end, true);

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size = ImGui::CalcItemSize({ 318, 57 }, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, pos + size);
	ImGui::ItemSize(bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, 0);

	if (hovered)
		ImGui::SetMouseCursor(7);

	if (pressed)
		v = !v;

	float Active = ImTricks::Animations::FastFloatLerp(id, v, 0, 18, 0.1f);

	window->DrawList->AddRectFilled(bb.Min + ImVec2(276, 25), bb.Min + ImVec2(276 + 32, 25 + 7), ImColor(32, 39, 49), 5);

	window->DrawList->AddCircleFilled(bb.Min + ImVec2(276 + 9 + Active, 25 + 3), 9, ImColor(28, 34, 42), 32);
	window->DrawList->AddCircleFilled(bb.Min + ImVec2(276 + 9 + Active, 25 + 3), 6, ImTricks::Animations::FastColorLerp(ImColor(211, 211, 211, 211), ImColor(211, 243, 107), Active / 18.f), 32);

	window->DrawList->AddText(bb.Min + ImVec2(10, 12), ImColor(228, 228, 230), label, text_display_end);
	window->DrawList->AddText(bb.Min + ImVec2(10, 31), ImColor(156, 167, 190, 125), desc);
}