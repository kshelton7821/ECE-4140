	.cpu cortex-m4
	.eabi_attribute 27, 1
	.eabi_attribute 28, 1
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 1
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"m1b.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.delay_loop,"ax",%progbits
	.align	1
	.arch armv7e-m
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv4-sp-d16
	.type	delay_loop, %function
delay_loop:
.LVL0:
.LFB4:
	.file 1 "m1b.c"
	.loc 1 69 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 70 5 view .LVU1
	.loc 1 70 10 is_stmt 0 view .LVU2
	b	.L2
.L3:
	.loc 1 72 8 is_stmt 1 view .LVU3
	.syntax unified
@ 72 "m1b.c" 1
	nop
@ 0 "" 2
	.loc 1 73 8 view .LVU4
	.loc 1 73 13 is_stmt 0 view .LVU5
	.thumb
	.syntax unified
	subs	r0, r0, #1
.LVL1:
.L2:
	.loc 1 70 10 is_stmt 1 view .LVU6
	cmp	r0, #0
	bgt	.L3
	.loc 1 75 1 is_stmt 0 view .LVU7
	bx	lr
	.cfi_endproc
.LFE4:
	.size	delay_loop, .-delay_loop
	.section	.text.clock_setup,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv4-sp-d16
	.type	clock_setup, %function
clock_setup:
.LFB3:
	.loc 1 34 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
.LCFI0:
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
	sub	sp, sp, #8
.LCFI1:
	.cfi_def_cfa_offset 16
	.loc 1 36 2 view .LVU9
	movs	r0, #2
	bl	rcc_osc_on
.LVL2:
	.loc 1 39 2 view .LVU10
	bl	flash_prefetch_enable
.LVL3:
	.loc 1 40 2 view .LVU11
	movs	r0, #4
	bl	flash_set_ws
.LVL4:
	.loc 1 41 2 view .LVU12
	bl	flash_dcache_enable
.LVL5:
	.loc 1 42 2 view .LVU13
	bl	flash_icache_enable
.LVL6:
	.loc 1 45 2 view .LVU14
	movs	r4, #0
	str	r4, [sp, #4]
	str	r4, [sp]
	mov	r3, r4
	movs	r2, #40
	movs	r1, #4
	movs	r0, #2
	bl	rcc_set_main_pll
.LVL7:
	.loc 1 46 2 view .LVU15
	mov	r0, r4
	bl	rcc_osc_on
.LVL8:
	.loc 1 48 2 view .LVU16
	mov	r0, r4
	bl	rcc_wait_for_osc_ready
.LVL9:
	.loc 1 50 2 view .LVU17
	mov	r0, #2432
	bl	rcc_periph_clock_enable
.LVL10:
	.loc 1 52 2 view .LVU18
	movs	r0, #3
	bl	rcc_set_sysclk_source
.LVL11:
	.loc 1 53 2 view .LVU19
	mov	r0, r4
	bl	rcc_wait_for_sysclk_status
.LVL12:
	.loc 1 63 2 view .LVU20
	.loc 1 63 20 is_stmt 0 view .LVU21
	ldr	r3, .L6
	ldr	r2, .L6+4
	str	r3, [r2]
	.loc 1 64 2 is_stmt 1 view .LVU22
	.loc 1 64 21 is_stmt 0 view .LVU23
	ldr	r2, .L6+8
	str	r3, [r2]
	.loc 1 65 2 is_stmt 1 view .LVU24
	.loc 1 65 21 is_stmt 0 view .LVU25
	ldr	r2, .L6+12
	str	r3, [r2]
	.loc 1 66 1 view .LVU26
	add	sp, sp, #8
.LCFI2:
	.cfi_def_cfa_offset 8
	@ sp needed
	pop	{r4, pc}
.L7:
	.align	2
.L6:
	.word	80000000
	.word	rcc_ahb_frequency
	.word	rcc_apb1_frequency
	.word	rcc_apb2_frequency
	.cfi_endproc
.LFE3:
	.size	clock_setup, .-clock_setup
	.section	.text.main,"ax",%progbits
	.align	1
	.global	main
	.syntax unified
	.thumb
	.thumb_func
	.fpu fpv4-sp-d16
	.type	main, %function
main:
.LFB5:
	.loc 1 78 1 is_stmt 1 view -0
	.cfi_startproc
	@ Volatile: function does not return.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
.LCFI3:
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	.cfi_offset 14, -4
	.loc 1 81 2 view .LVU28
	bl	clock_setup
.LVL13:
	.loc 1 83 2 view .LVU29
	movs	r3, #32
	movs	r2, #1
	mov	r1, r2
	mov	r0, #1207959552
	bl	gpio_mode_setup
.LVL14:
.L9:
	.loc 1 85 2 discriminator 1 view .LVU30
	.loc 1 88 3 discriminator 1 view .LVU31
	movs	r1, #32
	mov	r0, #1207959552
	bl	gpio_toggle
.LVL15:
	.loc 1 90 3 discriminator 1 view .LVU32
	ldr	r0, .L11
	bl	delay_loop
.LVL16:
	.loc 1 85 7 discriminator 1 view .LVU33
	b	.L9
.L12:
	.align	2
.L11:
	.word	400000
	.cfi_endproc
.LFE5:
	.size	main, .-main
	.text
.Letext0:
	.file 2 "/usr/include/newlib/machine/_default_types.h"
	.file 3 "/usr/include/newlib/sys/_stdint.h"
	.file 4 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/l4/rcc.h"
	.file 5 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/gpio_common_f234.h"
	.file 6 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/gpio_common_all.h"
	.file 7 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/flash_common_all.h"
	.file 8 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/flash_common_idcache.h"
	.file 9 "/home/kshelton/Documents/GitHub/libopencm3/include/libopencm3/stm32/common/rcc_common_all.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x6b6
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF161
	.byte	0xc
	.4byte	.LASF162
	.4byte	.LASF163
	.4byte	.Ldebug_ranges0+0
	.4byte	0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF0
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.4byte	.LASF1
	.uleb128 0x3
	.byte	0x8
	.byte	0x4
	.4byte	.LASF2
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.4byte	.LASF3
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF4
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.4byte	.LASF5
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.4byte	.LASF6
	.uleb128 0x4
	.4byte	.LASF8
	.byte	0x2
	.byte	0x4d
	.byte	0x12
	.4byte	0x6d
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.4byte	.LASF7
	.uleb128 0x4
	.4byte	.LASF9
	.byte	0x2
	.byte	0x4f
	.byte	0x1b
	.4byte	0x80
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF10
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.4byte	.LASF11
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF12
	.uleb128 0x4
	.4byte	.LASF13
	.byte	0x3
	.byte	0x2c
	.byte	0x13
	.4byte	0x61
	.uleb128 0x4
	.4byte	.LASF14
	.byte	0x3
	.byte	0x30
	.byte	0x14
	.4byte	0x74
	.uleb128 0x5
	.4byte	.LASF15
	.byte	0x4
	.2byte	0x301
	.byte	0x11
	.4byte	0xa1
	.byte	0x1
	.byte	0x1
	.uleb128 0x5
	.4byte	.LASF16
	.byte	0x4
	.2byte	0x302
	.byte	0x11
	.4byte	0xa1
	.byte	0x1
	.byte	0x1
	.uleb128 0x5
	.4byte	.LASF17
	.byte	0x4
	.2byte	0x303
	.byte	0x11
	.4byte	0xa1
	.byte	0x1
	.byte	0x1
	.uleb128 0x6
	.4byte	.LASF25
	.byte	0x7
	.byte	0x1
	.4byte	0x4c
	.byte	0x4
	.2byte	0x309
	.byte	0x6
	.4byte	0x118
	.uleb128 0x7
	.4byte	.LASF18
	.byte	0
	.uleb128 0x7
	.4byte	.LASF19
	.byte	0x1
	.uleb128 0x7
	.4byte	.LASF20
	.byte	0x2
	.uleb128 0x7
	.4byte	.LASF21
	.byte	0x3
	.uleb128 0x7
	.4byte	.LASF22
	.byte	0x4
	.uleb128 0x7
	.4byte	.LASF23
	.byte	0x5
	.uleb128 0x7
	.4byte	.LASF24
	.byte	0x6
	.byte	0
	.uleb128 0x6
	.4byte	.LASF26
	.byte	0x7
	.byte	0x2
	.4byte	0x5a
	.byte	0x4
	.2byte	0x310
	.byte	0x6
	.4byte	0x474
	.uleb128 0x8
	.4byte	.LASF27
	.2byte	0x910
	.uleb128 0x8
	.4byte	.LASF28
	.2byte	0x90c
	.uleb128 0x8
	.4byte	.LASF29
	.2byte	0x908
	.uleb128 0x8
	.4byte	.LASF30
	.2byte	0x901
	.uleb128 0x8
	.4byte	.LASF31
	.2byte	0x900
	.uleb128 0x8
	.4byte	.LASF32
	.2byte	0x992
	.uleb128 0x8
	.4byte	.LASF33
	.2byte	0x990
	.uleb128 0x8
	.4byte	.LASF34
	.2byte	0x98d
	.uleb128 0x8
	.4byte	.LASF35
	.2byte	0x98d
	.uleb128 0x8
	.4byte	.LASF36
	.2byte	0x98c
	.uleb128 0x8
	.4byte	.LASF37
	.2byte	0x987
	.uleb128 0x8
	.4byte	.LASF38
	.2byte	0x986
	.uleb128 0x8
	.4byte	.LASF39
	.2byte	0x985
	.uleb128 0x8
	.4byte	.LASF40
	.2byte	0x984
	.uleb128 0x8
	.4byte	.LASF41
	.2byte	0x983
	.uleb128 0x8
	.4byte	.LASF42
	.2byte	0x982
	.uleb128 0x8
	.4byte	.LASF43
	.2byte	0x981
	.uleb128 0x8
	.4byte	.LASF44
	.2byte	0x980
	.uleb128 0x8
	.4byte	.LASF45
	.2byte	0xa08
	.uleb128 0x8
	.4byte	.LASF46
	.2byte	0xa00
	.uleb128 0x8
	.4byte	.LASF47
	.2byte	0xb1f
	.uleb128 0x8
	.4byte	.LASF48
	.2byte	0xb1e
	.uleb128 0x8
	.4byte	.LASF49
	.2byte	0xb1d
	.uleb128 0x8
	.4byte	.LASF50
	.2byte	0xb1c
	.uleb128 0x8
	.4byte	.LASF51
	.2byte	0xb1a
	.uleb128 0x8
	.4byte	.LASF52
	.2byte	0xb1a
	.uleb128 0x8
	.4byte	.LASF53
	.2byte	0xb19
	.uleb128 0x8
	.4byte	.LASF54
	.2byte	0xb18
	.uleb128 0x8
	.4byte	.LASF55
	.2byte	0xb17
	.uleb128 0x8
	.4byte	.LASF56
	.2byte	0xb16
	.uleb128 0x8
	.4byte	.LASF57
	.2byte	0xb15
	.uleb128 0x8
	.4byte	.LASF58
	.2byte	0xb14
	.uleb128 0x8
	.4byte	.LASF59
	.2byte	0xb13
	.uleb128 0x8
	.4byte	.LASF60
	.2byte	0xb12
	.uleb128 0x8
	.4byte	.LASF61
	.2byte	0xb11
	.uleb128 0x8
	.4byte	.LASF62
	.2byte	0xb0f
	.uleb128 0x8
	.4byte	.LASF63
	.2byte	0xb0e
	.uleb128 0x8
	.4byte	.LASF64
	.2byte	0xb09
	.uleb128 0x8
	.4byte	.LASF65
	.2byte	0xb05
	.uleb128 0x8
	.4byte	.LASF66
	.2byte	0xb04
	.uleb128 0x8
	.4byte	.LASF67
	.2byte	0xb03
	.uleb128 0x8
	.4byte	.LASF68
	.2byte	0xb02
	.uleb128 0x8
	.4byte	.LASF69
	.2byte	0xb01
	.uleb128 0x8
	.4byte	.LASF70
	.2byte	0xb00
	.uleb128 0x8
	.4byte	.LASF71
	.2byte	0xb85
	.uleb128 0x8
	.4byte	.LASF72
	.2byte	0xb82
	.uleb128 0x8
	.4byte	.LASF73
	.2byte	0xb80
	.uleb128 0x8
	.4byte	.LASF74
	.2byte	0xc18
	.uleb128 0x8
	.4byte	.LASF75
	.2byte	0xc16
	.uleb128 0x8
	.4byte	.LASF76
	.2byte	0xc15
	.uleb128 0x8
	.4byte	.LASF77
	.2byte	0xc12
	.uleb128 0x8
	.4byte	.LASF78
	.2byte	0xc11
	.uleb128 0x8
	.4byte	.LASF79
	.2byte	0xc10
	.uleb128 0x8
	.4byte	.LASF80
	.2byte	0xc0e
	.uleb128 0x8
	.4byte	.LASF81
	.2byte	0xc0d
	.uleb128 0x8
	.4byte	.LASF82
	.2byte	0xc0c
	.uleb128 0x8
	.4byte	.LASF83
	.2byte	0xc0b
	.uleb128 0x8
	.4byte	.LASF84
	.2byte	0xc0a
	.uleb128 0x8
	.4byte	.LASF85
	.2byte	0xc07
	.uleb128 0x8
	.4byte	.LASF86
	.2byte	0xc00
	.uleb128 0x8
	.4byte	.LASF87
	.2byte	0xd10
	.uleb128 0x8
	.4byte	.LASF88
	.2byte	0xd0c
	.uleb128 0x8
	.4byte	.LASF89
	.2byte	0xd09
	.uleb128 0x8
	.4byte	.LASF90
	.2byte	0xd08
	.uleb128 0x8
	.4byte	.LASF91
	.2byte	0xd01
	.uleb128 0x8
	.4byte	.LASF92
	.2byte	0xd00
	.uleb128 0x8
	.4byte	.LASF93
	.2byte	0xd92
	.uleb128 0x8
	.4byte	.LASF94
	.2byte	0xd90
	.uleb128 0x8
	.4byte	.LASF95
	.2byte	0xd8d
	.uleb128 0x8
	.4byte	.LASF96
	.2byte	0xd8d
	.uleb128 0x8
	.4byte	.LASF97
	.2byte	0xd8c
	.uleb128 0x8
	.4byte	.LASF98
	.2byte	0xd89
	.uleb128 0x8
	.4byte	.LASF99
	.2byte	0xd87
	.uleb128 0x8
	.4byte	.LASF100
	.2byte	0xd86
	.uleb128 0x8
	.4byte	.LASF101
	.2byte	0xd85
	.uleb128 0x8
	.4byte	.LASF102
	.2byte	0xd84
	.uleb128 0x8
	.4byte	.LASF103
	.2byte	0xd83
	.uleb128 0x8
	.4byte	.LASF104
	.2byte	0xd82
	.uleb128 0x8
	.4byte	.LASF105
	.2byte	0xd81
	.uleb128 0x8
	.4byte	.LASF106
	.2byte	0xd80
	.uleb128 0x8
	.4byte	.LASF107
	.2byte	0xe08
	.uleb128 0x8
	.4byte	.LASF108
	.2byte	0xe00
	.uleb128 0x8
	.4byte	.LASF109
	.2byte	0xb1f
	.uleb128 0x8
	.4byte	.LASF110
	.2byte	0xb1e
	.uleb128 0x8
	.4byte	.LASF111
	.2byte	0xb1d
	.uleb128 0x8
	.4byte	.LASF112
	.2byte	0xb1c
	.uleb128 0x8
	.4byte	.LASF113
	.2byte	0xb1a
	.uleb128 0x8
	.4byte	.LASF114
	.2byte	0xb19
	.uleb128 0x8
	.4byte	.LASF115
	.2byte	0xb17
	.uleb128 0x8
	.4byte	.LASF116
	.2byte	0xb16
	.uleb128 0x8
	.4byte	.LASF117
	.2byte	0xb15
	.uleb128 0x8
	.4byte	.LASF118
	.2byte	0xb14
	.uleb128 0x8
	.4byte	.LASF119
	.2byte	0xb13
	.uleb128 0x8
	.4byte	.LASF120
	.2byte	0xb12
	.uleb128 0x8
	.4byte	.LASF121
	.2byte	0xb11
	.uleb128 0x8
	.4byte	.LASF122
	.2byte	0xb0f
	.uleb128 0x8
	.4byte	.LASF123
	.2byte	0xb0e
	.uleb128 0x8
	.4byte	.LASF124
	.2byte	0xb0b
	.uleb128 0x8
	.4byte	.LASF125
	.2byte	0xb09
	.uleb128 0x8
	.4byte	.LASF126
	.2byte	0xb05
	.uleb128 0x8
	.4byte	.LASF127
	.2byte	0xb04
	.uleb128 0x8
	.4byte	.LASF128
	.2byte	0xb03
	.uleb128 0x8
	.4byte	.LASF129
	.2byte	0xb02
	.uleb128 0x8
	.4byte	.LASF130
	.2byte	0xb01
	.uleb128 0x8
	.4byte	.LASF131
	.2byte	0xb00
	.uleb128 0x8
	.4byte	.LASF132
	.2byte	0xb85
	.uleb128 0x8
	.4byte	.LASF133
	.2byte	0xb82
	.uleb128 0x8
	.4byte	.LASF134
	.2byte	0xb80
	.uleb128 0x8
	.4byte	.LASF135
	.2byte	0xc18
	.uleb128 0x8
	.4byte	.LASF136
	.2byte	0xc16
	.uleb128 0x8
	.4byte	.LASF137
	.2byte	0xc15
	.uleb128 0x8
	.4byte	.LASF138
	.2byte	0xc12
	.uleb128 0x8
	.4byte	.LASF139
	.2byte	0xc11
	.uleb128 0x8
	.4byte	.LASF140
	.2byte	0xc10
	.uleb128 0x8
	.4byte	.LASF141
	.2byte	0xc0e
	.uleb128 0x8
	.4byte	.LASF142
	.2byte	0xc0d
	.uleb128 0x8
	.4byte	.LASF143
	.2byte	0xc0c
	.uleb128 0x8
	.4byte	.LASF144
	.2byte	0xc0b
	.uleb128 0x8
	.4byte	.LASF145
	.2byte	0xc0a
	.uleb128 0x8
	.4byte	.LASF146
	.2byte	0xc00
	.byte	0
	.uleb128 0x9
	.byte	0x1
	.4byte	.LASF164
	.byte	0x1
	.byte	0x4d
	.byte	0x5
	.byte	0x1
	.4byte	0x29
	.4byte	.LFB5
	.4byte	.LFE5
	.4byte	.LLST2
	.byte	0x1
	.4byte	0x4f0
	.uleb128 0xa
	.4byte	.LVL13
	.4byte	0x51e
	.uleb128 0xb
	.4byte	.LVL14
	.4byte	0x60c
	.4byte	0x4c1
	.uleb128 0xc
	.byte	0x1
	.byte	0x50
	.byte	0x3
	.byte	0x42
	.byte	0x4a
	.byte	0x24
	.uleb128 0xc
	.byte	0x1
	.byte	0x51
	.byte	0x1
	.byte	0x31
	.uleb128 0xc
	.byte	0x1
	.byte	0x52
	.byte	0x1
	.byte	0x31
	.uleb128 0xc
	.byte	0x1
	.byte	0x53
	.byte	0x2
	.byte	0x8
	.byte	0x20
	.byte	0
	.uleb128 0xb
	.4byte	.LVL15
	.4byte	0x61b
	.4byte	0x4dc
	.uleb128 0xc
	.byte	0x1
	.byte	0x50
	.byte	0x3
	.byte	0x42
	.byte	0x4a
	.byte	0x24
	.uleb128 0xc
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x8
	.byte	0x20
	.byte	0
	.uleb128 0xd
	.4byte	.LVL16
	.4byte	0x4f0
	.uleb128 0xc
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0xc
	.4byte	0x61a80
	.byte	0
	.byte	0
	.uleb128 0xe
	.4byte	.LASF147
	.byte	0x1
	.byte	0x44
	.byte	0xd
	.byte	0x1
	.4byte	.LFB4
	.4byte	.LFE4
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x51e
	.uleb128 0xf
	.4byte	.LASF165
	.byte	0x1
	.byte	0x44
	.byte	0x20
	.4byte	0x95
	.4byte	.LLST0
	.4byte	.LVUS0
	.byte	0
	.uleb128 0x10
	.4byte	.LASF148
	.byte	0x1
	.byte	0x21
	.byte	0xd
	.byte	0x1
	.4byte	.LFB3
	.4byte	.LFE3
	.4byte	.LLST1
	.byte	0x1
	.4byte	0x60c
	.uleb128 0xb
	.4byte	.LVL2
	.4byte	0x629
	.4byte	0x54b
	.uleb128 0xc
	.byte	0x1
	.byte	0x50
	.byte	0x1
	.byte	0x32
	.byte	0
	.uleb128 0xa
	.4byte	.LVL3
	.4byte	0x638
	.uleb128 0xb
	.4byte	.LVL4
	.4byte	0x646
	.4byte	0x567
	.uleb128 0xc
	.byte	0x1
	.byte	0x50
	.byte	0x1
	.byte	0x34
	.byte	0
	.uleb128 0xa
	.4byte	.LVL5
	.4byte	0x654
	.uleb128 0xa
	.4byte	.LVL6
	.4byte	0x662
	.uleb128 0xb
	.4byte	.LVL7
	.4byte	0x670
	.4byte	0x5ab
	.uleb128 0xc
	.byte	0x1
	.byte	0x50
	.byte	0x1
	.byte	0x32
	.uleb128 0xc
	.byte	0x1
	.byte	0x51
	.byte	0x1
	.byte	0x34
	.uleb128 0xc
	.byte	0x1
	.byte	0x52
	.byte	0x2
	.byte	0x8
	.byte	0x28
	.uleb128 0xc
	.byte	0x1
	.byte	0x53
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0xc
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0xc
	.byte	0x2
	.byte	0x7d
	.sleb128 4
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.byte	0
	.uleb128 0xb
	.4byte	.LVL8
	.4byte	0x629
	.4byte	0x5bf
	.uleb128 0xc
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.byte	0
	.uleb128 0xb
	.4byte	.LVL9
	.4byte	0x67f
	.4byte	0x5d3
	.uleb128 0xc
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.byte	0
	.uleb128 0xb
	.4byte	.LVL10
	.4byte	0x68d
	.4byte	0x5e8
	.uleb128 0xc
	.byte	0x1
	.byte	0x50
	.byte	0x3
	.byte	0xa
	.2byte	0x980
	.byte	0
	.uleb128 0xb
	.4byte	.LVL11
	.4byte	0x69b
	.4byte	0x5fb
	.uleb128 0xc
	.byte	0x1
	.byte	0x50
	.byte	0x1
	.byte	0x33
	.byte	0
	.uleb128 0xd
	.4byte	.LVL12
	.4byte	0x6aa
	.uleb128 0xc
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x11
	.byte	0x1
	.byte	0x1
	.4byte	.LASF149
	.4byte	.LASF149
	.byte	0x5
	.2byte	0x118
	.byte	0x6
	.uleb128 0x12
	.byte	0x1
	.byte	0x1
	.4byte	.LASF150
	.4byte	.LASF150
	.byte	0x6
	.byte	0x4d
	.byte	0x6
	.uleb128 0x11
	.byte	0x1
	.byte	0x1
	.4byte	.LASF151
	.4byte	.LASF151
	.byte	0x4
	.2byte	0x3f4
	.byte	0x6
	.uleb128 0x12
	.byte	0x1
	.byte	0x1
	.4byte	.LASF152
	.4byte	.LASF152
	.byte	0x7
	.byte	0x29
	.byte	0x6
	.uleb128 0x12
	.byte	0x1
	.byte	0x1
	.4byte	.LASF153
	.4byte	.LASF153
	.byte	0x7
	.byte	0x3b
	.byte	0x6
	.uleb128 0x12
	.byte	0x1
	.byte	0x1
	.4byte	.LASF154
	.4byte	.LASF154
	.byte	0x8
	.byte	0x27
	.byte	0x6
	.uleb128 0x12
	.byte	0x1
	.byte	0x1
	.4byte	.LASF155
	.4byte	.LASF155
	.byte	0x8
	.byte	0x2d
	.byte	0x6
	.uleb128 0x11
	.byte	0x1
	.byte	0x1
	.4byte	.LASF156
	.4byte	.LASF156
	.byte	0x4
	.2byte	0x3fd
	.byte	0x6
	.uleb128 0x12
	.byte	0x1
	.byte	0x1
	.4byte	.LASF157
	.4byte	.LASF157
	.byte	0x9
	.byte	0x44
	.byte	0x6
	.uleb128 0x12
	.byte	0x1
	.byte	0x1
	.4byte	.LASF158
	.4byte	.LASF158
	.byte	0x9
	.byte	0x2e
	.byte	0x6
	.uleb128 0x11
	.byte	0x1
	.byte	0x1
	.4byte	.LASF159
	.4byte	.LASF159
	.byte	0x4
	.2byte	0x3f8
	.byte	0x6
	.uleb128 0x11
	.byte	0x1
	.byte	0x1
	.4byte	.LASF160
	.4byte	.LASF160
	.byte	0x4
	.2byte	0x3f3
	.byte	0x6
	.byte	0
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.uleb128 0x2137
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x2007
	.uleb128 0xe
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x2007
	.uleb128 0xe
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LLST2:
	.4byte	.LFB5
	.4byte	.LCFI3
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI3
	.4byte	.LFE5
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
.LVUS0:
	.uleb128 0
	.uleb128 .LVU6
	.uleb128 .LVU6
	.uleb128 0
.LLST0:
	.4byte	.LVL0
	.4byte	.LVL1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL1
	.4byte	.LFE4
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LLST1:
	.4byte	.LFB3
	.4byte	.LCFI0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI0
	.4byte	.LCFI1
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	.LCFI1
	.4byte	.LCFI2
	.2byte	0x2
	.byte	0x7d
	.sleb128 16
	.4byte	.LCFI2
	.4byte	.LFE3
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x2c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LFB4
	.4byte	.LFE4
	.4byte	.LFB3
	.4byte	.LFE3
	.4byte	.LFB5
	.4byte	.LFE5
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF35:
	.ascii	"RCC_ADC1\000"
.LASF18:
	.ascii	"RCC_PLL\000"
.LASF73:
	.ascii	"RCC_LPUART1\000"
.LASF24:
	.ascii	"RCC_HSI48\000"
.LASF27:
	.ascii	"RCC_TSC\000"
.LASF0:
	.ascii	"unsigned int\000"
.LASF134:
	.ascii	"SCC_LPUART1\000"
.LASF45:
	.ascii	"RCC_QSPI\000"
.LASF119:
	.ascii	"SCC_UART4\000"
.LASF118:
	.ascii	"SCC_UART5\000"
.LASF123:
	.ascii	"SCC_SPI2\000"
.LASF8:
	.ascii	"__int32_t\000"
.LASF95:
	.ascii	"SCC_ADC\000"
.LASF109:
	.ascii	"SCC_LPTIM1\000"
.LASF132:
	.ascii	"SCC_LPTIM2\000"
.LASF46:
	.ascii	"RCC_FMC\000"
.LASF149:
	.ascii	"gpio_mode_setup\000"
.LASF159:
	.ascii	"rcc_set_sysclk_source\000"
.LASF147:
	.ascii	"delay_loop\000"
.LASF14:
	.ascii	"uint32_t\000"
.LASF30:
	.ascii	"RCC_DMA2\000"
.LASF163:
	.ascii	"/home/kshelton/Documents/GitHub/ECE-4140/M1/m1b\000"
.LASF162:
	.ascii	"m1b.c\000"
.LASF84:
	.ascii	"RCC_SDMMC1\000"
.LASF17:
	.ascii	"rcc_apb2_frequency\000"
.LASF11:
	.ascii	"long long unsigned int\000"
.LASF28:
	.ascii	"RCC_CRC\000"
.LASF151:
	.ascii	"rcc_osc_on\000"
.LASF135:
	.ascii	"SCC_DFSDM\000"
.LASF54:
	.ascii	"RCC_CRS\000"
.LASF96:
	.ascii	"SCC_ADC1\000"
.LASF21:
	.ascii	"RCC_MSI\000"
.LASF106:
	.ascii	"SCC_GPIOA\000"
.LASF19:
	.ascii	"RCC_HSE\000"
.LASF154:
	.ascii	"flash_dcache_enable\000"
.LASF112:
	.ascii	"SCC_PWR\000"
.LASF158:
	.ascii	"rcc_periph_clock_enable\000"
.LASF80:
	.ascii	"RCC_USART1\000"
.LASF61:
	.ascii	"RCC_USART2\000"
.LASF60:
	.ascii	"RCC_USART3\000"
.LASF107:
	.ascii	"SCC_QSPI\000"
.LASF48:
	.ascii	"RCC_OPAMP\000"
.LASF16:
	.ascii	"rcc_apb1_frequency\000"
.LASF89:
	.ascii	"SCC_SRAM1\000"
.LASF98:
	.ascii	"SCC_SRAM2\000"
.LASF15:
	.ascii	"rcc_ahb_frequency\000"
.LASF12:
	.ascii	"char\000"
.LASF152:
	.ascii	"flash_prefetch_enable\000"
.LASF125:
	.ascii	"SCC_LCD\000"
.LASF44:
	.ascii	"RCC_GPIOA\000"
.LASF43:
	.ascii	"RCC_GPIOB\000"
.LASF42:
	.ascii	"RCC_GPIOC\000"
.LASF41:
	.ascii	"RCC_GPIOD\000"
.LASF40:
	.ascii	"RCC_GPIOE\000"
.LASF39:
	.ascii	"RCC_GPIOF\000"
.LASF38:
	.ascii	"RCC_GPIOG\000"
.LASF37:
	.ascii	"RCC_GPIOH\000"
.LASF49:
	.ascii	"RCC_DAC1\000"
.LASF92:
	.ascii	"SCC_DMA1\000"
.LASF91:
	.ascii	"SCC_DMA2\000"
.LASF51:
	.ascii	"RCC_USB\000"
.LASF79:
	.ascii	"RCC_TIM15\000"
.LASF78:
	.ascii	"RCC_TIM16\000"
.LASF77:
	.ascii	"RCC_TIM17\000"
.LASF1:
	.ascii	"long long int\000"
.LASF57:
	.ascii	"RCC_I2C1\000"
.LASF56:
	.ascii	"RCC_I2C2\000"
.LASF55:
	.ascii	"RCC_I2C3\000"
.LASF93:
	.ascii	"SCC_RNG\000"
.LASF156:
	.ascii	"rcc_set_main_pll\000"
.LASF34:
	.ascii	"RCC_ADC\000"
.LASF82:
	.ascii	"RCC_SPI1\000"
.LASF63:
	.ascii	"RCC_SPI2\000"
.LASF62:
	.ascii	"RCC_SPI3\000"
.LASF161:
	.ascii	"GNU C17 10.3.1 20210621 (release) -mcpu=cortex-m4 -"
	.ascii	"mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -march=ar"
	.ascii	"mv7e-m+fp -g -gdwarf-2 -Og -fdata-sections -ffuncti"
	.ascii	"on-sections\000"
.LASF148:
	.ascii	"clock_setup\000"
.LASF141:
	.ascii	"SCC_USART1\000"
.LASF121:
	.ascii	"SCC_USART2\000"
.LASF120:
	.ascii	"SCC_USART3\000"
.LASF157:
	.ascii	"rcc_wait_for_osc_ready\000"
.LASF145:
	.ascii	"SCC_SDMMC1\000"
.LASF127:
	.ascii	"SCC_TIM6\000"
.LASF29:
	.ascii	"RCC_FLASH\000"
.LASF36:
	.ascii	"RCC_OTGFS\000"
.LASF124:
	.ascii	"SCC_WWDG\000"
.LASF76:
	.ascii	"RCC_SAI1\000"
.LASF75:
	.ascii	"RCC_SAI2\000"
.LASF86:
	.ascii	"RCC_SYSCFG\000"
.LASF2:
	.ascii	"long double\000"
.LASF83:
	.ascii	"RCC_TIM1\000"
.LASF70:
	.ascii	"RCC_TIM2\000"
.LASF69:
	.ascii	"RCC_TIM3\000"
.LASF68:
	.ascii	"RCC_TIM4\000"
.LASF67:
	.ascii	"RCC_TIM5\000"
.LASF66:
	.ascii	"RCC_TIM6\000"
.LASF33:
	.ascii	"RCC_AES\000"
.LASF81:
	.ascii	"RCC_TIM8\000"
.LASF26:
	.ascii	"rcc_periph_clken\000"
.LASF110:
	.ascii	"SCC_OPAMP\000"
.LASF5:
	.ascii	"short int\000"
.LASF7:
	.ascii	"long int\000"
.LASF108:
	.ascii	"SCC_FMC\000"
.LASF53:
	.ascii	"RCC_CAN1\000"
.LASF52:
	.ascii	"RCC_CAN2\000"
.LASF72:
	.ascii	"RCC_SWPMI1\000"
.LASF105:
	.ascii	"SCC_GPIOB\000"
.LASF104:
	.ascii	"SCC_GPIOC\000"
.LASF103:
	.ascii	"SCC_GPIOD\000"
.LASF102:
	.ascii	"SCC_GPIOE\000"
.LASF101:
	.ascii	"SCC_GPIOF\000"
.LASF100:
	.ascii	"SCC_GPIOG\000"
.LASF99:
	.ascii	"SCC_GPIOH\000"
.LASF155:
	.ascii	"flash_icache_enable\000"
.LASF50:
	.ascii	"RCC_PWR\000"
.LASF160:
	.ascii	"rcc_wait_for_sysclk_status\000"
.LASF117:
	.ascii	"SCC_I2C1\000"
.LASF116:
	.ascii	"SCC_I2C2\000"
.LASF115:
	.ascii	"SCC_I2C3\000"
.LASF140:
	.ascii	"SCC_TIM15\000"
.LASF139:
	.ascii	"SCC_TIM16\000"
.LASF138:
	.ascii	"SCC_TIM17\000"
.LASF85:
	.ascii	"RCC_FW\000"
.LASF10:
	.ascii	"long unsigned int\000"
.LASF13:
	.ascii	"int32_t\000"
.LASF59:
	.ascii	"RCC_UART4\000"
.LASF58:
	.ascii	"RCC_UART5\000"
.LASF31:
	.ascii	"RCC_DMA1\000"
.LASF88:
	.ascii	"SCC_CRC\000"
.LASF4:
	.ascii	"unsigned char\000"
.LASF143:
	.ascii	"SCC_SPI1\000"
.LASF9:
	.ascii	"__uint32_t\000"
.LASF122:
	.ascii	"SCC_SPI3\000"
.LASF111:
	.ascii	"SCC_DAC1\000"
.LASF165:
	.ascii	"loops\000"
.LASF146:
	.ascii	"SCC_SYSCFG\000"
.LASF64:
	.ascii	"RCC_LCD\000"
.LASF20:
	.ascii	"RCC_HSI16\000"
.LASF90:
	.ascii	"SCC_FLASH\000"
.LASF137:
	.ascii	"SCC_SAI1\000"
.LASF136:
	.ascii	"SCC_SAI2\000"
.LASF97:
	.ascii	"SCC_OTGFS\000"
.LASF47:
	.ascii	"RCC_LPTIM1\000"
.LASF71:
	.ascii	"RCC_LPTIM2\000"
.LASF144:
	.ascii	"SCC_TIM1\000"
.LASF131:
	.ascii	"SCC_TIM2\000"
.LASF130:
	.ascii	"SCC_TIM3\000"
.LASF129:
	.ascii	"SCC_TIM4\000"
.LASF128:
	.ascii	"SCC_TIM5\000"
.LASF22:
	.ascii	"RCC_LSE\000"
.LASF126:
	.ascii	"SCC_TIM7\000"
.LASF142:
	.ascii	"SCC_TIM8\000"
.LASF23:
	.ascii	"RCC_LSI\000"
.LASF3:
	.ascii	"signed char\000"
.LASF65:
	.ascii	"RCC_TIM7\000"
.LASF6:
	.ascii	"short unsigned int\000"
.LASF164:
	.ascii	"main\000"
.LASF153:
	.ascii	"flash_set_ws\000"
.LASF150:
	.ascii	"gpio_toggle\000"
.LASF94:
	.ascii	"SCC_AES\000"
.LASF32:
	.ascii	"RCC_RNG\000"
.LASF133:
	.ascii	"SCC_SWPMI1\000"
.LASF25:
	.ascii	"rcc_osc\000"
.LASF114:
	.ascii	"SCC_CAN1\000"
.LASF113:
	.ascii	"SCC_CAN2\000"
.LASF74:
	.ascii	"RCC_DFSDM\000"
.LASF87:
	.ascii	"SCC_TSC\000"
	.ident	"GCC: (15:10.3-2021.07-4) 10.3.1 20210621 (release)"
