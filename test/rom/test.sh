#!/bin/bash

# Download the firmware
wget 'http://80.211.96.38/s/inc/downloads/es40-srmon/cl67srmrom.exe'

# Start AXPbox
../../build/axpbox run &
AXPBOX_PID=$!

# Wait for AXPbox to start
sleep 3

# Connect to terminal
ncat -t 127.0.0.1 21000 | tee axp.log &
NETCAT_PID=$!

# Wait for the last line of log to become P00>>>
timeout=300
while true
do
  if [ $timeout -eq 0 ]
  then
    echo "waiting for SRM prompt timed out" >&2
    exit 1
  fi

  if [ "$(tail -n 1 axp.log | tr -d '\0')" == "P00>>>"  ]
  then
    break
  fi

  sleep 1
  timeout=$(($timeout - 1))
done

kill $NETCAT_PID
kill $AXPBOX_PID
diff axp_correct.log axp.log
rm -f axp.log cl67* *.rom
