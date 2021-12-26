#Actividad Evaluada 1
#Rodrigo Kobayashi Araya
#Lenguaje Python 2.7
#Problema: generar una simulación de planificación de procesos para el algoritmo Round Robin 

#Programa hecho para entrada de 6 procesos.


letras = ["A","B","C","D","E","F"]

#clase proceso, se genera la clase para obtener objetos llamados Procesos, los cuales tienen atributos necesarios para 
#su funcionamiento y el cálculo posterior de métricas
class Proceso:
    def __init__(self, nombre, tCpu, tLlegada):
        self.nombre = nombre
        self.tCpu = tCpu
        self.tLlegada = tLlegada
        self.tEspera = 0
        self.tRetorno = 0
        self.tRNormalizado = 0.0
        self.tProcesado = 0
        self.status = " "
    
    def calcularMetricas(self):
        self.tRetorno = self.tCpu + self.tEspera
        self.tRNormalizado = float(self.tRetorno/self.tCpu)

def printProcesos(lista):
    print "___"+lista[0].status+"___"+lista[1].status+"___"+lista[2].status+"___"+lista[3].status+"___"+lista[4].status+"___"+lista[5].status+"___"


# Se inicia la toma de datos
listaProcesos = []
print "ingrese el tiempo maximo de procesamiento: "
q = int(raw_input())
print "Este programa requiere ingresar 6 procesos."
for i in letras:
    print "ingrese el tiempo de procesamiento del proceso  " , i , ": "
    tCpu = int(raw_input())
    print "ingrese el tiempo de llegada del proceso  " , i , ": "
    tLlegada = int(raw_input())
    pr = Proceso(i, tCpu, tLlegada)
    listaProcesos.append(pr)


#generacion de tabla
print "TABLA DE PROCESOS: x=procesando"
print "___A___B___C___D___E___F___"


tTotal = 0
orden = []
tActivo = 0
#se recorren los procesos para obtener el tiempo total de procesamiento
for p in listaProcesos:
    tTotal += p.tCpu

#se genera un loop de acuerdo al total del tiempo de procesamiento
for i in range(-1,tTotal):
    if len(orden) != 0 :
        if orden[0].tProcesado == orden[0].tCpu:    #caso en el que un proceso termine 
            orden[0].calcularMetricas
            orden[0].status = " "
            del orden[0]
        if tActivo==q:      #caso en que se llegue al tiempo máximo de procesamiento
            tActivo = 0
            aux = orden.pop()
            orden.sort(key= lambda x: x.tCpu - x.tProcesado)
            iterador = 0
            while(iterador<len(orden) and aux.tCpu - aux.tProcesado >= orden[iterador].tCpu - orden[iterador].tProcesado) :
                iterador+=1   
            orden.insert(iterador-1, aux)
        orden[0].tProcesado+=1
        tActivo+=1
        orden[0].status = "x"
        for k in range(len(orden[1:])):  #se cambia el status de los procesos de acuerdo a su espera en la cola
            orden[k+1].status=str(k+1)
        printProcesos(listaProcesos)
    for p in listaProcesos:             #se buscan los procesos que lleguen en el tiempo de la iteracion 
        if(p.tLlegada == i):
            orden.append(p)
    for p in orden[1:]:                 #se agrega el tiempo de espera a los procesos que noo esten en la cabeza de la cola
        p.tEspera+=1
tiempoEspera = 0
tiempoRetorno = 0
tiermpoRNormalizado = 0


#Calculo de metricas
print "METRICAS:"
for i in listaProcesos:
    print i.nombre, ":"
    i.calcularMetricas()
    tiempoEspera += i.tEspera
    tiempoRetorno+=i.tRetorno
    tiermpoRNormalizado+=i.tRNormalizado
    print "tiempo de retorno:", i.tRetorno
    print "tiempo de retorno normalizado:", i.tRNormalizado
    print "tiempo de espera:",i.tEspera
print "PROMEDIOS: "
print "promedio retorno:", tiempoRetorno/6.0
print "promedio retorno normalizado:", tiermpoRNormalizado/6.0
print "promedio espera:", tiempoEspera/6.0
raw_input()