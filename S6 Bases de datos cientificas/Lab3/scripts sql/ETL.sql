/*-----------------------------------------------------------*/
/*----------------------EXTRACCION---------------------------*/
/*-----------------------------------------------------------*/

    /* --------tablas de fechas transicionales ----------*/
       /*Se extraen las fechas desde las bases de datos*/
CREATE TABLE Comercio_fechas AS
select DISTINCT factura.fecha as fecha from BDR_comercio.factura;

CREATE TABLE Restaurant_fechas AS
select DISTINCT cuenta.fecha as fecha from BDR_restaurant.cuenta



/* -----------tablas de clientes transicionales ---------------*/

/*se extraen los clientes desde las bases de datos*/
CREATE TABLE comercio_clientes AS
SELECT rut, rs as razon_social from BDR_comercio.cliente

CREATE TABLE Restaurant_clientes AS
SELECT DISTINCT rutcli, nomcli from BDR_restaurant.cuenta


/* -----------tablas de  productos transicionales -------------------*/

/*se extraen los productos desde las bases de datos*/
CREATE TABLE Comercio_productos AS
SELECT DISTINCT producto.id as IDP, producto.nom as Nombre, 
producto.valor as Precio
FROM BDR_comercio.producto;

CREATE TABLE Restaurant_productos AS
SELECT DISTINCT producto.idp as IDP, producto.nom as Nombre, 
producto.precio as Precio
FROM BDR_restaurant.producto;



/*---------------------tablas de Ventas------------------------------*/
CREATE TABLE Comercio_Ventas AS
SELECT factura.fecha as IDFecha, 
cliente.rut as Rut_Cliente, 
producto.id as IDP, 
SUM(detalle.cantidad * producto.valor) as Ingreso,
AVG(detalle.descuento) as Descuento, 
SUM(detalle.cantidad) as Cantidad
FROM BDR_comercio.cliente, BDR_comercio.factura, BDR_comercio.detalle,
BDR_comercio.producto
WHERE
cliente.rut = factura.idc AND
factura.nfac = detalle.nfac AND
detalle.idp = producto.id 
GROUP BY IDFecha, Rut_Cliente, IDP

CREATE TABLE Restaurant_Ventas AS
SELECT cuenta.fecha as IDFecha, 
cuenta.rutcli as Rut_Cliente, 
producto.idp as IDP, 
SUM(incluye.cant * producto.precio) as Ingreso,
AVG(cuenta.descuento) as Descuento, 
SUM(incluye.cant) as Cantidad
FROM BDR_restaurant.cuenta, BDR_restaurant.incluye, BDR_restaurant.producto
WHERE
incluye.idc = cuenta.idc AND
producto.idp = incluye.idp
GROUP BY IDFecha, Rut_Cliente, IDP
/*-----------------------------------------------------------*/
/*----------------------TRANSFORMACION-----------------------*/
/*-----------------------------------------------------------*/


/* Se modifica el tipo de dato de las fechas de restaurant a varchar: */
ALTER TABLE Restaurant_fechas 
ALTER COLUMN fecha varchar(8)


/* Se modifica el tipo de dato de rut para calzar a varchar(12) y nombre para 
calzar a varchar(50) */

ALTER TABLE comercio_clientes
MODIFY COLUMN rut varchar(12);

ALTER TABLE comercio_clientes
MODIFY COLUMN razon_social varchar(50);

ALTER TABLE Restaurant_clientes
MODIFY COLUMN rutcli varchar(12);

ALTER TABLE Restaurant_clientes
MODIFY COLUMN nomcli varchar(50);

/* Se modifica el tipo de dato de IDP para calzar a varchar(6), Nombre para
 calzar a varchar(50) y Cantidad para calzar a double */

ALTER TABLE Restaurant_productos
MODIFY COLUMN IDP varchar(6);

ALTER TABLE Restaurant_productos
MODIFY COLUMN Nombre varchar(50);

ALTER TABLE Comercio_productos
MODIFY COLUMN IDP varchar(6);


/*se modifican las columnas de rut del cliente, ID del producto y cantidad 
vendida de la tabla Comercio_Ventas para calzar con la tabla Ventas*/
ALTER TABLE Comercio_Ventas 
MODIFY COLUMN Rut_Cliente varchar(12);

ALTER TABLE Comercio_Ventas 
MODIFY COLUMN IDP varchar(6);

ALTER TABLE Comercio_Ventas 
MODIFY COLUMN Descuento float;

ALTER TABLE Comercio_Ventas 
MODIFY COLUMN Cantidad double;
/*se modifican las columnas de ID de fecha, Rut del cliente y ID del producto
 de la tabla Restaurant_Ventas para calzar con la tabla Ventas*/
ALTER TABLE Restaurant_Ventas 
MODIFY COLUMN IDFecha varchar(8);

ALTER TABLE Restaurant_Ventas 
MODIFY COLUMN Rut_Cliente varchar(12);

ALTER TABLE Restaurant_Ventas 
MODIFY COLUMN IDP varchar(6);

/*-----------------------------------------------------------*/
/*---------------------------CARGA---------------------------*/
/*-----------------------------------------------------------*/


/*METODOS PARA OBTENER COLUMNAS ADICIONALES DE FECHA */

                /* DIA DE LA SEMANA */
SELECT DAYOFWEEK(fecha) from Comercio_fechas

                    /*SEMANA*/
SELECT WEEKOFYEAR(fecha) from Comercio_fechas

                     /*MES*/
SELECT SUBSTR(fecha, 5, 2) from Comercio_fechas

                     /*AÑO*/
SELECT SUBSTR(fecha, 1, 4) from Comercio_fechas

/*Carga de Fechas*/

INSERT INTO Fecha (IDF, Dia_semana, Semana, Mes, Annio)
SELECT fecha, 
DAYOFWEEK(fecha), 
WEEKOFYEAR(fecha), 
SUBSTR(fecha, 5, 2), 
SUBSTR(fecha, 1, 4)
FROM Comercio_fechas

INSERT INTO Fecha (IDF, Dia_semana, Semana, Mes, Annio)
SELECT fecha, 
DAYOFWEEK(fecha), 
WEEKOFYEAR(fecha), 
SUBSTR(fecha, 5, 2), 
SUBSTR(fecha, 1, 4)
FROM Restaurant_fechas

/*se testea que no existan datos repetidos*/
SELECT IDF, count(IDF) 
FROM Fecha 
GROUP BY IDF  
ORDER BY count(IDF)  DESC

/*carga de fechas*/
INSERT INTO Cliente (Rut, Nombre_Razon_Social)
SELECT rut, razon_social from comercio_clientes;

INSERT INTO Cliente (Rut, Nombre_Razon_Social)
SELECT rutcli, nomcli from Restaurant_clientes;

/*carga de productos*/
INSERT INTO Producto (IDP, Nombre, Precio)
SELECT IDP, Nombre, Precio FROM Comercio_productos;

INSERT INTO Producto (IDP, Nombre, Precio)
SELECT IDP, Nombre, Precio FROM Restaurant_productos;

/*Carga de Ventas*/
INSERT INTO Ventas (IDFecha, Rut_Cliente, IDP, Ingreso, Descuento, Cantidad)
SELECT IDFecha, Rut_Cliente, IDP, Ingreso, Descuento, Cantidad
from Comercio_Ventas;

INSERT INTO Ventas (IDFecha, Rut_Cliente, IDP, Ingreso, Descuento, Cantidad)
SELECT IDFecha, Rut_Cliente, IDP, Ingreso, Descuento, Cantidad
from Restaurant_Ventas;





