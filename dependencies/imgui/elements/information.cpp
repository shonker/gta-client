#include "../../../renderer/renderer.hpp"

#include "../libs/imgui_tricks.hpp"

int DataTypeFormatString(char* buf, int buf_size, ImGuiDataType data_type, const void* p_data, const char* format)
{
	if (data_type == ImGuiDataType_S32 || data_type == ImGuiDataType_U32)
		return ImFormatString(buf, buf_size, format, *(const ImU32*)p_data);
	if (data_type == ImGuiDataType_S64 || data_type == ImGuiDataType_U64)
		return ImFormatString(buf, buf_size, format, *(const ImU64*)p_data);
	if (data_type == ImGuiDataType_Float)
		return ImFormatString(buf, buf_size, format, *(const float*)p_data);
	if (data_type == ImGuiDataType_Double)
		return ImFormatString(buf, buf_size, format, *(const double*)p_data);
	if (data_type == ImGuiDataType_S8)
		return ImFormatString(buf, buf_size, format, *(const ImS8*)p_data);
	if (data_type == ImGuiDataType_U8)
		return ImFormatString(buf, buf_size, format, *(const ImU8*)p_data);
	if (data_type == ImGuiDataType_S16)
		return ImFormatString(buf, buf_size, format, *(const ImS16*)p_data);
	if (data_type == ImGuiDataType_U16)
		return ImFormatString(buf, buf_size, format, *(const ImU16*)p_data);
	IM_ASSERT(0);
	return 0;
}

void renderer::imgui::elements::functions::information(const char* label, const char* desc, float p_data, const char* format)
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
	ImVec2 size = ImGui::CalcItemSize({ 318, 52 }, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, pos + size);
	ImGui::ItemSize(bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, 0);

	char value_buf[64] = { 0 };
	const char* value_buf_end = value_buf;
	bool bRenderData = format;
	if (bRenderData)
		value_buf_end = value_buf + ImFormatString(value_buf, IM_ARRAYSIZE(value_buf), format, p_data);

	window->DrawList->AddText(bb.Min + ImVec2(10, 12), ImColor(228, 228, 230), label, text_display_end);
	if (desc)
		window->DrawList->AddText(bb.Min + ImVec2(10, 31), ImColor(156, 167, 190, 125), desc);

	window->DrawList->AddText(NULL, 9, bb.Min + ImVec2(225, 27), ImColor(211, 211, 211, 211), (const char*)ICON_FA_RADAR);
	if (bRenderData)
		window->DrawList->AddText(bb.Min + ImVec2(245, 21), ImColor(211, 211, 211, 211), value_buf);
}

void renderer::imgui::elements::functions::information(const char* label, const char* desc, int p_data, const char* format)
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
	ImVec2 size = ImGui::CalcItemSize({ 318, 52 }, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, pos + size);
	ImGui::ItemSize(bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, 0);

	char value_buf[64] = { 0 };
	const char* value_buf_end = value_buf;
	bool bRenderData = format;
	if (bRenderData)
		value_buf_end = value_buf + ImFormatString(value_buf, IM_ARRAYSIZE(value_buf), format, p_data);

	window->DrawList->AddText(bb.Min + ImVec2(10, 12), ImColor(228, 228, 230), label, text_display_end);
	if (desc)
		window->DrawList->AddText(bb.Min + ImVec2(10, 31), ImColor(156, 167, 190, 125), desc);

	window->DrawList->AddText(NULL, 9, bb.Min + ImVec2(225, 27), ImColor(211, 211, 211, 211), (const char*)ICON_FA_RADAR);
	if (bRenderData)
		window->DrawList->AddText(bb.Min + ImVec2(245, 21), ImColor(211, 211, 211, 211), value_buf);
}

void renderer::imgui::elements::functions::information(const char* label, const char* desc, const char* p_data, const char* icon)
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
	ImVec2 size = ImGui::CalcItemSize({ 318, 52 }, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, pos + size);
	ImGui::ItemSize(bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, 0);

	window->DrawList->AddText(bb.Min + ImVec2(10, 12), ImColor(228, 228, 230), label, text_display_end);
	if (desc)
		window->DrawList->AddText(bb.Min + ImVec2(10, 31), ImColor(156, 167, 190, 125), desc);
	if (icon)
		window->DrawList->AddText(NULL, 9, bb.Min + ImVec2(225, 27), ImColor(211, 211, 211, 211), icon);
	if (p_data)
		window->DrawList->AddText(bb.Min + ImVec2(245, 21), ImColor(211, 211, 211, 211), p_data);
}