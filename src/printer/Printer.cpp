/**
 * @file Printer.cpp
 * @brief Printer class implementation
 * @author Achraf El Khnissi
 */

#include "Printer.hpp"

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
        std::cout << "[ " << BLUE << "INFO" << END << " ]: ";
        std::cout << text << std::endl;
    }

}