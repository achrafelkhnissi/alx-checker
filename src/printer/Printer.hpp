/**
 * @file Print.hpp
 * @brief Print class definition
 * @author Achraf El Khnissi
 * @see https://github.com/ikalnytskyi/termcolor/
 */

#ifndef ALX_CHECKER_PRINT_HPP
#define ALX_CHECKER_PRINT_HPP

enum color {
	black = 30,
	red,
	green,
	yellow,
	blue,
	magenta,
	cyan,
	white,
	grey
};

enum background {
	b_black = 40,
	b_red,
	b_green,
	b_yellow,
	b_blue,
	b_magenta,
	b_cyan,
	b_white,
	b_grey
};

enum style {
	bold = 1,
	underline = 4,
	blink = 5,
	reverse = 7,
	concealed = 8
};

/* Text Styles */
#define END "\033[0m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"
#define BLINK "\033[5m"
#define REVERSE "\033[7m"
#define CONCEALED "\033[8m"

/* Foreground Colors */
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

/* Background Colors */
#define B_BLACK "\033[40m"
#define B_RED "\033[41m"
#define B_GREEN "\033[42m"
#define B_YELLOW "\033[43m"
#define B_BLUE "\033[44m"
#define B_MAGENTA "\033[45m"
#define B_CYAN "\033[46m"
#define B_WHITE "\033[47m"

#include <iostream>
#include <cstdio>
#include <sstream>
#include "termcolor.hpp"

/*
 * @brief alx namespace
 * @details This namespace contains all the alx libraries
 */
namespace alx {

    /**
     * @brief Print class
     * @details This class is used to print colored text in the terminal
     * @see https://en.wikipedia.org/wiki/ANSI_escape_code
     */
    class Printer {

    public:
        Printer();

        ~Printer();

        template<typename... Args>
        void printf(const Args &... args) const;

        void print(const std::string &text, const std::string &color) const;

        void print(const std::string &text, const std::string &color, const std::string &background) const;

        void print(const std::string &text, const std::string &color, const std::string &background,
                   const std::string &style) const;

        void error(const std::string &text) const;

        void warning(const std::string &text) const;

        void success(const std::string &text) const;

        void info(const std::string &text) const;

		void yellow(const std::string& text) const;
		void red(const std::string& text) const;
		void green(const std::string& text) const;
		void cyan(const std::string& text) const;

		void print(const std::string& text, enum color, enum background, enum style) const;
    };
}

#endif //ALX_CHECKER_PRINT_HPP
