import re

def generateEntity(pathFile,fileName):

    print("a")
    folderData = pathFile
    folderHasil = "./OUTPUT/"
    #namaFile = "12Pid.B2015.PNJktTim.txt"
    namaFile = fileName
    namaFileHasil = "O-"+namaFile
    listHasil =[]

    file_putusan = open(folderData+namaFile, "r", encoding='UTF8')
    baca_baris = file_putusan.readlines()

    terdakwa = 0
    tuntutan_pidana = 0
    tuntutanPidana = 0
    tuntutanHukuman = 0
    tindakPidana = 0
    hukuman = 0
    nomor_putusan = 0
    listTerdakwa=[]

    print("")
    print("====== KEPUTUSAN PENGADILAN =====")

    with open(folderHasil + namaFile, "w", encoding="utf-8") as file:
        for baris in baca_baris:
            panjang_baris = len(baris)
            if panjang_baris > 3:
                baris=baris.lower()

                # mendapatkan entitas NOMOR PUTUSAN
                if baris.find("pid.b") >= 0 and nomor_putusan == 0:
                    nomor_putusan +=1
                    eNomor = re.search( r'\d+/(.)*/\d{4}/(.)*',baris, re.M|re.I)	

                    print("Nomor Putusan : "+eNomor.group())
                    file.writelines("Nomor Putusan : "+eNomor.group())
                    listHasil.append(eNomor.group().rstrip("\n")) 
                    
                # mendapatkan entitas NAMA TERDAKWA
                if baris.find("nama terdakwa :") >= 0 or baris.find("nama lengkap :") >= 0:
                    terdakwa += 1
                    eTerdakwa = re.search( r'nama (lengkap|terdakwa) :(.*)',baris, re.M|re.I)                
                    terdakwaKe = str(terdakwa)
                    print("Terdakwa Ke : "+terdakwaKe)
                    print("Nama Terdakwa : "+eTerdakwa.group(2))
                    file.writelines("Terdakwa Ke : "+terdakwaKe)
                    file.writelines("Nama Terdakwa : "+eTerdakwa.group(2))
                    listTerdakwa.append(eTerdakwa.group(2).rstrip("\n"))

                if (baris.find("terdakwa ditahan") >= 0 or baris.find("telah ditahan") >= 0 or baris.find("terdakwa berada") >= 0 )and terdakwa >= 1:
                    listHasil.append(listTerdakwa[0])
                    if terdakwa == 1: 
                        listHasil.append("")                
                        listHasil.append("")
                    if terdakwa == 2: 
                        listHasil.append(listTerdakwa[1])                
                        listHasil.append("")
                    if terdakwa == 3: 
                        listHasil.append(listTerdakwa[1])                
                        listHasil.append(listTerdakwa[2])
                    terdakwa = 0
                    
                # mendapatkan entitas TUNTUTAN PIDANA
                if baris.find("menyatakan terdakwa") >= 0 and tuntutan_pidana == 0 and tuntutanPidana==0:
                    print("====== TUNTUTAN =====")
                    if baris.find("sebagaimana") >= 0:
                        ePidana = re.search( r'melakukan tindak pidana (.*) sebagaimana',baris, re.M|re.I)                
                    else:
                        ePidana = re.search( r'melakukan tindak pidana (.*) ;',baris, re.M|re.I)
                        
                    if ePidana:
                        print("Tindak Pidana : "+ePidana.group(1))            
                        listHasil.append(ePidana.group(1))
                    else:
                        print("Tindak Pidana : ")            
                        listHasil.append("")                

                    eKUHP = re.search( r'pasal (.*) kuhp',baris, re.M|re.I)
                    if eKUHP: 
                        print("Melanggar KUHP : " +eKUHP.group())
                        listHasil.append(eKUHP.group())
                    else:
                        print("Melanggar KUHP : ")
                        listHasil.append("")                    
                    tuntutanPidana = 1

                if baris.find("menjatuhkan pidana") >= 0 and tuntutan_pidana == 0 and tuntutanHukuman == 0:
                    #print(baris)
                    etuntutan = re.search( r'selama (.*) dikurangi',baris, re.M|re.I)
                    print("Tuntutan Hukuman : "+etuntutan.group(1))
                    listHasil.append(etuntutan.group(1))                
                    tuntutan_pidana = 1

                # mendapatkan entitas PUTUSAN PIDANA
                if baris.find("menyatakan terdakwa") >= 0 and baris.find("terbukti") >= 0 and tuntutan_pidana == 1 and tuntutanPidana ==1:
                    print("====== PUTUSAN =====")
                    #print(baris)
                    if baris.find("sebagaimana") >= 0:
                        ePutPidana = re.search( r'melakukan tindak pidana (.*) sebagaimana',baris, re.M|re.I)
                    else:
                        ePutPidana = re.search( r'melakukan tindak pidana (.*) ;',baris, re.M|re.I)
                    print("Putusan Pidana : "+ePutPidana.group(1))            
                    listHasil.append(ePutPidana.group(1))
                    tuntutanHukuman = 1

                if baris.find("menjatuhkan pidana") >= 0 and tuntutan_pidana == 1 and tuntutanHukuman == 1:
                    #print(baris)
                    if baris.find("dikurangi") >= 0:
                        ePutusan = re.search( r'selama (.*) dikurangi',baris, re.M|re.I)
                    else:
                        ePutusan = re.search( r'selama (.*) ;',baris, re.M|re.I)    
                    print("Putusan Hukuman : "+ePutusan.group(1))
                    listHasil.append(ePutusan.group(1))
                    #tuntutan_pidana = 1    
            
                # mendapatkan HAKIM KETUA MAJLIS HAKIM            
                if baris.find("diputuskan dalam") >= 0:
                    print("====== PENUTUP =====")
                    cari_tgl_putusan = baris.find("tanggal")
                    cari_tgl_putusan1 = baris.find("oleh")

                    if baris.find(", se") >= 0:
                        cari_hakim_ketua1 = baris.find(", se")
                    else:
                        cari_hakim_ketua1 = baris.find(". se")

                    if baris.find("oleh kami") >= 0:
                        oleh = 9
                    else:
                        oleh = 5

                    if baris.find("ketua majelis hakim, ") >= 0:  
                        cari_hakim_anggota1 = baris.find("ketua majelis hakim, ")+21
                    elif baris.find("hakim ketua majelis, ") >=0:    
                        cari_hakim_anggota1 = baris.find("hakim ketua majelis, ")+21
                    elif baris.find("hakim ketua, ") >=0:
                        cari_hakim_anggota1 = baris.find("hakim ketua, ")+13

                    cari_hakim_anggota2 = baris.find("masing")            
                    hakim_anggota = baris[cari_hakim_anggota1:cari_hakim_anggota2-1]
                    hakim_anggota1 = hakim_anggota[0:hakim_anggota.find(" dan")]
                    hakim_anggota2 = hakim_anggota[hakim_anggota.find(" dan")+5:len(hakim_anggota)]

                    if baris.find("dibantu oleh") >= 0:
                        cari_panitera1 = baris.find("dibantu oleh")+13
                    else:    
                        cari_panitera1 = baris.find("dibantu")+8

                    if baris.find("sebagai panitera pengganti") >= 0:              
                        cari_panitera2 = baris.find("sebagai panitera pengganti")
                    elif baris.find("panitera pengganti") >= 0:              
                        cari_panitera2 = baris.find("panitera pengganti")
                        
                    if baris.find("dihadiri oleh") >= 0:
                        cari_penuntut_umum1 = baris.find("dihadiri oleh")+13
                    elif baris.find("dihadiri") >= 0:
                        cari_penuntut_umum1 = baris.find("dihadiri")+9    

                    if baris.find("jaksa penuntut umum") >= 0:
                        cari_penuntut_umum2 = baris.find("jaksa penuntut umum")
                    elif baris.find("penuntut umum") >= 0:
                        cari_penuntut_umum2 = baris.find("penuntut umum")    
                    
                    tanggalPutusan = baris[cari_tgl_putusan+8:cari_tgl_putusan1]
                    hakimKetua = baris[cari_tgl_putusan1+oleh:cari_hakim_ketua1]
                    hakimAnggota1 = hakim_anggota1
                    hakimAnggota2 = hakim_anggota2
                    panitera = baris[cari_panitera1:cari_panitera2]
                    penuntutUmum = baris[cari_penuntut_umum1:cari_penuntut_umum2]

                    print("Tanggal Putusan : "+tanggalPutusan)
                    print("Hakim Ketua : "+hakimKetua)
                    print("Hakim Anggota 1 : "+hakimAnggota1)
                    print("Hakim Anggota 2 : "+hakimAnggota2)
                    print("Panitera : "+panitera)
                    print("Penuntut Umum : "+penuntutUmum)

                    listHasil.append(tanggalPutusan)
                    listHasil.append(hakimKetua)
                    listHasil.append(hakimAnggota1)
                    listHasil.append(hakimAnggota2)
                    listHasil.append(panitera)
                    listHasil.append(penuntutUmum)

            print(baris)
    file_putusan.close()
    print("======================")
    return listHasil


# #start_path = "./INPUT/"
# #namaFile = "48Pid.B2015.PNJKTTIM.txt"

# #hasil = generateEntity(start_path, namaFile)
# #print(hasil)
