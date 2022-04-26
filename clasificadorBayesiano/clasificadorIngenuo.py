import random, os

class clasificadorIngenuo:
    def __init__(self, clases, atributos):
        self.probabilidades = {}
        self.clases = clases
        self.atributos = atributos
        for clase in  clases:
            self.probabilidades[clase]={}
            for atributo in atributos:
                self.probabilidades[clase][atributo] = {}
                for value in atributos[atributo]:
                    self.probabilidades[clase][atributo][value] = 0
    def separateInClasses(self, archivo, limite):

        # separa los datos segun las clases
        archivo = open(archivo,"r")
        archivosSalida = {}
        classCount = {}
        for clase in self.clases:
            classCount[clase] = 0
            archivosSalida[clase] = open(clase+".txt","w")
        for line in archivo:
            campos = line[:-1].split(",") # [:-1] para ignorar el salto de linea
            if campos[-1] in self.clases:
                if classCount[campos[-1]] < limite:
                    archivosSalida[campos[-1]].write(line)
                    classCount[campos[-1]] += 1
        for clase in self.clases:
            archivosSalida[clase].close()

    def muestraTest(self,porcentaje):
        arrMuestra=[]
        f = open('muestra.txt', 'w')
        g = open('test.txt', 'w')
        for clase in self.clases:
            archivo = open(clase+".txt","r")
            arr = archivo.readlines()
            archivo.close()

            tamData = len(arr)
            dataPorcentaje=porcentaje*tamData//1
            while dataPorcentaje > 0:
                pos = random.randint(0, dataPorcentaje)
                arrMuestra.append(arr[pos])
                arr.pop(pos)
                dataPorcentaje=dataPorcentaje-1
            g.writelines(arr)
        f.writelines(arrMuestra)
        f.close()
        g.close()

    def build(self):
        archivo = open("muestra.txt","r")
        clasesCount = {}
        for clase in self.clases:
            clasesCount[clase] = 0
        
        # Conteo
        for line in archivo:
            campos = line[:-1].split(",")
            clase = campos[-1]
            clasesCount[clase] += 1
            i=0
            for atributo in self.atributos:
                self.probabilidades[clase][atributo][campos[i]] += 1
                i += 1
        archivo.close()

        # Calculo de probabilidad
        for clase in  self.clases:
            for atributo in self.atributos:
                for value in self.atributos[atributo]:
                    if clasesCount[clase]:
                        self.probabilidades[clase][atributo][value] /= clasesCount[clase]
    
    def evaluar(self,campos):
        mejorProbabilidad = {
            "nombre": "",
            "probabilidad": -1
        }
        for clase in self.probabilidades:
            probabilidadActual = 1
            i=0
            for atributo in self.atributos:
                probabilidadActual *= self.probabilidades[clase][atributo][campos[i]]
                i += 1
            if probabilidadActual > mejorProbabilidad["probabilidad"]:
                mejorProbabilidad = {
                    "nombre": clase,
                    "probabilidad": probabilidadActual
                }
        return mejorProbabilidad["nombre"]

    def evaluarPrecision(self):
        good = 0
        bad = 0
        archivo = open("test.txt", "r")
        for line in archivo:
            campos = line[:-1].split(",")
            prediccion = self.evaluar(campos)
            if(prediccion == campos[-1]):
                #print("+ Se predijo:",prediccion," y la respuesta correcta es:",campos[-1])
                good+= 1
            else:
                print("- Se predijo:",prediccion," y la respuesta correcta es:",campos[-1])
                bad+= 1
        print("Se predijeron ",good," resultados correcto(s) y ",bad," incorrecto(s)")
        precision = good / (good+bad)
        print("La precision es de ",precision *100, "%")
        return precision

    def removeFiles(self):
        for clase in self.clases:
            if os.path.exists(clase+".txt"):
                os.remove(clase+".txt")

def readAttributes(archivo):
    archivo = open(archivo, "r")
    archivo.readline() # Class Values:
    clases = archivo.readline()[:-1].split(", ")

    atributos = {}
    archivo.readline() # (Empty line)
    archivo.readline() # Attributes:
    for line in archivo:
        atVal = line[:-2].split(": ") # Ignora el punto y \n
        values = atVal[1].split(", ")
        atributos[atVal[0]] = values
    archivo.close()
    return clases, atributos

clases,atributos = readAttributes("carros.txt")
clasificador = clasificadorIngenuo(clases,atributos)
clasificador.separateInClasses("car.data", 65) # separa las clases
clasificador.muestraTest(0.8) # separa los datos en muestra.txt y test.txt
clasificador.build() # realiza un precalculo de la muestra
clasificador.evaluarPrecision() # evalua test.txt
clasificador.removeFiles() # paso adicional para eleiminar archivos intermedios 