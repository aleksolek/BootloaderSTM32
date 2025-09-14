#ifndef __BL1_H__
#define __BL1_H__

#include "crc.h"
#include <stdbool.h>

void bl1_read_data(void);
void bl1_jump_to_user_app(void);
bool bl1_verify_app(void);

#endif // __BL1_H__
