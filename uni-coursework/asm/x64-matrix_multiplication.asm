;
; ***************************************************************
;       SKELETON: INTEL ASSEMBLER MATRIX MULTIPLY (LINUX)
; ***************************************************************
;
;
; --------------------------------------------------------------------------
; class matrix {
;     int ROWS              // ints are 64-bit
;     int COLS
;     int elem [ROWS][COLS]
;
;     void print () {
;         output.newline ()
;         for (int row=0; row < this.ROWS; row++) {
;             for (int col=0; col < this.COLS; cols++) {
;                 output.tab ()
;                 output.int (this.elem[row, col])
;             }
;             output.newline ()
;         }
;     }
;
;     void mult (matrix A, matrix B) {
;         for (int row=0; row < this.ROWS; row++) {
;             for (int col=0; col < this.COLS; cols++) {
;                 int sum = 0
;                 for (int k=0; k < A.COLS; k++)
;                     sum = sum + A.elem[row, k] * B.elem[k, col]
;                 this.elem [row, col] = sum
;             }
;         }
;     }
; }
; ---------------------------------------------------------------------------
; main () {
;     matrix matrixA, matrixB, matrixC  ; Declare and suitably initialise
;                                         matrices A, B and C
;     matrixA.print ()
;     matrixB.print ()
;     matrixC.mult (matrixA, matrixB)
;     matrixC.print ()
; }
; ---------------------------------------------------------------------------
;
; Notes:
; 1. For conditional jump instructions use the form 'Jxx NEAR label'  if label
;    is more than 127 bytes from the jump instruction Jxx.
;    For example use 'JGE NEAR end_for' instead of 'JGE end_for', if the
;    assembler complains that the label end_for is more than 127 bytes from
;    the JGE instruction with a message like 'short jump is out of  range'
;
;
; ---------------------------------------------------------------------------

segment .text
        global  _start
_start:

main:
         mov  rax, matrixA     ; matrixA.print ()
         push rax
         call matrix_print
         add  rsp, 8

         mov  rax, matrixB     ; matrixB.print ()
         push rax
         call matrix_print
         add  rsp, 8

         mov  rax, matrixB     ; matrixC.mult (matrixA, matrixB)
         push rax
         mov  rax, matrixA
         push rax
         mov  rax, matrixC
         push rax
         call matrix_mult
         add  rsp, 24          ; pop parameters & object reference
         mov  rax, matrixC     ; matrixC.print ()
         push rax
         call matrix_print
         add  rsp, 8

         call os_return                ; return to operating system

; ---------------------------------------------------------------------

matrix_print:
  ;Prints out a matrix with tab spaces (each row on a new line)
  push rbp
  mov rbp,rsp
  
  push rbx  ;Save rbx 
  push rcx  ;Save rcx
  push rdx  ;Save rdx
  push rsi  ;Save rsi
  
  call output_newline ;Outputs a new lone
  lea rbx,[rbp+16]    ;Calculate the base address of the matrix  
  mov rsi,[rbx]       ;Point rsi to rbx (we dereference rbx since LEA only calculates the address)
  mov rbx,rsi         ;Point rbx to base of matrix
  add rsi,16          ;Point rsi to the first element of the matrix
  
  ;row = RCX
  ;col = RDX

for1:
  xor rcx,rcx         ;Clear rcx (rcx = row = 0)
loop1:
  cmp rcx,[rbx]       ;Compare row with matrix.rows
  jge end1            ;Jump out of loop on ¬cond
for2:
  xor rdx,rdx         ;Clear rdx (rdx = col = 0)
loop2:
  cmp rdx,[rbx+8]     ;Compare col with matrix.cols
  jge end2            ;Jump out of loop on ¬cond
  call output_tab     ;Output a tab
  push qword[rsi]     ;Push first element onto the stack to be printed
  call output_int     ;Print out the element
  add rsp,8           ;Restore the stack pointer (output_int leaves some garbage on the stack)
  add rsi,8           ;Advance rsi to point to next element
  inc rdx             ;rdx++ = col++
  jmp loop2           ;Jump to top of inner loop
end2:
  call output_newline ;Output a new line 
  inc rcx             ;rcx++ = row++
  jmp loop1           ;Jump to top of outer loop  
end1:
  pop rsi             ;Restore rsi
  pop rdx             ;Restore rdx
  pop rcx             ;Restore rcx
  pop rbx             ;Restore rbx
  pop rbp             ;Restore rbp
  ret                 ;Return 
   
;  --------------------------------------------------------------------------

matrix_mult:
  push rbp
  mov rbp,rsp
  
  ;Multiplies two matrices together 
  
  push rbx  ;Save rbx
  push rcx  ;Save rcx
  push rdx  ;Save rdx
  push rsi  ;Save rsi
  push rdi  ;Save rdi
 
 
  ;Matrix[i][j] = Base_Address + (Row * Row_Size + Col) * 8
  ;Base_Adress = Address of first element of array (Usually +16 of matrix address)
  ;rbx = row
  ;rcx = col
  ;rdx = k
  ;rax = sum 
  
  lea rax,[rbp+16]    ;Calculate base address of matrixC
  mov rax,[rax]       ;Store in rax 
  push qword[rax]     ;Push C.ROWS onto stack
  push qword[rax+8]   ;Push C.COLS onto stack 
  lea rax,[rbp+24]    ;Calculate base address of matrixA
  mov rax,[rax]       ;Store in rax 
  push qword[rax+8]   ;Push A.COLS onto stack 
  lea rax,[rbp+32]    ;Calculate base address of matrixB
  mov rax,[rax]       ;Store in rax
  push qword[rax+8]   ;Push B.ROW_SIZE onto stack 
  
  push r8             ;Save r8 (This shouldn't really be used but I realised I needed it at the end)            
  
for3:
  xor rbx,rbx         ;Clear rbx (rbx = row = 0)
loop3:
  cmp rbx,[rbp-48]    ;Compare row with C.ROWS 
  jge end3            ;Jump out of loop on ¬cond 
for4:
  xor rcx,rcx         ;Clear rcx (rcx = col = 0)
loop4:
  cmp rcx,[rbp-56]    ;Compare col with C.COLS 
  jge end4            ;Jump out of loop on ¬cond
  xor rax,rax         ;Clear rax (rax = sum = 0)
for5:
  xor rdx,rdx         ;Clear rdx (rdx = k = 0)
loop5:
  cmp rdx,[rbp-64]    ;Compare k with A.COLS
  jge end5            ;Jump out of loop on ¬cond   
  ;A[row][k]
  mov rsi,[rbp-64]     ;rsi = A.ROW_SIZE    
  imul rsi,rbx         ;rsi = A.ROW_SIZE * row 
  add rsi,rdx          ;rsi = A.ROW_SIZE * row + k 
  lea rsi,[rsi*8]      ;rsi = (A.ROW_SIZE * row + k) * 8
  mov rdi,[rbp+24]     ;Get address of matrixA
  lea rsi,[rsi+rdi+16] ;rsi = A.BASE_ADDRESS + (A.ROW_SIZE * row + k) * 8 
  mov rsi,[rsi]        ;rsi = A[row][k]
  ;B[k][col]
  mov rdi,[rbp-72]     ;rdi = B.ROW_SIZE 
  imul rdi,rdx         ;rdi = B.ROW_SIZE * k 
  add rdi,rcx          ;rdi = B.ROW_SIZE * k + col
  lea rdi,[rdi*8]      ;rdi = (B.ROW_SIZE * k + col) * 8
  mov r8,[rbp+32]      ;Get address of matrixB
  lea rdi,[rdi+r8+16]  ;rdi = B.BASE_ADDRESS + (B.ROW_SIZE * k + col) * 8  
  mov rdi,[rdi]        ;rdi = B[k][col] 
  imul rdi,rsi         ;rdi = A[row][k] * B[k][col]
  ;sum += A[row][k] * B[k][col]
  add rax,rdi          ;rax += A[row][k] * B[k][col]
  inc rdx              ;rdx++ = k++
  jmp loop5            ;Jump to top of current loop 
end5:
  ;C[row][col] = sum 
  mov rsi,[rbp-56]     ;rsi = C.ROW_SIZE 
  imul rsi,rbx         ;rsi = C.ROW_SIZE * row 
  add rsi,rcx          ;rsi = C.ROW_SIZE * row + col 
  lea rsi,[rsi*8]      ;rsi = (C.ROW_SIZE * row + col) * 8
  mov rdi,[rbp+16]     ;Get address of matrixC                      
  lea rsi,[rsi+rdi+16] ;rsi = C.BASE_ADDRESS + (C.ROW_SIZE * row + col) * 8
  mov qword[rsi],rax   ;C[row][k] = sum 
  inc rcx              ;rcx++ = col++
  jmp loop4            ;Jump to top of current loop 
end4:
  inc rbx              ;rbx++ = row++
  jmp loop3            ;Jump to outer most loop 
end3:
  jmp matrix_mult_end  ;Jump out of all loops to end of function 
matrix_mult_end:
  pop r8
  add rsp,32           ;Restore rsp to point to rdi 
  pop rdi              ;Restore rdi 
  pop rsi              ;Restore rsi 
  pop rdx              ;Restore rdx 
  pop rcx              ;Restore rcx 
  pop rbx              ;Restore rbx 
  pop rbp              ;Restore rbp 
  ret                  ;Return 

; ---------------------------------------------------------------------
;                    ADDITIONAL METHODS

CR      equ     13              ; carriage-return
LF      equ     10              ; line-feed
TAB     equ     9               ; tab
MINUS   equ     '-'             ; minus

LINUX   equ     80H             ; interupt number for entering Linux kernel
EXIT    equ     1               ; Linux system call 1 i.e. exit ()
WRITE   equ     4               ; Linux system call 4 i.e. write ()
STDOUT  equ     1               ; File descriptor 1 i.e. standard output

; ------------------------

os_return:
        mov  rax, EXIT          ; Linux system call 1 i.e. exit ()
        mov  rbx, 0             ; Error code 0 i.e. no errors
        int  LINUX              ; Interrupt Linux kernel

output_char:                    ; void output_char (ch)
        push rax
        push rbx
        push rcx
        push rdx    ;SYNTAX ERROR? (Originally rdxi)
        push r8                ; r8..r11 are altered by Linux kernel interrupt
        push r9
        push r10
        push r11
        push qword [octetbuffer] ; (just to make output_char() re-entrant...)

        mov  rax, WRITE         ; Linux system call 4; i.e. write ()
        mov  rbx, STDOUT        ; File descriptor 1 i.e. standard output
        mov  rcx, [rsp+80]      ; fetch char from non-I/O-accessible segment
        mov  [octetbuffer], rcx ; load into 1-octet buffer
        lea  rcx, [octetbuffer] ; Address of 1-octet buffer
        mov  rdx, 1             ; Output 1 character only
        int  LINUX              ; Interrupt Linux kernel

        pop qword [octetbuffer]
        pop  r11
        pop  r10
        pop  r9
        pop  r8
        pop  rdx
        pop  rcx
        pop  rbx
        pop  rax
        ret

; ------------------------

output_newline:                 ; void output_newline ()
       push qword LF
       call output_char
       add rsp, 8
       ret

; ------------------------

output_tab:                     ; void output_tab ()
       push qword TAB
       call output_char
       add  rsp, 8
       ret

; ------------------------

output_minus:                   ; void output_minus()
       push qword MINUS
       call output_char
       add  rsp, 8
       ret

; ------------------------

output_int:                     ; void output_int (int N)
       push rbp
       mov  rbp, rsp

       ; rax=N then N/10, rdx=N%10, rbx=10

       push rax                ; save registers
       push rbx
       push rdx

       cmp  qword [rbp+16], 0 ; minus sign for negative numbers
       jge  L88

       call output_minus
       neg  qword [rbp+16]

L88:
       mov  rax, [rbp+16]       ; rax = N
       mov  rdx, 0              ; rdx:rax = N (unsigned equivalent of "cqo")
       mov  rbx, 10
       idiv rbx                ; rax=N/10, rdx=N%10

       cmp  rax, 0              ; skip if N<10
       je   L99

       push rax                ; output.int (N / 10)
       call output_int
       add  rsp, 8

L99:
       add  rdx, '0'           ; output char for digit N % 10
       push rdx
       call output_char
       add  rsp, 8

       pop  rdx                ; restore registers
       pop  rbx
       pop  rax
       pop  rbp
       ret


; ---------------------------------------------------------------------

segment .data

        ; Declare test matrices
matrixA DQ 2                    ; ROWS
        DQ 3                    ; COLS
        DQ 1, 2, 3              ; 1st row
        DQ 4, 5, 6              ; 2nd row

matrixB DQ 3                    ; ROWS
        DQ 2                    ; COLS
        DQ 1, 2                 ; 1st row
        DQ 3, 4                 ; 2nd row
        DQ 5, 6                 ; 3rd row

matrixC DQ 2                    ; ROWS
        DQ 2                    ; COLS
        DQ 0, 0                 ; space for ROWS*COLS ints
        DQ 0, 0                 ; (for filling in with matrixA*matrixB)

; ---------------------------------------------------------------------

        ; The following is used by output_char - do not disturb
        ;
        ; space in I/O-accessible segment for 1-octet output buffer
octetbuffer     DQ 0            ; (qword as choice of size on stack)

