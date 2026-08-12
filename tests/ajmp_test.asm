; ================================================================
; AJMP Test (opcode 0x01)
; Jumps to a label within the same 2K page.
; ================================================================
                ORG     0000H
                AJMP    TARGET_AJMP         ; opcode 0x01 (assembler generates bytes)
                SJMP    $                   
TARGET_AJMP:
                SJMP    $                  
                END