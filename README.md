# Analisis Respons Transien Rangkaian RLC Menggunakan Metode Runge-Kutta Orde 4
Repositori ini berisi implementasi numerik untuk menganalisis respons transien pada rangkaian RLC seri sebagai bagian dari Proyek Ujian Akhir Semester (UAS) mata kuliah Metode Numerik.

- Nama Lengkap: Fadhlureza Sebastian
- NPM: 2306161971

## Deskripsi Program
Program ini adalah sebuah simulator yang ditulis dalam bahasa C/C++ untuk menghitung dan menampilkan respons transien (muatan dan arus) dari sebuah rangkaian RLC seri. Studi kasus yang diangkat adalah rangkaian source-free (tanpa sumber tegangan eksternal setelah t=0) dengan kondisi underdamped.

Perilaku dinamis dari rangkaian RLC dapat dimodelkan oleh Persamaan Diferensial Biasa (PDB) linear orde dua. Untuk dapat menyelesaikannya secara numerik, program ini mengkonversi PDB orde dua tersebut menjadi sebuah sistem yang terdiri dari dua PDB orde satu.

Metode numerik yang diimplementasikan untuk menyelesaikan sistem PDB tersebut adalah Metode Runge-Kutta Orde Empat (RK4), yang dikenal memiliki akurasi tinggi dan stabilitas yang baik untuk berbagai jenis masalah rekayasa.

## Parameter Studi Kasus
Simulasi dijalankan menggunakan parameter berikut untuk menghasilkan respons underdamped:
- Resistansi (R): 2.0 Ω
- Induktansi (L): 1.0 H
- Kapasitansi (C): 0.25 F
- Muatan Awal (q₀): 1.0 C
- Arus Awal (i₀): 0.0 A
- Ukuran Langkah (h): 0.01 s

## Struktur Kode
Source code (`rlc_solver.c`) disusun dengan struktur yang jelas dan dilengkapi dengan komentar untuk menjelaskan setiap bagian penting:
- **Definisi Konstanta**: Mendefinisikan semua parameter rangkaian dan simulasi di bagian awal kode.
- **Fungsi PDB (`f1` dan `f2`)**: Dua fungsi ini merepresentasikan sistem PDB orde satu yang telah dikonversi dari persamaan RLC orde dua. `f1` menghitung `dq/dt = i`, dan `f2` menghitung `di/dt`.
- **Fungsi `main`**:
    - Menginisialisasi variabel waktu, muatan, dan arus sesuai kondisi awal.
    - Mencetak header tabel ke konsol.
    - Melakukan loop iterasi dari t=0 hingga t=10 detik.
    - Di dalam setiap iterasi, algoritma RK4 dijalankan untuk menghitung nilai muatan dan arus pada langkah waktu berikutnya.
    - Mencetak hasil perhitungan ke konsol pada setiap interval waktu yang ditentukan.

## Cara Menggunakan
Program ini dapat dikompilasi dan dijalankan pada sistem operasi yang memiliki compiler C/C++ seperti GCC.

1. **Kompilasi**

    Buka terminal atau command prompt, navigasikan ke direktori tempat Anda menyimpan file .c, lalu jalankan perintah berikut:
    ```
    gcc rlc_solver.c -o rlc_solver -lm
    ```
    - gcc: Perintah untuk memanggil compiler GCC.
    - rlc_solver.c: Nama file source code Anda.
    - -o rlc_solver: Menentukan nama file output (file executable) menjadi rlc_solver.
    - -lm: Perintah untuk me-link math library yang diperlukan oleh fungsi-fungsi pada math.h.

2. **Menjalankan Program**

    Setelah kompilasi berhasil, jalankan program dengan perintah:
    ```
    ./rlc_solver
    ```

3. **Output Program**

    Program akan mencetak hasil simulasi langsung ke terminal dalam format tabel yang dipisahkan oleh titik koma (;), sehingga mudah disalin ke aplikasi spreadsheet (seperti Microsoft Excel atau Google Sheets) untuk dianalisis lebih lanjut atau dibuat grafiknya.
