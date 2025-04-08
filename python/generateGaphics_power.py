#!/usr/bin/env python3

import pandas as pd
import matplotlib.pyplot as plt
import sys
import os

def generate_plot(csv_url):
    try:
        data = pd.read_csv(csv_url)
        x = data['X']
        y1 = data['Device energy consumption']
        y2 = data['Device execution time']
        y3 = data['CPU energy consumption']
        y4 = data['CPU execution time']
        y5 = data['CPU optimized energy consumption']
        y6 = data['CPU optimized execution time']
        y7 = data['CPU-1']
        y8 = data['CPU-2']
    except FileNotFoundError:
        print(f"GenarateGraphics_power.py - ERROR..: File '{csv_url}' not found.")
        return

    # Define the order of the categories
    categories = ['mini', 'small', 'medium']
    #categories = ['mini', 'small', 'medium', 'large', 'extralarge']
    #categories = ['2Gb', '4Gb', '8Gb', '16Gb', '32Gb']                  #Categorias exclusivas del kernel VectorAdd

    plt.figure(figsize=(10, 6))
    plt.plot(x, y1, marker='o', label='Consumo energético del dispositivo', color='green')
    plt.plot(x, y3, marker='^', label='Consumo energético de la CPU', color='orange')
    plt.plot(x, y5, marker='s', label='Consumo energético de la CPU optimizada', color='orangered')


    #plt.title(f'Comparación de potencia consumida - {os.path.basename(csv_url)}')
    plt.xlabel('Tamaño de datos de entrada (según Polybench/C)')
    #plt.xlabel('Tamaño de datos de entrada')                          #Etiqueta exclusivas del kernel VectorAdd

    plt.ylabel('Potencia (Vatios)')
    plt.legend()
    plt.xticks(ticks=range(len(categories)), labels=categories)


    image_locationTemp = csv_url + ".jpg"
    plt.savefig(image_locationTemp, format='jpg', dpi=600, bbox_inches='tight')
    image_locationTemp = csv_url + ".pdf"
    plt.savefig(image_locationTemp, format='pdf', dpi=600, bbox_inches='tight')

    plt.close()

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("GenarateGraphics_power.py - ERROR..: Entry params unexpected")
        print("Usage: ./generatePictures.py <csv_url>")
        sys.exit(1)

    csv_url = sys.argv[1]

    generate_plot(csv_url)
    print("Plot generated and saved as a JPEG image.")
