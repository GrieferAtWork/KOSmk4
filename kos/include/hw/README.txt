
bus: Bus specifications
	- pci
	- serial
	- ...

disk: Disk specifications
	- ata   (/dev/hda)
	- scsi  (/dev/sda)
	- ...

hid: Human Interface Devices
	- ps2kbd
	- ps2mouse
	- usb mouse/keyboard
	- ...

ic: InterruptController
	- apic
	- pic
	- ...

net: Network adapters
	- ne2k
	- ...

rtc: Real Time Clock
	- cmos
	- ...

timer: Programmable clock timers
	- pit
	- ...

usb: USB base controllers
	- ohci
	- uhci
	- ...
	- basic control structures
	- ...

video: Video card devices
	- vga
	- ...
