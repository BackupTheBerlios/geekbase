#ifndef BLOCK_H
#define BLOCK_H

#include "buffer.h"

typedef struct block {
	buffer *buff;
	struct block *next;
} block;

/**
 * @brief Creates a new block.
 * @param member_size The size of the objects to contain
 * @param size The size of the buffer it contains
 * @return A pointer to the block just created
 */
block *block_new(unsigned member_size, unsigned size);

/**
 * @brief Free a block.
 * @param morituro The block to kill
 */
void block_free(block *morituro);

#endif /* BLOCK_H */
