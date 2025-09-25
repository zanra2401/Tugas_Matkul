import csv
import os.path

def courtHistory(listHasil):

	csvFolrder = "./"
	csvName = "courtHistory.csv"

	if os.path.exists(csvName):

		f = open(csvName, 'a', newline='\n')
		print(f)
		print("ada")
		w = csv.writer(f)

	else:

		f = open(csvName, 'w', newline='\n')
		print(f)
		print("tidak ada")
    
		w = csv.writer(f)
		w.writerow(('Nomor Putusan', 'Nama Terdakwa 1', 'Nama Terdakwa 2', 'Nama Terdakwa 3', 'Tuntutan Pidana', 'Tuntutan KUHP', 'Tuntukan Hukuman', 'Putusan Pidana', 'Putusan Hukuman', 'Tanggal Putusan', 'Hakim Ketua', 'Hakim Anggota1', 'Hakim Anggota2', 'Panitera', 'Penuntut Umum'))
    
	# menulis file csv
	for s in listHasil:
		w.writerow(s)

	f.close()
	berhasil = "\nCreate Csv file Berhasil\n" 
	return berhasil



