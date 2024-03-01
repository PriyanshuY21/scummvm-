;hq2x filter
;16bpp output
;----------------------------------------------------------
;Copyright (C) 2003 MaxSt ( maxst@hiend3d.com )
;
;This program is free software; you can redistribute it and/or
;modify it under the terms of the GNU General Public License
;as published by the Free Software Foundation; either
;version 2 of the License, or (at your option) any later
;version.
;
;This program is distributed in the hope that it will be useful,
;but WITHOUT ANY WARRANTY; without even the implied warranty of
;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;GNU General Public License for more details.
;
;You should have received a copy of the GNU General Public License
;along with this program; if not, write to the Free Software
;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

GLOBAL _hq2x_16

SECTION .text

thresholdVal0        equ 0x00300706
thresholdVal1        equ 0x00000000

; Function variables space

w1                   equ -112
w2                   equ -108
w3                   equ -104
w4                   equ -100
w5                   equ -96
w6                   equ -92
w7                   equ -88
w8                   equ -84
w9                   equ -80
linesleft            equ -76
xcounter             equ -72
cross                equ -68
nextline             equ -64
prevline             equ -60
moduloSrc            equ -56
moduloDst            equ -52
threshold            equ -48
; threshold is 64bits
pFuncTable2          equ -40
pFuncTable           equ -36

; the following variables must match hqx_parameters structure
; Address of the whole structure
hqx_params_          equ -32
RGBtoYUV             equ -32
highbits             equ -28
lowbits              equ -24
low2bits             equ -20
low3bits             equ -16
greenMask            equ -12
redBlueMask          equ -8
green_redBlue_Mask   equ -4

inbuffer     equ 8
outbuffer    equ 12
Xres         equ 16
Yres         equ 20
srcPitch     equ 24
dstPitch     equ 28
hqx_params   equ 32

%macro TestDiff 2
    xor     ecx,ecx
    mov     edx,[%1]
    cmp     edx,[%2]
    je      %%fin
    mov     ecx,[ebp+RGBtoYUV]
    movd    mm1,[ecx+edx*4]
    movq    mm5,mm1
    mov     edx,[%2]
    movd    mm2,[ecx+edx*4]
    psubusb mm1,mm2
    psubusb mm2,mm5
    por     mm1,mm2
    psubusb mm1,[ebp+threshold]
    movd    ecx,mm1
%%fin:
%endmacro

%macro DiffOrNot 4
   TestDiff %1,%2
   test ecx,ecx
   jz   %%same
   %3
   jmp %%fin
%%same:
   %4
%%fin:
%endmacro

%macro DiffOrNot 6
   TestDiff %1,%2
   test ecx,ecx
   jz   %%same
   %3
   %4
   jmp %%fin
%%same:
   %5
   %6
%%fin:
%endmacro

%macro DiffOrNot 8
   TestDiff %1,%2
   test ecx,ecx
   jz   %%same
   %3
   %4
   %5
   jmp %%fin
%%same:
   %6
   %7
   %8
%%fin:
%endmacro

%macro DiffOrNot 10
   TestDiff %1,%2
   test ecx,ecx
   jz %%same
   %3
   %4
   %5
   %6
   jmp %%fin
%%same:
   %7
   %8
   %9
   %10
%%fin:
%endmacro

; interpolate16_3_1
; Mix two pixels with weight 3 and 1, respectively: (c1*3+c2)/4;
; Note: This implementation is not completely accurate, it sacrifices
; some accuracy for raw speed.
%macro Interp1 3
    mov edx,%2
    mov ecx,%3
    and edx,[ebp+highbits]
    and ecx,[ebp+highbits]
    add ecx,edx
    shr ecx,1
    add ecx,[ebp+lowbits]
    and ecx,[ebp+highbits]
    add edx,ecx
    shr edx,1
    mov %1,dx
%endmacro

; interpolate16_2_1_1
; Mix three pixels with weight 2, 1, and 1, respectively: (c1*2+c2+c3)/4;
; Note: This implementation is not completely accurate, it sacrifices
; some accuracy for raw speed.
%macro Interp2 4
    mov edx,%3
    mov ecx,%4
    and edx,[ebp+highbits]
    and ecx,[ebp+highbits]
    add ecx,edx
    shr ecx,1
    add ecx,[ebp+lowbits]
    mov edx,%2
    and ecx,[ebp+highbits]
    and edx,[ebp+highbits]
    add edx,ecx
    shr edx,1
    mov %1,dx
%endmacro

; interpolate16_5_2_1
; Mix three pixels with weight 5, 2, and 1, respectively: (c1*5+c2*2+c3)/8;
%macro Interp6 3
	; Unpack eax to ecx
	mov ecx, eax
	shl ecx, 16
	or  ecx, eax
	and ecx, [ebp+green_redBlue_Mask]

	; multiply c1 by 5
	lea ecx, [5*ecx]

	; unpack c2 to edx
	mov edx, %2
	shl edx, 16
	or  edx, %2
	and edx, [ebp+green_redBlue_Mask]

	; add 2*c2 to 5*c1
	lea ecx, [ecx + 2*edx]

	; unpack c3 to edx
	mov edx, %3
	shl edx, 16
	or  edx, %3
	and edx, [ebp+green_redBlue_Mask]

	; add c3 and 2*c2+c1*5, divide by 8, mask the result
	add edx, ecx
	shr edx, 3
	and edx, [ebp+green_redBlue_Mask]

	; finally, repack the mixed pixel
	mov ecx, edx
	shr ecx, 16
	or  edx, ecx

    mov %1,  dx
%endmacro

; interpolate16_6_1_1
; Mix three pixels with weight 6, 1, and 1, respectively: (c1*6+c2+c3)/8;
%macro Interp7 3
	; unpack c1 to ecx
	mov ecx, eax
	shl ecx, 16
	or  ecx, eax
	and ecx, [ebp+green_redBlue_Mask]

	; multiply c1 by 6
	lea ecx, [3*ecx]		; mul by 3
	add ecx, ecx			; mul by 2

	; unpack c2 to edx
	mov edx, %2
	shl edx, 16
	or  edx, %2
	and edx, [ebp+green_redBlue_Mask]

	; add c2 to c1*6
	add ecx, edx

	; unpack c3 to edx
	mov edx, %3
	shl edx, 16
	or  edx, %3
	and edx, [ebp+green_redBlue_Mask]

	; add c3 and c2+c1*3, divide by 8, mask the result
	add edx, ecx
	shr edx, 3
	and edx, [ebp+green_redBlue_Mask]

	; finally, repack the mixed pixel
	mov ecx, edx
	shr ecx, 16
	or  edx, ecx

    mov %1,  dx
%endmacro

; interpolate16_2_3_3
; Mix three pixels with weight 2, 3, and 3, respectively: (c1*2+(c2+c3)*3)/8;
%macro Interp9 3
	; unpack c2 to edx
	mov edx, %2
	shl edx, 16
	or  edx, %2
	and edx, [ebp+green_redBlue_Mask]

	; unpack c3 to ecx
	mov ecx, %3
	shl ecx, 16
	or  ecx, %3
	and ecx, [ebp+green_redBlue_Mask]

	; set edx to 3*(c2+c3)
	add edx, ecx
	lea edx, [3*edx]

	; unpack c1 to ecx
	mov ecx, eax
	shl ecx, 16
	or  ecx, eax
	and ecx, [ebp+green_redBlue_Mask]

	; sum 2*c1 + 3*(c2+c3), divide by 8, mask the result
	lea edx, [edx + 2*ecx]
	shr edx, 3
	and edx, [ebp+green_redBlue_Mask]

	; finally, repack the mixed pixel
	mov ecx, edx
	shr ecx, 16
	or  edx, ecx

    mov %1,  dx
%endmacro

; interpolate16_14_1_1
; Mix three pixels with weight 14, 1, and 1, respectively: (c1*14+c2+c3)/16;
%macro Interp10 3
	; unpack c1 to edx
	mov edx, eax
	shl edx, 16
	or  edx, eax
	and edx, [ebp+green_redBlue_Mask]

	; multiply c1 by 7 -> store in ecx
	lea ecx, [8*edx]
	sub ecx, edx

	; unpack c2 to edx
	mov edx, %2
	shl edx, 16
	or  edx, %2
	and edx, [ebp+green_redBlue_Mask]

	; add c2 to 2*ecx=2*(c1*7)=c1*14 -> store in ecx
	lea ecx, [edx + 2*ecx]

	; unpack c3 to edx
	mov edx, %3
	shl edx, 16
	or  edx, %3
	and edx, [ebp+green_redBlue_Mask]

	; add c3 and c2+c1*14, divide by 16, mask the result
	add edx, ecx
	shr edx, 4
	and edx, [ebp+green_redBlue_Mask]

	; finally, repack the mixed pixel
	mov ecx, edx
	shr ecx, 16
	or  edx, ecx

    mov %1,  dx
%endmacro

%macro PIXEL00_0 0
    mov [edi],ax
%endmacro

%macro PIXEL00_10 0
    Interp1 [edi],eax,[ebp+w1]
%endmacro

%macro PIXEL00_11 0
    Interp1 [edi],eax,[ebp+w4]
%endmacro

%macro PIXEL00_12 0
    Interp1 [edi],eax,[ebp+w2]
%endmacro

%macro PIXEL00_20 0
    Interp2 [edi],eax,[ebp+w4],[ebp+w2]
%endmacro

%macro PIXEL00_21 0
    Interp2 [edi],eax,[ebp+w1],[ebp+w2]
%endmacro

%macro PIXEL00_22 0
    Interp2 [edi],eax,[ebp+w1],[ebp+w4]
%endmacro

%macro PIXEL00_60 0
    Interp6 [edi],[ebp+w2],[ebp+w4]
%endmacro

%macro PIXEL00_61 0
    Interp6 [edi],[ebp+w4],[ebp+w2]
%endmacro

%macro PIXEL00_70 0
    Interp7 [edi],[ebp+w4],[ebp+w2]
%endmacro

%macro PIXEL00_90 0
    Interp9 [edi],[ebp+w4],[ebp+w2]
%endmacro

%macro PIXEL00_100 0
    Interp10 [edi],[ebp+w4],[ebp+w2]
%endmacro

%macro PIXEL01_0 0
    mov [edi+2],ax
%endmacro

%macro PIXEL01_10 0
    Interp1 [edi+2],eax,[ebp+w3]
%endmacro

%macro PIXEL01_11 0
    Interp1 [edi+2],eax,[ebp+w2]
%endmacro

%macro PIXEL01_12 0
    Interp1 [edi+2],eax,[ebp+w6]
%endmacro

%macro PIXEL01_20 0
    Interp2 [edi+2],eax,[ebp+w2],[ebp+w6]
%endmacro

%macro PIXEL01_21 0
    Interp2 [edi+2],eax,[ebp+w3],[ebp+w6]
%endmacro

%macro PIXEL01_22 0
    Interp2 [edi+2],eax,[ebp+w3],[ebp+w2]
%endmacro

%macro PIXEL01_60 0
    Interp6 [edi+2],[ebp+w6],[ebp+w2]
%endmacro

%macro PIXEL01_61 0
    Interp6 [edi+2],[ebp+w2],[ebp+w6]
%endmacro

%macro PIXEL01_70 0
    Interp7 [edi+2],[ebp+w2],[ebp+w6]
%endmacro

%macro PIXEL01_90 0
    Interp9 [edi+2],[ebp+w2],[ebp+w6]
%endmacro

%macro PIXEL01_100 0
    Interp10 [edi+2],[ebp+w2],[ebp+w6]
%endmacro

%macro PIXEL10_0 0
    mov [edi+ebx],ax
%endmacro

%macro PIXEL10_10 0
    Interp1 [edi+ebx],eax,[ebp+w7]
%endmacro

%macro PIXEL10_11 0
    Interp1 [edi+ebx],eax,[ebp+w8]
%endmacro

%macro PIXEL10_12 0
    Interp1 [edi+ebx],eax,[ebp+w4]
%endmacro

%macro PIXEL10_20 0
    Interp2 [edi+ebx],eax,[ebp+w8],[ebp+w4]
%endmacro

%macro PIXEL10_21 0
    Interp2 [edi+ebx],eax,[ebp+w7],[ebp+w4]
%endmacro

%macro PIXEL10_22 0
    Interp2 [edi+ebx],eax,[ebp+w7],[ebp+w8]
%endmacro

%macro PIXEL10_60 0
    Interp6 [edi+ebx],[ebp+w4],[ebp+w8]
%endmacro

%macro PIXEL10_61 0
    Interp6 [edi+ebx],[ebp+w8],[ebp+w4]
%endmacro

%macro PIXEL10_70 0
    Interp7 [edi+ebx],[ebp+w8],[ebp+w4]
%endmacro

%macro PIXEL10_90 0
    Interp9 [edi+ebx],[ebp+w8],[ebp+w4]
%endmacro

%macro PIXEL10_100 0
    Interp10 [edi+ebx],[ebp+w8],[ebp+w4]
%endmacro

%macro PIXEL11_0 0
    mov [edi+ebx+2],ax
%endmacro

%macro PIXEL11_10 0
    Interp1 [edi+ebx+2],eax,[ebp+w9]
%endmacro

%macro PIXEL11_11 0
    Interp1 [edi+ebx+2],eax,[ebp+w6]
%endmacro

%macro PIXEL11_12 0
    Interp1 [edi+ebx+2],eax,[ebp+w8]
%endmacro

%macro PIXEL11_20 0
    Interp2 [edi+ebx+2],eax,[ebp+w6],[ebp+w8]
%endmacro

%macro PIXEL11_21 0
    Interp2 [edi+ebx+2],eax,[ebp+w9],[ebp+w8]
%endmacro

%macro PIXEL11_22 0
    Interp2 [edi+ebx+2],eax,[ebp+w9],[ebp+w6]
%endmacro

%macro PIXEL11_60 0
    Interp6 [edi+ebx+2],[ebp+w8],[ebp+w6]
%endmacro

%macro PIXEL11_61 0
    Interp6 [edi+ebx+2],[ebp+w6],[ebp+w8]
%endmacro

%macro PIXEL11_70 0
    Interp7 [edi+ebx+2],[ebp+w6],[ebp+w8]
%endmacro

%macro PIXEL11_90 0
    Interp9 [edi+ebx+2],[ebp+w6],[ebp+w8]
%endmacro

%macro PIXEL11_100 0
    Interp10 [edi+ebx+2],[ebp+w6],[ebp+w8]
%endmacro

_hq2x_16:
    push ebp
    mov ebp,esp
    sub esp,112
    pushad

    call    _get_pc
.pc_anchor:
    mov     ecx,eax
    add     eax,(FuncTable-.pc_anchor)
    mov     dword[ebp+pFuncTable],eax
    add     ecx,(FuncTable2-.pc_anchor)
    mov     dword[ebp+pFuncTable2],ecx
    mov     dword[ebp+threshold],thresholdVal0
    mov     dword[ebp+threshold+4], thresholdVal1

    mov     esi,[ebp+hqx_params]
    lea     edi,[ebp+hqx_params_]
    mov     ecx,(green_redBlue_Mask+4-hqx_params_)/4
    rep     movsd

    mov     esi,[ebp+inbuffer]
    mov     edi,[ebp+outbuffer]
    mov     edx,[ebp+Yres]
    mov     [ebp+linesleft],edx
    mov     ecx,[ebp+Xres]
    shl     ecx,1
    mov     ebx,[ebp+dstPitch]
    mov     dword[ebp+moduloDst],ebx
    sub     dword[ebp+moduloDst],ecx
    shl     dword[ebp+moduloDst],1
    mov     ebx,[ebp+srcPitch]
    mov     dword[ebp+nextline],ebx
    mov     dword[ebp+moduloSrc],ebx
    sub     dword[ebp+moduloSrc],ecx
    neg     ebx
    mov     dword[ebp+prevline],ebx
.loopy:
    mov     ecx,[ebp+Xres]
    mov     dword[ebp+xcounter],ecx
.loopx:
    mov     ebx,[ebp+prevline]
    movq    mm5,[esi+ebx-2]
    movq    mm6,[esi-2]
    mov     ebx,[ebp+nextline]
    movq    mm7,[esi+ebx-2]
    movd    eax,mm5
    movzx   edx,ax
    mov     [ebp+w1],edx
    shr     eax,16
    mov     [ebp+w2],eax
    psrlq   mm5,32
    movd    eax,mm5
    movzx   edx,ax
    mov     [ebp+w3],edx
    movd    eax,mm6
    movzx   edx,ax
    mov     [ebp+w4],edx
    shr     eax,16
    mov     [ebp+w5],eax
    psrlq   mm6,32
    movd    eax,mm6
    movzx   edx,ax
    mov     [ebp+w6],edx
    movd    eax,mm7
    movzx   edx,ax
    mov     [ebp+w7],edx
    shr     eax,16
    mov     [ebp+w8],eax
    psrlq   mm7,32
    movd    eax,mm7
    movzx   edx,ax
    mov     [ebp+w9],edx
.flags:
    mov     ebx,[ebp+RGBtoYUV]
    mov     eax,[ebp+w5]
    xor     ecx,ecx
    movd    mm5,[ebx+eax*4]
    mov     dword[ebp+cross],0

    mov     edx,[ebp+w2]
    cmp     eax,edx
    je      .noflag2
    or      dword[ebp+cross],1
    movq    mm1,mm5
    movd    mm2,[ebx+edx*4]
    psubusb mm1,mm2
    psubusb mm2,mm5
    por     mm1,mm2
    psubusb mm1,[ebp+threshold]
    movd    edx,mm1
    test    edx,edx
    jz      .noflag2
    or      ecx,2
.noflag2:
    mov     edx,[ebp+w4]
    cmp     eax,edx
    je      .noflag4
    or      dword[ebp+cross],2
    movq    mm1,mm5
    movd    mm2,[ebx+edx*4]
    psubusb mm1,mm2
    psubusb mm2,mm5
    por     mm1,mm2
    psubusb mm1,[ebp+threshold]
    movd    edx,mm1
    test    edx,edx
    jz      .noflag4
    or      ecx,8
.noflag4:
    mov     edx,[ebp+w6]
    cmp     eax,edx
    je      .noflag6
    or      dword[ebp+cross],4
    movq    mm1,mm5
    movd    mm2,[ebx+edx*4]
    psubusb mm1,mm2
    psubusb mm2,mm5
    por     mm1,mm2
    psubusb mm1,[ebp+threshold]
    movd    edx,mm1
    test    edx,edx
    jz      .noflag6
    or      ecx,16
.noflag6:
    mov     edx,[ebp+w8]
    cmp     eax,edx
    je      .noflag8
    or      dword[ebp+cross],8
    movq    mm1,mm5
    movd    mm2,[ebx+edx*4]
    psubusb mm1,mm2
    psubusb mm2,mm5
    por     mm1,mm2
    psubusb mm1,[ebp+threshold]
    movd    edx,mm1
    test    edx,edx
    jz      .noflag8
    or      ecx,64
.noflag8:
    test    ecx,ecx
    jnz     .testflag1
    mov     ecx,[ebp+cross]
    mov     ebx, [ebp+pFuncTable2]
    mov     ecx, [ebx+ecx*4]
    add     ecx, ebx
    mov     ebx,[ebp+dstPitch]
    jmp     ecx
.testflag1:
    mov     edx,[ebp+w1]
    cmp     eax,edx
    je      .noflag1
    movq    mm1,mm5
    movd    mm2,[ebx+edx*4]
    psubusb mm1,mm2
    psubusb mm2,mm5
    por     mm1,mm2
    psubusb mm1,[ebp+threshold]
    movd    edx,mm1
    test    edx,edx
    jz      .noflag1
    or      ecx,1
.noflag1:
    mov     edx,[ebp+w3]
    cmp     eax,edx
    je      .noflag3
    movq    mm1,mm5
    movd    mm2,[ebx+edx*4]
    psubusb mm1,mm2
    psubusb mm2,mm5
    por     mm1,mm2
    psubusb mm1,[ebp+threshold]
    movd    edx,mm1
    test    edx,edx
    jz      .noflag3
    or      ecx,4
.noflag3:
    mov     edx,[ebp+w7]
    cmp     eax,edx
    je      .noflag7
    movq    mm1,mm5
    movd    mm2,[ebx+edx*4]
    psubusb mm1,mm2
    psubusb mm2,mm5
    por     mm1,mm2
    psubusb mm1,[ebp+threshold]
    movd    edx,mm1
    test    edx,edx
    jz      .noflag7
    or      ecx,32
.noflag7:
    mov     edx,[ebp+w9]
    cmp     eax,edx
    je      .noflag9
    movq    mm1,mm5
    movd    mm2,[ebx+edx*4]
    psubusb mm1,mm2
    psubusb mm2,mm5
    por     mm1,mm2
    psubusb mm1,[ebp+threshold]
    movd    edx,mm1
    test    edx,edx
    jz      .noflag9
    or      ecx,128
.noflag9:
    mov  ebx, [ebp+pFuncTable]
    mov  ecx, [ebx+ecx*4]
    add  ecx, ebx
    mov  ebx,[ebp+dstPitch]
    jmp  ecx

..@flag0:
..@flag1:
..@flag4:
..@flag32:
..@flag128:
..@flag5:
..@flag132:
..@flag160:
..@flag33:
..@flag129:
..@flag36:
..@flag133:
..@flag164:
..@flag161:
..@flag37:
..@flag165:
    PIXEL00_20
    PIXEL01_20
    PIXEL10_20
    PIXEL11_20
    jmp .loopx_end
..@flag2:
..@flag34:
..@flag130:
..@flag162:
    PIXEL00_22
    PIXEL01_21
    PIXEL10_20
    PIXEL11_20
    jmp .loopx_end
..@flag16:
..@flag17:
..@flag48:
..@flag49:
    PIXEL00_20
    PIXEL01_22
    PIXEL10_20
    PIXEL11_21
    jmp .loopx_end
..@flag64:
..@flag65:
..@flag68:
..@flag69:
    PIXEL00_20
    PIXEL01_20
    PIXEL10_21
    PIXEL11_22
    jmp .loopx_end
..@flag8:
..@flag12:
..@flag136:
..@flag140:
    PIXEL00_21
    PIXEL01_20
    PIXEL10_22
    PIXEL11_20
    jmp .loopx_end
..@flag3:
..@flag35:
..@flag131:
..@flag163:
    PIXEL00_11
    PIXEL01_21
    PIXEL10_20
    PIXEL11_20
    jmp .loopx_end
..@flag6:
..@flag38:
..@flag134:
..@flag166:
    PIXEL00_22
    PIXEL01_12
    PIXEL10_20
    PIXEL11_20
    jmp .loopx_end
..@flag20:
..@flag21:
..@flag52:
..@flag53:
    PIXEL00_20
    PIXEL01_11
    PIXEL10_20
    PIXEL11_21
    jmp .loopx_end
..@flag144:
..@flag145:
..@flag176:
..@flag177:
    PIXEL00_20
    PIXEL01_22
    PIXEL10_20
    PIXEL11_12
    jmp .loopx_end
..@flag192:
..@flag193:
..@flag196:
..@flag197:
    PIXEL00_20
    PIXEL01_20
    PIXEL10_21
    PIXEL11_11
    jmp .loopx_end
..@flag96:
..@flag97:
..@flag100:
..@flag101:
    PIXEL00_20
    PIXEL01_20
    PIXEL10_12
    PIXEL11_22
    jmp .loopx_end
..@flag40:
..@flag44:
..@flag168:
..@flag172:
    PIXEL00_21
    PIXEL01_20
    PIXEL10_11
    PIXEL11_20
    jmp .loopx_end
..@flag9:
..@flag13:
..@flag137:
..@flag141:
    PIXEL00_12
    PIXEL01_20
    PIXEL10_22
    PIXEL11_20
    jmp .loopx_end
..@flag18:
..@flag50:
    PIXEL00_22
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_10,PIXEL01_20
    PIXEL10_20
    PIXEL11_21
    jmp .loopx_end
..@flag80:
..@flag81:
    PIXEL00_20
    PIXEL01_22
    PIXEL10_21
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_10,PIXEL11_20
    jmp .loopx_end
..@flag72:
..@flag76:
    PIXEL00_21
    PIXEL01_20
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_10,PIXEL10_20
    PIXEL11_22
    jmp .loopx_end
..@flag10:
..@flag138:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_10,PIXEL00_20
    PIXEL01_21
    PIXEL10_22
    PIXEL11_20
    jmp .loopx_end
..@flag66:
    PIXEL00_22
    PIXEL01_21
    PIXEL10_21
    PIXEL11_22
    jmp .loopx_end
..@flag24:
    PIXEL00_21
    PIXEL01_22
    PIXEL10_22
    PIXEL11_21
    jmp .loopx_end
..@flag7:
..@flag39:
..@flag135:
    PIXEL00_11
    PIXEL01_12
    PIXEL10_20
    PIXEL11_20
    jmp .loopx_end
..@flag148:
..@flag149:
..@flag180:
    PIXEL00_20
    PIXEL01_11
    PIXEL10_20
    PIXEL11_12
    jmp .loopx_end
..@flag224:
..@flag228:
..@flag225:
    PIXEL00_20
    PIXEL01_20
    PIXEL10_12
    PIXEL11_11
    jmp .loopx_end
..@flag41:
..@flag169:
..@flag45:
    PIXEL00_12
    PIXEL01_20
    PIXEL10_11
    PIXEL11_20
    jmp .loopx_end
..@flag22:
..@flag54:
    PIXEL00_22
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_20
    PIXEL10_20
    PIXEL11_21
    jmp .loopx_end
..@flag208:
..@flag209:
    PIXEL00_20
    PIXEL01_22
    PIXEL10_21
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_20
    jmp .loopx_end
..@flag104:
..@flag108:
    PIXEL00_21
    PIXEL01_20
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_20
    PIXEL11_22
    jmp .loopx_end
..@flag11:
..@flag139:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_20
    PIXEL01_21
    PIXEL10_22
    PIXEL11_20
    jmp .loopx_end
..@flag19:
..@flag51:
    DiffOrNot ebp+w2,ebp+w6,PIXEL00_11,PIXEL01_10,PIXEL00_60,PIXEL01_90
    PIXEL10_20
    PIXEL11_21
    jmp .loopx_end
..@flag146:
..@flag178:
    PIXEL00_22
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_10,PIXEL11_12,PIXEL01_90,PIXEL11_61
    PIXEL10_20
    jmp .loopx_end
..@flag84:
..@flag85:
    PIXEL00_20
    DiffOrNot ebp+w6,ebp+w8,PIXEL01_11,PIXEL11_10,PIXEL01_60,PIXEL11_90
    PIXEL10_21
    jmp .loopx_end
..@flag112:
..@flag113:
    PIXEL00_20
    PIXEL01_22
    DiffOrNot ebp+w6,ebp+w8,PIXEL10_12,PIXEL11_10,PIXEL10_61,PIXEL11_90
    jmp .loopx_end
..@flag200:
..@flag204:
    PIXEL00_21
    PIXEL01_20
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_10,PIXEL11_11,PIXEL10_90,PIXEL11_60
    jmp .loopx_end
..@flag73:
..@flag77:
    DiffOrNot ebp+w8,ebp+w4,PIXEL00_12,PIXEL10_10,PIXEL00_61,PIXEL10_90
    PIXEL01_20
    PIXEL11_22
    jmp .loopx_end
..@flag42:
..@flag170:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_10,PIXEL10_11,PIXEL00_90,PIXEL10_60
    PIXEL01_21
    PIXEL11_20
    jmp .loopx_end
..@flag14:
..@flag142:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_10,PIXEL01_12,PIXEL00_90,PIXEL01_61
    PIXEL10_22
    PIXEL11_20
    jmp .loopx_end
..@flag67:
    PIXEL00_11
    PIXEL01_21
    PIXEL10_21
    PIXEL11_22
    jmp .loopx_end
..@flag70:
    PIXEL00_22
    PIXEL01_12
    PIXEL10_21
    PIXEL11_22
    jmp .loopx_end
..@flag28:
    PIXEL00_21
    PIXEL01_11
    PIXEL10_22
    PIXEL11_21
    jmp .loopx_end
..@flag152:
    PIXEL00_21
    PIXEL01_22
    PIXEL10_22
    PIXEL11_12
    jmp .loopx_end
..@flag194:
    PIXEL00_22
    PIXEL01_21
    PIXEL10_21
    PIXEL11_11
    jmp .loopx_end
..@flag98:
    PIXEL00_22
    PIXEL01_21
    PIXEL10_12
    PIXEL11_22
    jmp .loopx_end
..@flag56:
    PIXEL00_21
    PIXEL01_22
    PIXEL10_11
    PIXEL11_21
    jmp .loopx_end
..@flag25:
    PIXEL00_12
    PIXEL01_22
    PIXEL10_22
    PIXEL11_21
    jmp .loopx_end
..@flag26:
..@flag31:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_20
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_20
    PIXEL10_22
    PIXEL11_21
    jmp .loopx_end
..@flag82:
..@flag214:
    PIXEL00_22
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_20
    PIXEL10_21
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_20
    jmp .loopx_end
..@flag88:
..@flag248:
    PIXEL00_21
    PIXEL01_22
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_20
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_20
    jmp .loopx_end
..@flag74:
..@flag107:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_20
    PIXEL01_21
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_20
    PIXEL11_22
    jmp .loopx_end
..@flag27:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_20
    PIXEL01_10
    PIXEL10_22
    PIXEL11_21
    jmp .loopx_end
..@flag86:
    PIXEL00_22
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_20
    PIXEL10_21
    PIXEL11_10
    jmp .loopx_end
..@flag216:
    PIXEL00_21
    PIXEL01_22
    PIXEL10_10
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_20
    jmp .loopx_end
..@flag106:
    PIXEL00_10
    PIXEL01_21
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_20
    PIXEL11_22
    jmp .loopx_end
..@flag30:
    PIXEL00_10
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_20
    PIXEL10_22
    PIXEL11_21
    jmp .loopx_end
..@flag210:
    PIXEL00_22
    PIXEL01_10
    PIXEL10_21
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_20
    jmp .loopx_end
..@flag120:
    PIXEL00_21
    PIXEL01_22
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_20
    PIXEL11_10
    jmp .loopx_end
..@flag75:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_20
    PIXEL01_21
    PIXEL10_10
    PIXEL11_22
    jmp .loopx_end
..@flag29:
    PIXEL00_12
    PIXEL01_11
    PIXEL10_22
    PIXEL11_21
    jmp .loopx_end
..@flag198:
    PIXEL00_22
    PIXEL01_12
    PIXEL10_21
    PIXEL11_11
    jmp .loopx_end
..@flag184:
    PIXEL00_21
    PIXEL01_22
    PIXEL10_11
    PIXEL11_12
    jmp .loopx_end
..@flag99:
    PIXEL00_11
    PIXEL01_21
    PIXEL10_12
    PIXEL11_22
    jmp .loopx_end
..@flag57:
    PIXEL00_12
    PIXEL01_22
    PIXEL10_11
    PIXEL11_21
    jmp .loopx_end
..@flag71:
    PIXEL00_11
    PIXEL01_12
    PIXEL10_21
    PIXEL11_22
    jmp .loopx_end
..@flag156:
    PIXEL00_21
    PIXEL01_11
    PIXEL10_22
    PIXEL11_12
    jmp .loopx_end
..@flag226:
    PIXEL00_22
    PIXEL01_21
    PIXEL10_12
    PIXEL11_11
    jmp .loopx_end
..@flag60:
    PIXEL00_21
    PIXEL01_11
    PIXEL10_11
    PIXEL11_21
    jmp .loopx_end
..@flag195:
    PIXEL00_11
    PIXEL01_21
    PIXEL10_21
    PIXEL11_11
    jmp .loopx_end
..@flag102:
    PIXEL00_22
    PIXEL01_12
    PIXEL10_12
    PIXEL11_22
    jmp .loopx_end
..@flag153:
    PIXEL00_12
    PIXEL01_22
    PIXEL10_22
    PIXEL11_12
    jmp .loopx_end
..@flag58:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_10,PIXEL00_70
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_10,PIXEL01_70
    PIXEL10_11
    PIXEL11_21
    jmp .loopx_end
..@flag83:
    PIXEL00_11
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_10,PIXEL01_70
    PIXEL10_21
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_10,PIXEL11_70
    jmp .loopx_end
..@flag92:
    PIXEL00_21
    PIXEL01_11
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_10,PIXEL10_70
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_10,PIXEL11_70
    jmp .loopx_end
..@flag202:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_10,PIXEL00_70
    PIXEL01_21
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_10,PIXEL10_70
    PIXEL11_11
    jmp .loopx_end
..@flag78:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_10,PIXEL00_70
    PIXEL01_12
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_10,PIXEL10_70
    PIXEL11_22
    jmp .loopx_end
..@flag154:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_10,PIXEL00_70
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_10,PIXEL01_70
    PIXEL10_22
    PIXEL11_12
    jmp .loopx_end
..@flag114:
    PIXEL00_22
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_10,PIXEL01_70
    PIXEL10_12
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_10,PIXEL11_70
    jmp .loopx_end
..@flag89:
    PIXEL00_12
    PIXEL01_22
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_10,PIXEL10_70
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_10,PIXEL11_70
    jmp .loopx_end
..@flag90:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_10,PIXEL00_70
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_10,PIXEL01_70
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_10,PIXEL10_70
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_10,PIXEL11_70
    jmp .loopx_end
..@flag55:
..@flag23:
    DiffOrNot ebp+w2,ebp+w6,PIXEL00_11,PIXEL01_0,PIXEL00_60,PIXEL01_90
    PIXEL10_20
    PIXEL11_21
    jmp .loopx_end
..@flag182:
..@flag150:
    PIXEL00_22
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL11_12,PIXEL01_90,PIXEL11_61
    PIXEL10_20
    jmp .loopx_end
..@flag213:
..@flag212:
    PIXEL00_20
    DiffOrNot ebp+w6,ebp+w8,PIXEL01_11,PIXEL11_0,PIXEL01_60,PIXEL11_90
    PIXEL10_21
    jmp .loopx_end
..@flag241:
..@flag240:
    PIXEL00_20
    PIXEL01_22
    DiffOrNot ebp+w6,ebp+w8,PIXEL10_12,PIXEL11_0,PIXEL10_61,PIXEL11_90
    jmp .loopx_end
..@flag236:
..@flag232:
    PIXEL00_21
    PIXEL01_20
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL11_11,PIXEL10_90,PIXEL11_60
    jmp .loopx_end
..@flag109:
..@flag105:
    DiffOrNot ebp+w8,ebp+w4,PIXEL00_12,PIXEL10_0,PIXEL00_61,PIXEL10_90
    PIXEL01_20
    PIXEL11_22
    jmp .loopx_end
..@flag171:
..@flag43:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL10_11,PIXEL00_90,PIXEL10_60
    PIXEL01_21
    PIXEL11_20
    jmp .loopx_end
..@flag143:
..@flag15:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL01_12,PIXEL00_90,PIXEL01_61
    PIXEL10_22
    PIXEL11_20
    jmp .loopx_end
..@flag124:
    PIXEL00_21
    PIXEL01_11
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_20
    PIXEL11_10
    jmp .loopx_end
..@flag203:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_20
    PIXEL01_21
    PIXEL10_10
    PIXEL11_11
    jmp .loopx_end
..@flag62:
    PIXEL00_10
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_20
    PIXEL10_11
    PIXEL11_21
    jmp .loopx_end
..@flag211:
    PIXEL00_11
    PIXEL01_10
    PIXEL10_21
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_20
    jmp .loopx_end
..@flag118:
    PIXEL00_22
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_20
    PIXEL10_12
    PIXEL11_10
    jmp .loopx_end
..@flag217:
    PIXEL00_12
    PIXEL01_22
    PIXEL10_10
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_20
    jmp .loopx_end
..@flag110:
    PIXEL00_10
    PIXEL01_12
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_20
    PIXEL11_22
    jmp .loopx_end
..@flag155:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_20
    PIXEL01_10
    PIXEL10_22
    PIXEL11_12
    jmp .loopx_end
..@flag188:
    PIXEL00_21
    PIXEL01_11
    PIXEL10_11
    PIXEL11_12
    jmp .loopx_end
..@flag185:
    PIXEL00_12
    PIXEL01_22
    PIXEL10_11
    PIXEL11_12
    jmp .loopx_end
..@flag61:
    PIXEL00_12
    PIXEL01_11
    PIXEL10_11
    PIXEL11_21
    jmp .loopx_end
..@flag157:
    PIXEL00_12
    PIXEL01_11
    PIXEL10_22
    PIXEL11_12
    jmp .loopx_end
..@flag103:
    PIXEL00_11
    PIXEL01_12
    PIXEL10_12
    PIXEL11_22
    jmp .loopx_end
..@flag227:
    PIXEL00_11
    PIXEL01_21
    PIXEL10_12
    PIXEL11_11
    jmp .loopx_end
..@flag230:
    PIXEL00_22
    PIXEL01_12
    PIXEL10_12
    PIXEL11_11
    jmp .loopx_end
..@flag199:
    PIXEL00_11
    PIXEL01_12
    PIXEL10_21
    PIXEL11_11
    jmp .loopx_end
..@flag220:
    PIXEL00_21
    PIXEL01_11
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_10,PIXEL10_70
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_20
    jmp .loopx_end
..@flag158:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_10,PIXEL00_70
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_20
    PIXEL10_22
    PIXEL11_12
    jmp .loopx_end
..@flag234:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_10,PIXEL00_70
    PIXEL01_21
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_20
    PIXEL11_11
    jmp .loopx_end
..@flag242:
    PIXEL00_22
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_10,PIXEL01_70
    PIXEL10_12
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_20
    jmp .loopx_end
..@flag59:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_20
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_10,PIXEL01_70
    PIXEL10_11
    PIXEL11_21
    jmp .loopx_end
..@flag121:
    PIXEL00_12
    PIXEL01_22
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_20
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_10,PIXEL11_70
    jmp .loopx_end
..@flag87:
    PIXEL00_11
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_20
    PIXEL10_21
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_10,PIXEL11_70
    jmp .loopx_end
..@flag79:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_20
    PIXEL01_12
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_10,PIXEL10_70
    PIXEL11_22
    jmp .loopx_end
..@flag122:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_10,PIXEL00_70
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_10,PIXEL01_70
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_20
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_10,PIXEL11_70
    jmp .loopx_end
..@flag94:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_10,PIXEL00_70
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_20
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_10,PIXEL10_70
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_10,PIXEL11_70
    jmp .loopx_end
..@flag218:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_10,PIXEL00_70
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_10,PIXEL01_70
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_10,PIXEL10_70
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_20
    jmp .loopx_end
..@flag91:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_20
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_10,PIXEL01_70
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_10,PIXEL10_70
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_10,PIXEL11_70
    jmp .loopx_end
..@flag229:
    PIXEL00_20
    PIXEL01_20
    PIXEL10_12
    PIXEL11_11
    jmp .loopx_end
..@flag167:
    PIXEL00_11
    PIXEL01_12
    PIXEL10_20
    PIXEL11_20
    jmp .loopx_end
..@flag173:
    PIXEL00_12
    PIXEL01_20
    PIXEL10_11
    PIXEL11_20
    jmp .loopx_end
..@flag181:
    PIXEL00_20
    PIXEL01_11
    PIXEL10_20
    PIXEL11_12
    jmp .loopx_end
..@flag186:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_10,PIXEL00_70
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_10,PIXEL01_70
    PIXEL10_11
    PIXEL11_12
    jmp .loopx_end
..@flag115:
    PIXEL00_11
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_10,PIXEL01_70
    PIXEL10_12
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_10,PIXEL11_70
    jmp .loopx_end
..@flag93:
    PIXEL00_12
    PIXEL01_11
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_10,PIXEL10_70
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_10,PIXEL11_70
    jmp .loopx_end
..@flag206:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_10,PIXEL00_70
    PIXEL01_12
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_10,PIXEL10_70
    PIXEL11_11
    jmp .loopx_end
..@flag205:
..@flag201:
    PIXEL00_12
    PIXEL01_20
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_10,PIXEL10_70
    PIXEL11_11
    jmp .loopx_end
..@flag174:
..@flag46:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_10,PIXEL00_70
    PIXEL01_12
    PIXEL10_11
    PIXEL11_20
    jmp .loopx_end
..@flag179:
..@flag147:
    PIXEL00_11
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_10,PIXEL01_70
    PIXEL10_20
    PIXEL11_12
    jmp .loopx_end
..@flag117:
..@flag116:
    PIXEL00_20
    PIXEL01_11
    PIXEL10_12
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_10,PIXEL11_70
    jmp .loopx_end
..@flag189:
    PIXEL00_12
    PIXEL01_11
    PIXEL10_11
    PIXEL11_12
    jmp .loopx_end
..@flag231:
    PIXEL00_11
    PIXEL01_12
    PIXEL10_12
    PIXEL11_11
    jmp .loopx_end
..@flag126:
    PIXEL00_10
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_20
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_20
    PIXEL11_10
    jmp .loopx_end
..@flag219:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_20
    PIXEL01_10
    PIXEL10_10
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_20
    jmp .loopx_end
..@flag125:
    DiffOrNot ebp+w8,ebp+w4,PIXEL00_12,PIXEL10_0,PIXEL00_61,PIXEL10_90
    PIXEL01_11
    PIXEL11_10
    jmp .loopx_end
..@flag221:
    PIXEL00_12
    DiffOrNot ebp+w6,ebp+w8,PIXEL01_11,PIXEL11_0,PIXEL01_60,PIXEL11_90
    PIXEL10_10
    jmp .loopx_end
..@flag207:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL01_12,PIXEL00_90,PIXEL01_61
    PIXEL10_10
    PIXEL11_11
    jmp .loopx_end
..@flag238:
    PIXEL00_10
    PIXEL01_12
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL11_11,PIXEL10_90,PIXEL11_60
    jmp .loopx_end
..@flag190:
    PIXEL00_10
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL11_12,PIXEL01_90,PIXEL11_61
    PIXEL10_11
    jmp .loopx_end
..@flag187:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL10_11,PIXEL00_90,PIXEL10_60
    PIXEL01_10
    PIXEL11_12
    jmp .loopx_end
..@flag243:
    PIXEL00_11
    PIXEL01_10
    DiffOrNot ebp+w6,ebp+w8,PIXEL10_12,PIXEL11_0,PIXEL10_61,PIXEL11_90
    jmp .loopx_end
..@flag119:
    DiffOrNot ebp+w2,ebp+w6,PIXEL00_11,PIXEL01_0,PIXEL00_60,PIXEL01_90
    PIXEL10_12
    PIXEL11_10
    jmp .loopx_end
..@flag237:
..@flag233:
    PIXEL00_12
    PIXEL01_20
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_100
    PIXEL11_11
    jmp .loopx_end
..@flag175:
..@flag47:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_100
    PIXEL01_12
    PIXEL10_11
    PIXEL11_20
    jmp .loopx_end
..@flag183:
..@flag151:
    PIXEL00_11
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_100
    PIXEL10_20
    PIXEL11_12
    jmp .loopx_end
..@flag245:
..@flag244:
    PIXEL00_20
    PIXEL01_11
    PIXEL10_12
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_100
    jmp .loopx_end
..@flag250:
    PIXEL00_10
    PIXEL01_10
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_20
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_20
    jmp .loopx_end
..@flag123:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_20
    PIXEL01_10
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_20
    PIXEL11_10
    jmp .loopx_end
..@flag95:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_20
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_20
    PIXEL10_10
    PIXEL11_10
    jmp .loopx_end
..@flag222:
    PIXEL00_10
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_20
    PIXEL10_10
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_20
    jmp .loopx_end
..@flag252:
    PIXEL00_21
    PIXEL01_11
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_20
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_100
    jmp .loopx_end
..@flag249:
    PIXEL00_12
    PIXEL01_22
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_100
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_20
    jmp .loopx_end
..@flag235:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_20
    PIXEL01_21
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_100
    PIXEL11_11
    jmp .loopx_end
..@flag111:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_100
    PIXEL01_12
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_20
    PIXEL11_22
    jmp .loopx_end
..@flag63:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_100
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_20
    PIXEL10_11
    PIXEL11_21
    jmp .loopx_end
..@flag159:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_20
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_100
    PIXEL10_22
    PIXEL11_12
    jmp .loopx_end
..@flag215:
    PIXEL00_11
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_100
    PIXEL10_21
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_20
    jmp .loopx_end
..@flag246:
    PIXEL00_22
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_20
    PIXEL10_12
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_100
    jmp .loopx_end
..@flag254:
    PIXEL00_10
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_20
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_20
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_100
    jmp .loopx_end
..@flag253:
    PIXEL00_12
    PIXEL01_11
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_100
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_100
    jmp .loopx_end
..@flag251:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_20
    PIXEL01_10
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_100
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_20
    jmp .loopx_end
..@flag239:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_100
    PIXEL01_12
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_100
    PIXEL11_11
    jmp .loopx_end
..@flag127:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_100
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_20
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_20
    PIXEL11_10
    jmp .loopx_end
..@flag191:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_100
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_100
    PIXEL10_11
    PIXEL11_12
    jmp .loopx_end
..@flag223:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_20
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_100
    PIXEL10_10
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_20
    jmp .loopx_end
..@flag247:
    PIXEL00_11
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_100
    PIXEL10_12
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_100
    jmp .loopx_end
..@flag255:
    DiffOrNot ebp+w4,ebp+w2,PIXEL00_0,PIXEL00_100
    DiffOrNot ebp+w2,ebp+w6,PIXEL01_0,PIXEL01_100
    DiffOrNot ebp+w8,ebp+w4,PIXEL10_0,PIXEL10_100
    DiffOrNot ebp+w6,ebp+w8,PIXEL11_0,PIXEL11_100
    jmp .loopx_end

..@cross0:
    mov     edx,eax
    shl     eax,16
    or      eax,edx
    mov     [edi],eax
    mov     [edi+ebx],eax
    jmp     .loopx_end
..@cross1:
    mov     edx,eax
    shl     eax,16
    or      eax,edx
    mov     ecx,[ebp+w2]
    and     edx,[ebp+highbits]
    and     ecx,[ebp+highbits]
    add     ecx,edx
    shr     ecx,1
    add     ecx,[ebp+lowbits]
    and     ecx,[ebp+highbits]
    add     edx,ecx
    shr     edx,1
    mov     ecx,edx
    shl     edx,16
    or      edx,ecx
    mov     [edi],edx
    mov     [edi+ebx],eax
    jmp     .loopx_end
..@cross2:
    shl     eax,16
    mov     ecx,[ebp+w4]
    and     edx,[ebp+highbits]
    and     ecx,[ebp+highbits]
    add     ecx,edx
    shr     ecx,1
    add     ecx,[ebp+lowbits]
    and     ecx,[ebp+highbits]
    add     edx,ecx
    shr     edx,1
    or      eax,edx
    mov     [edi],eax
    mov     [edi+ebx],eax
    jmp     .loopx_end
..@cross4:
    mov     ecx,[ebp+w6]
    and     edx,[ebp+highbits]
    and     ecx,[ebp+highbits]
    add     ecx,edx
    shr     ecx,1
    add     ecx,[ebp+lowbits]
    and     ecx,[ebp+highbits]
    add     edx,ecx
    shr     edx,1
    shl     edx,16
    or      eax,edx
    mov     [edi],eax
    mov     [edi+ebx],eax
    jmp     .loopx_end
..@cross8:
    mov     edx,eax
    shl     eax,16
    or      eax,edx
    mov     ecx,[ebp+w8]
    and     edx,[ebp+highbits]
    and     ecx,[ebp+highbits]
    add     ecx,edx
    shr     ecx,1
    add     ecx,[ebp+lowbits]
    and     ecx,[ebp+highbits]
    add     edx,ecx
    shr     edx,1
    mov     ecx,edx
    shl     edx,16
    or      edx,ecx
    mov     [edi],eax
    mov     [edi+ebx],edx
    jmp     .loopx_end

.loopx_end:
    add     esi,2
    add     edi,4
    dec     dword[ebp+xcounter]
    jz      .nexty
    jmp     .loopx
.nexty:
    add     esi,dword[ebp+moduloSrc]
    add     edi,dword[ebp+moduloDst]
    dec     dword[ebp+linesleft]
    jz      .fin
    mov     ebx,[ebp+srcPitch]
    mov     dword[ebp+nextline],ebx
    neg     ebx
    mov     dword[ebp+prevline],ebx
    jmp     .loopy
.fin:
    emms
    popad
    mov esp,ebp
    pop ebp
    ret

_get_pc:
    mov     eax, dword[esp]
    ret

FuncTable:
    dd ..@flag0 - FuncTable, ..@flag1 - FuncTable, ..@flag2 - FuncTable, ..@flag3 - FuncTable, ..@flag4 - FuncTable, ..@flag5 - FuncTable, ..@flag6 - FuncTable, ..@flag7 - FuncTable
    dd ..@flag8 - FuncTable, ..@flag9 - FuncTable, ..@flag10 - FuncTable, ..@flag11 - FuncTable, ..@flag12 - FuncTable, ..@flag13 - FuncTable, ..@flag14 - FuncTable, ..@flag15 - FuncTable
    dd ..@flag16 - FuncTable, ..@flag17 - FuncTable, ..@flag18 - FuncTable, ..@flag19 - FuncTable, ..@flag20 - FuncTable, ..@flag21 - FuncTable, ..@flag22 - FuncTable, ..@flag23 - FuncTable
    dd ..@flag24 - FuncTable, ..@flag25 - FuncTable, ..@flag26 - FuncTable, ..@flag27 - FuncTable, ..@flag28 - FuncTable, ..@flag29 - FuncTable, ..@flag30 - FuncTable, ..@flag31 - FuncTable
    dd ..@flag32 - FuncTable, ..@flag33 - FuncTable, ..@flag34 - FuncTable, ..@flag35 - FuncTable, ..@flag36 - FuncTable, ..@flag37 - FuncTable, ..@flag38 - FuncTable, ..@flag39 - FuncTable
    dd ..@flag40 - FuncTable, ..@flag41 - FuncTable, ..@flag42 - FuncTable, ..@flag43 - FuncTable, ..@flag44 - FuncTable, ..@flag45 - FuncTable, ..@flag46 - FuncTable, ..@flag47 - FuncTable
    dd ..@flag48 - FuncTable, ..@flag49 - FuncTable, ..@flag50 - FuncTable, ..@flag51 - FuncTable, ..@flag52 - FuncTable, ..@flag53 - FuncTable, ..@flag54 - FuncTable, ..@flag55 - FuncTable
    dd ..@flag56 - FuncTable, ..@flag57 - FuncTable, ..@flag58 - FuncTable, ..@flag59 - FuncTable, ..@flag60 - FuncTable, ..@flag61 - FuncTable, ..@flag62 - FuncTable, ..@flag63 - FuncTable
    dd ..@flag64 - FuncTable, ..@flag65 - FuncTable, ..@flag66 - FuncTable, ..@flag67 - FuncTable, ..@flag68 - FuncTable, ..@flag69 - FuncTable, ..@flag70 - FuncTable, ..@flag71 - FuncTable
    dd ..@flag72 - FuncTable, ..@flag73 - FuncTable, ..@flag74 - FuncTable, ..@flag75 - FuncTable, ..@flag76 - FuncTable, ..@flag77 - FuncTable, ..@flag78 - FuncTable, ..@flag79 - FuncTable
    dd ..@flag80 - FuncTable, ..@flag81 - FuncTable, ..@flag82 - FuncTable, ..@flag83 - FuncTable, ..@flag84 - FuncTable, ..@flag85 - FuncTable, ..@flag86 - FuncTable, ..@flag87 - FuncTable
    dd ..@flag88 - FuncTable, ..@flag89 - FuncTable, ..@flag90 - FuncTable, ..@flag91 - FuncTable, ..@flag92 - FuncTable, ..@flag93 - FuncTable, ..@flag94 - FuncTable, ..@flag95 - FuncTable
    dd ..@flag96 - FuncTable, ..@flag97 - FuncTable, ..@flag98 - FuncTable, ..@flag99 - FuncTable, ..@flag100 - FuncTable, ..@flag101 - FuncTable, ..@flag102 - FuncTable, ..@flag103 - FuncTable
    dd ..@flag104 - FuncTable, ..@flag105 - FuncTable, ..@flag106 - FuncTable, ..@flag107 - FuncTable, ..@flag108 - FuncTable, ..@flag109 - FuncTable, ..@flag110 - FuncTable, ..@flag111 - FuncTable
    dd ..@flag112 - FuncTable, ..@flag113 - FuncTable, ..@flag114 - FuncTable, ..@flag115 - FuncTable, ..@flag116 - FuncTable, ..@flag117 - FuncTable, ..@flag118 - FuncTable, ..@flag119 - FuncTable
    dd ..@flag120 - FuncTable, ..@flag121 - FuncTable, ..@flag122 - FuncTable, ..@flag123 - FuncTable, ..@flag124 - FuncTable, ..@flag125 - FuncTable, ..@flag126 - FuncTable, ..@flag127 - FuncTable
    dd ..@flag128 - FuncTable, ..@flag129 - FuncTable, ..@flag130 - FuncTable, ..@flag131 - FuncTable, ..@flag132 - FuncTable, ..@flag133 - FuncTable, ..@flag134 - FuncTable, ..@flag135 - FuncTable
    dd ..@flag136 - FuncTable, ..@flag137 - FuncTable, ..@flag138 - FuncTable, ..@flag139 - FuncTable, ..@flag140 - FuncTable, ..@flag141 - FuncTable, ..@flag142 - FuncTable, ..@flag143 - FuncTable
    dd ..@flag144 - FuncTable, ..@flag145 - FuncTable, ..@flag146 - FuncTable, ..@flag147 - FuncTable, ..@flag148 - FuncTable, ..@flag149 - FuncTable, ..@flag150 - FuncTable, ..@flag151 - FuncTable
    dd ..@flag152 - FuncTable, ..@flag153 - FuncTable, ..@flag154 - FuncTable, ..@flag155 - FuncTable, ..@flag156 - FuncTable, ..@flag157 - FuncTable, ..@flag158 - FuncTable, ..@flag159 - FuncTable
    dd ..@flag160 - FuncTable, ..@flag161 - FuncTable, ..@flag162 - FuncTable, ..@flag163 - FuncTable, ..@flag164 - FuncTable, ..@flag165 - FuncTable, ..@flag166 - FuncTable, ..@flag167 - FuncTable
    dd ..@flag168 - FuncTable, ..@flag169 - FuncTable, ..@flag170 - FuncTable, ..@flag171 - FuncTable, ..@flag172 - FuncTable, ..@flag173 - FuncTable, ..@flag174 - FuncTable, ..@flag175 - FuncTable
    dd ..@flag176 - FuncTable, ..@flag177 - FuncTable, ..@flag178 - FuncTable, ..@flag179 - FuncTable, ..@flag180 - FuncTable, ..@flag181 - FuncTable, ..@flag182 - FuncTable, ..@flag183 - FuncTable
    dd ..@flag184 - FuncTable, ..@flag185 - FuncTable, ..@flag186 - FuncTable, ..@flag187 - FuncTable, ..@flag188 - FuncTable, ..@flag189 - FuncTable, ..@flag190 - FuncTable, ..@flag191 - FuncTable
    dd ..@flag192 - FuncTable, ..@flag193 - FuncTable, ..@flag194 - FuncTable, ..@flag195 - FuncTable, ..@flag196 - FuncTable, ..@flag197 - FuncTable, ..@flag198 - FuncTable, ..@flag199 - FuncTable
    dd ..@flag200 - FuncTable, ..@flag201 - FuncTable, ..@flag202 - FuncTable, ..@flag203 - FuncTable, ..@flag204 - FuncTable, ..@flag205 - FuncTable, ..@flag206 - FuncTable, ..@flag207 - FuncTable
    dd ..@flag208 - FuncTable, ..@flag209 - FuncTable, ..@flag210 - FuncTable, ..@flag211 - FuncTable, ..@flag212 - FuncTable, ..@flag213 - FuncTable, ..@flag214 - FuncTable, ..@flag215 - FuncTable
    dd ..@flag216 - FuncTable, ..@flag217 - FuncTable, ..@flag218 - FuncTable, ..@flag219 - FuncTable, ..@flag220 - FuncTable, ..@flag221 - FuncTable, ..@flag222 - FuncTable, ..@flag223 - FuncTable
    dd ..@flag224 - FuncTable, ..@flag225 - FuncTable, ..@flag226 - FuncTable, ..@flag227 - FuncTable, ..@flag228 - FuncTable, ..@flag229 - FuncTable, ..@flag230 - FuncTable, ..@flag231 - FuncTable
    dd ..@flag232 - FuncTable, ..@flag233 - FuncTable, ..@flag234 - FuncTable, ..@flag235 - FuncTable, ..@flag236 - FuncTable, ..@flag237 - FuncTable, ..@flag238 - FuncTable, ..@flag239 - FuncTable
    dd ..@flag240 - FuncTable, ..@flag241 - FuncTable, ..@flag242 - FuncTable, ..@flag243 - FuncTable, ..@flag244 - FuncTable, ..@flag245 - FuncTable, ..@flag246 - FuncTable, ..@flag247 - FuncTable
    dd ..@flag248 - FuncTable, ..@flag249 - FuncTable, ..@flag250 - FuncTable, ..@flag251 - FuncTable, ..@flag252 - FuncTable, ..@flag253 - FuncTable, ..@flag254 - FuncTable, ..@flag255 - FuncTable

FuncTable2:
    dd ..@cross0 - FuncTable2, ..@cross1 - FuncTable2, ..@cross2 - FuncTable2, ..@flag0 - FuncTable2,
    dd ..@cross4 - FuncTable2, ..@flag0  - FuncTable2, ..@flag0  - FuncTable2, ..@flag0 - FuncTable2,
    dd ..@cross8 - FuncTable2, ..@flag0  - FuncTable2, ..@flag0  - FuncTable2, ..@flag0 - FuncTable2,
    dd ..@flag0  - FuncTable2, ..@flag0  - FuncTable2, ..@flag0  - FuncTable2, ..@flag0 - FuncTable2


%ifidn __OUTPUT_FORMAT__,elf
section .note.GNU-stack noalloc noexec nowrite progbits
%endif
