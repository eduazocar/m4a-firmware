#ifdef BOARD_NT_DB
#define EPD_BW_SPI_DISPLAY_X  (200)
#define EPD_BW_SPI_DISPLAY_Y  (200)
#define EPD_BW_SPI_CONTROLLER EPD_BW_SPI_CONTROLLER_IL3829
#define EPD_BW_SPI_PARAM_SPI SPI_DEV(1)

#define EPD_BW_SPI_PARAM_CS GPIO_PIN(PB, 15)
#define EPD_BW_SPI_PARAM_DC GPIO_PIN(PB, 14)
#define EPD_BW_SPI_PARAM_RST GPIO_PIN(PA, 21)
#define EPD_BW_SPI_PARAM_BUSY GPIO_PIN(PA, 20)
#endif

#include_next "epd_bw_spi_params.h"