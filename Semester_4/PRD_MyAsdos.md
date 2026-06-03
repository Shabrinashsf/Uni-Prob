# Product Requirements Document (PRD)

## MyAsdos — Sistem Informasi Gabungan Akademik Portal

**Versi:** 2.0  
**Tanggal:** 2025  
**Status:** Draft

---

## Daftar Isi

1. [Overview](#overview)
2. [Aktor & Role](#aktor--role)
3. [Modul & Fitur](#modul--fitur)
   - [M1 — Autentikasi & Manajemen Akun](#m1--autentikasi--manajemen-akun)
   - [M2 — Job Portal Lowongan Asdos](#m2--job-portal-lowongan-asdos)
   - [M3 — Manajemen Lamaran (Application)](#m3--manajemen-lamaran-application)
   - [M4 — Manajemen Asdos Aktif](#m4--manajemen-asdos-aktif)
   - [M5 — Sistem Pelaporan Asdos](#m5--sistem-pelaporan-asdos)
   - [M6 — Penerbitan SK Digital](#m6--penerbitan-sk-digital)
   - [M7 — Informasi Pencairan Honorarium](#m7--informasi-pencairan-honorarium)
   - [M8 — Notifikasi](#m8--notifikasi)
   - [M9 — Dashboard & Analitik Admin](#m9--dashboard--analitik-admin)

---

## Overview

MyAsdos adalah platform web yang mengintegrasikan seluruh siklus administrasi Asisten Dosen (Asdos) di ITS — dari rekrutmen, pelaporan, penerbitan SK, hingga pencairan honorarium — dalam satu sistem terpusat. PRD ini mendefinisikan fitur-fitur yang _possible_ untuk diimplementasikan, beserta detail fungsionalnya, dan akan menjadi acuan untuk pembuatan Use Case Diagram, Interaction Diagram, Activity Diagram, dan Class Diagram.

---

## Aktor & Role

| Role          | Kode       | Deskripsi                                          |
| ------------- | ---------- | -------------------------------------------------- |
| **Mahasiswa** | `STUDENT`  | Pelamar atau asdos aktif                           |
| **Dosen**     | `LECTURER` | Pembuka lowongan, pengelola asdos                  |
| **Admin**     | `ADMIN`    | Pengelola sistem, penerbit SK, pengelola pencairan |

> Catatan: `ADMIN` juga dapat melakukan task yang ditangani oleh role dosen.

## Modul & Fitur

---

### M1 — Autentikasi & Manajemen Akun

_Asumsi sistem: provisioning akun dilakukan via sinkronisasi myITS oleh admin (bukan use case terpisah)._

#### F-M1-01: Login via myITS SSO

- **Aktor:** Semua role
- **Deskripsi:** Pengguna masuk ke sistem menggunakan akun myITS (OAuth2/OIDC). Tidak ada login berbasis password lokal.
- **Input:** Redirect ke myITS SSO dan proses autentikasi myITS.
- **Output:** Session token (JWT); redirect ke dashboard sesuai role.
- **Aturan bisnis:**
  - Hanya akun yang sudah terdaftar di sistem dan berstatus `ACTIVE` yang dapat login.
  - Akun berstatus `SUSPENDED` ditolak dengan pesan yang sesuai.
  - Jika akun belum ada di sistem, tampilkan pesan bahwa akun belum diprovisioning oleh admin.

#### F-M1-02: Manajemen Profil

- **Aktor:** Semua role
- **Deskripsi:** Pengguna melihat dan memperbarui data profil mereka.
- **Data yang dapat diperbarui:**
  - Foto profil
  - Nomor telepon
  - Bio singkat (mahasiswa)
  - Link portofolio / CV (mahasiswa)
- **Data yang tidak dapat diperbarui secara mandiri:** Nama, NRP/NIP, email, jurusan (perlu request ke admin).

---

### M2 — Job Portal Lowongan Asdos

#### F-M2-01: Membuat Lowongan Asdos

- **Aktor:** `LECTURER`
- **Deskripsi:** Dosen memposting lowongan posisi asdos untuk mata kuliah tertentu.
- **Input:**
  - Mata kuliah (dipilih dari daftar mata kuliah yang diajar dosen; data diinput admin; pilihan dropdown)
  - Semester & tahun akademik (data diinput admin; pilihan dropdown)
  - Deskripsi tugas dan tanggung jawab asdos (opsional, teks)
  - Persyaratan pelamar (opsional, teks; contoh: IPK minimum, semester minimum, keahlian khusus)
  - Jumlah kuota asdos (atur dengan tombol +/-)
  - Tanggal buka & tutup pendaftaran (date picker)
  - Catatan tambahan (opsional)
- **Output:** Lowongan terpublikasi dengan status `OPEN`; mahasiswa dapat menemukan dan mendaftar.
- **Aturan bisnis:**
  - Satu dosen dapat memiliki lebih dari satu lowongan aktif (untuk mata kuliah berbeda).
  - Lowongan dengan kuota terisi penuh otomatis berstatus `FULL` namun masih bisa didaftar sebagai waiting list (opsional).
  - Setelah deadline, status otomatis berubah menjadi `CLOSED`.

#### F-M2-02: Mengedit / Menutup Lowongan

- **Aktor:** `LECTURER`
- **Deskripsi:** Dosen memperbarui informasi lowongan atau menutupnya lebih awal.
- **Aturan bisnis:** Lowongan hanya dapat diedit jika statusnya `OPEN`. Jika sudah ada pelamar, perubahan kuota tidak boleh kurang dari jumlah pelamar yang sudah diterima.

#### F-M2-03: Melihat Daftar Lowongan (Browse)

- **Aktor:** `STUDENT`
- **Deskripsi:** Mahasiswa menelusuri semua lowongan yang sedang buka.
- **Fitur filter & pencarian:**
  - Filter berdasarkan jurusan
  - Filter berdasarkan mata kuliah
  - Filter berdasarkan semester
  - Filter berdasarkan status (`OPEN`, `FULL`)
  - Pencarian teks (nama mata kuliah, nama dosen)
  - Urutkan berdasarkan: terbaru, deadline terdekat
- **Output:** Daftar kartu lowongan berisi: nama mata kuliah, nama dosen, jurusan, kuota tersisa, deadline, dan status.

#### F-M2-04: Melihat Detail Lowongan

- **Aktor:** `STUDENT`, `LECTURER` (lowongan milik sendiri), `ADMIN`
- **Deskripsi:** Melihat informasi lengkap satu lowongan.
- **Konten:** Semua data dari F-M2-01 ditambah jumlah pelamar saat ini dan status lowongan.

---

### M3 — Manajemen Lamaran (Application)

#### F-M3-01: Mendaftar ke Lowongan

- **Aktor:** `STUDENT`
- **Deskripsi:** Mahasiswa mengajukan lamaran ke lowongan yang sedang buka.
- **Input:**
  - Alasan ingin mendaftar menjadi asdos (teks, maks. 1.000 kata)
  - Upload CV atau file pendukung (PDF, maks. 5 MB) — opsional jika CV sudah ada di profil
  - Data tambahan sesuai persyaratan lowongan (lihat F-M2-01)
- **Output:** Lamaran tersimpan dengan status `PENDING`; notifikasi ke dosen pemilik lowongan.
- **Aturan bisnis:**
  - Mahasiswa tidak dapat mendaftar dua kali ke lowongan yang sama.
  - Mahasiswa tidak dapat mendaftar jika lowongan sudah `CLOSED`.
  - Mahasiswa tidak dapat mendaftar jika sudah diterima di lowongan lain pada semester yang sama untuk mata kuliah yang sama.

#### F-M3-02: Melihat & Menarik Lamaran

- **Aktor:** `STUDENT`
- **Deskripsi:** Mahasiswa melihat semua lamaran yang pernah mereka ajukan beserta statusnya, dan dapat menarik lamaran tertentu.
- **Status lamaran:**
  - `PENDING` — Menunggu ditinjau dosen
  - `REVIEWED` — Sudah dilihat dosen, belum ada keputusan
  - `ACCEPTED` — Diterima
  - `REJECTED` — Ditolak
  - `WITHDRAWN` — Dicabut oleh mahasiswa
- **Filter:** Status, semester.
- **Aturan bisnis:** Mahasiswa hanya dapat menarik lamaran jika statusnya masih `PENDING` atau `REVIEWED`.

#### F-M3-03: Meninjau & Memutuskan Pelamar (Dosen)

- **Aktor:** `LECTURER`
- **Deskripsi:** Dosen melihat daftar semua pelamar untuk satu lowongan miliknya dan memberikan keputusan.
- **Informasi per pelamar:** Nama, NRP, departemen, IPK (jika tersedia di profil), alasan mendaftar, CV.
- **Filter:** Status lamaran.
- **Input:** Keputusan + catatan untuk pelamar (opsional).
- **Output:**
  - Jika `ACCEPTED`: status lamaran berubah, record asdos aktif dibuat (lihat M4), notifikasi ke mahasiswa.
  - Jika `REJECTED`: status berubah, notifikasi ke mahasiswa beserta catatan dari dosen (jika ada).
- **Aturan bisnis:** Jika jumlah yang diterima sudah mencapai kuota, sistem menampilkan peringatan kepada dosen.

---

### M4 — Manajemen Asdos Aktif

#### F-M4-01: Melihat Asdos Aktif (Dosen)

- **Aktor:** `LECTURER`
- **Deskripsi:** Dosen melihat daftar semua asdos yang aktif untuk mata kuliahnya, per semester.
- **Informasi:** Nama, NRP, nomor telepon, status laporan terakhir, total jam/laporan yang sudah dikumpulkan.

#### F-M4-02: Melihat Riwayat Asdos (Mahasiswa)

- **Aktor:** `STUDENT`
- **Deskripsi:** Mahasiswa melihat rekam jejak pengalaman menjadi asdos — mata kuliah apa, semester berapa, dosen siapa.

---

### M5 — Sistem Pelaporan Asdos

#### F-M5-01: Submit Laporan Tanggung Jawab

- **Aktor:** `STUDENT` (asdos aktif)
- **Deskripsi:** Asdos mengisi dan mengumpulkan laporan tanggung jawab secara berkala (mingguan atau sesuai ketentuan dosen).
- **Input:**
  - File DOCX dengan template yang sudah disediakan; asdos melengkapinya di lokal masing-masing lalu mengunggah ke sistem
- **Output:** Laporan tersimpan dengan status `SUBMITTED`; notifikasi ke dosen.

#### F-M5-02: Submit Rencana Kerja

- **Aktor:** `STUDENT` (asdos aktif)
- **Deskripsi:** Asdos mengisi rencana kerja untuk periode mendatang.
- **Input:** File DOCX dengan template yang sudah disediakan; asdos melengkapinya di lokal masing-masing lalu mengunggah ke sistem

#### F-M5-03: Melihat Daftar Laporan Saya (termasuk laporan tanggung jawab dan rencana kerja)

- **Aktor:** `STUDENT`
- **Deskripsi:** Asdos melihat semua laporan yang pernah disubmit beserta statusnya dan feedback dari dosen.
- **Status laporan:**
  - `SUBMITTED` — Sudah disubmit, belum diverifikasi
  - `APPROVED` — Disetujui dosen
  - `REVISION` — Perlu revisi, ada catatan dari dosen
  - `REJECTED` — Ditolak

#### F-M5-04: Memverifikasi Laporan (Dosen)

- **Aktor:** `LECTURER`
- **Deskripsi:** Dosen meninjau dan memverifikasi laporan yang masuk dari asdos.
- **Input:** Status verifikasi (Approve / Minta Revisi / Reject), catatan/feedback, file hasil verifikasi (PDF) jika disetujui.
- **Output:** Status laporan diperbarui; notifikasi ke asdos.
- **Aturan bisnis:** File hasil verifikasi hanya dapat diunggah jika status `APPROVED`.

---

### M6 — Penerbitan SK Digital

#### F-M6-01: Upload SK Digital

- **Aktor:** `ADMIN`
- **Deskripsi:** Admin menerbitkan Surat Keterangan (SK) untuk asdos aktif berdasarkan data yang ada di sistem.
- **Input:**
  - Upload file SK Digital yang sudah diisi oleh TU (PDF atau DOCX)
- **Output:** File SK digital (PDF) digenerate dan disimpan di sistem; asdos yang bersangkutan dapat mengunduh.

#### F-M6-02: Mengunduh SK

- **Aktor:** `STUDENT`, `LECTURER` (untuk asdos mereka)
- **Deskripsi:** Asdos melihat daftar SK yang telah diterbitkan untuk mereka dan mengunduh dalam format PDF.

---

### M7 — Informasi Pencairan Honorarium

#### F-M7-01: Upload Laporan Pencairan Honorarium

- **Aktor:** `ADMIN`
- **Deskripsi:** Admin mengunggah file laporan pencairan honorarium dari pihak terkait.
- **Input:**
  - File laporan pencairan (PDF/XLSX)
- **Output:** File tersimpan dan dapat diakses oleh asdos.

#### F-M7-02: Melihat & Mengunduh Laporan Pencairan

- **Aktor:** `STUDENT`
- **Deskripsi:** Asdos melihat daftar laporan pencairan yang diunggah admin dan mengunduhnya untuk mengecek status pencairan.

---

### M8 — Notifikasi

#### F-M8-01: Notifikasi In-Platform

- **Aktor:** Semua role
- **Deskripsi:** Sistem menampilkan notifikasi di dalam platform (ikon lonceng) untuk berbagai event.
- **Trigger notifikasi per aktor:**

| Aktor      | Event                                        | Notifikasi                                                  |
| ---------- | -------------------------------------------- | ----------------------------------------------------------- |
| `STUDENT`  | Ada lowongan baru di departemen yang relevan | "Lowongan baru: Asdos [Mata Kuliah] oleh [Nama Dosen]"      |
| `STUDENT`  | Status lamaran berubah                       | "Lamaran kamu untuk [Mata Kuliah] [diterima/ditolak]"       |
| `STUDENT`  | Laporan diverifikasi                         | "Laporan periode [X] kamu telah [disetujui/diminta revisi]" |
| `STUDENT`  | Laporan pencairan diunggah                   | "Laporan pencairan honorarium [Periode X] sudah tersedia"   |
| `STUDENT`  | SK sudah diterbitkan                         | "SK Asdos kamu untuk [Mata Kuliah] sudah tersedia"          |
| `LECTURER` | Ada pelamar baru                             | "[Nama Mahasiswa] mendaftar ke lowongan [Mata Kuliah]"      |
| `LECTURER` | Laporan asdos masuk                          | "[Nama Asdos] mengumpulkan laporan periode [X]"             |
| `ADMIN`    | Akun baru terprovisioning dari myITS         | "Akun baru [Nama] berhasil ditambahkan dari myITS"          |

#### F-M8-02: Melihat & Mengelola Notifikasi

- **Aktor:** Semua role
- **Deskripsi:** Pengguna melihat daftar notifikasi, menandai sebagai sudah dibaca, atau menghapus notifikasi.

---

### M9 — Dashboard & Analitik Admin

#### F-M9-01: Dashboard Overview Admin

- **Aktor:** `ADMIN`
- **Deskripsi:** Halaman ringkasan yang menampilkan metrik utama sistem.
- **Konten:**
  - Total akun aktif (breakdown per role)
  - Total lowongan aktif saat ini
  - Total lamaran masuk semester ini
  - Total asdos aktif per departemen
  - Jumlah akun tersuspend
  - Jumlah SK yang belum diterbitkan

---
