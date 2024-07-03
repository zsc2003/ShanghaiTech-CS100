#ifndef ARTDIGITS_HPP
#define ARTDIGITS_HPP

inline constexpr int DigitHeight = 6;
inline constexpr int DigitWidth = 10;

inline constexpr int FrameHeight = 11;
inline constexpr int FrameWidth = 20;

inline constexpr char Frame[FrameHeight][FrameWidth + 1] = {
    " .----------------. ",
    "| .--------------. |",
    "| |              | |",
    "| |              | |",
    "| |              | |",
    "| |              | |",
    "| |              | |",
    "| |              | |",
    "| |              | |",
    "| '--------------' |",
    " '----------------' "
};

// The number is placed in the frame with the up-left corner at (2, 4).
inline constexpr int DigitBaseRow = 2;
inline constexpr int DigitBaseCol = 4;

inline constexpr char ArtDigit[10][DigitHeight][DigitWidth + 1] = {
    {
        "   ____   ",
        " .'    '. ",
        "|  .--.  |",
        "| |    | |",
        "|  `--'  |",
        " '.____.' "
    },

    {
        "   __     ",
        "  /  |    ",
        "  `| |    ",
        "   | |    ",
        "  _| |_   ",
        " |_____|  "
    },

    {
        "  _____   ",
        " / ___ `. ",
        "|_/___) | ",
        " .'____.' ",
        "/ /____   ",
        "|_______| "
    },

    {
        "  ______  ",
        " / ____ `.",
        " `'  __) |",
        " _  |__ '.",
        "| \\____) |",
        " \\______.'"
    },

    {
        " _    _   ",
        "| |  | |  ",
        "| |__| |_ ",
        "|____   _|",
        "    _| |_ ",
        "   |_____|"
    },

    {
        " _______  ",
        "|  _____| ",
        "| |____   ",
        "'_.____''.",
        "| \\____) |",
        " \\______.'"
    },

    {
        "  ______  ",
        ".' ____ \\ ",
        "| |____\\_|",
        "| '____`'.",
        "| (____) |",
        "'.______.'"
    },

    {
        " _______  ",
        "|  ___  | ",
        "|_/  / /  ",
        "    / /   ",
        "   / /    ",
        "  /_/     "
    },

    {
        "   ____   ",
        " .' __ '. ",
        " | (__) | ",
        " .`____'. ",
        "| (____) |",
        "`.______.'"
    },

    {
        "  ______  ",
        ".' ____ '.",
        "| (____) |",
        "'_.____. |",
        "| \\____| |",
        " \\______,'"
    }
};

inline constexpr int ColonWidth = 11;

inline constexpr char Colon[FrameHeight][ColonWidth + 1] = {
    "           ",
    "           ",
    "           ",
    "     _     ",
    "    (_)    ",
    "     _     ",
    "    (_)    ",
    "           ",
    "           ",
    "           ",
    "           "
};

#endif // ARTDIGITS_HPP