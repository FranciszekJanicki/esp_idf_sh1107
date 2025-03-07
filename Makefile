include make/espidf.mk
include make/linters.mk
include make/proto.mk

.DEFAULT_GOAL = help

.PHONY: setup-usb
setup-usb:
	$(SUDO) cp 99-usb-serial.rules /etc/udev/rules.d/
	$(SUDO) service udev restart
	$(SUDO) chmod a+rw $(PORT)

.PHONY: setup
setup: setup-linters setup-proto setup-usb

.PHONY: all
all: 
	clear && make build && make erase-flash-monitor