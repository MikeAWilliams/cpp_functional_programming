#pragma once
#include "logger.h"
#include "tennis.h"

#include <string>

Logger<tennis::GameState> LogScorePointP1(const tennis::GameState& state);
Logger<tennis::GameState> LogScorePointP2(const tennis::GameState& state);

std::string GetScoreAsString(tennis::GameState);