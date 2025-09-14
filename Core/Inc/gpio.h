#ifndef __GPIO_H__
#define __GPIO_H__
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void GPIO_Init(void);
bool GPIO_isUserButtonPressed(void);


#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

