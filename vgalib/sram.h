/* 
 * ATMega16 at 16MHz interfacing with the HY62256 SRAM chip.
 * See sram.h for connection details.
 * See the data sheet for the write cycle timing diagrams.
 *
 */

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

/* Port/pin definitions */

/* SRAM A0-A7 */
#define	SRAM_ADDRL_PORT		PORTB
#define	SRAM_ADDRL_DDR		DDRB

/* SRAM A8-A14 */
#define	SRAM_ADDRH_PORT		PORTA
#define	SRAM_ADDRH_DDR		DDRA

/* SRAM I/O0-I/O7 */
#define	SRAM_DATA_PORT		PORTC
#define	SRAM_DATA_PIN		PINC
#define SRAM_DATA_DDR		DDRC

/* SRAM /CE, /OE, /WE control pins */
#define SRAM_CTRL_PORT		PORTD
#define SRAM_CTRL_DDR		DDRD
#define	SRAM_CTRL_CE		7
#define SRAM_CTRL_OE		5
#define SRAM_CTRL_WE		4


/* Convenient control pin toggling macros */

#define SRAM_Deselect()	(SRAM_CTRL_PORT |= (1<<SRAM_CTRL_CE))
#define SRAM_Select()	(SRAM_CTRL_PORT &= ~(1<<SRAM_CTRL_CE))

#define SRAM_OE_High()	(SRAM_CTRL_PORT |= (1<<SRAM_CTRL_OE))
#define SRAM_OE_Low()	(SRAM_CTRL_PORT &= ~(1<<SRAM_CTRL_OE))

#define SRAM_WE_High()	(SRAM_CTRL_PORT |= (1<<SRAM_CTRL_WE))
#define SRAM_WE_Low()	(SRAM_CTRL_PORT &= ~(1<<SRAM_CTRL_WE))

/* SRAM interface functions */

/* SRAM_Init: sets up I/O for interfacing with the SRAM chip. */
void SRAM_Init(void);

/* SRAM_Write: writes 8-bit data to the 15-bit address (16th bit is ignored). */
void SRAM_Write(u8 addressh,u8 addressl, u8 data);

/* SRAM_Read: reads 8-bit data from the 15-bit address (16th bit is ignored). */
u8 SRAM_Read(u16 address);


void rect(int a1,int b1,int a2,int b2,int c);
void vga_init();
void vga_start();


