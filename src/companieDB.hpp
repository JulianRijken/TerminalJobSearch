#ifndef COMPANIES_H
#define COMPANIES_H

#include <SQLiteCpp/Database.h>

#include <cstdint>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace tjs
{
    struct Company
    {
        std::string name;
        std::string product;
        std::string status;
        std::string jobSite;
        std::string languages;
        std::string engines;
        std::string location;
        int rating;

        // // I guess seperate in the database?
        // std::string discription;
        // std::string contactInfo;
    };

    class CompanieDB
    {
    public:
        enum class Categories : uint8_t
        {
            Name,
            Product,
            Status,
            Language,
            Engine,
            Location,
            Rating,
            SIZE
        };


        inline static const std::unordered_map<Categories, std::string> CATEGORY_TO_STRING = {
            {     Categories::Name,     "Name" },
            {  Categories::Product,  "Product" },
            {   Categories::Status,   "Status" },
            { Categories::Language, "Language" },
            {   Categories::Engine,   "Engine" },
            { Categories::Location, "Location" },
            {   Categories::Rating,   "Rating" }
        };

        static std::string CategoryToString(Categories category)
        {
            auto it = CATEGORY_TO_STRING.find(category);
            return it != CATEGORY_TO_STRING.end() ? it->second : "Unknown";
        }

        const std::vector<int>& GetCategoryWidths();
        const std::vector<Company>& GetLoadedCompanies();
        ftxui::Element RenderCompanyTable();

        CompanieDB();

    private:
        static constexpr const char* COMPANIES_DB_PATH = "./companies.db";

        static constexpr int COL_COUNT = static_cast<int>(Categories::SIZE);
        static constexpr int MAX_COL_WIDTH = 30;

        SQLite::Database m_CompaniesDB{ COMPANIES_DB_PATH, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE };

        // clang-format off
        // NOLINTBEGIN
        std::vector<Company> m_LoadedCompanies = {
            {"Activision/Blizzard", "Call of Duty", "Check Site", "https://careers.activisionblizzard.com/early-careers", "C++", "Custom", "Europa", 0},
            {"Avalanche Studios", "theHunter; Just Cause", "Check Site", "https://avalanchestudios.com/technology", "C++", "Unreal", "Avalanche Studios", 0},
            {"Behaviour Interactive", "Dead By Daylight", "Check Site", "https://www.bhvr.com/", "C++, C#", "Unity, Unreal", "Behaviour Interactive NL", 0},
            {"CAPCOM", "Ace Attorney; Resident Evil", "Not for me", "https://www.capcom.co.jp/recruit/english/", "", "", "CAPCOM STORE TOKYO", 0},
            {"Chucklefish", "Starbound", "Check Site", "", "C++", "", "", 0},
            {"Climax Studios", "Remaster Mafia", "Check Site", "https://www.climaxstudios.com/join-our-team/", "C++", "Unreal", "Climax Studios", 4},
            {"CodeWeavers", "WINE, Proton", "Not for me", "https://www.codeweavers.com/about/jobs", "C++", "", "Codeweavers Ltd", 0},
            {"Coffee Stain", "Goat Sim, Satisfactory", "Check Site", "https://www.coffeestainstudios.com/games/", "C++", "", "Coffee Stain Studios", 0},
            {"Creative Assembly", "Alien, Total War", "Check Site", "https://www.creative-assembly.com/careers", "C++", "", "Creative Assembly", 0},
            {"Croteam", "The Talos Principle", "Check Site", "https://www.linkedin.com/company/croteam", "", "", "", 0},
            {"Crytek", "Crysis", "Check Site", "https://www.crytek.com/career/offers/overview/frankfurt-onsite-/programming-engineering/build-engineer", "C++", "Custom", "Crytek GmbH", 0},
            {"Devolver Digital", "Return to Monkey Island", "Check Site", "https://www.devolverdigital.com", "", "", "", 0},
            {"DICE", "Battlefield, Mirror's Edge", "Check Site", "https://jobs.ea.com/en_US/careers/Home/?4538=%5B8370%5D&4538_format=3021&listFilterMode=1&jobRecordsPerPage=20&", "C++", "Custom", "", 0},
            {"Embark Studios", "The Finals (UE), others unannounced", "Check Site", "https://www.embark-studios.com/", "C++", "", "Embark Studios, Bankpalatset", 5},
            {"Feral Interactive", "PORTING: Alien, Total War, way more", "Check Site", "https://jobs.feralinteractive.com/#grad_c_game_dev", "C++", "", "Feral Interactive Ltd", 0},
            {"Frictional Games", "", "Not for me", "", "C++", "", "Frictional Games AB", 0},
            {"Frozenbyte", "Trine", "Check Site", "https://www.frozenbyte.com/jobs#Programming", "C++", "", "Frozenbyte Oy", 0},
            {"Guerrilla", "Horizon Zero Dawn", "Check Site", "https://www.guerrilla-games.com/join/working-at-guerrilla", "C++", "", "Guerrilla", 0},
            {"Insomniac", "Ratchet & Clank; Spiderman", "Check Site", "https://insomniac.games", "C++", "", "Insomniac Games", 0},
            {"iOi", "Hitman", "Check Site", "https://ioi.dk/careers", "C++", "", "IOI Copenhagen", 5},
            {"Klei", "Don't Starve", "Check Site", "https://www.klei.com/", "C++, Lua", "", "", 0},
            {"Kojima Productions", "Death Stranding", "Check Site", "https://www.kojimaproductions.jp/en/system-programmer", "C++", "", "KOJIMA PRODUCTIONS Co., Ltd.", 5},
            {"Larian", "Baldur's Gate 3", "Check Site", "", "C++", "Custom", "Larian Studios", 3},
            {"MercurySteam", "Metroid Dread", "Check Site", "https://www.mercurysteam.com/", "", "", "Mercury Steam", 0},
            {"Mojang", "Minecraft", "Check Site", "", "Java", "Custom", "Mojang Studios", 5},
            {"Naughty Dog", "The Last of Us", "Check Site", "https://www.naughtydog.com/greenhouse/job/5705388?gh_jid=5705388", "C++", "", "Naughty Dog LLC", 0},
            {"Phobia Game Studio", "CARRION", "Not for me", "", "C#", "", "", 0},
            {"Playground Games", "Forza; Fable", "Check Site", "https://playground-games.com/careers/oWMnofwd/", "C++", "", "Playground Games", 5},
            {"Rare UK", "Sea Of Thieves", "Check Site", "https://www.rare.co.uk/", "C++", "Unreal", "Rare", 5},
            {"Rockstar North", "GTA", "Check Site", "", "C++", "Custom", "Rockstar North", 5},
            {"Sumo", "", "Check Site", "https://www.sumo-digital.com/our-games/", "", "", "Sumo Digital", 3},
            {"team reptile", "", "Check Site", "https://team-reptile.com/games/", "", "", "Team Reptile", 0},
            {"Egosoft", "X series", "Check Site", "https://www.egosoft.com/community/news_en.php", "C++", "Custom", "Würselen", 0},
            {"Remedy Entertainment", "FBC: Firebreak, Alan Wake, Quantum Break", "Check Site", "https://www.remedygames.com/", "C++", "", "Espoo", 0},
            {"Triangle Factory", "Hyper Dash", "Employed", "https://www.triangle-factory.be/#Games", "C#", "Unity", "", 4},
            {"Ubisoft", "", "Check Site", "", "", "", "", 0},
            {"Unity", "", "Check Site", "https://unity.com/", "C#", "Unity", "", 0},
            {"Unknown Worlds", "Subnatica", "Check Site", "https://unknownworlds.com/games/", "C#", "Unity", "San Francisco", 0},
            {"Valve", "Portal, Half Life", "Check Site", "", "", "Custom", "Washington D.C.", 0},
            {"Vertigo Games", "", "Check Site", "", "C++", "Unreal", "Vertigo Games", 0},
            {"Wube Software", "Factorio", "Check Site", "https://www.factorio.com/", "C++", "Custom", "Wube Software", 0},
            {"XR Lab BE", "", "Not for me", "https://xrlab.rma.ac.be/", "C++, C#", "Unreal, Unity", "", 0},
            {"XR Lab NL", "", "Not for me", "https://www.xr-lab.nl/", "C++, C#", "Unreal, Unity", "XR Lab", 0},
            {"ZeniMax", "", "Check Site", "", "C++", "", "ZeniMax Media Inc.", 0},
            {"House Of How", "Outsourcing", "Check Site", "https://www.houseofhow.com/careers/", "C#, C++", "Custom, Unity, Unreal", "House of How Sweden", 0},
            {"Infinity Ward", "Call Of Duty", "Check Site", "https://www.infinityward.com/", "C++", "Custom", "Infinity Ward", 0},
            {"Behemia Interactive", "Arma, Dayz", "Check Site", "https://careers.bohemia.net/positions?departments=6", "C++", "Custom", "Bohemia Interactive", 0},
            {"King Art Games", "Iron Harvest", "Check Site", "https://king-art-gmbh.factorialhr.de/#jobs", "C#", "Unity", "Bremen", 0},
            {"EA Studios", "", "Check Site", "https://jobs.ea.com/en_US/careers/JobDetail/Software-Engineer-Intern-C/201938", "C++", "Unreal", "Madrid", 0},
            {"Grimlore Games", "Titan Quest II", "Check Site", "https://grimloregames.com/jobs/", "C++", "Unreal", "Bavaria", 0},
            {"Mainframe", "PaxDei", "Check Site", "https://themainframe.com/en/", "", "", "", 0},
            {"Deck13", "The Surge, Atlas Fallen", "Check Site", "https://www.deck13.com/jobs", "C++", "Unreal, Custom", "Frankfurt", 0},
            {"Techland", "Dying light", "Check Site", "https://techland.net/job-offers/junior-programmer-76", "C++", "", "Wrocław", 0},
            {"Tarsier Studio", "Little Nightmares", "Check Site", "https://career.tarsier.se/jobs", "C++", "Unreal", "Malmö", 0}
        };
        // NOLINTEND
        // clang-format on

        // TODO: Make sure this is always updated when updating loaded companies
        std::vector<int> m_CategoryWidths{};

        void UpdateCategoryWidths();
    };


}  // namespace tjs::companies


#endif  // COMPANIES_H
