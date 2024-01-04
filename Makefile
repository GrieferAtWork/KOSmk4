# Copyright (c) 2019-2024 Griefer@Work
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgement (see the following) in the product
#    documentation is required:
#    Portions Copyright (c) 2019-2024 Griefer@Work
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.

### Collection of helpful commands for working with KOS
ifeq ($(OS),Windows_NT)
EXE := .exe
else
EXE :=
endif

SH     := bash
ROOT   := .
DEEMON := $(ROOT)/binutils/deemon/deemon$(EXE)
BIN    := $(ROOT)/bin/$(TARGET)-kos-$(CONFIG)

ifdef TARGET
TARGET_ARG = --target=$(TARGET)
else
TARGET_ARG =
TARGET = $(shell TGT="$$("$(DEEMON)" magic.dee --target 2>/dev/null)"; echo "$${TGT%%-*}")
endif
ifdef CONFIG
CONFIG_ARG = --config=$(CONFIG)
else
CONFIG_ARG =
CONFIG = $(shell TGT="$$("$(DEEMON)" magic.dee --target 2>/dev/null)"; echo "$${TGT##*-}")
endif

print-selected-target-info:
	@echo TARGET: $(TARGET)
	@echo CONFIG: $(CONFIG)

# KOS
launch:
	"$(DEEMON)" "$(ROOT)/magic.dee" $(TARGET_ARG) $(CONFIG_ARG)
build:
	"$(DEEMON)" "$(ROOT)/magic.dee" $(TARGET_ARG) $(CONFIG_ARG) --build-only
run:
	"$(DEEMON)" "$(ROOT)/magic.dee" $(TARGET_ARG) $(CONFIG_ARG) --run-only
.PHONY: launch build run
.DEFAULT_GOAL := launch


# Formatting
autom8:
	"$(DEEMON)" kos/misc/libgen/autom8.dee kos/**
.PHONY: autom8


# Toolchain
toolchain:
	"$(SH)" "$(ROOT)/kos/misc/make_toolchain.sh" $(TARGET)-kos
.PHONY: toolchain


# Important utilities
busybox:
	"$(SH)" "$(ROOT)/kos/misc/make_utility.sh" $(TARGET) busybox
.PHONY: busybox


# Code generation
headers:
	"$(DEEMON)" kos/misc/magicgenerator/generate_headers.dee
syscalls:
	"$(DEEMON)" kos/misc/magicgenerator/generate_syscalls.dee
	"$(DEEMON)" kos/misc/magicgenerator/generate_syscalls.dee $(TARGET)
.PHONY: headers syscalls



# Install to custom $DESTDIR
install-system:
	"$(DEEMON)" "$(ROOT)/magic.dee" $(TARGET_ARG) $(CONFIG_ARG) --install-sh | "$(SH)"
.PHONY: install-system
install-%:
	@UTILITY_NAME="$@"; \
		"$(SH)" "$(ROOT)/kos/misc/make_utility.sh" --install-sh --recursive \
			$(TARGET) $${UTILITY_NAME:8} | "$(SH)"
.PHONY: install-%



# Misc script invocations
vs-proj:
	"$(DEEMON)" kos/misc/build/make-vs-proj.dee
.PHONY: vs-proj

ifeq ($(MAKECMDGOALS),me a sandwich)
.PHONY: $(MAKECMDGOALS)
me a:
	@:
sandwich:
	@if [[ $$(id -u) == 0 ]]; then \
		echo "Okay"; \
	else \
		echo "What? Make it yourself"; \
	fi
endif
