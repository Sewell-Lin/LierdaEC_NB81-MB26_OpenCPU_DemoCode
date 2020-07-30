
CFLAGS_INC += -I$(TOP)/PLAT/driver/board/$(TARGET)/inc       \
              -I$(TOP)/PLAT/driver/chip/$(CHIP)/inc          \
              -I$(TOP)/PLAT/driver/chip/$(CHIP)/inc_cmsis    \
              -I$(TOP)/PLAT/os/freertos/CMSIS/inc            \
              -I$(TOP)/PLAT/os/freertos/inc                  \
              -I$(TOP)/PLAT/os/osa/inc


ifeq ($(DRIVER_PMU_ENABLE),y)  
    CFLAGS      += -DPM_FEATURE_ENABLE
endif

ifeq ($(DRIVER_UNILOG_ENABLE),y)  
    CFLAGS      += -DUINILOG_FEATURE_ENABLE
endif

libdriver-$(DRIVER_USART_ENABLE)         += PLAT/driver/chip/$(CHIP)/src_cmsis/bsp_usart.o
libdriver-$(DRIVER_ADC_ENABLE)           += PLAT/driver/chip/$(CHIP)/src/adc_ec616.o
libdriver-$(DRIVER_SPI_ENABLE)           += PLAT/driver/chip/$(CHIP)/src_cmsis/bsp_spi.o
libdriver-$(DRIVER_I2C_ENABLE)           += PLAT/driver/chip/$(CHIP)/src_cmsis/bsp_i2c.o
libdriver-$(DRIVER_GPIO_ENABLE)          += PLAT/driver/chip/$(CHIP)/src/gpio_ec616.o          \
                                            PLAT/driver/chip/$(CHIP)/src/pad_ec616.o
libdriver-$(DRIVER_TIMER_ENABLE)         += PLAT/driver/chip/$(CHIP)/src/timer_ec616.o
libdriver-$(DRIVER_WDG_ENABLE)           += PLAT/driver/chip/$(CHIP)/src/wdt_ec616.o
libdriver-y                              += PLAT/driver/chip/$(CHIP)/src/clock_ec616.o
libdriver-$(DRIVER_PMU_ENABLE)           += PLAT/driver/chip/$(CHIP)/src/vector_ec616.o


libdriverprivate-y                       += PLAT/driver/chip/$(CHIP)/src/uart_ec616.o
libdriverprivate-$(DRIVER_UNILOG_ENABLE) += PLAT/driver/chip/$(CHIP)/src/unilog_ec616.o
libdriverprivate-$(DRIVER_EFUSE_ENABLE)  += PLAT/driver/chip/$(CHIP)/src/efuse_ec616.o
libdriverprivate-$(DRIVER_CIPHER_ENABLE) += PLAT/driver/chip/$(CHIP)/src/l2cflh_ec616.o       \
                                            PLAT/driver/chip/$(CHIP)/src/l2ctls_ec616.o
libdriverprivate-$(DRIVER_RNG_ENABLE)    += PLAT/driver/chip/$(CHIP)/src/rng_ec616.o                                           
libdriverprivate-$(DRIVER_CACHE_ENABLE)  += PLAT/driver/chip/$(CHIP)/src/cache_ec616.o

libdriverprivate-$(DRIVER_FLASHRT_ENABLE)+= PLAT/driver/chip/$(CHIP)/src/flash_ec616_rt.o
libdriverprivate-$(DRIVER_FLASH_ENABLE)  += PLAT/driver/chip/$(CHIP)/src/qspi_ec616.o           \
                                            PLAT/driver/chip/$(CHIP)/src/flash_ec616.o
libdriverprivate-$(DRIVER_MCUMODE_ENABLE)+= PLAT/driver/chip/$(CHIP)/src/mcumode_ec616.o


libdriverprivate-$(DRIVER_IC_ENABLE)     += PLAT/driver/chip/$(CHIP)/src/ic_ec616.o
libdriverprivate-$(DRIVER_GPR_ENABLE)    += PLAT/driver/chip/$(CHIP)/src/gpr_ec616.o
libdriverprivate-$(DRIVER_DMA_ENABLE)    += PLAT/driver/chip/$(CHIP)/src/dma_ec616.o
libdriverprivate-$(DRIVER_PMU_ENABLE)       += PLAT/driver/chip/$(CHIP)/src/ecpm_ec616.o          \
                                            PLAT/driver/chip/$(CHIP)/src/pmu_ec616.o            \
                                            PLAT/driver/chip/$(CHIP)/src/swcnt_ec616.o          \
                                            PLAT/driver/chip/$(CHIP)/src/ramboot_ec616.o        \
                                           PLAT/driver/chip/$(CHIP)/src/timetrans_ec616.o      \
                                           PLAT/driver/chip/$(CHIP)/src/hibtimer_ec616.o       \
                                           PLAT/driver/chip/$(CHIP)/src/slpman_ec616.o  


##obj-$(DRIVER_PMU_ENABLE)                 += PLAT/driver/chip/$(CHIP)/src/vector_ec616.o

