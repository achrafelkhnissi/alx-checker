//
// Created by Achraf El khnissi on 2/24/23.
//

#ifndef ALX_CHECKER_ANIMATION_HPP
#define ALX_CHECKER_ANIMATION_HPP

#include <iostream>
#include <chrono>
#include <thread>

namespace alx
{
	class Animation {

	private:
		int delay_;
		mutable int width_;
		mutable bool finished_ = false;

	public:
		Animation(int width = 50, int delay = 100);
		~Animation();

		void start() const;
		void stop() const;

	};
}


#endif //ALX_CHECKER_ANIMATION_HPP
