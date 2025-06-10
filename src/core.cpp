#include "core.hpp"

#include <cmath>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/dom/table.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>

using namespace ftxui;

tjs::Core::Core()
{

    auto table = Table({
        { "Version",     "Marketing name",     "Release date", "API level",        "Runtime" },
        {     "2.3",        "Gingerbread",  "February 9 2011",        "10",   "Dalvik 1.4.0" },
        {     "4.0", "Ice Cream Sandwich",  "October 19 2011",        "15",         "Dalvik" },
        {     "4.1",         "Jelly Bean",      "July 9 2012",        "16",         "Dalvik" },
        {     "4.2",         "Jelly Bean", "November 13 2012",        "17",         "Dalvik" },
        {     "4.3",         "Jelly Bean",     "July 24 2013",        "18",         "Dalvik" },
        {     "4.4",             "KitKat",  "October 31 2013",        "19", "Dalvik and ART" },
        {     "5.0",           "Lollipop",  "November 3 2014",        "21",            "ART" },
        {     "5.1",           "Lollipop",     "March 9 2015",        "22",            "ART" },
        {     "6.0",        "Marshmallow",   "October 5 2015",        "23",            "ART" },
        {     "7.0",             "Nougat",   "August 22 2016",        "24",            "ART" },
        {     "7.1",             "Nougat",   "October 4 2016",        "25",            "ART" },
        {     "8.0",               "Oreo",   "August 21 2017",        "26",            "ART" },
        {     "8.1",               "Oreo",  "December 5 2017",        "27",            "ART" },
        {       "9",                "Pie",    "August 6 2018",        "28",            "ART" },
        {      "10",                 "10", "September 3 2019",        "29",            "ART" },
        {      "11",                 "11", "September 8 2020",        "30",            "ART" },
    });


    // Add border around the first column.
    table.SelectColumn(0).Border(ROUNDED);

    // Make first row bold with a double border.
    table.SelectRow(0).Decorate(bold);
    table.SelectRow(0).SeparatorVertical(ROUNDED);
    table.SelectRow(1).SeparatorHorizontal(DASHED);

    // Align right the "Release date" column.
    table.SelectColumn(2).DecorateCells(align_right);

    // Select row from the second to the last.
    auto content = table.SelectRows(1, -1);
    content.DecorateCellsAlternateRow(color(Color::Grey23), 2, 0);
    content.DecorateCellsAlternateRow(color(Color::GrayLight), 2, 1);

    Element document =
        hbox({ vbox({ text("The window") | bold | color(Color::Blue), gauge(1), text("The footer") }) | border | flex,
               vbox({ table.Render() }) | border | flex });


    Screen screen = ScreenInteractive::Create(Dimension::Full());
    Render(screen, document);

    screen.Print();

    int test;
    std::cin >> test;
}
