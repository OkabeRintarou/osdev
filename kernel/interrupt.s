; 处理器收到中断请求后保存当前上下文(EIP,ESP,CS,DS,EFLAG)到栈
; 然后跳转到中断处理程序入口

;有的中断处理函数会自动压入错误码，而有的不会
;所以为了方便，对不会自动压入错误码的中断处理统一压入错误码0
%macro ISR_NOERRCODE 1  ;define a macro,takeing one parameter
[GLOBAL isr%1] ;%1 access the first parameter
isr%1:
	cli
	push byte 0
	push byte %1
	jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 	1
[GLOBAL isr%1]
isr%1:
	cli
	push byte %1
	jmp isr_common_stub
%endmacro

; 8、10、11、12、13、14号中断处理函数会自动压入错误号
ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8
ISR_NOERRCODE 9
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19

; intel reserved
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

[EXTERN isr_handler]

isr_common_stub:
	pusha ;push edi,esi,ebp,esp,ebx,edx,ecx,eax

	mov ax,ds ; eax low 16 bits = ds
	push eax 

	mov ax,0x10
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax

	call isr_handler

	pop eax
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax

	popa	
	add esp,8 ; Cleans up the pushed error code and pushed ISR number
	sti
	iret

; This macro creates a stub for an IRQ - the first parameter is
; the IRQ number,the second is the ISR number it is remapped
%macro IRQ 2
[GLOBAL irq%1]
irq%1:	
	cli
	push byte 0
	push byte %2
	jmp irq_common_stub
%endmacro

IRQ 0,32
IRQ 1,33
IRQ 2,34
IRQ 3,35
IRQ 4,36
IRQ 5,37
IRQ 6,38
IRQ 7,39

IRQ 8,40
IRQ 9,41
IRQ 10,42
IRQ 11,43
IRQ 12,44
IRQ 13,45
IRQ 14,46
IRQ 15,47

[EXTERN irq_handler]
irq_common_stub:
	pusha

	mov ax,ds
	push eax

	mov ax,0x10
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax

	call irq_handler
	
	pop ebx
	mov ds,bx
	mov es,bx
	mov fs,bx
	mov gs,bx

	popa
	add esp,8
	sti
	iret

