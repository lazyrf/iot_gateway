#ifndef __ASSERT_H
#define __ASSERT_H

#include "config.h"

#if CONFIG_ASSERT
#define assert(expr) ((expr) ? (void) 0 : assert_cb((uint8_t *) __FILE__, __LINE__))
void assert_cb(uint8_t *file, uint32_t line);
#else
#define assert(expr) ((void) 0)
#endif /* CONFIG_ASSERT */

#endif /* __ASSERT_H */
