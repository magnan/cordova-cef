(c-declare #<<end-of-c-declare
#include "application.h"
#include "mylib.h"
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
    (lambda ()
      (display-exception exc))))

(define (write-to-string obj)
  (with-output-to-string
    '()
    (lambda ()
      (write obj))))

(define (read-from-string str)
  (with-input-from-string str read))

(c-define (eval-string-void str) (char-string) void "gambit_eval_string_void" "extern"
  (eval (read-from-string str)))

(c-define (eval-string-int str) (char-string) int "gambit_eval_string_int" "extern"
  (eval (read-from-string str)))

(c-define (eval-string-string str) (char-string) char-string "gambit_eval_string_string" "extern"
  (eval (read-from-string str)))

(c-define (eval-string str) (char-string) char-string "gambit_eval_string" "extern"
  (write-to-string
    (eval (read-from-string str))))

(c-define (eval-string-catch str) (char-string) char-string "gambit_eval_string_catch" "extern"
  (catch-all-errors
    (lambda ()
      (write-to-string
        (eval (read-from-string str))))))

(define call-js
  (c-lambda (char-string) void
    "call_js(___arg1);"))

(define register-export
  (c-lambda (char-string int) void
    "register_export(___arg1, ___arg2);"))

(c-define (heartbeat) () void "gambit_heartbeat" "extern"
  (##thread-heartbeat!)
  (let ((thread-process 'jazz.language.runtime.functional:thread-process))
    (if (##global-var? thread-process)
        (let ((func (##global-var-ref thread-process)))
          (if (not (##unbound? func))
              (func timeout: 0))))))
