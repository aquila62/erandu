#!/bin/bash
./erandunorm 15.0 2.0 4096 >rwxf
cat tst.r | R -q --no-save
