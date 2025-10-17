#include "Debug.h"


Console::Console()
{

}

void Console::Init(ImGuiIO& io)
{

	this->consoleFont = io.Fonts->AddFontFromFileTTF("C:\\Users\\kedan\\AppData\\Local\\Microsoft\\Windows\\Fonts\\CascadiaMono.TTF", 15);
	this->file.open("log2.txt");
}

void Console::RenderConsole()
{
	//ImGui::SetNextWindowPos({ 200, 200 });
	ImGui::SetNextWindowSize({ 800, 600 });

	ImGui::PushFont(this->consoleFont);
	ImGui::Begin("Console");

	float height = ImGui::GetTextLineHeightWithSpacing();
	float availableHeight = ImGui::GetContentRegionAvail().y;

	int lineCount =  availableHeight / height;

	for (int i = lineCount - 1; i >= 0 ; i--)
	{
		ImGui::Text(this->lines[i].c_str());
	}

	ImGui::End();
	ImGui::PopFont();
}

void Console::Clear()
{
	this->lines->clear();
}

void Console::WriteVector(UnityEngine_Vector3_o vector)
{
	this->PushBackLine(std::to_string(vector.fields.x) + "|" + std::to_string(vector.fields.y) + "|" + std::to_string(vector.fields.z));
}

void Console::WriteVectorInt(UnityEngine_Vector3Int_o vector)
{
	this->PushBackLine(std::to_string(vector.fields.m_X) + "|" + std::to_string(vector.fields.m_Y) + "|" + std::to_string(vector.fields.m_Z));
}

void Console::Log(std::string label, int value)
{
	this->PushBackLine(label + ": " + std::to_string(value));
}

void Console::Log(std::string label, float value)
{
	this->PushBackLine(label + ": " + std::to_string(value));
}

void Console::Log(std::string label, double value)
{
	this->PushBackLine(label + ": " + std::to_string(value));
}

void Console::Log(std::string label, unsigned long long value)
{
	std::string s = std::format("{:x}", value);
	this->PushBackLine(label + ": 0x" + s);
}

void Console::WriteLine(std::string line)
{
	this->PushBackLine(line);
}

void Console::WriteLine(int line)
{
	this->PushBackLine(std::to_string(line));
}

void Console::WriteLine(float line)
{
	this->PushBackLine(std::to_string(line));
}

void Console::PushBackLine(std::string line)
{
	for (int i = MAX_LINE_COUNT - 2; i >= 0; i--)
	{
		this->lines[i + 1] = this->lines[i];
	}

	this->lines[0] = line;
}