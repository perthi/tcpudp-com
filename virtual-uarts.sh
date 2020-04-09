#!/bin/bash
socat -lf    uarts.txt  -d -d pty,raw,echo=0 pty,raw,echo=0 &
cat  uarts.txt
