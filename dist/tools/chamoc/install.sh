#!/usr/bin/env bash
CHAMOC_DIR="$(dirname "$(readlink -f "$0")")"

SUDO=${SUDO:-sudo}
PREFIX=128
CHAMOC_APP=${CHAMOC_DIR}/chamoc_test_client

unsupported_platform() {
    echo "unsupported platform" >&2
    echo "(currently supported \`uname -s\` 'Darwin' and 'Linux')" >&2
}

INTERFACE_CHECK_COUNTER=5  # 5 attempts to find usb interface

find_interface() {
    INTERFACE=$(ls -A /sys/bus/usb/drivers/cdc_ether/*/net/ 2>/dev/null)
    INTERFACE_CHECK=$(echo -n "${INTERFACE}" | head -c1 | wc -c)
    if [ "${INTERFACE_CHECK}" -eq 0 ] && [ ${INTERFACE_CHECK_COUNTER} != 0 ]; then
        # We want to have multiple opportunities to find the USB interface
        # as sometimes it can take a few seconds for it to enumerate after
        # the device has been flashed.
        sleep 1
        ((INTERFACE_CHECK_COUNTER=INTERFACE_CHECK_COUNTER-1))
        find_interface
    fi
    INTERFACE="${INTERFACE%/}"
    echo "${INTERFACE}"
}

add_addresses(){
            ${SUDO} sysctl -w net.ipv6.conf."${INTERFACE}".forwarding=1
            ${SUDO} sysctl -w net.ipv6.conf."${INTERFACE}".accept_ra=0
            echo "Start sending a nib add request"
            ${SUDO} "${CHAMOC_DIR}"/chamoc_test_client nib add "${INTERFACE}" "${NETWORK}" "${PREFIX}"
            ${SUDO} ip link set "${INTERFACE}" up
}

start_dhcpd() {
    DHCPD_PIDFILE=$(mktemp)
    ${DHCPD} -d -p "${DHCPD_PIDFILE}" "${INTERFACE}" "${NETWORK}" 2> /dev/null
}

cleanup() {
    echo "Cleaning up..."
    if [ -n "${DHCPD_PIDFILE}" ]; then
        kill "$(cat "${DHCPD_PIDFILE}")"
        rm "${DHCPD_PIDFILE}"
    fi
    trap "" INT QUIT TERM EXIT
}
echo "Waiting for network interface."

NETWORK=$2

find_interface
trap "cleanup" INT QUIT TERM EXIT

if [ -z "${INTERFACE}" ]; then
   echo "USB network interface not found"
   exit 1
fi

if [ ! -f "${CHAMOC_APP}" ]; then
    make -C "${CHAMOC_DIR}"
fi

add_addresses
if [ "$1" = "-d" ] || [ "$1" = "--use-dhcpv6" ]; then
    USE_DHCPV6=1
    shift 1
fi


if [ ${USE_DHCPV6} -eq 1 ]; then
    DHCPD="$(readlink -f "${RIOTTOOLS}/dhcpv6-pd_ia/")/dhcpv6-pd_ia.py"
    start_dhcpd
fi


rm "${CHAMOC_APP}"
echo "Connection started"
