# name of the application
APPLICATION = border_router

include $(CURDIR)/../Makefile.common

USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps

USEMODULE += border_router
USEMODULE += chamos
USEMODULE += rpl_protocol
USEMODULE += netstats_l2
USEMODULE += netstats_ipv6

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1
ISP ?= 0
ifeq (${ISP}, 1)
	CFLAGS += -DISP=1
endif

HOST_IPV6 ?= 2001:db8::1
USB_IPV6 ?= ${CONFIG_ADDRESS_IPV6_WIRED}
TERMPROG ?= sudo sh ${BORDER_ROUTER_USBTOOL}/autoconfigure.sh
TERMFLAGS ?= $(HOST_IPV6) $(PORT) ${RIOTTOOLS} ${USB_IPV6}

BORDER_ROUTER_USBTOOL ?= $(RIOTBASE)/../dist/tools/usb-cdc-ecm
CHAMOC_DIR ?= ../../dist/tools/chamoc

install:
	./${CHAMOC_DIR}/install.sh ${HOST_IPV6} ${USB_IPV6}
uninstall:
	./${CHAMOC_DIR}/uninstall.sh ${HOST_IPV6} ${USB_IPV6}


include $(RIOTBASE)/Makefile.include
