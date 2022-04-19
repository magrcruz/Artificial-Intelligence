(defglobal ?*numero* = 10)

(deffunction pregunta-numerica (?pregunta ?rangini ?rangfi)
  (format t "%s [%d %d] " ?pregunta ?rangini ?rangfi )
  (bind ?respuesta (read))
  (while (not(and(> ?respuesta ?rangini)(< ?respuesta ?rangfi))) do
         (format t "¿%s [%d %d] " ?pregunta ?rangini ?rangfi )
         (bind ?respuesta (read)) 
  )
  ?respuesta
) 

(deffunction guess-number (?num)
  (bind ?number ?num)
  (while (not(= ?number ?*numero*)) do
      (if (> ?number ?*numero*)
        then
        (printout t "El numero recibido es mayor " crlf)
        else
        (printout t "El numero recibido es menor " crlf)
      )
    (bind ?number (pregunta-numerica "Ingrese otro numero" 1 100))
  )
  ?number
)
(defrule leer-numero
  =>
  (bind ?inp (pregunta-numerica "Ingrese un numero" 1 100))
  (bind ?n (guess-number ?inp))
  (assert (numero ?n))
)

(defrule num-actual
 (declare (salience -1))
 (numero ?n)
 =>
 (printout t "El numero que ingreso es el correcto" crlf)
)