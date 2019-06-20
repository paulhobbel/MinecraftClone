#pragma once

#include <chrono>

class Stopwatch
{
public:
	Stopwatch();

	double reset() noexcept;

	void start() noexcept;

	void stop() noexcept;

	double elapsedTime() noexcept;

private:
	std::chrono::steady_clock::time_point mStartTime;
	std::chrono::duration<double> mElapsed;
};
