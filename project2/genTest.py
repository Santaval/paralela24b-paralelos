import random

def generar_datos_particulas(n, archivo_salida="particulas.tsv"):
    """
    Genera un archivo TSV con datos de partículas en el espacio.

    Args:
        n (int): Cantidad de partículas a generar.
        archivo_salida (str): Nombre del archivo de salida.
    """
    with open(archivo_salida, "w") as archivo:
        archivo.write("masa\tradio\tx\ty\tz\tvx\tvy\tvz\n")  # Encabezado del archivo
        for _ in range(n):
            masa = random.randint(1, 100000)  # Masa entre 1 y 10000
            radio = random.randint(1, 5000)   # Radio entre 1 y 50
            x, y, z = (random.uniform(-10000, 10000) for _ in range(3))  # Posición entre -1000 y 1000
            vx, vy, vz = (random.uniform(-1, 1) for _ in range(3))  # Velocidad entre -100 y 100
            archivo.write(f"{masa}\t{radio}\t{x:.2f}\t{y:.2f}\t{z:.2f}\t{vx:.2f}\t{vy:.2f}\t{vz:.2f}\n")

if __name__ == "__main__":
    n = int(input("¿Cuántas partículas deseas generar? "))
    archivo_salida = input("Nombre del archivo de salida (default: particulas.tsv): ") or "particulas.tsv"
    generar_datos_particulas(n, archivo_salida)
    print(f"Se generaron {n} partículas en el archivo '{archivo_salida}'.")
