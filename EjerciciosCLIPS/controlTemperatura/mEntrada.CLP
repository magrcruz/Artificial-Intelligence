(deffunction readValvulas
    ( ?nombre ?temperatura)
    
    (bind ?nombre (read fichero))
    (bind ?temperatura (read-number fichero))
    (printout t "Pos ya que " ?nombre " es  (" ?temperatura ")" crlf)
    (assert (valvula ?nombre ?temperatura))
    
)

(deffunction outputStatus
    ( ?nombre ?temperatura ?estado)
    (printout salida "La temperatura de " ?nombre " es " ?estado " (" ?temperatura ")" crlf)
)

(defmodule IO 
(export readValvulas ?ALL )
(export outputStatus ?ALL )
)

