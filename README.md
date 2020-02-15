# amd_vbios_tools
```
Contains tools for modification of AMD / ATI video bios
Purpose of this repository was for analyzing the RX-570 "EtheCoin" mining card
to allow it to work with windows and linux to run OpenCL "BOINC" applications
OEM: SAPPHIRE POLARIS20_C940_XL_D5_4GB_HY
See doc folder for pictures and info

atiflash:  both windows and linux versions
	   windows location is techpowerup.com/download/ati-atiflash
	   linux version required searching to find it so use it at risk

biosmod: windows only (Polaris Bios Editor) is located at
         github.com/caa82437/PolarisBiosEditor

amdinfo: linux only, copyed to my archive but original is at
	 github.com/ystarnaud/amdmeminfo

ROM append: This simple program expand 256k bios to 512k by adding 0xff 
	    to the existing 256k bios.  rom_256_to_512.cpp
original bios: 113_eth_sam
```