#!/usr/bin/env python3

import pandas as pd
import matplotlib.pyplot as plt
import sys
import os

def generate_plot(csv_url):
    try:
        data = pd.read_csv(csv_url)
        x = data['X']
        y1 = data['CPU execution time']
        y2 = data['CPU optimized execution time']
        y3 = data['Device execution time']
        y4 = data['Transmision (S+R) time']
        y5 = data['Send to device time']
        y6 = data['Recieve from device time']
    except FileNotFoundError:
        print(f"GenarateGraphics_performance.py - ERROR..: File '{csv_url}' not found.")
        return

    # Define the order of the categories
    categories = ['mini', 'small', 'medium']
    #categories = ['mini', 'small', 'medium', 'large', 'extralarge']
    #categories = ['2Gb', '4Gb', '8Gb', '16Gb', '32Gb']                  #Categorias exclusivas del kernel VectorAdd

    plt.figure(figsize=(10, 6))
    plt.plot(x, y1, marker='o', label='Ejecucion de la CPU', color='red')
    plt.plot(x, y2, marker='^', label='Ejecución de la CPU optimizada', color='darkred')
    plt.plot(x, y3, marker='s', label='Ejecución del dispositivo', color='blue')
    plt.plot(x, y4, marker='p', label='Transmisión y recepción de datos al dispositivo', color='aquamarine')

    #plt.title(f'Comparación de tiempos de ejecución - {os.path.basename(csv_url)}')
    plt.xlabel('Tamaño de datos de entrada (según Polybench/C)')
    #plt.xlabel('Tamaño de datos de entrada')                            #Etiqueta exclusivas del kernel VectorAdd

    plt.ylabel('Tiempo (ms)')
    plt.legend()
    plt.xticks(ticks=range(len(categories)), labels=categories)
    plt.yscale('log')

    image_locationTemp = csv_url + ".jpg"
    plt.savefig(image_locationTemp, format='jpg', dpi=600, bbox_inches='tight')
    image_locationTemp = csv_url + ".pdf"
    plt.savefig(image_locationTemp, format='pdf', dpi=600, bbox_inches='tight')

    plt.close()

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("GenarateGraphics_performance.py - ERROR..: ERROR: Entry params unexpected")
        print("Usage: ./generatePictures.py <csv_url>")
        sys.exit(1)

    csv_url = sys.argv[1]

    generate_plot(csv_url)
    print("Plot generated and saved as a JPEG image.")
