#Author        : Justin Danglade
#Student ID    : 4552415
#Course        : COP4338
#Section       : U04
#Instructor    : William Feild
#Due Date      : November 6, 2018

# Create variables
App_1 = ValidateMain
App_2 = ConvertMain
HdrFile = datemanip.h
CCo = gcc -o
Src_1 = validateMain.c
Src_2 = convertMain.c
Src_3 = datemanip.c

# Enable multiple build targets
all: $(App_1) $(App_2)

# Make instructions
# Build executable files
$(App_1): $(Src_1) $(HdrFile)
	$(CCo) $(App_1) $(Src_1) $(Src_3)
$(App_2): $(Src_2) $(Src_3) $(HdrFile)
	$(CCo) $(App_2) $(Src_2) $(Src_3)
clean:
	rm *.o
