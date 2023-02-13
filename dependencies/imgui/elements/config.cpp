#include "../../../renderer/renderer.hpp"

#include "../libs/imgui_tricks.hpp"

#include <map>

struct anim {
	float size;
	float hover;
};

int renderer::imgui::elements::functions::config_button(const char* label, const char* data, const char* author)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	const ImGuiID id = window->GetID(label);

	static std::map<ImGuiID, anim>* circle_anim = nullptr;
	if (!circle_anim)
	{
		circle_anim = new std::map<ImGuiID, anim>();
	}

	auto it_circle = circle_anim->find(id);
	if (it_circle == circle_anim->end())
	{
		circle_anim->insert({ id, {61.f, 0.f} });
		it_circle = circle_anim->find(id);
	}

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	ImVec2 pos = window->DC.CursorPos;
	ImVec2 size = ImGui::CalcItemSize({ 338.f, it_circle->second.size }, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	ImRect bb(pos, pos + size);
	//int res = ImGui::InvisibleButton(label, size) ? 1 : 0;

	ImGui::ItemSize(size);
	if (!ImGui::ItemAdd(bb, id))
		return 0;

	int res = 0;
	ImGui::PushClipRect(bb.Min, bb.Max, false);

	bool itemHovered = ImGui::IsItemHovered(ImGuiHoveredFlags_RectOnly);
	if (itemHovered)
	{
		if (it_circle->second.hover <= 1.f)
			it_circle->second.hover += 0.05f;
	}
	else
	{
		if (it_circle->second.hover >= 0.f)
			it_circle->second.hover -= 0.05f;
	}

	it_circle->second.size = ImTricks::Animations::FastFloatLerp(id, itemHovered, 61.f, 131.f, 0.2f);

	

	window->DrawList->AddRectFilled(bb.Min, bb.Max, ImColor(32, 39, 49, 125 + int(it_circle->second.hover * 125)), 5);
	window->DrawList->AddText(bb.Min + ImVec2(15, 13), ImColor(230, 230, 230), label);
	window->DrawList->AddText(bb.Min + ImVec2(15, 34), ImColor(160, 160, 160), "data: ");
	window->DrawList->AddText(bb.Min + ImVec2(15 + ImGui::CalcTextSize("data: ").x, 34), ImColor(230, 230, 230), data);


	window->DrawList->AddText(bb.Min + ImVec2(125, 34), ImColor(160, 160, 160), "description: ");
	window->DrawList->AddText(bb.Min + ImVec2(125 + ImGui::CalcTextSize("description: ").x, 34), ImColor(211, 243, 107), author);

	bool anybuttonhovered = false;

	if (it_circle->second.size > 65.f)
	{
		//Button("test", ImVec2(80, 20), ButtonFlags::BUTTON_GREEN);

		window->DrawList->AddLine(bb.Min + ImVec2(10, 65), bb.Min + ImVec2(328.f, 65), ImColor(45, 45, 49, int(it_circle->second.hover * 255)), 1);

		if (1)
		{
			const char* text = "LOAD";

			ImGuiID newid = window->GetID(text);
			ImRect newbb;
			newbb.Min = bb.Min + ImVec2(10, 75);
			newbb.Max = bb.Min + ImVec2(120, 120);


			if (!res)
			{
				bool hovered;
				if (ImGui::ButtonBehavior(newbb, newid, &hovered, nullptr))
					res = 1;
				if (hovered)
					anybuttonhovered = true;
			}

			window->DrawList->AddRectFilled(newbb.Min, newbb.Max, ImColor(127, 128, 246, int(it_circle->second.hover * 255)), 5);

			auto text_size = ImGui::CalcTextSize(text);
			window->DrawList->AddText(newbb.GetCenter() - text_size / 2.f, ImColor(245, 245, 245, int(it_circle->second.hover * 255)), text);
		}

		if (1)
		{
			const char* text = "DELETE";
			ImGuiID newid = window->GetID(text);

			ImRect newbb;
			newbb.Min = bb.Min + ImVec2(10, 75);
			newbb.Max = bb.Min + ImVec2(120, 120);
			newbb.TranslateX(125);

			if (!res)
			{
				bool hovered;
				if (ImGui::ButtonBehavior(newbb, newid, &hovered, nullptr))
					res = 2;
				if (hovered)
					anybuttonhovered = true;
			}

			window->DrawList->AddRectFilled(newbb.Min, newbb.Max, ImColor(127, 128, 246, int(it_circle->second.hover * 255)), 5);

			auto text_size = ImGui::CalcTextSize(text);
			window->DrawList->AddText(newbb.GetCenter() - text_size / 2.f, ImColor(245, 245, 245, int(it_circle->second.hover * 255)), text);
		}
	}

	if (anybuttonhovered)
		ImGui::SetMouseCursor(7);

	ImGui::PopClipRect();

	return res;
}
