global _get_vesa_infos
global _get_vesa_mode_infos
global _set_vesa_mode

struc VesaInfoBlock
	.Signature resb 4
	.VbeVersion resw 1
	.OEMNamePtr resw 2
	.Capabilities resb 4
	.VideoModesOffset resw 1
	.VideoModesSegment resw 1
	.CountOf64KBlocks resw 1
	.OEMSoftwareRevision resw 1
	.OEMVendorNamePtr resd 1
	.OEMProductNamePtr resd 1
	.OEMProductRevisionPtr resd 1
	.Reserved resb 222
	.OEMData resb 256
endstruc

struc VesaModeInfosBlock
	.attributes resw 1;
	.window_a resb 1;
	.window_b resb 1;
	.granularity resw 1;
	.window_size resw 1;
	.segment_a resw 1;
	.segment_b resw 1;
	.win_func_ptr resd 1;
	.pitch resw 1;
	.width resw 1;
	.height resw 1;
	.w_char resb 1;
	.y_char resb 1;
	.planes resb 1;
	.bpp resb 1;
	.banks resb 1;
	.memory_model resb 1;
	.bank_size resb 1;
	.images_pages resb 1;
	.reserved0 resb 1;
	.red_mask resb 1;
	.red_position resb 1;
	.green_mask resb 1;
	.green_position resb 1;
	.blue_mask resb 1;
	.blue_position resb 1;
	.reserved_mask resb 1;
	.reserved_position resb 1;
	.direct_color_attributes resb 1;
	.framebuffer resd 1;
	.off_screen_mem_off resd 1;
	.off_screen_mem_size resw 1;
	.reserved1 resb 206
enstruc


_get_vesa_infos:

	push ds
	pop es
	mov di, VesaInfoBlockBuffer

	clc
	mov ax, 0x4f00
	int 0x10
	cmp al, 0x4f
	jne _error

	mov ax, VesaInfoBlock
	ret

_get_vesa_mode_infos:

	push word[VesaInfoBlockBuffer + VesaInfoBlock.VideoModesSegment]
	pop es
	mov di, VesaModeInfoBlockBuffer
	mov bx, [VesaInfoBlockBuffer + VesaInfoBlock.VideoModesOffset]
	mov cx, [bx]
	cmp cx, 0xffff
	je _no_modes

	clc
	mov ax, 0x4f01
	int 0x10
	cmp al, 0x4f
	jne _error

	mov ax, VesaModeInfosBlock
	ret

_set_vesa_mode:

	mov ax, 0x4f02
	mov bx, 0x118
	int 0x10
	ret

_no_modes:

	jmp $

_error:

	stc
	ret


align(4)
VesaInfoBlockBuffer: istruc VesaInfoBlock
	at VesaInfoBlock.Signature, db "VESA"
	at VesaInfoBlock.VbeVersion, dw 0x0300
	times 504 db 0
iend

VesaModeInfoBlockBuffer: istruc VesaModeInfoBlock
	times 256 db 0
iend
