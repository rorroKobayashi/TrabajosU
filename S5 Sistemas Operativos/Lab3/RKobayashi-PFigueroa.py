"""
----------------Nota Acumulativa 3----------------
Autores     : Rodrigo Kobayashi Araya
              Pedro Figueroa Cerda
Rut       : 18953714-k
Asignatura: Sistemas Operativos
Pofesor   : Juan Cubillos G.
Crear en algun lenguaje de programación un 
simulador de gestion de memoria usando Paginacion.

    -La simulación debe mostrar paso a paso el uso 
     de la memoria y la carga de las diferentes 
     tablas que usa la gestion. 
    
    -Debe validar el ingreso de la 
     informacion.

    -Se debe poder iniciar y terminar mínimo con 8
     procesos con tamannos de paginas variables de 
     1 a 6.

    -El marco de pagina debe tener 7 fragmentos

    -Se debe mostrar procesos en espera y en 
     ejecución
--------------------------------------------------
""" 

# Se crean variables globales:
nProcesos = 1
marcoPagina = [0]*7
paginasUsadas = 0
activos = []
enEspera = []
finalizados = []
master = True

#comienza la selección de opciones
while master:
    print ("0 = pagina libre")
    print ("los procesos son de la forma [nombre, tamanno]")
    print ("Marco de Página       : " , marcoPagina )
    print ("Procesos Activos      : " , activos )
    print ("Procesos en espera    : " , enEspera )
    print ("Procesos finalizados  : " , finalizados )
    print ("Paginas ocupadas      : " , paginasUsadas )
    print ("\n")
    print ("para ingresar procesos ingrese 1.")
    print ("para finalizar procesos ingrese 2.")
    print ("para restablecer listas ingrese 3.")
    print ("para salir ingrese 0.")
    opcion = input("opcion: ")
    # validacion de ingreso de informacion
    flag = True
    while flag:
        try:
            val = int(opcion)

        except ValueError:
            opcion = input("ingrese una opcion adecuada: ")
        opcion = int(opcion)
        if (opcion != 1 and opcion != 2 and opcion != 3 and opcion != 0):
            opcion = input("ingrese una opcion adecuada: ")
        else:
            flag = False
    
    # se restablecen todas las listas
    if opcion == 3:
        nProcesos = 1
        marcoPagina = [0]*7
        paginasUsadas = 0
        activos = []
        enEspera = []
        finalizados = []

    # ingreso de procesos al simulador
    if opcion == 1:
        largoProceso = input("ingrese el tamanno del proceso: ")
        # validacion de ingreso de informacion
        flag = True
        while flag:
            try:
                val = int(largoProceso)
            except ValueError:
                largoProceso = input("ingrese una opcion adecuada: ")
            largoProceso = int(largoProceso)  
            if (largoProceso< 1 or largoProceso > 6):
                largoProceso = input("el tamanno del proceso debe ser entre 1 y 6: ")            
            else:
                flag = False   
        #ingreso del proceso a la lista de espera
        if ((paginasUsadas + largoProceso) > 7):
            print ("el proceso ", nProcesos , " entra a la lista de espera.")
            enEspera.append([nProcesos , largoProceso])
        #ingreso del proceso a procesos activos
        else:
            print ("el proceso ", nProcesos, "entra a los procesos activos, se usan ", largoProceso, "paginas.")
            activos.append([nProcesos, largoProceso])
            temp = largoProceso
            for i in range(7):
                if(temp > 0):
                    if(marcoPagina[i] == 0):
                        marcoPagina[i] = nProcesos
                        temp -= 1
            paginasUsadas = paginasUsadas + largoProceso  
        nProcesos += 1  
    # eliminacion de procesos
    if opcion == 2:
        # verificacion de existencia de procesos activos
        if (activos == []):
            print("no hay procesos para finalizar.")
        else:
            procesoFinalizado = input ("ingrese el numero del proceso a finalizar: ")
            # validacion de ingreso de informacion
            flag = True
            while flag:
                try:
                    val = int(procesoFinalizado)
                except ValueError:
                    procesoFinalizado = input("ingrese una opcion adecuada: ")
                procesoFinalizado = int(procesoFinalizado)
                flag2 = True
                for i in activos:
                    if i[0] == procesoFinalizado:
                        flag2 = False
                if flag2:
                    procesoFinalizado = input("el numero de proceso no esta en los procesos activos, ingrese un numero de proceso:")
                else:
                    flag = False
            # se busca el proceso en la lista de los procesos activos
            for i in range(len(activos)):
                if activos[i][0] == procesoFinalizado:
                    finalizados.append(activos[i])
                    memoriaLiberada = activos[i][1]
                    eliminar = i
            del activos[eliminar]
            # se liberan las paginas que usaba el proceso para su ejecucion
            for i in range(7):
                if marcoPagina[i] == procesoFinalizado:
                    marcoPagina[i] = 0
            # se restan las paginas liberadas al total de paginas usadas
            paginasUsadas = paginasUsadas - memoriaLiberada
            print ("se finaliza el proceso " , procesoFinalizado , ", se liberan " , memoriaLiberada, " paginas.")
            
            # se verifica si hay procesos en espera que son aptos para entrar a los procesos activos
            while (len(enEspera) != 0 and enEspera[0][1] + paginasUsadas <7 ):
                print("el proceso " , enEspera[0][0] , "entra a los procesos activos, se usan ", enEspera[0][1], "paginas.")
                activos.append(enEspera[0])
                paginasUsadas = paginasUsadas + enEspera[0][1]
                temp = enEspera[0][1]
                for i in range(7):
                    if (temp>0 and marcoPagina[i] == 0):
                        marcoPagina[i] = enEspera[0][0]
                        temp -=1
                del enEspera[0]
            if (len(enEspera) == 0):
                print("no hay procesos en espera.")
            elif ((enEspera[0][1] + paginasUsadas) > 7):
                    print ("no hay memoria suficiente para activar el proceso " , enEspera[0][0])
                
    #finalizacion del simulador
    if (opcion == 0):
        master = False
    print ("\n\n")
temp = input("finalizado.")


                
