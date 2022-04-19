(reset)
(clear)

(open C:/Repositorios/IA/CLIPS/leerNombres/nombres.dat fichero )

(assert (persona (read fichero) (read fichero) (read fichero)) )

(defrule read-val
    ( persona ?nombre ?ap1 ?ap2 )
    =>
    (bind ?nombre (read fichero))
    (if (neq ?nombre EOF)
        then
        (bind ?apellido1 (read fichero))
        (bind ?apellido2 (read fichero))
        (assert (persona ?nombre ?apellido1 ?apellido2))
    )
)

(defrule printNames
    ( persona ?n ?ap1 ?ap2 )
    =>
    (printout t "Persona -> Nombre: " ?n " Apellido-1: " ?ap1 " Apellido-2: " ?ap2 crlf)
)
(run)
(close fichero)
