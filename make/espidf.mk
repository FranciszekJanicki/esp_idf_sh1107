include make/common.mk

.PHONY: build
build:
	$(IDF) build \
		-DMAKE_PROJECT_NAME="$(PROJECT_NAME)" \
		-DIDF_BUILD_TARGET="$(ESP_IDF_TARGET)" \
		-DIDF_TARGET=$(ESP_IDF_TARGET)

.PHONY: erase-flash
erase-flash:
	esptool.py erase_flash

.PHONY: flash
flash:
	$(IDF) flash -p $(PORT)

.PHONY: monitor
monitor:
	$(IDF) -p $(PORT) monitor

.PHONY: erase-flash-monitor
erase-flash-monitor: erase-flash flash monitor

.PHONY: clean
clean:
	$(IDF) clean

.PHONY: fullclean
fullclean:
	$(IDF) fullclean
	rm -rf $(BUILD_DIR)

.PHONY: menuconfig
menuconfig:
	$(IDF) menuconfig
