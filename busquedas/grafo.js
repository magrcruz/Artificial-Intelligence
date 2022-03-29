////////////////////////UTILIDADES
function shuffle(array) {
  var m = array.length, t, i;

  // While there remain elements to shuffle…
  while (m) {

    // Pick a remaining element…
    i = Math.floor(Math.random() * m--);

    // And swap it with the current element.
    t = array[m];
    array[m] = array[i];
    array[i] = t;
  }

  return array;
}

/*

La funcion de shuffle de https://bost.ocks.org/mike/shuffle/


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

class Graph{
    constructor(vertices) {
        this.tam_grafo=vertices;
        this.grafo = Array(vertices);
        for(let i=0;i< vertices;i++){
            this.grafo[i]=[];
        }
    }

    ///Funciones de utilidad para la clase grafo
    distancia(origin, destiny){
        return Math.sqrt(Math.pow(origin[0]-destiny[0],2)+Math.pow(origin[1]-destiny[1],2));
    }
    repetition(list,element){
        for(let j=0; j< list.length;j++){
          if(list[j][0]==element[0]&& list[j][1]== element[1])
            return true;
        }
        return false;
  
    }

    print() {
        for(let i=0;i<this.grafo.length;i++){
            console.log("vertice",i);
            console.log("numero de aristas",this.grafo[i].length);
            for(let j= 0; j<this.grafo[i].length;j++){
                console.log("arista",j,this.grafo[i][j])
            }
        }            
    }

    getCoord(index,n=Math.sqrt(this.tam_grafo,2)){
        let y = index%n;
        return [(index-y)/n, y];
    }
    ////////////////////////////////////////////////////////////////
    /////Funciones de crear y eliminar
    addEdge(origin, destiny){
        //Calcula la distancia entre los dos vertices
        let coor_ori=this.getCoord(origin);
        let coor_dest=this.getCoord(destiny);
        var distance=this.distancia(coor_ori,coor_dest);
        
        if(this.grafo[origin].length==0){
          this.grafo[origin].push([destiny,distance]);
        }
        if(this.grafo[destiny].length==0){
          this.grafo[destiny].push([origin,distance]);
        }

        if(this.repetition(this.grafo[origin],[destiny,distance])== false){
          this.grafo[origin].push([destiny,distance]);
        }
        if(this.repetition(this.grafo[destiny],[origin,distance])== false){
          this.grafo[destiny].push([origin,distance]);
        }
    }
    removeEdge(origen_i, destino_i){
        if(this.grafo[origen_i]) {
            for( let i=0;i<this.grafo[origen_i].length;){
                if(this.grafo[origen_i][i][0] == destino_i){
                    //Elimina el elemento poniendo en su lugar el ultimo elemento y eliminando el duplicado
                    this.grafo[origen_i][i]=this.grafo[origen_i][this.grafo[origen_i].length-1]
                    this.grafo[origen_i].pop()
                }
                i++
            }
        }
        //Repite el procedimiento para el edge en el detino
        if(this.grafo[destino_i]) {
            for( let i=0;i<this.grafo[destino_i].length;){
                if(this.grafo[destino_i][i][0] == origen_i){
                    this.grafo[destino_i][i]=this.grafo[destino_i][this.grafo[destino_i].length-1]
                    this.grafo[destino_i].pop()
                }
                i++
            }
            
        }
    }
    
    removeNode(nodo_i){
        //Elimina cada uno de los vertices del nodo
        let aristas = this.grafo[nodo_i].slice(0,this.grafo[nodo_i].length)
        aristas.forEach(arista => {
            this.removeEdge(nodo_i,arista[0])
        })

        /*        
        console.log("Llego este nodo ",nodo_i, "que tiene ",this.grafo[nodo_i].length," vertices")
        for(let i=0;i<this.grafo[nodo_i].length;i++){
            console.log("Paso por for ",++c," veces")
            this.removeEdge(nodo_i,this.grafo[nodo_i][i][0])
        }*/
        //Elimina el array de vertices indicando que el nodo no existe
        this.grafo[nodo_i] = null
        addChange([nodo_i,this.getCoord(nodo_i)],"none" )
    }

    eliminarNodos(porcentaje){//0.2
      let c=0
        let numbers = Array.from(Array(this.tam_grafo).keys())
        shuffle(numbers)
        this.nodosEliminados =  numbers.slice(0,porcentaje*this.tam_grafo)
        this.nodosEliminados.forEach(index => {
          this.removeNode(index)
        })
        
    }

    crearGrafocompleto(){
        let row_col=Math.sqrt(this.tam_grafo,2);
        ///////////////////////////////////////////////////////////
        //create corners
        let val_corners=[0,row_col-1,row_col*(row_col-1),row_col*(row_col-1)+(row_col-1)];// [0,99,9900,9999]
        
        //0 && 9990
        let val_first_last=[row_col+1,1,row_col]/// [101,100,1]
        for(let i=0;i<3;i++){
            this.addEdge(val_corners[0], val_corners[0] + val_first_last[i]);
            this.addEdge(val_corners[3], val_corners[3] - val_first_last[i]);
        }
        //99 && 9900
        let val_other_corners=[(row_col-1),-1,row_col]/// [99,-1,100]
        for(let i=0;i<3;i++){
            this.addEdge(val_corners[1], val_corners[1] + val_other_corners[i]);
            this.addEdge(val_corners[2], val_corners[2] - val_other_corners[i]);
        }
        ////////////////////////////////////////////////////////////
  
        //////////////////////////////////////////////////////////
        //create side left
        let val_left=[-1*(row_col-1),row_col+1,1,row_col,-row_col] ///[-99,101,1,100,-100]
        for(let i=row_col;i<row_col*(row_col-1);i=i+row_col){
          this.addEdge(i, i + val_left[0]);
          this.addEdge(i, i + val_left[1]);
          this.addEdge(i, i + val_left[2]);
          this.addEdge(i, i + val_left[3]);
          this.addEdge(i, i + val_left[4]);
        }
        ////////////////////////////////////////////////////////////
        //create side right
        let val_right=[-1*(row_col+1),row_col-1,-1,row_col,-row_col];///[-101,99,-1,100,-100]
        for(let i=row_col+row_col-1;i<row_col*(row_col-1)+(row_col-1);i=i+row_col){
          this.addEdge(i, i + val_right[0]);
          this.addEdge(i, i + val_right[1]);
          this.addEdge(i, i + val_right[2]);
          this.addEdge(i, i + val_right[3]);
          this.addEdge(i, i + val_right[4]);
        }
  
        ////////////////////////////////////////////////////////////
        //create side up
        let val_up=[row_col+1,row_col-1,-1,1,row_col];///[101,99,-1,1,100]
        for(let i=1;i<row_col-1;i++){
          this.addEdge(i, i + val_up[0]);
          this.addEdge(i, i + val_up[1]);
          this.addEdge(i, i + val_up[2]);
          this.addEdge(i, i + val_up[3]);
          this.addEdge(i, i + val_up[4]);
        }
  
        ////////////////////////////////////////////////////////////
        //create side down
        let val_down=[-1*(row_col-1),-1*(row_col+1),-1,1,-row_col];///[-99,-101,-1,1,-100]
        for(let i=row_col*(row_col-1)+1;i<row_col*(row_col-1)+(row_col-1);i++){
          this.addEdge(i, i + val_down[0]);
          this.addEdge(i, i + val_down[1]);
          this.addEdge(i, i + val_down[2]);
          this.addEdge(i, i + val_down[3]);
          this.addEdge(i, i + val_down[4]);
        }
        ////////////////////////////////////////////////////////////
        //create centers
        let val_centers=[row_col-1,-1*(row_col-1),row_col+1,-1*(row_col+1),-1,1,row_col,-row_col];///[99,-99,,01,-101,-1,1,100,-100]
        for(let i=row_col+1;i<row_col*(row_col-1)+1;i=i+row_col){
          for(let j=i;j<i+row_col-2;j++){
            this.addEdge(j, j + val_centers[0]);
            this.addEdge(j, j + val_centers[1]);
            this.addEdge(j, j + val_centers[2]);
            this.addEdge(j, j + val_centers[3]);
            this.addEdge(j, j + val_centers[4]);
            this.addEdge(j, j + val_centers[5]);
            this.addEdge(j, j + val_centers[6]);
            this.addEdge(j, j + val_centers[7]);
          }
  
        }
  
    }
    delGraph(){
        this.grafo = Array(this.tam_grafo);
        for(let i=0;i< this.tam_grafo;i++){
            this.grafo[i]=[];
        }
    }
    /////////////////////////////////////////////////////////////////////////////
    ////Busquedas Ciegas


    //Nodo [16,[x,y]]
    dfs_recursion(nodo, destino, visitados,recorrido,recorrido_b,recorrido_c){
        try{addChange(nodo,"actual")}catch (error){}
        
        if(nodo[0]==destino[0]){
          recorrido.push(nodo)
            return true
        }
        let edges = this.grafo[nodo[0]]
        //arista [nodo, distancia]
        for(let i=0;i<edges.length;i++){
            if(!visitados[edges[i][0]]){
                visitados[edges[i][0]]=1
                try{recorrido.push(nodo)}catch (error){
                  try{recorrido_b.push(nodo)}catch (error){recorrido_c.push(nodo)}
                }
                
                if(this.dfs_recursion([edges[i][0],this.getCoord(edges[i][0])], destino, visitados,recorrido,recorrido_b,recorrido_c)) return true;
                recorrido.pop()
            }
        }
        return false;
    }
    dfs(origen,destino){
        let visitados = Array(this.tam_grafo).fill(0);//Para guardar que nodos ya visite
        visitados[origen[0]]=1
        let recorrido = []
        let recorrido_b=[];
        let recorrido_c=[];
        let encontro = this.dfs_recursion(origen,destino,visitados,recorrido,recorrido_b,recorrido_c)
        mostrarCamino(recorrido)
        mostrarCamino(recorrido_b)
        mostrarCamino(recorrido_c)
        return encontro
    }

    bfs(origen,destino){
      let recorrido = [];
      let visited = Array(this.tam_grafo).fill(-1);
      visited[origen[0]]=1;
      var _cola=[origen]
      while(_cola.length>0){
          let currentVertex=_cola[0];
          let nodo = [currentVertex[0],this.getCoord(currentVertex[0])];
          try{addChange(nodo,"actual")}catch (error){}
          recorrido.push(nodo);
          
          if(currentVertex[0]==destino[0]) { return;}
          _cola.shift();
          for(let i = 0; i<this.grafo[currentVertex[0]].length;i++){
              if(visited[this.grafo[currentVertex[0]][i][0]]==-1){
                  visited[this.grafo[currentVertex[0]][i][0]]=1;
                  _cola.push(this.grafo[currentVertex[0]][i]);
              }
          }
          
          //addChange(origen,"inicio");
          //addChange(destino,"fin");
      }
      mostrarCamino(recorrido)
    }

    ////////////////////////////////////////////////
    /////Busquedas Heuristicas

    a_star_recursion(nodoActual, destino,visitados, recorrido){//Pasa todo el node
        addChange(nodoActual,"actual")
        if(nodoActual[0]==destino[0]){//Si encuentro el objetivo detiene la busqueda
            return true;
        }
        //Pasa por todos las aristas, calcula los costos y almacena ordenadamente
        let opciones = [];
        for( let i=0;i<this.grafo[nodoActual[0]].length;i++){
            if(!visitados[this.grafo[nodoActual[0]][i][0]]){//Si no esta visitado lo agrega a las opciones
              let nodoSiguiente = [this.grafo[nodoActual[0]][i][0],this.getCoord(this.grafo[nodoActual[0]][i][0])]
              opciones.push({cost:(this.grafo[nodoActual[0]][i][1]+this.distancia(nodoSiguiente[1],destino[1])),destino:nodoSiguiente});
            }
        }
        opciones.sort((a,b)=>a.cost-b.cost);
        //Se visitan los edges desde las mejor opcion
        for(let i=0;i<opciones.length;i++){
            let actual = opciones[i];//El edge que esta por visitar, se marca como visitado y agrega al recorrido
            visitados[actual.destino[0]]=1
            recorrido.push(actual.destino);
            if(this.a_star_recursion(actual.destino,destino,visitados,recorrido)) return true;
            //Si llega a un punto donde no puede avanzar retorna en la recursion, es poco probable
            recorrido.pop();
            //visitados[actual.destino[0]]=0
        }
        return false;
    }

    a_star(origen, destino){//Recibe el grafo y dos vertices
        //Paso 1, comprobar que el nodo exista
        if(this.grafo[origen[0]]==null || this.grafo[destino[0]]==null) return false;
    
        let visitados = Array(this.tam_grafo).fill(0);//Para guardar que nodos ya visite
        visitados[origen[0]]=1
        let recorrido = [origen]//Agrega el origen al inicio del recorrido
        let encontro = this.a_star_recursion(origen, destino,visitados,recorrido)
        mostrarCamino(recorrido)
        return encontro;
    }

    hill_climbing_recursion(nodoActual, destino,visitados, recorrido){//Pasa todo el node
      addChange(nodoActual,"actual")
      if(nodoActual[0]==destino[0]){//Si encuentro el objetivo detiene la busqueda
          return true;
      }
      //Pasa por todos las aristas, calcula los costos y almacena ordenadamente
      let opciones = [];
      for( let i=0;i<this.grafo[nodoActual[0]].length;i++){
          if(!visitados[this.grafo[nodoActual[0]][i][0]]){//Si no esta visitado lo agrega a las opciones
            let nodoSiguiente = [this.grafo[nodoActual[0]][i][0],this.getCoord(this.grafo[nodoActual[0]][i][0])]
            opciones.push({cost:(this.distancia(nodoSiguiente[1],destino[1])),destino:nodoSiguiente});
          }
      }
      opciones.sort((a,b)=>a.cost-b.cost);
      //Se visitan los edges desde las mejor opcion
      for(let i=0;i<opciones.length;i++){
          let actual = opciones[i];//El edge que esta por visitar, se marca como visitado y agrega al recorrido
          visitados[actual.destino[0]]=1
          recorrido.push(actual.destino);
          if(this.hill_climbing_recursion(actual.destino,destino,visitados,recorrido)) return true;
          //Si llega a un punto donde no puede avanzar retorna en la recursion, es poco probable
          recorrido.pop();
          //visitados[actual.destino[0]]=0
      }
      return false;
  }

  hill_climbing(origen, destino){//Recibe el grafo y dos vertices
      //Paso 1, comprobar que el nodo exista
      if(this.grafo[origen[0]]==null || this.grafo[destino[0]]==null) return false;
  
      let visitados = Array(this.tam_grafo).fill(0);//Para guardar que nodos ya visite
      visitados[origen[0]]=1
      let recorrido = [origen]//Agrega el origen al inicio del recorrido
      let encontro = this.hill_climbing_recursion(origen, destino,visitados,recorrido)
      mostrarCamino(recorrido)
      return encontro;
  }
    
    best_first_search_recursion(nodoActual, destino,visitados,recorrido){
      addChange(nodoActual,"actual")
        if(nodoActual[0]==destino[0]){//Si encuentro el objetivo detiene la busqueda
            return true;
        }
        //Pasa por todos las aristas, calcula los costos y almacena ordenadamente
        let opciones = [];
        for( let i=0;i<this.grafo[nodoActual[0]].length;i++){
            if(!visitados[this.grafo[nodoActual[0]][i][0]]){//Si no esta visitado lo agrega a las opciones
              let nodoSiguiente = [this.grafo[nodoActual[0]][i][0],this.getCoord(this.grafo[nodoActual[0]][i][0])]
              opciones.push({cost:(this.grafo[nodoActual[0]][i][1]),destino:nodoSiguiente});
            }
        }
        opciones.sort((a,b)=>a.cost-b.cost);
        //Se visitan los edges desde las mejor opcion
        for(let i=0;i<opciones.length;i++){
            let actual = opciones[i];//El edge que esta por visitar, se marca como visitado y agrega al recorrido
            visitados[actual.destino[0]]=1
            recorrido.push(actual.destino);
            if(this.best_first_search_recursion(actual.destino,destino,visitados,recorrido)) return true;
            //Si llega a un punto donde no puede avanzar retorna en la recursion, es poco probable
            recorrido.pop();
            //visitados[actual.destino[0]]=0
        }
        return false;
      }
      best_first_search(origen, destino){
        //Paso 1, comprobar que el nodo exista
        if(this.grafo[origen[0]]==null || this.grafo[destino[0]]==null) return false;
    
        let visitados = Array(this.tam_grafo).fill(0);//Para guardar que nodos ya visite
        visitados[origen[0]]=1
        let recorrido = [origen]//Agrega el origen al inicio del recorrido
        let encontro = this.best_first_search_recursion(origen, destino,visitados,recorrido)
        mostrarCamino(recorrido)
        return encontro;
      }
      
}

