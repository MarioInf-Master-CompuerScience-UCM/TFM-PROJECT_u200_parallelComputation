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
        y3 = data['Opt0 execution time']
        y4 = data['Opt1 execution time']
        y5 = data['Opt2 execution time']
        y6 = data['Opt3 execution time']
        y7 = data['Opt4 execution time']
    except FileNotFoundError:
        print(f"GenarateGraphics_global_performance.py - ERROR..: File '{csv_url}' not found.")
        return

    # Define the order of the categories
    categories = ['mini', 'small', 'medium']
    #categories = ['mini', 'small', 'medium', 'large', 'extralarge']
    #categories = ['2Gb', '4Gb', '8Gb', '16Gb', '32Gb']                  #Categorias exclusivas del kernel VectorAdd

    plt.figure(figsize=(10, 6))
    plt.plot(x, y1, marker='o', label='CPU', color='red')
    plt.plot(x, y2, marker='o', label='CPU opt', color='darkred')
    plt.plot(x, y3, marker='^', label='Dispositivo Opt0 (ejec+Tras)', color='green')
    plt.plot(x, y4, marker='s', label='Dispositivo Opt1 (ejec+Tras)', color='lime')
    plt.plot(x, y5, marker='p', label='Dispositivo Opt2 (ejec+Tras)', color='mediumaquamarine')
    plt.plot(x, y6, marker='P', label='Dispositivo Opt3 (ejec+Tras)', color='cyan')
    plt.plot(x, y7, marker='*', label='Dispositivo Opt4 (ejec+Tras)', color='blue')

    #plt.title(f'Comparación de tiempos de ejecución - {os.path.basename(csv_url)}')
    plt.xlabel('Tamaño de datos de entrada (según Polybench/C)')
    #plt.xlabel('Tamaño de datos de entrada')                  #Etiqueta exclusivas del kernel VectorAdd

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
