_size = 100
graph = new Graph(_size*_size)
nodoInicio = [0,[0,0]],
nodoFinal = [_size*_size-1,graph.getCoord(_size*_size-1)]
_clickStatus = ""
_porcentaje = 20

function addClickListener(){
    for(let i=0;i<_size;i++){
        for( let j=0;j<_size;j++){
            document.getElementById(i+","+j).addEventListener("click",controles.funciones._click )
        }
    }
}

controles = {
    buttons_id : {
        crear_nuevo_grafo: "comenzar",
        eliminar_pocentaje_grafo: "eliminar_porcentaje",
        borrar_caminos: "sin_caminos",
        bfs : "bfs",
        dfs : "dfs",
        mejor_el_primero: "mejor_el_primero",
        hill_climbing:"hill_climbing",
        a_star: "a_star",
        seleccionar_inicio:"seleccionarInicio",
        seleccionar_fin:"seleccionarFin",
        seleccionarBorrar:"borrando"
    },
    inputs_id :{
        delay_update : "delay",
        porcentaje_para_eliminar : "porcentaje",
    },
    funciones:{
        crear_grafo(){
            graph.delGraph()
            graph.crearGrafocompleto()
            _chart(_size)
            nodoInicio = [0,[0,0]],
            nodoFinal = [_size*_size-1,graph.getCoord(_size*_size-1)]
            addChange(nodoInicio,"inicio")
            addChange(nodoFinal,"fin")
            addClickListener()
            document.getElementById(controles.inputs_id.porcentaje_para_eliminar).disabled = false
            document.getElementById("eliminar_porcentaje").disabled=false
        },
        eliminar_nodos(){
            let porcentaje = document.getElementById(controles.inputs_id.porcentaje_para_eliminar)
            graph.eliminarNodos(_porcentaje/100)
            porcentaje.disabled = true
            this.disabled = true
            restablecerNodosExistentes()
        },
        bfs(){
            restablecerNodosExistentes()
            addChange(nodoInicio,"inicio")
            addChange(nodoFinal,"fin")
            graph.bfs(nodoInicio,nodoFinal)
            addChange(nodoInicio,"inicio")
            addChange(nodoFinal,"fin")
        },
        dfs(){
            restablecerNodosExistentes()
            addChange(nodoInicio,"inicio")
            addChange(nodoFinal,"fin")
            graph.dfs(nodoInicio,nodoFinal)
            addChange(nodoInicio,"inicio")
            addChange(nodoFinal,"fin")
        },
        mejor_el_primero(){
            restablecerNodosExistentes()
            addChange(nodoInicio,"inicio")
            addChange(nodoFinal,"fin")
            graph.best_first_search(nodoInicio,nodoFinal)
            addChange(nodoInicio,"inicio")
            addChange(nodoFinal,"fin")
        },
        hill_climbing(){
            restablecerNodosExistentes()
            addChange(nodoInicio,"inicio")
            addChange(nodoFinal,"fin")
            graph.hill_climbing(nodoInicio,nodoFinal)
            addChange(nodoInicio,"inicio")
            addChange(nodoFinal,"fin")
        },
        a_star(){
            restablecerNodosExistentes()
            addChange(nodoInicio,"inicio")
            addChange(nodoFinal,"fin")
            graph.a_star(nodoInicio,nodoFinal)
            addChange(nodoInicio,"inicio")
            addChange(nodoFinal,"fin")
        },
        _click(clickInfo){
            let coord= this.id.split(',')
            coord[0]=Number(coord[0])
            coord[1]=Number(coord[1])
            if(_clickStatus == "seleccionando_inicio"){
                addChange(nodoInicio,"default")
                nodoInicio = [_size*coord[0]+coord[1],coord]
                _clickStatus=""
                addChange(nodoInicio,"inicio")
            }
            else if(_clickStatus == "seleccionando_final"){
                addChange(nodoFinal,"default")
                nodoFinal = [_size*coord[0]+coord[1],coord]
                _clickStatus=""
                addChange(nodoFinal,"fin")
            }
            else if(_clickStatus == "eliminando_nodos"){
                //console.log("Estamos eliminando el nodo ",_size*coord[0]+coord[1])
                graph.removeNode(_size*coord[0]+coord[1])
            }
        },
        borrar_caminos(){
            restablecerNodosExistentes()
            addChange(nodoInicio,"inicio")
            addChange(nodoFinal,"fin")
        },
        delay_update(){
            changeDelay(this.value)
        },
        porcentaje_update(){
            _porcentaje = this.value
        },

    }
}

//Funciones grafo
document.getElementById(controles.buttons_id.crear_nuevo_grafo).addEventListener("click", controles.funciones.crear_grafo)
document.getElementById(controles.buttons_id.borrar_caminos).addEventListener("click", controles.funciones.borrar_caminos)
document.getElementById(controles.inputs_id.delay_update).addEventListener("input", controles.funciones.delay_update)
document.getElementById(controles.buttons_id.eliminar_pocentaje_grafo).addEventListener("click", controles.funciones.eliminar_nodos)

document.getElementById(controles.inputs_id.porcentaje_para_eliminar).addEventListener("input", controles.funciones.porcentaje_update)

//Busquedas
document.getElementById(controles.buttons_id.a_star).addEventListener("click", controles.funciones.a_star)
document.getElementById(controles.buttons_id.bfs).addEventListener("click", controles.funciones.bfs)
document.getElementById(controles.buttons_id.dfs).addEventListener("click", controles.funciones.dfs)
document.getElementById(controles.buttons_id.mejor_el_primero).addEventListener("click", controles.funciones.mejor_el_primero)
document.getElementById(controles.buttons_id.hill_climbing).addEventListener("click", controles.funciones.hill_climbing)

//Inicio y final
document.getElementById(controles.buttons_id.seleccionar_inicio).addEventListener("click", ()=>{_clickStatus = "seleccionando_inicio"})
document.getElementById(controles.buttons_id.seleccionar_fin).addEventListener("click", ()=>{_clickStatus = "seleccionando_final"})
document.getElementById(controles.buttons_id.seleccionarBorrar).addEventListener("click", ()=>{_clickStatus = "eliminando_nodos"})
