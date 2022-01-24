INCLUDE_DIR += -I./lib

SRC += ./lib/*.c

OPT = -w

.PHONY: rencode

rencode:
	gcc rencode.c $(INCLUDE_DIR) $(SRC) -o rencode $(OPT)
	./rencode

.PHONY: rdecode

rdecode:
	gcc rdecode.c $(INCLUDE_DIR) $(SRC) -o rdecode $(OPT)
	./rdecode

.PHONY: rder_encode

rder_encode:
	gcc rder_encode.c $(INCLUDE_DIR) $(SRC) -o rder_encode $(OPT)
	./rder_encode

.PHONY: rber_decode

rber_decode:
	gcc rber_decode.c $(INCLUDE_DIR) $(SRC) -o rber_decode $(OPT)
	./rber_decode
