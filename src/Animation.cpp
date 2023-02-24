//
// Created by Achraf El khnissi on 2/24/23.
//

#include "Animation.hpp"

namespace alx
{
	Animation::Animation(int width, int delay)
		: delay_(delay), width_(width){ }

	Animation::~Animation() { }

	void Animation::start() const {
		(void)width_;
		(void)delay_;
//
//		finished_ = false;
//		std::cout << "Downloading ";
//		while (!finished_ && width_--) {
//			std::cout << ".";
//			std::cout.flush();
//			std::this_thread::sleep_for(std::chrono::milliseconds(delay_));
//		}
//		std::cout << std::endl;
        std::cout << "Downloading: ";
        for (int i = 0; i <= 100; i += 5) {
            std::cout << "[";

            for (int j = 0; j <= i; j += 2) {
                std::cout << "#";
            }

            for (int j = i + 2; j <= 100; j += 2) {
                std::cout << " ";
            }

            std::cout << "] " << i << "%" << "\r";
            std::cout.flush();

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::cout << std::endl;
    }


    void Animation::stop() const {
        finished_ = true;
    }
}