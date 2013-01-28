(define (quit-for-error)
  ((println (net-error)) (exit)))

(set 'server-ip "localhost")
(set 'server-port 9999)
(set 'request-timeout 15000)

;; check if the connection is closed or not
(define (net-close2? s)
  (if (net-receive s buffer 2) nil true))

(define (net-close? s)
  (if (net-select s "exception" 1000) nil true))

;; send English message to echo server
(define (send-message str-msg)
  (let (s (net-connect server-ip server-port))
    ;; send length
    (unless (net-send s (pack ">u" (length str-msg))) (quit-for-error))
    (unless (net-send s str-msg) (quit-for-error))
    (if (net-receive s result (+ 2 (length str-msg)))
	(println (get-string (+ (address result) 2)))
	(quit-for-error))))

(send-message "hello, freebird")
(send-message "hello, sheismylife")
(exit)
