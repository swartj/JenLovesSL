#pragma once
#include <fstream>
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include <string>
#include <iomanip>
#include "il2cpp.h"

#define MAX_LINE_COUNT 100


class Console
{
public:
	Console();
	void Init(ImGuiIO& io);
	void RenderConsole();
	void Clear();
	//void Write(std::string text);
	void WriteLine(std::string line);
	void WriteLine(int line);
	void WriteLine(float line);

	void WriteVectorInt(UnityEngine_Vector3Int_o vector);
	void WriteVector(UnityEngine_Vector3_o vector);

	void Log(std::string label, int value);
	void Log(std::string label, float value);
	void Log(std::string label, double value);
	void Log(std::string label, unsigned long long value);

	std::ofstream file;

private:
	void PushBackLine(std::string line);
	
	ImFont* consoleFont;
	std::string currentLine;
	std::string lines[MAX_LINE_COUNT];
};
