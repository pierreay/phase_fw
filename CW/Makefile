CW_USB=$(shell lsusb)
DEVICE_ID=$$(shell echo $CW_USB | awk '{print $4}' | sed 's/://')
BUS_ID=$$(shell echo $CW_USB | awk '{print $2}')

check:
	echo $(CW_BUS)
	@if [ "$CW_USB" != "" ]; then \
		echo "Found ChipWhisperer"; \
	else \
		echo -e "ChipWhisperer not found in host\nExiting.."; \
		exit 1; \
	fi; \
	echo $(DEVICE_ID)


docker: check
	docker run -i -t -p 8888:8888 \
		-v /dev/bus/usb/$(BUS_ID)/$(DEVICE_ID):/dev/bus/usb/$(BUS_ID)/$(DEVICE_ID) \
		--device /dev/bus/usb/$(BUS_ID)/$(DEVICE_ID) \
		-u cw \
		-v ./work:/home/cw/work \
		cw;
