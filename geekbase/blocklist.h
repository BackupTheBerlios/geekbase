#ifndef BLOCKLIST_H
#define BLOCKLIST_H

#include <stdlib.h>

#include "block.h"

typedef struct {
	unsigned blocknum;     /**<  */
	unsigned member_size;  /**<  */
	unsigned block_size;   /**<  */
	block *first;          /**<  */
} blocklist;

/**
 * @brief Creates a blocklist with one block.
 * @param block_size The size of the block container
 * @param member_size The size of the member of the buffer in the block
 * @return A pointer to the blocklist just created
 **/
blocklist *blocklist_new(unsigned block_size, unsigned member_size);

/**
 * @brief Frees a blocklist and the blocks it contains.
 * @param morituro 
 **/
int blocklist_free(blocklist *morituro);

/**
 * @brief Insert a block in the blocklist after the block given.
 * @param bl The blocklist
 * @param b The block to insert
 * @param where The block before block b will be inserted
 **/
int blocklist_insert(blocklist *bl, block *b, block *where);

/**
 * @brief Append a block in the blocklist after the last block.
 * @param bl The blocklist
 * @param b The block to append
 **/
int blocklist_append(blocklist *bl, block *b);

/**
 * @brief Insert a block to the beginning of a blocklist.
 * @param bl The blocklist
 * @param b The block to insert
 **/
int blocklist_pushf(blocklist *bl, block *b);

#endif /* BLOCKLIST_H */
