#!/bin/bash
#
# The following are notes in BASH script form descripting how to
# decode HOTP/TOTP data using TCP/UDP ports
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

# reconstruct numeric UID from port numbers
TOTP_UID1=$(( $(( ${TOTP_PORT1} - 4096 )) * 4194304 ))
TOTP_UID2=$(( $(( ${TOTP_PORT2} - 4096 )) *   16384 ))
TOTP_UID3=$((     ${TOTP_PORT3} - 4096 ))

# reconstruct TOTP code from port numbers
TOTP_CODE1=$(( $(( ${TOTP_PORT4} - 4096 )) * 4194304 ))
TOTP_CODE2=$(( $(( ${TOTP_PORT5} - 4096 )) *   16384 ))
TOTP_CODE3=$((     ${TOTP_PORT6} - 4096 ))

# display results
printf "               %10s     %10s\n" \
       "Original" \
       "Calculated"
printf "Numeric UID:   %10s  /  %10s\n" \
       "${TOTP_UID}" \
       "$(( ${TOTP_UID1}  + ${TOTP_UID2}  + ${TOTP_UID3}  ))"
printf "TOTP Code:     %10s  /  %10s\n" \
       "${TOTP_CODE}" \
       "$(( ${TOTP_CODE1} + ${TOTP_CODE2} + ${TOTP_CODE3} ))"
printf "Encoded Ports: %5s  %5s  %5s  %5s  %5s  %5s\n" \
       ${TOTP_PORT1} \
       ${TOTP_PORT2} \
       ${TOTP_PORT3} \
       ${TOTP_PORT4} \
       ${TOTP_PORT5} \
       ${TOTP_PORT6}

# end of script
