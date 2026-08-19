; ================================================================
; POP Test (opcode 0xD0)
; Pop direct byte from stack.
; Initial: SP = 0x08, [0x08] = 0xCD
; Expected: SP = 0x07, [0x30] = 0xCD
; ================================================================
                ORG     0000H
                MOV     SP, #08H
                MOV     08H, #0CDH          ; stack location
                POP     30H                 ; opcode 0xD0, 0x30
                SJMP    $                   ; Halt - inspect SP and [30H]
                END