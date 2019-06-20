#include "Stopwatch.h"

Stopwatch::Stopwatch()
{
	start();
}

double Stopwatch::reset() noexcept
{
	//elapsed = 0;
	stop();
	start();

	return elapsedTime();
}

void Stopwatch::start() noexcept
{
	mStartTime = std::chrono::high_resolution_clock::now();
}

void Stopwatch::stop() noexcept
{
	mElapsed = std::chrono::high_resolution_clock::now() - mStartTime;
}

double Stopwatch::elapsedTime() noexcept
{
	return mElapsed.count();
}
