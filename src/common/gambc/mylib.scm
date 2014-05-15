(c-declare #<<end-of-c-declare
#include "mylib.h"
char* eval_result = NULL;
end-of-c-declare
)

(define (catch-all-errors thunk)
  (with-exception-catcher
    (lambda (exc)
      (write-exception-to-string exc))
    thunk))

(define (write-exception-to-string exc)
  (with-output-to-string
    '()
    (lambda () (display-exception exc))))

(define (write-to-string obj)
  (with-output-to-string
    '()
    (lambda () (write obj))))

(define (read-from-string str)
  (with-input-from-string str read))

;; quick hack around visual c++ compilation problems
(define eval-result-set!
  (c-lambda (char-string) void
#<<end-of-c-declare
    if (eval_result)
        free(eval_result);
    size_t size = strlen(___arg1) + 1;
    eval_result = (char*) malloc(size);
    strcpy_s(eval_result, size, ___arg1);
end-of-c-declare
))

(c-define (eval-string str) (char-string) void "eval_string" "extern"
  (eval-result-set!
    (catch-all-errors
      (lambda ()
        (write-to-string (eval (read-from-string str)))))))

#;
(c-define (eval-string str) (char-string) char-string "eval_string" "extern"
  (catch-all-errors
    (lambda () (write-to-string (eval (read-from-string str))))))
