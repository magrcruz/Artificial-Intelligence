(clear)
(reset)

(open C:/Repositorios/IA/CLIPS/controlTemperatura/temperaturas.dat fichero )
(open C:/Repositorios/IA/CLIPS/controlTemperatura/alarmas.out salida "w")

(defmodule CORE
    (export deffunction ?ALL )
)

(deffunction CORE::readValvulas
    ( ?nombre ?temperatura)
    (bind ?nombre (read fichero))
    (bind ?temperatura (read-number fichero))
    (assert (valvula ?nombre ?temperatura))
)

(deffunction CORE::outputStatus
    ( ?nombre ?temperatura ?estado)
    (printout salida "La temperatura de " ?nombre " es " ?estado " (" ?temperatura ")" crlf)
)

(defrule CORE::read-val
    ( valvula ?nombre ?temperatura )
    =>
    ( readValvulas ?nombre ?temperatura )
)
(defrule CORE::read-clean-trash
    ?v <- ( valvula EOF EOF )
    =>
    (retract ?v)
)

(defrule CORE::evaluar-valvulas
    (valvula $?nombre ?temperatura)
    =>
    (if (> ?temperatura 95)
        then
        ( outputStatus ?nombre ?temperatura peligrosa)
        else
        ( outputStatus ?nombre ?temperatura normal))
    
)

(assert (valvula EOF EOF))

(focus CORE)

(run)
(close fichero)
(close salida)
