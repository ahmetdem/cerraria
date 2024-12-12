#ifndef BLOCK_H
#define BLOCK_H

#include <tuple>

enum BlockType {
  DIRT,
  STONE,
  IRON,
};

struct Block {
  BlockType type;
  std::tuple<int, int> place;
  // Any other stuff goes here
};



#endif // BLOCK_H
