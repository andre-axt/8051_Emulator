; ================================================================
; LJMP Test (opcode 0x02)
; Jumps to an absolute 16‑bit address.
; ================================================================
                ORG     0000H
                LJMP    TARGET_LJMP         ; opcode 0x02 (bytes: 02 34 56)
                SJMP    $                  
                ORG     3456H               ; Set target address explicitly
TARGET_LJMP:
                SJMP    $                   ; Halt - PC should be 3456H
                END
