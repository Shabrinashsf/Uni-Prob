# Product Requirements Document (PRD)

## KarirHub — Platform Rekrutmen Digital

**Versi Dokumen:** 2.0  
**Tanggal:** 2025  
**Tim:** Nabila Shafa Rahayu (5025241150) · Shabrina Amalia Safaana (5025241157) · Rahma Sakinah (5025241222)  
**Mata Kuliah:** Manajemen Basis Data D — Teknik Informatika ITS  
**Dosen:** Shintami Chusnul Hidayati, S.Kom., M.Sc., Ph.D.

---

## Daftar Isi

1. [Ringkasan Eksekutif](#1-ringkasan-eksekutif)
2. [Tujuan Proyek](#2-tujuan-proyek)
3. [Pengguna Sistem (Actors)](#3-pengguna-sistem-actors)
4. [Proses Bisnis Sistem](#4-proses-bisnis-sistem)
5. [Aturan Bisnis Penting](#5-aturan-bisnis-penting-business-rules)
6. [Implementasi Materi MBD](#6-implementasi-materi-mbd)
7. [Tech Stack](#7-tech-stack)
8. [Arsitektur Aplikasi Frontend](#8-arsitektur-aplikasi-frontend)
9. [Halaman & Fitur Aplikasi](#9-halaman--fitur-aplikasi)
10. [Struktur Data Mock (Hardcoded)](#10-struktur-data-mock-hardcoded)
11. [Struktur Direktori Proyek](#11-struktur-direktori-proyek)
12. [Batasan & Asumsi](#12-batasan--asumsi)
13. [Deliverables Proyek](#13-deliverables-proyek)

---

## 1. Ringkasan Eksekutif

KarirHub adalah platform rekrutmen digital berbasis web yang menghubungkan pencari kerja dengan perusahaan secara efisien dan transparan. Platform ini mencakup alur rekrutmen end-to-end mulai dari publikasi lowongan, pengiriman lamaran, pengelolaan tahapan seleksi, penjadwalan wawancara, hingga notifikasi perubahan status secara real-time.

Seluruh pengguna berstatus setara — tidak ada fitur berbayar maupun tier premium. Fokus utama proyek ini adalah implementasi materi Manajemen Basis Data (MBD) pada sisi database (PostgreSQL), sementara frontend bersifat statis dan tidak terhubung ke database.

---

## 2. Tujuan Proyek

| Tujuan         | Keterangan                                                                                            |
| -------------- | ----------------------------------------------------------------------------------------------------- |
| **Akademik**   | Mengimplementasikan seluruh materi MBD: ERD, CDM, PDM, stored procedure, trigger, index, dan function |
| **Fungsional** | Memodelkan sistem rekrutmen yang realistis dan terstruktur                                            |
| **Frontend**   | Membuat tampilan antarmuka statis yang merepresentasikan alur sistem                                  |

---

## 3. Pengguna Sistem (Actors)

### 3.1 Pencari Kerja (Job Seeker)

Pengguna yang mendaftarkan diri, membangun profil karir, mencari lowongan, mengirim lamaran, dan memantau progres seleksi.

### 3.2 Perusahaan (Company)

Pengguna korporat yang memposting lowongan, mengelola lamaran masuk, mengatur tahapan rekrutmen, dan menjadwalkan wawancara. Akun perusahaan harus diverifikasi terlebih dahulu oleh Admin sebelum dapat memposting lowongan.

### 3.3 Admin Platform

Pengguna internal yang memverifikasi akun perusahaan, memantau aktivitas platform, dan mengelola data master (seperti skill).

---

## 4. Proses Bisnis Sistem

### 4.1 Manajemen Akun & Autentikasi

**Registrasi:**

- Setiap pengguna mendaftar dengan email unik dan password (disimpan dalam bentuk hash).
- Role ditentukan saat registrasi: `job_seeker`, `company`, atau `admin`.
- Setelah registrasi, sistem membuat profil turunan sesuai role:
  - `job_seeker` → record di tabel `job_seekers`
  - `company` → record di tabel `companies` (dengan `is_verified = FALSE`)
  - `admin` → record di tabel `admins`

**Login:**

- Autentikasi dilakukan melalui kombinasi email dan password.
- Sistem mengidentifikasi role dari tabel `accounts` untuk menentukan tampilan dan hak akses.

**Soft Delete Akun:**

- Akun yang dinonaktifkan tidak dihapus secara permanen. Kolom `deleted_at` diisi dengan timestamp penonaktifan. Record dengan `deleted_at IS NOT NULL` dianggap tidak aktif.

---

### 4.2 Manajemen Profil Pencari Kerja

Setelah registrasi, pencari kerja dapat melengkapi profil yang terdiri dari:

**Data Pribadi** (`job_seekers`):

- Nama lengkap, nomor telepon, tanggal lahir, jenis kelamin
- Alamat, kota, provinsi, foto profil, bio singkat

**Riwayat Pendidikan** (`educations`):

- Satu pencari kerja dapat memiliki banyak entri pendidikan.
- Setiap entri mencatat institusi, gelar, bidang studi, tahun mulai/selesai, GPA, dan status `is_ongoing`.
- Validasi: `end_year >= start_year`, GPA dalam rentang 0.00–4.00.

**Riwayat Pengalaman Kerja** (`work_experiences`):

- Satu pencari kerja dapat memiliki banyak pengalaman kerja.
- Setiap entri mencatat nama perusahaan, posisi, tanggal mulai/selesai, deskripsi, dan status `is_ongoing`.
- Validasi: `end_date >= start_date`.

**Skill** (`job_seeker_skills` + `skills`):

- Pencari kerja memilih skill dari master tabel `skills`.
- Setiap skill yang dipilih disertai level: `beginner`, `intermediate`, atau `advanced`.
- Satu skill hanya dapat ditambahkan sekali per pencari kerja (unique constraint).

---

### 4.3 Manajemen Profil Perusahaan

**Profil Perusahaan** (`companies`):

- Mencatat nama, industri, deskripsi, logo, website, alamat, kota, provinsi, dan jumlah karyawan.
- Status verifikasi (`is_verified`) dikelola oleh Admin.

**Verifikasi Perusahaan:**

- Admin memeriksa kelengkapan data perusahaan.
- Jika valid, Admin mengubah `is_verified = TRUE` dan mengisi `verified_at` (timestamp) serta `verified_by_id` (ID admin yang memverifikasi).
- Perusahaan yang belum terverifikasi tidak dapat memposting lowongan.

---

### 4.4 Manajemen Lowongan Kerja

**Pembuatan Lowongan** (`job_postings`):

- Hanya perusahaan yang sudah terverifikasi yang dapat membuat lowongan.
- Data lowongan meliputi: judul, deskripsi, persyaratan, kota, provinsi, rentang gaji (opsional), tipe pekerjaan, dan tipe kerja.
- Lowongan dibuat dengan status awal `draft`.

**Siklus Hidup Lowongan:**

```
draft → active → closed
                ↓ (otomatis oleh sistem jika melewati deadline)
             expired
```

| Status    | Deskripsi                                             |
| --------- | ----------------------------------------------------- |
| `draft`   | Sedang disusun, belum dipublikasikan                  |
| `active`  | Dipublikasikan, terbuka untuk lamaran                 |
| `closed`  | Ditutup manual oleh perusahaan                        |
| `expired` | Ditutup otomatis oleh sistem saat melewati `deadline` |

**Aturan bisnis penting:**

- Sistem secara otomatis mengubah status lowongan menjadi `expired` ketika tanggal `deadline` telah terlewati (diimplementasikan via trigger atau scheduled function di PostgreSQL).
- Lamaran hanya dapat dikirim ke lowongan berstatus `active`.

**Skill Lowongan** (`job_posting_skills`):

- Setiap lowongan dapat mencantumkan skill yang dibutuhkan dari master tabel `skills`.
- Setiap skill dikategorikan sebagai wajib (`is_required = TRUE`) atau nilai tambah (`is_required = FALSE`).

**Tahapan Rekrutmen** (`recruitment_stages`):

- Setiap lowongan memiliki tahapan seleksi yang dikonfigurasi oleh perusahaan.
- Tahapan bersifat sequential berdasarkan `stage_order` (dimulai dari 1).
- Contoh tahapan: Seleksi Administrasi (1) → Tes Online (2) → Interview HRD (3) → Interview User (4) → Offering (5).

---

### 4.5 Proses Lamaran Kerja

**Pengiriman Lamaran** (`applications`):

- Pencari kerja mengirim lamaran ke lowongan yang berstatus `active`.
- Satu pencari kerja hanya dapat mengirim satu lamaran per lowongan (unique constraint pada `job_seeker_id` + `job_posting_id`).
- Lamaran dapat disertai cover letter (teks bebas).
- Status awal lamaran adalah `in_progress`, dengan `current_stage_id = NULL` (belum masuk tahapan pertama).

**Status Lamaran:**

| Status        | Deskripsi                                   |
| ------------- | ------------------------------------------- |
| `in_progress` | Sedang berjalan, masih dalam proses seleksi |
| `hired`       | Kandidat diterima                           |
| `rejected`    | Kandidat tidak lolos                        |
| `withdrawn`   | Kandidat menarik diri                       |

**Penarikan Lamaran:**

- Pencari kerja dapat menarik lamaran (`withdrawn`) selama statusnya masih `in_progress`.

---

### 4.6 Pengelolaan Tahapan Seleksi (oleh Perusahaan)

**Perpindahan Tahapan** (`application_stage_histories`):

- Rekruter memindahkan kandidat dari satu tahapan ke tahapan berikutnya secara berurutan (tidak boleh melompat).
- Setiap perpindahan dicatat sebagai entri baru di `application_stage_histories` dengan:
  - `stage_id`: tahapan yang sedang dinilai
  - `status`: `pending` (sedang dinilai), `passed` (lolos), atau `failed` (tidak lolos)
  - `notes`: catatan opsional dari rekruter
  - `moved_by_id`: ID akun yang melakukan perubahan
  - `moved_at`: timestamp perpindahan
- Kolom `current_stage_id` di tabel `applications` diperbarui setiap kali terjadi perpindahan tahapan (diimplementasikan via trigger).

**Keputusan Akhir:**

- Jika kandidat `failed` di tahapan manapun → status lamaran diubah menjadi `rejected`.
- Jika kandidat `passed` di tahapan terakhir → status lamaran diubah menjadi `hired`.
- Kedua perubahan status ini diimplementasikan via trigger `trg_finalize_application`.

---

### 4.7 Penjadwalan Wawancara

**Jadwal Interview** (`interviews`):

- Rekruter dapat membuat jadwal wawancara untuk suatu lamaran pada tahapan tertentu.
- Data jadwal meliputi: waktu (`scheduled_at`), durasi (menit), lokasi fisik (untuk onsite), dan link meeting (untuk online).
- Satu lamaran pada satu tahapan dapat memiliki lebih dari satu sesi wawancara.

**Status Interview:**

| Status        | Deskripsi                     |
| ------------- | ----------------------------- |
| `scheduled`   | Terjadwal, belum dilaksanakan |
| `completed`   | Telah selesai dilaksanakan    |
| `cancelled`   | Dibatalkan                    |
| `rescheduled` | Dijadwalkan ulang             |

---

### 4.8 Sistem Notifikasi

**Notifikasi** (`notifications`):

- Notifikasi dikirimkan ke akun pengguna (`account_id`) saat terjadi perubahan status yang relevan.
- Setiap notifikasi memiliki judul (`title`) dan isi pesan (`message`).
- Status baca dilacak via kolom `is_read` (default `FALSE`).
- Notifikasi tidak dihapus secara permanen (menggunakan `deleted_at` untuk soft delete).

**Trigger notifikasi (diimplementasikan via trigger database):**

- Saat status lamaran berubah (misalnya: lolos tahapan, ditolak, diterima).
- Saat jadwal wawancara dibuat atau diperbarui.
- Saat status lowongan berubah menjadi `expired`.

---

### 4.9 Pengelolaan Data Master (Admin)

**Master Skill** (`skills`):

- Admin dapat menambahkan, mengedit, atau menonaktifkan skill dalam tabel master.
- Setiap skill memiliki nama (unik) dan kategori opsional.
- Skill yang sudah digunakan tidak dihapus secara permanen (soft delete).

---

## 5. Aturan Bisnis Penting (Business Rules)

| #     | Aturan                                                                                                   |
| ----- | -------------------------------------------------------------------------------------------------------- |
| BR-01 | Satu akun email hanya boleh terdaftar sekali                                                             |
| BR-02 | Satu pencari kerja hanya dapat mengirim satu lamaran per lowongan                                        |
| BR-03 | Lamaran hanya dapat dikirim ke lowongan berstatus `active`                                               |
| BR-04 | Perpindahan tahapan bersifat sequential — tidak dapat melompat urutan                                    |
| BR-05 | Perusahaan harus diverifikasi Admin sebelum dapat memposting lowongan                                    |
| BR-06 | Sistem otomatis mengubah status lowongan menjadi `expired` jika melewati `deadline`                      |
| BR-07 | Data tidak dihapus secara permanen — semua tabel menggunakan kolom `deleted_at` (soft delete)            |
| BR-08 | Password akun disimpan dalam bentuk hash, bukan plaintext                                                |
| BR-09 | GPA pendidikan harus dalam rentang 0.00 – 4.00                                                           |
| BR-10 | Salary range: `salary_max >= salary_min` jika keduanya diisi                                             |
| BR-11 | Satu skill hanya dapat ditambahkan sekali oleh satu pencari kerja; berlaku juga untuk skill per lowongan |
| BR-12 | Kandidat yang `failed` di tahapan manapun statusnya menjadi `rejected`                                   |
| BR-13 | Kandidat yang `passed` di tahapan terakhir statusnya menjadi `hired`                                     |
| BR-14 | Pencari kerja hanya dapat menarik lamaran (`withdrawn`) selama status masih `in_progress`                |

---

## 6. Implementasi Materi MBD

### 6.1 Struktur Database

| Komponen           | Detail                                                                                                                                                |
| ------------------ | ----------------------------------------------------------------------------------------------------------------------------------------------------- |
| **DBMS**           | PostgreSQL 14+                                                                                                                                        |
| **Normalisasi**    | 3NF — semua tabel bebas dari transitive dependency                                                                                                    |
| **Tipe Data Enum** | `account_role`, `gender_type`, `job_type`, `work_type`, `job_posting_status`, `application_status`, `stage_status`, `interview_status`, `skill_level` |
| **Primary Key**    | UUID dengan `gen_random_uuid()` untuk semua tabel                                                                                                     |
| **Soft Delete**    | Kolom `deleted_at TIMESTAMPTZ NULL` pada semua tabel utama                                                                                            |

---

### 6.2 Tabel Database (15 Tabel)

| #   | Tabel                         | Keterangan                                     |
| --- | ----------------------------- | ---------------------------------------------- |
| 1   | `accounts`                    | Pusat autentikasi semua pengguna               |
| 2   | `admins`                      | Profil admin (1:1 dengan accounts)             |
| 3   | `job_seekers`                 | Profil pencari kerja (1:1 dengan accounts)     |
| 4   | `educations`                  | Riwayat pendidikan pencari kerja (1:N)         |
| 5   | `work_experiences`            | Riwayat pengalaman kerja (1:N)                 |
| 6   | `skills`                      | Master data skill                              |
| 7   | `job_seeker_skills`           | Relasi M:M job_seekers ↔ skills                |
| 8   | `companies`                   | Profil perusahaan (1:1 dengan accounts)        |
| 9   | `job_postings`                | Lowongan kerja                                 |
| 10  | `job_posting_skills`          | Relasi M:M job_postings ↔ skills               |
| 11  | `recruitment_stages`          | Tahapan rekrutmen per lowongan                 |
| 12  | `applications`                | Lamaran kerja (M:M job_seekers ↔ job_postings) |
| 13  | `application_stage_histories` | Audit trail perpindahan tahapan                |
| 14  | `interviews`                  | Jadwal wawancara                               |
| 15  | `notifications`               | Notifikasi sistem ke pengguna                  |

---

### 6.3 Index

| Index                          | Tabel           | Kolom            | Kondisi                                  | Tujuan                        |
| ------------------------------ | --------------- | ---------------- | ---------------------------------------- | ----------------------------- |
| `idx_accounts_email`           | `accounts`      | `email`          | `deleted_at IS NULL`                     | Lookup login cepat            |
| `idx_accounts_role`            | `accounts`      | `role`           | `deleted_at IS NULL`                     | Filter per role               |
| `idx_job_seekers_city`         | `job_seekers`   | `city`           | `deleted_at IS NULL`                     | Pencarian seeker by kota      |
| `idx_job_postings_status`      | `job_postings`  | `status`         | `deleted_at IS NULL`                     | Filter lowongan aktif         |
| `idx_job_postings_city`        | `job_postings`  | `city`           | `deleted_at IS NULL`                     | Pencarian lowongan by kota    |
| `idx_job_postings_company`     | `job_postings`  | `company_id`     | —                                        | Dashboard perusahaan          |
| `idx_job_postings_deadline`    | `job_postings`  | `deadline`       | `status = 'active'`                      | Proses expiry otomatis        |
| `idx_applications_job_posting` | `applications`  | `job_posting_id` | `deleted_at IS NULL`                     | Daftar pelamar per lowongan   |
| `idx_applications_status`      | `applications`  | `status`         | `deleted_at IS NULL`                     | Filter status lamaran         |
| `idx_notifications_account`    | `notifications` | `account_id`     | `deleted_at IS NULL`                     | Inbox notifikasi              |
| `idx_notifications_unread`     | `notifications` | `account_id`     | `is_read = FALSE AND deleted_at IS NULL` | Badge notifikasi belum dibaca |

---

### 6.4 Trigger (Rencana Implementasi)

| Trigger                          | Event                                         | Fungsi                                                                                      |
| -------------------------------- | --------------------------------------------- | ------------------------------------------------------------------------------------------- |
| `trg_expire_job_postings`        | Scheduled / BEFORE INSERT on `applications`   | Mengubah status lowongan menjadi `expired` jika `deadline < NOW()`                          |
| `trg_update_current_stage`       | AFTER INSERT on `application_stage_histories` | Memperbarui `current_stage_id` di tabel `applications`                                      |
| `trg_notify_stage_change`        | AFTER UPDATE on `applications`                | Membuat record notifikasi ke pencari kerja saat status berubah                              |
| `trg_notify_interview_scheduled` | AFTER INSERT on `interviews`                  | Mengirim notifikasi jadwal wawancara ke pencari kerja                                       |
| `trg_finalize_application`       | AFTER UPDATE on `application_stage_histories` | Mengubah status aplikasi menjadi `hired` atau `rejected` berdasarkan hasil tahapan terakhir |

---

### 6.5 Stored Procedure & Function (Rencana Implementasi)

| Nama                                                           | Tipe      | Fungsi                                                                   |
| -------------------------------------------------------------- | --------- | ------------------------------------------------------------------------ |
| `fn_get_application_timeline(app_id UUID)`                     | Function  | Mengembalikan riwayat lengkap tahapan seleksi satu lamaran               |
| `fn_count_applications_per_posting(posting_id UUID)`           | Function  | Menghitung jumlah pelamar aktif per lowongan                             |
| `fn_search_jobs(keyword TEXT, city TEXT, job_type TEXT)`       | Function  | Pencarian lowongan berdasarkan keyword, kota, dan tipe pekerjaan         |
| `sp_advance_candidate(app_id UUID, notes TEXT, actor_id UUID)` | Procedure | Memindahkan kandidat ke tahapan seleksi berikutnya                       |
| `sp_reject_candidate(app_id UUID, notes TEXT, actor_id UUID)`  | Procedure | Menolak kandidat dan mengisi riwayat tahapan dengan status `failed`      |
| `sp_close_job_posting(posting_id UUID)`                        | Procedure | Menutup lowongan secara manual (ubah status ke `closed`)                 |
| `sp_expire_overdue_postings()`                                 | Procedure | Scan semua lowongan aktif yang melewati deadline, ubah menjadi `expired` |

---

## 7. Tech Stack

### 7.1 Database Layer

| Komponen                    | Teknologi                |
| --------------------------- | ------------------------ |
| DBMS                        | **PostgreSQL 14+**       |
| DDL Management              | SQL script (`.sql` file) |
| Stored Procedure / Function | PL/pgSQL                 |
| Trigger                     | PL/pgSQL                 |

### 7.2 Frontend Layer

> **Catatan Penting:** Frontend bersifat **statis** sepenuhnya. Tidak ada koneksi ke database maupun backend. Data yang ditampilkan adalah data dummy/hardcoded untuk keperluan visualisasi antarmuka. Next.js digunakan sebagai framework, namun hanya memanfaatkan fitur rendering dan routing-nya — tanpa API routes maupun server-side data fetching.

| Komponen         | Teknologi                                              |
| ---------------- | ------------------------------------------------------ |
| Framework        | **Next.js 14+** (App Router)                           |
| Bahasa           | **TypeScript**                                         |
| Styling          | **Tailwind CSS v3**                                    |
| Komponen UI      | **shadcn/ui**                                          |
| State Management | React `useState` / `useContext` (lokal, tanpa backend) |
| Routing          | Next.js App Router (file-based routing)                |
| Data Dummy       | Hardcoded TypeScript object / JSON lokal               |
| Package Manager  | **npm**                                                |
| Build Tool       | Next.js built-in (Webpack / Turbopack)                 |

---

## 8. Arsitektur Aplikasi Frontend

### 8.1 Simulasi Autentikasi

Karena frontend bersifat statis tanpa backend, autentikasi disimulasikan menggunakan React Context:

```typescript
// src/context/AppContext.tsx
interface AppContextType {
  activeRole: "job_seeker" | "company" | "admin" | null;
  setActiveRole: (role: AccountRole | null) => void;
  currentUser: JobSeeker | Company | Admin | null;
}
```

Pengguna "login" dengan memilih role dan akun dari daftar dummy. State tersimpan di context dan direset saat halaman di-refresh (tidak ada persistence).

### 8.2 Pola Data

Semua data hardcoded tersimpan di `src/data/` sebagai array TypeScript yang saling berelasi via ID:

```typescript
// src/data/jobs.ts — contoh
import { JobPosting } from "@/types";
export const jobPostings: JobPosting[] = [
  {
    id: "jp-001",
    companyId: "company-001",
    title: "Frontend Engineer",
    status: "active",
    // ...
  },
];
```

Relasi antar data (misal: mengambil company dari job posting) dilakukan dengan `.find()` di dalam komponen, menyimulasikan JOIN query database.

---

## 9. Halaman & Fitur Aplikasi

### 9.1 Halaman Publik

| Halaman                  | Route             | Deskripsi                                                                      |
| ------------------------ | ----------------- | ------------------------------------------------------------------------------ |
| Landing Page             | `/`               | Beranda platform, daftar lowongan unggulan, statistik platform, CTA registrasi |
| Daftar Lowongan          | `/jobs`           | Semua lowongan aktif dengan filter kota, tipe kerja, tipe pekerjaan            |
| Detail Lowongan          | `/jobs/[id]`      | Detail lengkap lowongan, skill dibutuhkan, tahapan seleksi, info perusahaan    |
| Profil Perusahaan Publik | `/companies/[id]` | Informasi perusahaan dan daftar lowongan aktifnya                              |
| Login                    | `/login`          | Form autentikasi (UI only, simulasi role switching)                            |
| Register                 | `/register`       | Form registrasi dengan pilihan role (UI only)                                  |

**Detail halaman Landing Page:**

- Hero section dengan search bar (keyword, kota, tipe pekerjaan)
- Statistik platform: total lowongan aktif, total perusahaan, total pencari kerja
- Grid lowongan terbaru
- Carousel/grid perusahaan terverifikasi
- Call-to-action daftar sebagai pencari kerja atau perusahaan

**Detail halaman Daftar Lowongan (`/jobs`):**

- Grid/list card lowongan: judul, nama perusahaan, logo, kota, `job_type`, `work_type`, rentang gaji, deadline
- Filter sidebar: kota/provinsi, `job_type`, `work_type`, skill yang dibutuhkan
- Hanya lowongan berstatus `active` yang ditampilkan

**Detail halaman Detail Lowongan (`/jobs/[id]`):**

- Informasi lengkap: deskripsi, persyaratan, lokasi, gaji, deadline
- Badge skill: required (solid) vs nice-to-have (outline), berdasarkan `is_required`
- Stepper/list tahapan rekrutmen dari `recruitment_stages`
- Card informasi perusahaan (nama, industri, jumlah karyawan, badge verifikasi)
- Tombol "Lamar Sekarang" (simulasi — menambahkan ke aplikasi di state lokal)

---

### 9.2 Halaman Pencari Kerja

| Halaman         | Route                       | Deskripsi                                                  |
| --------------- | --------------------------- | ---------------------------------------------------------- |
| Dashboard       | `/seeker/dashboard`         | Ringkasan lamaran aktif, notifikasi terbaru                |
| Profil Saya     | `/seeker/profile`           | Tampilan dan edit profil, pendidikan, pengalaman, skill    |
| Riwayat Lamaran | `/seeker/applications`      | Daftar semua lamaran beserta status dan tahapan terkini    |
| Detail Lamaran  | `/seeker/applications/[id]` | Timeline tahapan seleksi, jadwal wawancara, riwayat status |
| Notifikasi      | `/seeker/notifications`     | Inbox notifikasi sistem                                    |

**Detail `/seeker/dashboard`:**

- Summary card: total lamaran, lamaran aktif, lamaran diterima, lamaran ditolak
- Daftar lamaran terbaru dengan status
- Notifikasi terbaru (3-5 teratas)

**Detail `/seeker/profile`:**

- Tab **Identitas:** foto profil, nama, telepon, tanggal lahir, gender, kota, provinsi, bio
- Tab **Pendidikan:** daftar entri pendidikan dengan tombol tambah/edit/hapus (state lokal)
- Tab **Pengalaman Kerja:** daftar pengalaman dengan tombol tambah/edit/hapus (state lokal)
- Tab **Skill:** daftar skill dengan level badge; pilih dari master `skills`

**Detail `/seeker/applications`:**

- Card per lamaran: judul lowongan, nama perusahaan, tanggal lamar, status (`in_progress` / `hired` / `rejected` / `withdrawn`)
- Badge warna per status
- Tombol "Tarik Lamaran" untuk lamaran berstatus `in_progress` (mengubah status di state lokal)

**Detail `/seeker/applications/[id]`:**

- Stepper/timeline tahapan rekrutmen dari `application_stage_histories`
- Per tahapan: nama stage, status (pending/passed/failed), catatan rekruter, tanggal perpindahan
- Card jadwal wawancara (jika ada): tanggal, durasi, lokasi/link meeting, status interview

**Detail `/seeker/notifications`:**

- List notifikasi: judul, pesan, waktu, status baca
- Notifikasi belum dibaca di-highlight
- Simulasi mark as read (toggle `is_read` di state lokal)

---

### 9.3 Halaman Perusahaan

| Halaman           | Route                         | Deskripsi                                                        |
| ----------------- | ----------------------------- | ---------------------------------------------------------------- |
| Dashboard         | `/company/dashboard`          | Ringkasan lowongan aktif, jumlah pelamar masuk                   |
| Kelola Lowongan   | `/company/postings`           | Daftar semua lowongan (draft, aktif, tutup, expired)             |
| Buat Lowongan     | `/company/postings/new`       | Form pembuatan lowongan beserta tahapan rekrutmen                |
| Edit Lowongan     | `/company/postings/[id]/edit` | Form edit lowongan                                               |
| Detail Lowongan   | `/company/postings/[id]`      | Daftar pelamar per lowongan beserta status tahapan               |
| Detail Pelamar    | `/company/applicants/[id]`    | Timeline seleksi kandidat, form pindah tahapan, jadwal wawancara |
| Profil Perusahaan | `/company/profile`            | Tampilan dan edit profil perusahaan                              |
| Notifikasi        | `/company/notifications`      | Inbox notifikasi perusahaan                                      |

**Detail `/company/dashboard`:**

- Summary card: total lowongan (breakdown per status), total pelamar, lowongan aktif
- Tabel lowongan aktif dengan jumlah pelamar masing-masing
- Grafik sederhana lamaran masuk (data statis)

**Detail `/company/postings/new` (Buat Lowongan):**

- **Informasi Dasar:** judul, deskripsi, persyaratan, kota, provinsi
- **Klasifikasi:** `job_type` (dropdown), `work_type` (dropdown)
- **Gaji:** `salary_min`, `salary_max` (opsional)
- **Deadline:** date picker
- **Skill Dibutuhkan:** multi-select dari master skill + toggle required/nice-to-have
- **Tahapan Rekrutmen:** input daftar tahapan dengan nama dan urutan (add/remove)

**Detail `/company/postings/[id]` (Detail Lowongan):**

- Ringkasan lowongan dan kontrol status (aktifkan, tutup)
- Tabel pelamar: nama, stage saat ini, status lamaran, tanggal lamar
- Filter berdasarkan stage dan status
- Klik baris pelamar → navigasi ke `/company/applicants/[id]`

**Detail `/company/applicants/[id]` (Detail Pelamar):**

- Informasi kandidat: nama, kota, skill
- Timeline riwayat perpindahan tahapan dari `application_stage_histories`
- Tombol "Pindahkan ke Tahapan Berikutnya" dan "Tolak Kandidat" (simulasi di state lokal)
- Form jadwal wawancara: tanggal & waktu, durasi, tipe (onsite/online), lokasi/meeting link

---

### 9.4 Halaman Admin

| Halaman               | Route              | Deskripsi                                                |
| --------------------- | ------------------ | -------------------------------------------------------- |
| Dashboard             | `/admin/dashboard` | Statistik platform (total user, lowongan aktif, lamaran) |
| Verifikasi Perusahaan | `/admin/verify`    | Daftar perusahaan pending verifikasi                     |
| Kelola Skill          | `/admin/skills`    | CRUD master data skill                                   |
| Pantau Aktivitas      | `/admin/activity`  | Log aktivitas platform                                   |

**Detail `/admin/dashboard`:**

- Total akun terdaftar (breakdown per role)
- Total perusahaan (terverifikasi vs belum)
- Total lowongan aktif & total lamaran
- Daftar perusahaan menunggu verifikasi

**Detail `/admin/verify`:**

- Tabel perusahaan: nama, industri, kota, `is_verified`, `verified_at`
- Filter: belum terverifikasi / sudah terverifikasi
- Tombol "Verifikasi" — set `is_verified = true`, isi `verified_at` dan `verified_by_id` di state lokal
- Klik perusahaan → lihat detail profil lengkap

**Detail `/admin/skills`:**

- Tabel master skill: nama, kategori, status (aktif/nonaktif)
- Tombol tambah skill baru (form modal)
- Tombol edit nama/kategori
- Tombol nonaktifkan (soft delete di state lokal)

**Detail `/admin/activity`:**

- Log aktivitas simulasi: registrasi akun baru, lowongan diposting, lamaran dikirim
- Filter berdasarkan tipe aktivitas

---

## 10. Struktur Data Mock (Hardcoded)

### 10.1 TypeScript Interfaces (merefleksikan skema DDL)

```typescript
// src/types/index.ts

export type AccountRole = "job_seeker" | "company" | "admin";
export type GenderType = "male" | "female" | "other";
export type JobType = "full_time" | "part_time" | "contract" | "internship";
export type WorkType = "remote" | "onsite" | "hybrid";
export type JobPostingStatus = "draft" | "active" | "closed" | "expired";
export type ApplicationStatus =
  | "in_progress"
  | "hired"
  | "rejected"
  | "withdrawn";
export type StageStatus = "pending" | "passed" | "failed";
export type InterviewStatus =
  | "scheduled"
  | "completed"
  | "cancelled"
  | "rescheduled";
export type SkillLevel = "beginner" | "intermediate" | "advanced";

export interface Account {
  id: string;
  email: string;
  password: string;
  role: AccountRole;
  createdAt: string;
  updatedAt: string;
  deletedAt: string | null;
}
export interface JobSeeker {
  id: string;
  accountId: string;
  fullName: string;
  phone: string | null;
  birthDate: string | null;
  gender: GenderType | null;
  address: string | null;
  city: string | null;
  province: string | null;
  bio: string | null;
  profileImg: string | null;
  createdAt: string;
  updatedAt: string;
  deletedAt: string | null;
}
export interface Education {
  id: string;
  jobSeekerId: string;
  institution: string;
  degree: string;
  fieldOfStudy: string | null;
  startYear: number;
  endYear: number | null;
  isOngoing: boolean;
  gpa: number | null;
  createdAt: string;
  updatedAt: string;
  deletedAt: string | null;
}
export interface WorkExperience {
  id: string;
  jobSeekerId: string;
  companyName: string;
  position: string;
  startDate: string;
  endDate: string | null;
  isOngoing: boolean;
  description: string | null;
  createdAt: string;
  updatedAt: string;
  deletedAt: string | null;
}
export interface Skill {
  id: string;
  name: string;
  category: string | null;
  createdAt: string;
  updatedAt: string;
  deletedAt: string | null;
}
export interface JobSeekerSkill {
  id: string;
  jobSeekerId: string;
  skillId: string;
  level: SkillLevel;
  createdAt: string;
  updatedAt: string;
  deletedAt: string | null;
}
export interface Company {
  id: string;
  accountId: string;
  name: string;
  industry: string | null;
  description: string | null;
  logoUrl: string | null;
  website: string | null;
  address: string | null;
  city: string | null;
  province: string | null;
  employeeCount: number;
  isVerified: boolean;
  verifiedAt: string | null;
  verifiedById: string | null;
  createdAt: string;
  updatedAt: string;
  deletedAt: string | null;
}
export interface JobPosting {
  id: string;
  companyId: string;
  title: string;
  description: string;
  requirements: string | null;
  city: string | null;
  province: string | null;
  salaryMin: number | null;
  salaryMax: number | null;
  jobType: JobType;
  workType: WorkType;
  status: JobPostingStatus;
  deadline: string;
  createdAt: string;
  updatedAt: string;
  deletedAt: string | null;
}
export interface JobPostingSkill {
  id: string;
  jobPostingId: string;
  skillId: string;
  isRequired: boolean;
  createdAt: string;
  updatedAt: string;
  deletedAt: string | null;
}
export interface RecruitmentStage {
  id: string;
  jobPostingId: string;
  stageName: string;
  stageOrder: number;
  createdAt: string;
  updatedAt: string;
  deletedAt: string | null;
}
export interface Application {
  id: string;
  jobSeekerId: string;
  jobPostingId: string;
  currentStageId: string | null;
  status: ApplicationStatus;
  coverLetter: string | null;
  appliedAt: string;
  createdAt: string;
  updatedAt: string;
  deletedAt: string | null;
}
export interface ApplicationStageHistory {
  id: string;
  applicationId: string;
  stageId: string;
  status: StageStatus;
  notes: string | null;
  movedById: string;
  movedAt: string;
  createdAt: string;
  updatedAt: string;
  deletedAt: string | null;
}
export interface Interview {
  id: string;
  applicationId: string;
  stageId: string;
  scheduledAt: string;
  durationMinutes: number;
  location: string | null;
  meetingLink: string | null;
  interviewerNotes: string | null;
  status: InterviewStatus;
  createdAt: string;
  updatedAt: string;
  deletedAt: string | null;
}
export interface Notification {
  id: string;
  accountId: string;
  title: string;
  message: string;
  isRead: boolean;
  createdAt: string;
  deletedAt: string | null;
}
```

### 10.2 File Data Dummy

```
src/data/
├── accounts.ts         # accounts + admins
├── job-seekers.ts      # job_seekers + educations + work_experiences + job_seeker_skills
├── companies.ts        # companies
├── jobs.ts             # job_postings + job_posting_skills + recruitment_stages
├── applications.ts     # applications + application_stage_histories + interviews
├── skills.ts           # skills (master)
└── notifications.ts    # notifications
```

Data dikelompokkan per domain, bukan per tabel, untuk memudahkan import di komponen.

---

## 11. Struktur Direktori Proyek

```
karirhub/
├── database/
│   ├── karirhub_ddl_free.sql        # DDL utama (15 tabel, enum, index, constraint)
│   ├── triggers.sql                  # Semua trigger (5 trigger)
│   ├── functions.sql                 # Stored functions (3 function)
│   ├── procedures.sql                # Stored procedures (4 procedure)
│   └── seed.sql                      # Data dummy untuk demo database
│
└── frontend/                         # Next.js App Router project
    ├── public/
    │   └── images/                   # Aset gambar statis (logo, ilustrasi)
    ├── src/
    │   ├── app/                      # App Router — setiap folder = route
    │   │   ├── layout.tsx            # Root layout (Navbar, Footer)
    │   │   ├── page.tsx              # Landing page (/)
    │   │   │
    │   │   ├── (auth)/               # Route group autentikasi
    │   │   │   ├── login/
    │   │   │   │   └── page.tsx      # /login
    │   │   │   └── register/
    │   │   │       └── page.tsx      # /register
    │   │   │
    │   │   ├── jobs/                 # Halaman publik lowongan
    │   │   │   ├── page.tsx          # /jobs  — daftar lowongan + filter
    │   │   │   └── [id]/
    │   │   │       └── page.tsx      # /jobs/[id] — detail lowongan
    │   │   │
    │   │   ├── companies/            # Halaman publik profil perusahaan
    │   │   │   └── [id]/
    │   │   │       └── page.tsx      # /companies/[id]
    │   │   │
    │   │   ├── seeker/               # Halaman pencari kerja (simulasi auth)
    │   │   │   ├── layout.tsx        # Layout dashboard seeker (sidebar)
    │   │   │   ├── dashboard/
    │   │   │   │   └── page.tsx      # /seeker/dashboard
    │   │   │   ├── profile/
    │   │   │   │   └── page.tsx      # /seeker/profile
    │   │   │   ├── applications/
    │   │   │   │   ├── page.tsx      # /seeker/applications — riwayat lamaran
    │   │   │   │   └── [id]/
    │   │   │   │       └── page.tsx  # /seeker/applications/[id] — detail lamaran
    │   │   │   └── notifications/
    │   │   │       └── page.tsx      # /seeker/notifications
    │   │   │
    │   │   ├── company/              # Halaman perusahaan (simulasi auth)
    │   │   │   ├── layout.tsx        # Layout dashboard company (sidebar)
    │   │   │   ├── dashboard/
    │   │   │   │   └── page.tsx      # /company/dashboard
    │   │   │   ├── profile/
    │   │   │   │   └── page.tsx      # /company/profile
    │   │   │   ├── postings/
    │   │   │   │   ├── page.tsx      # /company/postings — kelola lowongan
    │   │   │   │   ├── new/
    │   │   │   │   │   └── page.tsx  # /company/postings/new — buat lowongan
    │   │   │   │   └── [id]/
    │   │   │   │       ├── page.tsx  # /company/postings/[id] — detail lowongan
    │   │   │   │       └── edit/
    │   │   │   │           └── page.tsx  # /company/postings/[id]/edit
    │   │   │   ├── applicants/
    │   │   │   │   └── [id]/
    │   │   │   │       └── page.tsx  # /company/applicants/[id] — detail pelamar
    │   │   │   └── notifications/
    │   │   │       └── page.tsx      # /company/notifications
    │   │   │
    │   │   └── admin/                # Halaman admin (simulasi auth)
    │   │       ├── layout.tsx        # Layout dashboard admin (sidebar)
    │   │       ├── dashboard/
    │   │       │   └── page.tsx      # /admin/dashboard
    │   │       ├── verify/
    │   │       │   └── page.tsx      # /admin/verify — verifikasi perusahaan
    │   │       ├── skills/
    │   │       │   └── page.tsx      # /admin/skills — kelola master skill
    │   │       └── activity/
    │   │           └── page.tsx      # /admin/activity — pantau aktivitas
    │   │
    │   ├── components/               # Komponen reusable
    │   │   ├── ui/                   # Komponen shadcn/ui (auto-generated)
    │   │   │   ├── button.tsx
    │   │   │   ├── card.tsx
    │   │   │   ├── badge.tsx
    │   │   │   ├── dialog.tsx
    │   │   │   ├── input.tsx
    │   │   │   ├── select.tsx
    │   │   │   ├── table.tsx
    │   │   │   └── ...
    │   │   ├── layout/               # Komponen layout global
    │   │   │   ├── Navbar.tsx
    │   │   │   ├── Footer.tsx
    │   │   │   └── Sidebar.tsx
    │   │   ├── jobs/                 # Komponen khusus lowongan
    │   │   │   ├── JobCard.tsx
    │   │   │   └── JobFilter.tsx
    │   │   ├── applications/         # Komponen alur lamaran
    │   │   │   ├── StageTimeline.tsx
    │   │   │   └── ApplicationCard.tsx
    │   │   └── shared/               # Komponen umum lainnya
    │   │       ├── SkillBadge.tsx
    │   │       └── StatusBadge.tsx
    │   │
    │   ├── context/
    │   │   └── AppContext.tsx         # Global state: role aktif, current user
    │   │
    │   ├── data/                     # Data dummy hardcoded (pengganti DB)
    │   │   ├── accounts.ts
    │   │   ├── job-seekers.ts
    │   │   ├── companies.ts
    │   │   ├── jobs.ts
    │   │   ├── applications.ts
    │   │   ├── skills.ts
    │   │   └── notifications.ts
    │   │
    │   ├── types/                    # TypeScript type definitions
    │   │   └── index.ts              # Semua interface & type (merefleksikan DDL)
    │   │
    │   └── lib/                      # Helper / utility functions
    │       └── utils.ts              # cn() dari shadcn/ui, formatDate, formatSalary, dll.
    │
    ├── components.json               # Konfigurasi shadcn/ui
    ├── tailwind.config.ts            # Konfigurasi Tailwind CSS
    ├── tsconfig.json                 # Konfigurasi TypeScript
    ├── next.config.ts                # Konfigurasi Next.js
    └── package.json
```

---

## 12. Batasan & Asumsi

| #    | Batasan / Asumsi                                                          |
| ---- | ------------------------------------------------------------------------- |
| A-01 | Frontend tidak terhubung ke database — semua data bersifat statis/dummy   |
| A-02 | Tidak ada backend server (Node.js, Django, dll.) dalam scope proyek ini   |
| A-03 | Autentikasi hanya disimulasikan di frontend (UI only, via React Context)  |
| A-04 | DBMS yang digunakan adalah PostgreSQL 14+                                 |
| A-05 | Semua pengguna (job_seeker dan company) setara — tidak ada fitur berbayar |
| A-06 | Soft delete diterapkan di semua tabel (menggunakan kolom `deleted_at`)    |
| A-07 | UUID digunakan sebagai primary key di seluruh tabel                       |
| A-08 | Tahapan rekrutmen bersifat sequential — tidak dapat melompat urutan       |

---

## 13. Deliverables Proyek

| Deliverable             | Keterangan                                                                      |
| ----------------------- | ------------------------------------------------------------------------------- |
| ERD                     | Entity Relationship Diagram lengkap                                             |
| CDM                     | Conceptual Data Model                                                           |
| PDM                     | Physical Data Model                                                             |
| DDL Script              | `karirhub_ddl_free.sql` (15 tabel, enum, index, constraint)                     |
| Trigger Script          | `triggers.sql` — implementasi 5 trigger di PostgreSQL                           |
| Function Script         | `functions.sql` — 3 stored function PL/pgSQL                                    |
| Stored Procedure Script | `procedures.sql` — 4 stored procedure PL/pgSQL                                  |
| Seed Script             | `seed.sql` — data dummy untuk demo database                                     |
| Frontend Statis         | Aplikasi Next.js (TypeScript + Tailwind CSS + shadcn/ui) tanpa koneksi database |
| Dokumentasi             | PRD ini dan laporan akhir                                                       |

---

_Dokumen ini merupakan bagian dari Final Project mata kuliah Manajemen Basis Data D, Program Studi Teknik Informatika, Institut Teknologi Sepuluh Nopember (ITS)._
