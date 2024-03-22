#ifndef App_Base_H
#define App_Base_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
// #include <implot.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>

#include "../../../Backend/Backend.cpp"

void ErrorCallback(int error, const char *description);
// #include "app_base.hpp"

void ErrorCallback(int error, const char *description)
{
  fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

template <typename Derived> class App_Base
{
public:
  App_Base()
  {
    glfwSetErrorCallback(ErrorCallback);

    if (!glfwInit())
      std::exit(1);

    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create window with graphics context
    window = glfwCreateWindow(1600, 900, "LCHATTER", nullptr, nullptr);
    if (window == NULL)
      std::exit(1);

    // glfwSetWindowSize(window, 1920, 1080);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Add window based callbacks to the underlying app
    glfwSetMouseButtonCallback(window, &Derived::MouseButtonCallback);
    glfwSetCursorPosCallback(window, &Derived::CursorPosCallback);
    glfwSetKeyCallback(window, &Derived::KeyCallback);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // ImPlot::CreateContext();

    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform
    // Windows
    // io.ConfigViewportsNoAutoMerge = true;
    // io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGuiStyle &style = ImGui::GetStyle();
    // ImVec4 *colors = style.Colors;

    // SetTheme(colors, "dracula");
    // SetTheme(colors, "neon");
    // SetTheme(colors, "monokai");
    // SetTheme(colors, "cyberpunk");
    // SetTheme(colors, "node");
    // SetTheme(colors, "highcontrast");

    style.WindowPadding = ImVec2(10.0f, 10.0f);
    style.FramePadding = ImVec2(6.0f, 4.0f);
    style.CellPadding = ImVec2(8.0f, 8.0f);
    style.ItemSpacing = ImVec2(8.0f, 8.0f);
    style.ItemInnerSpacing = ImVec2(8.0f, 8.0f);
    style.TouchExtraPadding = ImVec2(0.0f, 0.0f);
    style.IndentSpacing = 20;
    style.ScrollbarSize = 12;
    style.GrabMinSize = 8;
    style.WindowBorderSize = 0;
    style.ChildBorderSize = 0;
    style.PopupBorderSize = 0;
    style.FrameBorderSize = 0;
    style.TabBorderSize = 0;
    style.WindowRounding = 5;
    style.ChildRounding = 3;
    style.FrameRounding = 3;
    style.PopupRounding = 3;
    style.ScrollbarRounding = 6;
    style.GrabRounding = 3;
    style.LogSliderDeadzone = 4;
    style.TabRounding = 3;

    // final scaling
    style.ScaleAllSizes(2.0f);

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Add custom fonts
    // ImGuiIO& io = ImGui::GetIO();
    // io.Fonts->AddFontFromFileTTF("../../../imgui/misc/fonts/Roboto-Medium.ttf",
    // 18.0f);
  }

  virtual ~App_Base()
  {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    // ImPlot::DestroyContext();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
  }

  void SetTheme(ImVec4 *colors, std::string themeName)
  {
    if (themeName == "dracula")
    {

      colors[ImGuiCol_Text] = ImColor(248, 248, 242);
      colors[ImGuiCol_TextDisabled] = ImColor(116, 113, 94);
      colors[ImGuiCol_WindowBg] = ImColor(40, 42, 54);
      colors[ImGuiCol_ChildBg] = ImColor(40, 42, 54);
      colors[ImGuiCol_PopupBg] = ImColor(40, 42, 54);
      colors[ImGuiCol_Border] = ImColor(68, 71, 90);
      colors[ImGuiCol_BorderShadow] = ImColor(0, 0, 0);
      colors[ImGuiCol_FrameBg] = ImColor(68, 71, 90);
      colors[ImGuiCol_FrameBgHovered] = ImColor(98, 114, 164);
      colors[ImGuiCol_FrameBgActive] = ImColor(189, 147, 249);
      colors[ImGuiCol_TitleBg] = ImColor(68, 71, 90);
      colors[ImGuiCol_TitleBgActive] = ImColor(98, 114, 164);
      colors[ImGuiCol_TitleBgCollapsed] = ImColor(68, 71, 90);
      colors[ImGuiCol_MenuBarBg] = ImColor(68, 71, 90);
      colors[ImGuiCol_ScrollbarBg] = ImColor(68, 71, 90);
      colors[ImGuiCol_ScrollbarGrab] = ImColor(98, 114, 164);
      colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(139, 233, 253);
      colors[ImGuiCol_ScrollbarGrabActive] = ImColor(189, 147, 249);
      colors[ImGuiCol_CheckMark] = ImColor(189, 147, 249);
      colors[ImGuiCol_SliderGrab] = ImColor(98, 114, 164);
      colors[ImGuiCol_SliderGrabActive] = ImColor(139, 233, 253);
      colors[ImGuiCol_Button] = ImColor(68, 71, 90);
      colors[ImGuiCol_ButtonHovered] = ImColor(98, 114, 164);
      colors[ImGuiCol_ButtonActive] = ImColor(189, 147, 249);
      colors[ImGuiCol_Header] = ImColor(98, 114, 164);
      colors[ImGuiCol_HeaderHovered] = ImColor(139, 233, 253);
      colors[ImGuiCol_HeaderActive] = ImColor(189, 147, 249);
      colors[ImGuiCol_Separator] = ImColor(68, 71, 90);
      colors[ImGuiCol_SeparatorHovered] = ImColor(98, 114, 164);
      colors[ImGuiCol_SeparatorActive] = ImColor(189, 147, 249);
      colors[ImGuiCol_ResizeGrip] = ImColor(68, 71, 90);
      colors[ImGuiCol_ResizeGripHovered] = ImColor(98, 114, 164);
      colors[ImGuiCol_ResizeGripActive] = ImColor(189, 147, 249);
      colors[ImGuiCol_Tab] = ImColor(68, 71, 90);
      colors[ImGuiCol_TabHovered] = ImColor(98, 114, 164);
      colors[ImGuiCol_TabActive] = ImColor(189, 147, 249);
      colors[ImGuiCol_TabUnfocused] = ImColor(68, 71, 90);
      colors[ImGuiCol_TabUnfocusedActive] = ImColor(98, 114, 164);
      colors[ImGuiCol_PlotLines] = ImColor(255, 121, 198);
      colors[ImGuiCol_PlotLinesHovered] = ImColor(255, 121, 198);
      colors[ImGuiCol_PlotHistogram] = ImColor(255, 121, 198);
      colors[ImGuiCol_PlotHistogramHovered] = ImColor(255, 121, 198);
      colors[ImGuiCol_TableHeaderBg] = ImColor(68, 71, 90);
      colors[ImGuiCol_TableBorderStrong] = ImColor(68, 71, 90);
      colors[ImGuiCol_TableBorderLight] = ImColor(98, 114, 164);
      colors[ImGuiCol_TableRowBg] = ImColor(68, 71, 90);
      colors[ImGuiCol_TableRowBgAlt] = ImColor(40, 42, 54);
      colors[ImGuiCol_TextSelectedBg] = ImColor(139, 233, 253);
      colors[ImGuiCol_DragDropTarget] = ImColor(139, 233, 253);
      colors[ImGuiCol_NavHighlight] = ImColor(189, 147, 249);
      colors[ImGuiCol_NavWindowingHighlight] = ImColor(189, 147, 249);
      colors[ImGuiCol_NavWindowingDimBg] = ImColor(189, 147, 249);
      colors[ImGuiCol_ModalWindowDimBg] = ImColor(68, 71, 90);
    }
    else if (themeName == "neon")
    {
      colors[ImGuiCol_Text] = ImColor(173, 255, 47);
      colors[ImGuiCol_TextDisabled] = ImColor(100, 100, 100);
      colors[ImGuiCol_WindowBg] = ImColor(34, 34, 34);
      colors[ImGuiCol_ChildBg] = ImColor(0, 0, 0);
      colors[ImGuiCol_PopupBg] = ImColor(0, 255, 255);
      colors[ImGuiCol_Border] = ImColor(0, 255, 255);
      colors[ImGuiCol_BorderShadow] = ImColor(0, 0, 0);
      colors[ImGuiCol_FrameBg] = ImColor(0, 0, 255);
      colors[ImGuiCol_FrameBgHovered] = ImColor(0, 255, 255);
      colors[ImGuiCol_FrameBgActive] = ImColor(30, 144, 255);
      colors[ImGuiCol_TitleBg] = ImColor(0, 0, 0);
      colors[ImGuiCol_TitleBgActive] = ImColor(0, 0, 0);
      colors[ImGuiCol_TitleBgCollapsed] = ImColor(0, 0, 0);
      colors[ImGuiCol_MenuBarBg] = ImColor(34, 34, 34);
      colors[ImGuiCol_ScrollbarBg] = ImColor(0, 0, 0);
      colors[ImGuiCol_ScrollbarGrab] = ImColor(255, 69, 0);
      colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(255, 165, 0);
      colors[ImGuiCol_ScrollbarGrabActive] = ImColor(255, 215, 0);
      colors[ImGuiCol_CheckMark] = ImColor(255, 215, 0);
      colors[ImGuiCol_SliderGrab] = ImColor(255, 69, 0);
      colors[ImGuiCol_SliderGrabActive] = ImColor(255, 215, 0);
      colors[ImGuiCol_Button] = ImColor(255, 69, 0);
      colors[ImGuiCol_ButtonHovered] = ImColor(255, 140, 0);
      colors[ImGuiCol_ButtonActive] = ImColor(255, 165, 0);
      colors[ImGuiCol_Header] = ImColor(0, 0, 0);
      colors[ImGuiCol_HeaderHovered] = ImColor(0, 0, 0);
      colors[ImGuiCol_HeaderActive] = ImColor(30, 144, 255);
      colors[ImGuiCol_Separator] = ImColor(128, 0, 128);
      colors[ImGuiCol_SeparatorHovered] = ImColor(147, 112, 219);
      colors[ImGuiCol_SeparatorActive] = ImColor(138, 43, 226);
      colors[ImGuiCol_ResizeGrip] = ImColor(128, 0, 128);
      colors[ImGuiCol_ResizeGripHovered] = ImColor(147, 112, 219);
      colors[ImGuiCol_ResizeGripActive] = ImColor(138, 43, 226);
      colors[ImGuiCol_Tab] = ImColor(0, 0, 0);
      colors[ImGuiCol_TabHovered] = ImColor(255, 140, 0);
      colors[ImGuiCol_TabActive] = ImColor(255, 69, 0);
      colors[ImGuiCol_TabUnfocused] = ImColor(0, 0, 0);
      colors[ImGuiCol_TabUnfocusedActive] = ImColor(34, 34, 34);
      colors[ImGuiCol_PlotLines] = ImColor(255, 0, 255);
      colors[ImGuiCol_PlotLinesHovered] = ImColor(255, 0, 255);
      colors[ImGuiCol_PlotHistogram] = ImColor(255, 0, 255);
      colors[ImGuiCol_PlotHistogramHovered] = ImColor(255, 0, 255);
      colors[ImGuiCol_TableHeaderBg] = ImColor(0, 0, 0);
      colors[ImGuiCol_TableBorderStrong] = ImColor(0, 0, 0);
      colors[ImGuiCol_TableBorderLight] = ImColor(128, 0, 128);
      colors[ImGuiCol_TableRowBg] = ImColor(0, 0, 0);
      colors[ImGuiCol_TableRowBgAlt] = ImColor(255, 255, 255);
      colors[ImGuiCol_TextSelectedBg] = ImColor(30, 144, 255);
      colors[ImGuiCol_DragDropTarget] = ImColor(255, 215, 0);
      colors[ImGuiCol_NavHighlight] = ImColor(255, 0, 255);
      colors[ImGuiCol_NavWindowingHighlight] = ImColor(255, 0, 255);
      colors[ImGuiCol_NavWindowingDimBg] = ImColor(255, 0, 255);
      colors[ImGuiCol_ModalWindowDimBg] = ImColor(255, 0, 255);
    }
    else if (themeName == "monokai")
    {
      colors[ImGuiCol_Text] = ImColor(248, 248, 242);
      colors[ImGuiCol_TextDisabled] = ImColor(117, 113, 94);
      colors[ImGuiCol_WindowBg] = ImColor(39, 40, 34);
      colors[ImGuiCol_ChildBg] = ImColor(39, 40, 34);
      colors[ImGuiCol_PopupBg] = ImColor(39, 40, 34);
      colors[ImGuiCol_Border] = ImColor(92, 90, 83);
      colors[ImGuiCol_BorderShadow] = ImColor(0, 0, 0);
      colors[ImGuiCol_FrameBg] = ImColor(49, 50, 44);
      colors[ImGuiCol_FrameBgHovered] = ImColor(59, 60, 54);
      colors[ImGuiCol_FrameBgActive] = ImColor(69, 70, 64);
      colors[ImGuiCol_TitleBg] = ImColor(39, 40, 34);
      colors[ImGuiCol_TitleBgActive] = ImColor(49, 50, 44);
      colors[ImGuiCol_TitleBgCollapsed] = ImColor(39, 40, 34);
      colors[ImGuiCol_MenuBarBg] = ImColor(39, 40, 34);
      colors[ImGuiCol_ScrollbarBg] = ImColor(39, 40, 34);
      colors[ImGuiCol_ScrollbarGrab] = ImColor(94, 91, 82);
      colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(108, 105, 94);
      colors[ImGuiCol_ScrollbarGrabActive] = ImColor(125, 121, 110);
      colors[ImGuiCol_CheckMark] = ImColor(248, 248, 242);
      colors[ImGuiCol_SliderGrab] = ImColor(94, 91, 82);
      colors[ImGuiCol_SliderGrabActive] = ImColor(125, 121, 110);
      colors[ImGuiCol_Button] = ImColor(59, 60, 54);
      colors[ImGuiCol_ButtonHovered] = ImColor(69, 70, 64);
      colors[ImGuiCol_ButtonActive] = ImColor(79, 80, 74);
      colors[ImGuiCol_Header] = ImColor(59, 60, 54);
      colors[ImGuiCol_HeaderHovered] = ImColor(69, 70, 64);
      colors[ImGuiCol_HeaderActive] = ImColor(79, 80, 74);
      colors[ImGuiCol_Separator] = ImColor(92, 90, 83);
      colors[ImGuiCol_SeparatorHovered] = ImColor(108, 105, 94);
      colors[ImGuiCol_SeparatorActive] = ImColor(125, 121, 110);
      colors[ImGuiCol_ResizeGrip] = ImColor(92, 90, 83);
      colors[ImGuiCol_ResizeGripHovered] = ImColor(108, 105, 94);
      colors[ImGuiCol_ResizeGripActive] = ImColor(125, 121, 110);
      colors[ImGuiCol_Tab] = ImColor(39, 40, 34);
      colors[ImGuiCol_TabHovered] = ImColor(49, 50, 44);
      colors[ImGuiCol_TabActive] = ImColor(59, 60, 54);
      colors[ImGuiCol_TabUnfocused] = ImColor(39, 40, 34);
      colors[ImGuiCol_TabUnfocusedActive] = ImColor(49, 50, 44);
      colors[ImGuiCol_PlotLines] = ImColor(248, 248, 242);
      colors[ImGuiCol_PlotLinesHovered] = ImColor(248, 248, 242);
      colors[ImGuiCol_PlotHistogram] = ImColor(248, 248, 242);
      colors[ImGuiCol_PlotHistogramHovered] = ImColor(248, 248, 242);
      colors[ImGuiCol_TableHeaderBg] = ImColor(39, 40, 34);
      colors[ImGuiCol_TableBorderStrong] = ImColor(92, 90, 83);
      colors[ImGuiCol_TableBorderLight] = ImColor(49, 50, 44);
      colors[ImGuiCol_TableRowBg] = ImColor(39, 40, 34);
      colors[ImGuiCol_TableRowBgAlt] = ImColor(59, 60, 54);
      colors[ImGuiCol_TextSelectedBg] = ImColor(108, 105, 94);
      colors[ImGuiCol_DragDropTarget] = ImColor(108, 105, 94);
      colors[ImGuiCol_NavHighlight] = ImColor(93, 144, 251);
      colors[ImGuiCol_NavWindowingHighlight] = ImColor(93, 144, 251);
      colors[ImGuiCol_NavWindowingDimBg] = ImColor(93, 144, 251);
      colors[ImGuiCol_ModalWindowDimBg] = ImColor(39, 40, 34);
    }
    else if (themeName == "cyberpunk")
    {
      colors[ImGuiCol_Text] = ImColor(139, 233, 253);
      colors[ImGuiCol_TextDisabled] = ImColor(100, 100, 100);
      colors[ImGuiCol_WindowBg] = ImColor(0, 0, 0);
      colors[ImGuiCol_ChildBg] = ImColor(16, 16, 16);
      colors[ImGuiCol_PopupBg] = ImColor(16, 16, 16);
      colors[ImGuiCol_Border] = ImColor(98, 114, 164);
      colors[ImGuiCol_BorderShadow] = ImColor(0, 0, 0);
      colors[ImGuiCol_FrameBg] = ImColor(16, 16, 16);
      colors[ImGuiCol_FrameBgHovered] = ImColor(98, 114, 164);
      colors[ImGuiCol_FrameBgActive] = ImColor(189, 147, 249);
      colors[ImGuiCol_TitleBg] = ImColor(0, 0, 0);
      colors[ImGuiCol_TitleBgActive] = ImColor(16, 16, 16);
      colors[ImGuiCol_TitleBgCollapsed] = ImColor(0, 0, 0);
      colors[ImGuiCol_MenuBarBg] = ImColor(16, 16, 16);
      colors[ImGuiCol_ScrollbarBg] = ImColor(16, 16, 16);
      colors[ImGuiCol_ScrollbarGrab] = ImColor(139, 233, 253);
      colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(189, 147, 249);
      colors[ImGuiCol_ScrollbarGrabActive] = ImColor(98, 114, 164);
      colors[ImGuiCol_CheckMark] = ImColor(139, 233, 253);
      colors[ImGuiCol_SliderGrab] = ImColor(139, 233, 253);
      colors[ImGuiCol_SliderGrabActive] = ImColor(189, 147, 249);
      colors[ImGuiCol_Button] = ImColor(16, 16, 16);
      colors[ImGuiCol_ButtonHovered] = ImColor(98, 114, 164);
      colors[ImGuiCol_ButtonActive] = ImColor(189, 147, 249);
      colors[ImGuiCol_Header] = ImColor(98, 114, 164);
      colors[ImGuiCol_HeaderHovered] = ImColor(139, 233, 253);
      colors[ImGuiCol_HeaderActive] = ImColor(189, 147, 249);
      colors[ImGuiCol_Separator] = ImColor(68, 71, 90);
      colors[ImGuiCol_SeparatorHovered] = ImColor(98, 114, 164);
      colors[ImGuiCol_SeparatorActive] = ImColor(189, 147, 249);
      colors[ImGuiCol_ResizeGrip] = ImColor(68, 71, 90);
      colors[ImGuiCol_ResizeGripHovered] = ImColor(98, 114, 164);
      colors[ImGuiCol_ResizeGripActive] = ImColor(189, 147, 249);
      colors[ImGuiCol_Tab] = ImColor(16, 16, 16);
      colors[ImGuiCol_TabHovered] = ImColor(98, 114, 164);
      colors[ImGuiCol_TabActive] = ImColor(189, 147, 249);
      colors[ImGuiCol_TabUnfocused] = ImColor(16, 16, 16);
      colors[ImGuiCol_TabUnfocusedActive] = ImColor(98, 114, 164);
      colors[ImGuiCol_PlotLines] = ImColor(255, 121, 198);
      colors[ImGuiCol_PlotLinesHovered] = ImColor(255, 121, 198);
      colors[ImGuiCol_PlotHistogram] = ImColor(255, 121, 198);
      colors[ImGuiCol_PlotHistogramHovered] = ImColor(255, 121, 198);
      colors[ImGuiCol_TableHeaderBg] = ImColor(16, 16, 16);
      colors[ImGuiCol_TableBorderStrong] = ImColor(68, 71, 90);
      colors[ImGuiCol_TableBorderLight] = ImColor(98, 114, 164);
      colors[ImGuiCol_TableRowBg] = ImColor(16, 16, 16);
      colors[ImGuiCol_TableRowBgAlt] = ImColor(0, 0, 0);
      colors[ImGuiCol_TextSelectedBg] = ImColor(98, 114, 164);
      colors[ImGuiCol_DragDropTarget] = ImColor(139, 233, 253);
      colors[ImGuiCol_NavHighlight] = ImColor(189, 147, 249);
      colors[ImGuiCol_NavWindowingHighlight] = ImColor(189, 147, 249);
      colors[ImGuiCol_NavWindowingDimBg] = ImColor(189, 147, 249);
      colors[ImGuiCol_ModalWindowDimBg] = ImColor(16, 16, 16);
    }
    else if (themeName == "node")
    {
      colors[ImGuiCol_Text] = ImColor(255, 255, 255);
      colors[ImGuiCol_TextDisabled] = ImColor(128, 128, 128);
      colors[ImGuiCol_WindowBg] = ImColor(43, 43, 43);
      colors[ImGuiCol_ChildBg] = ImColor(53, 53, 53);
      colors[ImGuiCol_PopupBg] = ImColor(43, 43, 43);
      colors[ImGuiCol_Border] = ImColor(77, 77, 77);
      colors[ImGuiCol_BorderShadow] = ImColor(0, 0, 0);
      colors[ImGuiCol_FrameBg] = ImColor(77, 77, 77);
      colors[ImGuiCol_FrameBgHovered] = ImColor(105, 105, 105);
      colors[ImGuiCol_FrameBgActive] = ImColor(128, 128, 128);
      colors[ImGuiCol_TitleBg] = ImColor(43, 43, 43);
      colors[ImGuiCol_TitleBgActive] = ImColor(53, 53, 53);
      colors[ImGuiCol_TitleBgCollapsed] = ImColor(43, 43, 43);
      colors[ImGuiCol_MenuBarBg] = ImColor(43, 43, 43);
      colors[ImGuiCol_ScrollbarBg] = ImColor(77, 77, 77);
      colors[ImGuiCol_ScrollbarGrab] = ImColor(105, 105, 105);
      colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(128, 128, 128);
      colors[ImGuiCol_ScrollbarGrabActive] = ImColor(153, 153, 153);
      colors[ImGuiCol_CheckMark] = ImColor(128, 128, 128);
      colors[ImGuiCol_SliderGrab] = ImColor(105, 105, 105);
      colors[ImGuiCol_SliderGrabActive] = ImColor(128, 128, 128);
      colors[ImGuiCol_Button] = ImColor(77, 77, 77);
      colors[ImGuiCol_ButtonHovered] = ImColor(105, 105, 105);
      colors[ImGuiCol_ButtonActive] = ImColor(128, 128, 128);
      colors[ImGuiCol_Header] = ImColor(77, 77, 77);
      colors[ImGuiCol_HeaderHovered] = ImColor(105, 105, 105);
      colors[ImGuiCol_HeaderActive] = ImColor(128, 128, 128);
      colors[ImGuiCol_Separator] = ImColor(77, 77, 77);
      colors[ImGuiCol_SeparatorHovered] = ImColor(105, 105, 105);
      colors[ImGuiCol_SeparatorActive] = ImColor(128, 128, 128);
      colors[ImGuiCol_ResizeGrip] = ImColor(128, 128, 128);
      colors[ImGuiCol_ResizeGripHovered] = ImColor(105, 105, 105);
      colors[ImGuiCol_ResizeGripActive] = ImColor(77, 77, 77);
      colors[ImGuiCol_Tab] = ImColor(43, 43, 43);
      colors[ImGuiCol_TabHovered] = ImColor(53, 53, 53);
      colors[ImGuiCol_TabActive] = ImColor(77, 77, 77);
      colors[ImGuiCol_TabUnfocused] = ImColor(43, 43, 43);
      colors[ImGuiCol_TabUnfocusedActive] = ImColor(53, 53, 53);
      colors[ImGuiCol_PlotLines] = ImColor(128, 128, 128);
      colors[ImGuiCol_PlotLinesHovered] = ImColor(153, 153, 153);
      colors[ImGuiCol_PlotHistogram] = ImColor(128, 128, 128);
      colors[ImGuiCol_PlotHistogramHovered] = ImColor(153, 153, 153);
      colors[ImGuiCol_TableHeaderBg] = ImColor(43, 43, 43);
      colors[ImGuiCol_TableBorderStrong] = ImColor(77, 77, 77);
      colors[ImGuiCol_TableBorderLight] = ImColor(105, 105, 105);
      colors[ImGuiCol_TableRowBg] = ImColor(43, 43, 43);
      colors[ImGuiCol_TableRowBgAlt] = ImColor(53, 53, 53);
      colors[ImGuiCol_TextSelectedBg] = ImColor(105, 105, 105);
      colors[ImGuiCol_DragDropTarget] = ImColor(153, 153, 153);
      colors[ImGuiCol_NavHighlight] = ImColor(128, 128, 128);
      colors[ImGuiCol_NavWindowingHighlight] = ImColor(128, 128, 128);
      colors[ImGuiCol_NavWindowingDimBg] = ImColor(43, 43, 43);
      colors[ImGuiCol_ModalWindowDimBg] = ImColor(43, 43, 43);
    }
    else if (themeName == "highcontrast")
    {
      colors[ImGuiCol_Text] = ImColor(255, 255, 255);
      colors[ImGuiCol_TextDisabled] = ImColor(128, 128, 128);
      colors[ImGuiCol_WindowBg] = ImColor(0, 0, 0);
      colors[ImGuiCol_ChildBg] = ImColor(30, 30, 30);
      colors[ImGuiCol_PopupBg] = ImColor(20, 20, 20);
      colors[ImGuiCol_Border] = ImColor(255, 255, 255);
      colors[ImGuiCol_BorderShadow] = ImColor(0, 0, 0);
      colors[ImGuiCol_FrameBg] = ImColor(50, 50, 50);
      colors[ImGuiCol_FrameBgHovered] = ImColor(70, 70, 70);
      colors[ImGuiCol_FrameBgActive] = ImColor(100, 100, 100);
      colors[ImGuiCol_TitleBg] = ImColor(0, 0, 0);
      colors[ImGuiCol_TitleBgActive] = ImColor(20, 20, 20);
      colors[ImGuiCol_TitleBgCollapsed] = ImColor(0, 0, 0);
      colors[ImGuiCol_MenuBarBg] = ImColor(30, 30, 30);
      colors[ImGuiCol_ScrollbarBg] = ImColor(50, 50, 50);
      colors[ImGuiCol_ScrollbarGrab] = ImColor(100, 100, 100);
      colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(120, 120, 120);
      colors[ImGuiCol_ScrollbarGrabActive] = ImColor(140, 140, 140);
      colors[ImGuiCol_CheckMark] = ImColor(255, 255, 255);
      colors[ImGuiCol_SliderGrab] = ImColor(100, 100, 100);
      colors[ImGuiCol_SliderGrabActive] = ImColor(120, 120, 120);
      colors[ImGuiCol_Button] = ImColor(50, 50, 50);
      colors[ImGuiCol_ButtonHovered] = ImColor(70, 70, 70);
      colors[ImGuiCol_ButtonActive] = ImColor(100, 100, 100);
      colors[ImGuiCol_Header] = ImColor(50, 50, 50);
      colors[ImGuiCol_HeaderHovered] = ImColor(70, 70, 70);
      colors[ImGuiCol_HeaderActive] = ImColor(100, 100, 100);
      colors[ImGuiCol_Separator] = ImColor(255, 255, 255);
      colors[ImGuiCol_SeparatorHovered] = ImColor(120, 120, 120);
      colors[ImGuiCol_SeparatorActive] = ImColor(140, 140, 140);
      colors[ImGuiCol_ResizeGrip] = ImColor(255, 255, 255);
      colors[ImGuiCol_ResizeGripHovered] = ImColor(120, 120, 120);
      colors[ImGuiCol_ResizeGripActive] = ImColor(140, 140, 140);
      colors[ImGuiCol_Tab] = ImColor(30, 30, 30);
      colors[ImGuiCol_TabHovered] = ImColor(50, 50, 50);
      colors[ImGuiCol_TabActive] = ImColor(100, 100, 100);
      colors[ImGuiCol_TabUnfocused] = ImColor(30, 30, 30);
      colors[ImGuiCol_TabUnfocusedActive] = ImColor(50, 50, 50);
      colors[ImGuiCol_PlotLines] = ImColor(255, 255, 255);
      colors[ImGuiCol_PlotLinesHovered] = ImColor(255, 255, 255);
      colors[ImGuiCol_PlotHistogram] = ImColor(255, 255, 255);
      colors[ImGuiCol_PlotHistogramHovered] = ImColor(255, 255, 255);
      colors[ImGuiCol_TableHeaderBg] = ImColor(30, 30, 30);
      colors[ImGuiCol_TableBorderStrong] = ImColor(255, 255, 255);
      colors[ImGuiCol_TableBorderLight] = ImColor(100, 100, 100);
      colors[ImGuiCol_TableRowBg] = ImColor(20, 20, 20);
      colors[ImGuiCol_TableRowBgAlt] = ImColor(30, 30, 30);
      colors[ImGuiCol_TextSelectedBg] = ImColor(70, 70, 70);
      colors[ImGuiCol_DragDropTarget] = ImColor(70, 70, 70);
      colors[ImGuiCol_NavHighlight] = ImColor(255, 255, 255);
      colors[ImGuiCol_NavWindowingHighlight] = ImColor(255, 255, 255);
      colors[ImGuiCol_NavWindowingDimBg] = ImColor(70, 70, 70);
      colors[ImGuiCol_ModalWindowDimBg] = ImColor(0, 0, 0);
    }
  }

  void Run()
  {
    // Initialize the underlying app
    AppBackend::init();
    StartUp();

    while (!glfwWindowShouldClose(window))
    {
      // Poll events like key presses, mouse movements etc.
      glfwPollEvents();

      // Start the Dear ImGui frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      // Main loop of the underlying app
      Update();
      AppBackend::update();

      // Rendering
      ImGui::Render();
      int display_w, display_h;
      glfwGetFramebufferSize(window, &display_w, &display_h);
      glViewport(0, 0, display_w, display_h);
      glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
                   clear_color.w);
      glClear(GL_COLOR_BUFFER_BIT);
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      // Update and Render additional Platform Windows
      // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste
      // this code elsewhere.
      //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
      ImGuiIO &io = ImGui::GetIO();
      if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
      {
        GLFWwindow *backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
      }
      glfwSwapBuffers(window);
    }
  }

  void Update()
  {
    static_cast<Derived *>(this)->Update();
  }

  void StartUp()
  {
    static_cast<Derived *>(this)->StartUp();
  }

private:
  GLFWwindow *window = nullptr;
  ImVec4 clear_color = ImVec4(0.1058, 0.1137f, 0.1255f, 1.00f);
};

#endif // App_Base_H