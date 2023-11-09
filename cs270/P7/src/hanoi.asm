; Description: LC3 Tower of Hanoi Implementation 

; Ojaswi Sinha

;------------------------------------------------------------------------------
; BEGIN_RESERVED_SECTION: do not change ANYTHING in reserved the section!
; The ONLY exception to this is that you MAY change the .FILL value for
; any memory location marked for modification. This makes debugging easier
; as you need only change your code and re-assemble. Your test value(s) will
; already be set.

                .ORIG x3000
                BR main

option          .FILL 0  ; YOU_MAY_MODIFY_VAL ; 0 => Hanoi, non-0 => printMove
numDisks        .FILL 4  ; YOU_MAY_MODIFY_VAL
startTower      .FILL 1  ; YOU_MAY_MODIFY_VAL
endTower        .FILL 3  ; YOU_MAY_MODIFY_VAL

                ; misc strings for printing
digits          .STRINGZ "0123456789"
msg1            .STRINGZ "Move disk ";
msg2            .STRINGz " from tower ";
msg3            .STRINGz " to tower ";
endMsg          .STRINGz "\nThe world has ended\n"

stack           .FILL 0x4000

main            LD   R6,stack           ; initialize stack
                LD   R5,stack           ; initialize frame pointer

                LD   R0,endTower        ; both function have three parameters
                PUSH R0                 ; so put them on stack before JSR
                LD   R0,startTower
                PUSH R0
                LD   R0,numDisks
                PUSH R0

                LD   R0,option          ; get option to test
                BRZ  testHanoi

testPrintMove   JSR  printMove
                BR   endTest

testHanoi       JSR  hanoi

endTest         ADD  R6,R6,#3           ; clean up parameters
                LEA  R0,endMsg
                PUTS
theEnd          HALT                    ; check R5, R6 here, should be initial 'stack' value

; END_RESERVED_SECTION

;----  S t u d e n t   c o d e   g o e s   h e r e  --------------------------

; void printMove(disk, from, to)

; disk @ FP   ; from at FP   ; to @ FP   ; complete line

printMove
                PUSH R7
                PUSH R5
                ADD R5, R6, #-1
                LEA R0, msg1
                PUTS
                LDR R1, R5, #3         ; POINTER TO THE DISK
                LEA R0, digits
                ADD R0, R1, R0
                LDR R0, R0, #0 
                OUT

                LEA R0, msg2
                PUTS
                LDR R1, R5, #4         ; POINTER TO THE DISK
                LEA R0, digits
                ADD R0, R1, R0
                LDR R0, R0, #0
                OUT


                LEA R0, msg3
                PUTS
                LDR R1, R5, #5         ; POINTER TO THE DISK
                LEA R0, digits
                ADD R0, R1, R0
                LDR R0, R0, #0
                OUT
                NEWLN

                POP R5
                POP R7
                RET                     ; return to caller

;------------------------------------------------------------------------------
 
; void hanoi(numDisks, fromDisk, toDisk)

; numDisks @ R5   ; fromTower @ R5   ; toTower @ R5   ; auxTower @ R5   ; complete line

six             .FILL #6
hanoi
                PUSH R7
                PUSH R5
                ADD R5, R6,#-1                  ; FP
                ADD R6, R6, #-1                 ; SP
                LDR R0, R5, #3                  ; Get numDisk
                ADD R0, R0, #-1                 ; check if numDisk is 1
                BRz print                       ; if base case call printMove
                BRp Next                        ; else start hanoi 
print
                LDR R1, R5, #5                  ; totower
                PUSH R1
                LDR R1, R5, #4                  ; fromtower
                PUSH R1
                LDR R0, R5, #3                  ; numDisk
                PUSH R0
                JSR printMove
                ADD R6, R6, #3                  ; remove 3 parameters
                BR clean                 

Next
                LDR R2, R5, #4                  ; load fromtower value
                LDR R3, R5, #5                  ; load totower value
                ADD R4, R2, R3                  ; sum
                NOT R4, R4                      ; 1's compliment 
                ADD R4, R4, #1                  ; +1 = 2's compliment
                ADD R1, R4, #6                  ;auxtower =  6-(fromtower + totower)
                STR R1, R5, #0
                
                
                LDR R0, R5, #0                  ; auxtower
                PUSH R0
                LDR R1, R5, #4                  ; fromtower
                PUSH R1
                LDR R2, R5, #3                  ; numdisk
                ADD R2, R2, #-1
                PUSH R2  
                JSR hanoi
                ADD R6, R6, #3                  ; REMOVE PARAMETER

                
                LDR R0, R5, #5                  ; TOtower
                PUSH R0
                LDR R1, R5, #4                  ; fromtower
                PUSH R1
                LDR R2, R5, #3                  ; numdisk
                PUSH R2
                JSR printMove
                ADD R6, R6, #3
               
                LDR R0, R5, #5                  ; totower 
                PUSH R0
                LDR R0, R5, #0                  ; auxtower
                PUSH R0
                LDR R0, R5, #3                  ; numdisks
                ADD R0, R0, #-1
                PUSH R0    
                JSR hanoi
                ADD R6, R6, #3
clean 
                ADD R6, R6, #1

                POP R5
                POP R7 
                RET                     ; return to caller
;------------------------------------------------------------------------------
                .END
