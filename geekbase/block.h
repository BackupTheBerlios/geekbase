#ifndef BLOCK_H
#define BLOCK_H

#include <sys/types.h>

#include "buffer.h"

struct block;

typedef struct block_ block;

struct block_ {
	buffer *buff;
	block *next;
};

/**
 * @brief Creates a new block.
 * @param member_size The size of the objects to contain
 * @param data The element to add
 * @return A pointer to the block just created
 */
block *block_new(size_t member_size, size_t size);

/**
 * @brief Free a  block.
 * @param morituro The block to kill
 */
void block_free(block *morituro);

#endif /* BLOCK_H */
