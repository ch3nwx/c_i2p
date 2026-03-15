	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 26, 0	sdk_version 26, 2
	.globl	_alloc_matrix                   ; -- Begin function alloc_matrix
	.p2align	2
_alloc_matrix:                          ; @alloc_matrix
	.cfi_startproc
; %bb.0:
	stp	x22, x21, [sp, #-48]!           ; 16-byte Folded Spill
	stp	x20, x19, [sp, #16]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset w21, -40
	.cfi_offset w22, -48
	mov	x21, x0
	sbfiz	x0, x21, #3, #32
	bl	_malloc
	mov	x19, x0
	cmp	w21, #1
	b.lt	LBB0_3
; %bb.1:
	sxtw	x8, w21
	lsl	x20, x8, #2
	mov	w21, w21
	mov	x22, x19
LBB0_2:                                 ; =>This Inner Loop Header: Depth=1
	mov	x0, x20
	bl	_malloc
	str	x0, [x22], #8
	subs	x21, x21, #1
	b.ne	LBB0_2
LBB0_3:
	mov	x0, x19
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #16]             ; 16-byte Folded Reload
	ldp	x22, x21, [sp], #48             ; 16-byte Folded Reload
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_free_matrix                    ; -- Begin function free_matrix
	.p2align	2
_free_matrix:                           ; @free_matrix
	.cfi_startproc
; %bb.0:
	stp	x22, x21, [sp, #-48]!           ; 16-byte Folded Spill
	stp	x20, x19, [sp, #16]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset w21, -40
	.cfi_offset w22, -48
	mov	x19, x0
	cmp	w1, #1
	b.lt	LBB1_3
; %bb.1:
	mov	w20, w1
	mov	x21, x19
LBB1_2:                                 ; =>This Inner Loop Header: Depth=1
	ldr	x0, [x21], #8
	bl	_free
	subs	x20, x20, #1
	b.ne	LBB1_2
LBB1_3:
	mov	x0, x19
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #16]             ; 16-byte Folded Reload
	ldp	x22, x21, [sp], #48             ; 16-byte Folded Reload
	b	_free
	.cfi_endproc
                                        ; -- End function
	.globl	_scan_matrix                    ; -- Begin function scan_matrix
	.p2align	2
_scan_matrix:                           ; @scan_matrix
	.cfi_startproc
; %bb.0:
                                        ; kill: def $w1 killed $w1 def $x1
	cmp	w1, #1
	b.lt	LBB2_6
; %bb.1:
	sub	sp, sp, #80
	stp	x24, x23, [sp, #16]             ; 16-byte Folded Spill
	stp	x22, x21, [sp, #32]             ; 16-byte Folded Spill
	stp	x20, x19, [sp, #48]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #64]             ; 16-byte Folded Spill
	add	x29, sp, #64
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset w21, -40
	.cfi_offset w22, -48
	.cfi_offset w23, -56
	.cfi_offset w24, -64
	mov	x19, x0
	mov	x21, #0                         ; =0x0
	ubfiz	x22, x1, #2, #32
	mov	w23, w1
Lloh0:
	adrp	x20, l_.str@PAGE
Lloh1:
	add	x20, x20, l_.str@PAGEOFF
LBB2_2:                                 ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB2_3 Depth 2
	mov	x24, #0                         ; =0x0
LBB2_3:                                 ;   Parent Loop BB2_2 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ldr	x8, [x19, x21, lsl #3]
	add	x8, x8, x24
	str	x8, [sp]
	mov	x0, x20
	bl	_scanf
	add	x24, x24, #4
	cmp	x22, x24
	b.ne	LBB2_3
; %bb.4:                                ;   in Loop: Header=BB2_2 Depth=1
	add	x21, x21, #1
	cmp	x21, x23
	b.ne	LBB2_2
; %bb.5:
	ldp	x29, x30, [sp, #64]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #48]             ; 16-byte Folded Reload
	ldp	x22, x21, [sp, #32]             ; 16-byte Folded Reload
	ldp	x24, x23, [sp, #16]             ; 16-byte Folded Reload
	add	sp, sp, #80
LBB2_6:
	ret
	.loh AdrpAdd	Lloh0, Lloh1
	.cfi_endproc
                                        ; -- End function
	.globl	_flip                           ; -- Begin function flip
	.p2align	2
_flip:                                  ; @flip
	.cfi_startproc
; %bb.0:
                                        ; kill: def $w1 killed $w1 def $x1
	cmp	w1, #1
	b.lt	LBB3_6
; %bb.1:
	mov	x8, #0                          ; =0x0
	lsr	w10, w1, #1
	mov	w9, w1
	cmp	w10, #1
	csinc	w10, w10, wzr, hi
	ubfiz	x11, x1, #2, #32
	sub	x11, x11, #4
	b	LBB3_3
LBB3_2:                                 ;   in Loop: Header=BB3_3 Depth=1
	add	x8, x8, #1
	cmp	x8, x9
	b.eq	LBB3_6
LBB3_3:                                 ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB3_5 Depth 2
	cmp	w1, #1
	b.eq	LBB3_2
; %bb.4:                                ;   in Loop: Header=BB3_3 Depth=1
	ldr	x12, [x0, x8, lsl #3]
	add	x13, x12, x11
	mov	x14, x10
LBB3_5:                                 ;   Parent Loop BB3_3 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ldr	w15, [x12]
	ldr	w16, [x13]
	str	w16, [x12], #4
	str	w15, [x13], #-4
	subs	x14, x14, #1
	b.ne	LBB3_5
	b	LBB3_2
LBB3_6:
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_apply_filter                   ; -- Begin function apply_filter
	.p2align	2
_apply_filter:                          ; @apply_filter
	.cfi_startproc
; %bb.0:
	cmp	w5, #1
	b.lt	LBB4_10
; %bb.1:
	mov	x8, #0                          ; =0x0
	mov	w9, w5
	mov	w10, w4
	b	LBB4_3
LBB4_2:                                 ;   in Loop: Header=BB4_3 Depth=1
	add	x8, x8, #1
	cmp	x8, x9
	b.eq	LBB4_10
LBB4_3:                                 ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB4_5 Depth 2
                                        ;       Child Loop BB4_7 Depth 3
                                        ;         Child Loop BB4_8 Depth 4
	mov	x11, #0                         ; =0x0
	mov	x12, #0                         ; =0x0
	lsl	x14, x8, #3
	ldr	x13, [x2, x14]
	add	x14, x0, x14
	b	LBB4_5
LBB4_4:                                 ;   in Loop: Header=BB4_5 Depth=2
	add	x12, x12, #1
	add	x11, x11, #4
	cmp	x12, x9
	b.eq	LBB4_2
LBB4_5:                                 ;   Parent Loop BB4_3 Depth=1
                                        ; =>  This Loop Header: Depth=2
                                        ;       Child Loop BB4_7 Depth 3
                                        ;         Child Loop BB4_8 Depth 4
	str	wzr, [x13, x12, lsl #2]
	cmp	w4, #1
	b.lt	LBB4_4
; %bb.6:                                ;   in Loop: Header=BB4_5 Depth=2
	mov	x15, #0                         ; =0x0
	ldr	w16, [x13, x12, lsl #2]
LBB4_7:                                 ;   Parent Loop BB4_3 Depth=1
                                        ;     Parent Loop BB4_5 Depth=2
                                        ; =>    This Loop Header: Depth=3
                                        ;         Child Loop BB4_8 Depth 4
	ldr	x3, [x14, x15, lsl #3]
	ldr	x17, [x1, x15, lsl #3]
	add	x3, x3, x11
	mov	x5, x10
LBB4_8:                                 ;   Parent Loop BB4_3 Depth=1
                                        ;     Parent Loop BB4_5 Depth=2
                                        ;       Parent Loop BB4_7 Depth=3
                                        ; =>      This Inner Loop Header: Depth=4
	ldr	w6, [x3], #4
	ldr	w7, [x17], #4
	madd	w16, w7, w6, w16
	str	w16, [x13, x12, lsl #2]
	subs	x5, x5, #1
	b.ne	LBB4_8
; %bb.9:                                ;   in Loop: Header=BB4_7 Depth=3
	add	x15, x15, #1
	cmp	x15, x10
	b.ne	LBB4_7
	b	LBB4_4
LBB4_10:
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #144
	stp	x28, x27, [sp, #48]             ; 16-byte Folded Spill
	stp	x26, x25, [sp, #64]             ; 16-byte Folded Spill
	stp	x24, x23, [sp, #80]             ; 16-byte Folded Spill
	stp	x22, x21, [sp, #96]             ; 16-byte Folded Spill
	stp	x20, x19, [sp, #112]            ; 16-byte Folded Spill
	stp	x29, x30, [sp, #128]            ; 16-byte Folded Spill
	add	x29, sp, #128
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset w21, -40
	.cfi_offset w22, -48
	.cfi_offset w23, -56
	.cfi_offset w24, -64
	.cfi_offset w25, -72
	.cfi_offset w26, -80
	.cfi_offset w27, -88
	.cfi_offset w28, -96
	add	x8, sp, #44
	str	x8, [sp]
Lloh2:
	adrp	x0, l_.str@PAGE
Lloh3:
	add	x0, x0, l_.str@PAGEOFF
	bl	_scanf
	ldr	w8, [sp, #44]
	cmp	w8, #1
	b.lt	LBB5_50
; %bb.1:
	mov	w26, #0                         ; =0x0
Lloh4:
	adrp	x20, l_.str@PAGE
Lloh5:
	add	x20, x20, l_.str@PAGEOFF
	b	LBB5_3
LBB5_2:                                 ;   in Loop: Header=BB5_3 Depth=1
	mov	x0, x23
	bl	_free
	add	w26, w26, #1
	ldr	w8, [sp, #44]
	cmp	w26, w8
	b.ge	LBB5_50
LBB5_3:                                 ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB5_5 Depth 2
                                        ;     Child Loop BB5_7 Depth 2
                                        ;       Child Loop BB5_8 Depth 3
                                        ;     Child Loop BB5_12 Depth 2
                                        ;     Child Loop BB5_14 Depth 2
                                        ;       Child Loop BB5_15 Depth 3
                                        ;     Child Loop BB5_20 Depth 2
                                        ;       Child Loop BB5_22 Depth 3
                                        ;     Child Loop BB5_25 Depth 2
                                        ;     Child Loop BB5_28 Depth 2
                                        ;       Child Loop BB5_30 Depth 3
                                        ;         Child Loop BB5_32 Depth 4
                                        ;           Child Loop BB5_33 Depth 5
                                        ;     Child Loop BB5_37 Depth 2
                                        ;       Child Loop BB5_38 Depth 3
                                        ;     Child Loop BB5_43 Depth 2
                                        ;     Child Loop BB5_46 Depth 2
                                        ;     Child Loop BB5_49 Depth 2
	add	x8, sp, #32
	str	x8, [sp, #16]
	add	x8, sp, #36
	str	x8, [sp, #8]
	add	x8, sp, #40
	str	x8, [sp]
Lloh6:
	adrp	x0, l_.str.1@PAGE
Lloh7:
	add	x0, x0, l_.str.1@PAGEOFF
	bl	_scanf
	ldrsw	x19, [sp, #40]
	lsl	x0, x19, #3
	bl	_malloc
	mov	x22, x0
	cmp	w19, #1
	b.lt	LBB5_10
; %bb.4:                                ;   in Loop: Header=BB5_3 Depth=1
	lsl	x23, x19, #2
	mov	x24, x22
	mov	x21, x19
LBB5_5:                                 ;   Parent Loop BB5_3 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	mov	x0, x23
	bl	_malloc
	str	x0, [x24], #8
	subs	x21, x21, #1
	b.ne	LBB5_5
; %bb.6:                                ;   in Loop: Header=BB5_3 Depth=1
	mov	x23, #0                         ; =0x0
LBB5_7:                                 ;   Parent Loop BB5_3 Depth=1
                                        ; =>  This Loop Header: Depth=2
                                        ;       Child Loop BB5_8 Depth 3
	ldr	x24, [x22, x23, lsl #3]
	mov	x25, x19
LBB5_8:                                 ;   Parent Loop BB5_3 Depth=1
                                        ;     Parent Loop BB5_7 Depth=2
                                        ; =>    This Inner Loop Header: Depth=3
	str	x24, [sp]
	mov	x0, x20
	bl	_scanf
	add	x24, x24, #4
	subs	x25, x25, #1
	b.ne	LBB5_8
; %bb.9:                                ;   in Loop: Header=BB5_7 Depth=2
	add	x23, x23, #1
	cmp	x23, x19
	b.ne	LBB5_7
LBB5_10:                                ;   in Loop: Header=BB5_3 Depth=1
	ldrsw	x19, [sp, #36]
	lsl	x0, x19, #3
	bl	_malloc
	mov	x23, x0
	cmp	w19, #1
	b.lt	LBB5_17
; %bb.11:                               ;   in Loop: Header=BB5_3 Depth=1
	lsl	x24, x19, #2
	mov	x25, x23
	mov	x21, x19
LBB5_12:                                ;   Parent Loop BB5_3 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	mov	x0, x24
	bl	_malloc
	str	x0, [x25], #8
	subs	x21, x21, #1
	b.ne	LBB5_12
; %bb.13:                               ;   in Loop: Header=BB5_3 Depth=1
	mov	x24, #0                         ; =0x0
LBB5_14:                                ;   Parent Loop BB5_3 Depth=1
                                        ; =>  This Loop Header: Depth=2
                                        ;       Child Loop BB5_15 Depth 3
	ldr	x25, [x23, x24, lsl #3]
	mov	x27, x19
LBB5_15:                                ;   Parent Loop BB5_3 Depth=1
                                        ;     Parent Loop BB5_14 Depth=2
                                        ; =>    This Inner Loop Header: Depth=3
	str	x25, [sp]
	mov	x0, x20
	bl	_scanf
	add	x25, x25, #4
	subs	x27, x27, #1
	b.ne	LBB5_15
; %bb.16:                               ;   in Loop: Header=BB5_14 Depth=2
	add	x24, x24, #1
	cmp	x24, x19
	b.ne	LBB5_14
LBB5_17:                                ;   in Loop: Header=BB5_3 Depth=1
	ldr	w8, [sp, #40]
	cmp	w8, #1
	b.lt	LBB5_23
; %bb.18:                               ;   in Loop: Header=BB5_3 Depth=1
	mov	x9, #0                          ; =0x0
	ubfx	x10, x8, #1, #31
	cmp	w10, #1
	csinc	w10, w10, wzr, hi
	lsl	x11, x8, #2
	b	LBB5_20
LBB5_19:                                ;   in Loop: Header=BB5_20 Depth=2
	add	x9, x9, #1
	cmp	x9, x8
	b.eq	LBB5_23
LBB5_20:                                ;   Parent Loop BB5_3 Depth=1
                                        ; =>  This Loop Header: Depth=2
                                        ;       Child Loop BB5_22 Depth 3
	cmp	w8, #1
	b.eq	LBB5_19
; %bb.21:                               ;   in Loop: Header=BB5_20 Depth=2
	ldr	x12, [x22, x9, lsl #3]
	add	x13, x12, x11
	sub	x13, x13, #4
	mov	x14, x10
LBB5_22:                                ;   Parent Loop BB5_3 Depth=1
                                        ;     Parent Loop BB5_20 Depth=2
                                        ; =>    This Inner Loop Header: Depth=3
	ldr	w15, [x12]
	ldr	w16, [x13]
	str	w16, [x12], #4
	str	w15, [x13], #-4
	subs	x14, x14, #1
	b.ne	LBB5_22
	b	LBB5_19
LBB5_23:                                ;   in Loop: Header=BB5_3 Depth=1
	ldp	w19, w8, [sp, #36]
	sub	w25, w8, w19
	add	w8, w25, #1
	sxtw	x28, w8
	sbfiz	x0, x8, #3, #32
	bl	_malloc
	mov	x21, x0
	tbnz	w25, #31, LBB5_35
; %bb.24:                               ;   in Loop: Header=BB5_3 Depth=1
	str	w25, [sp, #28]                  ; 4-byte Folded Spill
	mov	x27, x26
	lsl	x25, x28, #2
	mov	x24, x21
	mov	x26, x28
LBB5_25:                                ;   Parent Loop BB5_3 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	mov	x0, x25
	bl	_malloc
	str	x0, [x24], #8
	subs	x26, x26, #1
	b.ne	LBB5_25
; %bb.26:                               ;   in Loop: Header=BB5_3 Depth=1
	mov	x8, #0                          ; =0x0
	mov	x26, x27
	ldr	w25, [sp, #28]                  ; 4-byte Folded Reload
	b	LBB5_28
LBB5_27:                                ;   in Loop: Header=BB5_28 Depth=2
	add	x8, x8, #1
	cmp	x8, x28
	b.eq	LBB5_35
LBB5_28:                                ;   Parent Loop BB5_3 Depth=1
                                        ; =>  This Loop Header: Depth=2
                                        ;       Child Loop BB5_30 Depth 3
                                        ;         Child Loop BB5_32 Depth 4
                                        ;           Child Loop BB5_33 Depth 5
	mov	x9, #0                          ; =0x0
	mov	x10, #0                         ; =0x0
	lsl	x12, x8, #3
	ldr	x11, [x21, x12]
	add	x12, x22, x12
	b	LBB5_30
LBB5_29:                                ;   in Loop: Header=BB5_30 Depth=3
	add	x10, x10, #1
	add	x9, x9, #4
	cmp	x10, x28
	b.eq	LBB5_27
LBB5_30:                                ;   Parent Loop BB5_3 Depth=1
                                        ;     Parent Loop BB5_28 Depth=2
                                        ; =>    This Loop Header: Depth=3
                                        ;         Child Loop BB5_32 Depth 4
                                        ;           Child Loop BB5_33 Depth 5
	str	wzr, [x11, x10, lsl #2]
	cmp	w19, #1
	b.lt	LBB5_29
; %bb.31:                               ;   in Loop: Header=BB5_30 Depth=3
	mov	w13, #0                         ; =0x0
	mov	x14, #0                         ; =0x0
LBB5_32:                                ;   Parent Loop BB5_3 Depth=1
                                        ;     Parent Loop BB5_28 Depth=2
                                        ;       Parent Loop BB5_30 Depth=3
                                        ; =>      This Loop Header: Depth=4
                                        ;           Child Loop BB5_33 Depth 5
	ldr	x16, [x12, x14, lsl #3]
	ldr	x15, [x23, x14, lsl #3]
	add	x16, x16, x9
	mov	x17, x19
LBB5_33:                                ;   Parent Loop BB5_3 Depth=1
                                        ;     Parent Loop BB5_28 Depth=2
                                        ;       Parent Loop BB5_30 Depth=3
                                        ;         Parent Loop BB5_32 Depth=4
                                        ; =>        This Inner Loop Header: Depth=5
	ldr	w0, [x16], #4
	ldr	w1, [x15], #4
	madd	w13, w1, w0, w13
	str	w13, [x11, x10, lsl #2]
	subs	x17, x17, #1
	b.ne	LBB5_33
; %bb.34:                               ;   in Loop: Header=BB5_32 Depth=4
	add	x14, x14, #1
	cmp	x14, x19
	b.ne	LBB5_32
	b	LBB5_29
LBB5_35:                                ;   in Loop: Header=BB5_3 Depth=1
	tbnz	w25, #31, LBB5_40
; %bb.36:                               ;   in Loop: Header=BB5_3 Depth=1
	mov	x9, #0                          ; =0x0
	mov	w8, #0                          ; =0x0
	ldr	w10, [sp, #32]
LBB5_37:                                ;   Parent Loop BB5_3 Depth=1
                                        ; =>  This Loop Header: Depth=2
                                        ;       Child Loop BB5_38 Depth 3
	ldr	x11, [x21, x9, lsl #3]
	mov	x12, x28
LBB5_38:                                ;   Parent Loop BB5_3 Depth=1
                                        ;     Parent Loop BB5_37 Depth=2
                                        ; =>    This Inner Loop Header: Depth=3
	ldr	w13, [x11], #4
	cmp	w13, w10
	cinc	w8, w8, gt
	subs	x12, x12, #1
	b.ne	LBB5_38
; %bb.39:                               ;   in Loop: Header=BB5_37 Depth=2
	add	x9, x9, #1
	cmp	x9, x28
	b.ne	LBB5_37
	b	LBB5_41
LBB5_40:                                ;   in Loop: Header=BB5_3 Depth=1
	mov	w8, #0                          ; =0x0
LBB5_41:                                ;   in Loop: Header=BB5_3 Depth=1
	str	x8, [sp]
Lloh8:
	adrp	x0, l_.str.2@PAGE
Lloh9:
	add	x0, x0, l_.str.2@PAGEOFF
	bl	_printf
	ldr	w19, [sp, #40]
	cmp	w19, #1
	b.lt	LBB5_44
; %bb.42:                               ;   in Loop: Header=BB5_3 Depth=1
	mov	x24, x22
LBB5_43:                                ;   Parent Loop BB5_3 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ldr	x0, [x24], #8
	bl	_free
	subs	x19, x19, #1
	b.ne	LBB5_43
LBB5_44:                                ;   in Loop: Header=BB5_3 Depth=1
	mov	x0, x22
	bl	_free
	tbnz	w25, #31, LBB5_47
; %bb.45:                               ;   in Loop: Header=BB5_3 Depth=1
	mov	x19, x21
LBB5_46:                                ;   Parent Loop BB5_3 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ldr	x0, [x19], #8
	bl	_free
	subs	x28, x28, #1
	b.ne	LBB5_46
LBB5_47:                                ;   in Loop: Header=BB5_3 Depth=1
	mov	x0, x21
	bl	_free
	ldr	w19, [sp, #36]
	cmp	w19, #1
	b.lt	LBB5_2
; %bb.48:                               ;   in Loop: Header=BB5_3 Depth=1
	mov	x21, x23
LBB5_49:                                ;   Parent Loop BB5_3 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ldr	x0, [x21], #8
	bl	_free
	subs	x19, x19, #1
	b.ne	LBB5_49
	b	LBB5_2
LBB5_50:
	mov	w0, #0                          ; =0x0
	ldp	x29, x30, [sp, #128]            ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #112]            ; 16-byte Folded Reload
	ldp	x22, x21, [sp, #96]             ; 16-byte Folded Reload
	ldp	x24, x23, [sp, #80]             ; 16-byte Folded Reload
	ldp	x26, x25, [sp, #64]             ; 16-byte Folded Reload
	ldp	x28, x27, [sp, #48]             ; 16-byte Folded Reload
	add	sp, sp, #144
	ret
	.loh AdrpAdd	Lloh2, Lloh3
	.loh AdrpAdd	Lloh4, Lloh5
	.loh AdrpAdd	Lloh6, Lloh7
	.loh AdrpAdd	Lloh8, Lloh9
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"%d"

l_.str.1:                               ; @.str.1
	.asciz	"%d %d %d"

l_.str.2:                               ; @.str.2
	.asciz	"%d\n"

.subsections_via_symbols
