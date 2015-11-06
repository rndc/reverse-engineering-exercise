Solusi:
-------

Soal reverseme.com adalah file executable 16bit untuk sistem operasi MS-DOS. Berikut ini adalah cara memperoleh solusinya:

* Pertama, periksa dulu _printable_ _string_ yang ada pada file tersebut:

```
% strings reverseme.com
!r6P
6<17K49
$9Mflag.txt
error: file flag.txt tidak ditemukan
$flagnya masih salah :(
$selamat, flagnya benar!$
```

* Dari hasil perintah di atas, bisa terlihat bahwa aplikasi reverseme tersebut akan mencari file __flag.txt__ yang berisi flag.

* Disassemble file tersebut menggunakan radare2 dengan menambahkan opsi "-b 16" seperti ini:

```
% r2 -b 16 reverseme.com
[0000:0000]>
```

* Selanjutnya lakukan analisis menggunakan perintah __aaa__ seperti ini pada prompt radare2

```
[0000:0000]> aaa
```

* Lanjutkan dengan memberikan perintah __pd__ untuk melakukan disassemble:

```
[0000:0000]> pd
/ (fcn) fcn.00000000 80
|           0000:0000    ba5e01         mov dx, 0x15e                  ; 350
|           0000:0003    b8003d         mov ax, 0x3d00
|           0000:0006    cd21           int 0x21
|       ,=< 0000:0008    7236           jb 0x40
|       |   0000:000a    50             push ax
|       |   0000:000b    8d16c201       lea dx, [0x1c2]                ; 0x1c2  ; 450
|       |   0000:000f    b90e00         mov cx, 0xe                    ; 14
|       |   0000:0012    89c3           mov bx, ax
|       |   0000:0014    b43f           mov ah, 0x3f                   ; '?' ; 63
|       |   0000:0016    cd21           int 0x21
|       |   0000:0018    5b             pop bx
|       |   0000:0019    b43e           mov ah, 0x3e                   ; '>' ; 62
|       |   0000:001b    cd21           int 0x21
|       |   0000:001d    b90d00         mov cx, 0xd                    ; 13
|     .---> 0000:0020    89cb           mov bx, cx
|     | |   0000:0022    8a875001       mov al, byte [bx + 0x150]      ; [0x150:1]=255 ; 336
|     | |   0000:0026    0430           add al, 0x30
|     | |   0000:0028    3a87c201       cmp al, byte [bx + 0x1c2]      ; [0x1c2:1]=255 ; 450
|     |,==< 0000:002c    750a           jne 0x38
|     `===< 0000:002e    e2f0           loop 0x20
|      ||   0000:0030    baa701         mov dx, 0x1a7                  ; 423
|      ||   0000:0033    e81500         call 0x4b
|    ,====< 0000:0036    eb0e           jmp 0x46
|    | `--> 0000:0038    ba8e01         mov dx, 0x18e                  ; 398
|    |  |   0000:003b    e80d00         call 0x4b
|   ,      ; DATA XREF from 0x00000019 (fcn.00000000)
|   ,=====< 0000:003e    eb06           jmp 0x46
|   ||  `-> 0000:0040    ba6701         mov dx, 0x167                  ; 359
|   ||      0000:0043    e80500         call 0x4b
|   ||      ; JMP XREF from 0x0000003e (fcn.00000000)
|   ||      ; JMP XREF from 0x00000036 (fcn.00000000)
|   ``----> 0000:0046    b8004c         mov ax, 0x4c00
|           0000:0049    cd21           int 0x21
|           ; CALL XREF from 0x00000043 (fcn.00000000)
|           ; CALL XREF from 0x0000003b (fcn.00000000)
|           ; CALL XREF from 0x00000033 (fcn.00000000)
|           0000:004b    b409           mov ah, 9
|           0000:004d    cd21           int 0x21
\           0000:004f    c3             ret
            0000:0050    363c31         cmp al, 0x31                   ; '1' ; 49
            0000:0053    37             aaa
            0000:0054    4b             dec bx
            0000:0055    3439           xor al, 0x39
            0000:0057    17             pop ss
            0000:0058    152211         adc ax, 0x1122
            0000:005b    2439           and al, 0x39
            0000:005d    4d             dec bp
            0000:005e    666c           insb byte es:[di], dx
            0000:0060    61             popaw
        ,=< 0000:0061    672e7478       je 0xdd
       ,==< 0000:0065    7400           je 0x67
      ,`--> 0000:0067    657272         jb 0xdc
      | |   0000:006a    6f             outsw dx, word [si]
     ,====< 0000:006b    723a           jb 0xa7
     || |   0000:006d    206669         and byte [bp + 0x69], ah
     || |   0000:0070    6c             insb byte es:[di], dx
     || |   0000:0071    6520666c       and byte gs:[bp + 0x6c], ah
     || |   0000:0075    61             popaw
    ,=====< 0000:0076    672e7478       je 0xf2
   ,======< 0000:007a    7420           je 0x9c
  ,=======< 0000:007c    7469           je 0xe7
  ||||| |   0000:007e    6461           popaw
  ||||| |   0000:0080    6b2064         imul sp, word [bx + si], 0x64
  ||||| |   0000:0083    6974656d75     imul si, word [si + 0x65], 0x756d
  ||||| |   0000:0088    6b616e0d       imul sp, word [bx + di + 0x6e], 0xd
  ||||| |   0000:008c    0a24           or ah, byte [si]
  ||||| |   0000:008e    666c           insb byte es:[di], dx
  ||||| |   0000:0090    61             popaw
  ||||| |   0000:0091    676e           outsb dx, byte [esi]
  ========< 0000:0093    7961           jns 0xf6
```

* Untuk mempermudah analisis, gunakan dokumen [Ralf Brown Interrupt Table](http://www.ctyme.com/intr/int.htm) dan khusus untuk interupsi 21 heksadesimal (21h) pada MS-DOS bisa diakses pada [tautan ini](http://www.ctyme.com/intr/int-21.htm) atau untuk tampilan yang lebih sederhana, bisa dilihat pada [tautan ini](http://stanislavs.org/helppc/int_21.html). Bagian yang penting pada interupsi __21h__ adalah register __AX__. Register tersebut adalah register 16 bit yang dapat dibagi menjadi 2 buah register 8 bit, yaitu register __AH__ yang berisi __HIGH__ byte dan register __AL__ yang berisi __LOW__ byte. Jadi misalnya register __AX__ berisi nilai __0x3d00__, maka register __AH__ nilainya __0x3d__ dan register __AL__ nilainya __0x00__. Fungsi yang akan dipanggil ditentukan oleh isi dari register AH. Berikut ini adalah ilustrasinya:

```
+-----------------------+
|      AX = 0x3d00      |
+-----------+-----------+
| AH = 0x3d | AL = 0x00 |
+-----------+-----------+
```

* Agar lebih mudah, hasil disassembly radare2 di atas akan dijelaskan setiap bagian.

```
0000:0000    ba5e01         mov dx, 0x15e
0000:0003    b8003d         mov ax, 0x3d00
0000:0006    cd21           int 0x21
```

* Pada bagian di atas, register __AX__ nilainya __0x3d00__, artinya register __AH__ nilainya __0x3d__ dan register __AL__ nilainya __0x00__. Yang perlu diperhatikan adalah jika register __AH__ nilainya __0x3d__, berarti fungsi yang akan dipanggil adalah [fungsi untuk membuka file](http://stanislavs.org/helppc/int_21-3d.html). Register __AL__ nilainya __0x00__ artinya file tersebut akan dibuka dengan akses _READ_ONLY_. Alamat memori yang berisi nama file yang akan dibuka dimasukkan ke register __DX__. Perlu dicatat bahwa aplikasi COM untuk MS-DOS di-_load_ ke memori pada alamat __0x100__, karena bagian sebelum alamat tersebut digunakan untuk struktur yang disebut __PSP__ (Program Segment Prefix). Sehingga, pada baris _disassembly_ di atas, alamat yang dimasukkan ke register __DX__, yaitu __0x15e__ dikurangi dengan nilai __0x100__ sehingga memperoleh nilai _offset_ __0x5e__. Pada offset tersebut, kita bisa menemukan string yang berisi nama file seperti yang bisa terlihat dari _disassembly_ berikut ini:

```
0000:005e    666c           insb byte es:[di], dx
0000:0060    61             popaw
0000:0061    672e7478       je 0xdd
0000:0065    7400           je 0x67
```

* Jika diperhatikan baik-baik, bagian tersebut berisi nama file. Untuk memudahkan, Anda dapat langsung mengubah barisan byte tersebut menjadi _string_ dengan perintah seperti ini:

```
% echo -e '\x66\x6c\x61\x67\x2e\x74\x78\x74'
flag.txt
```

* Selanjutnya, perhatikan potongan _disassembly_ berikut ini:

```
0000:0008    7236           jb 0x40         ; jika file tidak dapat dibuka atau tidak ditemukan maka lompat ke alamat 0x40 (0000:0040)
0000:000a    50             push ax         ; jika file berhasil dibuka maka handlenya akan berada pada register AX,
                                            ; pada baris ini, handle tersebut disimpan ke stack untuk nantinya digunakan
0000:000b    8d16c201       lea dx, [0x1c2] ; register DX adalah alamat memori untuk menyimpan isi file (buffer)
0000:000f    b90e00         mov cx, 0xe     ; register CX adalah jumlah byte yang akan dibaca (0xe = 14 byte)
0000:0012    89c3           mov bx, ax      ; register BX diisi dengan isi register AX (file handle)
0000:0014    b43f           mov ah, 0x3f    ; register AH diisi dengan nilai 0x3f yaitu fungsi untuk membaca file
0000:0016    cd21           int 0x21        ; interupsi 0x21
```

* Setelah membaca file, maka selanjutnya adalah menutup _handle_ yang digunakan oleh file. Pada alamat __0000:000a__ bisa terlihat bahwa handle tersebut kita simpan ke _stack_ sehingga untuk mengaksesnya, kita cukup menggunakan instruksi __POP__  seperti ini:

```
0000:0018    5b             pop bx          ; sekarang register BX berisi handle file
0000:0019    b43e           mov ah, 0x3e    ; register AH diisi dengan nilai 0x3e yaitu fungsi untuk menutup handle file
0000:001b    cd21           int 0x21        ; interupsi 0x21
```

* Selanjutnya adalah bagian yang akan melakukan pengecekan flag yang benar.

```
0000:001d    b90d00         mov cx, 0xd               ; isi register CX dengan nilai 0xd (13 desimal), karena kita akan mengakses
                                                      ; flag menggunakan index 0, sehingga jika terdapat 14 byte maka kita akan
                                                      ; mengakses mulai dari 0 hingga 13.
0000:0020    89cb           mov bx, cx                ; register BX diisi dengan nilai pada register CX. Pada awalnya, nilai register
                                                      ; CX adalah 0xd (13 desimal) dan akan dikurangi satu setiap kali instruksi "loop"
                                                      ; melompat ke alamat ini.
0000:0022    8a875001       mov al, byte [bx + 0x150] ; register AL diisi dengan byte pada alamat 0x150 yang diindex menggunakan
                                                      ; register BX. Alamat 0x150 berisi key yang benar yang telah melalui proses
                                                      ; kalkulasi sederhana.
0000:0026    0430           add al, 0x30              ; byte pada register AL ditambah dengan nilai 0x30.
0000:0028    3a87c201       cmp al, byte [bx + 0x1c2] ; hasilnya dibandingkan dengan byte yang terdapat pada alamat 0x1c2 dimana index
                                                      ; byte yang akan diakses ditentukan oleh nilai pada register BX. Alamat memori
                                                      ; 0x1c2 adalah flag yang dimasukkan oleh user (perhatikan instruksi pada alamat
                                                      ; 0000:000b)
0000:002c    750a           jne 0x38                  ; jika nilainya tidak sama, maka lompat ke alamat 0000:0038
0000:002e    e2f0           loop 0x20                 ; instruksi loop akan mengurangi (decrement) nilai yang ada pada register CX
                                                      ; dan melompat ke alamat 0000:0020
```

* Sebenarnya, dari potongan kode di atas, kita sudah dapat menemukan flag yang benar. Caranya adalah dengan mengambil 14 byte dari alamat 0x50 dan menambahkan nilai 0x30 pada setiap byte. Berikut ini adalah byte yang dimaksud:

```
0000:0050    363c31         cmp al, 0x31              ; \x36\x3c\x31
0000:0053    37             aaa                       ; \x37
0000:0054    4b             dec bx                    ; \x4b
0000:0055    3439           xor al, 0x39              ; \x34\x39
0000:0057    17             pop ss                    ; \x17
0000:0058    152211         adc ax, 0x1122            ; \x15\x22\x11
0000:005b    2439           and al, 0x39              ; \x24\x39
0000:005d    4d             dec bp                    ; \x4d
```

* Dan berikut ini adalah salah satu contoh cara untuk mengubah byte tersebut menjadi flag:

```python
>>> print ''.join([chr(ord(c) + 0x30) for c in '\x36\x3c\x31\x37\x4b\x34\x39\x17\x15\x22\x11\x24\x39\x4d'])
flag{diGERATi}
```

* Bagian selanjutnya dari potongan kode disassembly tersebut adalah untuk menampilkan beberapa kalimat yang terdapat pada aplikasi reverseme tersebut:

```
0000:0030    baa701         mov dx, 0x1a7   ; register DX diisi dengan alamat kalimat yang akan ditampilkan
                                            ; yaitu kalimat "selamat, flagnya benar!"
0000:0033    e81500         call 0x4b       ; panggil fungsi untuk menampilkan kalimat tersebut ke layar (STDOUT)
0000:0036    eb0e           jmp 0x46        ; setelah menampilkan kalimat tersebut, lompat ke alamat untuk keluar dari aplikasi
0000:0038    ba8e01         mov dx, 0x18e   ; alamat ini akan dieksekusi jika flag yang dimasukkan user salah.
                                            ; register DX akan diisi dengan kalimat "flagnya masih salah :("
0000:003b    e80d00         call 0x4b       ; lalu memanggil fungsi untuk mencetak kalimat tersebut ke layar (STDOUT)
0000:003e    eb06           jmp 0x46        ; setelah itu melompat ke alamat untuk keluar dari aplikasi.

0000:0040    ba6701         mov dx, 0x167   ; instruksi pada baris ini akan dieksekusi jika file "flag.txt" tidak ditemukan,
                                            ; yaitu dari instruksi yang ada pada alamat 0000:0008.
                                            ; register DX diisi dengan kalimat "error: file flag.txt tidak ditemukan"
0000:0043    e80500         call 0x4b       ; lalu panggil fungsi untuk menampilkan kalimat tersebut ke layar (STDOUT)
```

* Potongan kode berikut ini adalah bagian untuk menghentikan program (_exit_):

```
0000:0046    b8004c         mov ax, 0x4c00  ; register AH diisi dengan nilai 0x4C yaitu fungsi exit
                                            ; register AL adalah return value (exit code) yaitu 0x00
                                            ; atau dalam bahasa C, baris ini dan baris selanjutnya adalah "return 0;"
0000:0049    cd21           int 0x21        ; interupsi 0x21
```

* Berikut ini adalah potongan kode dari fungsi yang tugasnya menuliskan (_print_) kalimat ke layar (_STDOUT_). Sebelum fungsi ini dipanggil, register __DX__ terlebih dahulu diisi dengan alamat kalimat yang akan ditampilkan:

```
0000:004b    b409           mov ah, 9       ; register AH diisi dengan nilai 9 yaitu fungsi untuk mencetak kalimat ke layar (STDOUT)
0000:004d    cd21           int 0x21        ; interupsi 0x21
0000:004f    c3             ret             ; kembali ke alamat pemanggil fungsi ini
```

* Sekian tutorial singkat kali ini semoga bermanfaat.
