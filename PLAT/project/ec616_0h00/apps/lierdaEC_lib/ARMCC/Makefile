AVAILABLE_TARGETS = ec616_0h00
TOOLCHAIN         = ARMCC
BINNAME           = lierdaEC_lib_flash
TOP               := ../../../../../..
THIRDPARTY_CTWING1_5_ENABLE   = y
THIRDPARTY_WAKAAMA_ENABLE   = y
THIRDPARTY_ERCOAP_ENABLE   = y
THIRDPARTY_CISONENET_ENABLE = y
THIRDPARTY_LIBCOAP_ENABLE  = y
THIRDPARTY_MQTT_ENABLE     = y
THIRDPARTY_HTTPC_ENABLE    = y
THIRDPARTY_MBEDTLS_ENABLE  = y
THIRDPARTY_TINYDTLS_ENABLE = y
THIRDPARTY_CJSON_ENABLE = n
THIRDPARTY_ABUP_FOTA_ENABLE = n
THIRDPARTY_CTCC_DM_ENABLE = y
THIRDPARTY_CUCC_DM_ENABLE = y
THIRDPARTY_CMCC_DM_ENABLE = y
AT_EXAMPLE_ENABLE = n
AT_ADC_ENABLE = y
BUILD_AT_REF   = n


CFLAGS_INC        +=  -I ../inc
obj-y              = PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/app.o \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/bsp_custom.o \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/demo_app.o \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/lierdaEC_DEMO_ADC.o \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/lierdaEC_DEMO_AT.o \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/lierdaEC_DEMO_DATA.o \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/lierdaEC_DEMO_GPIO.o \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/lierdaEC_DEMO_I2C.o \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/lierdaEC_DEMO_SPI.o \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/lierdaEC_DEMO_TCPIP.o \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/lierdaEC_DEMO_Timer_PWM.o \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/lierdaEC_DEMO_USART.o \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/lierdaEC_ct_task.o \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/lierdaEC_ct_api.o 
                     
                                    
libEC-y           += PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/lierdaEC_adc.o \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/lierdaEC_gpio.o \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/lierdaEC_virtual_at.o  \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/lierdaEC_tcpip.o \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/lierdaEC_timer_pwm.o \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/lierdaEC_uart.o \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/lierdaEC_i2c.o \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/lierdaEC_spi.o \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/lierdaEC_wdt.o \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/lierdaEC_rtc_time.o \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/lierdaEC_ctiot.o  \
                     PLAT/project/$(TARGET)/apps/lierdaEC_lib/src/hal_uart_atcmd.o 
                     

APP_OBJS := $(addprefix $(TOP)/PLAT/out/$(TARGET)/$(PROJECT)/,$(libEC-y))
-include $(APP_OBJS:.o=.d)

ifeq ($(BUILD_USE_PREBUILD_LIB),n)
ifneq ($(APP_OBJS),)
lib-y += liblierdaEC.lib
endif
endif

$(TOP)/PLAT/out/$(TARGET)/$(PROJECT)/lib/liblierdaEC.lib: $(APP_OBJS)
	@mkdir -p $(dir $@)
	$(ECHO) AR $@
	$(Q)$(AR) $(ARFLAGS) $@ $^


#CONFIG_PROJ_APP_SECURITY_BOOT  = y
include $(TOP)/PLAT/project/$(TARGET)/apps/$(PROJECT)/armcc/MakeProj.rules
include $(TOP)/PLAT/tools/scripts/Makefile.rules
#enable wdt
CFLAGS += -DWDT_FEATURE_ENABLE=1
ifneq ($(BUILD_AT),y)
$(error This example needs to modify "BUILD_AT" to "y" in device\eigencomm\board\$(TARGET)\ec616_0h00.mk)
endif



