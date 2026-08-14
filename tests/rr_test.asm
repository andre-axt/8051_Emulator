; ================================================================
; RR A Test (opcode 0x03)
; Rotate A right by one bit.
; Initial: A = 0x85 (1000 0101b)
; Expected: A = 0xC2 (1100 0010b)
; ================================================================
                ORG     0000H
                MOV     A, #85H
                RR      A                   ; opcode 0x03
                SJMP    $                   ; Halt - inspect A
                END
