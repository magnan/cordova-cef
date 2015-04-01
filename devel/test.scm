(define baz
  (js-lambda_v2 (a b)
    "alert(a+b);"))


(define-export somebool
  #f)

(define-export someint
  2)

(define-export somestring
  "hello")

(define-export someundefined
  'foo)


(define-export (mutate str)
  (set! somestring str))


(define-export (exp)
  (exit))


(define call-exp
  (js-lambda_v2 ()
    "alert(somebool()); alert(someint()); alert(somestring()); mutate('ca marche'); alert(somestring()); alert(someundefined()); exp();"))


(call-exp)
