import java.util.Map;
import java.util.HashMap;
import java.util.Random;

public class Responder {
    private Map<String, String> responses;
    private Random random;
    
    public Responder(){
        responses = new HashMap<>();
        random = new Random();
        
        responses.put("login", "Terima kasih sudah melapor! Tim kami akan segera memeriksa kendala login Anda.");
        responses.put("password", "Lupa password? Tenang, klik saja tombol 'Lupa Password' di halaman FRS untuk reset.");
        responses.put("portal", "Pastikan portal diakses lewat browser versi terbaru dan koneksi internet stabil, ya.");
        responses.put("error", "Apakah muncul pesan error tertentu? Jika iya, mohon kirimkan tangkapan layarnya.");
        responses.put("crash", "Portal tiba-tiba crash? Ceritakan kapan terjadinya dan apa aktivitas Anda saat itu.");
        responses.put("slow", "Portal terasa lambat? Coba bersihkan cache browser atau gunakan jaringan lain yang lebih stabil.");
        responses.put("jadwal", "Apakah masalah berkaitan dengan jadwal mata kuliah atau proses pengisian FRS?");
        responses.put("kuota", "Periksa kembali kuota kelas sebelum mengisi FRS, bisa jadi kelas sudah penuh.");
        responses.put("pembayaran", "Sudah melakukan pembayaran SPP? Pastikan statusnya sudah 'Lunas' di portal pembayaran.");
        responses.put("koneksi", "Koneksi terputus? Pastikan jaringan lancar dan hindari penggunaan VPN.");
        responses.put("update", "Pastikan Anda menggunakan versi terbaru dari portal FRS agar semua fitur berfungsi normal.");
        responses.put("submit", "Gagal saat submit? Pastikan data sudah lengkap dan koneksi internet tidak terputus.");
        responses.put("notif", "Tidak dapat notifikasi FRS? Coba cek folder spam email atau notifikasi di dashboard portal.");
        responses.put("akses", "Tidak bisa mengakses portal? Coba login ulang setelah beberapa menit, mungkin sedang maintenance.");
        responses.put("verifikasi", "Sudah melakukan verifikasi akun? Pastikan email Anda sudah terkonfirmasi.");
        responses.put("mahasiswa", "Apakah Anda mahasiswa aktif? Coba pastikan status akademik Anda di portal.");
        responses.put("browser", "Beberapa masalah bisa terjadi karena browser. Coba gunakan Chrome atau Firefox versi terbaru.");
        responses.put("timeout", "Sesi Anda mungkin habis, silakan login kembali untuk melanjutkan.");
        responses.put("server", "Server sedang sibuk atau maintenance. Mohon tunggu beberapa saat sebelum mencoba lagi.");
        responses.put("data", "Periksa kembali data yang Anda input, pastikan tidak ada kolom yang kosong atau salah format.");
        responses.put("help", "Jika masih kesulitan, hubungi helpdesk melalui email resmi universitas untuk bantuan lanjutan.");
    }
    
    public String getResponse(String userInput) {
        String[] words = userInput.toLowerCase().split("\\s+");
        for(String w : words) {
            if(responses.containsKey(w)) {
                return responses.get(w);
            }
        }
        
        String[] generic = {
            "Bisa Anda jelaskan lebih detail.",
            "Saya belum mengerti, bisa diulangi?",
            "Bisakah Anda memberi detail lebih lanjut?"
        };
        return generic[random.nextInt(generic.length)];
    }
}