;; Using new-if instead of the built-in if statement causes the
;; interpreter to evaluate all arguments (and thus all branches) for
;; every iteration instead of evaluating only one branch. This is
;; because new-if is a normal procedure (or function) and in these
;; cases the interpreter evaluates all the arguments before invoking
;; it. This causes an infinite recursion and the stack blows up.
(define (new-if predicate then-clause else-clause)
  (cond (predicate then-clause)
        (else else-clause)))

(define (average x y)
  (/ (+ x y) 2))

(define (improve guess x)
  (average guess (/ x guess)))

(define (good-enough? guess x)
  (< (abs (- (square guess) x)) 0.001))

;; (define (sqrt-iter guess x)
;;   (if (good-enough? guess x)
;;       guess
;;       (sqrt-iter (improve guess x)
;;                  x)))

(define (sqrt-iter guess x)
  (new-if (good-enough? guess x)
          guess
          (sqrt-iter (improve guess x)
                     x)))

(define (sqrt-me x)
  (sqrt-iter 1.0 x))

(sqrt-me 9)
