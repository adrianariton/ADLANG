.data
.text
.globl _start
_start:
	mov x29, sp
	mov x7, x29 ;; store original base pointer
;;-------


;; [LINE] composefun => @(f, g, h)

		;; Token{composefun, 1, 0, |0}
		;; Token{=, 0, 0, |0}
		;; Token{=>, 0, 4, |0}
		;; Token{@, 6, 9, |0}
		;; Token{(, 3, 1, |0}
		;; Token{f, 1, 0, |0}
		;; Token{,, 0, 3, |0}
		;; Token{g, 1, 0, |0}
		;; Token{,, 0, 3, |0}
		;; Token{h, 1, 0, |0}
		;; Token{), 3, 2, |0}
		;; Token{composefun, 1, 6, |0}
		;; Token{=>, 0, 4, |0}
		;; Token{@, 6, 9, |0}
		;; Token{(, 3, 1, |0}
		;; Token{f, 1, 6, |0}
		;; Token{,, 0, 3, |0}
		;; Token{g, 1, 6, |0}
		;; Token{,, 0, 3, |0}
		;; Token{h, 1, 6, |0}
		;; Token{), 3, 2, |0}
;;------- POSTFIX
		;; Token{composefun, 1, 6, |0}
		;; Token{@, 6, 9, |0}
		;; Token{f, 1, 6, |0}
		;; Token{g, 1, 6, |0}
		;; Token{h, 1, 6, |0}
		;; Token{=>, 0, 4, |0}
;;------- //POSTFIX
		;; Token{composefun, 1, 6, |0}
;; resolving... 
		;; Token{composefun, 1, 6, |0}
;; ENTERING IF main
	b endcomposefun
;; begin scope composefun

composefun:
	stp x29, x30, [sp, #-16]!
	mov x29, sp
		;; Token{@, 6, 9, |0}
		;; Token{f, 1, 6, |0}
;; resolving... 
		;; Token{f, 1, 6, |0}
;; ENTERING IF composefun
;; VAR f NOT HERE
;; VAR f NOT HERE 0
		;; Token{g, 1, 6, |0}
;; resolving... 
		;; Token{g, 1, 6, |0}
;; ENTERING IF composefun
;; VAR g NOT HERE
;; VAR g NOT HERE 0
		;; Token{h, 1, 6, |0}
;; resolving... 
		;; Token{h, 1, 6, |0}
;; ENTERING IF composefun
;; VAR h NOT HERE
;; VAR h NOT HERE 0
		;; Token{=>, 0, 4, |0}
;; @param:h  @param:g  @param:f 
;; activating scope: composefun #params=3
;;-------


;; [LINE]     make f : func(1, 1)

		;; Token{make, 6, 10, |0}
		;; Token{f, 1, 0, |0}
		;; Token{:, 3, 0, |0}
		;; Token{func, 1, 11, |0}
		;; Token{(, 3, 1, |0}
		;; Token{1, 4, 7, |0}
		;; Token{,, 0, 3, |0}
		;; Token{1, 4, 7, |0}
		;; Token{), 3, 2, |0}
		;; Token{make, 6, 10, |0}
		;; Token{f, 1, 6, |0}
		;; Token{:, 3, 0, |0}
		;; Token{func, 1, 11, |0}
		;; Token{(, 3, 1, |0}
		;; Token{1, 4, 7, |0}
		;; Token{,, 0, 3, |0}
		;; Token{1, 4, 7, |0}
		;; Token{), 3, 2, |0}
;;------- POSTFIX
		;; Token{make, 6, 10, |0}
		;; Token{f, 1, 6, |0}
		;; Token{1, 4, 7, |0}
		;; Token{1, 4, 7, |0}
		;; Token{func, 1, 11, |0}
;;------- //POSTFIX
		;; Token{make, 6, 10, |0}
		;; Token{f, 1, 6, |0}
;; resolving... 
		;; Token{make, 6, 10, |0}
		;; Token{f, 1, 6, |0}
;; ENTERING IF composefun
;; VAR f HERE
;; PARAMS SIZE: 1
		;; Token{make, 6, 10, |0}

;; IS_VAR f
;; IDENTITY
;; stpush 		;; Token{f, 1, 6, |0}


		;; Token{1, 4, 7, |0}
		;; Token{1, 4, 7, |0}
		;; Token{func, 1, 11, |0}
;; resolving... 
		;; Token{func, 1, 11, |0}
;; ENTERING IF composefun
;; MAKE_TOK: PARAMS#: 3
		;; Token{1, 4, 7, |0}
		;; Token{1, 4, 7, |0}
		;; Token{f, 1, 6, |0}
;; make f :: ret 1 :: pno 1
;; DONE MAKE_TOK
;;-------


;; [LINE]     make g : func(1, 1)

		;; Token{make, 6, 10, |0}
		;; Token{g, 1, 0, |0}
		;; Token{:, 3, 0, |0}
		;; Token{func, 1, 11, |0}
		;; Token{(, 3, 1, |0}
		;; Token{1, 4, 7, |0}
		;; Token{,, 0, 3, |0}
		;; Token{1, 4, 7, |0}
		;; Token{), 3, 2, |0}
		;; Token{make, 6, 10, |0}
		;; Token{g, 1, 6, |0}
		;; Token{:, 3, 0, |0}
		;; Token{func, 1, 11, |0}
		;; Token{(, 3, 1, |0}
		;; Token{1, 4, 7, |0}
		;; Token{,, 0, 3, |0}
		;; Token{1, 4, 7, |0}
		;; Token{), 3, 2, |0}
;;------- POSTFIX
		;; Token{make, 6, 10, |0}
		;; Token{g, 1, 6, |0}
		;; Token{1, 4, 7, |0}
		;; Token{1, 4, 7, |0}
		;; Token{func, 1, 11, |0}
;;------- //POSTFIX
		;; Token{make, 6, 10, |0}
		;; Token{g, 1, 6, |0}
;; resolving... 
		;; Token{make, 6, 10, |0}
		;; Token{g, 1, 6, |0}
;; ENTERING IF composefun
;; VAR g HERE
;; PARAMS SIZE: 1
		;; Token{make, 6, 10, |0}

;; IS_VAR g
;; IDENTITY
;; stpush 		;; Token{g, 1, 6, |0}


		;; Token{1, 4, 7, |0}
		;; Token{1, 4, 7, |0}
		;; Token{func, 1, 11, |0}
;; resolving... 
		;; Token{func, 1, 11, |0}
;; ENTERING IF composefun
;; MAKE_TOK: PARAMS#: 3
		;; Token{1, 4, 7, |0}
		;; Token{1, 4, 7, |0}
		;; Token{g, 1, 6, |0}
;; make g :: ret 1 :: pno 1
;; DONE MAKE_TOK
;;-------


;; [LINE]     return _f(_g(_h))

		;; Token{return, 2, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{f, 1, 0, |0}
		;; Token{(, 3, 1, |0}
		;; Token{_, 6, 0, |0}
		;; Token{g, 1, 0, |0}
		;; Token{(, 3, 1, |0}
		;; Token{_, 6, 0, |0}
		;; Token{h, 1, 0, |0}
		;; Token{), 3, 2, |0}
		;; Token{), 3, 2, |0}
		;; Token{return, 2, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{f, 1, 0, |0}
		;; Token{(, 3, 1, |0}
		;; Token{_, 6, 0, |0}
		;; Token{g, 1, 0, |0}
		;; Token{(, 3, 1, |0}
		;; Token{_, 6, 0, |0}
		;; Token{h, 1, 6, |0}
		;; Token{), 3, 2, |0}
		;; Token{), 3, 2, |0}
;;------- POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{h, 1, 6, |0}
		;; Token{g, 1, 0, |0}
		;; Token{f, 1, 0, |0}
		;; Token{return, 2, 0, |0}
;;------- //POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{h, 1, 6, |0}
;; resolving... 
		;; Token{h, 1, 6, |0}
;; ENTERING IF composefun
;; VAR h HERE
;; PARAMS SIZE: 0

;; IS_VAR h
		;; Token{$$[x29 , #48], 4, 8, |1}
;; stpush 		;; Token{$$[x29 , #48], 4, 8, |1}


		;; Token{g, 1, 0, |0}
;; resolving... 
		;; Token{g, 1, 0, |0}
;; ENTERING IF composefun
;; VAR g HERE
;; PARAMS SIZE: 1
		;; Token{$$[x29 , #48], 4, 8, |1}

;; FCT CALL g: @return 1 @#params: 1
		;; begin push 
	ldr  x15, [x29 , #48]
	str x15 , [sp, #-16]! ;; push x15
;; ret nr: 1
	ldr x14, [x29 , #32] ;; [g]
	blr x14
	add sp, sp, #16
	str x0 , [sp, #-16]! ;; push x0
		;; Token{$$[x29 , #-16], 4, 8, |1}
;; stpush 		;; Token{$$[x29 , #-16], 4, 8, |1}


		;; Token{f, 1, 0, |0}
;; resolving... 
		;; Token{f, 1, 0, |0}
;; ENTERING IF composefun
;; VAR f HERE
;; PARAMS SIZE: 1
		;; Token{$$[x29 , #-16], 4, 8, |1}

;; FCT CALL f: @return 1 @#params: 1
		;; begin push 
	ldr  x15, [x29 , #-16]
	str x15 , [sp, #-16]! ;; push x15
;; ret nr: 1
	ldr x14, [x29 , #16] ;; [f]
	blr x14
	add sp, sp, #16
	str x0 , [sp, #-16]! ;; push x0
		;; Token{$$[x29 , #-32], 4, 8, |1}
;; stpush 		;; Token{$$[x29 , #-32], 4, 8, |1}


		;; Token{return, 2, 0, |0}
;; resolving... 
;; @return: 1 of: composefun
	ldr x0, [x29 , #-32]
;; set ret: 1
	mov sp, x29
	ldp x29, x30, [sp], #16
	ret
endcomposefun:
;;-------


;; [LINE] dblp => @(a)

		;; Token{dblp, 1, 0, |0}
		;; Token{=, 0, 0, |0}
		;; Token{=>, 0, 4, |0}
		;; Token{@, 6, 9, |0}
		;; Token{(, 3, 1, |0}
		;; Token{a, 1, 0, |0}
		;; Token{), 3, 2, |0}
		;; Token{dblp, 1, 6, |0}
		;; Token{=>, 0, 4, |0}
		;; Token{@, 6, 9, |0}
		;; Token{(, 3, 1, |0}
		;; Token{a, 1, 6, |0}
		;; Token{), 3, 2, |0}
;;------- POSTFIX
		;; Token{dblp, 1, 6, |0}
		;; Token{@, 6, 9, |0}
		;; Token{a, 1, 6, |0}
		;; Token{=>, 0, 4, |0}
;;------- //POSTFIX
		;; Token{dblp, 1, 6, |0}
;; resolving... 
		;; Token{dblp, 1, 6, |0}
;; ENTERING IF main
	b enddblp
;; begin scope dblp

dblp:
	stp x29, x30, [sp, #-16]!
	mov x29, sp
		;; Token{@, 6, 9, |0}
		;; Token{a, 1, 6, |0}
;; resolving... 
		;; Token{a, 1, 6, |0}
;; ENTERING IF dblp
;; VAR a NOT HERE
;; VAR a NOT HERE 0
		;; Token{=>, 0, 4, |0}
;; @param:a 
;; activating scope: dblp #params=1
;;-------


;; [LINE]     return _a + _a + 1

		;; Token{return, 2, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 0, |0}
		;; Token{+, 0, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 0, |0}
		;; Token{+, 0, 0, |0}
		;; Token{1, 4, 7, |0}
		;; Token{return, 2, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 6, |0}
		;; Token{+, 0, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 6, |0}
		;; Token{+, 0, 0, |0}
		;; Token{1, 4, 7, |0}
;;------- POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 6, |0}
		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 6, |0}
		;; Token{+, 0, 0, |0}
		;; Token{1, 4, 7, |0}
		;; Token{+, 0, 0, |0}
		;; Token{return, 2, 0, |0}
;;------- //POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 6, |0}
;; resolving... 
		;; Token{a, 1, 6, |0}
;; ENTERING IF dblp
;; VAR a HERE
;; PARAMS SIZE: 0

;; IS_VAR a
		;; Token{$$[x29 , #16], 4, 8, |1}
;; stpush 		;; Token{$$[x29 , #16], 4, 8, |1}


		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 6, |0}
;; resolving... 
		;; Token{a, 1, 6, |0}
;; ENTERING IF dblp
;; VAR a HERE
;; PARAMS SIZE: 0

;; IS_VAR a
		;; Token{$$[x29 , #16], 4, 8, |1}
;; stpush 		;; Token{$$[x29 , #16], 4, 8, |1}


		;; Token{+, 0, 0, |0}
	ldr x14, [x29 , #16]
	ldr x15, [x29 , #16]
	add x13, x14, x15
	str x13 , [sp, #-16]! ;; push x13
		;; Token{$$[x29 , #-16], 4, 8, |1}
		;; Token{1, 4, 7, |0}
		;; Token{+, 0, 0, |0}
	ldr x14, [x29 , #-16]
	mov x15, #1
	add x13, x14, x15
	str x13 , [sp, #-16]! ;; push x13
		;; Token{$$[x29 , #-32], 4, 8, |1}
		;; Token{return, 2, 0, |0}
;; resolving... 
;; @return: 1 of: dblp
	ldr x0, [x29 , #-32]
;; set ret: 1
	mov sp, x29
	ldp x29, x30, [sp], #16
	ret
enddblp:
;;-------


;; [LINE] trpl => @(a)

		;; Token{trpl, 1, 0, |0}
		;; Token{=, 0, 0, |0}
		;; Token{=>, 0, 4, |0}
		;; Token{@, 6, 9, |0}
		;; Token{(, 3, 1, |0}
		;; Token{a, 1, 0, |0}
		;; Token{), 3, 2, |0}
		;; Token{trpl, 1, 6, |0}
		;; Token{=>, 0, 4, |0}
		;; Token{@, 6, 9, |0}
		;; Token{(, 3, 1, |0}
		;; Token{a, 1, 6, |0}
		;; Token{), 3, 2, |0}
;;------- POSTFIX
		;; Token{trpl, 1, 6, |0}
		;; Token{@, 6, 9, |0}
		;; Token{a, 1, 6, |0}
		;; Token{=>, 0, 4, |0}
;;------- //POSTFIX
		;; Token{trpl, 1, 6, |0}
;; resolving... 
		;; Token{trpl, 1, 6, |0}
;; ENTERING IF main
	b endtrpl
;; begin scope trpl

trpl:
	stp x29, x30, [sp, #-16]!
	mov x29, sp
		;; Token{@, 6, 9, |0}
		;; Token{a, 1, 6, |0}
;; resolving... 
		;; Token{a, 1, 6, |0}
;; ENTERING IF trpl
;; VAR a NOT HERE
;; VAR a NOT HERE 0
		;; Token{=>, 0, 4, |0}
;; @param:a 
;; activating scope: trpl #params=1
;;-------


;; [LINE]     _b(_a + _a + _a)

		;; Token{_, 6, 0, |0}
		;; Token{b, 1, 0, |0}
		;; Token{(, 3, 1, |0}
		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 0, |0}
		;; Token{+, 0, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 0, |0}
		;; Token{+, 0, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 0, |0}
		;; Token{), 3, 2, |0}
		;; Token{_, 6, 0, |0}
		;; Token{b, 1, 0, |0}
		;; Token{(, 3, 1, |0}
		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 6, |0}
		;; Token{+, 0, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 6, |0}
		;; Token{+, 0, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 6, |0}
		;; Token{), 3, 2, |0}
;;------- POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 6, |0}
		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 6, |0}
		;; Token{+, 0, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 6, |0}
		;; Token{+, 0, 0, |0}
		;; Token{b, 1, 0, |0}
;;------- //POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 6, |0}
;; resolving... 
		;; Token{a, 1, 6, |0}
;; ENTERING IF trpl
;; VAR a HERE
;; PARAMS SIZE: 0

;; IS_VAR a
		;; Token{$$[x29 , #16], 4, 8, |1}
;; stpush 		;; Token{$$[x29 , #16], 4, 8, |1}


		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 6, |0}
;; resolving... 
		;; Token{a, 1, 6, |0}
;; ENTERING IF trpl
;; VAR a HERE
;; PARAMS SIZE: 0

;; IS_VAR a
		;; Token{$$[x29 , #16], 4, 8, |1}
;; stpush 		;; Token{$$[x29 , #16], 4, 8, |1}


		;; Token{+, 0, 0, |0}
	ldr x14, [x29 , #16]
	ldr x15, [x29 , #16]
	add x13, x14, x15
	str x13 , [sp, #-16]! ;; push x13
		;; Token{$$[x29 , #-16], 4, 8, |1}
		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 6, |0}
;; resolving... 
		;; Token{a, 1, 6, |0}
;; ENTERING IF trpl
;; VAR a HERE
;; PARAMS SIZE: 0

;; IS_VAR a
		;; Token{$$[x29 , #16], 4, 8, |1}
;; stpush 		;; Token{$$[x29 , #16], 4, 8, |1}


		;; Token{+, 0, 0, |0}
	ldr x14, [x29 , #-16]
	ldr x15, [x29 , #16]
	add x13, x14, x15
	str x13 , [sp, #-16]! ;; push x13
		;; Token{$$[x29 , #-32], 4, 8, |1}
		;; Token{b, 1, 0, |0}
;; resolving... 
		;; Token{b, 1, 0, |0}
;; ENTERING IF trpl
;; VAR b NOT HERE
;; VAR b NOT HERE 1
		;; begin push 
	ldr  x15, [x29 , #-32]
	str x15 , [sp, #-16]! ;; push x15
;;-------


;; [LINE]     if (_a == 2)

		;; Token{if, 1, 13, |0}
		;; Token{(, 3, 1, |0}
		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 0, |0}
		;; Token{=, 0, 0, |0}
		;; Token{==, 0, 0, |0}
		;; Token{2, 4, 7, |0}
		;; Token{), 3, 2, |0}
		;; Token{if, 1, 13, |0}
		;; Token{(, 3, 1, |0}
		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 6, |0}
		;; Token{==, 0, 0, |0}
		;; Token{2, 4, 7, |0}
		;; Token{), 3, 2, |0}
;;------- POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 6, |0}
		;; Token{2, 4, 7, |0}
		;; Token{==, 0, 0, |0}
		;; Token{if, 1, 13, |0}
;;------- //POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{a, 1, 6, |0}
;; resolving... 
		;; Token{a, 1, 6, |0}
;; ENTERING IF trpl
;; VAR a HERE
;; PARAMS SIZE: 0

;; IS_VAR a
		;; Token{$$[x29 , #16], 4, 8, |1}
;; stpush 		;; Token{$$[x29 , #16], 4, 8, |1}


		;; Token{2, 4, 7, |0}
		;; Token{==, 0, 0, |0}
	ldr x14, [x29 , #16]
	mov x15, #2
	cmp x14, x15
cset x13, eq
	str x13 , [sp, #-16]! ;; push x13
	ldr x14, [x29 , #16]
	mov x15, #2
	cmp x14, x15
		;; Token{$$[x29 , #-64], 4, 8, |1}
		;; Token{if, 1, 13, |0}
;; resolving... 
		;; Token{if, 1, 13, |0}
;; ENTERING IF trpl
;; OKOK
;; OKOK
;; ENTERING IF .F8
		;; Token{$$[x29 , #-64], 4, 8, |1}
	ldr x14, [x29 , #-64]
	cmp x14, #0
b.eq .F8
;;-------


;; [LINE]         _b(1)

		;; Token{_, 6, 0, |0}
		;; Token{b, 1, 0, |0}
		;; Token{(, 3, 1, |0}
		;; Token{1, 4, 7, |0}
		;; Token{), 3, 2, |0}
		;; Token{_, 6, 0, |0}
		;; Token{b, 1, 0, |0}
		;; Token{(, 3, 1, |0}
		;; Token{1, 4, 7, |0}
		;; Token{), 3, 2, |0}
;;------- POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{1, 4, 7, |0}
		;; Token{b, 1, 0, |0}
;;------- //POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{1, 4, 7, |0}
		;; Token{b, 1, 0, |0}
;; resolving... 
		;; Token{b, 1, 0, |0}
;; ENTERING IF .F8
;; VAR b HERE
;; PARAMS SIZE: 1
		;; Token{1, 4, 7, |0}

;; IS_VAR b
	mov x15, #1
	str x15, [x29 , #-48]
;;-------


;; [LINE]         if (_b == 13)

		;; Token{if, 1, 13, |0}
		;; Token{(, 3, 1, |0}
		;; Token{_, 6, 0, |0}
		;; Token{b, 1, 0, |0}
		;; Token{=, 0, 0, |0}
		;; Token{==, 0, 0, |0}
		;; Token{13, 4, 7, |0}
		;; Token{), 3, 2, |0}
		;; Token{if, 1, 13, |0}
		;; Token{(, 3, 1, |0}
		;; Token{_, 6, 0, |0}
		;; Token{b, 1, 6, |0}
		;; Token{==, 0, 0, |0}
		;; Token{13, 4, 7, |0}
		;; Token{), 3, 2, |0}
;;------- POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{b, 1, 6, |0}
		;; Token{13, 4, 7, |0}
		;; Token{==, 0, 0, |0}
		;; Token{if, 1, 13, |0}
;;------- //POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{b, 1, 6, |0}
;; resolving... 
		;; Token{b, 1, 6, |0}
;; ENTERING IF .F8
;; VAR b HERE
;; PARAMS SIZE: 0

;; IS_VAR b
		;; Token{$$[x29 , #-48], 4, 8, |1}
;; stpush 		;; Token{$$[x29 , #-48], 4, 8, |1}


		;; Token{13, 4, 7, |0}
		;; Token{==, 0, 0, |0}
	ldr x14, [x29 , #-48]
	mov x15, #13
	cmp x14, x15
cset x13, eq
	str x13 , [sp, #-16]! ;; push x13
	ldr x14, [x29 , #-48]
	mov x15, #13
	cmp x14, x15
		;; Token{$$[x29 , #-80], 4, 8, |1}
		;; Token{if, 1, 13, |0}
;; resolving... 
		;; Token{if, 1, 13, |0}
;; ENTERING IF .F8
;; OKOK
;; OKOK
;; ENTERING IF .F10
		;; Token{$$[x29 , #-80], 4, 8, |1}
	ldr x14, [x29 , #-80]
	cmp x14, #0
b.eq .F10
;;-------


;; [LINE]             _b(2)

		;; Token{_, 6, 0, |0}
		;; Token{b, 1, 0, |0}
		;; Token{(, 3, 1, |0}
		;; Token{2, 4, 7, |0}
		;; Token{), 3, 2, |0}
		;; Token{_, 6, 0, |0}
		;; Token{b, 1, 0, |0}
		;; Token{(, 3, 1, |0}
		;; Token{2, 4, 7, |0}
		;; Token{), 3, 2, |0}
;;------- POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{2, 4, 7, |0}
		;; Token{b, 1, 0, |0}
;;------- //POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{2, 4, 7, |0}
		;; Token{b, 1, 0, |0}
;; resolving... 
		;; Token{b, 1, 0, |0}
;; ENTERING IF .F10
;; VAR b HERE
;; PARAMS SIZE: 1
		;; Token{2, 4, 7, |0}

;; IS_VAR b
	mov x15, #2
	str x15, [x29 , #-48]
;;-------


;; [LINE]         end

		;; Token{end, 2, 0, |0}
		;; Token{end, 2, 0, |0}
;;------- POSTFIX
		;; Token{end, 2, 0, |0}
;;------- //POSTFIX
		;; Token{end, 2, 0, |0}
;; resolving... 
.F10:
;;-------


;; [LINE]     end

		;; Token{end, 2, 0, |0}
		;; Token{end, 2, 0, |0}
;;------- POSTFIX
		;; Token{end, 2, 0, |0}
;;------- //POSTFIX
		;; Token{end, 2, 0, |0}
;; resolving... 
.F8:
;;-------


;; [LINE]     return _b

		;; Token{return, 2, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{b, 1, 0, |0}
		;; Token{return, 2, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{b, 1, 0, |0}
;;------- POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{b, 1, 0, |0}
		;; Token{return, 2, 0, |0}
;;------- //POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{b, 1, 0, |0}
;; resolving... 
		;; Token{b, 1, 0, |0}
;; ENTERING IF trpl
;; VAR b HERE
;; PARAMS SIZE: 0

;; IS_VAR b
		;; Token{$$[x29 , #-48], 4, 8, |1}
;; stpush 		;; Token{$$[x29 , #-48], 4, 8, |1}


		;; Token{return, 2, 0, |0}
;; resolving... 
;; @return: 1 of: trpl
	ldr x0, [x29 , #-48]
;; set ret: 1
	mov sp, x29
	ldp x29, x30, [sp], #16
	ret
endtrpl:
;;-------


;; [LINE] getaddr => @(f)

		;; Token{getaddr, 1, 0, |0}
		;; Token{=, 0, 0, |0}
		;; Token{=>, 0, 4, |0}
		;; Token{@, 6, 9, |0}
		;; Token{(, 3, 1, |0}
		;; Token{f, 1, 0, |0}
		;; Token{), 3, 2, |0}
		;; Token{getaddr, 1, 6, |0}
		;; Token{=>, 0, 4, |0}
		;; Token{@, 6, 9, |0}
		;; Token{(, 3, 1, |0}
		;; Token{f, 1, 6, |0}
		;; Token{), 3, 2, |0}
;;------- POSTFIX
		;; Token{getaddr, 1, 6, |0}
		;; Token{@, 6, 9, |0}
		;; Token{f, 1, 6, |0}
		;; Token{=>, 0, 4, |0}
;;------- //POSTFIX
		;; Token{getaddr, 1, 6, |0}
;; resolving... 
		;; Token{getaddr, 1, 6, |0}
;; ENTERING IF main
	b endgetaddr
;; begin scope getaddr

getaddr:
	stp x29, x30, [sp, #-16]!
	mov x29, sp
		;; Token{@, 6, 9, |0}
		;; Token{f, 1, 6, |0}
;; resolving... 
		;; Token{f, 1, 6, |0}
;; ENTERING IF getaddr
;; VAR f NOT HERE
;; VAR f NOT HERE 0
		;; Token{=>, 0, 4, |0}
;; @param:f 
;; activating scope: getaddr #params=1
;;-------


;; [LINE]     make f : func(??, ??)

		;; Token{make, 6, 10, |0}
		;; Token{f, 1, 0, |0}
		;; Token{:, 3, 0, |0}
		;; Token{func, 1, 11, |0}
		;; Token{(, 3, 1, |0}
		;; Token{?, 3, 0, |0}
		;; Token{??, 1, 0, |0}
		;; Token{,, 0, 3, |0}
		;; Token{?, 3, 0, |0}
		;; Token{??, 1, 0, |0}
		;; Token{), 3, 2, |0}
		;; Token{make, 6, 10, |0}
		;; Token{f, 1, 6, |0}
		;; Token{:, 3, 0, |0}
		;; Token{func, 1, 11, |0}
		;; Token{(, 3, 1, |0}
		;; Token{??, 1, 6, |0}
		;; Token{,, 0, 3, |0}
		;; Token{??, 1, 6, |0}
		;; Token{), 3, 2, |0}
;;------- POSTFIX
		;; Token{make, 6, 10, |0}
		;; Token{f, 1, 6, |0}
		;; Token{??, 1, 6, |0}
		;; Token{??, 1, 6, |0}
		;; Token{func, 1, 11, |0}
;;------- //POSTFIX
		;; Token{make, 6, 10, |0}
		;; Token{f, 1, 6, |0}
;; resolving... 
		;; Token{make, 6, 10, |0}
		;; Token{f, 1, 6, |0}
;; ENTERING IF getaddr
;; VAR f HERE
;; PARAMS SIZE: 1
		;; Token{make, 6, 10, |0}

;; IS_VAR f
;; IDENTITY
;; stpush 		;; Token{f, 1, 6, |0}


		;; Token{??, 1, 6, |0}
		;; Token{??, 1, 6, |0}
		;; Token{func, 1, 11, |0}
;; resolving... 
		;; Token{func, 1, 11, |0}
;; ENTERING IF getaddr
;; MAKE_TOK: PARAMS#: 3
		;; Token{??, 1, 6, |0}
		;; Token{??, 1, 6, |0}
		;; Token{f, 1, 6, |0}
;; make f :: ret -1 :: pno -1
;; DONE MAKE_TOK
;;-------


;; [LINE]     return _f

		;; Token{return, 2, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{f, 1, 0, |0}
		;; Token{return, 2, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{f, 1, 0, |0}
;;------- POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{f, 1, 0, |0}
		;; Token{return, 2, 0, |0}
;;------- //POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{f, 1, 0, |0}
;; resolving... 
		;; Token{f, 1, 0, |0}
;; ENTERING IF getaddr
;; VAR f HERE
;; PARAMS SIZE: 0

;; stpush 		;; Token{f, 1, 0, |0}


		;; Token{return, 2, 0, |0}
;; resolving... 
;; @return: 1 of: getaddr
	ldr x0, [x29 , #16] ;; [f]
;; set ret: 1
	mov sp, x29
	ldp x29, x30, [sp], #16
	ret
endgetaddr:
;;-------


;; [LINE] _gasan(6)

		;; Token{_, 6, 0, |0}
		;; Token{gasan, 1, 0, |0}
		;; Token{(, 3, 1, |0}
		;; Token{6, 4, 7, |0}
		;; Token{), 3, 2, |0}
		;; Token{_, 6, 0, |0}
		;; Token{gasan, 1, 0, |0}
		;; Token{(, 3, 1, |0}
		;; Token{6, 4, 7, |0}
		;; Token{), 3, 2, |0}
;;------- POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{6, 4, 7, |0}
		;; Token{gasan, 1, 0, |0}
;;------- //POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{6, 4, 7, |0}
		;; Token{gasan, 1, 0, |0}
;; resolving... 
		;; Token{gasan, 1, 0, |0}
;; ENTERING IF main
;; VAR gasan NOT HERE
;; VAR gasan NOT HERE 1
		;; begin push 
	mov  x15, #6
	str x15 , [sp, #-16]! ;; push x15
;;-------


;; [LINE] _gasan(_getaddr(_composefun))

		;; Token{_, 6, 0, |0}
		;; Token{gasan, 1, 0, |0}
		;; Token{(, 3, 1, |0}
		;; Token{_, 6, 0, |0}
		;; Token{getaddr, 1, 0, |0}
		;; Token{(, 3, 1, |0}
		;; Token{_, 6, 0, |0}
		;; Token{composefun, 1, 0, |0}
		;; Token{), 3, 2, |0}
		;; Token{), 3, 2, |0}
		;; Token{_, 6, 0, |0}
		;; Token{gasan, 1, 0, |0}
		;; Token{(, 3, 1, |0}
		;; Token{_, 6, 0, |0}
		;; Token{getaddr, 1, 0, |0}
		;; Token{(, 3, 1, |0}
		;; Token{_, 6, 0, |0}
		;; Token{composefun, 1, 6, |0}
		;; Token{), 3, 2, |0}
		;; Token{), 3, 2, |0}
;;------- POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{composefun, 1, 6, |0}
		;; Token{getaddr, 1, 0, |0}
		;; Token{gasan, 1, 0, |0}
;;------- //POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{composefun, 1, 6, |0}
;; resolving... 
		;; Token{composefun, 1, 6, |0}
;; ENTERING IF main
;; VAR composefun HERE
;; PARAMS SIZE: 0

;; stpush 		;; Token{composefun, 1, 6, |0}


		;; Token{getaddr, 1, 0, |0}
;; resolving... 
		;; Token{getaddr, 1, 0, |0}
;; ENTERING IF main
;; VAR getaddr HERE
;; PARAMS SIZE: 1
		;; Token{composefun, 1, 6, |0}

;; FCT CALL getaddr: @return 1 @#params: 1
	adr x15, composefun
	str x15 , [sp, #-16]! ;; push x15
;; ret nr: 1
	bl getaddr
	add sp, sp, #16
	str x0 , [sp, #-16]! ;; push x0
		;; Token{$$[x29 , #-32], 4, 8, |1}
;; stpush 		;; Token{$$[x29 , #-32], 4, 8, |1}


		;; Token{gasan, 1, 0, |0}
;; resolving... 
		;; Token{gasan, 1, 0, |0}
;; ENTERING IF main
;; VAR gasan HERE
;; PARAMS SIZE: 1
		;; Token{$$[x29 , #-32], 4, 8, |1}

;; IS_VAR gasan
	ldr x15, [x29 , #-32]
	str x15, [x29 , #-16]
;;-------


;; [LINE] _horia(_getaddr(_gasan))

		;; Token{_, 6, 0, |0}
		;; Token{horia, 1, 0, |0}
		;; Token{(, 3, 1, |0}
		;; Token{_, 6, 0, |0}
		;; Token{getaddr, 1, 0, |0}
		;; Token{(, 3, 1, |0}
		;; Token{_, 6, 0, |0}
		;; Token{gasan, 1, 0, |0}
		;; Token{), 3, 2, |0}
		;; Token{), 3, 2, |0}
		;; Token{_, 6, 0, |0}
		;; Token{horia, 1, 0, |0}
		;; Token{(, 3, 1, |0}
		;; Token{_, 6, 0, |0}
		;; Token{getaddr, 1, 0, |0}
		;; Token{(, 3, 1, |0}
		;; Token{_, 6, 0, |0}
		;; Token{gasan, 1, 6, |0}
		;; Token{), 3, 2, |0}
		;; Token{), 3, 2, |0}
;;------- POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{gasan, 1, 6, |0}
		;; Token{getaddr, 1, 0, |0}
		;; Token{horia, 1, 0, |0}
;;------- //POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{gasan, 1, 6, |0}
;; resolving... 
		;; Token{gasan, 1, 6, |0}
;; ENTERING IF main
;; VAR gasan HERE
;; PARAMS SIZE: 0

;; IS_VAR gasan
		;; Token{$$[x29 , #-16], 4, 8, |1}
;; stpush 		;; Token{$$[x29 , #-16], 4, 8, |1}


		;; Token{getaddr, 1, 0, |0}
;; resolving... 
		;; Token{getaddr, 1, 0, |0}
;; ENTERING IF main
;; VAR getaddr HERE
;; PARAMS SIZE: 1
		;; Token{$$[x29 , #-16], 4, 8, |1}

;; FCT CALL getaddr: @return 1 @#params: 1
		;; begin push 
	ldr  x15, [x29 , #-16]
	str x15 , [sp, #-16]! ;; push x15
;; ret nr: 1
	bl getaddr
	add sp, sp, #16
	str x0 , [sp, #-16]! ;; push x0
		;; Token{$$[x29 , #-48], 4, 8, |1}
;; stpush 		;; Token{$$[x29 , #-48], 4, 8, |1}


		;; Token{horia, 1, 0, |0}
;; resolving... 
		;; Token{horia, 1, 0, |0}
;; ENTERING IF main
;; VAR horia NOT HERE
;; VAR horia NOT HERE 1
		;; begin push 
	ldr  x15, [x29 , #-48]
	str x15 , [sp, #-16]! ;; push x15
;;-------


;; [LINE] make horia : func(3, 1)

		;; Token{make, 6, 10, |0}
		;; Token{horia, 1, 0, |0}
		;; Token{:, 3, 0, |0}
		;; Token{func, 1, 11, |0}
		;; Token{(, 3, 1, |0}
		;; Token{3, 4, 7, |0}
		;; Token{,, 0, 3, |0}
		;; Token{1, 4, 7, |0}
		;; Token{), 3, 2, |0}
		;; Token{make, 6, 10, |0}
		;; Token{horia, 1, 6, |0}
		;; Token{:, 3, 0, |0}
		;; Token{func, 1, 11, |0}
		;; Token{(, 3, 1, |0}
		;; Token{3, 4, 7, |0}
		;; Token{,, 0, 3, |0}
		;; Token{1, 4, 7, |0}
		;; Token{), 3, 2, |0}
;;------- POSTFIX
		;; Token{make, 6, 10, |0}
		;; Token{horia, 1, 6, |0}
		;; Token{3, 4, 7, |0}
		;; Token{1, 4, 7, |0}
		;; Token{func, 1, 11, |0}
;;------- //POSTFIX
		;; Token{make, 6, 10, |0}
		;; Token{horia, 1, 6, |0}
;; resolving... 
		;; Token{make, 6, 10, |0}
		;; Token{horia, 1, 6, |0}
;; ENTERING IF main
;; VAR horia HERE
;; PARAMS SIZE: 1
		;; Token{make, 6, 10, |0}

;; IS_VAR horia
;; IDENTITY
;; stpush 		;; Token{horia, 1, 6, |0}


		;; Token{3, 4, 7, |0}
		;; Token{1, 4, 7, |0}
		;; Token{func, 1, 11, |0}
;; resolving... 
		;; Token{func, 1, 11, |0}
;; ENTERING IF main
;; MAKE_TOK: PARAMS#: 3
		;; Token{1, 4, 7, |0}
		;; Token{3, 4, 7, |0}
		;; Token{horia, 1, 6, |0}
;; make horia :: ret 3 :: pno 1
;; DONE MAKE_TOK
;;-------


;; [LINE] _call(1, _horia(_dblp, _trpl, 2))
		;; Token{_, 6, 0, |0}
		;; Token{call, 1, 5, |0}
		;; Token{(, 3, 1, |0}
		;; Token{1, 4, 7, |0}
		;; Token{,, 0, 3, |0}
		;; Token{_, 6, 0, |0}
		;; Token{horia, 1, 0, |0}
		;; Token{(, 3, 1, |0}
		;; Token{_, 6, 0, |0}
		;; Token{dblp, 1, 0, |0}
		;; Token{,, 0, 3, |0}
		;; Token{_, 6, 0, |0}
		;; Token{trpl, 1, 0, |0}
		;; Token{,, 0, 3, |0}
		;; Token{2, 4, 7, |0}
		;; Token{), 3, 2, |0}
		;; Token{), 3, 2, |0}
		;; Token{_, 6, 0, |0}
		;; Token{call, 1, 5, |0}
		;; Token{(, 3, 1, |0}
		;; Token{1, 4, 7, |0}
		;; Token{,, 0, 3, |0}
		;; Token{_, 6, 0, |0}
		;; Token{horia, 1, 0, |0}
		;; Token{(, 3, 1, |0}
		;; Token{_, 6, 0, |0}
		;; Token{dblp, 1, 6, |0}
		;; Token{,, 0, 3, |0}
		;; Token{_, 6, 0, |0}
		;; Token{trpl, 1, 6, |0}
		;; Token{,, 0, 3, |0}
		;; Token{2, 4, 7, |0}
		;; Token{), 3, 2, |0}
		;; Token{), 3, 2, |0}
;;------- POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{1, 4, 7, |0}
		;; Token{_, 6, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{dblp, 1, 6, |0}
		;; Token{_, 6, 0, |0}
		;; Token{trpl, 1, 6, |0}
		;; Token{2, 4, 7, |0}
		;; Token{horia, 1, 0, |0}
		;; Token{call, 1, 5, |0}
;;------- //POSTFIX
		;; Token{_, 6, 0, |0}
		;; Token{1, 4, 7, |0}
		;; Token{_, 6, 0, |0}
		;; Token{_, 6, 0, |0}
		;; Token{dblp, 1, 6, |0}
;; resolving... 
		;; Token{dblp, 1, 6, |0}
;; ENTERING IF main
;; VAR dblp HERE
;; PARAMS SIZE: 0

;; stpush 		;; Token{dblp, 1, 6, |0}


		;; Token{_, 6, 0, |0}
		;; Token{trpl, 1, 6, |0}
;; resolving... 
		;; Token{trpl, 1, 6, |0}
;; ENTERING IF main
;; VAR trpl HERE
;; PARAMS SIZE: 0

;; stpush 		;; Token{trpl, 1, 6, |0}


		;; Token{2, 4, 7, |0}
		;; Token{horia, 1, 0, |0}
;; resolving... 
		;; Token{horia, 1, 0, |0}
;; ENTERING IF main
;; VAR horia HERE
;; PARAMS SIZE: 3
		;; Token{2, 4, 7, |0}
		;; Token{trpl, 1, 6, |0}
		;; Token{dblp, 1, 6, |0}

;; FCT CALL horia: @return 1 @#params: 3
		;; begin push 
	mov  x15, #2
	str x15 , [sp, #-16]! ;; push x15
	adr x15, trpl
	str x15 , [sp, #-16]! ;; push x15
	adr x15, dblp
	str x15 , [sp, #-16]! ;; push x15
;; ret nr: 1
	ldr x14, [x29 , #-64] ;; [horia]
	blr x14
	add sp, sp, #48
	str x0 , [sp, #-16]! ;; push x0
		;; Token{$$[x29 , #-80], 4, 8, |1}
;; stpush 		;; Token{$$[x29 , #-80], 4, 8, |1}


		;; Token{call, 1, 5, |0}
		;; Token{call, 1, 5, |0}
;; ENTERING IF main
	mov   x16, #1
		;; begin push 
	ldr  x15, [x29 , #-80]
	str x15 , [sp, #-16]! ;; push x15
	ldr x0, [sp], #16 ;; pop x0
	svc #0
		;; Token{$$x0, 4, 8, |0}
;;<<END
