#ifndef BUFFER_H
#define BUFFER_H

#include <sys/types.h>

/** @brief A simple buffer */
typedef struct {
	void *buf;          /**< The memory zone occupied by the buffer */
	unsigned used;      /**< The number of objects in the buffer */
	size_t size;        /**< The maximum number of objects that fit into the buffer */
	size_t member_size; /**< The size of the objects in the buffer */
} buffer;

/**
 * @brief Creates a new buffer.
 * @param member_size The size of the objects to contain
 * @param size The number of locations to allocate
 * @return A pointer to the buffer just created
 **/
buffer *buffer_new(size_t member_size, size_t size);

/**
 * @brief Frees the memory allocated by buffer.
 * @param buff The buffer to be eliminated
 **/
void buffer_free(buffer *buff);

/**
 * @brief Add an element to a buffer
 * @param buff The buffer
 * @param data The element to add
 * @return 0 if all went ok, -1 if malloc failed
 **/
int buffer_add(buffer *buff, void *data);

void *buffer_get(buffer *buff, size_t index);

/**
 * @brief Merge two buffers
 * @param dest The destination buffer
 * @param destpos The location in the destination buffer where to attach the source buffer
 * @param src The source buffer
 * @param src_startpos The location in source buffer where to start the copy
 * @param n The number of elements to copy from the source buffer
 * @return 0 if all went ok, -1 if malloc failed
 **/
int buffer_merge(buffer *dest, size_t destpos, buffer *src, size_t src_startpos, size_t n);

#endif /* BUFFER_H */
