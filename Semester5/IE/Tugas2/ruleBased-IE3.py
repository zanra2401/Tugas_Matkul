import os
from entityGenerator2 import generateEntity
from courtHistoryCsv import courtHistory

def main():

    start_path = "./INPUT/"
    hasil_path = "./OUTPUT/"
    daftarFile = os.listdir(start_path)
    listHasil = []
    #namaFile = "48Pid.B2015.PNJKTTIM.txt"
    #namaFile = "161Pid.B2015.PNJktTim.txt"
    #hasil = generateEntity(start_path, namaFile)
    #listHasil.append(hasil)
    for tiapFile in daftarFile:
        hasil = generateEntity(start_path, tiapFile)
        listHasil.append(hasil)
        print("======= ROW HASIL =======")    
        print(hasil)

    createFile = courtHistory(listHasil)
	
    print("======= HASIL AKHIR =======")
    print(createFile)    

main();
