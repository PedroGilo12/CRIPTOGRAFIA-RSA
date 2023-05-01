from PyQt6 import uic
from PyQt6.QtWidgets import QApplication
from PyQt6 import QtCore, QtGui, QtWidgets
from frontQt6 import Ui_Dialog
import sys
import os
import shutil
import tkinter as tk
from tkinter import filedialog
from tkinter import messagebox
from tkinter import simpledialog
import time
import subprocess

'''
    def setCommand(self, button: QtWidgets.QPushButton, func):
        button.clicked.connect(func)

    def unsetCommand(self, button: QtWidgets.QPushButton, func):
        button.clicked.disconnect(func)
'''


def SetFileForDescript():
    targetfile = str(filedialog.askopenfilename())                      # Abre o contexto de dialogo para seleção do arquivo retorna o caminho do arquivo
    targetFolder = str(os.path.dirname(os.path.abspath(__file__)))      # Armazena o caminho raiz onde o arquivo em python está localizado

    # Confirmo se algum arquivo foi selecionado
    if targetfile != "":

        # Crio o arquivo temporário cript.tmp
        with open("InputFile.tmp", "w") as file:
            file.close()

        # Copio os dados do arquivo selecionado para o arquivo cript.tmp
        shutil.copyfile(targetfile, targetFolder+"\InputFile.tmp")
        print(targetfile)
        return

def SetMsgForCript():
    entrada_usuario = simpledialog.askstring("Criptografar", "Digite uma mensagem para ser criptografada                                                ")

    print(f"Entrada do usuario: {entrada_usuario}")

    if entrada_usuario != "":

        try:
            with open("InputFile.tmp", "w") as file:
                file.write(entrada_usuario)
                file.close()

                return True
        except:
            print("Algo inesperado aconteceu com a entrada do usuário, verifique se a entrada foi digitada corretamente")
    else:
        return False

def SetFileForCript():
    targetfile = str(filedialog.askopenfilename())                      # Abre o contexto de dialogo para seleção do arquivo retorna o caminho do arquivo
    targetFolder = str(os.path.dirname(os.path.abspath(__file__)))      # Armazena o caminho raiz onde o arquivo em python está localizado

    # Confirmo se algum arquivo foi selecionado
    if targetfile != "":

        # Crio o arquivo temporário cript.tmp
        with open("tmpfiles/cript.tmp", "w") as file:
            file.close()

        # Copio os dados do arquivo selecionado para o arquivo cript.tmp
        shutil.copyfile(targetfile, targetFolder+"\arquivo-criptografado.tmp")
        print(targetfile)
        return

def CommandGenerateKey():
    entrada_usuario = simpledialog.askstring("Gerar chave pública", "Digite dois numeros primos grandes p e q separados por um espaço")

    if entrada_usuario != None:
        try:
            key = entrada_usuario.split(" ")
        
            with open("tmpfiles/pq.tmp", "w") as file:
                file.write(f"{int(key[0])} {int(key[1])} {int(key[2])}")
                file.close()

            os.system("cmd /c generateKey < tmpfiles\pq.tmp")

            with open("key_pub.txt", "r") as file:
                valor = file.read()
                file.close()

            if valor == "-1\n-1\n":
                messagebox.showerror("Error","A entrada digitada não é válida")
                os.remove("key_pub.txt")
            else:
                messagebox.showinfo("Gerar chave pública","p e q salvos com sucesso!")

        except:

            messagebox.showerror("Error","Algo inesperado aconteceu com a entrada do usuário, verifique se a entrada foi digitada corretamente")

    return

def CommandCript():

    if SetMsgForCript():
        os.system("cmd /c cript")

        targetfolder = str(filedialog.askdirectory())
        targetFile = str(os.path.dirname(os.path.abspath(__file__))+"\OutputFile.tmp")  

        with open(targetfolder+"\ArquivoCriptografado.txt", "w") as file:
            file.close()

        shutil.copyfile(targetFile, targetfolder+"\ArquivoCriptografado.txt")

        print(targetfolder)

        messagebox.showinfo("Criptografia concluída!", f"O arquivo criptografado foi salvo em: {targetfolder+'/ArquivoCriptografado.txt'}")
        print("Criptografado!")

        os.remove('InputFile.tmp')
        os.remove('OutputFile.tmp')

    else:
        messagebox.showerror("Error", "Entrada Vazia!")

        print("Entrada vazia")
    
    return

def CommandDescript():

    entrada_usuario = simpledialog.askstring("Insira os valores", "Digite respectivamente 'p' 'q' e 'e' separados por um espaço cada um deles:")

    targetFolder = str(os.path.dirname(os.path.abspath(__file__)))  

    with open(targetFolder+"\pqe.tmp", "w") as file:
        file.write(entrada_usuario)
        file.close()

    SetFileForDescript()

    os.system(f"cmd /c descript.exe < pqe.tmp")

    targetfolder = str(filedialog.askdirectory())
    shutil.copyfile("OutputFile.tmp", targetfolder+"\ArquivoDescriptografado.txt")

    os.remove("pqe.tmp")
    os.remove("OutputFile.tmp")
    os.remove("InputFile.tmp")
    
    print("Descriptografado!")
    return

if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    Dialog = QtWidgets.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)

    ui.setCommand(ui.GenerateKey, CommandGenerateKey)
    ui.setCommand(ui.Cript, CommandCript)
    ui.setCommand(ui.Desencript, CommandDescript)

    Dialog.show()
    sys.exit(app.exec())