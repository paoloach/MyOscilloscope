	.section	.text,code
	.align	2
	.global	_Mps3ReadADC	
	.global _Mps1ReadADC
	.global	_Kps100ReadADC	
	.type	_Mps3ReadADC,@function
_Mps3ReadADC:
	.set ___PA___,0
	mov #_triggerValue,W0
	mov.b [W0],W2
	
	mov #_data1,W0
	mov #0,W3
	mov #_data2,W4
	mov #0,W5
.3MpsL1:
	mov	PORTB,W1
	mov.b	W1,[W0+W3]
	nop
	nop
	nop
	cp.b	W1,W2  // W1-W2
	BRA	NC,.3MpsBelowTrigger
	INC.b	W3,W3
	bra	.3MpsL1
.3MpsBelowTrigger:	
	inc.b	w3,w3
	nop
.3MpsL2:
	mov	PORTB,W1
	mov.b	W1,[W0+W3]
	nop
	nop
	nop
	cp.b	W1,W2  // W1-W2
	BRA	C,.3MpsTRIGGER_FOUND
	INC.b	W3,W3
	bra	.3MpsL2
.3Mps_AFTER_TRIGGER:
	NOP
	nop
.3MpsTRIGGER_FOUND:
	nop
	nop
	MOV	PORTB,W1
	MOV.b	W1,[W4+W5]
	INC.b  W5,W5
	BRA	Z,.3Mps_END
	BRA	.3Mps_AFTER_TRIGGER
.3Mps_END:
	MOV	#_triggerPos,w0
	MOV.b	w3,[w0]
	RETURN

	
	

	.type	_Mps1ReadADC,@function
_Mps1ReadADC:
	.set ___PA___,0
	mov #_triggerValue,W0
	mov.b [W0],W2
	
	mov #_data1,W0
	mov #0,W3
	mov #_data2,W4
	mov #0,W5
.1MpsL1:
	mov	PORTB,W1
	mov.b	W1,[W0+W3]
	REPEAT  #21
	NOP
	cp.b	W1,W2  // W1-W2
	BRA	NC,.1MpsBelowTrigger
	INC.b	W3,W3
	bra	.1MpsL1
.1MpsBelowTrigger:	
	inc.b	w3,w3
	NOP
.1MpsL2:
	mov	PORTB,W1
	mov.b	W1,[W0+W3]
	REPEAT #21
	NOP
	cp.b	W1,W2  // W1-W2
	BRA	C,.1MpsTRIGGER_FOUND
	INC.b	W3,W3
	bra	.1MpsL2
.1Mps_AFTER_TRIGGER:
	REPEAT #20
	nop
.1MpsTRIGGER_FOUND:
	NOP
	NOP
	MOV	PORTB,W1
	MOV.b	W1,[W4+W5]
	INC.b  W5,W5
	BRA	Z,.1Mps_END
	BRA	.1Mps_AFTER_TRIGGER
.1Mps_END:
	MOV	#_triggerPos,w0
	MOV.b	w3,[w0]
	RETURN
	

	
	
	.type	_Kps100ReadADC,@function
_Kps100ReadADC:
	.set ___PA___,0
	mov #_triggerValue,W0
	mov.b [W0],W2
	
	mov #_data1,W0
	mov #0,W3
	mov #_data2,W4
	mov #0,W5
.100KpsL1:
	mov	PORTB,W1
	mov.b	W1,[W0+W3]
	REPEAT  #291
	NOP
	cp.b	W1,W2  // W1-W2
	BRA	NC,.100KpsBelowTrigger
	INC.b	W3,W3
	bra	.100KpsL1
.100KpsBelowTrigger:	
	inc.b	w3,w3
	NOP
.100KpsL2:
	mov	PORTB,W1
	mov.b	W1,[W0+W3]
	REPEAT #291
	NOP
	cp.b	W1,W2  // W1-W2
	BRA	C,.100KpsTRIGGER_FOUND
	INC.b	W3,W3
	bra	.100KpsL2
.100Kps_AFTER_TRIGGER:
	REPEAT #290
	nop
.100KpsTRIGGER_FOUND:
	NOP
	NOP
	MOV	PORTB,W1
	MOV.b	W1,[W4+W5]
	INC.b  W5,W5
	BRA	Z,.100Kps_END
	BRA	.100Kps_AFTER_TRIGGER
.100Kps_END:
	MOV	#_triggerPos,w0
	MOV.b	w3,[w0]
	RETURN
	
	
	
	
	.section	*_pretriggerSection,bss,xmemory
	.align	256
_data1:	.space	256
	.section	*_posttriggerSection,bss,xmemory
	.align	256
_data2:	.space	256
	.global	_data1
	.global _data2
	.extern _triggerValue
	.extern _triggerPos
; MCHP configuration words

	.set ___PA___,0
	.end
