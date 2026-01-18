import java.io.File;
import java.io.IOException;
import java.awt.Desktop;
//import java.net.URI;

public class SystemHelper {
    public static void openFile(String path) {
        if (path == null || path.equals("N/A")) {
            System.err.println("Ошибка: Файл книги не указан.");
            return;
        }
        
        try {
            Desktop desktop = Desktop.getDesktop();
            if (desktop.isSupported(Desktop.Action.OPEN)) {
                System.out.println("Попытка открыть файл: " + path);
                desktop.open(new File(path)); 
                System.out.println("Файл успешно открыт.");
            } else {
                System.err.println("Ошибка: Системное действие OPEN не поддерживается этой средой.");
            }
        } catch (IOException e) {
            System.err.println("Ошибка при попытке открыть файл: " + e.getMessage());
        }
    }
}