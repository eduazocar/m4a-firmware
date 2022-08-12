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
USEMODULE += dhcpv6_relay
USEMODULE += gnrc_dhcpv6_client_6lbr
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

CHAMOC_DIR ?= ../../dist/tools/chamoc
NETWORK := 2001:db8:1::/64
USE_DHCPV6 ?= 1

ifeq (1,$(USE_DHCPV6))
  FLAGS_EXTRAS += --use-dhcpv6
endif

install:
	./${CHAMOC_DIR}/install.sh ${FLAGS_EXTRAS} ${NETWORK}
uninstall:
	./${CHAMOC_DIR}/uninstall.sh ${FLAGS_EXTRAS} ${NETWORK} 


include $(RIOTBASE)/Makefile.include
