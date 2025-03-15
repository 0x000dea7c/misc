(define (sum-of-largest-squares a b c)
  (cond ((> a b)
         (cond ((> b c) (+ (* a a) (* b b)))
                (else (+ (* a a) (* c c)))))
        (else
         (cond ((> a c) (+ (* b b) (* a a)))
                (else (+ (* b b) (* c c)))))))

(sum-of-largest-squares -4 -3 -2)       ; prints 13

(sum-of-largest-squares 0 0 0)          ; prints 0

(sum-of-largest-squares 4 9 5)          ; prints 106
