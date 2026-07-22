#include "data/BoardData.hpp"

namespace EvoSphere
{
    std::array<Tile, BOARD_SIZE> createBoardTiles()
    {
        return {
            Tile{0, TileType::OriginGate, ElementType::None, "", "", false},

            // Nature territory
            Tile{1, TileType::WildEvoran, ElementType::Nature, "Nature", "Mossari", true},
            Tile{2, TileType::BlessingShrine, ElementType::None, "", "", false},
            Tile{3, TileType::WildEvoran, ElementType::Nature, "Nature", "Florayn", true},
            Tile{4, TileType::WildEvoran, ElementType::Nature, "Nature", "Thorniva", true},

            Tile{5, TileType::Teleport, ElementType::None, "", "", false},

            // Rock / Electric section
            Tile{6, TileType::WildEvoran, ElementType::Rock, "Rock", "Basaldrum", true},
            Tile{7, TileType::ChaosRift, ElementType::None, "", "", false},
            Tile{8, TileType::WildEvoran, ElementType::Electric, "Electric", "Sparqit", true},
            Tile{9, TileType::WildEvoran, ElementType::Electric, "Electric", "Ionixu", true},

            Tile{10, TileType::Guardian, ElementType::Mystic, "Guardian", "Solvyrion", false},

            Tile{11, TileType::WildEvoran, ElementType::Electric, "Electric", "Thundravo", true},
            Tile{12, TileType::SpecialOwnable, ElementType::None, "Relic", "Gemstone Mine", true},

            // Fire / Water section
            Tile{13, TileType::WildEvoran, ElementType::Fire, "Fire", "Flarexon", true},
            Tile{14, TileType::WildEvoran, ElementType::Fire, "Fire", "Pyroclast", true},

            Tile{15, TileType::Teleport, ElementType::None, "", "", false},

            Tile{16, TileType::WildEvoran, ElementType::Water, "Water", "Ripplin", true},
            Tile{17, TileType::BlessingShrine, ElementType::None, "", "", false},
            Tile{18, TileType::WildEvoran, ElementType::Water, "Water", "Tidalux", true},
            Tile{19, TileType::WildEvoran, ElementType::Water, "Water", "Mistora", true},

            Tile{20, TileType::Guardian, ElementType::Mystic, "Guardian", "Aequorion", false},

            // Air / Dark section
            Tile{21, TileType::WildEvoran, ElementType::Air, "Air", "Driftail", true},
            Tile{22, TileType::ChaosRift, ElementType::None, "", "", false},
            Tile{23, TileType::WildEvoran, ElementType::Air, "Air", "Zephyrox", true},
            Tile{24, TileType::WildEvoran, ElementType::Dark, "Dark", "Duskleaf", true},

            Tile{25, TileType::Teleport, ElementType::None, "", "", false},

            Tile{26, TileType::WildEvoran, ElementType::Dark, "Dark", "Voidmar", true},
            Tile{27, TileType::SpecialOwnable, ElementType::None, "Relic", "Orb Forge", true},

            // Mystic section
            Tile{28, TileType::WildEvoran, ElementType::Mystic, "Mystic", "Auramind", true},
            Tile{29, TileType::WildEvoran, ElementType::Mystic, "Mystic", "Runelith", true},

            Tile{30, TileType::Guardian, ElementType::Dark, "Guardian", "Noctharax", false},

            // Remaining unique roster Evorans
            Tile{31, TileType::WildEvoran, ElementType::Dark, "Dark", "Umbraxo", true},
            Tile{32, TileType::BlessingShrine, ElementType::None, "", "", false},
            Tile{33, TileType::WildEvoran, ElementType::Rock, "Rock", "Pebloru", true},
            Tile{34, TileType::WildEvoran, ElementType::Rock, "Rock", "Cragorn", true},

            Tile{35, TileType::Teleport, ElementType::None, "", "", false},

            Tile{36, TileType::ChaosRift, ElementType::None, "", "", false},
            Tile{37, TileType::WildEvoran, ElementType::Fire, "Fire", "Emberu", true},
            Tile{38, TileType::SpecialOwnable, ElementType::None, "Relic", "Ancient Relic Shrine", true},
            Tile{39, TileType::WildEvoran, ElementType::Air, "Air", "Galevi", true}
        };
    }

    const std::array<int, TELEPORT_TILE_COUNT>& getTeleportTerminalPositions()
    {
        static const std::array<int, TELEPORT_TILE_COUNT> terminals{
            5, 15, 25, 35
        };

        return terminals;
    }
}