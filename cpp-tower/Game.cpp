/**
 * C++ class for a game of the Tower of Hanoi puzzle.
 * 
 * @author
 *   Wade Fagen-Ulmschneider <waf@illinois.edu>
 */

#include "Game.h"
#include "Stack.h"
#include "uiuc/Cube.h"
#include "uiuc/HSLAPixel.h"

#include <iostream>
using std::cout;
using std::endl;

// Solves the Tower of Hanoi puzzle.
// (Feel free to call "helper functions" to help you solve the puzzle.)
void Game::solve() {
  int last_rounds_stack = -1;

  while(stacks_.back().size() < NUM_CUBES_) {
    // iterate on stacks always starting from the left
    bool start_over = false;
    for (int current_stack = 0; current_stack < num_stacks_; current_stack++) {
      // a stack that was just place will be skipped the next round
      if (start_over) {
        break;
      } else if (current_stack == last_rounds_stack ||
                  stacks_[current_stack].size() == 0) {
        continue;
      } else {
        // get the size of the top cube
        int top_size = stacks_[current_stack].peekTop().getLength();
        // iterate over stacks starting with the one immediately to the right of the current
        // circling back to the beginning
        for (int j = 1; j < num_stacks_; j++) {
          int prospective_stack = (current_stack + j) % stacks_.size();
          cout << "current_stack: " << current_stack << " | prospective_stack: " << prospective_stack << endl;
          // prospective stack is an allowed move if top cube of that stack is larger than current cube
          // or if stack is empty
          if (stacks_[prospective_stack].size() == 0 || 
              stacks_[prospective_stack].peekTop().getLength() > top_size) {
            cout << "moving" << endl;
            stacks_[prospective_stack].push_back(stacks_[current_stack].removeTop());
            last_rounds_stack = prospective_stack;
            start_over = true;
            // Prints out the state of the game:
            cout << *this << endl;
            break;
          }
        }
      }
    }
  }
}

// Default constructor to create the initial state:
Game::Game(int num_stacks) {
  num_stacks_ = num_stacks;
  
  // Create the three empty stacks:
  for (int i = 0; i < num_stacks_; i++) {
    Stack stackOfCubes;
    stacks_.push_back( stackOfCubes );
  }

  // Create the four cubes, placing each on the [0]th stack:
  Cube blue(4, uiuc::HSLAPixel::BLUE);
  stacks_[0].push_back(blue);

  Cube orange(3, uiuc::HSLAPixel::ORANGE);
  stacks_[0].push_back(orange);

  Cube purple(2, uiuc::HSLAPixel::PURPLE);
  stacks_[0].push_back(purple);

  Cube yellow(1, uiuc::HSLAPixel::YELLOW);
  stacks_[0].push_back(yellow);
}

std::ostream& operator<<(std::ostream & os, const Game & game) {
  for (unsigned i = 0; i < game.stacks_.size(); i++) {
    os << "Stack[" << i << "]: " << game.stacks_[i];
  }
  return os;
}
