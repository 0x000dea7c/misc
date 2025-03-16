;; If the interpreter uses applicative-order evaluation it will loop
;; forever because when evaluating the argument p, it is going to go
;; look the definition of p, and p is defined as p, too. Therefore, it
;; will recurse forever.  If the interpreter uses normal-order
;; evaluation, p won't be evaluated until it is needed. Therefore,
;; when calling test, it will proceed and will evaluate the if
;; statement, and since x is 0, it will return 0, without needing to
;; evaluate p.

(define (p) (p))

(define (test x y)
  (if (= x 0)
      0
      y))

(test 0 (p))
