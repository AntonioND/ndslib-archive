@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ code to capture the ARM9 without making any assumptions about the
@ code currently running on it (other than that it doesn't overwrite
@ the first 30 or 40 bytes of main RAM in the time it takes me to
@ write them there).  Should work 99+% of the time.
@ -- joat
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.arm
.section	".text"
.align	4

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global CallARM7
.func CallARM7
CallARM7:
		mov	r0, #0x02380000
		bx	r0
.endfunc


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.global CapARM9
.func CapARM9

@ r0 is RAM dest address
@ r1 is copy source address
@ r2 is target address
@ r3 is data being moved

CapARM9:	mov	r0, #0x02000000		@ Fill RAM with copy loop
		ldr	r1, =Waiter
		ldr	r2, =EndWaiter
Copier:		ldr	r3, [r1], #4
		str	r3, [r0], #4
		cmp	r1, r2
		bne	Copier

		ldr	r2, =Mover		@ Fill RAM with mover
		ldr	r3, [r2]
		mov	r2, #0x02300000
Filler:		str	r3, [r0], #4
		cmp	r0, r2
		bne	Filler

		bx	lr

@ code to copy (doing constants manually to avoid having to copy a pool)
Mover:		mov	pc, #0x02000000

Waiter:		mov	r1, #0x02000		@ disable DTCM and protection unit
		orr	r1, r1, #0x78;
		mcr	p15, 0, r1, c1, c0

		mov	r0, #0x00800000
		orr	r0, r0, #0xA
		mcr	p15, 0, r0, c9, c1	@ TCM base = 0x00800*4096, size = 16 KB
		mrc	p15, 0, r0, c1, c0	@ reading cp15.c1, then throwing away r0

		orr	r1, r1, #0x10000
		mcr	p15, 0, r1, c1, c0	@ cp15.c1 = 0x00012078;

		mov	r0, #0x02300000
		mov	r1, #0xC000
		orr	r1, r1, #0x00DE		@ r1 = 0xC0DE
		strh	r1, [r0]		@ mem_sig = 0xC0DE
		strh	r1, [r0]		@ mem_sig = 0xC0DE
		strh	r1, [r0]		@ mem_sig = 0xC0DE
		strh	r1, [r0]		@ mem_sig = 0xC0DE

		mov	r2, #0xD000
		orr	r2, r2, #0x000D		@ r2 = 0xD00D
		mov	r0, #0x02300000
Looper:		ldrh	r1, [r0]		@ wait until sig = 0xD00D
		cmp	r1, r2
		bne	Looper

		mov	r0, #0x02000000		@ jump to 0x02004000
		add	r0, r0, #0x4000
		bx	r0
EndWaiter:

.pool
.endfunc

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.end
