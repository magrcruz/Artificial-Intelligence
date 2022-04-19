(deftemplate valvula
    (slot nombre
        (type SYMBOL))
    (slot temperatura
        (type NUMBER))
    (slot estado
        (type SYMBOL)
        (default normal)
        (allowed-symbols normal peligrosa)
        )
)
(assert leer 1)
(open C:/Repositorios/IA/CLIPS/controlTemperatura/temperaturas.dat fichero)

(defrule leer-valvula
(leer)
=>
printout t "Esto leyo " (readline fichero) crlf
)



(defrule leer-nombres
=>
(open nombres.txt fichero)

(assert (nombre (readline fichero)))
(close fichero))






# aqui


modulo de leer, de evaluar, de escribir

(close fichero)
(open C:/Repositorios/IA/CLIPS/controlTemperatura/temperaturas.dat fichero)
(assert (leer si ))

(defrule leerValvulas
    (leer ?fin )
    =>
    (while (> 1 0 )
        (( ?fin(read fichero) )
        (printout t "Leyo algo" crlf))
    )
)

(defrule leer-valvulas
    (leer ?fin )
    =>
    ((?fin(read fichero))
    (printout t "Algo " ?fin crlf))
)

(read fichero)


(while (?lectura <- read fichero neq EOF) [do] (printout t "Leyo algo" crlf))
(close fichero)




MODO SERIO

(open C:/Repositorios/IA/CLIPS/controlTemperatura/temperaturas.dat fichero )
(read fichero)
(close fichero)

//Version funcion sencilla

(assert (leyendo sigue))
(defrule read-val
    ( leyendo ?in )
    =>
    (printout t "funciona")
)


//En funcion
(assert (leyendo sigue))
(close fichero)
(open C:/Repositorios/IA/CLIPS/controlTemperatura/temperaturas.dat fichero )

(defrule read-val
    ( leyendo ?in )
    =>
    (printout t "Esto leyo " (read fichero))
    (bind ?in (read fichero))
)

// Funciona armar una valvula
(assert (valvula nombre 0))
(close fichero)
(open C:/Repositorios/IA/CLIPS/controlTemperatura/temperaturas.dat fichero )

(defrule read-val
    ( valvula ?nombre ?temperatura )
    =>
    (bind ?nombre (read fichero))
    (bind ?temperatura (read-number fichero))
    (printout t "La valvula es: " ?nombre " y su temperatura es " ?temperatura crlf)
)


// Armar valvulas
(assert (valvula nombre 0))
(close fichero)
(open C:/Repositorios/IA/CLIPS/controlTemperatura/temperaturas.dat fichero )

(defrule read-val
    ( valvula ?nombre ?temperatura )
    =>
    (bind ?nombre (read fichero))
    (bind ?temperatura (read-number fichero))
    (printout t "La valvula es: " ?nombre " y su temperatura es " ?temperatura crlf)
    (assert (valvula ?nombre ?temperatura))
)

(defrule print-val
    (valvula $?nombre ?temperatura)
    =>
    (printout t "La valvula es: " ?nombre " y su temperatura es " ?temperatura crlf)
)


// Eliminar valvula EOF
(clear)
(reset)
(close fichero)
(open C:/Repositorios/IA/CLIPS/controlTemperatura/temperaturas.dat fichero )
(assert (valvula nombre 0))

(defrule read-val
    ( valvula ?nombre ?temperatura )
    =>
    (bind ?nombre (read fichero))
    (bind ?temperatura (read-number fichero))
    (assert (valvula ?nombre ?temperatura))
)
(defrule read-clean-trash
    ?v <- ( valvula EOF EOF )
    =>
    (retract ?v)
)

(defrule print-val
    (valvula $?nombre ?temperatura)
    =>
    (printout t "La valvula es: " ?nombre " y su temperatura es " ?temperatura crlf)
)

//Evaluar si es peligroso

(clear)
(reset)
(close fichero)
(open C:/Repositorios/IA/CLIPS/controlTemperatura/temperaturas.dat fichero )

(assert (valvula nombre 0))
(defrule read-val
    ( valvula ?nombre ?temperatura )
    =>
    (bind ?nombre (read fichero))
    (bind ?temperatura (read-number fichero))
    (assert (valvula ?nombre ?temperatura))
)
(defrule read-clean-trash
    ?v <- ( valvula EOF EOF )
    =>
    (retract ?v)
)

(defrule print-val
    (valvula $?nombre ?temperatura)
    =>
    (printout t "La valvula es: " ?nombre " y su temperatura es " ?temperatura crlf)
)

(defrule evaluar-valvulas
    (valvula $?nombre ?temperatura)
    =>
    (if(<> ?temperatura 0)
        then 
            (if (> ?temperatura 95)
            then
            (printout t "La temperatura de " ?nombre " es peligrosa (" ?temperatura ")" crlf)
            else
            (printout t "La temperatura de " ?nombre " es normal (" ?temperatura ")" crlf))
    )
)

//Pasar a funcion

(clear)
(reset)
(close fichero)
(open C:/Repositorios/IA/CLIPS/controlTemperatura/temperaturas.dat fichero )

(assert (valvula nombre 0))
(defrule read-val
    ( valvula ?nombre ?temperatura )
    =>
    (bind ?nombre (read fichero))
    (bind ?temperatura (read-number fichero))
    (assert (valvula ?nombre ?temperatura))
)
(defrule read-clean-trash
    ?v <- ( valvula EOF EOF )
    =>
    (retract ?v)
)

(defrule print-val
    (valvula $?nombre ?temperatura)
    =>
    (printout t "La valvula es: " ?nombre " y su temperatura es " ?temperatura crlf)
)

(deffunction printStatus
    ( ?nombre ?temperatura ?estado)
    (printout t "La temperatura de " ?nombre " es " ?estado " (" ?temperatura ")" crlf)
)

(defrule evaluar-valvulas
    (valvula $?nombre ?temperatura)
    =>
    (if(<> ?temperatura 0)
        then 
            (if (> ?temperatura 95)
            then
            ( printStatus ?nombre ?temperatura peligrosa)
            else
            ( printStatus ?nombre ?temperatura normal))
    )
)

//Escribe :D

(clear)
(reset)
(close fichero)
(close salida)
(open C:/Repositorios/IA/CLIPS/controlTemperatura/temperaturas.dat fichero )
(open C:/Repositorios/IA/CLIPS/controlTemperatura/alarmas.out salida "w")


(assert (valvula nombre 0))
(defrule read-val
    ( valvula ?nombre ?temperatura )
    =>
    (bind ?nombre (read fichero))
    (bind ?temperatura (read-number fichero))
    (assert (valvula ?nombre ?temperatura))
)
(defrule read-clean-trash
    ?v <- ( valvula EOF EOF )
    =>
    (retract ?v)
)

(deffunction printStatus
    ( ?nombre ?temperatura ?estado)
    (printout salida "La temperatura de " ?nombre " es " ?estado " (" ?temperatura ")" crlf)
)

(defrule evaluar-valvulas
    (valvula $?nombre ?temperatura)
    =>
    (if(<> ?temperatura 0)
        then 
            (if (> ?temperatura 95)
            then
            ( printStatus ?nombre ?temperatura peligrosa)
            else
            ( printStatus ?nombre ?temperatura normal))
    )
)


//FUNCIONA CON BATCH
(clear)
(reset)

(open C:/Repositorios/IA/CLIPS/controlTemperatura/temperaturas.dat fichero )
(open C:/Repositorios/IA/CLIPS/controlTemperatura/alarmas.out salida "w")

(defrule read-val
    ( valvula ?nombre ?temperatura )
    =>
    (bind ?nombre (read fichero))
    (bind ?temperatura (read-number fichero))
    (assert (valvula ?nombre ?temperatura))
)
(defrule read-clean-trash
    ?v <- ( valvula EOF EOF )
    =>
    (retract ?v)
)

(deffunction printStatus
    ( ?nombre ?temperatura ?estado)
    (printout salida "La temperatura de " ?nombre " es " ?estado " (" ?temperatura ")" crlf)
)

(defrule evaluar-valvulas
    (valvula $?nombre ?temperatura)
    =>
    (if(<> ?temperatura 0)
        then 
            (if (> ?temperatura 95)
            then
            ( printStatus ?nombre ?temperatura peligrosa)
            else
            ( printStatus ?nombre ?temperatura normal))
    )
)

(assert (valvula nombre 0))
(run)

//Intento de modulos

(defmodule IO 
(export deffunction ?ALL )
)
