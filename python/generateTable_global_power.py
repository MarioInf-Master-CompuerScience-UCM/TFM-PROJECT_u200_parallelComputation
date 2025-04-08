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
        if abs(x) >= 1e6 or (0 < abs(x) < 1e-3):
            x = f"{x:.2e}"  # Notación científica con dos cifras decimales
        else:
            x = f"{x:.2f}"  # Notación decimal con dos cifras decimales
    if col in df.columns[-2:]:  # Las dos últimas columnas
        x = f"\t{x}"
    return x


def format_dataframe(df):
    return df.apply(lambda col: col.apply(format_value, args=(col.name, df)))




def generateSpeedupTable(csv_file):

    df_ini = pd.read_csv(csv_file)
    df=pd.DataFrame(columns=['', 'Aceleración (CPU->X)', 'Energía', 'Aceleración/Energía'])
    df.loc[df.shape[0]]=['', 'Aceleración (CPU->X)', 'Energía', 'Aceleración/Energía']


    #################################
    # Tratamiento de datos Mini
    #################################
    dataRow = df_ini.iloc[0, 1:]
    CPU_energy = dataRow.iloc[0]
    CPU_time = dataRow.iloc[1]

    CPUOpt_energy = dataRow.iloc[2]
    CPUOpt_time = dataRow.iloc[3]
    CPUOpt_accel = ((CPU_time-CPUOpt_time)/CPUOpt_time)*100
    Opt0_energy = dataRow.iloc[4]
    Opt0_time = dataRow.iloc[5]
    Opt0_accel = ((CPU_time-Opt0_time)/Opt0_time)*100
    Opt1_energy = dataRow.iloc[6]
    Opt1_time = dataRow.iloc[7]
    Opt1_accel = ((CPU_time-Opt1_time)/Opt1_time)*100
    Opt2_energy = dataRow.iloc[8]
    Opt2_time = dataRow.iloc[9]
    Opt2_accel = ((CPU_time-Opt2_time)/Opt2_time)*100
    Opt3_energy = dataRow.iloc[10]
    Opt3_time = dataRow.iloc[11]
    Opt3_accel = ((CPU_time-Opt3_time)/Opt3_time)*100
    Opt4_energy = dataRow.iloc[12]
    Opt4_time = dataRow.iloc[13]
    Opt4_accel = ((CPU_time-Opt4_time)/Opt4_time)*100


    df.loc[df.shape[0]]=['\\textbf{{\\emph{{\\underline{{Mini}}}}}}', '', '', '']
    df.loc[df.shape[0]]=['CPU Opt', CPUOpt_accel, CPUOpt_energy, CPUOpt_accel/CPUOpt_energy]
    df.loc[df.shape[0]]=['OPT0', Opt0_accel, Opt0_energy, Opt0_accel/Opt0_energy]
    df.loc[df.shape[0]]=['OPT1', Opt1_accel, Opt1_energy, Opt1_accel/Opt1_energy]
    df.loc[df.shape[0]]=['OPT2', Opt2_accel, Opt2_energy, Opt2_accel/Opt2_energy]
    df.loc[df.shape[0]]=['OPT3', Opt3_accel, Opt3_energy, Opt3_accel/Opt3_energy]
    df.loc[df.shape[0]]=['OPT4', Opt4_accel, Opt4_energy, Opt4_accel/Opt4_energy]


    #################################
    # Tratamiento de datos Small
    #################################
    dataRow = df_ini.iloc[1, 1:]
    CPU_energy = dataRow.iloc[0]
    CPU_time = dataRow.iloc[1]

    CPUOpt_energy = dataRow.iloc[2]
    CPUOpt_time = dataRow.iloc[3]
    CPUOpt_accel = ((CPU_time-CPUOpt_time)/CPUOpt_time)*100
    Opt0_energy = dataRow.iloc[4]
    Opt0_time = dataRow.iloc[5]
    Opt0_accel = ((CPU_time-Opt0_time)/Opt0_time)*100
    Opt1_energy = dataRow.iloc[6]
    Opt1_time = dataRow.iloc[7]
    Opt1_accel = ((CPU_time-Opt1_time)/Opt1_time)*100
    Opt2_energy = dataRow.iloc[8]
    Opt2_time = dataRow.iloc[9]
    Opt2_accel = ((CPU_time-Opt2_time)/Opt2_time)*100
    Opt3_energy = dataRow.iloc[10]
    Opt3_time = dataRow.iloc[11]
    Opt3_accel = ((CPU_time-Opt3_time)/Opt3_time)*100
    Opt4_energy = dataRow.iloc[12]
    Opt4_time = dataRow.iloc[13]
    Opt4_accel = ((CPU_time-Opt4_time)/Opt4_time)*100


    df.loc[df.shape[0]]=['\\textbf{{\\emph{{\\underline{{Small}}}}}}', '', '', '']
    df.loc[df.shape[0]]=['CPU Opt', CPUOpt_accel, CPUOpt_energy, CPUOpt_accel/CPUOpt_energy]
    df.loc[df.shape[0]]=['OPT0', Opt0_accel, Opt0_energy, Opt0_accel/Opt0_energy]
    df.loc[df.shape[0]]=['OPT1', Opt1_accel, Opt1_energy, Opt1_accel/Opt1_energy]
    df.loc[df.shape[0]]=['OPT2', Opt2_accel, Opt2_energy, Opt2_accel/Opt2_energy]
    df.loc[df.shape[0]]=['OPT3', Opt3_accel, Opt3_energy, Opt3_accel/Opt3_energy]
    df.loc[df.shape[0]]=['OPT4', Opt4_accel, Opt4_energy, Opt4_accel/Opt4_energy]




    #################################
    # Tratamiento de datos Medium
    #################################
    dataRow = df_ini.iloc[2, 1:]
    CPU_energy = dataRow.iloc[0]
    CPU_time = dataRow.iloc[1]

    CPUOpt_energy = dataRow.iloc[2]
    CPUOpt_time = dataRow.iloc[3]
    CPUOpt_accel = ((CPU_time-CPUOpt_time)/CPUOpt_time)*100
    Opt0_energy = dataRow.iloc[4]
    Opt0_time = dataRow.iloc[5]
    Opt0_accel = ((CPU_time-Opt0_time)/Opt0_time)*100
    Opt1_energy = dataRow.iloc[6]
    Opt1_time = dataRow.iloc[7]
    Opt1_accel = ((CPU_time-Opt1_time)/Opt1_time)*100
    Opt2_energy = dataRow.iloc[8]
    Opt2_time = dataRow.iloc[9]
    Opt2_accel = ((CPU_time-Opt2_time)/Opt2_time)*100
    Opt3_energy = dataRow.iloc[10]
    Opt3_time = dataRow.iloc[11]
    Opt3_accel = ((CPU_time-Opt3_time)/Opt3_time)*100
    Opt4_energy = dataRow.iloc[12]
    Opt4_time = dataRow.iloc[13]
    Opt4_accel = ((CPU_time-Opt4_time)/Opt4_time)*100


    df.loc[df.shape[0]]=['\\textbf{{\\emph{{\\underline{{Medium}}}}}}', '', '', '']
    df.loc[df.shape[0]]=['CPU Opt', CPUOpt_accel, CPUOpt_energy, CPUOpt_accel/CPUOpt_energy]
    df.loc[df.shape[0]]=['OPT0', Opt0_accel, Opt0_energy, Opt0_accel/Opt0_energy]
    df.loc[df.shape[0]]=['OPT1', Opt1_accel, Opt1_energy, Opt1_accel/Opt1_energy]
    df.loc[df.shape[0]]=['OPT2', Opt2_accel, Opt2_energy, Opt2_accel/Opt2_energy]
    df.loc[df.shape[0]]=['OPT3', Opt3_accel, Opt3_energy, Opt3_accel/Opt3_energy]
    df.loc[df.shape[0]]=['OPT4', Opt4_accel, Opt4_energy, Opt4_accel/Opt4_energy]




    #################################
    # Tratamiento de datos Large
    #################################
    dataRow = df_ini.iloc[3, 1:]
    CPU_energy = dataRow.iloc[0]
    CPU_time = dataRow.iloc[1]

    CPUOpt_energy = dataRow.iloc[2]
    CPUOpt_time = dataRow.iloc[3]
    CPUOpt_accel = ((CPU_time-CPUOpt_time)/CPUOpt_time)*100
    Opt0_energy = dataRow.iloc[4]
    Opt0_time = dataRow.iloc[5]
    Opt0_accel = ((CPU_time-Opt0_time)/Opt0_time)*100
    Opt1_energy = dataRow.iloc[6]
    Opt1_time = dataRow.iloc[7]
    Opt1_accel = ((CPU_time-Opt1_time)/Opt1_time)*100
    Opt2_energy = dataRow.iloc[8]
    Opt2_time = dataRow.iloc[9]
    Opt2_accel = ((CPU_time-Opt2_time)/Opt2_time)*100
    Opt3_energy = dataRow.iloc[10]
    Opt3_time = dataRow.iloc[11]
    Opt3_accel = ((CPU_time-Opt3_time)/Opt3_time)*100
    Opt4_energy = dataRow.iloc[12]
    Opt4_time = dataRow.iloc[13]
    Opt4_accel = ((CPU_time-Opt4_time)/Opt4_time)*100


    df.loc[df.shape[0]]=['\\textbf{{\\emph{{\\underline{{Large}}}}}}', '', '', '']
    df.loc[df.shape[0]]=['CPU Opt', CPUOpt_accel, CPUOpt_energy, CPUOpt_accel/CPUOpt_energy]
    df.loc[df.shape[0]]=['OPT0', Opt0_accel, Opt0_energy, Opt0_accel/Opt0_energy]
    df.loc[df.shape[0]]=['OPT1', Opt1_accel, Opt1_energy, Opt1_accel/Opt1_energy]
    df.loc[df.shape[0]]=['OPT2', Opt2_accel, Opt2_energy, Opt2_accel/Opt2_energy]
    df.loc[df.shape[0]]=['OPT3', Opt3_accel, Opt3_energy, Opt3_accel/Opt3_energy]
    df.loc[df.shape[0]]=['OPT4', Opt4_accel, Opt4_energy, Opt4_accel/Opt4_energy]




    #################################
    # Tratamiento de datos Extralarge
    #################################
    dataRow = df_ini.iloc[4, 1:]
    CPU_energy = dataRow.iloc[0]
    CPU_time = dataRow.iloc[1]

    CPUOpt_energy = dataRow.iloc[2]
    CPUOpt_time = dataRow.iloc[3]
    CPUOpt_accel = ((CPU_time-CPUOpt_time)/CPUOpt_time)*100
    Opt0_energy = dataRow.iloc[4]
    Opt0_time = dataRow.iloc[5]
    Opt0_accel = ((CPU_time-Opt0_time)/Opt0_time)*100
    Opt1_energy = dataRow.iloc[6]
    Opt1_time = dataRow.iloc[7]
    Opt1_accel = ((CPU_time-Opt1_time)/Opt1_time)*100
    Opt2_energy = dataRow.iloc[8]
    Opt2_time = dataRow.iloc[9]
    Opt2_accel = ((CPU_time-Opt2_time)/Opt2_time)*100
    Opt3_energy = dataRow.iloc[10]
    Opt3_time = dataRow.iloc[11]
    Opt3_accel = ((CPU_time-Opt3_time)/Opt3_time)*100
    Opt4_energy = dataRow.iloc[12]
    Opt4_time = dataRow.iloc[13]
    Opt4_accel = ((CPU_time-Opt4_time)/Opt4_time)*100


    df.loc[df.shape[0]]=['\\textbf{{\\emph{{\\underline{{Exralarge}}}}}}', '', '', '']
    df.loc[df.shape[0]]=['CPU Opt', CPUOpt_accel, CPUOpt_energy, CPUOpt_accel/CPUOpt_energy]
    df.loc[df.shape[0]]=['OPT0', Opt0_accel, Opt0_energy, Opt0_accel/Opt0_energy]
    df.loc[df.shape[0]]=['OPT1', Opt1_accel, Opt1_energy, Opt1_accel/Opt1_energy]
    df.loc[df.shape[0]]=['OPT2', Opt2_accel, Opt2_energy, Opt2_accel/Opt2_energy]
    df.loc[df.shape[0]]=['OPT3', Opt3_accel, Opt3_energy, Opt3_accel/Opt3_energy]
    df.loc[df.shape[0]]=['OPT4', Opt4_accel, Opt4_energy, Opt4_accel/Opt4_energy]



    df=format_dataframe(df)
    df = df.reset_index(drop=True)
    #print("\nDataFrame salida:")
    #print(df)   

    # Crear el contenido LaTeX para la tabla con colores
    latex_table = "\\begin{table}[H]\n"
    latex_table += "    \\centering\n"
    latex_table += "    \\begin{tabular}{lllr}\n"
    
    numRow=0
    for idx, row in df.iterrows():
        if numRow == 0:
            latex_table += f"    \\rowcolor[HTML]{{DAE8FC}} \\ & "
            rowTemp=row.iloc[1:]
            for i, cell in enumerate(rowTemp):
                latex_table += "\\textbf{" +str(cell)+"}"
                if i < len(rowTemp) - 1:
                    latex_table += " & "
            latex_table += " \\\\\n"

        else:
            if numRow%2 != 0:
                latex_table += f"    \\cellcolor[HTML]{{DAE8FC}} \\textbf{{{row.iloc[0]}}} & "
            else:
                latex_table += f"    \\rowcolor[HTML]{{EFEFEF}} \cellcolor[HTML]{{DAE8FC}} \\textbf{{{row.iloc[0]}}} &"
            
            rowTemp=row.iloc[1:]
            if rowTemp.iloc[0] != "" and rowTemp.iloc[0]!="\t":
                latex_table += rowTemp.iloc[0]+"\%  &" + rowTemp.iloc[1] + " kWh  &"+ rowTemp.iloc[2]+" s/j \\\\\n"
            else:
                latex_table += rowTemp.iloc[0]+"&" + rowTemp.iloc[1] + "&"+ rowTemp.iloc[2]+" \\\\\n"
        numRow+=1
    
    nameFile = ultimo_elemento = csv_file.split("/")[-1]
    nameFile_parts=nameFile.split("_")


    latex_table += "    \\end{tabular}\n"
    latex_table += f"    \\caption[Resultados generales de rendimiento "+nameFile_parts[1]+"]{{Resultados generales de rendimiento "+nameFile_parts[1]+". Fuente: Creación propia}}\n"
    latex_table += f"    \\label{{table_{os.path.splitext(os.path.basename(csv_file))[0]}_speedup-energy}}\n"
    latex_table += "\\end{table}"

    # Crear el nombre del archivo de salida .tex
    output_tex_file = f"{csv_file}_speedup-energy.tex"

    # Escribir el contenido LaTeX en un archivo
    with open(output_tex_file, 'w') as f:
        f.write(latex_table)





def generateDataTable(csv_file):
 
    df_ini = pd.read_csv(csv_file)
    df_ini = df_ini.transpose()
    df_ini.columns = df_ini.iloc[0]                                         # Ajustar los nombres de las columnas para que se muestren como el índice después de transponer


    df=df_ini[:1]

    #Agregamos consumos en Vátios
    ######################################
    newRow_name = "\\textbf{{\\emph{{\\underline{{Potencia (W)}}}}}}"
    newRow = df_ini.iloc[0].copy()
    newRow.loc[:]=""
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name = "CPU"
    newRow = df_ini.iloc[1].copy()
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name = "CPU Opt"
    newRow = df_ini.iloc[3].copy()
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name = "Opt0"
    newRow = df_ini.iloc[5].copy()
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])
    
    newRow_name = "Opt1"
    newRow = df_ini.iloc[7].copy()
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name = "Opt2"
    newRow = df_ini.iloc[9].copy()
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name = "Opt3"
    newRow = df_ini.iloc[11].copy()
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name = "Opt4"
    newRow = df_ini.iloc[13].copy()
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])



    #Agregamos consumos en KiloVátios/Hora
    ######################################
    newRow_name = "\\textbf{{\\emph{{\\underline{{Energía (kWh)}}}}}}"
    newRow = df_ini.iloc[0].copy()
    newRow.loc[:]=""
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name = "CPU"
    newRow = df_ini.iloc[1].copy()
    newRow = (df_ini.iloc[1]/1000)*((df_ini.iloc[2]/3600000))
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name = "CPU Opt"
    newRow = df_ini.iloc[3].copy()
    newRow = (df_ini.iloc[3]/1000)*((df_ini.iloc[4]/3600000))
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name = "Opt0"
    newRow = df_ini.iloc[5].copy()
    newRow = (df_ini.iloc[5]/1000)*((df_ini.iloc[6]/3600000))
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name = "Opt1"
    newRow = df_ini.iloc[7].copy()
    newRow = (df_ini.iloc[7]/1000)*((df_ini.iloc[8]/3600000))
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name = "Opt2"
    newRow = df_ini.iloc[9].copy()
    newRow = (df_ini.iloc[9]/1000)*((df_ini.iloc[10]/3600000))
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name = "Opt3"
    newRow = df_ini.iloc[11].copy()
    newRow = (df_ini.iloc[11]/1000)*((df_ini.iloc[12]/3600000))
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name = "Opt4"
    newRow = df_ini.iloc[13].copy()
    newRow = (df_ini.iloc[13]/1000)*((df_ini.iloc[14]/3600000))
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])

    df = format_dataframe(df)

    # Crear el contenido LaTeX para la tabla con colores
    latex_table = "\\begin{table}[H]\n"
    latex_table += "    \\centering\n"
    latex_table += "    \\begin{tabular}{lllllll}\n"
    
    numRow=0
    for idx, row in df.iterrows():

        if numRow == 0:
            latex_table += f"    \\rowcolor[HTML]{{DAE8FC}} \\ & "
        elif numRow%2 != 0:
            latex_table += f"    \\cellcolor[HTML]{{DAE8FC}} \\textbf{{{idx}}} & "
        else:
            latex_table += f"    \\rowcolor[HTML]{{EFEFEF}} \cellcolor[HTML]{{DAE8FC}} \\textbf{{{idx}}} & "

        latex_table += " & ".join(row) + " \\\\\n"
        numRow+=1
    
    nameFile = ultimo_elemento = csv_file.split("/")[-1]
    nameFile_parts=nameFile.split("_")


    latex_table += "    \\end{tabular}\n"
    latex_table += f"    \\caption[Resultados de consumo "+nameFile_parts[1]+" "+nameFile_parts[2]+"]{{Resultados de consumo "+nameFile_parts[1]+" "+nameFile_parts[2]+". Fuente: Creación propia}}\n"
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
