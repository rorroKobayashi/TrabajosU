/* Crear Tabla Fecha */
CREATE TABLE Fecha(
    IDF varchar(8) NOT NULL,
    Dia_Semana varchar(1) NOT NULL,
    Semana Varchar(2) NOT NULL,
    Mes varchar(2) NOT NULL,
    Annio varchar(4) NOT NULL 
);

/* Crear Tabla Cliente */
CREATE TABLE Cliente (
	Rut varchar(12) NOT NULL,
	Nombre_Razon_Social varchar(50) NOT NULL
);

/* Crear Tabla Producto */
CREATE TABLE Producto (
    IDP varchar(6) NOT NULL,
    Nombre varchar(50) NOT NULL,
    Precio double NOT NULL
);

/* Crear Tabla Ventas*/
CREATE TABLE Ventas (
    IDFecha varchar (8) NOT NULL,
    Rut_Cliente varchar(12) NOT NULL,
    IDP varchar(6) NOT NULL,
    Ingreso double NOT NULL,
    Descuento float NOT NULL,
    Cantidad double NOT NULL
);

/*Creación de Claves primarias*/

ALTER TABLE Cliente ADD PRIMARY KEY (Rut);
ALTER TABLE Fecha ADD PRIMARY KEY (IDF);
ALTER TABLE Producto ADD PRIMARY KEY (IDP);
ALTER TABLE Ventas ADD PRIMARY KEY (Rut_Cliente, IDFecha, IDP);

/* Creación de claves foráneas*/

ALTER TABLE Ventas ADD FOREIGN KEY (Rut_Cliente) REFERENCES Cliente(Rut);
ALTER TABLE Ventas ADD FOREIGN KEY (IDFecha) REFERENCES Fecha(IDF);
ALTER TABLE Ventas ADD FOREIGN KEY (IDP) REFERENCES Producto(IDP);