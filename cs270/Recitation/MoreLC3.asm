; Recitation MoreLC3
; Author: <Ojaswi Sinha>
; Date:   <3/4/2022>
; Email:  <ojaswi@colostate.edu>
; Class:  CS270
; Description: Mirrors least significant byte to most significant
;--------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

            .ORIG x3000

            JSR mirror               ; call function
            HALT

; Parameter and return value
Param           .FILL 0x5634              ; space to specify parameter
Result          .BLKW 1              ; space to store result

; Constants
One             .FILL #1             ; the number 1       
Eight           .FILL #8             ; the number 8
Mask            .FILL x00ff          ; mask top bits

; End reserved section: do not change ANYTHING in reserved section!
;--------------------------------------------------------------------------
mirror                           ; Mirrors bits 7:0 to 15:8
                                 ; ~20 lines of assembly code

            LD R0,Param          ; load pattern
                                 ; your code here
	    ADD  R1, R0, #0		
	    LD R2, Mask
	    AND R1, R1, R2
	    LD R2, One
	    LD R3, One
	    LD R4, Eight

Loop1	    ADD R3, R3, R3
	    ADD R4 , R4, #-1
	    BRp Loop1

	    LD R4, Eight

Loop2	    AND R5, R2, R0
	    BRz Loop3
	    ADD R1 , R1, R3
Loop3
	    ADD R2, R2, R2
	    ADD R3, R3, R3
	    ADD R4, R4, #-1
	    BRzp Loop2
	  
            ST R1,Result         ; store result
            RET
;--------------------------------------------------------------------------
           .END
