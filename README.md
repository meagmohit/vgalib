# vgalib
## A MicroController (ATMEGA 16) based Graphic Driver design to display on VGA protocol

Codes for turning ATMEGA16 uC to a Graphic Driver for VGA protocol 
This repository includes hardware design and codes

***

##### Compiling Details
On Command Line, `make all' 

***

##### displayImage
Displays any 50x120 image on CRT Monitor whose Image data is written in *vga_symbol_tbl.h* file. For any new image, replace with new image data which should be organised first all horizontal (x) pixels of vertical line (y) then for next line all horizontal (x) pixels. Image data should be either in binary format or digital format. 
Colour values are describes here--


brg      // colours


reading where not written-- white response

000-


001-blue


010-red


100-green


011-pink


101-sky


110-yellow


111-white

**Image Data example:-**
**In Binary:-**
0b00000010,0b00000001,so on...

**In digital:-**
1,4,.. and so on..

***

#### vgalib
Sample VGA library

***

#### pingpong
A basic demonstration of designing Ping Pong game using vgalib

***

> P.S. The codes were written in 2011, and released in public in 2018
