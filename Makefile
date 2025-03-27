include make/espidf.mk
include make/linters.mk
include make/proto.mk
include make/common.mk

.PHONY: setup-usb
setup-usb:
	$(SUDO) cp 99-usb-serial.rules /etc/udev/rules.d/
	$(SUDO) service udev restart
	$(SUDO) chmod a+rw $(PORT)

.PHONY: add-utility
add-utility:
	git submodule add -f https://github.com/franciszekjanicki/esp32-utility.git ${UTILITY_DIR}

.PHONY: update-utility
update-utility:
	git submodule update --init --recursive

.PHONY: remove-utility
remove-utility:
	git submodule deinit -f ${UTILITY_DIR}
	git rm -rf ${UTILITY_DIR}
	rm -rf ${UTILITY_DIR}
	rm -rf .git/modules/app/utility

.PHONY: setup
setup: setup-linters setup-external setup-proto setup-usb

.PHONY: all
all: 
	clear && make build && make erase-flash-monitor