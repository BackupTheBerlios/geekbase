#ifndef BLOCKLIST_H
#define BLOCKLIST_H

#include <stdlib.h>

#include "block.h"

typedef struct {
	unsigned blocknum;
	size_t member_size;
	size_t block_size;
	block *first;
} blocklist;

/**
 * @brief Creates a blocklist with one block.
 * @param block_size The size of the block container
 * @return A pointer to the blocklist just created
 */
blocklist *blocklist_new(size_t block_size, size_t member_size);

/**
 * @brief Frees a blocklist and the blocks it contains.
 * @param morituro 
 */
int blocklist_free(blocklist *morituro);

/**
 * @brief Insert a block in the blocklist after the block given.
 * @param bl The blocklist
 * @param b The block to insert
 * @param where The block before block b will be inserted
 */
int blocklist_block_insert(blocklist *bl, block *b, block *where);

/**
 * @brief Append a block in the blocklist after the last block.
 * @param bl The blocklist
 * @param b The block to append
 */
int blocklist_block_append(blocklist *bl, block *b);

/**
 * @brief Insert a block to the beginning of a blocklist.
 * @param bl The blocklist
 * @param b The block to insert
 */
int blocklist_block_first(blocklist *bl, block *b);

#endif /* BLOCKLIST_H */