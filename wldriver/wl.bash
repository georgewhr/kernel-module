#!/bin/bash
sudo rmmod b43
sudo rmmod bcma
sudo rmmod ssb
sudo modprobe lib80211
sudo insmod wl.ko
