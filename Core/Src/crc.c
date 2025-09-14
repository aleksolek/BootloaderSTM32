/* Includes ------------------------------------------------------------------*/
#include "crc.h"
#include "stm32f3xx_ll_crc.h"
#include "stm32f3xx_ll_bus.h"

__attribute__((section(".crc")))
const uint32_t app_crc_placeholder = 0xFFFFFFFF;

/* CRC init function */
void CRC_Init(void)
{


  /* Peripheral clock enable */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_CRC);

  LL_CRC_SetInputDataReverseMode(CRC, LL_CRC_INDATA_REVERSE_NONE);
  LL_CRC_SetOutputDataReverseMode(CRC, LL_CRC_OUTDATA_REVERSE_NONE);
  LL_CRC_SetPolynomialCoef(CRC, LL_CRC_DEFAULT_CRC32_POLY);
  LL_CRC_SetPolynomialSize(CRC, LL_CRC_POLYLENGTH_32B);
  LL_CRC_SetInitialData(CRC, LL_CRC_DEFAULT_CRC_INITVALUE);


}

uint32_t CRC_compute(uint32_t startAddress, uint32_t endAddress){

	    LL_CRC_ResetCRCCalculationUnit(CRC);  // reset before each calculation

	    while (startAddress < endAddress) {
	        uint32_t data = *(uint32_t*)startAddress;
	        LL_CRC_FeedData32(CRC, data);
	        startAddress += 4;
	    }

	    return LL_CRC_ReadData32(CRC);
	}

