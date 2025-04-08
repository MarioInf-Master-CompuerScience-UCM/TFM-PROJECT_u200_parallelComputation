import pandas as pd
import numpy as np
import os
import sys


def csv_to_latex(csv_file):

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
    newRow = df_ini.iloc[3].copy()
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name = "CPU Opt"
    newRow = df_ini.iloc[5].copy()
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])
    
    newRow_name = "\\quad CPU-1"
    newRow = df_ini.iloc[7].copy()
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name = "\\quad CPU-2"
    newRow = df_ini.iloc[8].copy()
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name = "Dispositivo"
    newRow = df_ini.iloc[1].copy()
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name = "CPU->Disp"
    newRow = ((df_ini.iloc[1] - df_ini.iloc[3])/df_ini.iloc[3])*100
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name = "CPU Opt->Disp"
    newRow = ((df_ini.iloc[1] - df_ini.iloc[5])/df_ini.iloc[5])*100
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])



    #Agregamos consumos en KiloVátios/Hora
    ######################################
    newRow_name = "\\textbf{{\\emph{{\\underline{{Energía (kWh)}}}}}}"
    newRow = df_ini.iloc[0].copy()
    newRow.loc[:]=""
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name = "CPU"
    newRow = df_ini.iloc[3].copy()
    newRow = (df_ini.iloc[3]/1000)*((df_ini.iloc[4]/3600000))
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name = "CPU Opt"
    newRow = df_ini.iloc[5].copy()
    newRow = (df_ini.iloc[5]/1000)*((df_ini.iloc[6]/3600000))
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])

    newRow_name = "Dispositivo"
    newRow = df_ini.iloc[1].copy()
    newRow = (df_ini.iloc[1]/1000)*((df_ini.iloc[2]/3600000))
    df = pd.concat([df, pd.DataFrame([newRow], index=[newRow_name])])


    # Redondear los valores numéricos a dos decimales y agregar tabulador a las dos últimas columnas
    def format_value(x, col):
        if isinstance(x, (int, float)):
            # Si el número es mayor que 1e6 o menor que 1e-3, usa notación científica
            if abs(x) >= 1e6 or (0 < abs(x) < 1e-3):
                x = f"{x:.2e}"  # Notación científica con dos cifras decimales
            else:
                x = f"{x:.2f}"  # Notación decimal con dos cifras decimales
        if col in df.columns[-2:]:  # Las dos últimas columnas
            x = f"\t{x}"
        return x


    df = df.apply(lambda col: col.map(lambda x: format_value(x, col.name)))

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

        if numRow == 0:
            latex_table += " & ".join("\\textbf{"+row+"}") + " \\\\\n"
        elif numRow >=7 and numRow<=8 :
            latex_table += " & ".join(row+"\%") + " \\\\\n"
        else:
            latex_table += " & ".join(row) + " \\\\\n"

        numRow+=1
    
    nameFile = ultimo_elemento = csv_file.split("/")[-1]
    nameFile_parts=nameFile.split("_")


    latex_table += "    \\end{tabular}\n"
    latex_table += f"    \\caption[Resultados de consumo "+nameFile_parts[1]+" "+nameFile_parts[2]+"]{{Resultados de consumo "+nameFile_parts[1]+" "+nameFile_parts[2]+". Fuente: Creación propia}}\n"
    latex_table += f"    \\label{{table_{os.path.splitext(os.path.basename(csv_file))[0]}}}\n"
    latex_table += "\\end{table}"

    # Crear el nombre del archivo de salida .tex
    output_tex_file = f"{csv_file}.tex"

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
    csv_to_latex(csv_file)
