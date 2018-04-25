	org		07c00h	;ORG是Origin的缩写：起始地址，将程序加载到7c00处
	mov		ax,cs
	mov		ds,ax
	mov		es,ax
	call	DispStr	;调用DispStr函数
	jmp		$		;无限循环
DispStr:
	mov		ax,BootMessage
	mov		bp,ax	;ES:BP = 串地址
	mov		cx,16
	mov		ax,01301h	
	mov		bx,000ch
	mov 	dl,0
	int 	10h; 10h 中断
BootMessage:		dw		"Welcome to KK OperatingSystem !"
times	510-($-$$)	db		0;	填充剩下的空间，使得生成的二进制代码恰好为512字节
dw	0xaa55			;结束标志