#pragma once

class Application;
class Scheduler {
public:
	double currentTime = 0;
	double deltaTime = 0;
	int FPS = 0;
	double lastTime = 0;
	double secondAccumulator = 0;
	double updateAccumulator = 0;
	double updateInterval = 0;
public:
	Scheduler(double updateInterval);
	~Scheduler();
public:
	bool shouldUpdate();
};
