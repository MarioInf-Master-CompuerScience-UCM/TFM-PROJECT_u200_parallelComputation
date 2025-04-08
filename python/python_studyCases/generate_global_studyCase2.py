#!/usr/bin/env python3

import pandas as pd
import matplotlib.pyplot as plt
import sys
import os

def format_value(x, col, df):
    if isinstance(x, (int, float)):
        x = f"{x:.2f}ms"
    if col in df.columns[-2:]:  # Las dos últimas columnas
        x = f"\t{x}"
    return x


def format_dataframe(df):
    return df.apply(lambda col: col.apply(format_value, args=(col.name, df)))


def format_value_percent(x, col, df):
    if isinstance(x, (int, float)):
        x = f"{x:.2f}\%"
    if col in df.columns[-2:]:  # Las dos últimas columnas
        x = f"\t{x}"
    return x


def format_dataframe_percent(df):
    return df.apply(lambda col: col.apply(format_value_percent, args=(col.name, df)))




def generate_plot(csv_url):
    try:
        data = pd.read_csv(csv_url)
        x = data['X']
        y1 = data['CPU execution time']
        y2 = data['CaseA execution time']
        y3 = data['CaseB execution time']
        y3 = data['CaseB execution time']
        y4 = data['CaseC execution time']
        y5 = data['CaseD execution time']
    except FileNotFoundError:
        print(f"GenarateGraphics_performance.py - ERROR..: File '{csv_url}' not found.")
        return

    # Define the order of the categories
    #categories = ['mini', 'small', 'medium', 'large', 'extralarge']
    categories = ['2Gb', '4Gb', '8Gb', '16Gb', '32Gb']                  #Categorias exclusivas del kernel VectorAdd

    plt.figure(figsize=(10, 7))
    plt.plot(x, y1, marker='o', label='Ejecución CPU', color='red')
    plt.plot(x, y2, marker='s', label='Ejecución Dispositivo (sin optimizacion)', color='lightblue')
    plt.plot(x, y3, marker='s', label='Ejecución Dispositivo (stream)', color='dodgerblue')
    plt.plot(x, y4, marker='s', label='Ejecución Dispositivo (pipeline)', color='blue')
    plt.plot(x, y5, marker='s', label='Ejecución Dispositivo (stream + pipeline)', color='darkblue')

    plt.title(f'Comparación de tiempos de ejecución - {os.path.basename(csv_url)}')
    #plt.xlabel('Tamaño de datos de entrada (según Polybench/C)')
    plt.xlabel('Tamaño de datos de entrada')                            #Etiqueta exclusivas del kernel VectorAdd

    plt.ylabel('Tiempo (ms)')
    plt.legend()
    plt.xticks(ticks=range(len(categories)), labels=categories)
    plt.yscale('log')


    image_locationTemp = csv_url + ".jpg"
    plt.savefig(image_locationTemp, format='jpg', dpi=600)
    image_locationTemp = csv_url + ".pdf"
    plt.savefig(image_locationTemp, format='pdf', dpi=600)

    plt.close()



def generateTable_data(csv_file):
    
    df=pd.DataFrame()
    dfTemp=pd.DataFrame()
    dfIni = pd.read_csv(csv_file)
    dfIni = dfIni.transpose()    


    #################################
    # Tratamiento tiempo de ejecución
    #################################
    newRow_name="CPU"
    newRow = dfIni.iloc[1]
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="Dispositivo (sin Opt)"
    newRow = dfIni.iloc[2]
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="Dispositivo (stream)"
    newRow = dfIni.iloc[3]
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="Dispositivo (pipeline)"
    newRow = dfIni.iloc[4]
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="Dispositivo (stream+pipeline)"
    newRow = dfIni.iloc[5]
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    dfTemp = format_dataframe(dfTemp)
    df = pd.concat([df, dfTemp])


    #################################
    # Tratamiento aceleraciones
    #################################
    dfTemp=pd.DataFrame()
    newEmptyRow_name = "\\textbf{{\\emph{{\\underline{{}}}}}}"
    newEmptyRow = dfIni.iloc[0].copy()
    newEmptyRow.loc[:]=""
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newEmptyRow], index=[newEmptyRow_name]) ])

    newRow_name="CPU->Dis (sin Opt)"
    newRow = ((dfIni.iloc[1]-dfIni.iloc[2])/dfIni.iloc[2])*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="CPU->Dis (stream)"
    newRow = ((dfIni.iloc[1]-dfIni.iloc[3])/dfIni.iloc[3])*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="CPU->Dis (pipeline)"
    newRow = ((dfIni.iloc[1]-dfIni.iloc[4])/dfIni.iloc[4])*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="CPU->Dis (stream+pipeline)"
    newRow = ((dfIni.iloc[1]-dfIni.iloc[5])/dfIni.iloc[5])*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    dfTemp = format_dataframe_percent(dfTemp)
    df = pd.concat([df, dfTemp])



    HeaderRow = dfIni.iloc[0].copy()
    HeaderRow.iloc[0]="Mini"
    HeaderRow.iloc[1]="Small"
    HeaderRow.iloc[2]="Medium"
    HeaderRow.iloc[3]="Large"
    HeaderRow.iloc[4]="Extralarge"
    df = pd.concat([pd.DataFrame([HeaderRow], index=[""]), df])
    #df = format_dataframe(df)



    # Crear el contenido LaTeX para la tabla con colores
    latex_table = "\\begin{table}[H]\n"
    latex_table += "    \\centering\n"
    latex_table += "    \\begin{tabular}{llllll}\n"
    
    numRow=0
    for idx, row in df.iterrows():

        if numRow == 0:
            latex_table += f"    \\rowcolor[HTML]{{DAE8FC}} \\ & "
            latex_table += " & ".join(" \\textbf{"+row+"}") + " \\\\\n"
        elif numRow%2 != 0:
            latex_table += f"    \\cellcolor[HTML]{{DAE8FC}} \\textbf{{{idx}}} & "
            latex_table += " & ".join(row) + " \\\\\n"
        else:
            latex_table += f"    \\rowcolor[HTML]{{EFEFEF}} \cellcolor[HTML]{{DAE8FC}} \\textbf{{{idx}}} & "
            latex_table += " & ".join(row) + " \\\\\n"

        numRow+=1

    nameFile = ultimo_elemento = csv_file.split("/")[-1]
    nameFile_parts=nameFile.split("_")


    latex_table += "    \\end{tabular}\n"
    latex_table += f"    \\caption[Resultados de rendimiento Caso de estudio 1]{{Resultados de rendimiento Caso de estudio 1. Fuente: Creación propia}}\n"
    latex_table += f"    \\label{{table_{os.path.splitext(os.path.basename(csv_file))[0]}}}\n"
    latex_table += "\\end{table}"

    # Crear el nombre del archivo de salida .tex
    output_tex_file = f"{csv_file}.tex"

    # Escribir el contenido LaTeX en un archivo
    with open(output_tex_file, 'w') as f:
        f.write(latex_table)





if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("GenarateGraphics_performance.py - ERROR..: ERROR: Entry params unexpected")
        print("Usage: ./generatePictures.py <csv_url>")
        sys.exit(1)

    csv_url = sys.argv[1]

    generate_plot(csv_url)
    print("Plot generated and saved as a JPEG image.")
    generateTable_data(csv_url)
    print("Data tagble generated and save as TEX file.")
