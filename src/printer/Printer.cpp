/**
 * @file Printer.cpp
 * @brief Printer class implementation
 * @author Achraf El Khnissi
 */

#include "Printer.hpp"
#include <iomanip>

namespace alx {

    /* @brief Construct a new Printer:: Printer object */
    Printer::Printer() {
        // TODO
    }

    /* @brief Destroy the Printer:: Printer object */
    Printer::~Printer() {
        // TODO
    }

//	template<typename... Args>
//	void Printer::printf(const Args&... args) const {
//		std::ostringstream oss;
//		(oss << ... << args);
//		std::cout << oss.str() << std::endl;
//	}

    /**
     * @brief Printer a text with a color
     * @param text
     * @param color
     */
    void Printer::print(const std::string &text, const std::string &color) const {
        std::cout << color << text << END << std::endl;
    }

    /**
     * @brief Printer a text with a color and a background
     * @param text : text to print
     * @param color : color of the text
     * @param background : background of the text
     */
    void Printer::print(const std::string &text, const std::string &color, const std::string &background) const {
        std::cout << color << background << text << END << std::endl;
    }

    /**
     * @brief Printer a text with a color, a background and a style
     * @param text : text to print
     * @param color : color of the text
     * @param background : background of the text
     * @param style : style of the text
     */
    void Printer::print(const std::string &text, const std::string &color, const std::string &background,
                        const std::string &style) const {
        std::cout << color << background << style << text << END << std::endl;
    }

    /**
     * @brief Printer an error text with a RED color
     * @param text: text to print
     */
    void Printer::error(const std::string &text) const {
        std::cerr << RED << text << END << std::endl;
    }

    /**
     * @brief Printer a warning text with a YELLOW color
     * @param text: text to print
     */
    void Printer::warning(const std::string &text) const {
        std::cout << YELLOW << text << END << std::endl;
    }

    /**
     * @brief Printer a success text with a GREEN color
     * @param text  : text to print
     */
    void Printer::success(const std::string &text) const {
        std::cout << GREEN << text << END << std::endl;
    }

    /**
     * @brief Printer an info text with a BLUE color
     * @param text : text to print
     */
    void Printer::info(const std::string &text) const {
		std::string info = "[ " BLUE "INFO" END " ]: " + text;
        std::cout << std::setw(70) << std::left << info;
    }

	void Printer::yellow(const std::string &text) const {
		termcolor::yellow(std::cout) << text << termcolor::reset << std::endl;
	}

	void Printer::red(const std::string &text) const {
		termcolor::red(std::cout) << text << termcolor::reset << std::endl;
	}

	void Printer::green(const std::string &text) const {
		termcolor::green(std::cout) << text << termcolor::reset << std::endl;
	}

	void Printer::cyan(const std::string &text) const {
		termcolor::cyan(std::cout) << text << termcolor::reset << std::endl;
	}

	void Printer::print(const std::string &text, enum color c, enum background b, enum style s) const {

		/*
		 * TODO: implement a color class
		 *     - \033[<color>;<background>;<style>m
		 *     - \033[<color>;<background>m
		 *     - \033[<color>;<style>m
		 *     - \033[<color>m
		 *     - \033[<background>;<style>m
		 *     - \033[<background>m
		 *     - \033[<style>m
		 *     - \033[0m (reset)
		 *     - Make it change dynamically
		 */

		switch (c) {
		case color::red:
			termcolor::red(std::cout);
			break;
		case color::green:
			termcolor::green(std::cout);
			break;
		case color::yellow:
			termcolor::yellow(std::cout);
			break;
		case color::blue:
			termcolor::blue(std::cout);
			break;
		case color::magenta:
			termcolor::magenta(std::cout);
			break;
		case color::cyan:
			termcolor::cyan(std::cout);
			break;
		case color::white:
			termcolor::white(std::cout);
			break;
		case color::grey:
			termcolor::grey(std::cout);
			break;
		default:
			break;
		}

		switch (b) {
		case background::b_red:
			termcolor::on_red(std::cout);
			break;
		case background::b_green:
			termcolor::on_green(std::cout);
			break;
		case background::b_yellow:
			termcolor::on_yellow(std::cout);
			break;
		case background::b_blue:
			termcolor::on_blue(std::cout);
			break;
		case background::b_magenta:
			termcolor::on_magenta(std::cout);
			break;
		case background::b_cyan:
			termcolor::on_cyan(std::cout);
			break;
		case background::b_white:
			termcolor::on_white(std::cout);
			break;
		case background::b_grey:
			termcolor::on_grey(std::cout);
			break;
		default:
			break;
		}

		switch (s) {
		case style::bold:
			termcolor::bold(std::cout);
			break;
		case style::underline:
			termcolor::underline(std::cout);
			break;
		case style::blink:
			termcolor::blink(std::cout);
			break;
		case style::reverse:
			termcolor::reverse(std::cout);
			break;
		case style::concealed:
			termcolor::concealed(std::cout);
			break;
		default:
			break;
		}

		std::cout << text << termcolor::reset << std::endl;

	}

}