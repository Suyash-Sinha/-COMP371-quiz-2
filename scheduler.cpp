#include <cstdio>

#include <GLFW/glfw3.h>

#include "scheduler.hpp"

Scheduler::Scheduler(double updateInterval) {
    this->updateInterval = updateInterval;
}
Scheduler::~Scheduler() {
    return;
}
bool Scheduler::shouldUpdate() {
    currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    secondAccumulator += deltaTime;
    updateAccumulator += deltaTime;
    // This accumulator is for the printing of the FPS value.
    // It essentially accumulates deltaTime steps until it hits 1 second
    // and prints the FPS value.
    if (secondAccumulator >= 1) {
        secondAccumulator -= 1;
        printf("FPS: %d\n", FPS);
        FPS = 0;
    }
    // This accumulator essentially accumulates until it hits the update interval
    // Which is 1 / 30 wherein 30 is the number of times we'd want to update per second.
    if (updateAccumulator >= updateInterval) {
        updateAccumulator -= updateInterval;
        return true;
    }
    return false;
}
