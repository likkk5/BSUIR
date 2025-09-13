 org $8000
 ldx #$821f
 stx $0000
 ldab #8
 stab $0002
 ldx #$8200
 ldab #0
 ldy #0
 stab $0005
start:  ldaa $0000,x
label:  asla
  staa $0003
  tpa ;save ccr to A
  staa $0004
  ldaa $0005
  inca
  cmpa $0002
  bgt iter
  staa $0005
  ldaa $0004
  tap
        ldaa $0003
  bcs label2
  bcc label
label2: iny
  jmp label
iter: inx
      cpx $0000
      bgt finish
      ldaa #0
      staa $0005
      jmp start
finish: pshy
        pulx
