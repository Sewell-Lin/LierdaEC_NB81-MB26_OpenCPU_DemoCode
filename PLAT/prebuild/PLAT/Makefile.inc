CFLAGS_INC += -I $(LIBDIR)/PLAT/inc

ifeq ($(TOOLCHAIN),ARMCC)
PREBUILDLIBS += $(LIBDIR)/PLAT/lib/keil/libosa.lib \
                $(LIBDIR)/PLAT/lib/keil/libdriver_private.lib \
                $(LIBDIR)/PLAT/lib/keil/libmiddleware_ec_private.lib \
                $(LIBDIR)/PLAT/lib/keil/liblierdaEC.lib \
                $(LIBDIR)/PLAT/lib/keil/libcis_onenet.lib \
                $(LIBDIR)/PLAT/lib/keil/libctlwm2m.lib \
                $(LIBDIR)/PLAT/lib/keil/libdm.lib \
                $(LIBDIR)/PLAT/lib/keil/libdriver.lib \
                $(LIBDIR)/PLAT/lib/keil/libercoap.lib \
                $(LIBDIR)/PLAT/lib/keil/libhttpclient.lib \
                $(LIBDIR)/PLAT/lib/keil/libiperf.lib \
                $(LIBDIR)/PLAT/lib/keil/liblfs.lib \
                $(LIBDIR)/PLAT/lib/keil/liblibcoap.lib \
                $(LIBDIR)/PLAT/lib/keil/liblwip.lib \
                $(LIBDIR)/PLAT/lib/keil/libmbedtls.lib \
                $(LIBDIR)/PLAT/lib/keil/libmqtt.lib \
                $(LIBDIR)/PLAT/lib/keil/libping.lib \
                $(LIBDIR)/PLAT/lib/keil/libpsnv.lib \
                $(LIBDIR)/PLAT/lib/keil/libsntp.lib \
                $(LIBDIR)/PLAT/lib/keil/libtinydtls.lib \
                $(LIBDIR)/PLAT/lib/keil/libstartup.lib \
                $(LIBDIR)/PLAT/lib/keil/libmiddleware_ec.lib 
               
                         

endif

ifeq ($(TOOLCHAIN),GCC)
PREBUILDLIBS += $(LIBDIR)/PLAT/lib/keil/libosa.a \
                $(LIBDIR)/PLAT/lib/keil/libdriver_private.a \
                $(LIBDIR)/PLAT/lib/keil/libmiddleware_ec_private.a


endif