#include "companies.hpp"

#include <cassert>
#include <cmath>

using namespace ftxui;

const std::vector<int>& tjs::Companies::GetCategoryWidths() { return m_CategoryWidths; }

ftxui::Element tjs::Companies::RenderCompanyTable()
{
    std::vector<Element> rows;

    auto separator = [] { return text(" │ ") | color(Color::GrayDark); };

    auto row_with_separators = [&](const std::vector<Element>& cells)
    {
        std::vector<Element> row;
        for(size_t i = 0; i < cells.size(); ++i)
        {
            if(i > 0)
            {
                row.push_back(separator());
            }
            row.push_back(cells[i]);
        }
        return hbox(std::move(row));
    };

    // Header row
    rows.push_back(row_with_separators({
                       text(Companies::CategoryToString(Companies::Categories::Name)) | bold |
                           size(WIDTH, EQUAL, m_CategoryWidths[0]),
                       text(Companies::CategoryToString(Companies::Categories::Product)) | bold |
                           size(WIDTH, EQUAL, m_CategoryWidths[1]),
                       text(Companies::CategoryToString(Companies::Categories::Status)) | bold |
                           size(WIDTH, EQUAL, m_CategoryWidths[2]),
                       text(Companies::CategoryToString(Companies::Categories::Language)) | bold |
                           size(WIDTH, EQUAL, m_CategoryWidths[3]),
                       text(Companies::CategoryToString(Companies::Categories::Engine)) | bold |
                           size(WIDTH, EQUAL, m_CategoryWidths[4]),
                       text(Companies::CategoryToString(Companies::Categories::Location)) | bold |
                           size(WIDTH, EQUAL, m_CategoryWidths[5]),
                       text(Companies::CategoryToString(Companies::Categories::Rating)) | bold |
                           size(WIDTH, EQUAL, m_CategoryWidths[6]),
                   }) |
                   borderEmpty | bgcolor(Color::RGB(60, 20, 20)));

    // Data rows
    int row = 0;
    for(const auto& companie : m_LoadedCompanies)
    {
        rows.push_back(
            row_with_separators({
                text(companie.name) | size(WIDTH, EQUAL, m_CategoryWidths[0]),
                text(companie.product) | size(WIDTH, EQUAL, m_CategoryWidths[1]),
                text(companie.status) | size(WIDTH, EQUAL, m_CategoryWidths[2]),
                text(companie.languages) | bgcolor(Color::DarkGreen) | size(WIDTH, EQUAL, m_CategoryWidths[3]),
                text(companie.engines) | size(WIDTH, EQUAL, m_CategoryWidths[4]),
                text(companie.location) | size(WIDTH, EQUAL, m_CategoryWidths[5]),
                text(std::to_string(companie.rating)) | size(WIDTH, EQUAL, m_CategoryWidths[6]),
            }) |
            borderStyled(BorderStyle::ROUNDED, Color::GrayDark) |
            bgcolor((row % 2 == 0) ? Color::RGB(15, 15, 15) : Color::RGB(10, 10, 10)));

        row++;
    }

    return vbox(rows) | flex | frame | border;
}

tjs::Companies::Companies() { UpdateCategoryWidths(); }

const std::vector<tjs::Company>& tjs::Companies::GetLoadedCompanies() { return m_LoadedCompanies; }

void tjs::Companies::UpdateCategoryWidths()
{
    m_CategoryWidths = std::vector<int>(COL_COUNT);

    // Grow max width with header size
    for(int col = 0; col < COL_COUNT; ++col)
    {
        const auto category = static_cast<Categories>(col);
        m_CategoryWidths[col] = std::max<int>(m_CategoryWidths[col], std::ceil(CategoryToString(category).length()));
    }

    // const int rowCount = static_cast<int>(companies::items.size());
    for(const auto& company : m_LoadedCompanies)
    {
        m_CategoryWidths[0] = std::max<int>(m_CategoryWidths[0], std::ceil(company.name.length()));
        m_CategoryWidths[1] = std::max<int>(m_CategoryWidths[1], std::ceil(company.product.length()));
        m_CategoryWidths[2] = std::max<int>(m_CategoryWidths[2], std::ceil(company.status.length()));
        m_CategoryWidths[3] = std::max<int>(m_CategoryWidths[3], std::ceil(company.languages.length()));
        m_CategoryWidths[4] = std::max<int>(m_CategoryWidths[4], std::ceil(company.engines.length()));
        m_CategoryWidths[5] = std::max<int>(m_CategoryWidths[5], std::ceil(company.location.length()));
        m_CategoryWidths[6] = std::max<int>(m_CategoryWidths[6], std::ceil(std::to_string(company.rating).length()));
    }

    // Limit size
    for(int& width : m_CategoryWidths)
    {
        width = std::min<int>(width, MAX_COL_WIDTH);
    }
}
