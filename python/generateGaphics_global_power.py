#!/usr/bin/env python3

import pandas as pd
import matplotlib.pyplot as plt
import sys
import os

def generate_plot(csv_url):
    try:
        data = pd.read_csv(csv_url)
        x = data['X']
        y_cpu_energy = data['CPU energy consumption']
        y_cpu_time = data['CPU execution time']
        y_cpuOpt_energy = data['CPU optimized energy consumption']
        y_cpuOpt_time = data['CPU optimized execution time']
        y_opt0_energy = data['Opt0 energy consumption']
        y_opt0_time = data['Opt0 execution time']
        y_opt1_energy = data['Opt1 energy consumption']
        y_opt1_time = data['Opt1 execution time']
        y_opt2_energy = data['Opt2 energy consumption']
        y_opt2_time = data['Opt2 execution time']
        y_opt3_energy = data['Opt3 energy consumption']
        y_opt3_time = data['Opt3 execution time']
        y_opt4_energy = data['Opt4 energy consumption']
        y_opt4_time = data['Opt4 execution time']

    except FileNotFoundError:
        print(f"GenarateGraphics_global_power.py - ERROR..: File '{csv_url}' not found.")
        return

    # Define the order of the categories
    categories = ['mini', 'small', 'medium']
    #categories = ['mini', 'small', 'medium', 'large', 'extralarge']
    #categories = ['2Gb', '4Gb', '8Gb', '16Gb', '32Gb']                  #Categorias exclusivas del kernel VectorAdd

    plt.figure(figsize=(10, 6))
    plt.plot(x, y_cpu_energy, marker='o', label='Consumo energético de la CPU', color='red')
    plt.plot(x, y_cpuOpt_energy, marker='o', label='Consumo energético de la CPU optimizadaa', color='darkred')
    plt.plot(x, y_opt0_energy, marker='^', label='Consumo energético del dispositivo Opt0', color='orange')
    plt.plot(x, y_opt1_energy, marker='s', label='Consumo energético del dispositivo Opt1', color='gold')
    plt.plot(x, y_opt2_energy, marker='p', label='Consumo energético del dispositivo Opt2', color='yellowgreen')
    plt.plot(x, y_opt3_energy, marker='P', label='Consumo energético del dispositivo Opt3', color='lime')
    plt.plot(x, y_opt4_energy, marker='*', label='Consumo energético del dispositivo Opt4', color='green')

    #plt.title(f'Comparación de potencia consumida - {os.path.basename(csv_url)}')
    plt.xlabel('Tamaño de datos de entrada (según Polybench/C)')
    #plt.xlabel('Tamaño de datos de entrada')                  #Etiqueta exclusivas del kernel VectorAdd

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
        print("GenarateGraphics_performance.py - ERROR..: ERROR: Entry params unexpected")
        print("Usage: ./generatePictures.py <csv_url>")
        sys.exit(1)

    csv_url = sys.argv[1]

    generate_plot(csv_url)
    print("Plot generated and saved as a JPEG image.")
