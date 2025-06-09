#include <stdio.h>
#include <math.h>

// --- Definisi Parameter dan Kondisi Awal Sistem ---
// Parameter rangkaian dan simulasi didefinisikan sesuai studi kasus pada laporan.
const double R = 2.0;    // Nilai resistansi (Ohm)
const double L = 1.0;    // Nilai induktansi (Henry)
const double C = 0.25;   // Nilai kapasitansi (Farad)
const double E = 0.0;    // Tegangan sumber (Volt), diasumsikan source-free.

// Kondisi awal untuk t = 0
const double q0 = 1.0;   // Muatan awal pada kapasitor (Coulomb)
const double i0 = 0.0;   // Arus awal pada rangkaian (Ampere)

// Pengaturan parameter simulasi numerik
const double t_final = 10.0; // Batas waktu akhir simulasi (detik)
const double h = 0.01;       // Ukuran langkah waktu (step size) untuk iterasi.

/*
 * ===================================================================================
 * FUNGSI UNTUK SISTEM PERSAMAAN DIFERENSIAL BIASA (PDB)
 * ===================================================================================
 * Persamaan diferensial orde dua untuk rangkaian RLC: L*q'' + R*q' + (1/C)*q = E
 * Persamaan ini dikonversi menjadi sebuah sistem PDB orde satu.
 *
 * Dengan mendefinisikan:
 * y1 = q (muatan)
 * y2 = q' = i (arus)
 *
 * Maka, sistem PDB yang ekivalen adalah:
 * 1. dy1/dt = y2                      --> direpresentasikan oleh fungsi f1
 * 2. dy2/dt = (E - R*y2 - y1/C)/L     --> direpresentasikan oleh fungsi f2
 *===================================================================================
 */

/**
 * @brief Menghitung turunan dari y1 (muatan) terhadap waktu.
 * @param t Waktu saat ini (tidak digunakan secara eksplisit dalam formula ini).
 * @param q Nilai muatan (y1) saat ini.
 * @param i Nilai arus (y2) saat ini.
 * @return dq/dt, yang nilainya sama dengan arus (i).
 */
double f1(double t, double q, double i) {
    return i;
}

/**
 * @brief Menghitung turunan dari y2 (arus) terhadap waktu.
 * @param t Waktu saat ini (tidak digunakan secara eksplisit dalam formula ini).
 * @param q Nilai muatan (y1) saat ini.
 * @param i Nilai arus (y2) saat ini.
 * @return di/dt, berdasarkan persamaan KVL rangkaian RLC.
 */
double f2(double t, double q, double i) {
    return (E - R * i - (1.0/C) * q) / L;
}

/**
 * @brief Fungsi utama program untuk menjalankan simulasi numerik.
 */
int main() {
    // Deklarasi variabel untuk proses simulasi
    double t;      // Variabel waktu
    double q;      // Variabel muatan, q(t)
    double i;      // Variabel arus, i(t)

    // Deklarasi variabel intermediate untuk metode Runge-Kutta 4
    double k1q, k2q, k3q, k4q;
    double k1i, k2i, k3i, k4i;
    
    // Variabel untuk mengontrol interval pencetakan hasil
    int steps_per_print;
    int step_counter;

    // Mengaplikasikan kondisi awal pada variabel simulasi
    t = 0.0;
    q = q0;
    i = i0;
    step_counter = 0;
    steps_per_print = (int)(1.0 / h); // Menghitung jumlah langkah per 1 detik

    // --- Menampilkan Header Tabel pada Konsol ---
    // Header tabel ini dapat disalin beserta datanya untuk dijadikan file CSV.
    printf("Waktu (s);Muatan q(t);Arus i(t)\n");

    // Menampilkan kondisi awal (t=0)
    printf("%.2f;%.6f;%.6f\n", t, q, i);

    // Loop utama untuk iterasi metode Runge-Kutta
    while (t < t_final) {
        // Langkah-langkah perhitungan intermediate values (k) untuk RK4
        k1q = h * f1(t, q, i);
        k1i = h * f2(t, q, i);

        k2q = h * f1(t + h/2.0, q + k1q/2.0, i + k1i/2.0);
        k2i = h * f2(t + h/2.0, q + k1q/2.0, i + k1i/2.0);

        k3q = h * f1(t + h/2.0, q + k2q/2.0, i + k2i/2.0);
        k3i = h * f2(t + h/2.0, q + k2q/2.0, i + k2i/2.0);

        k4q = h * f1(t + h, q + k3q, i + k3i);
        k4i = h * f2(t + h, q + k3q, i + k3i);

        // Memperbarui nilai variabel q dan i menggunakan formula RK4
        q = q + (1.0/6.0) * (k1q + 2.0*k2q + 2.0*k3q + k4q);
        i = i + (1.0/6.0) * (k1i + 2.0*k2i + 2.0*k3i + k4i);

        // Inkrementasi waktu simulasi dan penghitung langkah
        t = t + h;
        step_counter++;

        // Menampilkan hasil pada setiap kelipatan 1 detik
        if (step_counter % steps_per_print == 0) {
            printf("%.2f;%.6f;%.6f\n", t, q, i);
        }
    }
    
    // Memberikan notifikasi di konsol bahwa proses telah selesai
    // dan instruksi untuk menyimpan output secara manual.
    fprintf(stderr, "\n=========================================================\n");
    fprintf(stderr, "Proses simulasi telah selesai.\n");
    fprintf(stderr, "Salin output di atas dan simpan sebagai file 'output_rlc.csv'.\n");
    fprintf(stderr, "=========================================================\n");

    return 0; // Mengindikasikan program berakhir dengan sukses.
}
