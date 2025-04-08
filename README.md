# Trabajo Fin de Máster - Proyecto

![Idioma: Español](https://img.shields.io/badge/Idioma-Español-green.svg)
![Idioma: Español](https://img.shields.io/badge/Año_académico-2023/2024-blue.svg)
![Idioma: Español](https://img.shields.io/badge/Curso_académico-Segundo_curso-blue.svg)

Título: **_Evaluación del rendimiento de FPGAs para aceleración de kernels de cómputo: Un estudio comparativo_**

Enlaces relevantes:

- [Página web de la titulación](https://informatica.ucm.es/master-en-ingenieria-informatica)
- [Ficha docente de la asignatura](docs/fichaDocente.pdf)

## REQUISITOS PREVIOS

- **Instalación de la biblioteca JsonCpp:** Utilizada para poder extraer la configuración del bechmark del fichero Json.

```BASH
sudo apt-get install libjsoncpp-dev
```

- **Instalación de Python y sus librerías pertinentes**

```BASH
sudo apt-get update
sudo apt-get install -y python3 python3-pip
sudo apt-get install -y python3-pip
pip3 install matplotlib
pip install pandas
```

## EJECUTAR CON PERMISOS DE SUDO

```BASH
sudo -E PATH=$PATH make run_hw
sudo -E PATH=$PATH make clear_out
```
