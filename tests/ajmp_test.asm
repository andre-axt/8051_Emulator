; ================================================================
; AJMP Test (opcode 0x01)
; Jumps to a label within the same 2K page.
; ================================================================
                ORG     0000H
                AJMP    TARGET_AJMP        
                SJMP    $                   
TARGET_AJMP:
                SJMP    $                  
                END
