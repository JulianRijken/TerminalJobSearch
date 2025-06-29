#include "core.hpp"

#include <cmath>
#include <companies.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/dom/table.hpp>
#include <ftxui/screen/screen.hpp>

// TODO: Rating should be a bar wth color

using namespace ftxui;

tjs::Core::Core()
{
    std::vector<Component> rowComponents;
    Component container = Container::Vertical(rowComponents);

    // Screen
    auto screen = ScreenInteractive::Fullscreen();

    // Main renderer
    Component main_renderer = Renderer(container, [&] { return m_Companies.RenderCompanyTable(); });
    screen.Loop(main_renderer);
}
