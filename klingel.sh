#!/bin/bash

/usr/bin/gpio mode 9 down
/usr/bin/gpio mode 7 out

/usr/sbin/asterisk  -rx "core show uptime" > /dev/null
if [ $? -ne 0 ]; then
	echo "asterisk laeuft nicht"
	sleep 30
	/usr/sbin/asterisk  -rx "core show uptime" > /dev/null
	if [ $? -ne 0 ]; then
	        echo "asterisk laeuft immer noch nicht"
		exit 1
	fi
fi

while [ 1 ]; do
	# gpio wfi 9 rising
	/root/klingel/warteaufklingel
	asterisk -rx "console dial 123456@console"
done
