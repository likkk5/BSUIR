 org $8000
 ldaa #$21
 clrb
mirr_loop:
 asra
 rolb
 dex
 bne mirror_loop

 ldaa #$21