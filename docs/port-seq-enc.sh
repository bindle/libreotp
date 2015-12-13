#!/bin/bash
#
# The following are notes in BASH script form descripting how to
# encode HOTP/TOTP data using TCP/UDP ports
#

# set parameters
TOTP_UID=${1:-$UID}
TOTP_CODE=${2:-123456}

# encode numeric UID into three port numbers
TOTP_PORT1=$(( $((     ${TOTP_UID}  / 4194304))            + 4096 ))
TOTP_PORT2=$(( $(( $(( ${TOTP_UID}  % 4194304)) / 16384 )) + 4096 ))
TOTP_PORT3=$(( $(( $(( ${TOTP_UID}  % 4194304)) % 16384 )) + 4096 ))

# encode TOTP code into three port numbers
TOTP_PORT4=$(( $((     ${TOTP_CODE} / 4194304))            + 4096 ))
TOTP_PORT5=$(( $(( $(( ${TOTP_CODE} % 4194304)) / 16384 )) + 4096 ))
TOTP_PORT6=$(( $(( $(( ${TOTP_CODE} % 4194304)) % 16384 )) + 4096 ))

# display results
printf "Numeric UID:   %s\n" ${TOTP_UID}
printf "TOTP Code:     %s\n" ${TOTP_CODE}
printf "Encoded Ports: %-5s  %-5s  %-5s  %-5s  %-5s  %-5s\n" \
       ${TOTP_PORT1} \
       ${TOTP_PORT2} \
       ${TOTP_PORT3} \
       ${TOTP_PORT4} \
       ${TOTP_PORT5} \
       ${TOTP_PORT6}

# end of script
