#pragma once

#include "game.h"

Game ParseLine(const std::string &line);
Games ParseFile(const std::string &filename);