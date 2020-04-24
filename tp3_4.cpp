#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* TiposProductos[] = {"Galletas", "Snack", "Cigarrillos", "Caramelos", "Bebidas"};

typedef struct {
    int ProductoID;         //Numerado en ciclo iterativo
    int Cantidad;           //Entre 1 y 10
    char* TipoProducto;     //Algun valor del arreglo TiposProductos
    float PrecioUnitario;   //Entre 10 y 100
} Producto;

typedef struct {
    int ClienteID;                  //Numerado en ciclo iterativo
    char* NombreCliente;            //Ingresado por usuario
    int CantidadProductosAPedir;    //Aleatorio entre 1 y 5
    Producto* Productos;            //El tamanio de este arreglo depende de la variable "CantdidadProductosAPedir"
} Cliente;

void CargarClientes(Cliente* clientes, int cantidad);
void GenerarProductos(Producto* productos, int cantidad);
float CostoTotalPorProducto(Producto producto);
void MostrarClientes(Cliente* clientes, int cantidad);

int main()
{
    int cantidad_clientes;
    Cliente* clientes;

    do
    {
        system("cls");
        printf("Ingrese cantidad de clientes (entre 1 y 5): ");
        scanf("%d", &cantidad_clientes);
    }
    while (cantidad_clientes <= 0 || cantidad_clientes > 5);

    clientes = (Cliente*) malloc(cantidad_clientes * sizeof(Cliente));

    CargarClientes(clientes, cantidad_clientes);

    MostrarClientes(clientes, cantidad_clientes);
    
    getchar();
    system("PAUSE");
    return 0;
}

void CargarClientes(Cliente* clientes, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        char nombre[15];

        (clientes + i)->ClienteID = i+1;

        printf("Ingrese el nombre del cliente: ");
        scanf("%s", nombre);
        (clientes + i)->NombreCliente = (char*) malloc(strlen(nombre) * sizeof(char));
        strcpy((clientes + i)->NombreCliente, nombre);

        //printf("Ingrese la cantidad de productos a pedir: ");
        //scanf("%d", (clientes + i)->CantidadProductosAPedir);
        (clientes + i)->CantidadProductosAPedir = rand() % 10 + 1;

        (clientes + i)->Productos = (Producto*) malloc((clientes + i)->CantidadProductosAPedir * sizeof(Producto));
        GenerarProductos((clientes + i)->Productos, (clientes + i)->CantidadProductosAPedir);
    }
}

void GenerarProductos(Producto* productos, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        (productos + i)->ProductoID = i+1;
        (productos + i)->Cantidad = rand() % 10 + 1;
        //(productos + i)->TipoProducto =

        int numRand = rand() % 5;
        (productos + i)->TipoProducto = (char*) malloc(strlen(TiposProductos[numRand]) * sizeof(char));
        strcpy((productos + i)->TipoProducto, TiposProductos[numRand]);

        (productos + i)->PrecioUnitario = rand() % 100 + 10;
    }
}

float CostoTotalPorProducto(Producto producto)
{
    return producto.Cantidad * producto.PrecioUnitario;
}

void MostrarClientes(Cliente* clientes, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        printf("\n/////////////////////////////////////////////////////\n");

        printf("\nID de cliente: %d\n", (clientes + i)->ClienteID);
        printf("Nombre: %s\n", (clientes + i)->NombreCliente);

        printf("Cantidad de productos: %d\n\n", (clientes + i)->CantidadProductosAPedir);

        float sumaTotal = 0;

        for (int j = 0; j < (clientes + i)->CantidadProductosAPedir; j++)
        {
            printf("ID de producto: %d\n", (clientes + i)->Productos[j].ProductoID);
            printf("Cantidad de producto: %d\n", (clientes + i)->Productos[j].Cantidad);
            printf("Tipo de producto: %s\n", (clientes + i)->Productos[j].TipoProducto);
            printf("Precio de producto: $%.2f\n", (clientes + i)->Productos[j].PrecioUnitario);

            float costoDeProducto = CostoTotalPorProducto( (clientes + i)->Productos[j]);
            printf("Costo total del producto: $%.2f\n\n",  costoDeProducto);
            sumaTotal += costoDeProducto;
        }
        
        printf("Total a pagar del cliente: $%.2f\n\n",  sumaTotal);
    }
}