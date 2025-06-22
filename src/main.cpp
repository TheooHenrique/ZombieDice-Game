/**
 * @file main.cpp
 *
 * @description
 * This program implements an interactive Zombie Dice Game.
 *
 * ===========================================================================
 * @license
 *
 * This file is part of ZOMBIE DICE GAME project.
 *
 * ZOMBIE DICE GAME is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ZOMBIE DICE GAME is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ZOMBIE DICE GAME.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2024-2025 Selan R. dos Santos.
 * ===========================================================================
 *
 * @author	Selan R dos Santos, <selan.santos@ufrn.br>
 * @date	2024
 */

#include "game_controller.hpp"
#include <filesystem>
using size_type = size_t;

int main(int argc, char* argv[]) {
  //Calling a GameController object by singleton pattern
  GameController &gc = GameController::getInstance();

  size_type ct = 0;
  for (size_type i{1}; i < argc ; ++i){ 
    std::string extension = std::filesystem::path(argv[i]).extension().string();
    if (extension == ".ini"){
      gc.set_initializer(argv[i]);
      ++ct;
    }
  }
  gc.set_initializer_amount(ct);


  //gc.parse_config(argc, argv);
  // The Game Loop (Architecture)
  while (not gc.game_over()) {
    // GameController::print_state();
    gc.process_events();
    gc.update();
    gc.render();
  }
  return EXIT_SUCCESS;
}
