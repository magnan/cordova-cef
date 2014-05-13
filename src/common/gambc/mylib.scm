(c-declare #<<end-of-c-declare
#include "mylib.h"
end-of-c-declare
)

(define (catch-all-errors thunk)
  (with-exception-catcher
    (lambda (exc)
      (write-to-string exc))
    thunk))

(define (write-to-string obj)
  (with-output-to-string
    '()
    (lambda () (write obj))))

(define (read-from-string str)
  (with-input-from-string str read))

(c-define (eval-string str) (char-string) void "eval_string" "extern"
  (catch-all-errors
    (lambda () (write-to-string (eval (read-from-string str))))))

#;
(c-define (eval-string str) (char-string) char-string "eval_string" "extern"
  (catch-all-errors
    (lambda () (write-to-string (eval (read-from-string str))))))
