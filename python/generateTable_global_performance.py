import pandas as pd
import numpy as np
import os
import sys

# Diccionario para traducir los valores de la primera columna
translation_dict = {
    "CPU execution time"  : "CPU",
    "CPU optimized execution time"  : "CPU Opt",
    "Opt0 execution time" : "Opt0",
    "Opt1 execution time" : "Opt1",
    "Opt2 execution time" : "Opt2",
    "Opt3 execution time" : "Opt3",
    "Opt4 execution time" : "Opt4"
}


def calculate_differences(row, elementIdx):
    element = row.iloc[elementIdx]
    return ((row - element)/element)*100


def format_value_percent(x, col, df):
    if isinstance(x, (int, float)):
        x = f"{x:.2f}\%"
    if col in df.columns[-2:]:  # Las dos últimas columnas
        x = f"\t{x}"
    return x


def format_dataframe_percent(df):
    return df.apply(lambda col: col.apply(format_value_percent, args=(col.name, df)))


def format_value(x, col, df):
    if isinstance(x, (int, float)):
        x = f"{x:.2f}"
    if col in df.columns[-2:]:  # Las dos últimas columnas
        x = f"\t{x}"
    return x


def format_dataframe(df):
    return df.apply(lambda col: col.apply(format_value, args=(col.name, df)))





def generateSpeedupTable(csv_file):

    df_ini = pd.read_csv(csv_file)
    df=pd.DataFrame()
    dfTemp=pd.DataFrame()



    #################################
    # Tratamiento de datos Mini
    #################################
    newRow_name="->CPU"
    newRow = df_ini.iloc[0, 1:]
    accelerator = df_ini.iloc[0, 1]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->CPU Opt"
    newRow = df_ini.iloc[0, 1:]
    accelerator = df_ini.iloc[0, 2]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt0"
    newRow = df_ini.iloc[0, 1:]
    accelerator = df_ini.iloc[0, 3]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt1"
    newRow = df_ini.iloc[0, 1:]
    accelerator = df_ini.iloc[0, 4]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt2"
    newRow = df_ini.iloc[0, 1:]
    accelerator = df_ini.iloc[0, 5]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt3"
    newRow = df_ini.iloc[0, 1:]
    accelerator = df_ini.iloc[0, 6]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt4"
    newRow = df_ini.iloc[0, 1:]
    accelerator = df_ini.iloc[0, 7]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])
    
    dfTemp = format_dataframe_percent(dfTemp)
    dfTemp = dfTemp.astype(object)
    for i in range(len(dfTemp)):
        for j in range(i+1, len(dfTemp)):
            dfTemp.iat[i, j] = '-'

    newEmptyRow_name = "\\textbf{{\\emph{{\\underline{{Mini}}}}}}"
    newEmptyRow = df_ini.iloc[0, 1:].copy()
    newEmptyRow.loc[:]=""
    df = pd.concat([df, pd.DataFrame([newEmptyRow], index=[newEmptyRow_name])])
    df = pd.concat([df, dfTemp])



    #################################
    # Tratamiento de datos Small
    #################################
    dfTemp=pd.DataFrame()
    newRow_name="->CPU"
    newRow = df_ini.iloc[1, 1:]
    accelerator = df_ini.iloc[1, 1]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->CPU Opt"
    newRow = df_ini.iloc[1, 1:]
    accelerator = df_ini.iloc[1, 2]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt0"
    newRow = df_ini.iloc[1, 1:]
    accelerator = df_ini.iloc[1, 3]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt1"
    newRow = df_ini.iloc[1, 1:]
    accelerator = df_ini.iloc[1, 4]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt2"
    newRow = df_ini.iloc[1, 1:]
    accelerator = df_ini.iloc[1, 5]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt3"
    newRow = df_ini.iloc[1, 1:]
    accelerator = df_ini.iloc[1, 6]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt4"
    newRow = df_ini.iloc[1, 1:]
    accelerator = df_ini.iloc[1, 7]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])
    
    dfTemp = format_dataframe_percent(dfTemp)
    dfTemp = dfTemp.astype(object)
    for i in range(len(dfTemp)):
        for j in range(i+1, len(dfTemp)):
            dfTemp.iat[i, j] = '-'

    newEmptyRow_name = "\\textbf{{\\emph{{\\underline{{Small}}}}}}"
    newEmptyRow = df_ini.iloc[0, 1:].copy()
    newEmptyRow.loc[:]=""
    df = pd.concat([df, pd.DataFrame([newEmptyRow], index=[newEmptyRow_name])])
    df = pd.concat([df, dfTemp])



    #################################
    # Tratamiento de datos Medium
    #################################
    dfTemp=pd.DataFrame()
    newRow_name="->CPU"
    newRow = df_ini.iloc[2, 1:]
    accelerator = df_ini.iloc[2, 1]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->CPU Opt"
    newRow = df_ini.iloc[2, 1:]
    accelerator = df_ini.iloc[2, 2]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt0"
    newRow = df_ini.iloc[2, 1:]
    accelerator = df_ini.iloc[2, 3]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt1"
    newRow = df_ini.iloc[2, 1:]
    accelerator = df_ini.iloc[2, 4]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt2"
    newRow = df_ini.iloc[2, 1:]
    accelerator = df_ini.iloc[2, 5]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt3"
    newRow = df_ini.iloc[2, 1:]
    accelerator = df_ini.iloc[2, 6]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt4"
    newRow = df_ini.iloc[2, 1:]
    accelerator = df_ini.iloc[2, 7]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])
    
    dfTemp = format_dataframe_percent(dfTemp)
    dfTemp = dfTemp.astype(object)
    for i in range(len(dfTemp)):
        for j in range(i+1, len(dfTemp)):
            dfTemp.iat[i, j] = '-'

    newEmptyRow_name = "\\textbf{{\\emph{{\\underline{{Medium}}}}}}"
    newEmptyRow = df_ini.iloc[0, 1:].copy()
    newEmptyRow.loc[:]=""
    df = pd.concat([df, pd.DataFrame([newEmptyRow], index=[newEmptyRow_name])])
    df = pd.concat([df, dfTemp])



    #################################
    # Tratamiento de datos Large
    #################################
    dfTemp=pd.DataFrame()
    newRow_name="->CPU"
    newRow = df_ini.iloc[3, 1:]
    accelerator = df_ini.iloc[3, 1]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->CPU Opt"
    newRow = df_ini.iloc[3, 1:]
    accelerator = df_ini.iloc[3, 3]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt0"
    newRow = df_ini.iloc[3, 1:]
    accelerator = df_ini.iloc[3, 2]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt1"
    newRow = df_ini.iloc[3, 1:]
    accelerator = df_ini.iloc[3, 4]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt2"
    newRow = df_ini.iloc[3, 1:]
    accelerator = df_ini.iloc[3, 5]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt3"
    newRow = df_ini.iloc[3, 1:]
    accelerator = df_ini.iloc[3, 6]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt4"
    newRow = df_ini.iloc[3, 1:]
    accelerator = df_ini.iloc[3, 7]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])
    
    dfTemp = format_dataframe_percent(dfTemp)
    dfTemp = dfTemp.astype(object)
    for i in range(len(dfTemp)):
        for j in range(i+1, len(dfTemp)):
            dfTemp.iat[i, j] = '-'

    newEmptyRow_name = "\\textbf{{\\emph{{\\underline{{Large}}}}}}"
    newEmptyRow = df_ini.iloc[0, 1:].copy()
    newEmptyRow.loc[:]=""
    df = pd.concat([df, pd.DataFrame([newEmptyRow], index=[newEmptyRow_name])])
    df = pd.concat([df, dfTemp])



    #################################
    # Tratamiento de datos Extralarge
    #################################
    dfTemp=pd.DataFrame()
    newRow_name="->CPU"
    newRow = df_ini.iloc[4, 1:]
    accelerator = df_ini.iloc[4, 1]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->CPU Opt"
    newRow = df_ini.iloc[4, 1:]
    accelerator = df_ini.iloc[4, 2]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt0"
    newRow = df_ini.iloc[4, 1:]
    accelerator = df_ini.iloc[4, 3]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt1"
    newRow = df_ini.iloc[4, 1:]
    accelerator = df_ini.iloc[4, 4]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt2"
    newRow = df_ini.iloc[4, 1:]
    accelerator = df_ini.iloc[4, 5]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt3"
    newRow = df_ini.iloc[4, 1:]
    accelerator = df_ini.iloc[4, 6]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name="->Opt4"
    newRow = df_ini.iloc[4, 1:]
    accelerator = df_ini.iloc[4, 7]
    newRow = ((newRow-accelerator)/accelerator)*100
    dfTemp = pd.concat([dfTemp, pd.DataFrame([newRow], index=[newRow_name])])
    
    dfTemp = format_dataframe_percent(dfTemp)
    dfTemp = dfTemp.astype(object)
    for i in range(len(dfTemp)):
        for j in range(i+1, len(dfTemp)):
            dfTemp.iat[i, j] = '-'

    newEmptyRow_name = "\\textbf{{\\emph{{\\underline{{Extralarge}}}}}}"
    newEmptyRow = df_ini.iloc[0, 1:].copy()
    newEmptyRow.loc[:]=""
    df = pd.concat([df, pd.DataFrame([newEmptyRow], index=[newEmptyRow_name])])
    df = pd.concat([df, dfTemp])



    #################################
    # Creando tabla en LaTex
    #################################
    HeaderRow = df_ini.iloc[0, 1:].copy()
    HeaderRow.iloc[0]="CPU"
    HeaderRow.iloc[1]="CPU Opt"
    HeaderRow.iloc[2]="Opt0"
    HeaderRow.iloc[3]="Opt1"
    HeaderRow.iloc[4]="Opt2"
    HeaderRow.iloc[5]="Opt3"
    HeaderRow.iloc[6]="Opt4"
    df = pd.concat([pd.DataFrame([HeaderRow], index=[""]), df])


    # Crear el contenido LaTeX para la tabla con colores
    latex_table = "\\begin{table}[H]\n"
    latex_table += "    \\centering\n"
    latex_table += "    \\begin{tabular}{llllllll}\n"
    
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
    latex_table += f"    \\caption[Resultados generales de rendimiento "+nameFile_parts[1]+"]{{Resultados generales de rendimiento "+nameFile_parts[1]+". Fuente: Creación propia}}\n"
    latex_table += f"    \\label{{table_{os.path.splitext(os.path.basename(csv_file))[0]}_speedup}}\n"
    latex_table += "\\end{table}"

    # Crear el nombre del archivo de salida .tex
    output_tex_file = f"{csv_file}_speedup.tex"

    # Escribir el contenido LaTeX en un archivo
    with open(output_tex_file, 'w') as f:
        f.write(latex_table)





def generateDataTable(csv_file):
    df = pd.read_csv(csv_file)
    df = df.transpose()    
    df.columns = df.iloc[0]
    df.index = df.index.map(lambda x: translation_dict.get(x, x))       # Traducir los índices (valores de la primera columna


    df = format_dataframe(df)

    # Crear el contenido LaTeX para la tabla con colores
    latex_table = "\\begin{table}[H]\n"
    latex_table += "    \\centering\n"
    latex_table += "    \\begin{tabular}{lllllll}\n"
    
    numRow=0
    for idx, row in df.iterrows():
        if numRow == 0:
            latex_table += f"    \\rowcolor[HTML]{{DAE8FC}} \\ & "
            latex_table += " & ".join(" \\textbf{"+row+"}") + " \\\\\n"
        elif numRow%2 != 0:
            if idx == "CPU -> Device (ejec)" or idx == "CPU -> Device (ejec+Tras)":
                latex_table += f"    \\cellcolor[HTML]{{DAE8FC}} \\textbf{{{idx}}} & "
                latex_table += " & ".join(row+"\%") + " \\\\\n"            
            else:
                latex_table += f"    \\cellcolor[HTML]{{DAE8FC}} \\textbf{{{idx}}} & "
                latex_table += " & ".join(row+"ms") + " \\\\\n"
        else:
            if idx == "CPU -> Device (ejec)" or idx == "CPU -> Device (ejec+Tras)":
                latex_table += f"    \\rowcolor[HTML]{{EFEFEF}} \cellcolor[HTML]{{DAE8FC}} \\textbf{{{idx}}} & "
                latex_table += " & ".join(row+"\%") + " \\\\\n"
            else:
                latex_table += f"    \\rowcolor[HTML]{{EFEFEF}} \cellcolor[HTML]{{DAE8FC}} \\textbf{{{idx}}} & "
                latex_table += " & ".join(row+"ms") + " \\\\\n"            
        numRow+=1
    
    nameFile = ultimo_elemento = csv_file.split("/")[-1]
    nameFile_parts=nameFile.split("_")


    latex_table += "    \\end{tabular}\n"
    latex_table += f"    \\caption[Resultados generales de rendimiento "+nameFile_parts[1]+"]{{Resultados generales de rendimiento "+nameFile_parts[1]+". Fuente: Creación propia}}\n"
    latex_table += f"    \\label{{table_{os.path.splitext(os.path.basename(csv_file))[0]}_data}}\n"
    latex_table += "\\end{table}"

    # Crear el nombre del archivo de salida .tex
    output_tex_file = f"{csv_file}_data.tex"

    # Escribir el contenido LaTeX en un archivo
    with open(output_tex_file, 'w') as f:
        f.write(latex_table)




if __name__ == "__main__":
    # Asegurarse de que se pase un argumento
    if len(sys.argv) != 2:
        print("Uso: python script.py ruta/al/archivo.csv")
        sys.exit(1)

    # Obtener la ruta del archivo CSV desde los argumentos de línea de comandos
    csv_file = sys.argv[1]
    generateSpeedupTable(csv_file)
    generateDataTable(csv_file)
