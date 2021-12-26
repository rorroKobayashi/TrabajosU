"""
----------------Nota Acumulativa 4----------------
Autores     : -Rodrigo Kobayashi Araya
              -Pedro Figueroa Cerda
Asignatura: Sistemas Operativos
Pofesor   : Juan Cubillos G.
crear en algún lenguaje de programación a elección
simuladores de gestión de Discos aplicando dos de los siguientes tipos:
 ALGORITMO FCFS
 ALGORITMO SSTF
 ALGORITMO SCAN
 ALGORITMO CSCAN
 ALGORITMO NSCAN
 ALGORITMO CLOOK

Debe validar el ingreso de datos, mostrar una breve explicación del algoritmo y no debe
tener datos precargados.
La entrada de datos mínima es de 8 peticiones.
Debe configurar el tamaño de las pistas del disco.
--------------------------------------------------
""" 

master = True
while master:
## declaracion y reinicio de variables: 
    tamPista = 0
    pista = []
    entradas = []

    opcion = 0
    flag = True
    largoRecorrido = 0
    posCilindro = 0
    posPeticion = 0
    nPeticiones = 0

# inicio del menu
    print("para aplicar el algoritmo FCFS ingrese 1")
    print("para aplicar el algoritmo CLOOK ingrese 2")
    print("para salir ingrese 0")
    opcion = input("opcion: ")
# Validacion de entrada
    while flag:
        try:
            val = int(opcion)

        except ValueError:
            opcion = input("ingrese una opcion adecuada: ")
        opcion = int(opcion)
        if (opcion != 1 and opcion != 2 and opcion != 0):
            opcion = input("ingrese una opcion adecuada: ")
        else:
            flag = False
# check si se quiere terminar el programa
    if opcion == 0:
        master = False
    else:
# se elige el tamanno de la pista, se valida entrada        
# Validacion de entrada
        flag = True
        while flag:
            tamPista = input("ingrese el tamanno de la pista: ")
            try:
                val = int(tamPista)
            except ValueError:
                tamPista = input("ingrese una opcion adecuada: ")
            tamPista = int(tamPista)  
            if (tamPista< 1 ):
                tamPista = input("el tamanno de la pista debe ser mayor: ")            
            else:
                flag = False
# ingreso de la posicion del cabezal, se valida entrada, ademas el cabezal debe estar dentro del tamanno de la pista
# Validacion de entrada
        flag = True
        while flag:
            posCilindro = input("ingrese la posicion del cabezal: ")
            try:
                val = int(posCilindro)
                posCilindro = int(posCilindro)
                if (posCilindro < 1 or posCilindro > tamPista):
                    print("la posicion de la pista debe estar dentro del tamanno del cilindro")
                else:
                    flag = False
            except ValueError:
                posCilindro =print ("ingrese una opcion adecuada")
            
            
# Ingreso de posicion de peticiones,  se valida entrada, ademas las peticiones deben estar dentro del tamanno de la pista
# Validacion de entrada
        flag = True
        while flag:
            print("si hay mas de 8 peticiones, puede ingresar 0 para dejar de ingresar peticiones.")
            posPeticion = input("ingrese la posicion de la posicion numero "+ str(nPeticiones+1) + ": ")
            try:
                posPeticion = int(posPeticion)
                if (posPeticion == 0 and nPeticiones>=7):
                    flag = False
                elif(posPeticion < 1 or posPeticion > tamPista):
                        print("la posicion de la peticion debe estar dentro del tamanno del cilindro")
                elif(posPeticion in entradas):
                    print("la posicion de la peticion ya esta dentro de las entradas. ingrese una nueva peticion")
                if(posPeticion != 0):
                    entradas.append(posPeticion)
                    nPeticiones += 1 
            except ValueError:
                posPeticion = print("ingrese una opcion adecuada: ")
               
# Algoritmo FCFS: se calcula el recorrido tomando el valor absoluto de la posicion del cabezal
# a la primera peticion, luego se suma la distancia desde una peticion a la siguiente, hasta 
# obtener la suma de todas las distancias.
        if opcion == 1:
            print("\n\nALGORITMO FCFS: ")
            print ("Recorrido: ")
            print (entradas)
            largoRecorrido = abs(posCilindro - entradas[0])
            for i in range(1, len(entradas)):
                largoRecorrido += abs(entradas[i-1] - entradas[i])
            print("Largo recorrido: ", largoRecorrido)
        if opcion == 2:
# Algoritmo CLOOK: se ordena la lista y se comienza a calcular el recorrido sumando las distancias
# desde el cabezal a la peticion mas cercana ascendentemente, luego de la primera peticion en la list
# hasta la que antecede a la posicion del cabezal.
            print("\n\nALGORITMO CLOOK:")
            entradas.sort()
            i = 0
            
            while(entradas[i] < posCilindro and i < len(entradas)):
                i += 1
            aux = []
            for j in range(i, len(entradas)):
                aux.append(entradas[j])
            for j in range(i):
                aux.append(entradas[j])
            print("recorrido: ")
            print(aux)
            largoRecorrido = abs(posCilindro - aux[0])
            for i in range(1, len(aux)):
                largoRecorrido += abs(aux[i-1] - aux[i])
            print("Largo recorrido: ", largoRecorrido)
        print ("\n\n")
