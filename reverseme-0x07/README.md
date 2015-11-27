### Pendahuluan

Tutorial ini akan membahas solusi untuk soal _veryhard_ pada CTF internal SMAKADUTA.


### Langkah-langkah

* Langkah pertama adalah mencari tahu tipe dari aplikasi tersebut. Langkah ini sifatnya opsional:
```
% file veryhard
veryhard: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked, interpreter /lib/ld-linux.so.2, \
for GNU/Linux 2.6.32, BuildID[sha1]=44f91fc551b9ff76ddeb134d0e443a0df4252e7f, not stripped
```

* Langkah kedua adalah mencari _printable string_ yang terdapat pada aplikasi tersebut:
```
% strings veryhard
/lib/ld-linux.so.2
libstdc++.so.6
...
0123456789_faisal_yudo_hernawan_GWP_deny_febriant_luqman_hakim_rizky_maulana
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA \
BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB \
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC \
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD \
EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE \
FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF \
GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG \
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH \
IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII \
JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ \
KKKKKKKKKKKK \
LLLLLLLLLLLLL \
MNOPQRSTUVWXYZ
febriant
Password :
Ya, itu flagnya!
Salah bro!
...
cinta.cpp
```

* Selanjutnya, coba jalankan aplikasi tersebut:
```
% ./veryhard
Password : mesintempur
Salah bro!
```

* Dari sini bisa terlihat bahwa jika password yang dimasukkan salah, maka akan muncul pesan __Salah bro!__. Selanjutnya, gunakan gdb untuk melakukan debugging terhadap aplikasi tersebut:
```
% gdb ./veryhard
Demangling of encoded C++/ObjC names when displaying symbols is on.
Demangling of C++/ObjC names in disassembly listings is on.
Reading symbols from ./veryhard...(no debugging symbols found)...done.
gdb>
```

* Lakukan disassembly terhadap fungsi __main__ pada aplikasi tersebut:
```
gdb> disass main
Dump of assembler code for function main:
   0x08048a2b <+0>: lea    ecx,[esp+0x4]
   0x08048a2f <+4>: and    esp,0xfffffff0
   0x08048a32 <+7>: push   DWORD PTR [ecx-0x4]
   0x08048a35 <+10>:    push   ebp
   0x08048a36 <+11>:    mov    ebp,esp
   0x08048a38 <+13>:    push   ebx
   0x08048a39 <+14>:    push   ecx
   0x08048a3a <+15>:    sub    esp,0x20
   0x08048a3d <+18>:    sub    esp,0xc
   0x08048a40 <+21>:    lea    eax,[ebp-0xe]
   0x08048a43 <+24>:    push   eax
   0x08048a44 <+25>:    call   0x8048900 <std::allocator<char>::allocator()@plt>
   0x08048a49 <+30>:    add    esp,0x10
   0x08048a4c <+33>:    sub    esp,0x4
   0x08048a4f <+36>:    lea    eax,[ebp-0xe]
   0x08048a52 <+39>:    push   eax
   0x08048a53 <+40>:    push   0x8048f90
   0x08048a58 <+45>:    lea    eax,[ebp-0x14]
   0x08048a5b <+48>:    push   eax
   0x08048a5c <+49>:    call   0x80488b0 <std::basic_string<char, std::char_traits<char>, std::allocator<char> > \
                                         ::basic_string(char const*, std::allocator<char> const&)@plt>
   0x08048a61 <+54>:    add    esp,0x10
   0x08048a64 <+57>:    sub    esp,0xc
   0x08048a67 <+60>:    lea    eax,[ebp-0xe]
   0x08048a6a <+63>:    push   eax
   0x08048a6b <+64>:    call   0x80488e0 <std::allocator<char>::~allocator()@plt>
   0x08048a70 <+69>:    add    esp,0x10
   0x08048a73 <+72>:    sub    esp,0xc
   0x08048a76 <+75>:    lea    eax,[ebp-0xd]
   0x08048a79 <+78>:    push   eax
   0x08048a7a <+79>:    call   0x8048900 <std::allocator<char>::allocator()@plt>
   0x08048a7f <+84>:    add    esp,0x10
   0x08048a82 <+87>:    sub    esp,0x4
   0x08048a85 <+90>:    lea    eax,[ebp-0xd]
   0x08048a88 <+93>:    push   eax
   0x08048a89 <+94>:    push   0x8048fe0
   0x08048a8e <+99>:    lea    eax,[ebp-0x18]
   0x08048a91 <+102>:   push   eax
   0x08048a92 <+103>:   call   0x80488b0 <std::basic_string<char, std::char_traits<char>, std::allocator<char> > \
                                         ::basic_string(char const*, std::allocator<char> const&)@plt>
   0x08048a97 <+108>:   add    esp,0x10
   0x08048a9a <+111>:   sub    esp,0xc
   0x08048a9d <+114>:   lea    eax,[ebp-0xd]
   0x08048aa0 <+117>:   push   eax
   0x08048aa1 <+118>:   call   0x80488e0 <std::allocator<char>::~allocator()@plt>
   0x08048aa6 <+123>:   add    esp,0x10
   0x08048aa9 <+126>:   sub    esp,0x8
   0x08048aac <+129>:   lea    eax,[ebp-0x14]
   0x08048aaf <+132>:   push   eax
   0x08048ab0 <+133>:   lea    eax,[ebp-0x1c]
   0x08048ab3 <+136>:   push   eax
   0x08048ab4 <+137>:   call   0x8048850 <std::basic_string<char, std::char_traits<char>, std::allocator<char> > \
                                         ::basic_string(std::string const&)@plt>
   0x08048ab9 <+142>:   add    esp,0x10
   0x08048abc <+145>:   sub    esp,0x4
   0x08048abf <+148>:   push   0x0
   0x08048ac1 <+150>:   push   0x80491f9
   0x08048ac6 <+155>:   lea    eax,[ebp-0x1c]
   0x08048ac9 <+158>:   push   eax
   0x08048aca <+159>:   call   0x8048870 <std::string::find(char const*, unsigned int) const@plt>
   0x08048acf <+164>:   add    esp,0x10
   0x08048ad2 <+167>:   mov    DWORD PTR [ebp-0xc],eax
   0x08048ad5 <+170>:   lea    eax,[ebp-0x20]
   0x08048ad8 <+173>:   push   0xffffffff
   0x08048ada <+175>:   push   DWORD PTR [ebp-0xc]
   0x08048add <+178>:   lea    edx,[ebp-0x1c]
   0x08048ae0 <+181>:   push   edx
   0x08048ae1 <+182>:   push   eax
   0x08048ae2 <+183>:   call   0x80488c0 <std::string::substr(unsigned int, unsigned int) const@plt>
   0x08048ae7 <+188>:   add    esp,0xc
   0x08048aea <+191>:   sub    esp,0x8
   0x08048aed <+194>:   push   0x1
   0x08048aef <+196>:   push   0x3
   0x08048af1 <+198>:   lea    eax,[ebp-0x14]
   0x08048af4 <+201>:   push   eax
   0x08048af5 <+202>:   push   0x1
   0x08048af7 <+204>:   push   0x1
   0x08048af9 <+206>:   lea    eax,[ebp-0x20]
   0x08048afc <+209>:   push   eax
   0x08048afd <+210>:   call   0x80488f0 <std::string::replace(unsigned int, unsigned int, std::string const&, \
                                         unsigned int, unsigned int)@plt>
   0x08048b02 <+215>:   add    esp,0x20
   0x08048b05 <+218>:   sub    esp,0x8
   0x08048b08 <+221>:   push   0x1
   0x08048b0a <+223>:   push   0x1
   0x08048b0c <+225>:   lea    eax,[ebp-0x14]
   0x08048b0f <+228>:   push   eax
   0x08048b10 <+229>:   push   0x1
   0x08048b12 <+231>:   push   0x4
   0x08048b14 <+233>:   lea    eax,[ebp-0x20]
   0x08048b17 <+236>:   push   eax
   0x08048b18 <+237>:   call   0x80488f0 <std::string::replace(unsigned int, unsigned int, std::string const&, \
                                         unsigned int, unsigned int)@plt>
   0x08048b1d <+242>:   add    esp,0x20
   0x08048b20 <+245>:   sub    esp,0x8
   0x08048b23 <+248>:   push   0x1
   0x08048b25 <+250>:   push   0x3
   0x08048b27 <+252>:   lea    eax,[ebp-0x14]
   0x08048b2a <+255>:   push   eax
   0x08048b2b <+256>:   push   0x1
   0x08048b2d <+258>:   push   0x5
   0x08048b2f <+260>:   lea    eax,[ebp-0x20]
   0x08048b32 <+263>:   push   eax
   0x08048b33 <+264>:   call   0x80488f0 <std::string::replace(unsigned int, unsigned int, std::string const&, \
                                         unsigned int, unsigned int)@plt>
   0x08048b38 <+269>:   add    esp,0x20
   0x08048b3b <+272>:   sub    esp,0x8
   0x08048b3e <+275>:   push   0x1
   0x08048b40 <+277>:   push   0xa
   0x08048b42 <+279>:   lea    eax,[ebp-0x14]
   0x08048b45 <+282>:   push   eax
   0x08048b46 <+283>:   push   0x1
   0x08048b48 <+285>:   push   0x8
   0x08048b4a <+287>:   lea    eax,[ebp-0x20]
   0x08048b4d <+290>:   push   eax
   0x08048b4e <+291>:   call   0x80488f0 <std::string::replace(unsigned int, unsigned int, std::string const&, \
                                         unsigned int, unsigned int)@plt>
   0x08048b53 <+296>:   add    esp,0x20
   0x08048b56 <+299>:   sub    esp,0x8
   0x08048b59 <+302>:   push   0x1
   0x08048b5b <+304>:   push   0xb
   0x08048b5d <+306>:   lea    eax,[ebp-0x14]
   0x08048b60 <+309>:   push   eax
   0x08048b61 <+310>:   push   0x1
   0x08048b63 <+312>:   push   0x10
   0x08048b65 <+314>:   lea    eax,[ebp-0x20]
   0x08048b68 <+317>:   push   eax
   0x08048b69 <+318>:   call   0x80488f0 <std::string::replace(unsigned int, unsigned int, std::string const&, \
                                         unsigned int, unsigned int)@plt>
   0x08048b6e <+323>:   add    esp,0x20
   0x08048b71 <+326>:   sub    esp,0x8
   0x08048b74 <+329>:   push   0x1
   0x08048b76 <+331>:   push   0x1
   0x08048b78 <+333>:   lea    eax,[ebp-0x14]
   0x08048b7b <+336>:   push   eax
   0x08048b7c <+337>:   push   0x1
   0x08048b7e <+339>:   push   0x12
   0x08048b80 <+341>:   lea    eax,[ebp-0x20]
   0x08048b83 <+344>:   push   eax
   0x08048b84 <+345>:   call   0x80488f0 <std::string::replace(unsigned int, unsigned int, std::string const&, \
                                         unsigned int, unsigned int)@plt>
   0x08048b89 <+350>:   add    esp,0x20
   0x08048b8c <+353>:   sub    esp,0x8
   0x08048b8f <+356>:   push   0x1
   0x08048b91 <+358>:   push   0x5
   0x08048b93 <+360>:   lea    eax,[ebp-0x14]
   0x08048b96 <+363>:   push   eax
   0x08048b97 <+364>:   push   0x1
   0x08048b99 <+366>:   push   0x13
   0x08048b9b <+368>:   lea    eax,[ebp-0x20]
   0x08048b9e <+371>:   push   eax
   0x08048b9f <+372>:   call   0x80488f0 <std::string::replace(unsigned int, unsigned int, std::string const&, \
                                         unsigned int, unsigned int)@plt>
   0x08048ba4 <+377>:   add    esp,0x20
   0x08048ba7 <+380>:   sub    esp,0x8
   0x08048baa <+383>:   push   0x1
   0x08048bac <+385>:   push   0x4
   0x08048bae <+387>:   lea    eax,[ebp-0x14]
   0x08048bb1 <+390>:   push   eax
   0x08048bb2 <+391>:   push   0x1
   0x08048bb4 <+393>:   push   0x14
   0x08048bb6 <+395>:   lea    eax,[ebp-0x20]
   0x08048bb9 <+398>:   push   eax
   0x08048bba <+399>:   call   0x80488f0 <std::string::replace(unsigned int, unsigned int, std::string const&, \
                                         unsigned int, unsigned int)@plt>
   0x08048bbf <+404>:   add    esp,0x20
   0x08048bc2 <+407>:   sub    esp,0x8
   0x08048bc5 <+410>:   push   0x1
   0x08048bc7 <+412>:   push   0x10
   0x08048bc9 <+414>:   lea    eax,[ebp-0x14]
   0x08048bcc <+417>:   push   eax
   0x08048bcd <+418>:   push   0x1
   0x08048bcf <+420>:   push   0x15
   0x08048bd1 <+422>:   lea    eax,[ebp-0x20]
   0x08048bd4 <+425>:   push   eax
   0x08048bd5 <+426>:   call   0x80488f0 <std::string::replace(unsigned int, unsigned int, std::string const&, \
                                         unsigned int, unsigned int)@plt>
   0x08048bda <+431>:   add    esp,0x20
   0x08048bdd <+434>:   sub    esp,0x8
   0x08048be0 <+437>:   push   0x1
   0x08048be2 <+439>:   push   0xa
   0x08048be4 <+441>:   lea    eax,[ebp-0x14]
   0x08048be7 <+444>:   push   eax
   0x08048be8 <+445>:   push   0x1
   0x08048bea <+447>:   push   0x16
   0x08048bec <+449>:   lea    eax,[ebp-0x20]
   0x08048bef <+452>:   push   eax
   0x08048bf0 <+453>:   call   0x80488f0 <std::string::replace(unsigned int, unsigned int, std::string const&, \
                                         unsigned int, unsigned int)@plt>
   0x08048bf5 <+458>:   add    esp,0x20
   0x08048bf8 <+461>:   sub    esp,0x8
   0x08048bfb <+464>:   push   0x1
   0x08048bfd <+466>:   push   0x20
   0x08048bff <+468>:   lea    eax,[ebp-0x14]
   0x08048c02 <+471>:   push   eax
   0x08048c03 <+472>:   push   0x1
   0x08048c05 <+474>:   push   0x17
   0x08048c07 <+476>:   lea    eax,[ebp-0x20]
   0x08048c0a <+479>:   push   eax
   0x08048c0b <+480>:   call   0x80488f0 <std::string::replace(unsigned int, unsigned int, std::string const&, \
                                         unsigned int, unsigned int)@plt>
   0x08048c10 <+485>:   add    esp,0x20
   0x08048c13 <+488>:   sub    esp,0x8
   0x08048c16 <+491>:   push   0x1
   0x08048c18 <+493>:   push   0x20
   0x08048c1a <+495>:   lea    eax,[ebp-0x14]
   0x08048c1d <+498>:   push   eax
   0x08048c1e <+499>:   push   0x1
   0x08048c20 <+501>:   push   0x18
   0x08048c22 <+503>:   lea    eax,[ebp-0x20]
   0x08048c25 <+506>:   push   eax
   0x08048c26 <+507>:   call   0x80488f0 <std::string::replace(unsigned int, unsigned int, std::string const&, \
                                         unsigned int, unsigned int)@plt>
   0x08048c2b <+512>:   add    esp,0x20
   0x08048c2e <+515>:   sub    esp,0x8
   0x08048c31 <+518>:   push   0x1
   0x08048c33 <+520>:   push   0x21
   0x08048c35 <+522>:   lea    eax,[ebp-0x14]
   0x08048c38 <+525>:   push   eax
   0x08048c39 <+526>:   push   0x1
   0x08048c3b <+528>:   push   0x19
   0x08048c3d <+530>:   lea    eax,[ebp-0x20]
   0x08048c40 <+533>:   push   eax
   0x08048c41 <+534>:   call   0x80488f0 <std::string::replace(unsigned int, unsigned int, std::string const&, \
                                         unsigned int, unsigned int)@plt>
   0x08048c46 <+539>:   add    esp,0x20
   0x08048c49 <+542>:   sub    esp,0x8
   0x08048c4c <+545>:   push   0x1
   0x08048c4e <+547>:   push   0x22
   0x08048c50 <+549>:   lea    eax,[ebp-0x14]
   0x08048c53 <+552>:   push   eax
   0x08048c54 <+553>:   push   0x1
   0x08048c56 <+555>:   push   0x1a
   0x08048c58 <+557>:   lea    eax,[ebp-0x20]
   0x08048c5b <+560>:   push   eax
   0x08048c5c <+561>:   call   0x80488f0 <std::string::replace(unsigned int, unsigned int, std::string const&, \
                                         unsigned int, unsigned int)@plt>
   0x08048c61 <+566>:   add    esp,0x20
   0x08048c64 <+569>:   sub    esp,0x8
   0x08048c67 <+572>:   push   0x1
   0x08048c69 <+574>:   push   0x4
   0x08048c6b <+576>:   lea    eax,[ebp-0x14]
   0x08048c6e <+579>:   push   eax
   0x08048c6f <+580>:   push   0x1
   0x08048c71 <+582>:   push   0x1d
   0x08048c73 <+584>:   lea    eax,[ebp-0x20]
   0x08048c76 <+587>:   push   eax
   0x08048c77 <+588>:   call   0x80488f0 <std::string::replace(unsigned int, unsigned int, std::string const&, \
                                         unsigned int, unsigned int)@plt>
   0x08048c7c <+593>:   add    esp,0x20
   0x08048c7f <+596>:   sub    esp,0x8
   0x08048c82 <+599>:   push   0x1
   0x08048c84 <+601>:   push   0x4
   0x08048c86 <+603>:   lea    eax,[ebp-0x14]
   0x08048c89 <+606>:   push   eax
   0x08048c8a <+607>:   push   0x1
   0x08048c8c <+609>:   push   0x20
   0x08048c8e <+611>:   lea    eax,[ebp-0x20]
   0x08048c91 <+614>:   push   eax
   0x08048c92 <+615>:   call   0x80488f0 <std::string::replace(unsigned int, unsigned int, std::string const&, \
                                         unsigned int, unsigned int)@plt>
   0x08048c97 <+620>:   add    esp,0x20
   0x08048c9a <+623>:   sub    esp,0xc
   0x08048c9d <+626>:   lea    eax,[ebp-0x24]
   0x08048ca0 <+629>:   push   eax
   0x08048ca1 <+630>:   call   0x80487e0 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::basic_string()@plt>
   0x08048ca6 <+635>:   add    esp,0x10
   0x08048ca9 <+638>:   sub    esp,0x8
   0x08048cac <+641>:   push   0x8049202
   0x08048cb1 <+646>:   push   0x804a6c0
   0x08048cb6 <+651>:   call   0x8048880 <std::basic_ostream<char, std::char_traits<char> >& std::operator<< \
                                         <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)@plt>
   0x08048cbb <+656>:   add    esp,0x10
   0x08048cbe <+659>:   sub    esp,0x8
   0x08048cc1 <+662>:   lea    eax,[ebp-0x24]
   0x08048cc4 <+665>:   push   eax
   0x08048cc5 <+666>:   push   0x804a600
   0x08048cca <+671>:   call   0x8048890 <std::basic_istream<char, std::char_traits<char> >& std::operator>><char, \
                                          std::char_traits<char>, std::allocator<char> >(std::basic_istream<char, \
                                          std::char_traits<char> >&, std::basic_string<char, std::char_traits<char>, \
                                          std::allocator<char> >&)@plt>
   0x08048ccf <+676>:   add    esp,0x10
   0x08048cd2 <+679>:   sub    esp,0x8
   0x08048cd5 <+682>:   lea    eax,[ebp-0x20]
   0x08048cd8 <+685>:   push   eax
   0x08048cd9 <+686>:   lea    eax,[ebp-0x24]
   0x08048cdc <+689>:   push   eax
   0x08048cdd <+690>:   call   0x8048e82 <__gnu_cxx::__enable_if<std::__is_char<char>::__value, bool>::__type \
                                         std::operator==<char>(std::basic_string<char, std::char_traits<char>, \
                                         std::allocator<char> > const&, std::basic_string<char, std::char_traits<char>, \
                                         std::allocator<char> > const&)>
   0x08048ce2 <+695>:   add    esp,0x10
   0x08048ce5 <+698>:   test   al,al
   0x08048ce7 <+700>:   je     0x8048d00 <main+725>
   0x08048ce9 <+702>:   sub    esp,0x8
   0x08048cec <+705>:   push   0x804920e
   0x08048cf1 <+710>:   push   0x804a6c0
   0x08048cf6 <+715>:   call   0x8048880 <std::basic_ostream<char, std::char_traits<char> >& std::operator<<  \
                                         <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)@plt>
   0x08048cfb <+720>:   add    esp,0x10
   0x08048cfe <+723>:   jmp    0x8048d15 <main+746>
   0x08048d00 <+725>:   sub    esp,0x8
   0x08048d03 <+728>:   push   0x804921f
   0x08048d08 <+733>:   push   0x804a6c0
   0x08048d0d <+738>:   call   0x8048880 <std::basic_ostream<char, std::char_traits<char> >& std::operator<<  \
                                         <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)@plt>
   0x08048d12 <+743>:   add    esp,0x10
   0x08048d15 <+746>:   sub    esp,0xc
   0x08048d18 <+749>:   lea    eax,[ebp-0x24]
   0x08048d1b <+752>:   push   eax
   0x08048d1c <+753>:   call   0x80488a0 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
   0x08048d21 <+758>:   add    esp,0x10
   0x08048d24 <+761>:   sub    esp,0xc
   0x08048d27 <+764>:   lea    eax,[ebp-0x20]
   0x08048d2a <+767>:   push   eax
   0x08048d2b <+768>:   call   0x80488a0 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
   0x08048d30 <+773>:   add    esp,0x10
   0x08048d33 <+776>:   sub    esp,0xc
   0x08048d36 <+779>:   lea    eax,[ebp-0x1c]
   0x08048d39 <+782>:   push   eax
   0x08048d3a <+783>:   call   0x80488a0 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
   0x08048d3f <+788>:   add    esp,0x10
   0x08048d42 <+791>:   sub    esp,0xc
   0x08048d45 <+794>:   lea    eax,[ebp-0x18]
   0x08048d48 <+797>:   push   eax
   0x08048d49 <+798>:   call   0x80488a0 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
   0x08048d4e <+803>:   add    esp,0x10
   0x08048d51 <+806>:   sub    esp,0xc
   0x08048d54 <+809>:   lea    eax,[ebp-0x14]
   0x08048d57 <+812>:   push   eax
   0x08048d58 <+813>:   call   0x80488a0 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
   0x08048d5d <+818>:   add    esp,0x10
   0x08048d60 <+821>:   mov    eax,0x0
   0x08048d65 <+826>:   jmp    0x8048e01 <main+982>
   0x08048d6a <+831>:   mov    ebx,eax
   0x08048d6c <+833>:   sub    esp,0xc
   0x08048d6f <+836>:   lea    eax,[ebp-0xe]
   0x08048d72 <+839>:   push   eax
   0x08048d73 <+840>:   call   0x80488e0 <std::allocator<char>::~allocator()@plt>
   0x08048d78 <+845>:   add    esp,0x10
   0x08048d7b <+848>:   mov    eax,ebx
   0x08048d7d <+850>:   sub    esp,0xc
   0x08048d80 <+853>:   push   eax
   0x08048d81 <+854>:   call   0x8048920 <_Unwind_Resume@plt>
   0x08048d86 <+859>:   mov    ebx,eax
   0x08048d88 <+861>:   sub    esp,0xc
   0x08048d8b <+864>:   lea    eax,[ebp-0xd]
   0x08048d8e <+867>:   push   eax
   0x08048d8f <+868>:   call   0x80488e0 <std::allocator<char>::~allocator()@plt>
   0x08048d94 <+873>:   add    esp,0x10
   0x08048d97 <+876>:   jmp    0x8048de7 <main+956>
   0x08048d99 <+878>:   mov    ebx,eax
   0x08048d9b <+880>:   sub    esp,0xc
   0x08048d9e <+883>:   lea    eax,[ebp-0x24]
   0x08048da1 <+886>:   push   eax
   0x08048da2 <+887>:   call   0x80488a0 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
   0x08048da7 <+892>:   add    esp,0x10
   0x08048daa <+895>:   jmp    0x8048dae <main+899>
   0x08048dac <+897>:   mov    ebx,eax
   0x08048dae <+899>:   sub    esp,0xc
   0x08048db1 <+902>:   lea    eax,[ebp-0x20]
   0x08048db4 <+905>:   push   eax
   0x08048db5 <+906>:   call   0x80488a0 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
   0x08048dba <+911>:   add    esp,0x10
   0x08048dbd <+914>:   jmp    0x8048dc1 <main+918>
   0x08048dbf <+916>:   mov    ebx,eax
   0x08048dc1 <+918>:   sub    esp,0xc
   0x08048dc4 <+921>:   lea    eax,[ebp-0x1c]
   0x08048dc7 <+924>:   push   eax
   0x08048dc8 <+925>:   call   0x80488a0 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
   0x08048dcd <+930>:   add    esp,0x10
   0x08048dd0 <+933>:   jmp    0x8048dd4 <main+937>
   0x08048dd2 <+935>:   mov    ebx,eax
   0x08048dd4 <+937>:   sub    esp,0xc
   0x08048dd7 <+940>:   lea    eax,[ebp-0x18]
   0x08048dda <+943>:   push   eax
   0x08048ddb <+944>:   call   0x80488a0 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
   0x08048de0 <+949>:   add    esp,0x10
   0x08048de3 <+952>:   jmp    0x8048de7 <main+956>
   0x08048de5 <+954>:   mov    ebx,eax
   0x08048de7 <+956>:   sub    esp,0xc
   0x08048dea <+959>:   lea    eax,[ebp-0x14]
   0x08048ded <+962>:   push   eax
   0x08048dee <+963>:   call   0x80488a0 <std::basic_string<char, std::char_traits<char>, std::allocator<char> >::~basic_string()@plt>
   0x08048df3 <+968>:   add    esp,0x10
   0x08048df6 <+971>:   mov    eax,ebx
   0x08048df8 <+973>:   sub    esp,0xc
   0x08048dfb <+976>:   push   eax
   0x08048dfc <+977>:   call   0x8048920 <_Unwind_Resume@plt>
   0x08048e01 <+982>:   lea    esp,[ebp-0x8]
   0x08048e04 <+985>:   pop    ecx
   0x08048e05 <+986>:   pop    ebx
   0x08048e06 <+987>:   pop    ebp
   0x08048e07 <+988>:   lea    esp,[ecx-0x4]
   0x08048e0a <+991>:   ret
End of assembler dump.
```

* Berikut ini adalah potongan kode yang berfungsi untuk mengambil input berupa password dari user lalu membandingkannya dengan password yang benar. Jika passwordnya benar, maka aplikasi tersebut akan menampilkan pesan bahwa passwordnya benar, demikian pula sebaliknya:
```
   0x08048cc1 <+662>:   lea    eax,[ebp-0x24]            // EAX = buffer untuk menyimpan password (str_input_password)
   0x08048cc4 <+665>:   push   eax                       // str_input_password
   0x08048cc5 <+666>:   push   0x804a600                 // cin
   0x08048cca <+671>:   call   0x8048890                 // cin >> str_input_password;
   0x08048ccf <+676>:   add    esp,0x10                  // normalisasi stack
   0x08048cd2 <+679>:   sub    esp,0x8                   //

   0x08048cd5 <+682>:   lea    eax,[ebp-0x20]            // EAX = str_valid_password
   0x08048cd8 <+685>:   push   eax                       // parameter2: str_valid_password
   0x08048cd9 <+686>:   lea    eax,[ebp-0x24]            // EAX = str_user_password
   0x08048cdc <+689>:   push   eax                       // parameter1: str_input_password
   0x08048cdd <+690>:   call   0x8048e82                 // fungsi untuk membandingkan password yang valid dengan input dari user
   0x08048ce2 <+695>:   add    esp,0x10                  // normalisasi stack
   0x08048ce5 <+698>:   test   al,al                     // str_valid_password == str_input_password ? (jika register AL = 0 berarti tidak sama)
   0x08048ce7 <+700>:   je     0x8048d00 <main+725>      // jika tidak sama, maka lompat ke alamat 0x8048d00 (tampilkan pesan salah) >-.
   0x08048ce9 <+702>:   sub    esp,0x8                   //                                                                            |
   0x08048cec <+705>:   push   0x804920e                 // "Ya, itu flagnya!"                                                         |
   0x08048cf1 <+710>:   push   0x804a6c0                 // cout                                                                       |
   0x08048cf6 <+715>:   call   0x8048880                 // cout << "Ya, itu flagnya!";                                                |
   0x08048cfb <+720>:   add    esp,0x10                  // normalisasi stack                                                          |
   0x08048cfe <+723>:   jmp    0x8048d15 <main+746>      // lompat ke alamat 0x8048d15 (keluar dari aplikasi)                          |
   0x08048d00 <+725>:   sub    esp,0x8                   // <--------------------------------------------------------------------------'
   0x08048d03 <+728>:   push   0x804921f                 // "Salah bro!"
   0x08048d08 <+733>:   push   0x804a6c0                 // cout
   0x08048d0d <+738>:   call   0x8048880                 // cout << "Salah bro!";</nowiki>
```

* Dari potongan kode di atas, pada alamat __0x08048cd5__ terdapat instruksi untuk memindahkan password yang benar dari alamat memori __EBP-0x24__ (variabel lokal) ke register __EAX__. Pasang _breakpoint_ pada alamat setelah instruksi tersebut, yaitu pada alamat __0x08048cd8__ seperti ini:
```
gdb> b *0x08048cd8
Breakpoint 1 at 0x8048cd8
```

* Jalankan aplikasi _veryhard_ tersebut dengan perintah seperti ini:
```
gdb> r
Starting program: /tmp/veryhard
Password : mesintempur

Breakpoint 1, 0x08048cd8 in main ()
```

* Bisa terlihat bahwa kita berada pada alamat setelah instruksi menyimpan alamat variabel password yang benar ke register __EAX__:
```
=> 0x8048cd8 <main+685>:   push   eax
   0x8048cd9 <main+686>:   lea    eax,[ebp-0x24]
   0x8048cdc <main+689>:   push   eax
   0x8048cdd <main+690>:
    call   0x8048e82 <__gnu_cxx::__enable_if ...
   0x8048ce2 <main+695>:   add    esp,0x10
```

* Selanjutnya, gunakan perintah seperti ini untuk menampilkan password yang benar:
```
gdb> x/s *($eax)
0x804fcac:  "f3br13nt_luqman_fa154l_GGWP_m4ul4na"
```

* Sedangkan password yang salah terdapat pada variabel lokal yang dapat diakses pada register __EBP-0x24__:
```
gdb> ##### tampilkan informasi stack frame
gdb> i frame
Stack level 0, frame at 0xffffc9f0:
 eip = 0x8048cd8 in main; saved eip = 0xf7bfd545
 Arglist at 0xffffc9d8, args:
 Locals at 0xffffc9d8, Previous frame's sp is 0xffffc9f0
 Saved registers:
  ebx at 0xffffc9d4, ebp at 0xffffc9d8, eip at 0xffffc9ec

gdb> ##### EBP berada pada alamat 0xffffc9d8, tampilkan isi (0xffffc9d8-0x24)
gdb> x/s *(0xffffc9d8-0x24)
0x804fd34:  "mesintempur"
```

* Saatnya menjalankan aplikasi _veryhard_ menggunakan password yang benar:
```
gdb> i break
Num     Type           Disp Enb Address    What
1       breakpoint     keep y   0x08048cd8 <main+685>
   breakpoint already hit 1 time
gdb> del 1
gdb> r
Starting program: /tmp/veryhard
Password : f3br13nt_luqman_fa154l_GGWP_m4ul4na
Ya, itu flagnya![Inferior 1 (process 23245) exited normally]
```

* Sebagai tambahan, Anda dapat melakukan rekonstruksi dari potongan kode di atas menjadi kode sumber aplikasi _veryhard_ tersebut. Berikut ini adalah rekonstruksi menggunakan bahasa pemrograman C++:
```cpp
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string a = "0123456789_faisal_yudo_hernawan_GWP_deny_febriant_luqman_hakim_rizky_maulana";
    size_t i = a.find("febriant");
    string s = a.substr(i);

    s.replace( 1, 1, a,  3, 1);
    s.replace( 4, 1, a,  1, 1);
    s.replace( 5, 1, a,  3, 1);
    s.replace(16, 2, a, 11, 2);
    s.replace(18, 1, a,  1, 1);
    s.replace(19, 1, a,  5, 1);
    s.replace(20, 1, a,  4, 1);
    s.replace(21, 1, a, 16, 1);
    s.replace(22, 1, a, 10, 1);
    s.replace(23, 1, a, 32, 1);
    s.replace(24, 1, a, 32, 1);
    s.replace(25, 1, a, 33, 1);
    s.replace(26, 1, a, 34, 1);
    s.replace(29, 1, a,  4, 1);
    s.replace(32, 1, a,  4, 1);

    string u;

    cout << "Password : ";
    cin >> u;

    if (s != u)
    {
      cout << "Salah bro!" << endl;
    } else {
      cout << "Ya, itu flagnya!" << endl;
    }

    return 0;
}
```

* Simpan kode sumber di atas dengan nama berkas _cinta.cpp_ sesuai dengan aplikasi asli _veryhard_ , lalu lakukan kompilasi dengan perintah seperti ini:
```
% g++ -Wall -s -o cinta cinta.cpp
```

* Jalankan aplikasi tersebut:
```
% ##### contoh menggunakan password yang salah
% ./cinta
Password : mesintempur
Salah bro!
%
% ##### contoh menggunakan password yang benar
% ./cinta
Password : f3br13nt_luqman_fa154l_GGWP_m4ul4na
Ya, itu flagnya!
```

* Bisa terlihat bahwa aplikasi hasil rekonstruksi berjalan seperti aplikasi aslinya, yaitu _veryhard_.


### Penutup

Sekian tutorial kali ini, semoga bermanfaat. Terima kasih kepada Tuhan Yang Maha Esa, Maxindo, N3, Deny Febriant, Faisal Yudo Hernawan, dan Anda yang telah membaca tutorial ini.


### Referensi

* [GDB: The GNU Project Debugger](https://sourceware.org/gdb/download/onlinedocs/)
