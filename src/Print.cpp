/**
 * @file Print.cpp
 * @brief Print class implementation
 * @author Achraf El Khnissi
 */

#include "Print.hpp"

namespace alx {

	/* @brief Construct a new Print:: Print object */
	Print::Print() {
		// TODO
	}

	/* @brief Destroy the Print:: Print object */
	Print::~Print() {
		// TODO
	}

//	template<typename... Args>
//	void Print::printf(const Args&... args) const {
//		std::ostringstream oss;
//		(oss << ... << args);
//		std::cout << oss.str() << std::endl;
//	}

	/**
	 * @brief Print a text with a color
	 * @param text
	 * @param color
	 */
	void Print::print(const std::string &text, const std::string &color) const {
		std::cout << color << text << END << std::endl;
	}

	/**
	 * @brief Print a text with a color and a background
	 * @param text : text to print
	 * @param color : color of the text
	 * @param background : background of the text
	 */
	void Print::print(const std::string &text, const std::string &color, const std::string &background) const {
		std::cout << color << background << text << END << std::endl;
	}

	/**
	 * @brief Print a text with a color, a background and a style
	 * @param text : text to print
	 * @param color : color of the text
	 * @param background : background of the text
	 * @param style : style of the text
	 */
	void Print::print(const std::string &text, const std::string &color, const std::string &background, const std::string &style) const {
		std::cout << color << background << style << text << END << std::endl;
	}

	/**
	 * @brief Print an error text with a RED color
	 * @param text: text to print
	 */
	void Print::error(const std::string &text) const {
		std::err << RED << text << END << std::endl;
	}

	/**
	 * @brief Print a warning text with a YELLOW color
	 * @param text: text to print
	 */
	void Print::warning(const std::string &text) const {
		std::cout << YELLOW << text << END << std::endl;
	}

	/**
	 * @brief Print a success text with a GREEN color
	 * @param text  : text to print
	 */
	void Print::success(const std::string &text) const {
		std::cout << GREEN << text << END << std::endl;
	}

	/**
	 * @brief Print an info text with a BLUE color
	 * @param text : text to print
	 */
	void Print::info(const std::string &text) const {
		std::cout << BLUE << text << END << std::endl;
	}

}