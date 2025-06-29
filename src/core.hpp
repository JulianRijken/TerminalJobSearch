#ifndef CORE_H
#define CORE_H

#include <ftxui/dom/elements.hpp>

#include "companies.hpp"

namespace tjs
{
    class Core
    {
    public:
        Core();

    private:
        Companies m_Companies{};
    };

#endif  // CORE_H
}
