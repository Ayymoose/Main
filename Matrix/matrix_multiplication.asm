
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

         mov  rax, matrixB     ; matrixC.mult (matrixA, matrixB)               | 80 CHAR LIMIT
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

matrix_print:                   ; void matrix_print ()
         push rbp                ; setup base pointer
         mov  rbp, rsp
         
         call output_newline          ;Output a new line                
         lea rbp,[rax+16]             ;Calcuate base address to offset from            
         for1: xor rcx,rcx            ;for (row=0; ... (Clear rcx)                  
         loop1:
           cmp rcx,[rax]              ;row < C.ROWS (row >= C.ROWS) 
           jge end1                   ;Jump out of loop                                                    
           for2: xor rdx,rdx          ;for (col=0; ... (Clear rdx)
           loop2:
              cmp rdx,[rax+8]         ;col < C.COLS (col >= C.COLS)     
	      jge end2                ;Jump out of loop                      
              call output_tab         ;Output tab
              push qword[rbp]         ;Calculate address of an element and push onto stack
              call output_int         ;Print element
              add rsp,8               ;Restore stack pointer
              add rbp,8               ;Increment base pointer to point to next element
              inc rdx                 ;col++
              jmp loop2;              ;Jump back to top of loop 
                end2:   
                  call output_newline ;Output newline                                     
              inc rcx                 ;row++
              jmp loop1 	      ;Jump back to outer loop  
         end1:
         pop  rbp                ; restore base pointer & return
         ret
;  --------------------------------------------------------------------------

matrix_mult:                    ; void matix_mult (matrix A, matrix B)

         push rbp                ; setup base pointer
         mov  rbp, rsp
          
         ;REGISTER TO VARIABLE MAP         
 
         ;rbx      = row
         ;rcx      = col
         ;rdx      = k
         ;r8       = A.COLS
         ;r9       = sum

         ;[r10+8]  = A.COLS
         ;[r12]    = C.ROWS
         ;[r12+8]  = C.COLS                                     
         
         ;r10 = matrixA
         ;r11 = matrixB
         ;r12 = matrixC           
 
         ;Use lea instruction to calculate base addresses
         ;MATRIX BASE ADDRESSES
         
         ;matrixA
         mov r10,[rbp+24]
         lea r10,[r10]        
         ;matrixB
         mov r11,[rbp+32]
         lea r11,[r11]
         ;matrixC
         mov r12,[rbp+16]
         lea r12,[r12] 
                
         for3: xor rbx,rbx            ;for (row=0; ...) Clear rbx 
         loop3:  
            cmp rbx,[r12]             ;row < C.ROWS (row >= C.ROWS)                   
            jge end3                  ;if row >= C.ROWS
            for4: xor rcx,rcx         ;for (col=0; ... (Clear rdx)
               loop4: 
                 cmp rcx,[r12+8]      ;col < C.ROWS
                 jge end4             ;if col >= C.ROWS   
                 xor r9,r9            ;sum = 0 (Clear rax)     
                 for5: xor rdi,rdi    ;for (k=0; ... (Clear rdx)      
                 loop5: 
                   cmp rdi,[r10+8]    ;k < A.COLS;   
                   jge end5;          ;Jump out of loop
                   ;Calculate sum 
                   ;sum += A[row][k] * B[k][col]                   
                   
                   ;rax = A[row][k]
                   ;r14 = B[k][col]
                            
                   ;BASE_ADDRESS (A) = [r10+16]
                   ;BASE_ADDRESS (B) = [r11+16]
                   ;row              = rbx
                   ;col              = rcx
                   ;k                = rdi
                   ;ROW_SIZE (A)     = [r10+8]
                   ;K_ROW_SIZE (B)   = [r11] 
                   ;ELEMENT_SIZE     = 8
                   ;BASE_ADDRESS + (ROW_INDEX * ROW_SIZE + COL_INDEX) * ELEMENT_SIZE  
                   ;Calculate A[row][k]                   
                   mov rax,qword[r10+8]  ;rax = ROW_SIZE
                   mul rbx               ;rax = ROW_SIZE * ROW_INDEX
                   add rax,rdi           ;rax = ROW_SIZE * ROW_INDEX + COL_INDEX
                   lea rax,[rax*8]       ;rax = (ROW_SIZE * ROW_INDEX + COL_INDEX) * ELEMENT_SIZE
                   lea rax,[rax+r10+16]  ;rax += BASE_ADDRESS 
                   mov r14,qword[rax]    ;Store in r14
                   ;Calculate B[k][col]                    
                   mov rax,qword[r11+8]  ;rax = ROW_SIZE
                   mul rdi               ;rax = ROW_SIZE * ROW_INDEX
                   add rax,rcx           ;rax = ROW_SIZE * ROW_INDEX + COL_INDEX
                   lea rax,[rax*8]       ;rax = (ROW_SIZE * ROW_INDEX + COL_INDEX) * ELEMENT_SIZE
                   lea rax,[rax+r11+16]  ;rax += BASE_ADDRESS                             
                   mov rax,[rax]         ;Move result back into rax
                   mul r14               ;Multiply by A[row][k]
                   jo overflow           ;Jump to end if overflow occured
                   add r9,rax            ;Add to sum (sum += A[row][k] * B[k][col]                           
                   inc rdi               ;k++
                   jmp loop5             ;Jump back to top of loop
                   end5:         
                     ;Base_Address = [r12+16]
                     ;col          = rcx
                     ;ROW_SIZE     = [r12+8]
                     ;row          = rbx
                     ;ELEMENT_SIZE = 8                               
                     ;C[row][col]  = sum                            
                     mov rax,qword[r12+8] ;rax = ROW_SIZE               
                     mul rbx              ;rax = ROW_SIZE * ROW
                     add rax,rcx          ;rax = ROW_SIZE * ROW + COL                 
                     lea rax,[rax*8]      ;rax = (ROW_SIZE * ROW + COL) * 8
                     lea rax,[rax+r12+16] ;rax = rax + BASE_ADDRESS of matrix
                     mov qword[rax],r9    ;C[row][col] = sum
                     inc rcx              ;col++
                     jmp loop4            ;Jump back to top of loop4
                   end4:     
                     inc rbx              ;row++
                     jmp loop3            ;Jump to top loop
           end3:
             jmp funcEnd                  ;Terminate function

         overflow: 
           call print                                    
 
         funcEnd:
           pop  rbp                ; restore base pointer & return
           ret
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

print: 
        mov rdx,msg_len		; arg3, length of string to print
	mov rcx,msg_overflow    ; arg2, pointer to string
	mov rbx,1		; arg1, where to write, screen
	mov rax,4		; write sysout command to int 80 hex
	int 0x80		; interrupt 80 hex, call kernel
	
	mov rbx,0		; exit code, 0=normal
	mov rax,1		; exit command to kernel
	int 0x80		; interrupt 80 hex, call kernel


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

msg_overflow db "Overflow occurred in matrix calculation!.",10
msg_len equ $-msg_overflow

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
        DQ 0,0                 ; space for ROWS*COLS ints
        DQ 0,0                ; (for filling in with matrixA*matrixB)

; ---------------------------------------------------------------------

        ; The following is used by output_char - do not disturb
        ;
        ; space in I/O-accessible segment for 1-octet output buffer
octetbuffer     DQ 0            ; (qword as choice of size on stack)
